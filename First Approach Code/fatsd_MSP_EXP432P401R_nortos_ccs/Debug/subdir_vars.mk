################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../MSP_EXP432P401R_NoRTOS.cmd 

SYSCFG_SRCS += \
../fatsd.syscfg 

C_SRCS += \
./syscfg/ti_drivers_config.c \
../fatsd_nortos.c \
../main_nortos.c \
../mp3_funcs.c \
../player1053.c \
../spi_portb.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./syscfg/ti_drivers_config.d \
./fatsd_nortos.d \
./main_nortos.d \
./mp3_funcs.d \
./player1053.d \
./spi_portb.d 

OBJS += \
./syscfg/ti_drivers_config.obj \
./fatsd_nortos.obj \
./main_nortos.obj \
./mp3_funcs.obj \
./player1053.obj \
./spi_portb.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"syscfg\ti_drivers_config.obj" \
"fatsd_nortos.obj" \
"main_nortos.obj" \
"mp3_funcs.obj" \
"player1053.obj" \
"spi_portb.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"syscfg\ti_drivers_config.d" \
"fatsd_nortos.d" \
"main_nortos.d" \
"mp3_funcs.d" \
"player1053.d" \
"spi_portb.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

SYSCFG_SRCS__QUOTED += \
"../fatsd.syscfg" 

C_SRCS__QUOTED += \
"./syscfg/ti_drivers_config.c" \
"../fatsd_nortos.c" \
"../main_nortos.c" \
"../mp3_funcs.c" \
"../player1053.c" \
"../spi_portb.c" 


