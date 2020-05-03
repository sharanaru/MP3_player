################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1137939375:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1137939375-inproc

build-1137939375-inproc: ../fatsd.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs910/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_msp432p4_sdk_3_30_00_13/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1137939375 ../fatsd.syscfg
syscfg/ti_drivers_config.h: build-1137939375
syscfg/syscfg_c.rov.xs: build-1137939375
syscfg/: build-1137939375

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs" --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/nortos" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/nortos/posix" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --advice:power=none --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs" --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs/Debug" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/source" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/nortos" --include_path="C:/ti/simplelink_msp432p4_sdk_3_30_00_13/kernel/nortos/posix" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --advice:power=none --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/shara/workspace_v9/fatsd_MSP_EXP432P401R_nortos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


