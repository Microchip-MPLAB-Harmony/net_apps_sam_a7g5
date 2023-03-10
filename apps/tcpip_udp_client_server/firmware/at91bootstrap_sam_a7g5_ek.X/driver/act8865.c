// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "hardware.h"
#include "board.h"
#include "twi.h"
#include "act8865.h"
#include "debug.h"

/*
 * ACT8865 Device Slave Address
 */
#define ACT8865_ADDR	0x5B

static unsigned int act8865_get_twi_bus(void)
{
	return CONFIG_PMIC_ON_TWI;
}

static int act8865_read(unsigned char reg_addr, unsigned char *data)
{
	unsigned int bus;
	int ret;

	bus = act8865_get_twi_bus();

	ret = twi_read(bus, ACT8865_ADDR, reg_addr, 1, data, 1);
	if (ret)
		return -1;

	return 0;
}

static int act8865_write(unsigned char reg_addr, unsigned char data)
{
	unsigned int bus;
	int ret;

	bus = act8865_get_twi_bus();

	ret = twi_write(bus, ACT8865_ADDR, reg_addr, 1, &data, 1);
	if (ret)
		return -1;

	return 0;
}

int act8865_set_reg_voltage(unsigned char volt_reg, unsigned char value)
{
	unsigned char enable_reg;
	unsigned char data;
	int ret;

	switch (volt_reg) {
	case REG1_0:
	case REG1_1:
		enable_reg = REG1_2;
		break;
	case REG2_0:
	case REG2_1:
		enable_reg = REG2_2;
		break;
	case REG3_0:
	case REG3_1:
		enable_reg = REG3_2;
		break;
	case REG4_0:
		enable_reg = REG4_1;
		break;
	case REG5_0:
		enable_reg = REG5_1;
		break;
	case REG6_0:
		enable_reg = REG6_1;
		break;
	case REG7_0:
		enable_reg = REG7_1;
		break;
	default:
		return -1;
	}

	/* Set output voltage */
	ret = act8865_write(volt_reg, value);
	if (ret)
		return -1;

	if ((enable_reg == REG1_2) || (enable_reg == REG2_2) ||
	    (enable_reg == REG3_2))
		return 0;

	/* Enable Regulator */
	data = 0;
	ret = act8865_read(enable_reg, &data);
	if (ret)
		return -1;

	data |= REG_ENABLE_BIT;
	ret = act8865_write(enable_reg, data);
	if (ret)
		return -1;

	return 0;
}

int act8865_check_i2c_disabled(void)
{
	unsigned char data = 0;

	return act8865_read(SYS_0, &data);
}

#ifdef CONFIG_ACT8865_POWER_SAVING
static int act8865_set_reg_mode(unsigned char mode_reg, unsigned mode)
{
	unsigned char value;
	int ret;

	value = 0;
	ret = act8865_read(mode_reg, &value);
	if (ret)
		return -1;

	value &= ~REG_MODE_BIT;
	value |= (mode == ACT8865_MODE_FIX_FREQ) ? REG_MODE_FIX_FREQ : 0;

	ret = act8865_write(mode_reg, value);
	if (ret)
		return -1;

	return 0;
}

int act8865_set_power_saving_mode(void)
{
	unsigned char mode = ACT8865_MODE_POWER_SAVING;
	unsigned char reg_list[] = {REG1_2, REG2_2, REG3_2};
	unsigned char reg;
	unsigned i;
	int ret;

	if (act8865_check_i2c_disabled())
		return 0;

	for (i = 0; i < ARRAY_SIZE(reg_list); i++) {
		reg = reg_list[i];
		ret = act8865_set_reg_mode(reg, mode);
		if (ret)
			console_printf("ACT8865: Failed to set Power-saving mode\n");
	}

	console_printf("ACT8865: Set REG1/REG2/REG3 Power-saving mode\n");

	return 0;
}
#endif

/*--------------------- ACT8865 Workaround -----------------------*/

#if defined(CONFIG_DISABLE_ACT8865_I2C)
/*
 * Special Registers
 */
#define REGS_0B		0x0b
#define REGS_02		0x02
#define REGS_03		0x03

enum version_id {
	ACT8865_VERSION_303,
	ACT8865_VERSION_304,
	ACT8865_VERSION_305
};

static struct {
	enum version_id	ver_id;
	unsigned char	set_value;
} version_array[] = {{ACT8865_VERSION_303, 0xE9},
				{ACT8865_VERSION_304, 0xEE},
				{ACT8865_VERSION_305, 0xEF} };

/*
 * About this workaround, for cases where ACT8865 I2C lines are already shared
 * with some other components, ACT8865 features a function to allow user to
 * disable its interface to avoid conflicts. please see
 * Section ERRATA INFO, Workaround of the ACT8865 datasheet Rev 4
 */
static int act8865_disable_i2c_sequence(unsigned char data)
{
	int ret;

	ret = act8865_write(REGS_0B, data);
	if (ret)
		return -1;

	data = 0x07;
	ret = act8865_write(REGS_02, data);
	if (ret)
		return -1;

	data = 0x01;
	ret = act8865_write(REGS_03, data);
	if (ret)
		return -1;

	return 0;
}

