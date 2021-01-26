/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage */
/* Leave eSPI pins untouched from default settings */
static const struct pad_config gpio_table[] = {
	/* A0 thru A6 come configured out of reset, do not touch */
	/* A0  : ESPI_IO0 ==> ESPI_IO_0 */
	/* A1  : ESPI_IO1 ==> ESPI_IO_1 */
	/* A2  : ESPI_IO2 ==> ESPI_IO_2 */
	/* A3  : ESPI_IO3 ==> ESPI_IO_3 */
	/* A4  : ESPI_CS# ==> ESPI_CS_L */
	/* A5  : ESPI_CLK ==> ESPI_CLK */
	/* A6  : ESPI_RESET# ==> NC(TP764) */
	/* A7  : I2S2_SCLK ==> NC */
	PAD_NC(GPP_A7, NONE),
	/* A8  : I2S2_SFRM ==> NC */
	PAD_NC(GPP_A8, NONE),
	/* A9  : I2S2_TXD ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_A9, NONE, DEEP),
	/* A10 : I2S2_RXD ==> NC */
	PAD_NC(GPP_A10, NONE),
	/* A11 : PMC_I2C_SDA ==> SSD_PERST_L */
	PAD_CFG_GPO(GPP_A11, 1, DEEP),
	/* A12 : SATAXPCIE1 ==> M2_SSD_PEDET */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* A13 : PMC_I2C_SCL ==> NC */
	PAD_NC(GPP_A13, NONE),
	/* A14 : USB_OC1# ==> USB_A0_OC_ODL */
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	/* A15 : USB_OC2# ==> USB_A1_OC_ODL */
	PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1),
	/* A16 : USB_OC3# ==> NC */
	PAD_NC(GPP_A16, NONE),
	/* A17 : DDSP_HPDC ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_A17, NONE, DEEP),
	/* A18 : DDSP_HPDB ==> NC */
	PAD_NC(GPP_A18, NONE),
	/* A19 : DDSP_HPD1 ==> NC */
	PAD_NC(GPP_A19, NONE),
	/* A20 : DDSP_HPD2 ==> NC */
	PAD_NC(GPP_A20, NONE),
	/* A21 : DDPC_CTRCLK ==> NC */
	PAD_NC(GPP_A21, NONE),
	/* A22 : DDPC_CTRLDATA ==> NC */
	PAD_NC(GPP_A22, NONE),
	/* A23 : I2S1_SCLK ==> NC */
	PAD_NC(GPP_A23, NONE),

	/* B0  : CORE_VID0 */
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),
	/* B1  : CORE_VID1 */
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),
	/* B2  : VRALERT# ==> VRALERT_L */
	PAD_CFG_NF(GPP_B2, NONE, DEEP, NF1),
	/* B3  : CPU_GP2 ==> NC */
	PAD_NC(GPP_B3, NONE),
	/* B4  : CPU_GP3 ==> NC */
	PAD_NC(GPP_B4, NONE),
	/* B5  : NC */
	PAD_NC(GPP_B5, NONE),
	/* B6  : NC */
	PAD_NC(GPP_B6, NONE),
	/* B7  : ISH_12C1_SDA ==> NC */
	PAD_NC(GPP_B7, NONE),
	/* B8  : ISH_I2C1_SCL ==> NC */
	PAD_NC(GPP_B8, NONE),
	/* B9  : I2C5_SDA ==> NC */
	PAD_NC(GPP_B9, NONE),
	/* B10 : I2C5_SCL ==> NC */
	PAD_NC(GPP_B10, NONE),
	/* B11 : PMCALERT# ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_B11, NONE, DEEP),
	/* B12 : SLP_S0# ==> SLP_S0_L */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* B13 : PLTRST# ==> PLT_RST_L */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	/* B14 : SPKR ==> GPP_B14_STRAP */
	PAD_NC(GPP_B14, NONE),
	/* B15 : GSPI0_CS0# ==> PCH_GSPI0_H1_TPM_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),
	/* B16 : GSPI0_CLK ==> PCH_GSPI0_H1_TPM_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),
	/* B17 : GSPI0_MISO ==> PCH_GSPIO_H1_TPM_MISO */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),
	/* B18 : GSPI0_MOSI ==> PCH_GSPI0_H1_TPM_MOSI_STRAP */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),
	/* B19 : GSPI1_CS0# ==> NC */
	PAD_NC(GPP_B19, NONE),
	/* B20 : GSPI1_CLK ==> NC */
	PAD_NC(GPP_B20, NONE),
	/* B21 : GSPI1_MISO ==> NC */
	PAD_NC(GPP_B21, NONE),
	/* B22 : GSPI1_MOSI ==> PCH_GSPI1_GPMCU_MOSI */
	PAD_CFG_NF(GPP_B22, NONE, DEEP, NF1),
	/* B23 : SML1ALERT# ==> GPP_B23_STRAP # */
	PAD_NC(GPP_B23, NONE),

	/* C0  : SMBCLK ==> NC */
	PAD_NC(GPP_C0, NONE),
	/* C1  : SMBDATA ==> NOT USED */
	PAD_NC(GPP_C1, NONE),
	/* C2  : SMBALERT# ==> GPP_C2_STRAP */
	PAD_NC(GPP_C2, NONE),
	/* C3  : SML0CLK ==> NC */
	PAD_NC(GPP_C3, NONE),
	/* C4  : SML0DATA ==> NC */
	PAD_NC(GPP_C4, NONE),
	/* C5  : SML0ALERT# ==> USB_SMB_INT_L_BOOT_STRAP0 */
	PAD_NC(GPP_C5, NONE),
	/* C6  : SML1CLK ==> EC_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C6, NONE, PLTRST, LEVEL, INVERT),
	/* C7  : SML1DATA ==> NC */
	PAD_NC(GPP_C7, NONE),
	/* C8  : UART0_RXD ==> UART_PCH_RX_DEBUG_TX */
	PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),
	/* C9  : UART0_TXD ==> UART_PCH_TX_DEBUG_RX */
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),
	/* C10 : UART0_RTS# ==> NC */
	PAD_NC(GPP_C10, NONE),
	/* C11 : UART0_CTS# ==> NC */
	PAD_NC(GPP_C11, NONE),
	/* C12 : UART1_RXD ==> MEM_STRAP_0 */
	PAD_CFG_GPI(GPP_C12, NONE, DEEP),
	/* C13 : UART1_TXD ==> NC */
	PAD_NC(GPP_C13, NONE),
	/* C14 : UART1_RTS# ==> MEM_STRAP_2 */
	PAD_CFG_GPI(GPP_C14, NONE, DEEP),
	/* C15 : UART1_CTS# ==> MEM_STRAP_1 */
	PAD_CFG_GPI(GPP_C15, NONE, DEEP),
	/* C16 : I2C0_SDA ==> NC */
	PAD_NC(GPP_C16, NONE),
	/* C17 : I2C0_SCL ==> NC */
	PAD_NC(GPP_C17, NONE),
	/* C18 : I2C1_SDA ==> NC */
	PAD_NC(GPP_C18, NONE),
	/* C19 : I2C1_SCL ==> NC */
	PAD_NC(GPP_C19, NONE),
	/* C20 : UART2_RXD ==> NC */
	PAD_NC(GPP_C20, NONE),
	/* C21 : UART2_TXD ==> H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C21, NONE, PLTRST, LEVEL, INVERT),
	/* C22 : UART2_RTS# ==> NC */
	PAD_NC(GPP_C22, NONE),
	/* C23 : UART2_CTS# ==> NC */
	PAD_NC(GPP_C23, NONE),

	/* D0  : ISH_GP0 ==> NC */
	PAD_NC(GPP_D0, NONE),
	/* D1  : ISH_GP1 ==> NC */
	PAD_NC(GPP_D1, NONE),
	/* D2  : ISH_GP2 ==> NC */
	PAD_NC(GPP_D2, NONE),
	/* D3  : ISH_GP3 ==> NC */
	PAD_NC(GPP_D3, NONE),
	/* D4  : IMGCLKOUT0 ==> NC */
	PAD_NC(GPP_D4, NONE),
	/* D5  : SRCCLKREQ0$ ==> SSD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
	/* D6  : SRCCLKREQ1# ==> NC */
	PAD_NC(GPP_D6, NONE),
	/* D7  : SRCCLKREQ2# ==> NC */
	PAD_NC(GPP_D7, NONE),
	/* D8  : SRCCLKREQ3# ==> NC */
	PAD_NC(GPP_D8, NONE),
	/* D9  : ISH_SPI_CS# ==> NC */
	PAD_NC(GPP_D9, NONE),
	/* D10 : ISH_SPI_CLK ==> NC */
	PAD_NC(GPP_D10, NONE),
	/* D11 : ISH_SPI_MISO ==> NC */
	PAD_NC(GPP_D11, NONE),
	/* D12 : ISH_SPI_MOSI ==> NC */
	PAD_NC(GPP_D12, NONE),
	/* D13 : ISH_UART0_RXD ==> NC */
	PAD_NC(GPP_D13, NONE),
	/* D14 : ISH_UART0_TXD ==> NC */
	PAD_NC(GPP_D14, NONE),
	/* D15 : ISH_UART0_RTS# ==> MEM_STRAP_3 */
	PAD_CFG_GPI(GPP_D15, NONE, DEEP),
	/* D16 : ISH_UART0_CTS# ==> NC */
	PAD_NC(GPP_D16, NONE),
	/* D17 : ISH_GP4 ==> NC */
	PAD_NC(GPP_D17, NONE),
	/* D18 : ISH_GP5 ==> NC */
	PAD_NC(GPP_D18, NONE),
	/* D19 : I2S_MCLK1 ==> I2S_MCLK1 */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),

	/* E0  : SATAXPCIE0 ==> USB_A1_RT_RST_ODL */
	PAD_CFG_GPO(GPP_E0, 1, DEEP),
	/* E1  : SPI1_IO2 ==> NC */
	PAD_NC(GPP_E1, NONE),
	/* E2  : SPI1_IO3 ==> NC */
	PAD_NC(GPP_E2, NONE),
	/* E3  : CPU_GP0 ==> NC */
	PAD_NC(GPP_E3, NONE),
	/* E4  : SATA_DEVSLP0 ==> M2_SSD_PE_WAKE_ODL */
	PAD_NC(GPP_E4, NONE),
	/* E5  : SATA_DEVSLP1 ==> M2_SSD_DEVSLP_OD */
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),
	/* E6  : THC0_SPI1_RST# ==> GPPE6_STRAP */
	PAD_NC(GPP_E6, NONE),
	/* E7  : CPU_GP1 ==> NC */
	PAD_NC(GPP_E7, NONE),
	/* E8  : SPI1_CS1# ==> NC */
	PAD_NC(GPP_E8, NONE),
	/* E9  : USB2_OC0# ==> USB_C1_OC_ODL */
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	/* E10 : SPI1_CS# ==> USB_C0_AUXP_DC */
	PAD_CFG_NF(GPP_E10, NONE, DEEP, NF6),
	/* E11 : SPI1_CLK ==> NC */
	PAD_NC(GPP_E11, NONE),
	/* E12 : SPI1_MISO_IO1 ==> NOT USED */
	PAD_NC(GPP_E12, NONE),
	/* E13 : SPI1_MOSI_IO0 ==> USB_C0_AUXN_DC */
	PAD_CFG_NF(GPP_E13, NONE, DEEP, NF6),
	/* E14 : DDPC_HPDA ==> SOC_EDP_HPD */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	/* E15 : ISH_GP6 ==> NC */
	PAD_NC(GPP_E15, NONE),
	/* E16 : ISH_GP7 ==> NC */
	PAD_NC(GPP_E16, NONE),
	/* E17 : THC0_SPI1_INT# ==> NC */
	PAD_NC(GPP_E17, NONE),
	/* E18 : DDP1_CTRLCLK ==> USB_C0_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	/* E19 : DDP1_CTRLDATA ==> USB0_C0_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	/* E20 : DDP2_CTRLCLK ==> USB_C1_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	/* E21 : DDP2_CTRLDATA ==> USB_C1_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),
	/* E22 : DDPA_CTRLCLK ==> USB_C1_AUXP_DC: Retimer FW drives this pin */
	PAD_NC(GPP_E22, NONE),
	/* E23 : DDPA_CTRLDATA ==> USB_C1_AUXN_DC: Retimer FW drives this pin */
	PAD_NC(GPP_E23, NONE),

	/* F0  : CNV_BRI_DT ==> CNV_BRI_DT_STRAP */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	/* F1  : CNV_BRI_RSP ==> NCV_BRI_RSP */
	PAD_CFG_NF(GPP_F1, UP_20K, DEEP, NF1),
	/* F2  : I2S2_TXD ==> CNV_RGI_DT_STRAP */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	/* F3  : I2S2_RXD ==> CNV_RGI_RSP */
	PAD_CFG_NF(GPP_F3, UP_20K, DEEP, NF1),
	/* F4  : CNV_RF_RESET# ==> CNV_RF_RST_L */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F5  : MODEM_CLKREQ ==> CNV_CLKREQ0 */
	PAD_CFG_NF(GPP_F5, NONE, DEEP, NF3),
	/* F6  : CNV_PA_BLANKING ==> NC */
	PAD_NC(GPP_F6, NONE),
	/* F7  : GPPF7_STRAP */
	PAD_NC(GPP_F7, NONE),
	/* F8  : I2S_MCLK2_INOUT ==> NC */
	PAD_NC(GPP_F8, NONE),
	/* F9  : Reserved ==> NC */
	PAD_NC(GPP_F9, NONE),
	/* F10 : GPPF10_STRAP */
	PAD_NC(GPP_F10, DN_20K),
	/* F11 : THC1_SPI2_CLK ==> EN_PP3300_WWAN */
	PAD_CFG_GPO(GPP_F11, 1, DEEP),
	/* F12 : GSXDOUT ==> NC */
	PAD_NC(GPP_F12, NONE),
	/* F13 : GSXDOUT ==> NC */
	PAD_NC(GPP_F13, NONE),
	/* F14 : GSXDIN ==> NC */
	PAD_NC(GPP_F14, NONE),
	/* F15 : GSXSRESET# ==> NC */
	PAD_NC(GPP_F15, NONE),
	/* F16 : GSXCLK ==> NC */
	PAD_NC(GPP_F16, NONE),
	/* F17 : NC */
	PAD_NC(GPP_F17, NONE),
	/* F18 : THC1_SPI2_INT# ==> NC */
	PAD_NC(GPP_F18, NONE),
	/* F19 : SRCCLKREQ6# ==> NC */
	PAD_NC(GPP_F19, NONE),
	/* F20 : EXT_PWR_GATE# ==> EXT_PWR_GATE_L */
	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1),
	/* F21 : EXT_PWR_GATE2# ==> EXT_PWR_GATE2_L */
	PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1),
	/* F22 : VNN_CTRL */
	PAD_CFG_NF(GPP_F22, NONE, DEEP, NF1),
	/* F23 : V1P05_CTRL */
	PAD_CFG_NF(GPP_F23, NONE, DEEP, NF1),

	/* H0  : GPPH0_BOOT_STRAP1 */
	PAD_NC(GPP_H0, NONE),
	/* H1  : GPPH1_BOOT_STRAP2 */
	PAD_NC(GPP_H1, NONE),
	/* H2  : GPPH2_BOOT_STRAP3 */
	PAD_NC(GPP_H2, NONE),
	/* H3  : SX_EXIT_HOLDOFF# ==> NC */
	PAD_NC(GPP_H3, NONE),
	/* H4  : I2C2_SDA ==> PCH_I2C2_MISC_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : I2C2_SCL ==> PCH_I2C2_MISC_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H6  : I2C3_SDA ==> NC */
	PAD_NC(GPP_H6, NONE),
	/* H7  : I2C3_SCL ==> NC */
	PAD_NC(GPP_H7, NONE),
	/* H8  : I2C4_SDA ==> NC */
	PAD_NC(GPP_H8, NONE),
	/* H9  : I2C4_SCL ==> NC */
	PAD_NC(GPP_H9, NONE),
	/* H10 : SRCCLKREQ4# ==> USB_C1_RT_FORCE_PWR */
	PAD_CFG_GPO(GPP_H10, 0, DEEP),
	/* H11 : SRCCLKREQ5# ==> NC */
	PAD_NC(GPP_H11, NONE),
	/* H12 : M2_SKT2_CFG0 ==> NONE */
	PAD_NC(GPP_H12, NONE),
	/* H13 : M2_SKT2_CFG1 # ==> NONE */
	PAD_NC(GPP_H13, NONE),
	/* H14 : M2_SKT2_CFG2 # ==> NC */
	PAD_NC(GPP_H14, NONE),
	/* H15 : M2_SKT2_CFG3 # ==> NC */
	PAD_NC(GPP_H15, NONE),
	/* H16 : DDPB_CTRLCLK ==> NC */
	PAD_NC(GPP_H16, NONE),
	/* H17 : DDPB_CTRLDATA ==> NC */
	PAD_NC(GPP_H17, NONE),
	/* H18 : CPU_C10_GATE# ==> CPU_C10_GATE_L */
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),
	/* H19 : TIME_SYNC0 ==> NC */
	PAD_NC(GPP_H19, NONE),
	/* H20 : IMGCLKOUT1 ==> NC */
	PAD_NC(GPP_H20, NONE),
	/* H21 : IMGCLKOUT2 ==> NC */
	PAD_NC(GPP_H21, NONE),
	/* H22 : IMGCLKOUT3 ==> NC */
	PAD_NC(GPP_H22, NONE),
	/* H23 : IMGCLKOUT4 ==> NC */
	PAD_NC(GPP_H23, NONE),

	/* R0 : HDA_BCLK ==> NC */
	PAD_NC(GPP_R0, NONE),
	/* R1 : HDA_SYNC ==> NC */
	PAD_NC(GPP_R1, NONE),
	/* R2 : HDA_SDO ==> NC */
	PAD_NC(GPP_R2, NONE),
	/* R3 : HDA_SDIO ==> NC */
	PAD_NC(GPP_R3, NONE),
	/* R4 : HDA_RST# ==> NC */
	PAD_NC(GPP_R4, NONE),
	/* R5 : HDA_SDI1 ==> NC */
	PAD_NC(GPP_R5, NONE),
	/* R6 : I2S1_TXD ==> NC */
	PAD_NC(GPP_R6, NONE),
	/* R7 : I2S1_SFRM ==> NC */
	PAD_NC(GPP_R7, NONE),

	/* S0 : SNDW0_CLK ==> NC */
	PAD_NC(GPP_S0, NONE),
	/* S1 : SNDW0_DATA ==> NC */
	PAD_NC(GPP_S1, NONE),
	/* S2 : SNDW1_CLK ==> NC */
	PAD_NC(GPP_S2, NONE),
	/* S3 : SNDW1_DATA ==> NC */
	PAD_NC(GPP_S3, NONE),
	/* S4 : SNDW2_CLK ==> NC */
	PAD_NC(GPP_S4, NONE),
	/* S5 : SNDW2_DATA ==> NC */
	PAD_NC(GPP_S5, NONE),
	/* S6 : SNDW3_CLK ==> NC */
	PAD_NC(GPP_S6, NONE),
	/* S7 : SNDW3_DATA ==> NC */
	PAD_NC(GPP_S7, NONE),

	/* GPD0: BATLOW# ==> BATLOW_L */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
	/* GPD1: ACPRESENT ==> PCH_ACPRESENT */
	PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
	/* GPD2: LAN_WAKE# ==> EC_PCH_WAKE_ODL */
	PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
	/* GPD3: PWRBTN# ==> EC_PCH_PWR_BTN_ODL */
	PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
	/* GPD4: SLP_S3# ==> SLP_S3_L */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
	/* GPD5: SLP_S4# ==> SLP_S4_L */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
	/* GPD6: SLP_A# ==> SLP_A_L */
	PAD_CFG_NF(GPD6, NONE, DEEP, NF1),
	/* GPD7: GPD7_STRAP */
	PAD_CFG_GPI(GPD7, DN_20K, DEEP),
	/* GPD8: SUSCLK ==> PCH_SUSCLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* GPD9: SLP_WLAN# ==> NC */
	PAD_NC(GPD9, NONE),
	/* GPD10: SLP_S5# ==> SLP_S5_L */
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
	/* GPD11: LANPHYC ==> NC */
	PAD_NC(GPD11, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* C8 : UART0 RX */
	PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),
	/* C9 : UART0 TX */
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),

	/* A12 : SATAXPCIE1 ==> M2_SSD_PEDET */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* A13 : PMC_I2C_SCL ==> BT_DISABLE_L */
	/* assert reset on reboot */
	PAD_CFG_GPO(GPP_A13, 0, DEEP),
	/* A17 : DDSP_HPDC ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_A17, NONE, DEEP),

	/* B11 : PMCALERT# ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_B11, NONE, DEEP),

	/* B15 : GSPI0_CS0# ==> PCH_GSPI0_H1_TPM_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),

	/* B16 : GSPI0_CLK ==> PCH_GSPI0_H1_TPM_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),

	/* B17 : GSPI0_MISO ==> PCH_GSPIO_H1_TPM_MISO */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),

	/* B18 : GSPI0_MOSI ==> PCH_GSPI0_H1_TPM_MOSI_STRAP */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),

	/* C21 : UART2_TXD ==> H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_C21, NONE, PLTRST, LEVEL, INVERT),

	/* F11 : THC1_SPI2_CLK ==> EN_PP3300_WWAN */
	PAD_CFG_GPO(GPP_F11, 1, DEEP),
};

const struct pad_config *__weak variant_base_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *__weak variant_override_gpio_table(size_t *num)
{
	*num = 0;
	return NULL;
}

const struct pad_config *__weak variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
	CROS_GPIO_WP_AH(GPIO_PCH_WP, CROS_GPIO_DEVICE_NAME),
};

const struct cros_gpio *__weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
