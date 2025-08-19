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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <osi_kernel.h>
#include <hci_transport.h>

//*****************************************************************************
//                          LOCAL DEFINES
//*****************************************************************************
// HCI Packet Types
#define HCI_CMD_PACKET                                    0x01        //!< Command Packet
#define HCI_ACL_DATA_PACKET                               0x02        //!< ACL Data Packet (2 bytes length)
#define HCI_SCO_DATA_PACKET                               0x03        //!< SCO Data Packet
#define HCI_EVENT_PACKET                                  0x04        //!< Event Packet
#define HCI_EXTENDED_EVENT_PACKET                         0x05        //!< Extended Event Packet   (2 bytes length)
#define HCI_EXTENDED_CMD_PACKET                           0x09        //!< Extended Command Packet (2 bytes length)

//HCI Packet Length
#define HCI_MAX_PKT_LEN                                   256

//HCI Header Length
#define HCI_EVENT_PKT_HDR_LEN                             3
#define HCI_CMD_PKT_HDR_LEN                               4
#define HCI_DATA_PKT_HDR_LEN                              5

//HCI Header Bytes Location
#define HCI_PKT_TYPE_BYTE                                 1
#define HCI_EVENT_HDR_LEN_BYTE                            2
#define HCI_EVENT_HDR_DATA_BYTE                           3
#define HCI_CMD_HDR_LEN_BYTE                              3
#define HCI_CMD_HDR_DATA_BYTE                             4
#define HCI_DATA_HDR_LEN_BYTE1                            3
#define HCI_DATA_HDR_LEN_BYTE2                            4
#define HCI_DATA_HDR_DATA_BYTE                            5


//*****************************************************************************
//                          LOCAL VARIABLES
//*****************************************************************************
hcitrans_rx_cb_t g_rx_cb;
const hciTransport_t* g_pTransport;

//*****************************************************************************
//                          LOCAL FUNCTIONS
//*****************************************************************************


//*****************************************************************************
//                          GLOBAL VARIABLES
//*****************************************************************************
#define TransportRxCb               g_rx_cb
#define TransportInitialized()      (NULL != g_pTransport)
#define TransportRead(buf,len)      g_pTransport->read(buf,len)
#define TransportWrite(buf,len)     g_pTransport->write(buf,len)

//*****************************************************************************
//                          HCI THREAD
//*****************************************************************************
/******************************************************************************
THREAD DEFINES
******************************************************************************/
#ifdef CC33XX
#define HCI_THRD_PRIORITY   (3)
#else
#define HCI_THRD_PRIORITY   (6)
#endif
#define HCI_THRD_STACK_SIZE (2048)

/******************************************************************************
THREAD VARIABLES
******************************************************************************/
OsiThread_t gHciThreadTcb = NULL;
Bool_e      gHciThreadRunning = FALSE;

/******************************************************************************
THREAD FUNCTIONS
******************************************************************************/
void HciThread_Entry(void* params)
{
    OsiReturnVal_e rc;
    uint8_t* hciPktBuf;
    uint16_t hciPktReadLen = 0;

    Report("\n\rHci_Thread: thrd is running\n");

    //Mark thread as running
    gHciThreadRunning = TRUE;

    //Allocate memory for the HCI packet
    //This memory will only be released when thread is destructed
    hciPktBuf = os_malloc(HCI_MAX_PKT_LEN);

    //Initialize the packet before reading it from the transport
    os_memset(hciPktBuf,0,HCI_MAX_PKT_LEN);

    Report("\n\rHci_Thread: Start Listening...\n");

    while (gHciThreadRunning)
    {
        if (HciTransport_ReadHciPacket(hciPktBuf, &hciPktReadLen) == 0)
        {
            TransportRxCb(hciPktBuf, hciPktReadLen);
        }
    }

    Report("\n\rHciThread: Stop Listening...\n");

    //Release the packet memory
    os_free(hciPktBuf);

    Report("\n\rHci_Thread: thrd is stopped\n");
}

int HciThread_Init()
{
    OsiReturnVal_e rc = OSI_OK;

    //Create Task
    rc = osi_ThreadCreate(&gHciThreadTcb,                  // Thread control block
                         "hciThread",                      // Thread name
                          HCI_THRD_STACK_SIZE,             // Stack size
                          HCI_THRD_PRIORITY,               // Thread priority
                          HciThread_Entry,                 // Thread entry function
                          NULL);                           // Thread init parameters
    if (OSI_OK != rc)
    {
        Report("\n\r HciThread_Init: ThreadCreate failed !!!");
        return -1;
    }

    return 0;
}

void HciThread_Destruct()
{
    OsiReturnVal_e rc = OSI_OK;

    //Delete HCI Thread
    rc = osi_ThreadDelete(&gHciThreadTcb);
    if (OSI_OK != rc)
    {
        Report("\n\rHciThread_Destruct: ThreadDelete failed !!!");
        ASSERT_GENERAL(0);
    }

    //Mark thread as ended
    gHciThreadRunning = FALSE;
}


