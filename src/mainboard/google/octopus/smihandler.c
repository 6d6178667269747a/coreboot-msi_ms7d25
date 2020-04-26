/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <arch/acpi.h>
#include <baseboard/variants.h>
#include <cpu/x86/smm.h>
#include <ec/google/chromeec/ec.h>
#include <ec/google/chromeec/smm.h>
#include <elog.h>
#include <intelblocks/smihandler.h>
#include <soc/pm.h>
#include <soc/gpio.h>
#include <variant/ec.h>
#include <variant/gpio.h>

void mainboard_smi_gpi_handler(const struct gpi_status *sts)
{
	if (gpi_status_get(sts, EC_SMI_GPI))
		chromeec_smi_process_events();
}

void mainboard_smi_sleep(u8 slp_typ)
{
	const struct pad_config *pads;
	size_t num;

	pads = variant_sleep_gpio_table(&num, slp_typ);
	gpio_configure_pads(pads, num);

	variant_smi_sleep(slp_typ);

	chromeec_smi_sleep(slp_typ, MAINBOARD_EC_S3_WAKE_EVENTS,
				MAINBOARD_EC_S5_WAKE_EVENTS);
}

int mainboard_smi_apmc(u8 apmc)
{
	chromeec_smi_apmc(apmc, MAINBOARD_EC_SCI_EVENTS,
				MAINBOARD_EC_SMI_EVENTS);
	return 0;
}

void mainboard_smi_espi_handler(void)
{
	chromeec_smi_process_events();
}

void elog_gsmi_cb_mainboard_log_wake_source(void)
{
	google_chromeec_log_events(MAINBOARD_EC_LOG_EVENTS |
					MAINBOARD_EC_S0IX_WAKE_EVENTS);
}

void __weak variant_smi_sleep(u8 slp_typ)
{
	/* Leave for the variant to implement if necessary. */
}
