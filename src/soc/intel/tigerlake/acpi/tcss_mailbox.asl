/* SPDX-License-Identifier: GPL-2.0-or-later */

#define PCIE2TBT_CONNECT_TOPOLOGY_COMMAND           0x3E //(0x1F << 1)

/* ITBT MailBox Command Method */
Method(ITMB, 1, Serialized) {
	P2TB = Arg0 | 1
}


/* Wait For Command Completed */
Method(WFCC, 1, Serialized) {
	WTBS (Arg0)
	P2TB = 0
	WTBC (Arg0)
}

/* Wait For Command Set */
Method(WTBS, 1, Serialized) {
	Local0 = Arg0
	While (Local0 > 0) {
		If (TB2P & 1) {
			Break
		}
		Local0--
		Sleep (1)
	}
}

/* Wait For Command Clear */
Method(WTBC, 1, Serialized) {
	Local0 = Arg0
	While (Local0 > 0) {
		If ((TB2P & 1) != 1) {
			Break
		}
		Local0--
		Sleep (1)
	}
}


/* TCSS ITBT CONNECT_TOPOLOGY MailBox Command Method */
Method(CNTP, 0, Serialized) {
	Local0 = 0
	/* Set Force Power if it is not set. */
	If (DFPE == 0) {
		DMAD = 0x22
		DFPE = 1
		/*
		 * Poll the ITBT NVM FW Ready bit with timeout (default
		 *  is 500ms) before send the TBT MailBox command.
		 */
		While ((INFR == 0) && (Local0 < 500)) {
			Sleep (1)
			Local0++
		}
	}
	If (Local0 != 500) {
		ITMB (PCIE2TBT_CONNECT_TOPOLOGY_COMMAND)
	}
}