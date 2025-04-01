****
  @page Window_App
  @verbatim
  ******************************************************************************
  * @file    Matter/Window_App
  * @author  MCD Application Team
  * @brief   This file lists the modification done by STMicroelectronics on
  *          Matter for integration with STM32Cube solution.
  ******************************************************************************
  *
  * Copyright (c) 2019-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim



Window_App example is based on Matter and behaves as a Matter accessory communicating over a 802.15.4 Thread network.
It can be commissioned into an existing Matter Fabric and can interact with other devices within this Fabric.
The STM32WB5MM-DK board running Window-app application is capable 
of BLE and OpenThread activity at the same time.

See Wiki articles (https://wiki.st.com/stm32mcu/wiki/Category:Matter) to demonstrate the features.

@par Keywords

THREAD,BLE,Matter

@par Directory contents 

 
  Using Matter v1.3 SDK.
  
  - Matter/Window-App/STM32_WPAN/App/app_ble.h            Header for app_ble.c module
  - Matter/Window-App/Core/Core/Inc/app_common.h          Header for all modules with common definition
  - Matter/Window-App/Core/Core/Inc/app_conf.h            Parameters configuration file of the application
  - Matter/Window-App/Core/Core/Inc/app_entry.h           Parameters configuration file of the application
  - Matter/Window-App/STM32_WPAN/App/app_thread.h         Header for app_thread.c module
  - Matter/Window-App/STM32_WPAN/App/ble_conf.h           BLE Services configuration
  - Matter/Window-App/STM32_WPAN/App/ble_dbg_conf.h       BLE Traces configuration of the BLE services
  - Matter/Window-App/Core/Core/Inc/hw_conf.h             Configuration file of the HW
  - Matter/Window-App/Core/Inc/main.h                     Header for main.c module
  - Matter/Window-App/STM32_WPAN/App/p2p_server_app.h     Header for BLE P2P Server application
  - Matter/Window-App/Core/Inc/stm32wbxx_hal_conf.h       HAL configuration file
  - Matter/Window-App/Core/Inc/stm32wbxx_it.h             Interrupt handlers header file
  - Matter/Window-App/STM32_WPAN/App/app_ble.c            BLE Profile implementation
  - Matter/Window-App/STM32_WPAN/App/app_matter.c         Matter Profile implementation
  - Matter/Window-App/STM32_WPAN/app/app_thread.c         Thread application implementation
  - Matter/Window-App/STM32_WPAN/Target/hw_ipcc.c         IPCC Driver
  - Matter/Window-App/Core/Src/app_entry.cpp              Initialization of the application
  - Matter/Window-App/Core/Core/Src/stm32_lpm_if.c        Low Power Manager Interface
  - Matter/Window-App/Core/Core/Src/hw_timerserver.c      Timer Server based on RTC
  - Matter/Window-App/Core/Core/Src/hw_uart.c             UART Driver
  - Matter/Window-App/Core/Src/app_main.cpp               Main program
  - Matter/Window-App/STM32_WPAN/App/p2p_server_app.c     BLE P2P Server application implementation
  - Matter/Window-App/Core/Src/stm32wbxx_it.c             Interrupt handlers
  - Matter/Window-App/Core/Src/system_stm32wbxx.c         stm32wbxx system source file
  - Matter/Window-App/Core/Src/AppTask.cpp                Entry application source file for matter 
  - Matter/Window-App/Core/Src/ZclCallbacks.cpp           Cluster output source file for Matter 
  - Matter/Window-App/Core/Src/WindowCovering.cpp         Window Cluster callback handler
  - Matter/Window-App/Core/Src/freertos_port.c            Custom porting of FreeRTOS functionalities
  - Matter/Window-App/Core/Src/entropy_hardware_poll.c    Custom porting of entropy with MbedTLS
  - Matter/Window-App/Core/Inc/FreeRTOSConfig.h           FreeRTOS specific defines
  - Matter/Window-App/Core/Inc/mbedtls_user_config.h      MbedTLS specific defines
  - Matter/Window-App/Core/Inc/CHIPProjectConfig.h        Matter specific defines
  - Matter/Window-App/Core/Inc/AppEvent.h                 Window App event handler
  - Matter/Window-App/Core/Inc/AppTask.h                  Header for AppTask.cpp module
  
 
@par Hardware and Software environment

  - This example has been tested with an STMicroelectronics STM32WB5MM-DK board 
    

@par How to use it ? 

This application requests having the stm32wb5x_BLE_Thread_light_dynamic_fw.bin binary flashed on the Wireless Coprocessor.
If it is not the case, you need to use STM32CubeProgrammer to load the appropriate binary.
All available binaries are located under /Projects/STM32_Copro_Wireless_Binaries directory.
Refer to UM2237 to learn how to use/install STM32CubeProgrammer.
Refer to /Projects/STM32_Copro_Wireless_Binaries/ReleaseNote.html for the detailed procedure to load the proper
Wireless Coprocessor binary. 


Minimum requirements for the demo:
- 1 STM32WB5MM-DK board with Window-App firmware.
- 1 OTBR (Raspberry Pi or MP135 + Nucleo RCP)
- 1 Smartphone (Android) with "CHIPTool" Phone Application (available Utilities/APK/app-debug-v_1_1.zip) or chiptool on OTBR


In order to make the program work, you must do the following: 
 - Connect STM32WB5MM-DK boards to your PC 
 - Open STM32CubdeIDE
 - Rebuild all files and load your image into target memory
 - Run the example
 
To get the traces in real time, you can connect an HyperTerminal to the STLink Virtual Com Port. 
    
 For the the traces, the UART must be configured as follows:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits 
    - Stop Bit = 1 bit
    - Parity = none
    - Flow control = none

**** START DEMO ****
1st boot the End Device must be commissioned (BLE then Thread)
Then other boot, only Thread is needed

**** LCD SUMMARY ****
LCD Mapping :
 - The LCD screen displays "BLE connected" when the BLE rendezvous started.
 - The LCD screen displays "Network Joined" when the board joined a thread network.
 - The LCD screen displays the opening pourcentage of the windows or the finish status
 - The LCD screen displays: "Fabric Created": if commissioning success.
                            "Fabric Failed" : if commissioning failed.
                            "Fabric Found"  : if the credentials from the non-volatile memory(NVM)
                                              have been found 
****  BUTTON SUMMARY ****
Button Mapping:

- Button 1:
   Press the button for at least 10 seconds to trigger a factory reset.
   Press the button (short press) to save persistent data in non-volatile memory before resetting or removing power supply of the board.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 


 
	   
