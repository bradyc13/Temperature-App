/*
 *   Copyright (c) 2020-2022 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#pragma once

#include <app/util/basic-types.h>
#include <controller/CHIPDeviceController.h>
#include <inipp/inipp.h>
#include <lib/support/logging/CHIPLogging.h>

class PersistentStorage : public chip::PersistentStorageDelegate
{
public:
    /**
     * name is the name of the storage to use.  If null, defaults to
     * "chip_tool_config.ini".
     *
     * directory is the directory the storage file should be placed in.  If
     * null, falls back to getenv("TMPDIR") and if that is not set falls back
     * to /tmp.
     *
     * If non-null values are provided, the memory they point to is expected to
     * outlive this object.
     */
    CHIP_ERROR Init(const char * name = nullptr, const char * directory = nullptr);

    /////////// PersistentStorageDelegate Interface /////////
    CHIP_ERROR SyncGetKeyValue(const char * key, void * buffer, uint16_t & size) override;
    CHIP_ERROR SyncSetKeyValue(const char * key, const void * value, uint16_t size) override;
    CHIP_ERROR SyncDeleteKeyValue(const char * key) override;
    bool SyncDoesKeyExist(const char * key) override;

    void DumpKeys() const;

    uint16_t GetListenPort();
    chip::Logging::LogCategory GetLoggingLevel();

    // Return the stored local node id, or the default one if nothing is stored.
    chip::NodeId GetLocalNodeId();

    // Store local node id.
    CHIP_ERROR SetLocalNodeId(chip::NodeId nodeId);

    // Return the stored local device (commissioner) CASE Authenticated Tags (CATs).
    chip::CATValues GetCommissionerCATs();

    // Store local CATs.
    CHIP_ERROR SetCommissionerCATs(const chip::CATValues & cats);

    // Clear all of the persistent storage for running session.
    CHIP_ERROR SyncClearAll();

    // Get the directory actually being used for the storage.
    const char * GetDirectory() const;

private:
    CHIP_ERROR CommitConfig(const char * directory, const char * name);
    inipp::Ini<char> mConfig;
    const char * mName;
    const char * mDirectory;
};
