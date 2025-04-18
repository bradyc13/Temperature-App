/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

#pragma once

#include <inttypes.h>
#include <stddef.h>

namespace chip {

/// A very basic single-linked list
template <typename T>
struct SingleLinkedListNode
{
    T mValue;
    SingleLinkedListNode * mpNext = nullptr;

    size_t Count() const
    {
        size_t ret = 0;
        for (auto p = this; p != nullptr; p = p->mpNext)
        {
            ret++;
        }
        return ret;
    }
};

} // namespace chip
