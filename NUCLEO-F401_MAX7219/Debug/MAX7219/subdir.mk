################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MAX7219/MAX7219.c 

OBJS += \
./MAX7219/MAX7219.o 

C_DEPS += \
./MAX7219/MAX7219.d 


# Each subdirectory must supply rules for building sources it contributes
MAX7219/MAX7219.o: ../MAX7219/MAX7219.c MAX7219/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../MAX7219 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MAX7219/MAX7219.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

