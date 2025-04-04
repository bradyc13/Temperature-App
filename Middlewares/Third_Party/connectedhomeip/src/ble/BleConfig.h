/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2014-2018 Nest Labs, Inc.
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
 *    @file
 *      This file defines default compile-time configuration constants
 *      for the CHIP BleLayer, a Bluetooth Low Energy communications
 *      abstraction layer.
 *
 *      Package integrators that wish to override these values should
 *      either use preprocessor definitions or create a project-
 *      specific BleProjectConfig.h header and then assert
 *      HAVE_BLEPROJECTCONFIG_H via the package configuration tool
 *      via --with-chip-ble-project-includes=DIR where DIR is the
 *      directory that contains the header.
 *
 *  NOTE WELL: On some platforms, this header is included by C-language programs.
 *
 */

#pragma once

#if CHIP_HAVE_CONFIG_H
#include <ble/BleBuildConfig.h>
#include <platform/CHIPDeviceBuildConfig.h>
#endif

#include <system/SystemConfig.h>

/* Include a project-specific configuration file, if defined.
 *
 * An application or module that incorporates chip can define a project configuration
 * file to override standard BLE Layer configuration with application-specific values.
 * The project config file is typically located outside the Openchip source tree,
 * alongside the source code for the application.
 */
#ifdef BLE_PROJECT_CONFIG_INCLUDE
#include BLE_PROJECT_CONFIG_INCLUDE
#endif

/* Include a platform-specific configuration file, if defined.
 *
 * A platform configuration file contains overrides to standard BLE Layer configuration
 * that are specific to the platform or OS on which chip is running.  It is typically
 * provided as apart of an adaptation layer that adapts Openchip to the target
 * environment.  This adaptation layer may be included in the Openchip source tree
 * itself or implemented externally.
 */
#ifdef BLE_PLATFORM_CONFIG_INCLUDE
#include BLE_PLATFORM_CONFIG_INCLUDE
#endif

// clang-format off


/**
 *  @def BLE_LAYER_NUM_BLE_ENDPOINTS
 *
 *  @brief
 *    This defines the number of BLEEndPoint objects allocated for use by the
 *    BleLayer subsystem. Value should be defined as the minimum of (max number
 *    of simultaneous BLE connections the system supports, max number of
 *    simultaneous BLE connections the application will establish).
 */
#ifndef BLE_LAYER_NUM_BLE_ENDPOINTS
#define BLE_LAYER_NUM_BLE_ENDPOINTS 1
#endif // BLE_LAYER_NUM_BLE_ENDPOINTS

#if (BLE_LAYER_NUM_BLE_ENDPOINTS < 1)
#error "BLE_LAYER_NUM_BLE_ENDPOINTS must be greater than 0. configure options may be used to disable chip over BLE."
#endif

/**
 *  @def BLE_CONNECTION_OBJECT
 *
 *  @brief
 *    This defines the type of BLE_CONNECTION_OBJECT parameters passed between
 *    BLE platform code and the BleLayer subsystem.
 *
 *    This type must support operator == such that BLE_CONNECTION_OBJECT instances
 *    which refer to the same BLE connection are considered equivalent.
 *
 *    Most platforms should be able to retain this type's default definition as
 *    (void *), and pass [pointers to] connection handles generated by their
 *    platform interface where BLE_CONNECTION_OBJECT arguments are required by
 *    BleLayer input functions.
 *
 */
#ifndef BLE_CONNECTION_OBJECT
#define BLE_CONNECTION_OBJECT void*
#endif // BLE_CONNECTION_OBJECT

/**
 *  @def BLE_CONNECTION_UNINITIALIZED
 *
 *  @brief
 *    This defines the value of an uninitialized BLE_CONNECTION_OBJECT.
 *
 */
#ifndef BLE_CONNECTION_UNINITIALIZED
#define BLE_CONNECTION_UNINITIALIZED nullptr
#endif // BLE_CONNECTION_UNINITIALIZED

/**
 *  @def BLE_READ_REQUEST_CONTEXT
 *
 *  @brief
 *    This defines the type of BLE_READ_REQUEST_CONTEXT parameters passed between
 *    BLE platform code and the BleLayer subsystem.
 *
 *    BLE_READ_REQUEST_CONTEXT objects are handed to BleLayer when a read request
 *    is received by the BLE platform. BleLayer hands these objects back to the
 *    appropriate platform delegate function when sending the read response.
 *
 */
