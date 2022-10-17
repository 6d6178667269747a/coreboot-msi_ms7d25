#ifndef GPIO_NAMES_ELKHARTLAKE
#define GPIO_NAMES_ELKHARTLAKE

#include "gpio_groups.h"

/* ----------------------------- Elkhart Lake ----------------------------- */

const char *const elkhartlake_pch_group_a_names[] = {
"GP_A00","PSE_GBE0_RGMII_TXD3","n/a",
"GP_A01","PSE_GBE0_RGMII_TXD2","n/a",
"GP_A02","PSE_GBE0_RGMII_TXD1","n/a",
"GP_A03","PSE_GBE0_RGMII_TXD0","n/a",
"GP_A04","PSE_GBE0_RGMII_TXCLK","n/a",
"GP_A05","PSE_GBE0_RGMII_TXCTL","n/a",
"GP_A06","PSE_GBE0_RGMII_RXCLK","n/a",
"GP_A07","PSE_GBE0_RGMII_RXD3","n/a",
"GP_A08","PSE_GBE0_RGMII_RXD2","n/a",
"GP_A09","PSE_GBE0_RGMII_RXD1","n/a",
"GP_A10","PSE_GBE0_RGMII_RXD0","n/a",
"GP_A11","PSE_GBE1_RGMII_TXD3","n/a",
"GP_A12","PSE_GBE1_RGMII_TXD2","n/a",
"GP_A13","PSE_GBE1_RGMII_TXD1","n/a",
"GP_A14","PSE_GBE1_RGMII_TXD0","n/a",
"GP_A15","PSE_GBE1_RGMII_TXCLK","n/a",
"GP_A16","PSE_GBE1_RGMII_TXCTL","n/a",
"GP_A17","PSE_GBE1_RGMII_RXCLK","n/a",
"GP_A18","PSE_GBE1_RGMII_RXCTL","n/a",
"GP_A19","PSE_GBE1_RGMII_RXD3","AVS_I2S5_SCLK",
"GP_A20","PSE_GBE1_RGMII_RXD2","AVS_I2S5_SFRM",
"GP_A21","PSE_GBE1_RGMII_RXD1","AVS_I2S5_TXD",
"GP_A22","PSE_GBE1_RGMII_RXD0","AVS_I2S5_RXD",
"GP_A23","PSE_GBE0_RGMII_RXCTL","n/a",
};

const struct gpio_group elkhartlake_pch_group_a = {
	.display	= "------- GPIO Group GPP_A -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_a_names) / 3,
	.func_count	= 3,
	.pad_names	= elkhartlake_pch_group_a_names,
};

const char *const elkhartlake_pch_group_b_names[] = {
"GP_B00","PMC_CORE_VID0","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B01","PMC_CORE_VID1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B02","PMC_VRALERT_N","n/a","n/a","ESPI_ALERT2_N","n/a","n/a","n/a","PSE_TGPIO25",
"GP_B03","CPU_GP2","n/a","n/a","ESPI_ALERT0_N","n/a","n/a","n/a","PSE_TGPIO26",
"GP_B04","CPU_GP3","n/a","n/a","ESPI_ALERT1_N","n/a","n/a","n/a","PSE_TGPIO27",
"GP_B05","PSE_I2C0_SCL","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_B06","PSE_I2C0_SDA","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO07",
"GP_B07","PSE_I2C1_SCL","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO08",
"GP_B08","PSE_I2C1_SDA","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO09",
"GP_B09","SIO_I2C5_SDA","PSE_I2C2_SDA","n/a","ESPI_CS3_N","n/a","n/a","n/a","n/a",
"GP_B10","SIO_I2C5_SCL","PSE_I2C2_SCL","n/a","ESPI_ALERT3_N","n/a","n/a","n/a","n/a",
"GP_B11","PMC_ALERT_N","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_B12","PMC_SLP_S0_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B13","PMC_PLTRST_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_B14","SPKR","PMC_TGPIO1","SIO_SPI0_CS1_N","PSE_SPI2_CS1_N","n/a","n/a","n/a","n/a",
"GP_B15","SIO_SPI0_CS0_N","n/a","PSE_SPI2_CS0_N","n/a","ESPI_CS1_N","n/a","n/a","n/a",
"GP_B16","SIO_SPI0_CLK","n/a","PSE_SPI2_CLK","n/a","n/a","n/a","n/a","n/a",
"GP_B17","SIO_SPI0_MISO","n/a","PSE_SPI2_MISO","n/a","n/a","n/a","n/a","n/a",
"GP_B18","SIO_SPI0_MOSI","n/a","PSE_SPI2_MOSI","n/a","n/a","n/a","n/a","n/a",
"GP_B19","SIO_SPI1_CS0_N","n/a","PSE_SPI3_CS0_N","n/a","ESPI_CS2_N","n/a","n/a","n/a",
"GP_B20","SIO_SPI1_CLK","RSVD","PSE_SPI3_CLK","n/a","n/a","n/a","n/a","n/a",
"GP_B21","SIO_SPI1_MISO","RSVD","PSE_SPI3_MISO","n/a","n/a","n/a","n/a","n/a",
"GP_B22","SIO_SPI1_MOSI","n/a","PSE_SPI3_MOSI","n/a","n/a","n/a","n/a","n/a",
"GP_B23","n/a","PCHHOT_N","SIO_SPI1_CS1_N","PSE_SPI3_CS1_N","n/a","n/a","n/a","PSE_TGPIO28",
"GPIO_RSVD_0","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_1","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_b = {
	.display	= "------- GPIO Group GPP_B -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_b_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_b_names,
};

