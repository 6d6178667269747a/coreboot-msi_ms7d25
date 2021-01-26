/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <acpi/acpi_gnvs.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <intelblocks/lpc_lib.h>
#include <soc/pm.h>

/* SoC overrides */

/* Common weak definition, needs to be implemented in each soc LPC driver. */
__weak void lpc_soc_init(struct device *dev)
{
	/* no-op */
}

/* Fill up LPC IO resource structure inside SoC directory */
__weak void pch_lpc_soc_fill_io_resources(struct device *dev)
{
	/* no-op */
}

void pch_lpc_add_new_resource(struct device *dev, uint8_t offset,
	uintptr_t base, size_t size, unsigned long flags)
{
	struct resource *res;
	res = new_resource(dev, offset);
	res->base = base;
	res->size = size;
	res->flags = flags;
}

static void pch_lpc_add_io_resources(struct device *dev)
{
	/* Add the default claimed legacy IO range for the LPC device. */
	pch_lpc_add_new_resource(dev, 0, 0, 0x1000, IORESOURCE_IO |
			IORESOURCE_ASSIGNED | IORESOURCE_FIXED);

	/* SoC IO resource overrides */
	pch_lpc_soc_fill_io_resources(dev);
}

static void pch_lpc_read_resources(struct device *dev)
{
	/* Get the PCI resources of this device. */
	pci_dev_read_resources(dev);

	/* Add IO resources to LPC. */
	pch_lpc_add_io_resources(dev);
}

static void pch_lpc_set_child_resources(struct device *dev);

static void pch_lpc_loop_resources(struct device *dev)
{
	struct resource *res;

	for (res = dev->resource_list; res; res = res->next) {
		if (res->flags & IORESOURCE_IO)
			lpc_open_pmio_window(res->base, res->size);
	}
	pch_lpc_set_child_resources(dev);
}

/*
 * Loop through all the child devices' resources, and open up windows to the
 * LPC bus, as appropriate.
 */
static void pch_lpc_set_child_resources(struct device *dev)
{
	struct bus *link;
	struct device *child;

	for (link = dev->link_list; link; link = link->next) {
		for (child = link->children; child; child = child->sibling)
			pch_lpc_loop_resources(child);
	}
}

static void pch_lpc_set_resources(struct device *dev)
{
	pci_dev_set_resources(dev);

	/* Now open up windows to devices which have declared resources. */
	pch_lpc_set_child_resources(dev);
}

#if CONFIG(HAVE_ACPI_TABLES)
static const char *lpc_acpi_name(const struct device *dev)
{
	return "LPCB";
}
#endif

static struct device_operations device_ops = {
	.read_resources		= pch_lpc_read_resources,
	.set_resources		= pch_lpc_set_resources,
	.enable_resources	= pci_dev_enable_resources,
#if CONFIG(HAVE_ACPI_TABLES)
	.write_acpi_tables	= southbridge_write_acpi_tables,
	.acpi_name		= lpc_acpi_name,
#endif
	.init			= lpc_soc_init,
	.scan_bus		= scan_static_bus,
	.ops_pci		= &pci_dev_ops_pci,
};

