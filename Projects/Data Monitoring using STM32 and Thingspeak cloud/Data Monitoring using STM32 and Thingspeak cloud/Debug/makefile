################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Data Monitoring using STM32 and Thingspeak cloud
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.elf \

MAP_FILES += \
Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.list \


# All Target
all: main-build

# Main-build Target
main-build: Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.elf secondary-outputs

# Tool invocations
Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.elf Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.map: $(OBJS) $(USER_OBJS) C:\Users\pragn\OneDrive\Desktop\GitHub\ARM_Cortex_M4\Projects\Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud\Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Data Monitoring using STM32 and Thingspeak cloud.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pragn\OneDrive\Desktop\GitHub\ARM_Cortex_M4\Projects\Data Monitoring using STM32 and Thingspeak cloud\Data Monitoring using STM32 and Thingspeak cloud\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Data Monitoring using STM32 and Thingspeak cloud.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Data Monitoring using STM32 and Thingspeak cloud.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.elf Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.list Data\ Monitoring\ using\ STM32\ and\ Thingspeak\ cloud.map Data\\ Monitoring\\ using\\ STM32\\ and\\ Thingspeak\\ cloud.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
