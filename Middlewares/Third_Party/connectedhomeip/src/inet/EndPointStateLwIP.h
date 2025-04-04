/*
 *
 *    Copyright (c) 2020-2021 Project CHIP Authors
 *    Copyright (c) 2015-2017 Nest Labs, Inc.
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

/**
 *  Shared state for LwIP implementations of TCPEndPoint and UDPEndPoint.
 */

#pragma once

#include <functional>

#include <inet/EndPointBasis.h>
#include <inet/IPAddress.h>

struct udp_pcb;
struct tcp_pcb;

namespace chip {
namespace Inet {

/**
 * Definitions shared by all LwIP EndPoint classes.
 */
class DLL_EXPORT EndPointStateLwIP
{
protected:
    EndPointStateLwIP() : mLwIPEndPointType(LwIPEndPointType::Unknown) {}

    enum class LwIPEndPointType : uint8_t
    {
        Unknown = 0,
        UDP     = 1,
        TCP     = 2
    } mLwIPEndPointType;

    // Synchronously runs a function within the TCPIP task's context.
    static void RunOnTCPIP(std::function<void()>);
    static err_t RunOnTCPIPRet(std::function<err_t()>);
};

} // namespace Inet
} // namespace chip
