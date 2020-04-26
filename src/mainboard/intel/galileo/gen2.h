/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

/* PCIe reset pin */
#define GEN2_PCI_RESET_RESUMEWELL_GPIO		0

static const struct reg_script gen2_gpio_init[] = {
	/* Initialize the legacy GPIO controller */
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGEN_CORE_WELL, 0x03),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGIO_CORE_WELL, 0x03),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGLVL_CORE_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGTPE_CORE_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGTNE_CORE_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGGPE_CORE_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGSMI_CORE_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CGTS_CORE_WELL, 0x03),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_CNMIEN_CORE_WELL, 0x00),

	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGEN_RESUME_WELL, 0x3f),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGIO_RESUME_WELL, 0x1c),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGLVL_RESUME_WELL, 0x02),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGTPE_RESUME_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGTNE_RESUME_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGGPE_RESUME_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGSMI_RESUME_WELL, 0x00),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RGTS_RESUME_WELL, 0x3f),
	REG_LEG_GPIO_WRITE(R_QNC_GPIO_RNMIEN_RESUME_WELL, 0x00),

	/* Initialize the GPIO controller */
	REG_GPIO_WRITE(GPIO_INTEN, 0),
	REG_GPIO_WRITE(GPIO_INTSTATUS, 0),
	REG_GPIO_WRITE(GPIO_SWPORTA_DR, 5),
	REG_GPIO_WRITE(GPIO_SWPORTA_DDR, 5),
	REG_GPIO_WRITE(GPIO_INTMASK, 0),
	REG_GPIO_WRITE(GPIO_INTTYPE_LEVEL, 0),
	REG_GPIO_WRITE(GPIO_INT_POLARITY, 0),
	REG_GPIO_WRITE(GPIO_DEBOUNCE, 0),
	REG_GPIO_WRITE(GPIO_LS_SYNC, 0),

	REG_SCRIPT_END
};

static const struct reg_script gen2_hsuart0[] = {
	/* Route UART0_TXD to MUX7_Y -> BUF_IO1 -> IO1 -> DIGITAL 1
	 * Set MUX7_SEL (EXP1.P1_5) high
	 * Configure MUX7_SEL (EXP1.P1_5) as an output
	 * Set LVL_B_OE6_N (EXP0.P1_4) low
	 * Configure LVL_B_OE6_N (EXP0.P1_4) as an output
	 */
	REG_I2C_OR(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_OUTPUT1, BIT5),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_CONFIG1, ~BIT5),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP0, GEN2_GPIO_EXP_OUTPUT1, ~BIT4),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP0, GEN2_GPIO_EXP_CONFIG1, ~BIT4),

	/* Route DIGITAL 0 -> IO0 -> UART0_RXD
	 * Set LVL_C_OE0_N (EXP1.P0_0) high
	 * Configure LVL_C_OE0_N (EXP1.P0_0) as an output
	 */
	REG_I2C_OR(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_OUTPUT0, BIT0),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_CONFIG0, ~BIT0),

	REG_SCRIPT_END
};

static const struct reg_script gen2_i2c_init[] = {
	/* Route I2C to Arduino Shield connector:
	 * Set AMUX1_IN (EXP2.P1_4) low
	 * Configure AMUX1_IN (EXP2.P1_4) as an output
	 *
	 *	I2C_SDA -> ANALOG_A4
	 *	I2C_SCL -> ANALOG_A5
	 */
	REG_I2C_AND(GEN2_I2C_GPIO_EXP2, GEN2_GPIO_EXP_OUTPUT1, ~BIT4),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP2, GEN2_GPIO_EXP_CONFIG1, ~BIT4),

	/* Set all GPIO expander pins connected to the Reset Button as inputs
	 * Configure Reset Button(EXP1.P1_7) as an input
	 * Disable pullup on Reset Button(EXP1.P1_7)
	 * Configure Reset Button(EXP2.P1_7) as an input
	 * Disable pullup on Reset Button(EXP2.P1_7)
	 */
	REG_I2C_OR(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_CONFIG1, BIT7),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_PULL_UP_DOWN_EN1, ~BIT7),
	REG_I2C_OR(GEN2_I2C_GPIO_EXP2, GEN2_GPIO_EXP_CONFIG1, BIT7),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP2, GEN2_GPIO_EXP_PULL_UP_DOWN_EN1, ~BIT7),

	REG_SCRIPT_END
};

static const struct reg_script gen2_tpm_reset[] = {
	/* Reset the TPM using SW_RESET_N_SHLD (EXP1 P1.7):
	 * low, output, delay, input
	 */
	REG_I2C_AND(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_OUTPUT1, ~BIT7),
	REG_I2C_AND(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_CONFIG1, ~BIT7),
	TIME_DELAY_USEC(5),
	REG_I2C_OR(GEN2_I2C_GPIO_EXP1, GEN2_GPIO_EXP_CONFIG1, BIT7),

	REG_SCRIPT_END
};
