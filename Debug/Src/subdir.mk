################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/usart.c 

OBJS += \
./Src/dma.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/usart.o 

C_DEPS += \
./Src/dma.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Inc" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Drivers/CMSIS/Include" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/TP-moje dokumenty/Programowanie/ST/sw_workspace/freertosdisco/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


