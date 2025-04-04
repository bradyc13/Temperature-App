/*
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
package matter.controller.cluster.eventstructs

import matter.controller.cluster.*
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

class SwitchClusterMultiPressOngoingEvent(
  val newPosition: UByte,
  val currentNumberOfPressesCounted: UByte
) {
  override fun toString(): String = buildString {
    append("SwitchClusterMultiPressOngoingEvent {\n")
    append("\tnewPosition : $newPosition\n")
    append("\tcurrentNumberOfPressesCounted : $currentNumberOfPressesCounted\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      put(ContextSpecificTag(TAG_NEW_POSITION), newPosition)
      put(ContextSpecificTag(TAG_CURRENT_NUMBER_OF_PRESSES_COUNTED), currentNumberOfPressesCounted)
      endStructure()
    }
  }

  companion object {
    private const val TAG_NEW_POSITION = 0
    private const val TAG_CURRENT_NUMBER_OF_PRESSES_COUNTED = 1

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): SwitchClusterMultiPressOngoingEvent {
      tlvReader.enterStructure(tlvTag)
      val newPosition = tlvReader.getUByte(ContextSpecificTag(TAG_NEW_POSITION))
      val currentNumberOfPressesCounted =
        tlvReader.getUByte(ContextSpecificTag(TAG_CURRENT_NUMBER_OF_PRESSES_COUNTED))

      tlvReader.exitContainer()

      return SwitchClusterMultiPressOngoingEvent(newPosition, currentNumberOfPressesCounted)
    }
  }
}