#ifndef BLE_READ_REQUEST_CONTEXT
#define BLE_READ_REQUEST_CONTEXT void*
#endif // BLE_READ_REQUEST_CONTEXT

/**
 *  @def BLE_MAX_RECEIVE_WINDOW_SIZE
 *
 *  @brief
 *    This is the maximum allowed size of a BLE end point's receive window, defined as the number of fragments the
 *    end point may reliably receive without BTP-layer acknowledgement. This value should be no larger than the floor
 *    of ONE-HALF the total number of slots or buffers reserved for GATT operations at any point along a platform's
 *    BLE pipeline. The BLE layer reserves all of these buffers for its own use - one half for incoming GATT writes or
 *    indications, and the other half for incoming GATT confirmations.
 *
 *    This value must be greater than 1, or race condition avoidance logic will prevent send the on remote device. This
 *    logic prevents any send with no piggybacked ack when the receiver's window has only 1 slot open. Without this
 *    logic, simultaneous data transmissions could fill both receiver's windows, leaving no room for the acks required
 *    to re-open them. Both senders would wedge, and the BTP connection would stall.
 *
 *    This value must also exceed (BLE_CONFIG_IMMEDIATE_ACK_WINDOW_THRESHOLD + 1), or ***immediate*** stand-alone
 *    acks will forever be sent without delay in response to one another as each peer's window size dips below
 *    BLE_CONFIG_IMMEDIATE_ACK_WINDOW_THRESHOLD with receipt of any single message fragment.
 *
 *    Default value of 3 is absolute minimum for stable performance, and an attempt to ensure safe window sizes on new
 *    platforms.
 *
 */
#ifndef BLE_MAX_RECEIVE_WINDOW_SIZE
#define BLE_MAX_RECEIVE_WINDOW_SIZE 6
#endif

#if (BLE_MAX_RECEIVE_WINDOW_SIZE < 3)
#error "BLE_MAX_RECEIVE_WINDOW_SIZE must be greater than 2 for BLE transport protocol stability."
#endif

/**
 *  @def BLE_CONFIG_ERROR_MIN
 *
 *  @brief
 *    This defines the base or minimum BleLayer error number range.
 *
 */
#ifndef BLE_CONFIG_ERROR_MIN
#define BLE_CONFIG_ERROR_MIN 6000
#endif // BLE_CONFIG_ERROR_MIN

/**
 *  @def BLE_CONFIG_ERROR_MAX
 *
 *  @brief
 *    This defines the top or maximum BleLayer error number range.
 *
 */
#ifndef BLE_CONFIG_ERROR_MAX
#define BLE_CONFIG_ERROR_MAX 6999
#endif // BLE_CONFIG_ERROR_MAX

/**
 *  @def BLE_CONFIG_ERROR
 *
 *  @brief
 *    This defines a mapping function for BleLayer errors that allows
 *    mapping such errors into a platform- or system-specific range.
 *
 */
#ifndef BLE_CONFIG_ERROR
#define BLE_CONFIG_ERROR(e) (BLE_CONFIG_ERROR_MIN + (e))
#endif // BLE_CONFIG_ERROR


/**
 * @def BTP_CONN_RSP_TIMEOUT_MS
 *
 * @brief
 *   Maximum amount of time, in milliseconds, after sending or receiving a BTP Session Handshake
 *   request to wait for connection establishment.
 */
#ifndef BTP_CONN_RSP_TIMEOUT_MS
#define BTP_CONN_RSP_TIMEOUT_MS 15000 // 15 seconds
#endif // BTP_CONN_RSP_TIMEOUT_MS

/**
 * @def BTP_ACK_TIMEOUT_MS
 *
 * @brief
 *   Maximum amount of time, in milliseconds, after sending a BTP packet to wait for
 *   an acknowledgement. When the ack is not received within this period the BTP session is closed.
 */
#ifndef BTP_ACK_TIMEOUT_MS
#define BTP_ACK_TIMEOUT_MS 15000 // 15 seconds
#endif // BTP_ACK_TIMEOUT_MS

// clang-format on

#include <lib/core/CHIPConfig.h>
