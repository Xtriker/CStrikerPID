################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicaciones/app_Debounce.c \
../Aplicaciones/app_Delay.c \
../Aplicaciones/app_DigitalDimmer.c \
../Aplicaciones/app_MAX7219.c \
../Aplicaciones/pid_controller.c 

OBJS += \
./Aplicaciones/app_Debounce.o \
./Aplicaciones/app_Delay.o \
./Aplicaciones/app_DigitalDimmer.o \
./Aplicaciones/app_MAX7219.o \
./Aplicaciones/pid_controller.o 

C_DEPS += \
./Aplicaciones/app_Debounce.d \
./Aplicaciones/app_Delay.d \
./Aplicaciones/app_DigitalDimmer.d \
./Aplicaciones/app_MAX7219.d \
./Aplicaciones/pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicaciones/app_Debounce.o: ../Aplicaciones/app_Debounce.c Aplicaciones/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Aplicaciones/app_Debounce.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Aplicaciones/app_Delay.o: ../Aplicaciones/app_Delay.c Aplicaciones/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Aplicaciones/app_Delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Aplicaciones/app_DigitalDimmer.o: ../Aplicaciones/app_DigitalDimmer.c Aplicaciones/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Aplicaciones/app_DigitalDimmer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Aplicaciones/app_MAX7219.o: ../Aplicaciones/app_MAX7219.c Aplicaciones/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Aplicaciones/app_MAX7219.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Aplicaciones/pid_controller.o: ../Aplicaciones/pid_controller.c Aplicaciones/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Aplicaciones/pid_controller.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