const char *const elkhartlake_pch_group_c_names[] = {
"GP_C00","SMB_CLK","PSE_I2C3_SCL","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO18",
"GP_C01","SMB_DATA","PSE_I2C3_SDA","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO19",
"GP_C02","PSE_PWM00","SMB_ALERT_N","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO29",
"GP_C03","PSE_GBE0_MDC","n/a","PSE_HSUART3_EN","n/a","n/a","RSVD","n/a","n/a",
"GP_C04","PSE_GBE0_MDIO","n/a","PSE_UART3_RTS_N","PSE_HSUART3_DE","n/a","RSVD","n/a","n/a",
"GP_C05","PSE_PWM01","n/a","PSE_UART3_CTS_N","n/a","n/a","SML_ALERT0_N","n/a","PSE_TGPIO30",
"GP_C06","PSE_GBE1_MDC","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_C07","PSE_GBE1_MDIO","n/a","PSE_HSUART3_RE","n/a","n/a","n/a","n/a","n/a",
"GP_C08","PSE_TGPIO04","DNX_FORCE_RELOAD","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C09","PSE_HSUART0_EN","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C10","PSE_TGPIO05","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C11","PSE_HSUART0_RE","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_C12","PSE_UART0_RXD","n/a","n/a","SIO_UART1_RXD","n/a","n/a","n/a","n/a",
"GP_C13","PSE_UART0_TXD","n/a","n/a","SIO_UART1_TXD","n/a","n/a","n/a","n/a",
"GP_C14","PSE_UART0_RTS_N","PSE_HSUART0_DE","n/a","SIO_UART1_RTS_N","n/a","n/a","n/a","n/a",
"GP_C15","PSE_UART0_CTS_N","n/a","n/a","SIO_UART1_CTS_N","n/a","n/a","n/a","n/a",
"GP_C16","GBE_MDIO","n/a","PSE_UART3_RXD","SIO_I2C0_SDA","n/a","n/a","n/a","n/a",
"GP_C17","GBE_MDC","n/a","PSE_UART3_TXD","SIO_I2C0_SCL","n/a","n/a","n/a","n/a",
"GP_C18","PSE_I2C4_SDA","n/a","SML_DATA0","SIO_I2C1_SDA","n/a","n/a","n/a","n/a",
"GP_C19","PSE_I2C4_SCL","n/a","SML_CLK0","SIO_I2C1_SCL","n/a","n/a","n/a","n/a",
"GP_C20","PSE_UART4_RXD","n/a","RSVD","SIO_UART2_RXD","n/a","n/a","n/a","n/a",
"GP_C21","PSE_UART4_TXD","n/a","RSVD","SIO_UART2_TXD","n/a","n/a","n/a","n/a",
"GP_C22","PSE_UART4_RTS_N","A0: N/A B0: ISI_SPIM_MOSI","RSVD","SIO_UART2_RTS_N","n/a","n/a","n/a","n/a",
"GP_C23","PSE_UART4_CTS_N","A0: N/A B0: ISI_SPIS_MOSI","RSVD","SIO_UART2_CTS_N","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_c = {
	.display	= "------- GPIO Group GPP_C -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_c_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_c_names,
};

