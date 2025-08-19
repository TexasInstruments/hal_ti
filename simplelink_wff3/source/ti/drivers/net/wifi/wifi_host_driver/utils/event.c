/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdint.h>
#include "wlan_if.h"
#include "errors.h"
#include "osi_kernel.h"
#include <string.h>
#include "tx.h"
#include "fw_event_if.h"
#include "host_event_if.h"

// ============================================================================
//      Host Event Handler
// ============================================================================
extern OsiMsgQ_t eventMsgQueue;
void Wlan_HostSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen)
{
    // marking the parameter as unused to bypass 'unused parameter' warning
    (void)argsLen;

    EventMessage_t event;
    uint8_t *event_data;
    event_data = os_malloc(sizeof(WlanEvent_t) + HOST_EVENT_RESERVED_EVENT_HEADER);

    if (!args)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\r[dispatcherSendEvent] ERROR NULL buffer,opcode:%d\n\r",opcode);
    }

    switch (opcode)
    {
        case WLAN_EVENT_ERROR:
        {
            WlanEventError_t*  pArgs = (WlanEventError_t *)(event_data + sizeof(uint32_t) + HOST_EVENT_RESERVED_EVENT_HEADER);
            pArgs->module = ((WlanEventError_t *)(args))->module;
            pArgs->error_num = ((WlanEventError_t *)(args))->error_num;
            pArgs->severity = ((WlanEventError_t *)(args))->severity;
            ((WlanEvent_t *)(event_data + HOST_EVENT_RESERVED_EVENT_HEADER))->Id = WLAN_EVENT_ERROR;

        }
        break;
        case WLAN_EVENT_FW_CRASH:
        {
            WlanEventError_t*  pArgs = (WlanEventError_t *)(event_data + sizeof(uint32_t) + HOST_EVENT_RESERVED_EVENT_HEADER);
            pArgs->module = ((WlanEventError_t *)(args))->module;
            pArgs->error_num = ((WlanEventError_t *)(args))->error_num;
            pArgs->severity = ((WlanEventError_t *)(args))->severity;
            ((WlanEvent_t *)(event_data + HOST_EVENT_RESERVED_EVENT_HEADER))->Id = WLAN_EVENT_FW_CRASH;
        }
        break;
    }


    event.message = event_data;
    event.len = sizeof(WlanEvent_t) + HOST_EVENT_RESERVED_EVENT_HEADER;
    osi_MsgQWrite(&eventMsgQueue, &event, OSI_WAIT_FOREVER,OSI_FLAG_NOT_FROM_INTR);


}
