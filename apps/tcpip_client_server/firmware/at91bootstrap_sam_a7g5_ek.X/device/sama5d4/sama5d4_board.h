/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DEV_SAMA5D4_H__
#define __DEV_SAMA5D4_H__

/*
 * PMC Setting
 *
 * The main oscillator is enabled as soon as possible in the lowlevel_clock_init
 * and MCK is switched on the main oscillator.
 */

#if defined(CONFIG_CPU_CLK_444MHZ)

/* PCK: 444M, MCK: 148M */
#define BOARD_PLLA_MULA		73

#define BOARD_PCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2))
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2 / 3))

#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		((AT91C_CKGR_MULA << 2) & (BOARD_PLLA_MULA << 18))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 1)

/* Master Clock Register */
#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_H32MXDIV_H32MXDIV2 \
					| AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_PLLA_CLK)

#define MASTER_CLOCK		148000000

#elif defined(CONFIG_CPU_CLK_510MHZ)
/* PCK: 510M, MCK: 170M */
#define BOARD_PCK		((unsigned long)((BOARD_MAINOSC * 85) / 2))
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC * 85) / 2 / 3))

#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		((AT91C_CKGR_MULA << 2) & (84 << 18))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 1)

/* Master Clock Register */
#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_H32MXDIV_H32MXDIV2 \
					| AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_PLLA_CLK)

#define MASTER_CLOCK		170000000

#elif defined(CONFIG_CPU_CLK_528MHZ)

/* PCK: 528M, MCK: 176M */
#define BOARD_PLLA_MULA		87

#define BOARD_PCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2))
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2 / 3))

#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		((AT91C_CKGR_MULA << 2) & (BOARD_PLLA_MULA << 18))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 1)

/* Master Clock Register */
#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_H32MXDIV_H32MXDIV2 \
					| AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_PLLA_CLK)

#define MASTER_CLOCK		176000000

#elif defined(CONFIG_CPU_CLK_594MHZ)

/* PCK: 594M, MCK: 148.5M */
#define BOARD_PLLA_MULA		98

#define BOARD_PCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2))
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2 / 4))

#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		((AT91C_CKGR_MULA << 2) & (BOARD_PLLA_MULA << 18))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 1)

/* Master Clock Register */
#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_4 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_H32MXDIV_H32MXDIV2 \
					| AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_4 \
					| AT91C_PMC_CSS_PLLA_CLK)

#define MASTER_CLOCK		148500000

#elif defined(CONFIG_CPU_CLK_600MHZ)

/* PCK: 600MHz, MCK: 200MHz */
#define BOARD_PLLA_MULA		99

#define BOARD_PCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2))
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC * (BOARD_PLLA_MULA + 1)) / 2 / 3))

#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		((AT91C_CKGR_MULA << 2) & (BOARD_PLLA_MULA << 18))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 1)

/* Master Clock Register */
#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_H32MXDIV_H32MXDIV2 \
					| AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_PLLA_CLK)


#define MASTER_CLOCK		200000000

#else
#error "No CLK setting defined"
#endif

#define PLLA_SETTINGS		(BOARD_CKGR_PLLA | \
				BOARD_PLLACOUNT | \
				BOARD_MULA | \
				BOARD_DIVA)

/*
 * DataFlash Settings
 */
#define CONFIG_SYS_SPI_CLOCK	AT91C_SPI_CLK
#define CONFIG_SYS_SPI_MODE	SPI_MODE3

#if defined(CONFIG_SPI)
#if CONFIG_SPI_BUS == 0
#define CONFIG_SYS_BASE_SPI	AT91C_BASE_SPI0
#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PC(3)
#elif (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PC(4)
#endif
#elif CONFIG_SPI_BUS == 1
#define CONFIG_SYS_BASE_SPI	AT91C_BASE_SPI1
#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PB(21)
#elif (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PB(22)
#endif
#else
	#error "Invalid SPI BUS was chosen"
#endif
#endif

/*
 * NandFlash Settings
 */
#define CONFIG_SYS_NAND_BASE            AT91C_BASE_CS3
#define CONFIG_SYS_NAND_MASK_ALE        (1 << 21)
#define CONFIG_SYS_NAND_MASK_CLE        (1 << 22)

#define CONFIG_SYS_NAND_OE_PIN		AT91C_PIN_PC(13)
#define CONFIG_SYS_NAND_WE_PIN		AT91C_PIN_PC(14)
#define CONFIG_SYS_NAND_ALE_PIN		AT91C_PIN_PC(17)
#define CONFIG_SYS_NAND_CLE_PIN		AT91C_PIN_PC(18)
#define CONFIG_SYS_NAND_ENABLE_PIN      AT91C_PIN_PC(15)

#define	NO_GALOIS_TABLE_IN_ROM

/*
 * MCI Settings
 */
#if defined(CONFIG_AT91_MCI0)
#define CONFIG_SYS_BASE_MCI	AT91C_BASE_HSMCI0
#elif defined(CONFIG_AT91_MCI1)
#define CONFIG_SYS_BASE_MCI	AT91C_BASE_HSMCI1
#endif

/*
 * Recovery function
 */
#define CONFIG_SYS_RECOVERY_BUTTON_PIN	AT91C_PIN_PE(13)
#define RECOVERY_BUTTON_NAME	"BP2/PB_USER1"

#endif
