################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/MCAL/USART/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/I2C/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/KEYPAD/subdir.mk
-include Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Arm_course.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Arm_course.list \

OBJCOPY_BIN += \
Arm_course.bin \


# All Target
all: Arm_course.elf secondary-outputs

# Tool invocations
Arm_course.elf: $(OBJS) $(USER_OBJS) C:\Users\adham\STM32CubeIDE\workspace_1.4.0\Arm_course\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Arm_course.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\adham\STM32CubeIDE\workspace_1.4.0\Arm_course\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Arm_course.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	arm-none-eabi-objdump -D Arm_course.axf > Arm_course.s
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Arm_course.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Arm_course.list"
	@echo 'Finished building: $@'
	@echo ' '

Arm_course.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Arm_course.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
