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
package chip.devicecontroller.cluster.structs

import chip.devicecontroller.cluster.*
import matter.tlv.AnonymousTag
import matter.tlv.ContextSpecificTag
import matter.tlv.Tag
import matter.tlv.TlvReader
import matter.tlv.TlvWriter

class ActionsClusterEndpointListStruct(
  val endpointListID: UInt,
  val name: String,
  val type: UInt,
  val endpoints: List<UInt>
) {
  override fun toString(): String = buildString {
    append("ActionsClusterEndpointListStruct {\n")
    append("\tendpointListID : $endpointListID\n")
    append("\tname : $name\n")
    append("\ttype : $type\n")
    append("\tendpoints : $endpoints\n")
    append("}\n")
  }

  fun toTlv(tlvTag: Tag, tlvWriter: TlvWriter) {
    tlvWriter.apply {
      startStructure(tlvTag)
      put(ContextSpecificTag(TAG_ENDPOINT_LIST_I_D), endpointListID)
      put(ContextSpecificTag(TAG_NAME), name)
      put(ContextSpecificTag(TAG_TYPE), type)
      startArray(ContextSpecificTag(TAG_ENDPOINTS))
      for (item in endpoints.iterator()) {
        put(AnonymousTag, item)
      }
      endArray()
      endStructure()
    }
  }

  companion object {
    private const val TAG_ENDPOINT_LIST_I_D = 0
    private const val TAG_NAME = 1
    private const val TAG_TYPE = 2
    private const val TAG_ENDPOINTS = 3

    fun fromTlv(tlvTag: Tag, tlvReader: TlvReader): ActionsClusterEndpointListStruct {
      tlvReader.enterStructure(tlvTag)
      val endpointListID = tlvReader.getUInt(ContextSpecificTag(TAG_ENDPOINT_LIST_I_D))
      val name = tlvReader.getString(ContextSpecificTag(TAG_NAME))
      val type = tlvReader.getUInt(ContextSpecificTag(TAG_TYPE))
      val endpoints =
        buildList<UInt> {
          tlvReader.enterArray(ContextSpecificTag(TAG_ENDPOINTS))
          while (!tlvReader.isEndOfContainer()) {
            add(tlvReader.getUInt(AnonymousTag))
          }
          tlvReader.exitContainer()
        }

      tlvReader.exitContainer()

      return ActionsClusterEndpointListStruct(endpointListID, name, type, endpoints)
    }
  }
}
