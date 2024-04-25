################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AE_RTOS/AE_RTOS_FIFO.c \
../AE_RTOS/CortexMx_Os_Porting.c \
../AE_RTOS/Scheduler.c 

OBJS += \
./AE_RTOS/AE_RTOS_FIFO.o \
./AE_RTOS/CortexMx_Os_Porting.o \
./AE_RTOS/Scheduler.o 

C_DEPS += \
./AE_RTOS/AE_RTOS_FIFO.d \
./AE_RTOS/CortexMx_Os_Porting.d \
./AE_RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
AE_RTOS/AE_RTOS_FIFO.o: ../AE_RTOS/AE_RTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/CMSIS_V5" -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/AE_RTOS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AE_RTOS/AE_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
AE_RTOS/CortexMx_Os_Porting.o: ../AE_RTOS/CortexMx_Os_Porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/CMSIS_V5" -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/AE_RTOS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AE_RTOS/CortexMx_Os_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
AE_RTOS/Scheduler.o: ../AE_RTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/CMSIS_V5" -I"C:/Users/adham/STM32CubeIDE/workspace_1.4.0/Arm_course/AE_RTOS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"AE_RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

