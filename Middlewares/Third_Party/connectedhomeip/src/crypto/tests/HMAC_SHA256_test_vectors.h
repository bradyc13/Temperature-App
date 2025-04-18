/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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
 * @file - This file contains HMAC SHA256 test vectors.
 *
 * See https://tools.ietf.org/html/rfc4231#section-4.7
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct hmac_sha256_vector
{
    const uint8_t * key;
    const size_t key_length;
    const uint8_t * message;
    const size_t message_length;
    const uint8_t * output_hash;
    const size_t output_hash_length;
} hmac_sha256_vector;

// Common Test case messages
const uint8_t kHmacTestCase1Message[] = {
    0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c, 0x61, 0x72, 0x67, 0x65, 0x72, 0x20,
    0x54, 0x68, 0x61, 0x6e, 0x20, 0x42, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a, 0x65, 0x20, 0x4b, 0x65,
    0x79, 0x20, 0x2d, 0x20, 0x48, 0x61, 0x73, 0x68, 0x20, 0x4b, 0x65, 0x79, 0x20, 0x46, 0x69, 0x72, 0x73, 0x74,
};

// Basic test case
const uint8_t kHmacRawKeyTestCase1Key[] = {
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
};

const uint8_t kHmacRawKeyTestCase1Expected[] = {
    0x60, 0xe4, 0x31, 0x59, 0x1e, 0xe0, 0xb6, 0x7f, 0x0d, 0x8a, 0x26, 0xaa, 0xcb, 0xf5, 0xb7, 0x7f,
    0x8e, 0x0b, 0xc6, 0x21, 0x37, 0x28, 0xc5, 0x14, 0x05, 0x46, 0x04, 0x0f, 0x0e, 0xe3, 0x7f, 0x54,
};

hmac_sha256_vector kHmacSha256TestCase1 = { .key                = kHmacRawKeyTestCase1Key,
                                            .key_length         = sizeof(kHmacRawKeyTestCase1Key),
                                            .message            = kHmacTestCase1Message,
                                            .message_length     = sizeof(kHmacTestCase1Message),
                                            .output_hash        = kHmacRawKeyTestCase1Expected,
                                            .output_hash_length = sizeof(kHmacRawKeyTestCase1Expected) };

hmac_sha256_vector hmac_sha256_test_vectors_raw_key[] = { kHmacSha256TestCase1 };

// KeyHandle Test Case - Symmetric 128 Bits key
const uint8_t kHmacKeyHandleTestCase1Key[] = { 0xba, 0xba, 0xba, 0xba, 0xba, 0xba, 0xba, 0xba,
                                               0xba, 0xba, 0xba, 0xba, 0xba, 0xba, 0xba, 0xba };

const uint8_t kHmacKeyHandleTestCase1Expected[] = { 0xc0, 0xcd, 0x77, 0x23, 0xdc, 0xf1, 0x57, 0xa5, 0xfe, 0x53, 0xc5,
                                                    0x6b, 0x2d, 0x86, 0xd4, 0x1c, 0x78, 0x61, 0xb4, 0x20, 0x67, 0xca,
                                                    0x7c, 0xae, 0x44, 0x13, 0x57, 0x4d, 0x25, 0xda, 0x84, 0x1e };

hmac_sha256_vector kHmacKeyHandleSha256TestCase1 = { .key                = kHmacKeyHandleTestCase1Key,
                                                     .key_length         = sizeof(kHmacKeyHandleTestCase1Key),
                                                     .message            = kHmacTestCase1Message,
                                                     .message_length     = sizeof(kHmacTestCase1Message),
                                                     .output_hash        = kHmacKeyHandleTestCase1Expected,
                                                     .output_hash_length = sizeof(kHmacKeyHandleTestCase1Expected) };

hmac_sha256_vector hmac_sha256_test_vectors_key_handle[] = { kHmacKeyHandleSha256TestCase1 };
