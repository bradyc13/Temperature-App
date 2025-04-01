################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/brady/Downloads/STM32CubeExpansion_MATTER_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

C_DEPS += \
./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 

OBJS += \
./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o: /Users/brady/Downloads/STM32CubeExpansion_MATTER_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DCHIP_PLATFORM_CONFIG_INCLUDE=<CHIPPlatformConfig.h>' '-DCHIP_PROJECT_CONFIG_INCLUDE=<CHIPProjectConfig.h>' '-DMBEDTLS_CONFIG_FILE=<matter_config.h>' -DCHIP_HAVE_CONFIG_H -DUSE_HAL_DRIVER '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_matter.h>' -DCORE_CM4 -DTHREAD_WB -DDEBUG -DSTM32WB55xx -DUSE_STM32WB5M_DK -c -I../../Core/Inc -I../../Codegen/ -I../../STM32_WPAN/App -I../../STM32_WPAN/Target -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/thread/openthread/stack/include/openthread -I../../../../../../../Middlewares/ST/STM32_WPAN/thread/openthread/stack/src/core -I../../../../../../../Middlewares/ST/STM32_WPAN/thread/openthread/stack/src/core/config -I../../../../../../../Middlewares/ST/STM32_WPAN/thread/openthread/stack/include -I../../../../../../../Middlewares/ST/STM32_WPAN/thread/openthread/core/openthread_api -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Drivers/BSP/STM32WB5MM-DK -I../../../../../../../Drivers/BSP/Components/s25fl128s -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../Drivers/BSP/Components/ssd1315 -I../../../../../../../Utilities/Fonts -I../../../../../../../Utilities/LCD -I../../../../../../../Middlewares/Third_Party/mbedtls/library -I../../../../../../../Middlewares/Third_Party/mbedtls/include -I../../../../../../../Middlewares/Third_Party/connectedhomeip/src/platform/stm32 -I../../../../../../../Middlewares/Third_Party/connectedhomeip/src/platform -Os -ffunction-sections -fdata-sections -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-Middlewares-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

