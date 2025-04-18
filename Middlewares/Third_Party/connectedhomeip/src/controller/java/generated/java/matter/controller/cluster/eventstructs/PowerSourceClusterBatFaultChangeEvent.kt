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
import matter.tlv.AnonymousTag
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

class PowerSourceClusterBatFaultChangeEvent(val current: List<UByte>, val previous: List<UByte>) {
  override fun toString(): String = buildString {
    append("PowerSourceClusterBatFaultChangeEvent {\n")
    append("\tcurrent : $current\n")
    append("\tprevious : $previous\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      startArray(ContextSpecificTag(TAG_CURRENT))
      for (item in current.iterator()) {
        put(AnonymousTag, item)
      }
      endArray()
      startArray(ContextSpecificTag(TAG_PREVIOUS))
      for (item in previous.iterator()) {
        put(AnonymousTag, item)
      }
      endArray()
      endStructure()
    }
  }

  companion object {
    private const val TAG_CURRENT = 0
    private const val TAG_PREVIOUS = 1

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): PowerSourceClusterBatFaultChangeEvent {
      tlvReader.enterStructure(tlvTag)
      val current =
        buildList<UByte> {
          tlvReader.enterArray(ContextSpecificTag(TAG_CURRENT))
          while (!tlvReader.isEndOfContainer()) {
            this.add(tlvReader.getUByte(AnonymousTag))
          }
          tlvReader.exitContainer()
        }
      val previous =
        buildList<UByte> {
          tlvReader.enterArray(ContextSpecificTag(TAG_PREVIOUS))
          while (!tlvReader.isEndOfContainer()) {
            this.add(tlvReader.getUByte(AnonymousTag))
          }
          tlvReader.exitContainer()
        }

      tlvReader.exitContainer()

      return PowerSourceClusterBatFaultChangeEvent(current, previous)
    }
  }
}
