/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

Scope(\_GPE) {	/* Start Scope GPE */

	/*  Legacy PM event  */
	Method(_L08) {
		/* DBGO("\\_GPE\\_L08\n") */
	}

	/*  Temp warning (TWarn) event  */
	Method(_L09) {
		/* DBGO("\\_GPE\\_L09\n") */
		/* Notify (\_TZ.TZ00, 0x80) */
	}

	/*  USB controller PME#  */
	Method(_L0B) {
		Store("USB PME", Debug)
		/* Notify devices of wake event */
		Notify(\_SB.PCI0.UOH1, 0x02)
		Notify(\_SB.PCI0.UOH2, 0x02)
		Notify(\_SB.PCI0.UOH3, 0x02)
		Notify(\_SB.PCI0.UOH4, 0x02)
		Notify(\_SB.PCI0.XHC0, 0x02)
		Notify(\_SB.PCI0.UEH1, 0x02)
		Notify(\_SB.PWRB, 0x02)
	}

	/*  ExtEvent0 SCI event  */
	Method(_L10) {
		/* DBGO("\\_GPE\\_L10\n") */
	}


	/*  ExtEvent1 SCI event  */
	Method(_L11) {
		/* DBGO("\\_GPE\\_L11\n") */
	}

	/* Lid switch opened or closed */
	Method(_L16) {
		Store("Lid status changed", Debug)
		/* Flip trigger polarity */
		Not(LPOL, LPOL)
		/* Notify lid object of status change */
		Notify(\_SB.LID, 0x80)
	}

	/*  GPIO0 or GEvent8 event  */
	Method(_L18) {
		Store("PCI bridge wake event", Debug)
		/* Notify PCI bridges of wake event */
		Notify(\_SB.PCI0.PBR4, 0x02)
		Notify(\_SB.PCI0.PBR5, 0x02)
	}

	/*  Azalia SCI event  */
	Method(_L1B) {
		/* DBGO("\\_GPE\\_L1B\n") */
		Notify(\_SB.PCI0.AZHD, 0x02) /* NOTIFY_DEVICE_WAKE */
		Notify(\_SB.PWRB, 0x02) /* NOTIFY_DEVICE_WAKE */
	}
}	/* End Scope GPE */
