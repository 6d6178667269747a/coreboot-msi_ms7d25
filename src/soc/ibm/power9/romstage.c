/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <cpu/power/vpd.h>
#include <cpu/power/istep_8.h>
#include <cpu/power/istep_9.h>
#include <cpu/power/istep_10.h>
#include <cpu/power/istep_13.h>
#include <cpu/power/istep_14.h>
#include <cpu/power/proc.h>
#include <drivers/ipmi/ipmi_if.h>
#include <drivers/ipmi/ipmi_ops.h>
#include <program_loading.h>
#include <lib.h>	// hexdump
#include <spd_bin.h>
#include <endian.h>
#include <cbmem.h>
#include <timestamp.h>

#include "fsi.h"
#include "pci.h"

mcbist_data_t mem_data[MAX_CHIPS];

static void dump_mca_data(mca_data_t *mca)
{
	printk(BIOS_SPEW, "\tCL =      %d\n", mca->cl);
	printk(BIOS_SPEW, "\tCCD_L =   %d\n", mca->nccd_l);
	printk(BIOS_SPEW, "\tWTR_S =   %d\n", mca->nwtr_s);
	printk(BIOS_SPEW, "\tWTR_L =   %d\n", mca->nwtr_l);
	printk(BIOS_SPEW, "\tFAW =     %d\n", mca->nfaw);
	printk(BIOS_SPEW, "\tRCD =     %d\n", mca->nrcd);
	printk(BIOS_SPEW, "\tRP =      %d\n", mca->nrp);
	printk(BIOS_SPEW, "\tRAS =     %d\n", mca->nras);
	printk(BIOS_SPEW, "\tWR =      %d\n", mca->nwr);
	printk(BIOS_SPEW, "\tRRD_S =   %d\n", mca->nrrd_s);
	printk(BIOS_SPEW, "\tRRD_L =   %d\n", mca->nrrd_l);
	printk(BIOS_SPEW, "\tRFC =     %d\n", mca->nrfc);
	printk(BIOS_SPEW, "\tRFC_DLR = %d\n", mca->nrfc_dlr);

	int i;
	for (i = 0; i < 2; i++) {
		if (mca->dimm[i].present) {
			printk(BIOS_SPEW, "\tDIMM%d: %dRx%d ", i, mca->dimm[i].mranks,
			       (mca->dimm[i].width + 1) * 4);

			if (mca->dimm[i].log_ranks != mca->dimm[i].mranks)
				printk(BIOS_SPEW, "%dH 3DS ", mca->dimm[i].log_ranks / mca->dimm[i].mranks);

			printk(BIOS_SPEW, "%dGB\n", mca->dimm[i].size_gb);
		}
		else
			printk(BIOS_SPEW, "\tDIMM%d: not installed\n", i);
	}
}

/* TODO: add checks for same ranks configuration for both DIMMs under one MCA */
static inline bool is_proper_dimm(spd_raw_data spd, int slot)
{
	struct dimm_attr_ddr4_st attr;
	if (spd == NULL)
		return false;

	if (spd_decode_ddr4(&attr, spd) != SPD_STATUS_OK) {
		printk(BIOS_ERR, "Malformed SPD for slot %d\n", slot);
		return false;
	}

	if (attr.dram_type != SPD_MEMORY_TYPE_DDR4_SDRAM ||
	    attr.dimm_type != SPD_DDR4_DIMM_TYPE_RDIMM ||
	    attr.ecc_extension == false) {
		printk(BIOS_ERR, "Bad DIMM type in slot %d\n", slot);
		return false;
	}

	return true;
}

static void mark_nonfunctional(uint8_t chip, int mcs, int mca)
{
	mem_data[chip].mcs[mcs].mca[mca].functional = false;

	/* Propagate upwards */
	if (mem_data[chip].mcs[mcs].mca[mca ^ 1].functional == false) {
		mem_data[chip].mcs[mcs].functional = false;
		if (mem_data[chip].mcs[mcs ^ 1].functional == false)
			die("No functional MCS left");
	}
}

