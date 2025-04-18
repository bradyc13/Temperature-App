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
#include <lib/dnssd/minimal_mdns/core/QNameString.h>

namespace mdns {
namespace Minimal {

QNameString::QNameString(const mdns::Minimal::FullQName & name)
{
    for (unsigned i = 0; i < name.nameCount; i++)
    {
        if (i != 0)
        {
            mBuffer.Add(".");
        }
        mBuffer.Add(name.names[i]);
    }
}

QNameString::QNameString(mdns::Minimal::SerializedQNameIterator name)
{
    bool first = true;
    while (name.Next())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            mBuffer.Add(".");
        }
        mBuffer.Add(name.Value());
    }
    if (!name.IsValid())
    {
        mBuffer.Add("(!INVALID!)");
    }
}

} // namespace Minimal
} // namespace mdns
