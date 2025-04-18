/*
 *   Copyright (c) 2024 Project CHIP Authors
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
package matter.controller

import matter.controller.model.AttributePath
import matter.controller.model.Status

/** An interface for receiving write response. */
interface WriteAttributesCallback {
  /**
   * OnError will be called when an error occurs after failing to write
   *
   * @param attributePath The attribute path field
   * @param Exception The IllegalStateException which encapsulated the error message, the possible
   *   chip error could be CHIP_ERROR_TIMEOUT: A response was not received within the expected
   *   response timeout. - CHIP_ERROR_*TLV*: A malformed, non-compliant response was received from
   *   the server. - CHIP_ERROR encapsulating the converted error from the StatusIB: If we got a
   *   non-path-specific status response from the server. CHIP_ERROR*: All other cases.
   */
  fun onError(attributePath: AttributePath?, ex: Exception)

  /**
   * OnResponse will be called when a write response has been received and processed for the given
   * path.
   *
   * @param attributePath The attribute path field in write response.
   * @param status The attribute status field in write response.
   */
  fun onResponse(attributePath: AttributePath, status: Status)

  fun onDone() {}
}