static uint64_t find_min_mtb_ftb(uint8_t chip, rdimm_data_t *dimm, int mtb_idx, int ftb_idx)
{
	uint64_t val0 = 0, val1 = 0;

	if (dimm[0].present)
		val0 = mtb_ftb_to_nck(chip, dimm[0].spd[mtb_idx], (int8_t)dimm[0].spd[ftb_idx]);
	if (dimm[1].present)
		val1 = mtb_ftb_to_nck(chip, dimm[1].spd[mtb_idx], (int8_t)dimm[1].spd[ftb_idx]);

	return (val0 < val1) ? val1 : val0;
}

static uint64_t find_min_multi_mtb(uint8_t chip, rdimm_data_t *dimm, int mtb_l, int mtb_h,
				   uint8_t mask, int shift)
{
	uint64_t val0 = 0, val1 = 0;

	if (dimm[0].present)
		val0 = dimm[0].spd[mtb_l] | ((dimm[0].spd[mtb_h] & mask) << shift);
	if (dimm[1].present)
		val1 = dimm[1].spd[mtb_l] | ((dimm[1].spd[mtb_h] & mask) << shift);

	return (val0 < val1) ? mtb_ftb_to_nck(chip, val1, 0) : mtb_ftb_to_nck(chip, val0, 0);
}

/* https://review.coreboot.org/c/coreboot/+/52061 */
/* DIMM SPD addresses */
#define DIMM0                            0x50
#define DIMM1                            0x51
#define DIMM2                            0x52
#define DIMM3                            0x53
#define DIMM4                            0x54
#define DIMM5                            0x55
#define DIMM6                            0x56
#define DIMM7                            0x57

