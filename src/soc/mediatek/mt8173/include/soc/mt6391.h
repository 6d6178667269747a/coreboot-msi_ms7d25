/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef __SOC_MEDIATEK_MT8173_MT6391_H__
#define __SOC_MEDIATEK_MT8173_MT6391_H__

#include <types.h>

/*
 * PMIC definition
 */
enum {
	PMIC6391_E1_CID_CODE = 0x1091,
	PMIC6391_E2_CID_CODE = 0x2091,
	PMIC6397_E1_CID_CODE = 0x1097,
	PMIC6397_E2_CID_CODE = 0x2097,
	PMIC6397_E3_CID_CODE = 0x3097,
	PMIC6397_E4_CID_CODE = 0x4097
};

/*
 * PMIC Register Index
 */

/* PCHR Register Definition */
enum {
	PMIC_RG_CHR_CON1 = 0x0002,
	PMIC_RG_CHR_CON6 = 0x000C,
	PMIC_RG_CHR_CON13 = 0x001A,
	PMIC_RG_CHR_CON18 = 0x0024,
	PMIC_RG_CHR_CON21 = 0x002A,
	PMIC_RG_CHR_CON23 = 0x002E,
};

/* TOP Register Definition */
enum{
	PMIC_RG_CID = 0x0100,
	PMIC_RG_TOP_CKPDN = 0x0102,
	PMIC_RG_TOP_CKPDN2 = 0x0108,
	PMIC_RG_TOP_RST_CON = 0x0114,
	PMIC_RG_WRP_CKPDN = 0x011A,
	PMIC_RG_TOP_RST_MISC = 0x0126,
	PMIC_RG_TOP_CKCON1 = 0x0128,
	PMIC_RG_TOP_CKCON2 = 0x012A,
	PMIC_RG_TOP_CKTST1 = 0x012C,
	PMIC_RG_TOP_CKTST2 = 0x012E,
	PMIC_RG_OC_DEG_EN = 0x0130,
	PMIC_RG_OC_CTL1 = 0x0134,
	PMIC_RG_CHRSTATUS = 0x0144,
	PMIC_RG_OCSTATUS0 = 0x0146,
	PMIC_RG_OCSTATUS1 = 0x0148,
	PMIC_RG_OCSTATUS2 = 0x014A,
	PMIC_RG_TOP_CKPDN3 = 0x01CE,
	PMIC_RG_TOP_CKCON3 = 0x01D4
};

/* INT Register Definition */
enum{
	PMIC_RG_INT_CON0 = 0x0178,
	PMIC_RG_INT_CON1 = 0x017E,
};

/* FQMTR Register Definition */
enum{
	PMIC_RG_FQMTR_CON0 = 0x0188,
	PMIC_RG_FQMTR_CON1 = 0x018A,
	PMIC_RG_FQMTR_CON2 = 0x018C
};

/* EFUSE Register Definition */
enum{
	PMIC_RG_EFUSE_DOUT_256_271 = 0x01EE,
	PMIC_RG_EFUSE_DOUT_272_287 = 0x01F0,
	PMIC_RG_EFUSE_DOUT_288_303 = 0x01F2,
	PMIC_RG_EFUSE_DOUT_304_319 = 0x01F4
};

