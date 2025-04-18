/**
 *
 *    Copyright (c) 2023 Project CHIP Authors
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
/****************************************************************************
 * @file
 * @brief Routines for the Content App Observer plugin, the
 *server implementation of the Content App Observer cluster.
 *******************************************************************************
 ******************************************************************************/

#pragma once

#include "content-app-observer-delegate.h"
#include <app-common/zap-generated/cluster-objects.h>

namespace chip {
namespace app {
namespace Clusters {
namespace ContentAppObserver {

void SetDefaultDelegate(EndpointId endpoint, Delegate * delegate);

} // namespace ContentAppObserver
} // namespace Clusters
} // namespace app
} // namespace chip