/* This is most of step 7 condensed into one function */
static void prepare_cpu_dimm_data(uint8_t chip)
{
	int i, mcs, mca;
	int tckmin = 0x06;		// Platform limit
	unsigned int spd_bus = I2C_BUSES_PER_CPU * chip + SPD_I2C_BUS;

	/*
	 * DIMMs 4-7 are under a different port. This is not the same as bus, but we
	 * need to pass that information to I2C function. As there is no easier way,
	 * use MSB of address and mask it out at the receiving side. This will print
	 * wrong addresses in dump_spd_info(), but that is small price to pay.
	 */
	struct spd_block blk = {
		.addr_map = { DIMM0, DIMM1, DIMM2, DIMM3,
		              DIMM4 | 0x80, DIMM5 | 0x80, DIMM6 | 0x80, DIMM7 | 0x80},
	};

	get_spd_i2c(spd_bus, &blk);
	dump_spd_info(&blk);

	/*
	 * We need to find the highest common (for all DIMMs and the platform)
	 * supported frequency, meaning we need to compare minimum clock cycle times
	 * and choose the highest value. For the range supported by the platform we
	 * can check MTB only.
	 *
	 * TODO: check if we can have different frequencies across MCSs.
	 */
	for (i = 0; i < CONFIG_DIMM_MAX; i++) {
		if (is_proper_dimm(blk.spd_array[i], i)) {
			mcs = i / DIMMS_PER_MCS;
			mca = (i % DIMMS_PER_MCS) / MCA_PER_MCS;
			int dimm_idx = i % 2;	// (i % DIMMS_PER_MCS) % MCA_PER_MCS


			/* Maximum for 2 DIMMs on one port (channel, MCA) is 2400 MT/s */
			if (tckmin < 0x07 && mem_data[chip].mcs[mcs].mca[mca].functional)
				tckmin = 0x07;

			mem_data[chip].mcs[mcs].functional = true;
			mem_data[chip].mcs[mcs].mca[mca].functional = true;

			rdimm_data_t *dimm = &mem_data[chip].mcs[mcs].mca[mca].dimm[dimm_idx];

			dimm->present = true;
			dimm->spd = blk.spd_array[i];
			/* RCD address is the same as SPD, with one additional bit set */
			dimm->rcd_i2c_addr = blk.addr_map[i] | 0x08;
			/*
			 * SPD fields in spd.h are not compatible with DDR4 and those in
			 * spd_bin.h are just a few of all required.
			 *
			 * TODO: add fields that are lacking to either of those files or
			 * add a file specific to DDR4 SPD.
			 */
			dimm->width = blk.spd_array[i][12] & 7;
			dimm->mranks = ((blk.spd_array[i][12] >> 3) & 0x7) + 1;
			dimm->log_ranks = dimm->mranks * (((blk.spd_array[i][6] >> 4) & 0x7) + 1);
			dimm->density = blk.spd_array[i][4] & 0xF;
			dimm->size_gb = (1 << (dimm->density - 2)) * (2 - dimm->width) *
			                dimm->log_ranks;

			if ((blk.spd_array[i][5] & 0x38) == 0x30)
				die("DIMMs with 18 row address bits are not supported\n");

			if (blk.spd_array[i][18] > tckmin)
				tckmin = blk.spd_array[i][18];
		}
	}

	switch (tckmin) {
		/* For CWL assume 1tCK write preamble */
		case 0x06:
			mem_data[chip].speed = 2666;
			mem_data[chip].cwl = 14;
			break;
		case 0x07:
			mem_data[chip].speed = 2400;
			mem_data[chip].cwl = 12;
			break;
		case 0x08:
			mem_data[chip].speed = 2133;
			mem_data[chip].cwl = 11;
			break;
		case 0x09:
			mem_data[chip].speed = 1866;
			mem_data[chip].cwl = 10;
			break;
		default:
			die("Unsupported tCKmin: %d ps (+/- 125)\n", tckmin * 125);
	}

	/* Now that we know our speed, we can calculate the rest of the data */
	mem_data[chip].nrefi = ns_to_nck(chip, 7800);
	mem_data[chip].nrtp = ps_to_nck(chip, 7500);
	printk(BIOS_SPEW, "Common memory parameters:\n"
	                  "\tspeed =\t%d MT/s\n"
	                  "\tREFI =\t%d clock cycles\n"
	                  "\tCWL =\t%d clock cycles\n"
	                  "\tRTP =\t%d clock cycles\n",
	                  mem_data[chip].speed, mem_data[chip].nrefi,
	                  mem_data[chip].cwl, mem_data[chip].nrtp);

	for (mcs = 0; mcs < MCS_PER_PROC; mcs++) {
		if (!mem_data[chip].mcs[mcs].functional) continue;
		for (mca = 0; mca < MCA_PER_MCS; mca++) {
			if (!mem_data[chip].mcs[mcs].mca[mca].functional) continue;

			rdimm_data_t *dimm = mem_data[chip].mcs[mcs].mca[mca].dimm;
			uint32_t val0, val1, common;
			int min;	/* Minimum compatible with both DIMMs is the bigger value */

			/* CAS Latency */
			val0 = dimm[0].present ? le32_to_cpu(*(uint32_t *)&dimm[0].spd[20]) : -1;
			val1 = dimm[1].present ? le32_to_cpu(*(uint32_t *)&dimm[1].spd[20]) : -1;
			/* Assuming both DIMMs are in low CL range, true for all DDR4 speed bins */
			common = val0 & val1;

			/* tAAmin - minimum CAS latency time */
			min = find_min_mtb_ftb(chip, dimm, 24, 123);
			while (min <= 36 && ((common >> (min - 7)) & 1) == 0)
				min++;

			if (min > 36) {
				/* Maybe just die() instead? */
				printk(BIOS_WARNING, "Cannot find CL supported by all DIMMs under MCS%d, MCA%d."
				       " Marking as nonfunctional.\n", mcs, mca);
				mark_nonfunctional(chip, mcs, mca);
				continue;
			}

			mem_data[chip].mcs[mcs].mca[mca].cl = min;

			/*
			 * There are also minimal values in Table 170 of JEDEC Standard No. 79-4C which
			 * probably should also be honored. Some of them (e.g. RRD) depend on the page
			 * size, which depends on DRAM width. On tested DIMM they are just right - it is
			 * either minimal legal value or rounded up to whole clock cycle. Can we rely on
			 * vendors to put sane values in SPD or do we have to check them for validity?
			 */

			/* Minimum CAS to CAS Delay Time, Same Bank Group */
			mem_data[chip].mcs[mcs].mca[mca].nccd_l = find_min_mtb_ftb(chip, dimm, 40, 117);

			/* Minimum Write to Read Time, Different Bank Group */
			mem_data[chip].mcs[mcs].mca[mca].nwtr_s = find_min_multi_mtb(chip, dimm, 44, 43, 0x0F, 8);

			/* Minimum Write to Read Time, Same Bank Group */
			mem_data[chip].mcs[mcs].mca[mca].nwtr_l = find_min_multi_mtb(chip, dimm, 45, 43, 0xF0, 4);

			/* Minimum Four Activate Window Delay Time */
			mem_data[chip].mcs[mcs].mca[mca].nfaw = find_min_multi_mtb(chip, dimm, 37, 36, 0x0F, 8);

			/* Minimum RAS to CAS Delay Time */
			mem_data[chip].mcs[mcs].mca[mca].nrcd = find_min_mtb_ftb(chip, dimm, 25, 122);

			/* Minimum Row Precharge Delay Time */
			mem_data[chip].mcs[mcs].mca[mca].nrp = find_min_mtb_ftb(chip, dimm, 26, 121);

			/* Minimum Active to Precharge Delay Time */
			mem_data[chip].mcs[mcs].mca[mca].nras = find_min_multi_mtb(chip, dimm, 28, 27, 0x0F, 8);

			/* Minimum Write Recovery Time */
			mem_data[chip].mcs[mcs].mca[mca].nwr = find_min_multi_mtb(chip, dimm, 42, 41, 0x0F, 8);

			/* Minimum Activate to Activate Delay Time, Different Bank Group */
			mem_data[chip].mcs[mcs].mca[mca].nrrd_s = find_min_mtb_ftb(chip, dimm, 38, 119);

			/* Minimum Activate to Activate Delay Time, Same Bank Group */
			mem_data[chip].mcs[mcs].mca[mca].nrrd_l = find_min_mtb_ftb(chip, dimm, 39, 118);

			/* Minimum Refresh Recovery Delay Time */
			/* Assuming no fine refresh mode. */
			mem_data[chip].mcs[mcs].mca[mca].nrfc = find_min_multi_mtb(chip, dimm, 30, 31, 0xFF, 8);

			/* Minimum Refresh Recovery Delay Time for Different Logical Rank (3DS only) */
			/*
			 * This one is set per MCA, but it depends on DRAM density, which can be
			 * mixed between DIMMs under the same channel. We need to choose the bigger
			 * minimum time, which corresponds to higher density.
			 *
			 * Assuming no fine refresh mode.
			 */
			val0 = dimm[0].present ? dimm[0].spd[4] & 0xF : 0;
			val1 = dimm[1].present ? dimm[1].spd[4] & 0xF : 0;
			min = (val0 < val1) ? val1 : val0;

			switch (min) {
				case 0x4:
					mem_data[chip].mcs[mcs].mca[mca].nrfc_dlr = ns_to_nck(chip, 90);
					break;
				case 0x5:
					mem_data[chip].mcs[mcs].mca[mca].nrfc_dlr = ns_to_nck(chip, 120);
					break;
				case 0x6:
					mem_data[chip].mcs[mcs].mca[mca].nrfc_dlr = ns_to_nck(chip, 185);
					break;
				default:
					die("Unsupported DRAM density\n");
			}

			printk(BIOS_SPEW, "MCS%d, MCA%d times (in clock cycles):\n", mcs, mca);
			dump_mca_data(&mem_data[chip].mcs[mcs].mca[mca]);
		}
	}
}