/* BUCK Register Definition */
enum{
	PMIC_RG_BUCK_CON3 = 0x0206,
	PMIC_RG_BUCK_CON8 = 0x0210,
	PMIC_RG_VCA15_CON1 = 0x0216,
	PMIC_RG_VCA15_CON5 = 0x021E,
	PMIC_RG_VCA15_CON7 = 0x0222,
	PMIC_RG_VCA15_CON8 = 0x0224,
	PMIC_RG_VCA15_CON9 = 0x0226,
	PMIC_RG_VCA15_CON10 = 0x0228,
	PMIC_RG_VCA15_CON11 = 0x022A,
	PMIC_RG_VCA15_CON12 = 0x022C,
	PMIC_RG_VCA15_CON18 = 0x0238,
	PMIC_RG_VSRMCA15_CON5 = 0x0244,
	PMIC_RG_VSRMCA15_CON6 = 0x0246,
	PMIC_RG_VSRMCA15_CON7 = 0x0248,
	PMIC_RG_VSRMCA15_CON8 = 0x024A,
	PMIC_RG_VSRMCA15_CON9 = 0x024C,
	PMIC_RG_VSRMCA15_CON10 = 0x024E,
	PMIC_RG_VSRMCA15_CON11 = 0x0250,
	PMIC_RG_VSRMCA15_CON18 = 0x025E,
	PMIC_RG_VSRMCA15_CON19 = 0x0260,
	PMIC_RG_VSRMCA15_CON20 = 0x0262,
	PMIC_RG_VSRMCA15_CON21 = 0x0264,
	PMIC_RG_VCORE_CON5 = 0x0270,
	PMIC_RG_VCORE_CON6 = 0x0272,
	PMIC_RG_VCORE_CON8 = 0x0276,
	PMIC_RG_VCORE_CON9 = 0x0278,
	PMIC_RG_VCORE_CON10 = 0x027A,
	PMIC_RG_VCORE_CON11 = 0x027C,
	PMIC_RG_VCORE_CON18 = 0x028A,
	PMIC_RG_VGPU_CON1 = 0x028E,
	PMIC_RG_VGPU_CON8 = 0x029C,
	PMIC_RG_VGPU_CON18 = 0x02B0,
	PMIC_RG_VIO18_CON18 = 0x0324,
	PMIC_RG_VPCA7_CON5  = 0x0330,
	PMIC_RG_VPCA7_CON6  = 0x0332,
	PMIC_RG_VPCA7_CON7  = 0x0334,
	PMIC_RG_VPCA7_CON8  = 0x0336,
	PMIC_RG_VPCA7_CON9  = 0x0338,
	PMIC_RG_VPCA7_CON10 = 0x033A,
	PMIC_RG_VPCA7_CON11 = 0x033C,
	PMIC_RG_VPCA7_CON18 = 0x034A,
	PMIC_RG_VSRMCA7_CON5 =  0x0356,
	PMIC_RG_VSRMCA7_CON6 =  0x0358,
	PMIC_RG_VSRMCA7_CON8 =  0x035C,
	PMIC_RG_VSRMCA7_CON9 =  0x035E,
	PMIC_RG_VSRMCA7_CON10 = 0x0360,
	PMIC_RG_VSRMCA7_CON11 = 0x0362,
	PMIC_RG_VSRMCA7_CON18 = 0x0370,
	PMIC_RG_VSRMCA7_CON19 = 0x0372,
	PMIC_RG_VSRMCA7_CON20 = 0x0374,
	PMIC_RG_VSRMCA7_CON21 = 0x0376,
	PMIC_RG_VDRM_CON9 = 0x038A,
	PMIC_RG_VDRM_CON10 = 0x038C,
	PMIC_RG_VDRM_CON18 = 0x039C,
	PMIC_RG_BUCK_K_CON0 = 0x039E
};

/* ANALDO Register Definition */
enum{
	PMIC_RG_ANALDO_CON0 = 0x0400,
	PMIC_RG_ANALDO_CON2 = 0x0404,
	PMIC_RG_ANALDO_CON6 = 0x040C,
};

/* DIGLDO Register Definition */
enum{
	PMIC_RG_DIGLDO_CON5 = 0x041A,
	PMIC_RG_DIGLDO_CON6 = 0x041C,
	PMIC_RG_DIGLDO_CON8 = 0x0420,
	PMIC_RG_DIGLDO_CON10  = 0x0424,
	PMIC_RG_DIGLDO_CON19  = 0x0436,
	PMIC_RG_DIGLDO_CON20  = 0x0438,
	PMIC_RG_DIGLDO_CON22  = 0x043C,
	PMIC_RG_DIGLDO_CON24  = 0x0440,
	PMIC_RG_DIGLDO_CON27  = 0x0446,
	PMIC_RG_DIGLDO_CON30  = 0x044C,
	PMIC_RG_DIGLDO_CON33  = 0x045A
};

/* STRUP Register Definition */
enum{
	PMIC_RG_STRUP_CON0	= 0x0500,
	PMIC_RG_STRUP_CON2	= 0x0502,
	PMIC_RG_STRUP_CON5	= 0x0508,
	PMIC_RG_STRUP_CON7	= 0x050C,
	PMIC_RG_STRUP_CON10	= 0x0512
};

/* AUXADC Register Definition */
enum{
	PMIC_RG_AUXADC_CON14  = 0x055E
};