static int act8865_workaround_disable_i2c(void)
{
	unsigned char value;
	unsigned char i;

	/* Check ACT8865 I2C interface */
	if (act8865_check_i2c_disabled())
		return 0;

	/* Disable ACT8865 I2C interface */
	for (i = 0; i < ARRAY_SIZE(version_array); i++) {
		value = version_array[i].set_value;
		act8865_disable_i2c_sequence(value);
		if (act8865_check_i2c_disabled())
			break;
	}

	if (i >= ARRAY_SIZE(version_array)) {
		console_printf("ACT8865: Failed to disable I2C interface\n");
		return -1;
	}

	console_printf("ACT8865: Disable ACT8865's I2C interface\n");

	return 0;
}
#endif

#if defined(CONFIG_ACT8865)
void act8865_workaround(void)
{
	if (!twi_init_done)
		twi_init();

#if defined(CONFIG_ACT8865_SET_VOLTAGE)
	/* Set ACT8865 REG output voltage */
	at91_board_act8865_set_reg_voltage();
#endif

#if defined(CONFIG_DISABLE_ACT8865_I2C)
	/* Disable ACT8865 I2C interface, if failed, don't go on */
	if (act8865_workaround_disable_i2c()) {
		console_printf("ACT8865: Failed to disable I2C interface\n");
		while (1)
			;
	}
#endif
}
#endif

/**
 * ACT8945A Charger Registers Map
 */
/* 0x70: Reserved */
#define ACT8945A_APCH_CFG		0x71
#define ACT8945A_APCH_STATUS		0x78
#define ACT8945A_APCH_CTRL		0x79
#define ACT8945A_APCH_STATE		0x7A

/* ACT8945A_APCH_CFG */
#define APCH_CFG_OVPSET			(0x3 << 0)
#define APCH_CFG_PRETIMO		(0x3 << 2)
#define APCH_CFG_TOTTIMO		(0x3 << 4)
#define APCH_CFG_SUSCHG			(0x1 << 7)

/* ACT8945A_APCH_STATE */
#define APCH_STATE_ACINSTAT		(0x1 << 1)
#define APCH_STATE_CSTATE		(0x3 << 4)
#define APCH_STATE_CSTATE_SHIFT		4
#define APCH_STATE_CSTATE_DISABLED	0x00
#define APCH_STATE_CSTATE_EOC		0x01
#define APCH_STATE_CSTATE_FAST		0x02
#define APCH_STATE_CSTATE_PRE		0x03

#ifdef CONFIG_SUSPEND_ACT8945A_CHARGER
int act8945a_suspend_charger(void)
{
	unsigned char data;
	int ret;

	if (!twi_init_done)
		twi_init();

	ret = act8865_read(ACT8945A_APCH_CFG, &data);
	if (ret)
		return -1;

	data |= APCH_CFG_SUSCHG;
	ret = act8865_write(ACT8945A_APCH_CFG, data);
	if (ret)
		return -1;

	ret = act8865_read(ACT8945A_APCH_STATE, &data);
	if (ret)
		return -1;

	if ((data & APCH_STATE_CSTATE) != APCH_STATE_CSTATE_DISABLED) {
		console_printf("ACT8945A: Failed to suspend charger\n");
		return -1;
	}

	return 0;
}
#else
int act8945a_suspend_charger(void)
{
	return 0;
}
#endif

#if defined(CONFIG_ACT8865_SET_VOLTAGE)
struct act8865_tbl {
	unsigned char reg;
	unsigned int voltage;
};
static const struct act8865_tbl act8865_vol[] = {
	{0x14, 1100}, {0x18, 1200}, {0x19, 1250}, {0x1a, 1300}, {0x1b, 1350},
	{0x24, 1800}, {0x31, 2500}, {0x39, 3300},
};

#if CONFIG_ACT8865_VSEL == 0
static const struct act8865_tbl act8865_outs[] = {
	{REG1_0, CONFIG_VOLTAGE_OUT1},
	{REG2_0, CONFIG_VOLTAGE_OUT2},
	{REG3_0, CONFIG_VOLTAGE_OUT3},
	{REG4_0, CONFIG_VOLTAGE_OUT4},
	{REG5_0, CONFIG_VOLTAGE_OUT5},
	{REG6_0, CONFIG_VOLTAGE_OUT6},
	{REG7_0, CONFIG_VOLTAGE_OUT7},
};
#endif

#if CONFIG_ACT8865_VSEL == 1
static const struct act8865_tbl act8865_outs[] = {
	{REG1_1, CONFIG_VOLTAGE_OUT1},
	{REG2_1, CONFIG_VOLTAGE_OUT2},
	{REG3_1, CONFIG_VOLTAGE_OUT3},
	{REG4_0, CONFIG_VOLTAGE_OUT4},
	{REG5_0, CONFIG_VOLTAGE_OUT5},
	{REG6_0, CONFIG_VOLTAGE_OUT6},
	{REG7_0, CONFIG_VOLTAGE_OUT7},
};
#endif

int at91_board_act8865_set_reg_voltage(void)
{
	int i, j;
	int ret = 0;

	/* Check ACT8865 I2C interface */
	if (act8865_check_i2c_disabled())
		return 0;

	for (i = ARRAY_SIZE(act8865_outs) - 1; i >= 0; i--) {
		if (act8865_outs[i].voltage == 0)
			continue;

		ret = -1;
		for (j = 0; j < ARRAY_SIZE(act8865_vol); j++) {
			if (act8865_vol[j].voltage == act8865_outs[i].voltage) {
				ret = act8865_set_reg_voltage(act8865_outs[i].reg, act8865_vol[j].reg);
				break;
			}
		}
		if (ret)
			console_printf("ACT8865: Failed to make REG%d output %dmV\n", i + 1, act8865_outs[i].voltage);
	}

	return ret;
}
#endif