/* This is most of step 7 condensed into one function */
static void prepare_dimm_data(uint8_t chips)
{
	bool have_dimms;

	prepare_cpu_dimm_data(/*chip=*/0);
	if (chips & 0x02)
		prepare_cpu_dimm_data(/*chip=*/1);

	/*
	 * There is one (?) MCBIST per CPU. Fail if there are no supported DIMMs
	 * connected, otherwise assume it is functional. There is no reason to redo
	 * this test in the rest of isteps.
	 */
	have_dimms = false;
	have_dimms |= mem_data[0].mcs[0].functional;
	have_dimms |= mem_data[0].mcs[1].functional;
	have_dimms |= mem_data[1].mcs[0].functional;
	have_dimms |= mem_data[1].mcs[1].functional;
	if (!have_dimms)
		die("No DIMMs detected, aborting\n");
}

extern uint8_t sys_reset_thread_int[];
extern uint8_t sys_reset_thread_int_end[];

static int lock = 0;
volatile int value;

static void a_barrier(void)
{
	__asm__ __volatile__ ("sync" : : : "memory");
}

static inline int a_ll(volatile int *p)
{
	int v;
	__asm__ __volatile__ ("lwarx %0, 0, %2" : "=r"(v) : "m"(*p), "r"(p));
	return v;
}