const char *const elkhartlake_pch_group_d_names[] = {
"GP_D00","PSE_QEPA0","n/a","RSVD","PSE_SPI1_CS0_N","n/a","n/a","n/a","PSE_TGPIO32",
"GP_D01","PSE_QEPB0","n/a","RSVD","PSE_SPI1_CLK","n/a","n/a","n/a","PSE_TGPIO33",
"GP_D02","PSE_QEPI0","n/a","RSVD","PSE_SPI1_MISO","n/a","n/a","n/a","PSE_TGPIO34",
"GP_D03","PSE_PWM06","n/a","RSVD","PSE_SPI1_MOSI","n/a","n/a","n/a","PSE_TGPIO35",
"GP_D04","PSE_PWM02","n/a","RSVD","PSE_SPI1_CS1_N","n/a","n/a","n/a","PSE_TGPIO36",
"GP_D05","PCIE_CLKREQ0_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D06","PCIE_CLKREQ1_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D07","PCIE_CLKREQ2_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D08","PCIE_CLKREQ3_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_D09","PSE_SPI0_CS0_N","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_CS0_N","PSE_TGPIO10",
"GP_D10","PSE_SPI0_CLK","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_CLK","PSE_TGPIO11",
"GP_D11","PSE_SPI0_MISO","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_MISO","PSE_TGPIO12",
"GP_D12","PSE_SPI0_MOSI","n/a","n/a","n/a","n/a","n/a","SIO_SPI2_MOSI","PSE_TGPIO13",
"GP_D13","PSE_QEPA1","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO37",
"GP_D14","PSE_QEPB1","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO38",
"GP_D15","PSE_PWM03","SIO_SPI2_CS1_N","RSVD","PSE_SPI0_CS1_N","n/a","n/a","n/a","PSE_TGPIO39",
"GP_D16","PSE_QEPI1","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO40",
"GP_D17","PSE_PWM04","A0: N/A B0: ISI_SPIM_MOSI","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO41",
"GP_D18","PSE_PWM05","A0: N/A B0: ISI_SPIS_MOSI","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO42",
"GP_D19","AVS_I2S_MCLK1","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO43",
"GPIO_RSVD_3","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_d = {
	.display	= "------- GPIO Group GPP_D -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_d_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_d_names,
};

const char *const elkhartlake_pch_group_dsw_names[] = {
"GP_DSW00","PMC_BATLOW_N",
"GP_DSW01","PMC_ACPRESENT",
"GP_DSW02","RSVD",
"GP_DSW03","PMC_PWRBTN_N",
"GP_DSW04","PMC_SLP_S3_N",
"GP_DSW05","PMC_SLP_S4_N",
"GP_DSW06","n/a",
"GP_DSW07","n/a",
"GP_DSW08","PMC_SUSCLK",
"GP_DSW09","RSVD",
"GP_DSW10","PMC_SLP_S5_N",
"GP_DSW11","RSVD",
"GPIO_RSVD_8","n/a",
"GPIO_RSVD_9","n/a",
"GPIO_RSVD_10","n/a",
"GPIO_RSVD_11","n/a",
"GPIO_RSVD_12","n/a",
};

const struct gpio_group elkhartlake_pch_group_dsw = {
	.display	= "------- GPIO Group GPP_DSW -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_dsw_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_dsw_names,
};