//*****************************************************************************
//                          API FUNCTIONS
//*****************************************************************************
//*****************************************************************************
//
//! HciTransport_Init
//!
//! This function initialize the transport layer for HCI
//!
//! \param  pTransport - pointer to
//!
//! \return none
//
//*****************************************************************************
void HciTransport_Init(const hciTransport_t* const pTransport)
{
    //Set the transport functions
    if (pTransport != NULL)
    {
        g_pTransport = pTransport;
    }

    //Start the HCI thread in case it is not running
    if (gHciThreadRunning == FALSE)
    {
        HciThread_Init();
    }
}

//*****************************************************************************
//
//! HciTransport_Release
//!
//! This function releases the transport layer for HCI
//!
//! \param  none
//!
//! \return none
//
//*****************************************************************************
void HciTransport_Release()
{
    g_pTransport = NULL;
    HciThread_Destruct();
}

//*****************************************************************************
//
//! HciTransport_IsInitialized
//!
//! This function checks if transport was previously initialized
//!
//! \param  none
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_IsInitialized()
{
    return gHciThreadRunning;
}

//*****************************************************************************
//
//! HciTransport_ReadHciPacket
//!
//! This function reads a complete HCI packet with any transport
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_ReadHciPacket(uint8_t* pHciPkt, uint16_t* hciPktLen)
{
    uint8_t packetType = 0;
    uint16_t dataLength = 0;
    size_t bytesRead;

    //check if module was previously initialized
    if (TransportInitialized() == FALSE)
    {
        return -1;
    }

    //Initialize the local buffer
    os_memset(pHciPkt, 0x00, HCI_MAX_PKT_LEN);

    //Read Packet Type
    TransportRead(pHciPkt, HCI_PKT_TYPE_BYTE);

    //Set Packet Type
    packetType = pHciPkt[0];

    if ((packetType == HCI_EVENT_PACKET) || (packetType == HCI_EXTENDED_EVENT_PACKET))
    {
        //Read the rest of packet header
        TransportRead((pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_EVENT_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Event Parameters Data Length
        dataLength = pHciPkt[HCI_EVENT_HDR_LEN_BYTE];

        //Read Event Parameters Data
        if (dataLength > 0)
        {
            if (dataLength > (HCI_MAX_PKT_LEN-HCI_EVENT_HDR_DATA_BYTE))
            {
                assert(0);
            }
            TransportRead((pHciPkt + HCI_EVENT_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_EVENT_PKT_HDR_LEN + dataLength;
    }
    else if ((packetType == HCI_CMD_PACKET) || (packetType == HCI_EXTENDED_CMD_PACKET))
    {
        //Read the rest of packet header
        TransportRead((pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_CMD_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Command Parameters Data Length
        dataLength = pHciPkt[HCI_CMD_HDR_LEN_BYTE];

        //Read Command Parameters Data
        if (dataLength > 0)
        {
            if (dataLength > (HCI_MAX_PKT_LEN-HCI_CMD_HDR_DATA_BYTE))
            {
                assert(0);
            }
            TransportRead((pHciPkt + HCI_CMD_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_CMD_PKT_HDR_LEN + dataLength;
    }
    else if (packetType == HCI_ACL_DATA_PACKET)
    {
        //Read the rest of packet header
        TransportRead((pHciPkt + HCI_PKT_TYPE_BYTE), (HCI_DATA_PKT_HDR_LEN - HCI_PKT_TYPE_BYTE));

        //Get Data Total Length
        dataLength = pHciPkt[HCI_DATA_HDR_LEN_BYTE1];
        dataLength |= ((uint16_t)pHciPkt[HCI_DATA_HDR_LEN_BYTE2] << 8);

        //Read Data Total Length
        if (dataLength > 0)
        {
            if (dataLength > (HCI_MAX_PKT_LEN-HCI_DATA_HDR_DATA_BYTE))
            {
                assert(0);
            }
            TransportRead((pHciPkt + HCI_DATA_HDR_DATA_BYTE), dataLength);
        }

        //Set the HCI total packet length
        *hciPktLen = HCI_DATA_PKT_HDR_LEN + dataLength;
    }
    else
    {
        //ERROR
        return -1;
    }

    return 0;
}

//*****************************************************************************
//
//! HciTransport_WriteHciPacket
//!
//! This function writes a complete HCI packet with any transport
//!
//! \param  pHciPkt - pointer to HCI packet
//!         hciPktLen - HCI packet total length
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_WriteHciPacket(uint8_t* pHciPkt, uint16_t hciPktLen)
{
    return TransportWrite(pHciPkt, hciPktLen);
}

//*****************************************************************************
//
//! HciTransport_RxCallbackbRegister
//!
//! This function register the RX callback function
//!
//! \param  cb - callback to be called upon receiving hci packet from transport
//!
//! \return 0 for success or negative number for failure
//
//*****************************************************************************
int HciTransport_RxCallbackbRegister(hcitrans_rx_cb_t cb)
{
    if (cb == NULL)
    {
        //ERROR
        return -1;
    }

    g_rx_cb = cb;
    return 0;
}
