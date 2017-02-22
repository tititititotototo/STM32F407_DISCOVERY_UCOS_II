######################################
# Makefile by ST2Makefile.py
######################################

######################################
# target
######################################
TARGET = TrueSTUDIO

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0

#######################################
# pathes
#######################################
# source path
# Build path
BUILD_DIR = build

######################################
# source
######################################
C_SOURCES = \
  ../../../../../Software/uC-CPU/ARM-Cortex-M4/GNU/cpu_c.c \
  ../../../../../Software/uC-CPU/cpu_core.c \
  ../../../../../Software/uC-LIB/lib_ascii.c \
  ../../../../../Software/uC-LIB/lib_math.c \
  ../../../../../Software/uC-LIB/lib_mem.c \
  ../../../../../Software/uC-LIB/lib_str.c \
  ../../../../../Software/uC-Serial/Driver/ST/serial_drv_stm32.c \
  ../../../../../Software/uC-Serial/Line/serial_line_dflt.c \
  ../../../../../Software/uC-Serial/Line/serial_line_probe.c \
  ../../../../../Software/uC-Serial/Line/serial_line_tty.c \
  ../../../../../Software/uC-Serial/OS/uCOS-II/serial_os.c \
  ../../../../../Software/uC-Serial/Source/serial.c \
  ../../../../../Software/uC-Serial/Source/serial_buf.c \
  ../../../../../Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_c.c \
  ../../../../../Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU/os_dbg.c \
  ../../../../../Software/uCOS-II/Source/os_core.c \
  ../../../../../Software/uCOS-II/Source/os_flag.c \
  ../../../../../Software/uCOS-II/Source/os_mbox.c \
  ../../../../../Software/uCOS-II/Source/os_mem.c \
  ../../../../../Software/uCOS-II/Source/os_mutex.c \
  ../../../../../Software/uCOS-II/Source/os_q.c \
  ../../../../../Software/uCOS-II/Source/os_sem.c \
  ../../../../../Software/uCOS-II/Source/os_task.c \
  ../../../../../Software/uCOS-II/Source/os_time.c \
  ../../../../../Software/uCOS-II/Source/os_tmr.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_msp_template.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
  ../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
  ../../BSP/CMSIS/system_stm32f4xx.c \
  ../../BSP/OS/uCOS-II/bsp_os.c \
  ../../BSP/bsp.c \
  ../../BSP/UserBsp/bsp_user.c \
  ../../BSP/bsp_int.c \
  ../../BSP/bsp_periph.c \
  ../../BSP/cpu_bsp.c \
  ../../BSP/serial_bsp_stm3240x.c \
  ../UserApp/app_ansi_demo.c \
  ../app_hooks.c \
  ../app_serial.c  

ASM_SOURCES = \
  ../../../../../Software/uC-CPU/ARM-Cortex-M4/GNU/cpu_a.S \
  ../../../../../Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU/os_cpu_a.S \
  ../../BSP/TrueSTUDIO/startup.S 

#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc 
CP = arm-none-eabi-objcopy
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
SZ = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# macros for gcc
AS_DEFS = -DUSE_HAL_DRIVER -DSTM32F407xx -D__ASSEMBLY__
C_DEFS = -DUSE_HAL_DRIVER -DSTM32F407xx
# includes for gcc
AS_INCLUDES =
C_INCLUDES = -I"../"
C_INCLUDES += -I"../UserApp"
C_INCLUDES += -I"../../BSP"
C_INCLUDES += -I"../../BSP/UserBsp"
C_INCLUDES += -I"../../BSP/OS/uCOS-II"
C_INCLUDES += -I"../../../STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
C_INCLUDES += -I"../../../STM32CubeF4/Drivers/CMSIS/Include"
C_INCLUDES += -I"../../../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc"
C_INCLUDES += -I"../../../../../Software/uC-CPU"
C_INCLUDES += -I"../../../../../Software/uC-CPU/ARM-Cortex-M4/GNU"
C_INCLUDES += -I"../../../../../Software/uC-LIB"
C_INCLUDES += -I"../../../../../Software/uCOS-II/Source"
C_INCLUDES += -I"../../../../../Software/uCOS-II/Ports/ARM-Cortex-M4/Generic/GNU"
C_INCLUDES += -I"../../../../../Software/uC-Serial/Driver/ST"
C_INCLUDES += -I"../../../../../Software/uC-Serial/Line"
C_INCLUDES += -I"../../../../../Software/uC-Serial/OS"
C_INCLUDES += -I"../../../../../Software/uC-Serial/Source"
# compile gcc flags
ASFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = arm-gcc-link.ld
# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

burn:
	~/stlink/st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
	
#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES))) 

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	#$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) -o $@ $< 

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@	
	@$(NM) ${@} | grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | sort > ${@:.elf=.map} 	
	@$(OBJDUMP) -D -a -f -p -s -h ${@} > ${@:.elf=.das}	
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir -p $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
