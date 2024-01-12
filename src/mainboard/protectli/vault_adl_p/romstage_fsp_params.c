/* SPDX-License-Identifier: GPL-2.0-only */

#include <fsp/api.h>
#include <soc/romstage.h>
#include <soc/meminit.h>

#include "gpio.h"

static const struct mb_cfg ddr5_mem_config = {
	.type = MEM_TYPE_DDR5,

	.ect = true, /* Early Command Training */

	.UserBd = BOARD_TYPE_ULT_ULX,

	.LpDdrDqDqsReTraining = 1,

	.ddr_config = {
		.dq_pins_interleaved = true,
	},
};

static const struct mem_spd dimm_module_spd_info = {
	.topo = MEM_TOPO_DIMM_MODULE,
	.smbus = {
		[0] = {
			.addr_dimm[0] = 0x50,
		},
		[1] = {
			.addr_dimm[0] = 0x52,
		},
	},
};

void mainboard_memory_init_params(FSPM_UPD *memupd)
{

	memcfg_init(memupd, &ddr5_mem_config, &dimm_module_spd_info, false);

	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}