static inline int a_sc(volatile int *p, int v)
{
	int r;
	__asm__ __volatile__ (
		"stwcx. %2, 0, %3 ; mfcr %0"
		: "=r"(r), "=m"(*p) : "r"(v), "r"(p) : "memory", "cc");
	return r & 0x20000000; /* "bit 2" of "cr0" (backwards bit order) */
}

static inline void a_post_llsc(void)
{
	__asm__ __volatile__ ("isync" : : : "memory");
}

static inline int a_cas(volatile int *p, int v)
{
	int old;
	a_barrier();
	do
		old = a_ll(p);
	while (old == 0 && !a_sc(p, v));
	a_post_llsc();
	return old;
}

static inline void a_store(volatile int *p, int v)
{
	a_barrier();
	*p = v;
	a_barrier();
}

static int spin_lock(int *s)
{
	while (*(volatile int *)s || a_cas(s, 1) != 0)
		a_barrier();
	return 0;
}

static void spin_unlock(int *s)
{
	a_store(s, 0);
}

void second_thread(void);

void second_thread(void)
{
	// This should checkstop
	*(int *)0x800623FC000F000F += 1;
	write_rscom(1, 0x20010A9D, 0);
	/* printk(BIOS_EMERG, "Hello from second thread\n"); */
	value = 1234;
	spin_unlock(&lock);
	for(;;);
}

static inline void sync_icache(void)
{
	asm volatile("sync; icbi 0,%0; sync; isync" : : "r" (0) : "memory");
}

