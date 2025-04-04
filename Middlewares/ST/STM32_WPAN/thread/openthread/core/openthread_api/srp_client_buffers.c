/**
 ******************************************************************************
 * @file    srp_client_buffers.c
 * @author  MCD Application Team
 * @brief   This file contains the srp client buffers interface shared between M0 and
 *          M4.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

#include "stm32wbxx_core_interface_def.h"
#include "tl_thread_hci.h"

/* Include definition of compilation flags requested for OpenThread configuration */
#include OPENTHREAD_CONFIG_FILE

#if OPENTHREAD_CONFIG_SRP_CLIENT_BUFFERS_ENABLE

#include "srp_client_buffers.h"

char *otSrpClientBuffersGetHostNameString(otInstance *aInstance, uint16_t *aSize)
{
  char * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_HOST_NAME_STRING;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aSize;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (char *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

otIp6Address *otSrpClientBuffersGetHostAddressesArray(otInstance *aInstance, uint8_t *aArrayLength)
{
  otIp6Address * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_HOST_ADDRESSES_ARRAY;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aArrayLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otIp6Address *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

otSrpClientBuffersServiceEntry *otSrpClientBuffersAllocateService(otInstance *aInstance)
{
  otSrpClientBuffersServiceEntry * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_ALLOCATE_SERVICE;

  p_ot_req->Size=0;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otSrpClientBuffersServiceEntry *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

void otSrpClientBuffersFreeService(otInstance *aInstance, otSrpClientBuffersServiceEntry *aService)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_FREE_SERVICE;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aService;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

void otSrpClientBuffersFreeAllServices(otInstance *aInstance)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_FREE_ALL_SERVICES;

  p_ot_req->Size=0;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

char *otSrpClientBuffersGetServiceEntryServiceNameString(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize)
{
  char * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_SERVICE_ENTRY_SERVICE_NAME_STRING;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aEntry;
  p_ot_req->Data[1] = (uint32_t) aSize;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (char *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

char *otSrpClientBuffersGetServiceEntryInstanceNameString(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize)
{
  char * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_SERVICE_ENTRY_INSTANCE_NAME_STRING;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aEntry;
  p_ot_req->Data[1] = (uint32_t) aSize;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (char *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

uint8_t *otSrpClientBuffersGetServiceEntryTxtBuffer(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aSize)
{
  uint8_t * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_SERVICE_ENTRY_TX_BUFFER;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aEntry;
  p_ot_req->Data[1] = (uint32_t) aSize;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (uint8_t *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

const char **otSrpClientBuffersGetSubTypeLabelsArray(otSrpClientBuffersServiceEntry *aEntry, uint16_t *aArrayLength)
{
  const char ** rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_SRP_CLIENT_BUFFERS_GET_SUB_TYPE_LABELS_ARRAY;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aEntry;
  p_ot_req->Data[1] = (uint32_t) aArrayLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (const char **)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

#endif // OPENTHREAD_CONFIG_SRP_CLIENT_BUFFERS_ENABLE
