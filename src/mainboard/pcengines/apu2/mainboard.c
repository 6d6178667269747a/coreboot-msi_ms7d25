/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/acpi.h>
#include <arch/io.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_def.h>
#include <southbridge/amd/pi/hudson/hudson.h>
#include <southbridge/amd/pi/hudson/pci_devs.h>
#include <southbridge/amd/pi/hudson/amd_pci_int_defs.h>
#include <northbridge/amd/pi/00730F01/pci_devs.h>
#include <southbridge/amd/common/amd_pci_util.h>
#include <superio/nuvoton/nct5104d/nct5104d.h>
#include <smbios.h>
#include <string.h>
#include <cpu/x86/msr.h>
#include <cpu/amd/mtrr.h>
#include <spd_bin.h>
#include <spi_flash.h>
#include <spi-generic.h>
#include "gpio_ftns.h"
#include "bios_knobs.h"
#include "s1_button.h"

#define PM_RTC_CONTROL	    0x56
#define PM_RTC_SHADOW	    0x5B
#define PM_S_STATE_CONTROL  0xBA

#define SEC_REG_SERIAL_ADDR 0x1000
#define MAX_SERIAL_LEN	    10


/***********************************************************
 * These arrays set up the FCH PCI_INTR registers 0xC00/0xC01.
 * This table is responsible for physically routing the PIC and
 * IOAPIC IRQs to the different PCI devices on the system.  It
 * is read and written via registers 0xC00/0xC01 as an
 * Index/Data pair.  These values are chipset and mainboard
 * dependent and should be updated accordingly.
 *
 * These values are used by the PCI configuration space,
 * MP Tables.  TODO: Make ACPI use these values too.
 */
static const u8 mainboard_picr_data[FCH_INT_TABLE_SIZE] = {
	[0 ... FCH_INT_TABLE_SIZE-1] = 0x1F,
	/* INTA# - INTH# */
	[0x00] = 0x03,0x03,0x05,0x07,0x0B,0x0A,0x1F,0x1F,
	/* Misc-nil,0,1,2, INT from Serial irq */
	[0x08] = 0xFA,0xF1,0x00,0x00,0x1F,0x1F,0x1F,0x1F,
	/* SCI, SMBUS0, ASF, HDA, FC, RSVD, PerMon, SD */
	[0x10] = 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
	[0x18] = 0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* IMC INT0 - 5 */
	[0x20] = 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,
	[0x28] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* USB Devs 18/19/22 INTA-C */
	[0x30] = 0x05,0x1F,0x05,0x1F,0x04,0x1F,0x1F,0x1F,
	[0x38] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* SATA */
	[0x40] = 0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x48] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x50] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x58] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x60] = 0x00,0x00,0x1F
};

static const u8 mainboard_intr_data[FCH_INT_TABLE_SIZE] = {
	[0 ... FCH_INT_TABLE_SIZE-1] = 0x1F,
	/* INTA# - INTH# */
	[0x00] = 0x10,0x10,0x12,0x13,0x14,0x15,0x1F,0x1F,
	/* Misc-nil,0,1,2, INT from Serial irq */
	[0x08] = 0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,
	/* SCI, SMBUS0, ASF, HDA, FC, RSVD, PerMon, SD */
	[0x10] = 0x09,0x1F,0x1F,0x1F,0x1F,0x1f,0x1F,0x10,
	[0x18] = 0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* IMC INT0 - 5 */
	[0x20] = 0x05,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,
	[0x28] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* USB Devs 18/19/20/22 INTA-C */
	[0x30] = 0x12,0x1f,0x12,0x1F,0x12,0x1F,0x1F,0x00,
	[0x38] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* SATA */
	[0x40] = 0x1f,0x13,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x48] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x50] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x58] = 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	[0x60] = 0x00,0x00,0x1F
};