static const unsigned short pci_device_ids[] = {
	PCI_DEVICE_ID_INTEL_SPT_LP_SAMPLE,
	PCI_DEVICE_ID_INTEL_SPT_LP_U_BASE,
	PCI_DEVICE_ID_INTEL_SPT_LP_U_PREMIUM,
	PCI_DEVICE_ID_INTEL_SPT_LP_Y_PREMIUM,
	PCI_DEVICE_ID_INTEL_SPT_H_H110,
	PCI_DEVICE_ID_INTEL_SPT_H_H170,
	PCI_DEVICE_ID_INTEL_SPT_H_Z170,
	PCI_DEVICE_ID_INTEL_SPT_H_Q170,
	PCI_DEVICE_ID_INTEL_SPT_H_Q150,
	PCI_DEVICE_ID_INTEL_SPT_H_B150,
	PCI_DEVICE_ID_INTEL_SPT_H_C236,
	PCI_DEVICE_ID_INTEL_SPT_H_C232,
	PCI_DEVICE_ID_INTEL_SPT_H_QM170,
	PCI_DEVICE_ID_INTEL_SPT_H_HM170,
	PCI_DEVICE_ID_INTEL_SPT_H_CM236,
	PCI_DEVICE_ID_INTEL_SPT_H_HM175,
	PCI_DEVICE_ID_INTEL_SPT_H_QM175,
	PCI_DEVICE_ID_INTEL_SPT_H_CM238,
	PCI_DEVICE_ID_INTEL_LWB_C621,
	PCI_DEVICE_ID_INTEL_LWB_C622,
	PCI_DEVICE_ID_INTEL_LWB_C624,
	PCI_DEVICE_ID_INTEL_LWB_C625,
	PCI_DEVICE_ID_INTEL_LWB_C626,
	PCI_DEVICE_ID_INTEL_LWB_C627,
	PCI_DEVICE_ID_INTEL_LWB_C628,
	PCI_DEVICE_ID_INTEL_LWB_C629,
	PCI_DEVICE_ID_INTEL_LWB_C621A,
	PCI_DEVICE_ID_INTEL_LWB_C627A,
	PCI_DEVICE_ID_INTEL_LWB_C629A,
	PCI_DEVICE_ID_INTEL_LWB_C624_SUPER,
	PCI_DEVICE_ID_INTEL_LWB_C627_SUPER_1,
	PCI_DEVICE_ID_INTEL_LWB_C621_SUPER,
	PCI_DEVICE_ID_INTEL_LWB_C627_SUPER_2,
	PCI_DEVICE_ID_INTEL_LWB_C628_SUPER,
	PCI_DEVICE_ID_INTEL_LWB_C621A_SUPER,
	PCI_DEVICE_ID_INTEL_LWB_C627A_SUPER,
	PCI_DEVICE_ID_INTEL_LWB_C629A_SUPER,
	PCI_DEVICE_ID_INTEL_EMB_SUPER,
	PCI_DEVICE_ID_INTEL_KBP_H_Q270,
	PCI_DEVICE_ID_INTEL_KBP_H_H270,
	PCI_DEVICE_ID_INTEL_KBP_H_Z270,
	PCI_DEVICE_ID_INTEL_KBP_H_Q250,
	PCI_DEVICE_ID_INTEL_KBP_H_B250,
	PCI_DEVICE_ID_INTEL_SPT_LP_Y_PREMIUM_HDCP22,
	PCI_DEVICE_ID_INTEL_SPT_LP_U_PREMIUM_HDCP22,
	PCI_DEVICE_ID_INTEL_SPT_LP_U_BASE_HDCP22,
	PCI_DEVICE_ID_INTEL_KBP_LP_SUPER_SKU,
	PCI_DEVICE_ID_INTEL_KBP_LP_U_PREMIUM,
	PCI_DEVICE_ID_INTEL_KBP_LP_Y_PREMIUM,
	PCI_DEVICE_ID_INTEL_APL_LPC,
	PCI_DEVICE_ID_INTEL_GLK_LPC,
	PCI_DEVICE_ID_INTEL_GLK_ESPI,
	PCI_DEVICE_ID_INTEL_CNL_BASE_U_LPC,
	PCI_DEVICE_ID_INTEL_CNL_U_PREMIUM_LPC,
	PCI_DEVICE_ID_INTEL_CNL_Y_PREMIUM_LPC,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_H310,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_H370,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_Z390,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_Q370,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_B360,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_C246,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_C242,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_QM370,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_HM370,
	PCI_DEVICE_ID_INTEL_CNP_H_LPC_CM246,
	PCI_DEVICE_ID_INTEL_ICL_BASE_U_ESPI,
	PCI_DEVICE_ID_INTEL_ICL_BASE_Y_ESPI,
	PCI_DEVICE_ID_INTEL_ICL_U_PREMIUM_ESPI,
	PCI_DEVICE_ID_INTEL_ICL_U_SUPER_U_ESPI,
	PCI_DEVICE_ID_INTEL_ICL_U_SUPER_U_ESPI_REV0,
	PCI_DEVICE_ID_INTEL_ICL_SUPER_Y_ESPI,
	PCI_DEVICE_ID_INTEL_ICL_Y_PREMIUM_ESPI,
	PCI_DEVICE_ID_INTEL_CMP_SUPER_U_LPC,
	PCI_DEVICE_ID_INTEL_CMP_PREMIUM_Y_LPC,
	PCI_DEVICE_ID_INTEL_CMP_PREMIUM_U_LPC,
	PCI_DEVICE_ID_INTEL_CMP_BASE_U_LPC,
	PCI_DEVICE_ID_INTEL_CMP_SUPER_Y_LPC,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_HM470,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_WM490,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_QM480,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_W480,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_H470,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_Z490,
	PCI_DEVICE_ID_INTEL_CMP_H_LPC_Q470,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_0,
	PCI_DEVICE_ID_INTEL_TGP_SUPER_U_ESPI,
	PCI_DEVICE_ID_INTEL_TGP_PREMIUM_U_ESPI,
	PCI_DEVICE_ID_INTEL_TGP_BASE_U_ESPI,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_1,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_2,
	PCI_DEVICE_ID_INTEL_TGP_SUPER_Y_ESPI,
	PCI_DEVICE_ID_INTEL_TGP_PREMIUM_Y_ESPI,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_3,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_4,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_5,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_6,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_7,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_8,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_9,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_10,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_11,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_12,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_13,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_14,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_15,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_16,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_17,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_18,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_19,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_20,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_21,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_22,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_23,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_24,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_25,
	PCI_DEVICE_ID_INTEL_TGP_ESPI_26,
	PCI_DEVICE_ID_INTEL_MCC_ESPI_0,
	PCI_DEVICE_ID_INTEL_MCC_ESPI_1,
	PCI_DEVICE_ID_INTEL_MCC_BASE_ESPI,
	PCI_DEVICE_ID_INTEL_MCC_PREMIUM_ESPI,
	PCI_DEVICE_ID_INTEL_MCC_SUPER_ESPI,
	PCI_DEVICE_ID_INTEL_MCC_ESPI_2,
	PCI_DEVICE_ID_INTEL_MCC_ESPI_3,
	PCI_DEVICE_ID_INTEL_MCC_ESPI_4,
	PCI_DEVICE_ID_INTEL_JSP_SUPER_ESPI,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_0,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_1,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_2,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_3,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_4,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_5,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_6,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_7,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_8,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_9,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_10,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_11,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_12,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_13,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_14,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_15,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_16,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_17,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_18,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_19,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_20,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_21,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_22,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_23,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_24,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_25,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_26,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_27,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_28,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_29,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_30,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_31,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_32,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_33,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_0,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_1,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_2,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_3,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_4,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_5,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_6,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_7,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_8,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_9,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_10,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_11,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_12,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_13,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_14,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_15,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_16,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_17,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_18,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_19,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_20,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_21,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_22,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_23,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_24,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_25,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_26,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_27,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_28,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_29,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_30,
	PCI_DEVICE_ID_INTEL_ADP_S_ESPI_31,
	PCI_DEVICE_ID_INTEL_ADP_P_ESPI_32,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_0,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_1,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_2,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_3,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_4,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_5,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_7,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_8,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_9,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_10,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_11,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_12,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_13,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_14,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_15,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_16,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_17,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_18,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_19,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_20,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_21,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_22,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_23,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_24,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_25,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_26,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_27,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_28,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_29,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_30,
	PCI_DEVICE_ID_INTEL_ADP_M_ESPI_31,
	0
};

static const struct pci_driver pch_lpc __pci_driver = {
	.ops = &device_ops,
	.vendor = PCI_VENDOR_ID_INTEL,
	.devices = pci_device_ids,
};