static void start_second_thread(void)
{
#define CODE_SIZE(x) ((x ## _end) - (x))

	printk(BIOS_EMERG, "%d\n", __LINE__);
	memcpy((void *)0x100, sys_reset_thread_int, CODE_SIZE(sys_reset_thread_int));
	printk(BIOS_EMERG, "%d\n", __LINE__);
	sync_icache();

	printk(BIOS_EMERG, "%d\n", __LINE__);
	spin_lock(&lock);

	// No Precondition for Sreset; power management is handled by platform
	// Clear blocking interrupts

        // SW375288: Reads to C_RAS_MODEREG causes SPR corruption.
	// For now, the code will assume no other bits are set and only
	// set/clear mr_fence_interrupts
	/* printk(BIOS_EMERG, "0x20010A9D = 0x%llx\n\n\n\n\n\n", read_rscom(0, 0x20010A9D)); */
	write_rscom_for_chiplet(0, EC00_CHIPLET_ID + 1, 0x20010A9D, 0);
	printk(BIOS_EMERG, "%d\n\n\n\n\n\n", __LINE__);

	// Setup & Initiate SReset Command
	write_rscom_for_chiplet(0, EC00_CHIPLET_ID + 1, 0x20010A9C, 0x0080000000000000 >> 4);
	printk(BIOS_EMERG, "%d\n\n\n\n\n\n", __LINE__);

	// Was there a race?

	spin_lock(&lock);
	printk(BIOS_EMERG, "%d\n\n\n\n\n\n", __LINE__);
	printk(BIOS_EMERG, "%d: value = %d\n\n\n\n\n\n", __LINE__, *(volatile int *)&value);

	printk(BIOS_EMERG, "Waiting for second thread:\n");
	for(;;);

#undef CODE_SIZE
}

void main(void)
{
	uint8_t chips;

	struct pci_info pci_info[MAX_CHIPS] = { 0 };

	timestamp_add_now(TS_START_ROMSTAGE);

	console_init();

	init_timer();

	if (ipmi_premem_init(CONFIG_BMC_BT_BASE, 0) != CB_SUCCESS)
		die("Failed to initialize IPMI\n");

	/*
	 * Two minutes to load.
	 * Not handling return code, because the function itself prints log messages
	 * and its failure is not a critical error.
	 */
	(void)ipmi_init_and_start_bmc_wdt(CONFIG_BMC_BT_BASE, 120, TIMEOUT_HARD_RESET);

	printk(BIOS_EMERG, "Initializing FSI...\n");
	fsi_init();
	chips = fsi_get_present_chips();
	printk(BIOS_EMERG, "Initialized FSI (chips mask: 0x%02X)\n", chips);

	start_second_thread();

	istep_8_1(chips);
	istep_8_2(chips);
	istep_8_3(chips);
	istep_8_4(chips);
	istep_8_9(chips);
	istep_8_10(chips);
	istep_8_11(chips);

	istep_9_2(chips);
	istep_9_4(chips);
	istep_9_6(chips);
	istep_9_7(chips);

	istep_10_1(chips);
	istep_10_6(chips);
	istep_10_10(chips, pci_info);
	istep_10_12(chips);
	istep_10_13(chips);

	timestamp_add_now(TS_BEFORE_INITRAM);

	vpd_pnor_main();
	prepare_dimm_data(chips);

	report_istep(13,1);	// no-op
	istep_13_2(chips);
	istep_13_3(chips);
	istep_13_4(chips);
	report_istep(13,5);	// no-op
	istep_13_6(chips);
	report_istep(13,7);	// no-op
	istep_13_8(chips);
	istep_13_9(chips);
	istep_13_10(chips);
	istep_13_11(chips);
	report_istep(13,12);	// optional, not yet implemented
	istep_13_13(chips);

	istep_14_1(chips);
	istep_14_2(chips);
	istep_14_3(chips, pci_info);
	report_istep(14,4);	// no-op
	istep_14_5(chips);

	timestamp_add_now(TS_AFTER_INITRAM);

	/* Test if SCOM still works. Maybe should check also indirect access? */
	printk(BIOS_DEBUG, "0xF000F = %llx\n", read_scom(0xF000F));

	/*
	 * Halt to give a chance to inspect FIRs, otherwise checkstops from
	 * ramstage may cover up the failure in romstage.
	 */
	if (read_scom(0xF000F) == 0xFFFFFFFFFFFFFFFF)
		die("SCOM stopped working, check FIRs, halting now\n");

	cbmem_initialize_empty();
	run_ramstage();
}
