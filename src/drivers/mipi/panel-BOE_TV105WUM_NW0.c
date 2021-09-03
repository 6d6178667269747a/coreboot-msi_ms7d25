/* SPDX-License-Identifier: GPL-2.0-only */

#include <mipi/panel.h>

struct panel_serializable_data BOE_TV105WUM_NW0 = {
	.edid = {
		.ascii_string = "TV105WUM-NW0",
		.manufacturer_name = "BOE",
		.panel_bits_per_color = 8,
		.panel_bits_per_pixel = 24,
		.mode = {
			.pixel_clock = 159916,
			.lvds_dual_channel = 0,
			.refresh = 60,
			.ha = 1200, .hbl = 164, .hso = 80, .hspw = 24,
			.va = 1920, .vbl = 34, .vso = 20, .vspw = 4,
			.phsync = '-', .pvsync = '-',
			.x_mm = 147, .y_mm = 236,
		},
	},
	.orientation = LB_FB_ORIENTATION_LEFT_UP,
	.init = {
		PANEL_DCS(0x10),
		PANEL_DELAY(34),
		PANEL_DCS(0xB0, 0x05),
		PANEL_DCS(0xB1, 0xE5),
		PANEL_DCS(0xB3, 0x52),
		PANEL_DCS(0xB0, 0x00),
		PANEL_DCS(0xB3, 0x88),
		PANEL_DCS(0xB0, 0x04),
		PANEL_DCS(0xB8, 0x00),
		PANEL_DCS(0xB0, 0x00),
		PANEL_DCS(0xB6, 0x03),
		PANEL_DCS(0xBA, 0x87),
		PANEL_DCS(0xBF, 0x1F),
		PANEL_DCS(0xC0, 0x0F),
		PANEL_DCS(0xC2, 0x0E),
		PANEL_DCS(0xC3, 0x02),
		PANEL_DCS(0xC4, 0x0A),
		PANEL_DCS(0xC5, 0x02),
		PANEL_DCS(0xB0, 0x01),
		PANEL_DCS(0xE0, 0x26),
		PANEL_DCS(0xE1, 0x26),
		PANEL_DCS(0xDC, 0x00),
		PANEL_DCS(0xDD, 0x00),
		PANEL_DCS(0xCC, 0x26),
		PANEL_DCS(0xCD, 0x26),
		PANEL_DCS(0xC8, 0x00),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xD2, 0x03),
		PANEL_DCS(0xD3, 0x03),
		PANEL_DCS(0xE6, 0x04),
		PANEL_DCS(0xE7, 0x04),
		PANEL_DCS(0xC4, 0x09),
		PANEL_DCS(0xC5, 0x09),
		PANEL_DCS(0xD8, 0x0A),
		PANEL_DCS(0xD9, 0x0A),
		PANEL_DCS(0xC2, 0x0B),
		PANEL_DCS(0xC3, 0x0B),
		PANEL_DCS(0xD6, 0x0C),
		PANEL_DCS(0xD7, 0x0C),
		PANEL_DCS(0xC0, 0x05),
		PANEL_DCS(0xC1, 0x05),
		PANEL_DCS(0xD4, 0x06),
		PANEL_DCS(0xD5, 0x06),
		PANEL_DCS(0xCA, 0x07),
		PANEL_DCS(0xCB, 0x07),
		PANEL_DCS(0xDE, 0x08),
		PANEL_DCS(0xDF, 0x08),
		PANEL_DCS(0xB0, 0x02),
		PANEL_DCS(0xC0, 0x00),
		PANEL_DCS(0xC1, 0x0F),
		PANEL_DCS(0xC2, 0x1A),
		PANEL_DCS(0xC3, 0x2B),
		PANEL_DCS(0xC4, 0x38),
		PANEL_DCS(0xC5, 0x39),
		PANEL_DCS(0xC6, 0x38),
		PANEL_DCS(0xC7, 0x38),
		PANEL_DCS(0xC8, 0x36),
		PANEL_DCS(0xC9, 0x34),
		PANEL_DCS(0xCA, 0x35),
		PANEL_DCS(0xCB, 0x36),
		PANEL_DCS(0xCC, 0x39),
		PANEL_DCS(0xCD, 0x2D),
		PANEL_DCS(0xCE, 0x2E),
		PANEL_DCS(0xCF, 0x2F),
		PANEL_DCS(0xD0, 0x07),
		PANEL_DCS(0xD2, 0x00),
		PANEL_DCS(0xD3, 0x0F),
		PANEL_DCS(0xD4, 0x1A),
		PANEL_DCS(0xD5, 0x2B),
		PANEL_DCS(0xD6, 0x38),
		PANEL_DCS(0xD7, 0x39),
		PANEL_DCS(0xD8, 0x38),
		PANEL_DCS(0xD9, 0x38),
		PANEL_DCS(0xDA, 0x36),
		PANEL_DCS(0xDB, 0x34),
		PANEL_DCS(0xDC, 0x35),
		PANEL_DCS(0xDD, 0x36),
		PANEL_DCS(0xDE, 0x39),
		PANEL_DCS(0xDF, 0x2D),
		PANEL_DCS(0xE0, 0x2E),
		PANEL_DCS(0xE1, 0x2F),
		PANEL_DCS(0xE2, 0x07),
		PANEL_DCS(0xB0, 0x03),
		PANEL_DCS(0xC8, 0x0B),
		PANEL_DCS(0xC9, 0x07),
		PANEL_DCS(0xC3, 0x00),
		PANEL_DCS(0xE7, 0x00),
		PANEL_DCS(0xC5, 0x2A),
		PANEL_DCS(0xDE, 0x2A),
		PANEL_DCS(0xCA, 0x43),
		PANEL_DCS(0xC9, 0x07),
		PANEL_DCS(0xE4, 0xC0),
		PANEL_DCS(0xE5, 0x0D),
		PANEL_DCS(0xCB, 0x00),
		PANEL_DCS(0xB0, 0x06),
		PANEL_DCS(0xB8, 0xA5),
		PANEL_DCS(0xC0, 0xA5),
		PANEL_DCS(0xC7, 0x0F),
		PANEL_DCS(0xD5, 0x32),
		PANEL_DCS(0xBC, 0x33),
		PANEL_DCS(0xB0, 0x07),
		PANEL_DCS(0xB1, 0x00),
		PANEL_DCS(0xB2, 0x04),
		PANEL_DCS(0xB3, 0x0A),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x29),
		PANEL_DCS(0xB6, 0x38),
		PANEL_DCS(0xB7, 0x5A),
		PANEL_DCS(0xB8, 0x79),
		PANEL_DCS(0xB9, 0xBF),
		PANEL_DCS(0xBA, 0x05),
		PANEL_DCS(0xBB, 0x88),
		PANEL_DCS(0xBC, 0x14),
		PANEL_DCS(0xBD, 0x18),
		PANEL_DCS(0xBE, 0x97),
		PANEL_DCS(0xBF, 0x11),
		PANEL_DCS(0xC0, 0x4B),
		PANEL_DCS(0xC1, 0x82),
		PANEL_DCS(0xC2, 0x9B),
		PANEL_DCS(0xC3, 0xB6),
		PANEL_DCS(0xC4, 0xC3),
		PANEL_DCS(0xC5, 0xD0),
		PANEL_DCS(0xC6, 0xDB),
		PANEL_DCS(0xC7, 0xE1),
		PANEL_DCS(0xC8, 0xE4),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DCS(0xB0, 0x08),
		PANEL_DCS(0xB1, 0x00),
		PANEL_DCS(0xB2, 0x03),
		PANEL_DCS(0xB3, 0x0A),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x29),
		PANEL_DCS(0xB6, 0x38),
		PANEL_DCS(0xB7, 0x5A),
		PANEL_DCS(0xB8, 0x7A),
		PANEL_DCS(0xB9, 0xC1),
		PANEL_DCS(0xBA, 0x07),
		PANEL_DCS(0xBB, 0x8B),
		PANEL_DCS(0xBC, 0x17),
		PANEL_DCS(0xBD, 0x1B),
		PANEL_DCS(0xBE, 0x99),
		PANEL_DCS(0xBF, 0x13),
		PANEL_DCS(0xC0, 0x4C),
		PANEL_DCS(0xC1, 0x84),
		PANEL_DCS(0xC2, 0x9D),
		PANEL_DCS(0xC3, 0xB7),
		PANEL_DCS(0xC4, 0xC4),
		PANEL_DCS(0xC5, 0xD0),
		PANEL_DCS(0xC6, 0xDB),
		PANEL_DCS(0xC7, 0xE1),
		PANEL_DCS(0xC8, 0xE4),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DCS(0xB0, 0x09),
		PANEL_DCS(0xB1, 0x04),
		PANEL_DCS(0xB2, 0x04),
		PANEL_DCS(0xB3, 0x09),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x2B),
		PANEL_DCS(0xB6, 0x3A),
		PANEL_DCS(0xB7, 0x5D),
		PANEL_DCS(0xB8, 0x80),
		PANEL_DCS(0xB9, 0xCA),
		PANEL_DCS(0xBA, 0x13),
		PANEL_DCS(0xBB, 0x9D),
		PANEL_DCS(0xBC, 0x30),
		PANEL_DCS(0xBD, 0x34),
		PANEL_DCS(0xBE, 0xBB),
		PANEL_DCS(0xBF, 0x30),
		PANEL_DCS(0xC0, 0x6A),
		PANEL_DCS(0xC1, 0xA1),
		PANEL_DCS(0xC2, 0xBC),
		PANEL_DCS(0xC3, 0xD4),
		PANEL_DCS(0xC4, 0xE0),
		PANEL_DCS(0xC5, 0xEB),
		PANEL_DCS(0xC6, 0xF6),
		PANEL_DCS(0xC7, 0xFA),
		PANEL_DCS(0xC8, 0xFC),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DCS(0xB0, 0x0A),
		PANEL_DCS(0xB1, 0x00),
		PANEL_DCS(0xB2, 0x04),
		PANEL_DCS(0xB3, 0x0A),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x29),
		PANEL_DCS(0xB6, 0x38),
		PANEL_DCS(0xB7, 0x5A),
		PANEL_DCS(0xB8, 0x79),
		PANEL_DCS(0xB9, 0xBF),
		PANEL_DCS(0xBA, 0x05),
		PANEL_DCS(0xBB, 0x88),
		PANEL_DCS(0xBC, 0x14),
		PANEL_DCS(0xBD, 0x18),
		PANEL_DCS(0xBE, 0x97),
		PANEL_DCS(0xBF, 0x11),
		PANEL_DCS(0xC0, 0x4B),
		PANEL_DCS(0xC1, 0x82),
		PANEL_DCS(0xC2, 0x9B),
		PANEL_DCS(0xC3, 0xB6),
		PANEL_DCS(0xC4, 0xC3),
		PANEL_DCS(0xC5, 0xD0),
		PANEL_DCS(0xC6, 0xDB),
		PANEL_DCS(0xC7, 0xE1),
		PANEL_DCS(0xC8, 0xE4),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DCS(0xB0, 0x0B),
		PANEL_DCS(0xB1, 0x00),
		PANEL_DCS(0xB2, 0x03),
		PANEL_DCS(0xB3, 0x0A),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x29),
		PANEL_DCS(0xB6, 0x38),
		PANEL_DCS(0xB7, 0x5A),
		PANEL_DCS(0xB8, 0x7A),
		PANEL_DCS(0xB9, 0xC1),
		PANEL_DCS(0xBA, 0x07),
		PANEL_DCS(0xBB, 0x8B),
		PANEL_DCS(0xBC, 0x17),
		PANEL_DCS(0xBD, 0x1B),
		PANEL_DCS(0xBE, 0x99),
		PANEL_DCS(0xBF, 0x13),
		PANEL_DCS(0xC0, 0x4C),
		PANEL_DCS(0xC1, 0x84),
		PANEL_DCS(0xC2, 0x9D),
		PANEL_DCS(0xC3, 0xB7),
		PANEL_DCS(0xC4, 0xC4),
		PANEL_DCS(0xC5, 0xD0),
		PANEL_DCS(0xC6, 0xDB),
		PANEL_DCS(0xC7, 0xE1),
		PANEL_DCS(0xC8, 0xE4),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DCS(0xB0, 0x0C),
		PANEL_DCS(0xB1, 0x04),
		PANEL_DCS(0xB2, 0x04),
		PANEL_DCS(0xB3, 0x09),
		PANEL_DCS(0xB4, 0x1A),
		PANEL_DCS(0xB5, 0x2B),
		PANEL_DCS(0xB6, 0x3A),
		PANEL_DCS(0xB7, 0x5D),
		PANEL_DCS(0xB8, 0x80),
		PANEL_DCS(0xB9, 0xCA),
		PANEL_DCS(0xBA, 0x13),
		PANEL_DCS(0xBB, 0x9D),
		PANEL_DCS(0xBC, 0x30),
		PANEL_DCS(0xBD, 0x34),
		PANEL_DCS(0xBE, 0xBB),
		PANEL_DCS(0xBF, 0x30),
		PANEL_DCS(0xC0, 0x6A),
		PANEL_DCS(0xC1, 0xA1),
		PANEL_DCS(0xC2, 0xBC),
		PANEL_DCS(0xC3, 0xD4),
		PANEL_DCS(0xC4, 0xE0),
		PANEL_DCS(0xC5, 0xEB),
		PANEL_DCS(0xC6, 0xF6),
		PANEL_DCS(0xC7, 0xFA),
		PANEL_DCS(0xC8, 0xFC),
		PANEL_DCS(0xC9, 0x00),
		PANEL_DCS(0xCA, 0x00),
		PANEL_DCS(0xCB, 0x16),
		PANEL_DCS(0xCC, 0xAF),
		PANEL_DCS(0xCD, 0xFF),
		PANEL_DCS(0xCE, 0xFF),
		PANEL_DELAY(100),
		PANEL_DCS(0xB0, 0x00),
		PANEL_DCS(0xB3, 0x08),
		PANEL_DCS(0xB0, 0x04),
		PANEL_DCS(0xB8, 0x68),
		PANEL_DELAY(10),
		PANEL_DCS(0x11),
		PANEL_DELAY(100),
		PANEL_DCS(0x29),
		PANEL_DELAY(50),
		PANEL_END,
	},
};
