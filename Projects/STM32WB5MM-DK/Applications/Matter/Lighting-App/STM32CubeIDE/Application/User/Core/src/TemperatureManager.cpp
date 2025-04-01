/*
 * TemperatureManager.cpp
 *
 *  Created on: Feb 25, 2025
 *      Author: brady
 */

/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include "stdio.h"
#include <stdint.h>
#include "TemperatureManager.h"
#include <lib/support/logging/CHIPLogging.h>
#include "BMP280.h"

// default initialization value for the light level after start
constexpr uint8_t kDefaultLevel_Temp = 20;
TemperatureManager TemperatureManager::sTemp;

CHIP_ERROR TemperatureManager::Init() {

    mState = kState_Off;
    mLevel = kDefaultLevel_Temp;
	uint8_t control_configuration = 0xB3;
	uint8_t config_Setting = 0xA8;
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDRESS_L, resetRegister, I2C_MEMADD_SIZE_8BIT, &datatowrite, 1, 1000);
   ret = HAL_I2C_IsDeviceReady(&hi2c1,((Device_Address)<<1)+0 ,1,500 );
   //Configurate the Sensor
   ret = HAL_I2C_Mem_Write(&hi2c1, ((Device_Address)<<1)+0,Control_Config_Number, I2C_MEMADD_SIZE_8BIT, &control_configuration, 1, 500);
   ret = HAL_I2C_Mem_Write(&hi2c1,((Device_Address)<<1)+0,Configuration_Register_Number, I2C_MEMADD_SIZE_8BIT, &config_Setting, 1, 500);
   // read in the calibration data
   read_calibration_data();

    return CHIP_NO_ERROR;
}

bool TemperatureManager::IsTurnedOn() {
    return mState == kState_On;
}

uint8_t TemperatureManager::GetLevel() {
	// Use the I2C with sensor to read in the value and store in here
	int32_t raw_ADC_Data_Temp = read_ADC_T();
	float final_temperature_value = compensate_temperature(raw_ADC_Data_Temp);
    return final_temperature_value;
}

void TemperatureManager::SetCallbacks(LightingCallback_fn aActionInitiated_CB,
        LightingCallback_fn aActionCompleted_CB) {
    mActionInitiated_CB = aActionInitiated_CB;
    mActionCompleted_CB = aActionCompleted_CB;
}
// InitiateAction might not be needed for BMP 280?
//Not needed for BMP 280 as we are not turning on and off the LED
/*
bool LightingManager::InitiateAction(Action_t aAction, int32_t aActor, uint16_t size,
        uint8_t *value) {
    bool action_initiated = false;
    State_t new_state = kState_Off;

    switch (aAction) {
    case ON_ACTION:
        ChipLogProgress(NotSpecified, "LightMgr:ON: %s->ON", mState == kState_On ? "ON" : "OFF")
        ;
        break;
    case OFF_ACTION:
        ChipLogProgress(NotSpecified, "LightMgr:OFF: %s->OFF", mState == kState_On ? "ON" : "OFF")
        ;
        break;
    case LEVEL_ACTION:
        ChipLogProgress(NotSpecified, "LightMgr:LEVEL: lev:%u->%u", mLevel, *value)
        ;
        break;
    default:
        ChipLogProgress(NotSpecified, "LightMgr:Unknown")
        ;
        break;
    }

    // Initiate On/Off Action only when the previous one is complete.
    //aAction is the current state of the LED
    if (mState =kState_Off&& aAction== ON_Action){
    	action_initiate = true;
    	new_state = kState_On;
    }
    /*if (mState == kState_Off && aAction == ON_ACTION) {
        action_initiated = true;
        new_state = kState_On;
    } else if (mState == kState_On && aAction == OFF_ACTION) {
        action_initiated = true;
        new_state = kState_Off;
    } else if (aAction == LEVEL_ACTION && *value != mLevel) {
        action_initiated = true;
        if (*value == 0) {
            new_state = kState_Off;
        } else {
            new_state = kState_On;
        }
    }
    if (aAction == LEVEL_ACTION) {
        SetLevel(*value);
    } else {
        Set(new_state == kState_On);
    }
    if (action_initiated) {
        if (mActionInitiated_CB) {
            mActionInitiated_CB(aAction);
        }

        if (mActionCompleted_CB) {
            mActionCompleted_CB(aAction);
        }
    }

    return action_initiated;
}
*/
void LightingManager::SetLevel(uint8_t aLevel) {
    mLevel = aLevel;

    UpdateLight();
}

void LightingManager::Set(bool aOn) {
    if (aOn) {
        mState = kState_On;
    } else {
        mState = kState_Off;
    }
    UpdateLight();
}

void LightingManager::UpdateLight() {
}