/*
 * This table defines the index into the picr/intr_data
 * tables for each device.  Any enabled device and slot
 * that uses hardware interrupts should have an entry
 * in this table to define its index into the FCH
 * PCI_INTR register 0xC00/0xC01.  This index will define
 * the interrupt that it should use.  Putting PIRQ_A into
 * the PIN A index for a device will tell that device to
 * use PIC IRQ 10 if it uses PIN A for its hardware INT.
 */
static const struct pirq_struct mainboard_pirq_data[] = {
	/* {PCI_devfn,	{PIN A, PIN B, PIN C, PIN D}}, */
	{GFX_DEVFN,	{PIRQ_A, PIRQ_NC, PIRQ_NC, PIRQ_NC}},			/* VGA:		01.0 */
	{ACTL_DEVFN,{PIRQ_NC, PIRQ_B, PIRQ_NC, PIRQ_NC}},			/* Audio:	01.1 */
	{NB_PCIE_PORT1_DEVFN,	{PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D}},	/* x4 PCIe:	02.1 */
	{NB_PCIE_PORT2_DEVFN,	{PIRQ_B, PIRQ_C, PIRQ_D, PIRQ_A}},	/* mPCIe:	02.2 */
	{NB_PCIE_PORT3_DEVFN,	{PIRQ_C, PIRQ_D, PIRQ_A, PIRQ_B}},	/* NIC:		02.3 */
	{XHCI_DEVFN,	{PIRQ_C, PIRQ_NC, PIRQ_NC, PIRQ_NC}},		/* XHCI:	10.0 */
	{SATA_DEVFN,	{PIRQ_SATA, PIRQ_NC, PIRQ_NC, PIRQ_NC}},	/* SATA:	11.0 */
	{OHCI1_DEVFN,	{PIRQ_OHCI1, PIRQ_NC, PIRQ_NC, PIRQ_NC}},	/* OHCI1:	12.0 */
	{EHCI1_DEVFN,	{PIRQ_NC, PIRQ_EHCI1, PIRQ_NC, PIRQ_NC}},	/* EHCI1:	12.2 */
	{OHCI2_DEVFN,	{PIRQ_OHCI2, PIRQ_NC, PIRQ_NC, PIRQ_NC}},	/* OHCI2:	13.0 */
	{EHCI2_DEVFN,	{PIRQ_NC, PIRQ_EHCI2, PIRQ_NC, PIRQ_NC}},	/* EHCI2:	13.2 */
	{SMBUS_DEVFN,	{PIRQ_SMBUS, PIRQ_NC, PIRQ_NC, PIRQ_NC}},	/* SMBUS:	14.0 */
	{HDA_DEVFN,		{PIRQ_HDA, PIRQ_NC, PIRQ_NC, PIRQ_NC}},		/* HDA:		14.2 */
	{SD_DEVFN,		{PIRQ_SD, PIRQ_NC, PIRQ_NC, PIRQ_NC}},		/* SD:		14.7 */
	{OHCI3_DEVFN,	{PIRQ_OHCI3, PIRQ_NC, PIRQ_NC, PIRQ_NC}},	/* OHCI3:	16.0 (same device as xHCI 10.0) */
	{EHCI3_DEVFN,	{PIRQ_NC, PIRQ_EHCI3, PIRQ_NC, PIRQ_NC}},	/* EHCI3:	16.2 (same device as xHCI 10.1) */
};

/* PIRQ Setup */
static void pirq_setup(void)
{
	pirq_data_ptr = mainboard_pirq_data;
	pirq_data_size = sizeof(mainboard_pirq_data) / sizeof(struct pirq_struct);
	intr_data_ptr = mainboard_intr_data;
	picr_data_ptr = mainboard_picr_data;
}

/* Wrapper to enable GPIO/UART devices under menuconfig. Revisit
 * once configuration file format for SPI flash storage is complete.
 */
#define SIO_PORT 0x2E