const char *const elkhartlake_pch_group_e_names[] = {
"GP_E00","SATA_LED_N","SATAXPCIE_0","RSVD","RSVD","RSVD","RSVD","SATA_0_GP","n/a",
"GP_E01","n/a","RSVD","RSVD","RSVD","RSVD","RSVD","RSVD","n/a",
"GP_E02","n/a","RSVD","RSVD","RSVD","RSVD","RSVD","RSVD","n/a",
"GP_E03","DDI1_HPD","PNL_MISC_DDI1","RSVD","RSVD","RSVD","RSVD","CPU_GP0","PSE_TGPIO15",
"GP_E04","SATA_0_DEVSLP","n/a","RSVD","RSVD","RSVD","RSVD","PSE_PWM08","PSE_TGPIO44",
"GP_E05","DDI1_DDC_SDA","n/a","RSVD","RSVD","RSVD","RSVD","PSE_PWM09","PSE_TGPIO17",
"GP_E06","n/a","RSVD","RSVD","RSVD","RSVD","RSVD","PSE_PWM10","PSE_TGPIO18",
"GP_E07","DDI1_DDC_SCL","n/a","RSVD","RSVD","RSVD","RSVD","CPU_GP1","PSE_TGPIO16",
"GP_E08","n/a","SATA_1_DEVSLP","RSVD","RSVD","n/a","RSVD","RSVD","PSE_TGPIO45",
"GP_E09","USB2_OC0_N","n/a","RSVD","RSVD","n/a","RSVD","n/a","n/a",
"GP_E10","n/a","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E11","n/a","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E12","n/a","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E13","n/a","RSVD","RSVD","RSVD","n/a","RSVD","RSVD","n/a",
"GP_E14","DDI0_HPD","PNL_MISC_DDI0","RSVD","RSVD","n/a","RSVD","n/a","PSE_TGPIO19",
"GP_E15","PSE_I2S0_RXD","RSVD","RSVD","RSVD","n/a","RSVD","PSE_CAN0_TX","PSE_TGPIO17",
"GP_E16","PSE_I2S0_TXD","RSVD","RSVD","RSVD","RSVD","RSVD","PSE_CAN0_RX","PSE_TGPIO16",
"GP_E17","PNL1_VDDEN","RSVD","RSVD","RSVD","PNL_MISC_DDI2","RSVD","PSE_PWM11","PSE_TGPIO46",
"GP_E18","DDI0_DDC_SDA","n/a","n/a","n/a","RSVD","n/a","PSE_PWM12","PSE_TGPIO23",
"GP_E19","DDI0_DDC_SCL","n/a","n/a","n/a","RSVD","n/a","PSE_PWM13","PSE_TGPIO24",
"GP_E20","PSE_I2S0_SCLK","n/a","n/a","n/a","n/a","n/a","PSE_CAN1_TX","PSE_TGPIO14",
"GP_E21","PSE_I2S0_SFRM","n/a","n/a","n/a","n/a","n/a","PSE_CAN1_RX","PSE_TGPIO15",
"GP_E22","PNL1_BKLTCTL","n/a","n/a","n/a","n/a","n/a","PSE_PWM14","PSE_TGPIO18",
"GP_E23","PNL1_BKLTEN","n/a","n/a","n/a","n/a","n/a","PSE_PWM15","PSE_TGPIO19",
};

const struct gpio_group elkhartlake_pch_group_e = {
	.display	= "------- GPIO Group GPP_E -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_e_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_e_names,
};

const char *const elkhartlake_pch_group_f_names[] = {
"GP_F00","RSVD","SIO_UART0_RTS_N","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F01","RSVD","SIO_UART0_RXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F02","RSVD","SIO_UART0_TXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F03","RSVD","SIO_UART0_CTS_N","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F04","RSVD","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F05","RSVD","RSVD","RSVD","RSVD","n/a","n/a","n/a","PSE_TGPIO14",
"GP_F06","RSVD","n/a","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO47",
"GP_F07","PSE_I2S1_SCLK","n/a","n/a","n/a","AVS_I2S4_SCLK","n/a","n/a","PSE_TGPIO14",
"GP_F08","AVS_I2S_MCLK2","n/a","n/a","PSE_TRACEDATA_0","ISI_TRACEDATA_0","n/a","n/a","PSE_TGPIO48",
"GP_F09","BOOT_PWR_EN","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F10","PSE_I2S1_SFRM","n/a","n/a","n/a","AVS_I2S4_SFRM","n/a","n/a","PSE_TGPIO15",
"GP_F11","n/a","n/a","RSVD","PSE_TRACECLK","ISI_TRACECLK","n/a","n/a","PSE_TGPIO49",
"GP_F12","RSVD","AVS_I2S4_TXD","RSVD","PSE_TRACESWO","ISI_TRACESWO","n/a","n/a","n/a",
"GP_F13","RSVD","AVS_I2S4_SFRM","RSVD","PSE_SWDIO","ISI_SWDIO","n/a","n/a","n/a",
"GP_F14","RSVD","AVS_I2S4_RXD","RSVD","PSE_TRACEDATA_1","ISI_TRACEDATA_1","n/a","n/a","n/a",
"GP_F15","RSVD","n/a","RSVD","PSE_TRACEDATA_2","ISI_TRACEDATA_2","n/a","n/a","n/a",
"GP_F16","RSVD","AVS_I2S4_SCLK","RSVD","PSE_SWCLK","ISI_SWCLK","n/a","n/a","n/a",
"GP_F17","n/a","n/a","RSVD","PSE_TRACEDATA_3","ISI_TRACEDATA_3","n/a","n/a","PSE_TGPIO50",
"GP_F18","PSE_I2S1_TXD","n/a","n/a","n/a","AVS_I2S4_TXD","n/a","n/a","PSE_TGPIO16",
"GP_F19","PSE_I2S1_RXD","n/a","n/a","n/a","AVS_I2S4_RXD","n/a","n/a","PSE_TGPIO17",
"GP_F20","RSVD","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F21","RSVD","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F22","PMC_VNN_CTRL","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_F23","PMC_V1P05_CTRL","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_30","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_31","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_32","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_33","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_34","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_35","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_36","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_f = {
	.display	= "------- GPIO Group GPP_F -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_f_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_f_names,
};

