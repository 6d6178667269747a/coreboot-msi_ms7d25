/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

Field(ERAM, ByteAcc, NoLock, Preserve)
{
		Offset (0x06),
			SNDS, 8		/* Write to this register to generate sound */

}

Method(BEEP, 1, NotSerialized)
{
	Store (Arg0, SNDS)
}