static void config_gpio_mux(void)
{
	struct device *uart, *gpio;

	if (check_uartc()) {
		printk(BIOS_INFO, "UARTC enabled\n");

		uart = dev_find_slot_pnp(SIO_PORT, NCT5104D_SP3);
		if (uart)
			uart->enabled = 1;

		gpio = dev_find_slot_pnp(SIO_PORT, NCT5104D_GPIO0);
		if (gpio)
			gpio->enabled = 0;
	} else {
		printk(BIOS_INFO, "UARTC disabled\n");

		uart = dev_find_slot_pnp(SIO_PORT, NCT5104D_SP3);
		if (uart)
			uart->enabled = 0;

		gpio = dev_find_slot_pnp(SIO_PORT, NCT5104D_GPIO0);
		if (gpio)
			gpio->enabled = 1;
	}

	if (check_uartd()) {
		printk(BIOS_INFO, "UARTD enabled\n");

		uart = dev_find_slot_pnp(SIO_PORT, NCT5104D_SP4);
		if (uart)
			uart->enabled = 1;

		gpio = dev_find_slot_pnp(SIO_PORT, NCT5104D_GPIO1);
		if (gpio)
			gpio->enabled = 0;
	} else {
		printk(BIOS_INFO, "UARTD disabled\n");

		uart = dev_find_slot_pnp(SIO_PORT, NCT5104D_SP4);
		if (uart)
			uart->enabled = 0;

		gpio = dev_find_slot_pnp(SIO_PORT, NCT5104D_GPIO1);
		if (gpio)
			gpio->enabled = 1;
	}
}

/**********************************************
 * enable the dedicated function in mainboard.
 **********************************************/

static void mainboard_enable(struct device *dev)
{
	bool scon = check_console();

	config_gpio_mux();

	setup_bsp_ramtop();
	u32 total_mem = bsp_topmem() / (1024 * 1024);
	if (bsp_topmem2() > 0)
		total_mem += (bsp_topmem2() / (1024 * 1024)) - 4 * 1024;

	if(scon) {
		printk(BIOS_ALERT, "%d MB", total_mem);
	}
	//
	// Read memory configuration from GPIO 49 and 50
	//
	u8 spd_index = get_spd_offset();

	u8 spd_buffer[CONFIG_DIMM_SPD_SIZE];
	if (read_ddr3_spd_from_cbfs(spd_buffer, spd_index) < 0) {
		/* Indicate no ECC */
		spd_buffer[3] = 3;
	}

	if (scon) {
		if (spd_buffer[3] == 8)
			printk(BIOS_ALERT, " ECC");

		printk(BIOS_ALERT, " DRAM\n\n");
	}
	//
	// Enable the RTC output
	//
	pm_write16(PM_RTC_CONTROL, pm_read16(PM_RTC_CONTROL) | (1 << 11));

	//
	// Enable power on from WAKE#
	//
	pm_write16(PM_S_STATE_CONTROL, pm_read16(PM_S_STATE_CONTROL) | (1 << 14));

	//
	// Enable power on after power fail
	//
	pm_write8 ( PM_RTC_SHADOW, pm_read8( PM_RTC_SHADOW ) | (1 << 0));

	/* Initialize the PIRQ data structures for consumption */
	pirq_setup();
}