/* Driver Register Definition */
enum{
	PMIC_RG_FLASH_CON0  = 0x0560,
	PMIC_RG_KPLED_CON0  = 0x0566
};

/* SPK Register Definition */
enum{
	PMIC_RG_SPK_CON0	= 0x0600,
	PMIC_RG_SPK_CON2	= 0x0604,
	PMIC_RG_SPK_CON3	= 0x0606,
	PMIC_RG_SPK_CON5	= 0x060A,
	PMIC_RG_SPK_CON9	= 0x0612
};

/* FGADC Register Definition */
enum{
	PMIC_RG_FGADC_CON13	= 0x0632,
	PMIC_RG_FGADC_CON16	= 0x0638,
	PMIC_RG_FGADC_CON17	= 0x063A,
	PMIC_RG_FGADC_CON18	= 0x063C
};

/* AUDDAC Register Definition */
enum{
	PMIC_RG_AUDLDO_CFG0	= 0x0714,
	PMIC_RG_AUD_NCP0	= 0x071A
};

/* DCXO Register Definition */
enum{
	PMIC_RG_PMIC_RG_RG_DCXO_CON0 = 0x83a,
	PMIC_RG_DCXO_CON2 = 0x83e,
	PMIC_RG_DCXO_MANUAL_CON1 = 0x844,
	PMIC_RG_DCXO_ANALOG_CON1 = 0x84a,
	PMIC_RG_DCXO_FORCE_MODE1 = 0x854,
	PMIC_RG_DCXO_POR2_CON3 = 0x85c
};

/* TOP MASK and SHIFT Definition */
enum{
	PMIC_RG_FQMTR_PDN_SHIFT = 1,
	PMIC_RG_AP_RST_DIS_MASK = 0x1,
	PMIC_RG_AP_RST_DIS_SHIFT = 0,
	PMIC_RG_RST_PART_SEL_MASK = 0x1,
	PMIC_RG_RST_PART_SEL_SHIFT = 4,
	PMIC_RG_TOP_RST_MISC_RSV_3_MASK = 0x1,
	PMIC_RG_TOP_RST_MISC_RSV_3_SHIFT = 3,
	PMIC_RG_STRUP_MAN_RST_EN_MASK = 0x1,
	PMIC_RG_STRUP_MAN_RST_EN_SHIFT = 2,
	PMIC_RG_SYSRSTB_EN_MASK = 0x1,
	PMIC_RG_SYSRSTB_EN_SHIFT = 1,
	PMIC_RG_PWRKEY_DEB_MASK = 0x1,
	PMIC_RG_PWRKEY_DEB_SHIFT = 3,
	PMIC_RG_HOMEKEY_DEB_MASK = 0x1,
	PMIC_RG_HOMEKEY_DEB_SHIFT = 4
};

/* ANALDO MASK and SHIFT Definition */
enum{
	PMIC_RG_VCAMA_VOSEL_MASK = 0x3,
	PMIC_RG_VCAMA_VOSEL_SHIFT = 6,
	PMIC_RG_VCAMA_EN_MASK = 0x1,
	PMIC_RG_VCAMA_EN_SHIFT = 15,
};

/* DCXO MASK and SHIFT Definition */
enum{
	PMIC_RG_DCXO_C2_UNTRIM_MASK = 0x1,
	PMIC_RG_DCXO_C2_UNTRIM_SHIFT = 15,
	PMIC_RG_DCXO_MANUAL_C1C2_SYNC_EN_MASK = 0x1,
	PMIC_RG_DCXO_MANUAL_C1C2_SYNC_EN_SHIFT = 9,
	PMIC_RG_DCXO_MANUAL_SYNC_EN_MASK = 0x1,
	PMIC_RG_DCXO_MANUAL_SYNC_EN_SHIFT = 8,
	PMIC_RG_DCXO_ATTEN_BB_MASK = 0x3,
	PMIC_RG_DCXO_ATTEN_BB_SHIFT = 11,
	PMIC_RG_DCXO_LDO_BB_V_MASK = 0x3,
	PMIC_RG_DCXO_LDO_BB_V_SHIFT = 2
};

enum ldo_power {
	LDO_VCAMD  = 0,	/* VGP1 */
	LDO_VGP2   = 1,	/* VGP2 */
	LDO_VCAMAF = 2,	/* VGP3 */
	LDO_VGP4   = 3,
	LDO_VGP5   = 4,
	LDO_VGP6   = 5,
	/* special, not part of main register set */
	LDO_VCAMA  = 6,
};

