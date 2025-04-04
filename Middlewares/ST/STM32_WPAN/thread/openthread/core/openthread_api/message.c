/**
 ******************************************************************************
 * @file    message.c
 * @author  MCD Application Team
 * @brief   This file contains the message buffers and queues interface shared
 *          between M0 and M4.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2018-2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

#include "stm32wbxx_core_interface_def.h"
#include "tl_thread_hci.h"

/* Include definition of compilation flags requested for OpenThread configuration */
#include OPENTHREAD_CONFIG_FILE

#include "thread.h"
#include "message.h"


void otMessageFree(otMessage *aMessage)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_FREE;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

uint16_t otMessageGetLength(const otMessage *aMessage)
{
  uint16_t rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_GET_LENGTH;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (uint16_t)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

otError otMessageSetLength(otMessage *aMessage, uint16_t aLength)
{
  otError rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_SET_LENGTH;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otError)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

uint16_t otMessageGetOffset(const otMessage *aMessage)
{
  uint16_t rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_GET_OFFSET;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (uint16_t)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

void otMessageSetOffset(otMessage *aMessage, uint16_t aOffset)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_SET_OFFSET;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aOffset;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

bool otMessageIsLinkSecurityEnabled(const otMessage *aMessage)
{
  bool rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_IS_LINK_SECURITY_ENABLED;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (bool)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

void otMessageSetDirectTransmission(otMessage *aMessage, bool aEnabled)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_SET_DIRECT_TRANSMISSION;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aEnabled;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

int8_t otMessageGetRss(const otMessage *aMessage)
{
  int8_t rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_GET_RSS;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (int8_t)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

otError otMessageAppend(otMessage *aMessage, const void *aBuf, uint16_t aLength)
{
  otError rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_APPEND;

  p_ot_req->Size=3;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aBuf;
  p_ot_req->Data[2] = (uint32_t) aLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otError)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

uint16_t otMessageRead(const otMessage *aMessage, uint16_t aOffset, void *aBuf, uint16_t aLength)
{
  uint16_t rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_READ;

  p_ot_req->Size=4;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aOffset;
  p_ot_req->Data[2] = (uint32_t) aBuf;
  p_ot_req->Data[3] = (uint32_t) aLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (uint16_t)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

int otMessageWrite(otMessage *aMessage, uint16_t aOffset, const void *aBuf, uint16_t aLength)
{
  int rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_WRITE;

  p_ot_req->Size=4;
  p_ot_req->Data[0] = (uint32_t) aMessage;
  p_ot_req->Data[1] = (uint32_t) aOffset;
  p_ot_req->Data[2] = (uint32_t) aBuf;
  p_ot_req->Data[3] = (uint32_t) aLength;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (int)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

void otMessageQueueInit(otMessageQueue *aQueue)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_INIT;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aQueue;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

void otMessageQueueEnqueue(otMessageQueue *aQueue, otMessage *aMessage)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_ENQUEUE;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aQueue;
  p_ot_req->Data[1] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

void otMessageQueueEnqueueAtHead(otMessageQueue *aQueue, otMessage *aMessage)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_ATHEAD;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aQueue;
  p_ot_req->Data[1] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

void otMessageQueueDequeue(otMessageQueue *aQueue, otMessage *aMessage)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_DEQUEUE;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aQueue;
  p_ot_req->Data[1] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

otMessage *otMessageQueueGetHead(otMessageQueue *aQueue)
{
  otMessage * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_GET_HEAD;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aQueue;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otMessage *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

otMessage *otMessageQueueGetNext(otMessageQueue *aQueue, const otMessage *aMessage)
{
  otMessage * rspData;
  
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_QUEUE_GET_NEXT;

  p_ot_req->Size=2;
  p_ot_req->Data[0] = (uint32_t) aQueue;
  p_ot_req->Data[1] = (uint32_t) aMessage;

  Ot_Cmd_Transfer();

  p_ot_req = THREAD_Get_OTCmdRspPayloadBuffer();
  rspData = (otMessage *)p_ot_req->Data[0];
  
  Post_OtCmdProcessing();
  
  return rspData;
}

void otMessageGetBufferInfo(otInstance *aInstance, otBufferInfo *aBufferInfo)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_BUFFER_INFO;

  p_ot_req->Size=1;
  p_ot_req->Data[0] = (uint32_t) aBufferInfo;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing();
}

#if OPENTHREAD_FTD || OPENTHREAD_MTD
void otMessageResetBufferInfo(otInstance *aInstance)
{
  Pre_OtCmdProcessing();
  /* prepare buffer */
  Thread_OT_Cmd_Request_t* p_ot_req = THREAD_Get_OTCmdPayloadBuffer();

  p_ot_req->ID = MSG_M4TOM0_OT_MESSAGE_RESET_BUFFER_INFO;

  p_ot_req->Size=0;

  Ot_Cmd_Transfer();

  Post_OtCmdProcessing(); 
}
#endif // OPENTHREAD_FTD || OPENTHREAD_MTD