const char *const elkhartlake_pch_group_g_names[] = {
"GP_G00","SD_SDIO_CMD","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G01","SD_SDIO_D0","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G02","SD_SDIO_D1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G03","SD_SDIO_D2","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G04","SD_SDIO_D3","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G05","SD_SDIO_CD_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G06","SD_SDIO_CLK","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G07","AVS_I2S2_SCLK","n/a","n/a","DMIC_CLK_A0","n/a","n/a","n/a","n/a",
"GP_G08","AVS_I2S2_SFRM","RSVD","n/a","DMIC_DATA0","n/a","n/a","n/a","n/a",
"GP_G09","AVS_I2S2_TXD","RSVD","RSVD","DMIC_CLK_A1","n/a","n/a","n/a","n/a",
"GP_G10","AVS_I2S2_RXD","n/a","n/a","DMIC_DATA1","n/a","n/a","n/a","n/a",
"GP_G11","AVS_I2S3_SCLK","n/a","n/a","DMIC_DATA0","n/a","n/a","n/a","PSE_TGPIO07",
"GP_G12","AVS_I2S3_SFRM","SATA_1_GP","SATAXPCIE_1","DMIC_DATA1","n/a","n/a","n/a","PSE_TGPIO31",
"GP_G13","AVS_I2S3_TXD","n/a","n/a","DMIC_CLK_B0","n/a","n/a","n/a","PSE_TGPIO08",
"GP_G14","AVS_I2S3_RXD","n/a","n/a","DMIC_CLK_B1","n/a","n/a","n/a","PSE_TGPIO09",
"GP_G15","ESPI_IO0","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G16","ESPI_IO1","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G17","ESPI_IO2","Reserved","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G18","ESPI_IO3","Reserved","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G19","AVS_I2S1_SCLK","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G20","ESPI_CS0_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G21","ESPI_CLK","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G22","ESPI_RST0_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_G23","SD_SDIO_WP","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_2","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_g = {
	.display	= "------- GPIO Group GPP_G -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_g_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_g_names,
};

const char *const elkhartlake_pch_group_h_names[] = {
"GP_H00","PSE_GBE1_INT","n/a","n/a","PSE_UART5_RXD","n/a","n/a","n/a","n/a",
"GP_H01","PSE_GBE1_RST_N","n/a","n/a","PSE_UART5_TXD","n/a","n/a","n/a","n/a",
"GP_H02","PSE_GBE1_AUXTS","n/a","n/a","PSE_UART5_RTS_N","n/a","n/a","n/a","n/a",
"GP_H03","PSE_GBE1_PPS","n/a","n/a","PSE_UART5_CTS_N","n/a","n/a","n/a","PSE_TGPIO21",
"GP_H04","SIO_I2C2_SDA","n/a","n/a","PSE_PWM08","n/a","n/a","n/a","PSE_TGPIO10",
"GP_H05","SIO_I2C2_SCL","n/a","n/a","PSE_PWM09","n/a","n/a","n/a","PSE_TGPIO11",
"GP_H06","SIO_I2C3_SDA","PSE_I2C5_SDA","n/a","PSE_PWM10","n/a","n/a","n/a","n/a",
"GP_H07","SIO_I2C3_SCL","PSE_I2C5_SCL","n/a","PSE_PWM11","n/a","n/a","n/a","n/a",
"GP_H08","SIO_I2C4_SDA","RSVD","n/a","PSE_PWM12","n/a","n/a","n/a","n/a",
"GP_H09","SIO_I2C4_SCL","RSVD","n/a","PSE_PWM13","n/a","n/a","n/a","n/a",
"GP_H10","PCIE_CLKREQ4_N","n/a","n/a","PSE_PWM14","n/a","n/a","n/a","n/a",
"GP_H11","PCIE_CLKREQ5_N","n/a","n/a","PSE_PWM15","n/a","n/a","n/a","n/a",
"GP_H12","PSE_UART1_RXD","n/a","n/a","M2_SKT2_CFG0","n/a","n/a","n/a","PSE_TGPIO51",
"GP_H13","PSE_UART1_TXD","n/a","n/a","M2_SKT2_CFG1","n/a","n/a","n/a","PSE_TGPIO52",
"GP_H14","n/a","n/a","n/a","M2_SKT2_CFG2","n/a","n/a","n/a","PSE_TGPIO53",
"GP_H15","PSE_UART1_CTS_N","n/a","n/a","M2_SKT2_CFG3","n/a","n/a","n/a","PSE_TGPIO54",
"GP_H16","PCIE_LNK_DOWN","DDI2_DDC_SCL","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H17","SD_SDIO_PWR_EN_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H18","PMC_CPU_C10_GATE_N","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_H19","n/a","DDI2_DDC_SDA","n/a","PMC_TGPIO0","n/a","n/a","n/a","PSE_TGPIO20",
"GP_H20","PSE_PWM07","DDI2_HPD","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO55",
"GP_H21","PSE_HSUART1_DE","PSE_UART1_RTS_N","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO56",
"GP_H22","PSE_HSUART1_RE","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO57",
"GP_H23","PSE_HSUART1_EN","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO58",
};

