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
#pragma once

// Cluster masks modify how clusters are used by the framework
//
// Does this cluster have init function?
#define CLUSTER_MASK_INIT_FUNCTION (0x01)
// Does this cluster have attribute changed function?
#define CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION (0x02)
// Bits 0x04 and 0x08 are free.
// Does this cluster have shutdown function?
#define CLUSTER_MASK_SHUTDOWN_FUNCTION (0x10)
// Does this cluster have pre-attribute changed function?
#define CLUSTER_MASK_PRE_ATTRIBUTE_CHANGED_FUNCTION (0x20)
// Cluster is a server
#define CLUSTER_MASK_SERVER (0x40)
// Cluster is a client
#define CLUSTER_MASK_CLIENT (0x80)
