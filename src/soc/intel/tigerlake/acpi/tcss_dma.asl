/* SPDX-License-Identifier: GPL-2.0-or-later */

OperationRegion (DPME, SystemMemory, BASE(_ADR), 0x100)
Field (DPME, AnyAcc, NoLock, Preserve)
{
	VDID, 32,
	Offset(0x84),   /* 0x84, DMA CFG PM CAP */
	PMST, 2,        /* 1:0, PM_STATE */
	, 6,
	PMEE, 1,        /* 8, PME_EN */
	, 6,
	PMES, 1,        /* 15, PME_STATUS */
	Offset(0xC8),   /* 0xC8, TBT NVM FW Revision */
	,     31,
	INFR,  1,       /* TBT NVM FW Ready */
	Offset(0xEC),   /* 0xEC, TBT TO PCIE Register */
	TB2P, 32,       /* TBT to PCIe */
	P2TB, 32,       /* PCIe to TBT */
	Offset(0xFC),   /* 0xFC, DMA RTD3 Force Power */
	DD3E, 1,        /* 0:0 DMA RTD3 Enable */
	DFPE, 1,        /* 1:1 DMA Force Power */
	, 22,
	DMAD, 8         /* 31:24 DMA Active Delay */
}

Name (STAT, 0x1)  /* Variable to save power state 1 - D0, 0 - D3C */

Method (_S0W, 0x0)
{
	If (S0IX == 1) {
		Return (0x04)
	} Else {
		Return (0x03)
	}
}

If (S0IX == 1) {
	Method (_PR0)
	{
		If (DUID == 0) {
			Return (Package() { \_SB.PCI0.D3C, \_SB.PCI0.TBT0 })
		} Else {
			Return (Package() { \_SB.PCI0.D3C, \_SB.PCI0.TBT1 })
		}
	}

	Method (_PR3)
	{

		If (DUID == 0) {
			Return (Package() { \_SB.PCI0.D3C, \_SB.PCI0.TBT0 })
		} Else {
			Return (Package() { \_SB.PCI0.D3C, \_SB.PCI0.TBT1 })
		}
	}
}

/*
 * RTD3 Exit Method to bring TBT controller out of RTD3 mode.
 */
Method (D3CX, 0, Serialized)
{
	DD3E = 0x00	/* Disable DMA RTD3 */
	STAT = 0x01
}

/*
 * RTD3 Entry method to enable TBT controller RTD3 mode.
 */
Method (D3CE, 0, Serialized)
{
	DD3E = 0x01	/* Enable DMA RTD3 */
	STAT = 0x00
}

/*
 * Variable to skip TCSS/TBT D3 cold; 1+: Skip D3CE, 0 - Enable D3CE
 * TCSS D3 Cold and TBT RTD3 is only available when system power state is in S0.
 */
Name (SD3C, 0)

/* Connect-Topology cmd can be sent or not 1 - yes, 0 - no */
Name (ALCT, 0)

/* Wait Connect-Topology cmd done:
 * 2 - wait in progress,
 * 1 - need to waie,
 * 0 - no need to wait
 */
Name (WACT, 0)

Method (_PS0, 0, Serialized)
{
	If (WACT == 1) {
		WACT = 2 /* Indicate other thread's _PS0 to wait the response */
		WFCC (5000) /* Wait for command complete */
		WACT = 0
	} ElseIf (WACT == 2) {
		While (WACT != 0) {
			Sleep (5)
		}
	}
}

Method (_PS3, 0, Serialized)
{
}

Method (_DSW, 3)
{
	/* If entering Sx (Arg1 > 1), need to skip TCSS D3Cold & TBT RTD3/D3Cold. */
	SD3C = Arg1
}

Method (_PRW, 0)
{
	Return (Package() { 0x6D, 4 })
}

Method (_DSM, 4, Serialized) {  // _DSM: Device-Specific Method
	/*
	 * _DSM Definition for TBT DMA functions
	 * Arguments:
	 * Arg0: UUID: 197DB5E0-F095-4F33-B915-71DD70833E55
	 * Arg1: Revision ID: 1
	 * Arg2: Function Index: 0, 1
	 * Arg3: Additional Inputs Bits[31:0] Arg3 {Byte0, Byte1, Byte2, Byte3}
	 */
	If (Arg0 == ToUUID("197DB5E0-F095-4F33-B915-71DD70833E55")) { // TBT DMA
		Switch (ToInteger (Arg2))
		{
			Case (0) {
				/*
				 * Function Index: 0
				 * Standard query - A bitmask of functions supported
				 *
				 * Return: A bitmask of functions supported
				 */
				If (Arg1 == 1) {
					Return (Buffer() {0x07}) /* Functions 1 and 2 supported for revision 1 */
				}
				Else {
					Return (Buffer() {0x01}) /* revisions higher than 1 are not supported */
				}
			}
			Case (1) {
				/*
				 * Function Index: 1
				 * Standard query - A bitmask of ITBT PCIe RootPort supported
				 *
				 * Return: A bitmask of ITBT PCIe RootPort supported
				 *         below is the PCIe RP map
				 *         00b: both ports disabled
				 *         01b: first port is enable
				 *         10b: second port is enabled
				 *         11b: both ports enabled.
				 */
				Local0 = Buffer (1) { 0 }
				CreateBitField(Local0, 0, PCP0)
				CreateBitField(Local0, 1, PCP1)
				If (DUID == 0) {
					If (\_SB.PCI0.TRE0 == 1) {
						PCP0 = 1
					}
					If (\_SB.PCI0.TRE1 == 1) {
						PCP1 = 1
					}
				} Else {
					If (\_SB.PCI0.TRE2 == 1) {
						PCP0 = 1
					}
					If (\_SB.PCI0.TRE3 == 1) {
						PCP1 = 1
					}
				}

				Return (Local0)
			}
			Case (2) {
				/*
				 * Function Index: 2
				 * Standard query - A bitmask of ITBT DMA capability information
				 *
				 * Return: A bitmask of ITBT DMA capability information
				 *         Bit0: IMR_VALID
				 *         Bit1: WAKE_SUPPORTED
				 *         Bit2: vPro_Dock Supported
				 */
				Local0 = Buffer (1) { 0 }
				CreateBitField(Local0, 0, IMRV)
				CreateBitField(Local0, 1, WAKE)
				CreateBitField(Local0, 2, TVDS)
				If (ITIM) {
					IMRV = 1
				}
				WAKE = 1 /* Depends on VccSt setting, not changed by coreboot */
				TVDS = 0 /* no vPro dock supported */

				Return (Local0)
			}
		}
	}
	Return (Buffer() {0})
}
