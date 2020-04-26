/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x10ec0887,	/* Codec Vendor / Device ID: Realtek */
	0x14627707,	/* Subsystem ID */
	15,		/* Number of 4 dword sets */
	AZALIA_SUBVENDOR(0, 0x14627707),
	AZALIA_PIN_CFG(0, 0x11, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x12, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x14, 0x01014410),
	AZALIA_PIN_CFG(0, 0x15, 0x01011412),
	AZALIA_PIN_CFG(0, 0x16, 0x01016411),
	AZALIA_PIN_CFG(0, 0x17, 0x01012414),
	AZALIA_PIN_CFG(0, 0x18, 0x01813c40),
	AZALIA_PIN_CFG(0, 0x19, 0x02a19c50),
	AZALIA_PIN_CFG(0, 0x1a, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1b, 0x02214c20),
	AZALIA_PIN_CFG(0, 0x1c, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1d, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1e, 0x01454130),
	AZALIA_PIN_CFG(0, 0x1f, 0x411111f0),
};

const u32 pc_beep_verbs[0] = {};

AZALIA_ARRAY_SIZES;
