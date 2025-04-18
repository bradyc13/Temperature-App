/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include <app-common/zap-generated/callback.h>
#include <app/util/basic-types.h>
#include <lib/support/Span.h>
#include <protocols/interaction_model/Constants.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace chip;

// This file contains overridable callbacks that are not cluster specific.

bool __attribute__((weak)) emberAfAttributeReadAccessCallback(EndpointId endpoint, ClusterId clusterId, AttributeId attributeId)
{
    return true;
}

bool __attribute__((weak)) emberAfAttributeWriteAccessCallback(EndpointId endpoint, ClusterId clusterId, AttributeId attributeId)
{
    return true;
}

chip::Protocols::InteractionModel::Status __attribute__((weak))
emberAfExternalAttributeReadCallback(EndpointId endpoint, ClusterId clusterId, const EmberAfAttributeMetadata * attributeMetadata,
                                     uint8_t * buffer, uint16_t maxReadLength)
{
    return chip::Protocols::InteractionModel::Status::Failure;
}

chip::Protocols::InteractionModel::Status __attribute__((weak))
emberAfExternalAttributeWriteCallback(EndpointId endpoint, ClusterId clusterId, const EmberAfAttributeMetadata * attributeMetadata,
                                      uint8_t * buffer)
{
    return chip::Protocols::InteractionModel::Status::Failure;
}

chip::Protocols::InteractionModel::Status __attribute__((weak))
MatterPreAttributeChangeCallback(const chip::app::ConcreteAttributePath & attributePath, uint8_t type, uint16_t size,
                                 uint8_t * value)
{
    return chip::Protocols::InteractionModel::Status::Success;
}

void __attribute__((weak)) MatterPostAttributeChangeCallback(const chip::app::ConcreteAttributePath & attributePath, uint8_t type,
                                                             uint16_t size, uint8_t * value)
{}
