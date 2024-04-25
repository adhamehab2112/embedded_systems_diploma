################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/KEYPAD/KEYPAD.c 

OBJS += \
./Src/HAL/KEYPAD/KEYPAD.o 

C_DEPS += \
./Src/HAL/KEYPAD/KEYPAD.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/KEYPAD/KEYPAD.o: ../Src/HAL/KEYPAD/KEYPAD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/CMSIS_V5" -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/AE_RTOS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/KEYPAD/KEYPAD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