const struct gpio_group elkhartlake_pch_group_h = {
	.display	= "------- GPIO Group GPP_H -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_h_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_h_names,
};

const char *const elkhartlake_pch_group_r_names[] = {
"GP_R00","HDA_BCLK","AVS_I2S0_SCLK","PSE_I2S0_SCLK","RSVD","n/a",
"GP_R01","HDA_SYNC","AVS_I2S0_SFRM","PSE_I2S0_SFRM","n/a","n/a",
"GP_R02","HDA_SDO","AVS_I2S0_TXD","PSE_I2S0_TXD","RSVD","DMIC_CLK_B0",
"GP_R03","HDA_SDI0","AVS_I2S0_RXD","PSE_I2S0_RXD","RSVD","DMIC_CLK_B1",
"GP_R04","HDA_RST_N","n/a","n/a","n/a","DMIC_CLK_A1",
"GP_R05","HDA_SDI1","AVS_I2S1_RXD","n/a","n/a","DMIC_DATA1",
"GP_R06","n/a","AVS_I2S1_TXD","n/a","n/a","DMIC_CLK_A0",
"GP_R07","n/a","AVS_I2S1_SFRM","n/a","n/a","DMIC_DATA0",
};

const struct gpio_group elkhartlake_pch_group_r = {
	.display	= "------- GPIO Group GPP_R -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_r_names) / 6,
	.func_count	= 6,
	.pad_names	= elkhartlake_pch_group_r_names,
};

const char *const elkhartlake_pch_group_s_names[] = {
"GPIO_RSVD_13","n/a",
"GPIO_RSVD_14","n/a",
"GPIO_RSVD_15","n/a",
"GPIO_RSVD_16","n/a",
"GPIO_RSVD_17","n/a",
"GPIO_RSVD_18","n/a",
"GPIO_RSVD_19","n/a",
"GPIO_RSVD_20","n/a",
"GPIO_RSVD_21","n/a",
"GPIO_RSVD_22","n/a",
"GPIO_RSVD_23","n/a",
"GPIO_RSVD_24","n/a",
"GPIO_RSVD_25","n/a",
"GPIO_RSVD_26","n/a",
"GPIO_RSVD_27","n/a",
"GPIO_RSVD_28","n/a",
"GPIO_RSVD_29","n/a",
"GP_S00","n/a",
"GP_S01","n/a",
};

const struct gpio_group elkhartlake_pch_group_s = {
	.display	= "------- GPIO Group GPP_S -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_s_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_s_names,
};

const char *const elkhartlake_pch_group_t_names[] = {
"GP_T00","PSE_QEPA2","n/a","SIO_I2C6_SDA","n/a","n/a","n/a","n/a","PSE_TGPIO08",
"GP_T01","PSE_QEPB2","n/a","SIO_I2C6_SCL","n/a","n/a","n/a","n/a","PSE_TGPIO09",
"GP_T02","PSE_QEPI2","n/a","SIO_I2C7_SDA","n/a","n/a","n/a","n/a","PSE_TGPIO07",
"GP_T03","n/a","n/a","SIO_I2C7_SCL","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_T04","PSE_GBE0_INT","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T05","PSE_GBE0_RST_N","n/a","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T06","PSE_GBE0_AUXTS","USB2_OC1_N","n/a","RSVD","n/a","n/a","n/a","n/a",
"GP_T07","PSE_GBE0_PPS","n/a","n/a","RSVD","n/a","n/a","n/a","PSE_TGPIO59",
"GP_T08","USB2_OC2_N","RSVD","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO22",
"GP_T09","PSE_HSUART2_EN","RSVD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T10","PSE_HSUART2_RE","RSVD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T11","USB2_OC3_N","RSVD","n/a","n/a","n/a","n/a","n/a","PSE_TGPIO06",
"GP_T12","PSE_UART2_RXD","SIO_UART0_RXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T13","PSE_UART2_TXD","SIO_UART0_TXD","n/a","n/a","n/a","n/a","n/a","n/a",
"GP_T14","PSE_UART2_RTS_N","SIO_UART0_RTS_N","PSE_HSUART2_DE","n/a","n/a","n/a","n/a","n/a",
"GP_T15","PSE_UART2_CTS_N","SIO_UART0_CTS_N","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_t = {
	.display	= "------- GPIO Group GPP_T -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_t_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_t_names,
};