static void mainboard_final(void *chip_info)
{
	/* ECC was not working because all memory was marked
	 * as excluded from ECC checking and error reporting.
	 * Normally one contiguous range is excluded to cover
	 * framebuffer region in systems with internal GPUs.
	 * AGESA set bit 0, EccExclEn, in register D18F5x240 as 1.
	 * Range was incorrectly enabled to cover all memory
	 * for cases without UMA (no integrated graphics).
	 *
	 * In order to clear EccExclEn DRAM scrubber needs to be
	 * disabled temporarily by setting D18F3x88[DisDramScrub]
	 */
	u32 val;
	device_t D18F3 = dev_find_device(0x1022, 0x1583, NULL);
	device_t D18F5 = dev_find_device(0x1022, 0x1585, NULL);

	/* Disable DRAM ECC scrubbing */
	val = pci_read_config32(D18F3, 0x88);
	val |= (1 << 27);
	pci_write_config32(D18F3, 0x88, val);

	/* Clear reserved bits in register D18F3xB8
	 *
	 * D18F3xB8 NB Array Address has reserved bits [27:10]
	 * Multiple experiments showed that ECC injection
	 * doesn't work when these bits are set.
	 */
	val = pci_read_config32(D18F3, 0xB8);
	val &= 0xF000003F;
	pci_write_config32(D18F3, 0xB8, val);

	/* Disable ECC exclusion range */
	val = pci_read_config32(D18F5, 0x240);
	val &= ~1;
	pci_write_config32(D18F5, 0x240, val);

	/*  Re-enable DRAM ECC scrubbing */
	val = pci_read_config32(D18F3, 0x88);
	val &= ~(1 << 27);
	pci_write_config32(D18F3, 0x88, val);

	//
	// Turn off LED 2 and LED 3
	//
	write_gpio(GPIO_58, 1);
	write_gpio(GPIO_59, 1);

	if (!check_console()) {
		//
		// The console is disabled, check if S1 is pressed and enable if so
		//
#if IS_ENABLED(CONFIG_BOARD_PCENGINES_APU5)
 		if (!read_gpio(GPIO_22)) {
#else
		if (!read_gpio(GPIO_32)) {
#endif
			printk(BIOS_INFO, "S1 PRESSED\n");
			enable_console();
		}
	}
}

/*
 * We will stuff a modified version of the first NICs (BDF 1:0.0) MAC address
 * into the smbios serial number location.
 */
static int read_serial_from_nic(char *serial, size_t len)
{
	device_t nic_dev;
	uintptr_t bar10;
	u32 mac_addr = 0;
	int i;

	nic_dev = dev_find_slot(1, PCI_DEVFN(0, 0));
	if (!serial || !nic_dev)
		return -1;

	/* Read in the last 3 bytes of NIC's MAC address. */
	bar10 = pci_read_config32(nic_dev, 0x10);
	bar10 &= 0xFFFE0000;
	bar10 += 0x5400;
	for (i = 3; i < 6; i++) {
		mac_addr <<= 8;
		mac_addr |= read8((u8 *)bar10 + i);
	}
	mac_addr &= 0x00FFFFFF;
	mac_addr /= 4;
	mac_addr -= 64;

	snprintf(serial, len, "%d", mac_addr);
	return 0;
}

static int read_serial_from_flash(char *serial, size_t len)
{
	const struct spi_flash *flash = NULL;
	int ret;

	flash = boot_device_spi_flash();
	if (flash == NULL) {
		printk(BIOS_WARNING, "Can't get boot flash device\n");
		return -1;
	}

	ret = spi_flash_read_sec(flash, SEC_REG_SERIAL_ADDR, len, serial);
	if (ret) {
		printk(BIOS_WARNING, "Can't read security registers\n");
		return ret;
	}

	return ret;
}

const char *smbios_mainboard_serial_number(void)
{
	static char serial[MAX_SERIAL_LEN + 1] = { 0 }; /* extra slot for \0 */
	int ret;

	ret = read_serial_from_flash(serial, sizeof(serial)-1);

	if (ret || ((serial[0] & 0xff) == 0x00) || ((serial[0] & 0xff) == 0xff)) {
		ret = read_serial_from_nic(serial, sizeof(serial)-1);
		if (ret) {
			serial[0] = '0';
			serial[1] = '\0';
		}
	}

	return serial;
}

/*
 * We will stuff the memory size into the smbios sku location.
 */
const char *smbios_mainboard_sku(void)
{
	static char sku[5];
	if (sku[0] != 0)
		return sku;

	if (!get_spd_offset())
		snprintf(sku, sizeof(sku), "2 GB");
	else
		snprintf(sku, sizeof(sku), "4 GB");
	return sku;
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
	.final = mainboard_final,
};
