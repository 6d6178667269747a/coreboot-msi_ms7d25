/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef HDA_VERB_H
#define HDA_VERB_H

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {

	0x8086280B,
	0x00000000,
	0x00000005,

	/*
	 * Display Audio Verb Table
	 * Enable the third converter and Pin first (NID 08h)
	 */
	0x00878101,
	0x00878101,
	0x00878101,
	0x00878101,

	AZALIA_PIN_CFG(0, 0x05, 0x18560010),
	AZALIA_PIN_CFG(0, 0x06, 0x18560020),
	AZALIA_PIN_CFG(0, 0x07, 0x18560030),

	/* Disable the third converter and third Pin (NID 08h) */
	0x00878100,
	0x00878100,
	0x00878100,
	0x00878100,

	/* ALC 298 */
	0x10EC0298,
	0x00000000,
	0x00000023,

	AZALIA_SUBVENDOR(0, 0x10EC109C),
	AZALIA_PIN_CFG(0, 0x01, 0x00000000),
	AZALIA_PIN_CFG(0, 0x12, 0x411111F0),
	AZALIA_PIN_CFG(0, 0x13, 0x40000000),
	AZALIA_PIN_CFG(0, 0x14, 0x9017011F),
	AZALIA_PIN_CFG(0, 0x17, 0x90170110),
	AZALIA_PIN_CFG(0, 0x18, 0x03A11040),
	AZALIA_PIN_CFG(0, 0x19, 0x411111F0),
	AZALIA_PIN_CFG(0, 0x1A, 0x411111F0),
	AZALIA_PIN_CFG(0, 0x1D, 0x4066A22D),
	AZALIA_PIN_CFG(0, 0x1E, 0x411111F0),
	AZALIA_PIN_CFG(0, 0x21, 0x03211020),

	/* Widget node 0x20 */
	0x0205004F,
	0x0204B009,
	0x02050050,
	0x02041000,
	/* Widget node 0x20 - 1 */
	0x02050019,
	0x02040017,
	0x02050020,
	0x02040002,
	/* Widget node 0x20 - 2 */
	0x0205008F,
	0x02041008,
	0x02050036,
	0x020462C0,
	/* Widget node 0x20 - 3 */
	0x0205002B,
	0x02040D10,
	0x0205002D,
	0x02044020,
	/* Widget node 0x20 - 4 */
	0x0205000E,
	0x02046F80,
	0x01771F90,
	0x01771F90,
	/* Widget node 0x20 - 5 */
	0x02050079,
	0x02046800,
	0x02050079,
	0x02046800,

	/* TI AMP settings */
	0x02050022,
	0x0204004C,
	0x02050023,
	0x02040000,
	0x02050025,
	0x02040000,
	0x02050026,
	0x0204B010,

	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,

	0x02050022,
	0x0204004C,
	0x02050023,
	0x02040002,
	0x02050025,
	0x02040011,
	0x02050026,
	0x0204B010,

	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,

	0x02050022,
	0x0204004C,
	0x02050023,
	0x0204000F,
	0x02050025,
	0x02040010,
	0x02050026,
	0x0204B010,

	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,

	0x02050022,
	0x0204004C,
	0x02050023,
	0x02040025,
	0x02050025,
	0x02040008,
	0x02050026,
	0x0204B010,

	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,

	0x02050022,
	0x0204004C,
	0x02050023,
	0x02040002,
	0x02050025,
	0x02040000,
	0x02050026,
	0x0204B010,

	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,
	0x000F0000,

	0x02050022,
	0x0204004C,
	0x02050023,
	0x02040003,
	0x02050025,
	0x02040000,
	0x02050026,
	0x0204B010
};

const u32 pc_beep_verbs[] = {
};
AZALIA_ARRAY_SIZES;
#endif
