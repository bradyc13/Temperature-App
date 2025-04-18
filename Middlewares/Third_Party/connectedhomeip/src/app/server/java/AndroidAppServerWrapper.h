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
#include <app/server/AppDelegate.h>
#include <jni.h>
#include <lib/core/CHIPError.h>

CHIP_ERROR ChipAndroidAppInit(AppDelegate * appDelegate = nullptr);

void ChipAndroidAppShutdown(void);

void ChipAndroidAppReset(void);

jint AndroidAppServerJNI_OnLoad(JavaVM * jvm, void * reserved);

void AndroidAppServerJNI_OnUnload(JavaVM * jvm, void * reserved);
