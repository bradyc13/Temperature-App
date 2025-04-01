/*
 *    Copyright (c) 2022 Project CHIP Authors
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

#include "WindowCovering.h"

#include "stm32_lcd.h"
#include "stm32wb5mm_dk_lcd.h"
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app/util/af.h>
#include <platform/CHIPDeviceLayer.h>

// Added for Status
#include <protocols/interaction_model/StatusCode.h>

#define DELTA 100 // 1%
using namespace ::chip::Credentials;
using namespace ::chip::DeviceLayer;
using namespace chip::app::Clusters::WindowCovering;

// Added for Status
using chip::Protocols::InteractionModel::Status;


static constexpr uint32_t sMoveTimeoutMs{ 200 };

WindowCovering::WindowCovering()
{

}


chip::Percent100ths WindowCovering::CalculateSingleStep(MoveType aMoveType)
{
    Status status;
	chip::Percent100ths percent100ths{};
    NPercent100ths current{};
    OperationalState opState{};

    if (aMoveType == MoveType::LIFT)
    {
        status  = Attributes::CurrentPositionLiftPercent100ths::Get(Endpoint(), current);
        opState = OperationalStateGet(Endpoint(), OperationalStatus::kLift);
    }
    else if (aMoveType == MoveType::TILT)
    {
        status  = Attributes::CurrentPositionTiltPercent100ths::Get(Endpoint(), current);
        opState = OperationalStateGet(Endpoint(), OperationalStatus::kTilt);
    }
    if ((status == Status::Success) && !current.IsNull())
    {

        percent100ths = ComputePercent100thsStep(opState, current.Value(), 5*DELTA);
    }
    else
    {
    }

    return percent100ths;
}

bool WindowCovering::TargetCompleted(MoveType aMoveType, NPercent100ths aCurrent, NPercent100ths aTarget)
{
    return (OperationalState::Stall == ComputeOperationalState(aTarget, aCurrent));
}

void WindowCovering::StartTimer(MoveType aMoveType, uint32_t aTimeoutMs)
{
    MoveType * moveType = chip::Platform::New<MoveType>();
    VerifyOrReturn(moveType != nullptr);

    *moveType = aMoveType;
	(void) chip::DeviceLayer::SystemLayer().StartTimer(chip::System::Clock::Milliseconds32(aTimeoutMs), MoveTimerTimeoutCallback,
                                                       reinterpret_cast<void *>(moveType));
}

void WindowCovering::MoveTimerTimeoutCallback(chip::System::Layer * systemLayer, void * appState)
{
    MoveType * moveType = reinterpret_cast<MoveType *>(appState);
    VerifyOrReturn(moveType != nullptr);
    if (*moveType == MoveType::LIFT)
    {
        chip::DeviceLayer::PlatformMgr().ScheduleWork(WindowCovering::DriveCurrentLiftPosition);
    }
    else if (*moveType == MoveType::TILT)
    {
        chip::DeviceLayer::PlatformMgr().ScheduleWork(WindowCovering::DriveCurrentTiltPosition);
    }

    chip::Platform::Delete(moveType);
}


void WindowCovering::DriveCurrentTiltPosition(intptr_t)
{
    NPercent100ths current{};
    NPercent100ths target{};
    NPercent100ths positionToSet{};

    VerifyOrReturn(Attributes::CurrentPositionTiltPercent100ths::Get(Endpoint(), current) == Status::Success);
    VerifyOrReturn(Attributes::TargetPositionTiltPercent100ths::Get(Endpoint(), target) == Status::Success);
    OperationalState state = ComputeOperationalState(target, current);
    UpdateOperationalStatus(MoveType::TILT, state);

    chip::Percent100ths position = CalculateSingleStep(MoveType::TILT);

    if (state == OperationalState::MovingUpOrOpen)
    {
        positionToSet.SetNonNull(position > target.Value() ? position : target.Value());
    }
    else if (state == OperationalState::MovingDownOrClose)
    {
        positionToSet.SetNonNull(position < target.Value() ? position : target.Value());
    }
    else
    {
        positionToSet.SetNonNull(current.Value());
    }

    TiltPositionSet(Endpoint(), positionToSet);

    // assume single move completed
    Instance().mInTiltMove = false;

    VerifyOrReturn(Attributes::CurrentPositionTiltPercent100ths::Get(Endpoint(), current) == Status::Success);
    if (!TargetCompleted(MoveType::TILT, current, target))
    {
        // continue to move
        ChipLogDetail(Zcl, "Window covering cluster Tilt position set to %u %%",((WC_PERCENT100THS_MAX_CLOSED -current.Value())/100));

        StartTimer(MoveType::TILT, sMoveTimeoutMs);
    }
    else
    {
        // the OperationalStatus should indicate no-tilt-movement after the target is completed
        UpdateOperationalStatus(MoveType::TILT, ComputeOperationalState(target, current));
        ChipLogDetail(Zcl, "Window covering cluster  DriveCurrentTiltPosition finish ");

    }
}

//Stall             = 0x00, // currently not moving
//MovingUpOrOpen    = 0x01, // is currently opening
//MovingDownOrClose = 0x02, // is currently closing
//Reserved          = 0x03, // don't use


void WindowCovering::DriveCurrentLiftPosition(intptr_t)
{
    NPercent100ths current{};
    NPercent100ths target{};
    NPercent100ths positionToSet{};

    VerifyOrReturn(Attributes::CurrentPositionLiftPercent100ths::Get(Endpoint(), current) == Status::Success);
    VerifyOrReturn(Attributes::TargetPositionLiftPercent100ths::Get(Endpoint(), target) == Status::Success);
    OperationalState state = ComputeOperationalState(target, current);
    UpdateOperationalStatus(MoveType::LIFT, state);

    chip::Percent100ths position = CalculateSingleStep(MoveType::LIFT);

    if (state == OperationalState::MovingUpOrOpen)
    {
        positionToSet.SetNonNull(position > target.Value() ? position : target.Value());
    }
    else if (state == OperationalState::MovingDownOrClose)
    {
        positionToSet.SetNonNull(position < target.Value() ? position : target.Value());
    }
    else
    {
        positionToSet.SetNonNull(current.Value());
    }

    LiftPositionSet(Endpoint(), positionToSet);

    // assume single move completed
    Instance().mInLiftMove = false;

    VerifyOrReturn(Attributes::CurrentPositionLiftPercent100ths::Get(Endpoint(), current) == Status::Success);
    if (!TargetCompleted(MoveType::LIFT, current, target))
    {
    	uint8_t buff_str[32]= {0};
        ChipLogDetail(Zcl, "Window covering cluster Lift position set to %u %%",((WC_PERCENT100THS_MAX_CLOSED -current.Value())/100));
    	if(ComputeOperationalState(target, current) == chip::app::Clusters::WindowCovering::OperationalState::MovingUpOrOpen )
    	{
			sprintf((char*)buff_str,"Lift OPEN %u %%",((WC_PERCENT100THS_MAX_CLOSED -current.Value())/100));
#if (OTA_SUPPORT == 0)
			UTIL_LCD_DisplayStringAt(0,LINE(2),buff_str,LEFT_MODE);
			BSP_LCD_Refresh(0);
#endif
    	}
    	else
    	{
    		sprintf((char*)buff_str,"Lift CLOSE %u %%",((WC_PERCENT100THS_MAX_CLOSED -current.Value())/100));
#if (OTA_SUPPORT == 0)
			UTIL_LCD_DisplayStringAt(0,LINE(2),buff_str,LEFT_MODE);
			BSP_LCD_Refresh(0);
#endif
    	}

        StartTimer(MoveType::LIFT, sMoveTimeoutMs);
    }
    else
    {
        // the OperationalStatus should indicate no-lift-movement after the target is completed
        UpdateOperationalStatus(MoveType::LIFT, ComputeOperationalState(target, current));
        ChipLogDetail(Zcl, "Window covering cluster  DriveCurrentLiftPosition finish ");
#if (OTA_SUPPORT == 0)
		UTIL_LCD_DisplayStringAt(0,LINE(2),(uint8_t*)"Lift Finish      ",LEFT_MODE);
		BSP_LCD_Refresh(0);
#endif
    }
}

void WindowCovering::StartMove(MoveType aMoveType)
{
    switch (aMoveType)
    {
    case MoveType::LIFT:
        if (!mInLiftMove)
        {
            mInLiftMove = true;
            StartTimer(aMoveType, sMoveTimeoutMs);
        }
        break;
    case MoveType::TILT:
        if (!mInTiltMove)
        {
            mInTiltMove = true;
            StartTimer(aMoveType, sMoveTimeoutMs);
        }
        break;
    default:
        break;
    };
}

void WindowCovering::SetSingleStepTarget(OperationalState aDirection)
{
    UpdateOperationalStatus(mCurrentUIMoveType, aDirection);
    SetTargetPosition(aDirection, CalculateSingleStep(mCurrentUIMoveType));
}

void WindowCovering::UpdateOperationalStatus(MoveType aMoveType, OperationalState aDirection)
{
    switch (aMoveType)
    {
    case MoveType::LIFT:
        OperationalStateSet(Endpoint(), OperationalStatus::kLift, aDirection);
        break;
    case MoveType::TILT:
        OperationalStateSet(Endpoint(), OperationalStatus::kTilt, aDirection);
        break;
    case MoveType::NONE:
        break;
    default:
        break;
    }
}

void WindowCovering::SetTargetPosition(OperationalState aDirection, chip::Percent100ths aPosition)
{
    //EmberAfStatus status{};
    Status status;
	if (Instance().mCurrentUIMoveType == MoveType::LIFT)
    {
        status = Attributes::TargetPositionLiftPercent100ths::Set(Endpoint(), aPosition);
    }
    else if (Instance().mCurrentUIMoveType == MoveType::TILT)
    {
        status = Attributes::TargetPositionTiltPercent100ths::Set(Endpoint(), aPosition);
    }
	if (status != Status::Success)
	{
    }
}


void WindowCovering::SchedulePostAttributeChange(chip::EndpointId aEndpoint, chip::AttributeId aAttributeId)
{
    AttributeUpdateData * data = chip::Platform::New<AttributeUpdateData>();
    VerifyOrReturn(data != nullptr);

    data->mEndpoint    = aEndpoint;
    data->mAttributeId = aAttributeId;

    chip::DeviceLayer::PlatformMgr().ScheduleWork(DoPostAttributeChange, reinterpret_cast<intptr_t>(data));
}

void WindowCovering::DoPostAttributeChange(intptr_t aArg)
{
    AttributeUpdateData * data = reinterpret_cast<AttributeUpdateData *>(aArg);
    VerifyOrReturn(data != nullptr);

    PostAttributeChange(data->mEndpoint, data->mAttributeId);
    chip::Platform::Delete(data);
}
