#******************************************************************************
#
# Makefile - Rules for building the uart_echo example.
#
# Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
#
#******************************************************************************

#
# The base directory for TivaWare.
#
ROOT=.

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=./Micrium/Examples/ST/STM3240G-EVAL/OS2
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/OS2/UserApp
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/UserBsp
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/TrueSTUDIO
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/CMSIS
IPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/OS/uCOS-II
IPATH+=./Micrium/Examples/ST/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc
IPATH+=./Micrium/Examples/ST/STM32CubeF4/Drivers/CMSIS/Include
IPATH+=./Micrium/Examples/ST/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include
IPATH+=./Micrium/Software/uC-CPU/ARM-Cortex-M4/GNU
IPATH+=./Micrium/Software/uC-LIB/Ports/ARM-Cortex-M4/GNU
IPATH+=./Micrium/Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU
IPATH+=./Micrium/Software/uC-CPU
IPATH+=./Micrium/Software/uC-LIB
IPATH+=./Micrium/Software/uC-Serial/Line
IPATH+=./Micrium/Software/uC-Serial/OS
IPATH+=./Micrium/Software/uC-Serial/Source
IPATH+=./Micrium/Software/uC-Serial/Driver/ST
IPATH+=./Micrium/Software/uCOS-II/Source

VPATH=./Micrium/Examples/ST/STM3240G-EVAL/OS2
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/OS2/UserApp
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/UserBsp
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/OS/uCOS-II
VPATH+=./Micrium/Examples/ST/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/OS2/TrueSTUDIO
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/TrueSTUDIO
VPATH+=./Micrium/Examples/ST/STM3240G-EVAL/BSP/CMSIS
VPATH+=./Micrium/Software/uC-LIB/Ports/ARM-Cortex-M4/GNU
VPATH+=./Micrium/Software/uC-CPU/ARM-Cortex-M4/GNU
VPATH+=./Micrium/Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU
VPATH+=./Micrium/Software/uC-CPU
VPATH+=./Micrium/Software/uC-LIB
VPATH+=./Micrium/Software/uC-Serial/Line
VPATH+=./Micrium/Software/uC-Serial/OS/uCOS-II
VPATH+=./Micrium/Software/uC-Serial/Source
VPATH+=./Micrium/Software/uC-Serial/Driver/ST
VPATH+=./Micrium/Software/uCOS-II/Source

#
# The default rule, which causes the uart_echo example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/uCosII.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

install:
	openocd -f openocd.cfg -c "flash_image"
#	jlink.exe burn.txt

burn:
	~/stlink/st-flash write ./gcc/uCosII.bin 0x8000000

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the uart_echo example.
#

#OS2
#${COMPILER}/uCosII.axf: ${COMPILER}/app.o
${COMPILER}/uCosII.axf: ${COMPILER}/app_hooks.o
${COMPILER}/uCosII.axf: ${COMPILER}/app_serial.o
#${COMPILER}/uCosII.axf: ${COMPILER}/app_ansi_demo.o
${COMPILER}/uCosII.axf: ${COMPILER}/app_user_1_DelTask.o

#BSP
${COMPILER}/uCosII.axf: ${COMPILER}/system_stm32f4xx.o
${COMPILER}/uCosII.axf: ${COMPILER}/bsp_os.o
${COMPILER}/uCosII.axf: ${COMPILER}/bsp.o
${COMPILER}/uCosII.axf: ${COMPILER}/bsp_user.o
${COMPILER}/uCosII.axf: ${COMPILER}/bsp_int.o
${COMPILER}/uCosII.axf: ${COMPILER}/bsp_periph.o
${COMPILER}/uCosII.axf: ${COMPILER}/cpu_bsp.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_bsp_stm3240x.o

#uCOS-II-Ports
${COMPILER}/uCosII.axf: ${COMPILER}/os_cpu_a.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_cpu_c.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_dbg.o

#uCOS-II-Src
${COMPILER}/uCosII.axf: ${COMPILER}/os_core.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_flag.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_mem.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_mutex.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_q.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_sem.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_task.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_time.o
${COMPILER}/uCosII.axf: ${COMPILER}/os_tmr.o

# uC-CPU	

${COMPILER}/uCosII.axf: ${COMPILER}/cpu_c.o
${COMPILER}/uCosII.axf: ${COMPILER}/cpu_core.o

# uC-LIB
${COMPILER}/uCosII.axf: ${COMPILER}/lib_ascii.o
${COMPILER}/uCosII.axf: ${COMPILER}/lib_math.o
${COMPILER}/uCosII.axf: ${COMPILER}/lib_mem.o
${COMPILER}/uCosII.axf: ${COMPILER}/lib_str.o

#uC-SERIAL
${COMPILER}/uCosII.axf: ${COMPILER}/serial_drv_stm32.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_line_dflt.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_line_probe.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_line_tty.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_os.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial.o
${COMPILER}/uCosII.axf: ${COMPILER}/serial_buf.o

${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_adc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_adc_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_can.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_cec.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_cortex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_crc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_cryp.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_cryp_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dac.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dac_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dcmi.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dcmi_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dma.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dma2d.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_dma_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_eth.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_flash.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_flash_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_flash_ramfunc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_fmpi2c.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_fmpi2c_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_gpio.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_hash.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_hash_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_hcd.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_i2c.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_i2c_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_i2s.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_i2s_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_irda.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_iwdg.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_ltdc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_msp_template.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_nand.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_nor.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_pccard.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_pcd.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_pcd_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_pwr.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_pwr_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_qspi.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_rcc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_rcc_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_rng.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_rtc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_rtc_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_sai.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_sai_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_sd.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_sdram.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_smartcard.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_spdifrx.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_spi.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_sram.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_tim.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_tim_ex.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_uart.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_usart.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_hal_wwdg.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_ll_fmc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_ll_fsmc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_ll_sdmmc.o
${COMPILER}/uCosII.axf: ${COMPILER}/stm32f4xx_ll_usb.o	
${COMPILER}/uCosII.axf: ${COMPILER}/cpu_a.o
${COMPILER}/uCosII.axf: ${COMPILER}/startup.o
${COMPILER}/uCosII.axf: ${COMPILER}/lib_mem_a.o
${COMPILER}/uCosII.axf: ${COMPILER}/_sbrk.o
${COMPILER}/uCosII.axf: stm32f4_flash.ld
SCATTERgcc_uCosII=stm32f4_flash.ld
ENTRY_uCosII=Reset_Handler
CFLAGSgcc=-DSTM32F407xx -DUSE_HAL_DRIVER

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
