/*
 * (C) Copyright 2009
 * Texas Instruments <www.ti.com>
 * Richard Woodruff <r-woodruff2@ti.com>
 *
 * X-Loader Configuation settings for 3621 Gossamer board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* serial printf facility takes about 3.5K */
#define CFG_PRINTF

/*
 * High Level Configuration Options
 */
#define CONFIG_ARMCORTEXA8       1    /* This is an ARM V7 CPU core */
#define CONFIG_OMAP              1    /* in a TI OMAP core */
#define CONFIG_OMAP36XX          1    /* which is a 36XX */
#define CONFIG_OMAP34XX          1    /* reuse 34XX */
#define CONFIG_OMAP3430          1    /* reuse 3430 */
#define CONFIG_3621GOSSAMER		1    /* for specific IEC configuration	*/
#define CONFIG_OMAP3621_MM	1

//#define CONFIG_SDRAM_MT46H64M32LF	1
#define CONFIG_SDRAM_H5MS2G22MFR	1	/* Hynix 2Gb SDRAM H5MS2G22MFR */

#include <asm/arch/cpu.h>        /* get chip and board defs */

/* uncomment it if you need timer based udelay(). it takes about 250 bytes */
#undef CFG_UDELAY

/* Control SDRAM memory test with this macro.
 * 0     - Disable memory test
 * 1     - Test with step 1 byte (most stressful test)
 * other - Test with the specified step (relaxed fast test)
 */
#define CFG_MEMTEST_STEP	0
 
/* Clock Defines */
#define V_OSCK                   26000000  /* Clock output from T2 */

#if (V_OSCK > 19200000)
#define V_SCLK                   (V_OSCK >> 1)
#else
#define V_SCLK                   V_OSCK
#endif

// configure the DDR clock to 166Mhz
#define PRCM_CLK_CFG2_332MHZ     1    /* VDD2=1.15v - 166MHz DDR */
#define PRCM_PCLK_OPP2           1    /* ARM=500MHz - VDD1=1.20v */

/* Memory type */
#define CFG_3430SDRAM_DDR        1

/* The actual register values are defined in u-boot- mem.h */
/* SDRAM Bank Allocation method */
#undef SDRC_B_R_C
#undef SDRC_B1_R_B0_C
#define SDRC_R_B_C               1

/* Boot type */

#ifdef CFG_PRINTF

#define CFG_NS16550
#define CFG_NS16550_SERIAL
#define CFG_NS16550_REG_SIZE     (-4)
#define CFG_NS16550_CLK          (48000000)	/* MHz */
#define CFG_NS16550_COM3         OMAP34XX_UART3
#define CFG_NS16550_COM1         OMAP34XX_UART1

/*
 * Select serial console configuration. UART 1 is used as UART3 is muxed
 * with USB and a GPIO already used for EPD screen
 */

#define CONFIG_SERIAL3           1    /* UART1 on board */
#define CONFIG_CONS_INDEX        1

#define CONFIG_BAUDRATE          115200
#define CFG_PBSIZE               256

#endif /* CFG_PRINTF */

/*
 * Miscellaneous configurable options
 */
#define CFG_LOADADDR             0x80008000

#undef	CFG_CLKS_IN_HZ		/* everything, incl board info, in Hz */

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE         (128*1024) /* regular stack */


/* Enable CONFIG_MMC macro if MMC boot support is required */
/* if loadb and MMC support are enabled together, the size of x-loader
   (code + data) becomes greater than 32K - the size of SRAM. So don't enable
   them together.
 */
#if !defined(START_LOADB_DOWNLOAD)
#define CONFIG_MMC		1
#endif
#if defined(CONFIG_MMC)
	#define CFG_CMD_MMC	1
	#define CFG_CMD_FAT	1
	#define CFG_CMD_MMC_RAW	1
#endif

/* eMMC is Partition as in NAND */
#if defined(CFG_CMD_MMC_RAW)
	#define EMMC_UBOOT_START 0x0080000 /* Leaving first 4 blocks for x-load*/
	#define EMMC_UBOOT_END	 0x00C0000 /* Giving a space of 2 blocks=256KB */
	#define EMMC_BLOCK_SIZE	 0x20000
#endif



#endif /* __CONFIG_H */