const char *const elkhartlake_pch_group_u_names[] = {
"GP_U00","GBE_INT","PSE_I2C6_SCL","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U01","GBE_RST_N","PSE_I2C6_SDA","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U02","GBE_PPS","PSE_I2C7_SCL","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U03","GBE_AUXTS","PSE_I2C7_SDA","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U04","ISI_SPIM_CS","n/a","RSVD","PSE_SPI1_CS0_N","n/a","n/a","n/a","n/a",
"GP_U05","ISI_SPIM_SCLK","n/a","RSVD","PSE_SPI1_CLK","n/a","n/a","n/a","n/a",
"GP_U06","ISI_SPIM_MISO","n/a","RSVD","PSE_SPI1_MISO","n/a","n/a","n/a","n/a",
"GP_U07","PSE_QEPA3","n/a","RSVD","PSE_SPI1_MOSI","n/a","n/a","n/a","PSE_TGPIO10",
"GP_U08","ISI_SPIS_CS","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO10",
"GP_U09","ISI_SPIS_SCLK","ISI_I2CS_SCL","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO11",
"GP_U10","ISI_SPIS_MISO","ISI_I2CS_SDA","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO12",
"GP_U11","PSE_QEPB3","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO11",
"GP_U12","ISI_CHX_OKNOK_0","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U13","ISI_CHX_OKNOK_1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U14","ISI_CHX_RLY_SWTCH","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U15","ISI_CHX_PMIC_EN","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO13",
"GP_U16","ISI_OKNOK_0","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U17","ISI_OKNOK_1","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U18","ISI_ALERT_N","n/a","RSVD","n/a","n/a","n/a","n/a","n/a",
"GP_U19","PSE_QEPI3","n/a","RSVD","n/a","n/a","n/a","n/a","PSE_TGPIO12",
"GPIO_RSVD_4","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_5","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_6","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
"GPIO_RSVD_7","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a",
};

const struct gpio_group elkhartlake_pch_group_u = {
	.display	= "------- GPIO Group GPP_U -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_u_names) / 9,
	.func_count	= 9,
	.pad_names	= elkhartlake_pch_group_u_names,
};

const char *const elkhartlake_pch_group_v_names[] = {
"GP_V00","EMMC_CMD",
"GP_V01","EMMC_DATA0",
"GP_V02","EMMC_DATA1",
"GP_V03","EMMC_DATA2",
"GP_V04","EMMC_DATA3",
"GP_V05","EMMC_DATA4",
"GP_V06","EMMC_DATA5",
"GP_V07","EMMC_DATA6",
"GP_V08","EMMC_DATA7",
"GP_V09","EMMC_RCLK",
"GP_V10","EMMC_CLK",
"GP_V11","EMMC_RST_N",
"GP_V12","PSE_TGPIO00",
"GP_V13","PSE_TGPIO01",
"GP_V14","PSE_TGPIO02",
"GP_V15","PSE_TGPIO03",
};

const struct gpio_group elkhartlake_pch_group_v = {
	.display	= "------- GPIO Group GPP_V -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_v_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_v_names,
};

const char *const elkhartlake_pch_group_vgpio_names[] = {
"VGPIO_0","n/a",
"VGPIO_4","n/a",
"VGPIO_5","n/a",
"VGPIO_6","n/a",
"VGPIO_7","n/a",
"VGPIO_8","n/a",
"VGPIO_9","n/a",
"VGPIO_10","n/a",
"VGPIO_11","n/a",
"VGPIO_12","n/a",
"VGPIO_13","n/a",
"VGPIO_18","n/a",
"VGPIO_19","n/a",
"VGPIO_20","n/a",
"VGPIO_21","n/a",
"VGPIO_22","n/a",
"VGPIO_23","n/a",
"VGPIO_24","n/a",
"VGPIO_25","n/a",
"VGPIO_30","n/a",
"VGPIO_31","n/a",
"VGPIO_32","n/a",
"VGPIO_33","n/a",
"VGPIO_34","n/a",
"VGPIO_35","n/a",
"VGPIO_36","n/a",
"VGPIO_37","n/a",
"VGPIO_39","n/a",
};

