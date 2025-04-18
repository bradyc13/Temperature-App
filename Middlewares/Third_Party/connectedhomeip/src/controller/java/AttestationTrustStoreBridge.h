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
#include <credentials/attestation_verifier/DeviceAttestationVerifier.h>
#include <lib/support/JniReferences.h>
#include <lib/support/Span.h>

class AttestationTrustStoreBridge : public chip::Credentials::AttestationTrustStore
{
public:
    AttestationTrustStoreBridge(chip::JniGlobalReference && attestationTrustStoreDelegate) :
        mAttestationTrustStoreDelegate(std::move(attestationTrustStoreDelegate))
    {}

    CHIP_ERROR GetProductAttestationAuthorityCert(const chip::ByteSpan & skid,
                                                  chip::MutableByteSpan & outPaaDerBuffer) const override;

protected:
    chip::JniGlobalReference mAttestationTrustStoreDelegate;

    CHIP_ERROR GetPaaCertFromJava(const chip::ByteSpan & skid, chip::MutableByteSpan & outPaaDerBuffer) const;
};
