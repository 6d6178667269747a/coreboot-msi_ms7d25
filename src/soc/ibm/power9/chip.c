/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <cpu/power/istep_13.h>
#include "istep_13_scom.h"

#define SIZE_MASK	PPC_BITMASK(13,23)
#define SIZE_SHIFT	(63 - 23)
#define BASE_MASK	PPC_BITMASK(24,47)
#define BASE_SHIFT	(63 - 47)

/* Values in registers are in 4GB units, ram_resource_kb() expects kilobytes. */
#define CONVERT_4GB_TO_KB(x)	((x) << 22)

static inline unsigned long base_k(uint64_t reg)
{
	return CONVERT_4GB_TO_KB((reg & BASE_MASK) >> BASE_SHIFT);
}

static inline unsigned long size_k(uint64_t reg)
{
	return CONVERT_4GB_TO_KB(((reg & SIZE_MASK) >> SIZE_SHIFT) + 1);
}

static void enable_soc_dev(struct device *dev)
{
	int mcs_i, idx = 0;

	for (mcs_i = 0; mcs_i < MCS_PER_PROC; mcs_i++) {
		uint64_t reg;
		chiplet_id_t nest = mcs_to_nest[mcs_ids[mcs_i]];

		/* These registers are undocumented, see istep 14.5. */
		/* MCS_MCFGP */
		reg = read_scom_for_chiplet(nest, 0x0501080A);
		if (reg & PPC_BIT(0))
			ram_resource_kb(dev, idx++, base_k(reg), size_k(reg));

		/* MCS_MCFGPM */
		reg = read_scom_for_chiplet(nest, 0x0501080C);
		if (reg & PPC_BIT(0))
			ram_resource_kb(dev, idx++, base_k(reg), size_k(reg));
	}
}

struct chip_operations soc_ibm_power9_ops = {
	CHIP_NAME("POWER9")
	.enable_dev = enable_soc_dev,
};