const struct gpio_group elkhartlake_pch_group_vgpio = {
	.display	= "------- GPIO Group GPP_VGPIO -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_vgpio_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_vgpio_names,
};


const char *const elkhartlake_pch_group_vgpio_usb_names[] = {
"VGPIO_USB_0","n/a",
"VGPIO_USB_1","n/a",
"VGPIO_USB_2","n/a",
"VGPIO_USB_3","n/a",
};

const struct gpio_group elkhartlake_pch_group_vgpio_usb = {
	.display	= "------- GPIO Group GPP_VGPIO_USB -------",
	.pad_count	= ARRAY_SIZE(elkhartlake_pch_group_vgpio_usb_names) / 2,
	.func_count	= 2,
	.pad_names	= elkhartlake_pch_group_vgpio_usb_names,
};

const struct gpio_group *const elkhartlake_community_0_groups[] = {
	&elkhartlake_pch_group_b,
    &elkhartlake_pch_group_t,
    &elkhartlake_pch_group_g,
};

const struct gpio_community elkhartlake_community_0 = {
	.name		= "------- GPIO Community 0 -------",
	.pcr_port_id	= 0x6e,
	.group_count	= ARRAY_SIZE(elkhartlake_community_0_groups),
	.groups		= elkhartlake_community_0_groups,
};

const struct gpio_group *const elkhartlake_community_1_groups[] = {
    &elkhartlake_pch_group_v,
    &elkhartlake_pch_group_h,
    &elkhartlake_pch_group_d,
    &elkhartlake_pch_group_u,
    &elkhartlake_pch_group_vgpio,
};

const struct gpio_community elkhartlake_community_1 = {
	.name		= "------- GPIO Community 1 -------",
	.pcr_port_id	= 0x6d,
	.group_count	= ARRAY_SIZE(elkhartlake_community_1_groups),
	.groups		= elkhartlake_community_1_groups,
};

const struct gpio_group *const elkhartlake_community_2_groups[] = {
    &elkhartlake_pch_group_dsw,
};

const struct gpio_community elkhartlake_community_2 = {
	.name		= "------- GPIO Community 2 -------",
	.pcr_port_id	= 0x6c,
	.group_count	= ARRAY_SIZE(elkhartlake_community_2_groups),
	.groups		= elkhartlake_community_2_groups,
};

const struct gpio_group *const elkhartlake_community_3_groups[] = {
    &elkhartlake_pch_group_s,
    &elkhartlake_pch_group_a,
    &elkhartlake_pch_group_vgpio_usb,
};

const struct gpio_community elkhartlake_community_3 = {
	.name		= "------- GPIO Community 3 -------",
	.pcr_port_id	= 0x6b,
	.group_count	= ARRAY_SIZE(elkhartlake_community_3_groups),
	.groups		= elkhartlake_community_3_groups,
};

const struct gpio_group *const elkhartlake_community_4_groups[] = {
    &elkhartlake_pch_group_c,
    &elkhartlake_pch_group_f,
    &elkhartlake_pch_group_e,
};

const struct gpio_community elkhartlake_community_4 = {
	.name		= "------- GPIO Community 4 -------",
	.pcr_port_id	= 0x6a,
	.group_count	= ARRAY_SIZE(elkhartlake_community_4_groups),
	.groups		= elkhartlake_community_4_groups,
};

const struct gpio_group *const elkhartlake_community_5_groups[] = {
    &elkhartlake_pch_group_r,
};

const struct gpio_community elkhartlake_community_5 = {
	.name		= "------- GPIO Community 5 -------",
	.pcr_port_id	= 0x69,
	.group_count	= ARRAY_SIZE(elkhartlake_community_5_groups),
	.groups		= elkhartlake_community_5_groups,
};

const struct gpio_community *const elkhartlake_pch_communities[] = {
	&elkhartlake_community_0,
	&elkhartlake_community_1,
	&elkhartlake_community_2,
	&elkhartlake_community_3,
	&elkhartlake_community_4,
	&elkhartlake_community_5,
};

#endif