enum ldo_voltage {
	LDO_1P2  = 0,
	LDO_1P3  = 1,
	LDO_1P5  = 2,
	LDO_1P8  = 3,
	LDO_2P5  = 4,
	LDO_2P8  = 5,
	LDO_3P0  = 6,
	LDO_3P3  = 7,
	LDO_NUM_VOLTAGES,

	LDO_1P22, /* only VCAMD */
	LDO_1P0,  /* only VCAMIO */
	LDO_2P0,  /* only VGP5 */
};

/*
 * PMIC Exported Function
 */
int mt6391_configure_ca53_voltage(int uv);
void mt6391_configure_ldo(enum ldo_power ldo, enum ldo_voltage vsel);
void mt6391_enable_reset_when_ap_resets(void);
void mt6391_init(void);

/*
 * PMIC GPIO REGISTER DEFINITION
 */
enum {
	MT6391_GPIO_DIR_BASE = 0xC000,
	MT6391_GPIO_PULLEN_BASE = 0xC020,
	MT6391_GPIO_PULLSEL_BASE = 0xC040,
	MT6391_GPIO_DOUT_BASE = 0xC080,
	MT6391_GPIO_DIN_BASE = 0xC0A0,
	MT6391_GPIO_MODE_BASE = 0xC0C0,
};

enum mt6391_pull_enable {
	MT6391_GPIO_PULL_DISABLE = 0,
	MT6391_GPIO_PULL_ENABLE = 1,
};

enum mt6391_pull_select {
	MT6391_GPIO_PULL_DOWN = 0,
	MT6391_GPIO_PULL_UP = 1,
};

enum {
	MT6391_PMU_INT = 0,
	MT6391_SRCVOLTEN = 1,
	MT6391_SRCLKEN_PERI = 2,
	MT6391_RTC32K_1V8 = 3,
	MT6391_WRAP_EVENT = 4,
	MT6391_SPI_CLK = 5,
	MT6391_SPI_CSN = 6,
	MT6391_SPI_MOSI = 7,
	MT6391_SPI_MISO = 8,
	MT6391_AUD_CLK_MOSI = 9,
	MT6391_AUD_DAT_MISO = 10,
	MT6391_AUD_DAT_MOSI = 11,
	MT6391_KP_COL0 = 12,
	MT6391_KP_COL1 = 13,
	MT6391_KP_COL2 = 14,
	MT6391_KP_COL3 = 15,
	MT6391_KP_COL4 = 16,
	MT6391_KP_COL5 = 17,
	MT6391_KP_COL6 = 18,
	MT6391_KP_COL7 = 19,
	MT6391_KP_ROW0 = 20,
	MT6391_KP_ROW1 = 21,
	MT6391_KP_ROW2 = 22,
	MT6391_KP_ROW3 = 23,
	MT6391_KP_ROW4 = 24,
	MT6391_KP_ROW5 = 25,
	MT6391_KP_ROW6 = 26,
	MT6391_KP_ROW7 = 27,
	MT6391_VMSEL1 = 28,
	MT6391_VMSEL2 = 29,
	MT6391_PWM = 30,
	MT6391_SCL0 = 31,
	MT6391_SDA0 = 32,
	MT6391_SCL1 = 33,
	MT6391_SDA1 = 34,
	MT6391_SCL2 = 35,
	MT6391_SDA2 = 36,
	MT6391_HDMISD = 37,
	MT6391_HDMISCK = 38,
	MT6391_HTPLG = 39,
	MT6391_CEC = 40,
};

/*
 * PMIC GPIO Exported Function
 */
int mt6391_gpio_get(u32 gpio);
void mt6391_gpio_set(u32 gpio, int value);
void mt6391_gpio_input_pulldown(u32 gpio);
void mt6391_gpio_input_pullup(u32 gpio);
void mt6391_gpio_input(u32 gpio);
void mt6391_gpio_output(u32 gpio, int value);
void mt6391_gpio_set_pull(u32 gpio, enum mt6391_pull_enable enable,
			  enum mt6391_pull_select select);
void mt6391_gpio_set_mode(u32 gpio, int mode);

#endif /* __SOC_MEDIATEK_MT8173_MT6391_H__ */
