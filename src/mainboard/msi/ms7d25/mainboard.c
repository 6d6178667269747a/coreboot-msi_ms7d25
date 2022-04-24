/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include <device/device.h>
#include <soc/ramstage.h>
#include <string.h>

#include "gpio.h"

void mainboard_fill_fadt(acpi_fadt_t *fadt)
{
	fadt->preferred_pm_profile = PM_DESKTOP;
	fadt->iapc_boot_arch |= ACPI_FADT_LEGACY_DEVICES | ACPI_FADT_8042;
}

static void mainboard_init(void *chip_info)
{

}

static void mainboard_enable(struct device *dev)
{

}

void mainboard_silicon_init_params(FSP_S_CONFIG *params)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	memset(params->PcieRpEnableCpm, 0, sizeof(params->PcieRpEnableCpm));
	memset(params->CpuPcieRpEnableCpm, 0, sizeof(params->CpuPcieRpEnableCpm));
	memset(params->CpuPcieClockGating, 0, sizeof(params->CpuPcieClockGating));
	memset(params->CpuPciePowerGating, 0, sizeof(params->CpuPciePowerGating));
	memset(params->PcieRpSlotImplemented, 0, sizeof(params->PcieRpSlotImplemented));
	memset(params->CpuPcieRpSlotImplemented, 0, sizeof(params->CpuPcieRpSlotImplemented));

	params->CnviWifiCore = 1;
	params->CpuPcieFiaProgramming = 1;

	params->PcieRpFunctionSwap = 0;
	params->CpuPcieRpFunctionSwap = 0;

	params->CpuPcieRpSlotImplemented[0] = 1; // M2_1
	params->CpuPcieRpSlotImplemented[1] = 1; // PCI_E1
	params->PcieRpSlotImplemented[0]    = 1; // PCI_E2
	params->PcieRpSlotImplemented[1]    = 1; // PCI_E4
	params->PcieRpSlotImplemented[4]    = 1; // PCI_E3
	params->PcieRpSlotImplemented[8]    = 1; // M2_3
	params->PcieRpSlotImplemented[20]   = 1; // M2_4
	params->PcieRpSlotImplemented[24]   = 1; // M2_2

	params->CpuPcieRpPmSci[0] = 1; // M2_1
	params->CpuPcieRpPmSci[1] = 1; // PCI_E1
	params->PcieRpPmSci[0]    = 1; // PCI_E2
	params->PcieRpPmSci[1]    = 1; // PCI_E4
	params->PcieRpPmSci[2]    = 1; // Ethernet
	params->PcieRpPmSci[4]    = 1; // PCI_E3
	params->PcieRpPmSci[8]    = 1; // M2_3
	params->PcieRpPmSci[20]   = 1; // M2_4
	params->PcieRpPmSci[24]   = 1; // M2_2

	params->CpuPcieRpTransmitterHalfSwing[0] = 1; // M2_1
	params->CpuPcieRpTransmitterHalfSwing[1] = 1; // PCI_E1
	params->PcieRpTransmitterHalfSwing[0]    = 1; // PCI_E2
	params->PcieRpTransmitterHalfSwing[1]    = 1; // PCI_E4
	params->PcieRpTransmitterHalfSwing[2]    = 1; // Ethernet
	params->PcieRpTransmitterHalfSwing[4]    = 1; // PCI_E3
	params->PcieRpTransmitterHalfSwing[8]    = 1; // M2_3
	params->PcieRpTransmitterHalfSwing[20]   = 1; // M2_4
	params->PcieRpTransmitterHalfSwing[24]   = 1; // M2_2

	params->PcieRpEnableCpm[0]    = 1; // PCI_E2
	params->PcieRpEnableCpm[1]    = 1; // PCI_E4
	params->PcieRpEnableCpm[4]    = 1; // PCI_E3
	params->PcieRpEnableCpm[8]    = 1; // M2_3
	params->PcieRpEnableCpm[20]   = 1; // M2_4
	params->PcieRpEnableCpm[24]   = 1; // M2_2

	params->PcieRpAcsEnabled[0]    = 1; // PCI_E2
	params->PcieRpAcsEnabled[1]    = 1; // PCI_E4
	params->PcieRpAcsEnabled[2]    = 1; // Ethernet
	params->PcieRpAcsEnabled[4]    = 1; // PCI_E3
	params->PcieRpAcsEnabled[8]    = 1; // M2_3
	params->PcieRpAcsEnabled[20]   = 1; // M2_4
	params->PcieRpAcsEnabled[24]   = 1; // M2_2

	//TODO: Enable CPM, PG and CG when it start to work
	params->CpuPcieRpEnableCpm[0] = 0; // M2_1
	params->CpuPcieClockGating[0] = 0;
	params->CpuPciePowerGating[0] = 0;
	params->CpuPcieRpMultiVcEnabled[0] = 1;
	params->CpuPcieRpPeerToPeerMode[0] = 1;
	params->CpuPcieRpMaxPayload[0] = 1; // 256B
	params->CpuPcieRpAcsEnabled[0] = 1;

	params->CpuPcieRpEnableCpm[1] = 0; // PCI_E1
	params->CpuPcieClockGating[1] = 0;
	params->CpuPciePowerGating[1] = 0;
	params->CpuPcieRpDetectTimeoutMs[1] = 1000;
	params->CpuPcieRpPeerToPeerMode[1] = 1;
	params->CpuPcieRpMaxPayload[1] = 1; // 256B
	params->CpuPcieRpAcsEnabled[1] = 1;

	params->SataPortsSolidStateDrive[6] = 1; // M2_3
	params->SataPortsSolidStateDrive[7] = 1; // M2_4
	params->SataLedEnable = 1;
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
