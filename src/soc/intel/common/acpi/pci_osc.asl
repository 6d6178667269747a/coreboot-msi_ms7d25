/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#define PCI_OSC_UUID "33DB4D5B-1FF7-401C-9657-7441C03DD766"

Scope (\_SB.PCI0) {
	Method (_OSC, 4) {
		/* Check for proper GUID */
		If (LEqual (Arg0, ToUUID (PCI_OSC_UUID))) {
			/* Let OS control everything */
			Return (Arg3)
		} Else {
			/* Unrecognized UUID */
			CreateDWordField (Arg3, 0, CDW1)
			Or (CDW1, 4, CDW1)
			Return (Arg3)
		}
	}
}
