/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/cpu.h>
#include <device/device.h>
#include <smbios.h>
#include <soc/ramstage.h>
#include <string.h>

const char *smbios_mainboard_product_name(void)
{
	u32 tmp[13];
	const char *str = "Unknown Processor Name";

	if (cpu_have_cpuid()) {
		int i;
		struct cpuid_result res = cpuid(0x80000000);
		if (res.eax >= 0x80000004) {
			int j = 0;
			for (i = 0; i < 3; i++) {
				res = cpuid(0x80000002 + i);
				tmp[j++] = res.eax;
				tmp[j++] = res.ebx;
				tmp[j++] = res.ecx;
				tmp[j++] = res.edx;
			}
			tmp[12] = 0;
			str = (const char *)tmp;
		}
	}

	if (strstr(str, "i5-1235U") != NULL)
		return "VP6650";
	else if (strstr(str, "i7-1255U") != NULL)
		return "VP6670";
	else
		return CONFIG_MAINBOARD_SMBIOS_PRODUCT_NAME;
}


void mainboard_silicon_init_params(FSP_S_CONFIG *params)
{

}

static void mainboard_final(void *chip_info)
{
}

struct chip_operations mainboard_ops = {
	.final = mainboard_final,
};
