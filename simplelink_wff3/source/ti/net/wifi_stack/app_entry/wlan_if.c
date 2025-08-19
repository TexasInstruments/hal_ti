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
#ifndef USER_INTEFACE_WLAN_IF_C_
#define USER_INTEFACE_WLAN_IF_C_



//#include "io.h"

#include "wlan_if.h"
#include "ethernet.h"
#include "tx_ctrl_blk_api.h"
#include "udata_api.h"
#include "udata_net_api.h"
#include <init_host_if.h>
#include "gtrace.h"
#include "cme_fw_api.h"
#include "cme_dispatcher_api.h"
#include <public_types.h>
#include <trnspt_if.h>
#include <trnspt_thread.h>
#include "macro_utils.h"
#include "common.h"
#include "l2_cfg.h"
#include "errors.h"
#include "regulatory_domain.h"
#include "wlan_links.h"
#include "wlan_irq_adapt.h"
#include "drv_ti_internal.h"
#include "control_cmd_fw.h"
#include "tx_ctrl_api.h"
#include "trnspt_thread.h"
#include "init_host.h"
#include "drv_ext_app.h"
#include "scan_result_table.h"
#include <upper_mac_versions.h>
#include "csi.h"

//#define EVENT_TEST
#ifdef EVENT_TEST
void testEventHandler(uint16_t opcode);
#endif /* EVENT_TEST */

#ifdef CC35XX
Bool_e g_wait_p2p_scan_complete = FALSE;
OsiSyncObj_t p2p_find_stopped_syncObj = NULL;
#endif // CC35XX

#define WLAN_PROTECTION

extern StartRoleApps_t gRoleAppsParams;

WlanNetworkDataRecvCB_t RecvCallBack[2] = {0};

dbg_cntr_trnspt_t g_stat_trnpt;
device_info_t gDevice_info = {0};
uint32_t gWlanState = FALSE;
extern uint32_t drv_getDriverLink(uint32_t uNetIfId, uint8_t* dst);
extern char *cmeWlanGetKeyMgmt(void);
extern uint32_t txHwQueue_SetInitializeHwBlocks (uint32_t tx_BlocksAvailable, uint32_t tx_NumTxDescriptor);

int roleUp_Inter(WlanRole_e roleType, void *params, unsigned long int timeout);
int roleDown_inter(WlanRole_e roleType, unsigned long int timeout);

bool gExtendedScanResults = FALSE;

WlanSetCSIParams_t gCsiParams;

typedef enum
{
    WLAN_IF_ROLE_UP_IN_PROGRESS = 0x1,
    WLAN_IF_ROLE_DOWN_IN_PROGRESS = 0x2,
    WLAN_IF_SURVEY_SCAN_IN_PROCESS = 0x4,
    WLAN_IF_CONNECT_IN_PROGRESS = 0x8,
    WLAN_IF_START_IN_PROGRESS = 0x10, //16,
    WLAN_IF_STOP_IN_PROGRESS = 0x20, //32
    WLAN_IF_DISCONNECT_IN_PROGRESS = 0x40, //64
    WLAN_IF_SET_IN_PROGRESS = 0x80, //128
    WLAN_IF_GET_IN_PROGRESS = 0x100,//256
    WLAN_IF_GET_EXCLUDE_IN_PROGRESS = 0x200,//512 get operation can be done while connect
    WLAN_IF_SET_EXCLUDE_IN_PROGRESS = 0x400,//1024 ,set operation can be done while connect
    WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS = 0x800,//2048
    WLAN_IF_PERIODIC_SCAN_IN_PROGRESS = 0x1000,//4096
    WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS = 0x2000,//8192

}oper_bitmap_t;

OsiLockObj_t        g_wlan_if_lockObj = NULL;
uint32_t            g_oper_bitmap={0};/* see @oper_bitmap_t*/
uint32_t gIsRecovery;
// ============================================================================
//     utility Functions
// ============================================================================

void wlan_if_lock()
{
    OsiReturnVal_e ret = OSI_OK;
    if(g_wlan_if_lockObj != NULL)
    {
        /* Start critical section protection */
        ret= osi_LockObjLock(&g_wlan_if_lockObj, OSI_WAIT_FOREVER);
    }
    else //if lock was not created -- create it and lock
    {
        ret = osi_LockObjCreate(&g_wlan_if_lockObj);
        if (ret != OSI_OK)
        {
            CME_PRINT_REPORT_ERROR("\r\nfailed to create lock object:g_wlan_if_lockObj");
            assert(0);
        }
        ret= osi_LockObjLock(&g_wlan_if_lockObj, OSI_WAIT_FOREVER);
    }
    if (ret != OSI_OK)
    {
        CME_PRINT_REPORT_ERROR("\r\nfailed to lock object:g_wlan_if_lockObj");
        assert(0);
    }
}

void wlan_if_unlock()
{
    OsiReturnVal_e ret =OSI_OK;

    if(g_wlan_if_lockObj != NULL)
    {
        /* Stop critical section protection */
        ret = osi_LockObjUnlock(&g_wlan_if_lockObj);
        if (ret != OSI_OK)
        {
            CME_PRINT_REPORT_ERROR("\r\nfailed to unlock object:g_wlan_if_lockObj:%d",ret);
            assert(0);
        }
    }
    else
    {
        CME_PRINT_REPORT_ERROR("\r\nlock object:g_wlan_if_lockObj was not created");
    }
}



///  set ///////////////////////////
int32_t is_wlan_oper_in_progress(uint32_t bit_val, uint8_t isRetryPrint)
{
    int32_t ret = -1;
    uint32_t allow_bitmask = 0;


    if (bit_val == WLAN_IF_DISCONNECT_IN_PROGRESS)
    {
        allow_bitmask =
                WLAN_IF_SURVEY_SCAN_IN_PROCESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_GET_IN_PROGRESS|
                WLAN_IF_GET_EXCLUDE_IN_PROGRESS|
                WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    }
    else if (bit_val == WLAN_IF_GET_EXCLUDE_IN_PROGRESS)
    {
        allow_bitmask =
                WLAN_IF_ROLE_UP_IN_PROGRESS|
                WLAN_IF_ROLE_DOWN_IN_PROGRESS|
                WLAN_IF_SURVEY_SCAN_IN_PROCESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS|
                WLAN_IF_DISCONNECT_IN_PROGRESS;
    }
    else if (bit_val == WLAN_IF_SET_EXCLUDE_IN_PROGRESS)
    {
        allow_bitmask =
                WLAN_IF_ROLE_UP_IN_PROGRESS|
                WLAN_IF_ROLE_DOWN_IN_PROGRESS|
                WLAN_IF_SURVEY_SCAN_IN_PROCESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS|
                WLAN_IF_DISCONNECT_IN_PROGRESS;
    }
    else if (bit_val == WLAN_IF_ROLE_UP_IN_PROGRESS)
    {
        allow_bitmask =
                WLAN_IF_SURVEY_SCAN_IN_PROCESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    }
    else if (bit_val == WLAN_IF_ROLE_DOWN_IN_PROGRESS)
    {
        allow_bitmask =
                WLAN_IF_SURVEY_SCAN_IN_PROCESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    }
    else if (bit_val == WLAN_IF_SURVEY_SCAN_IN_PROCESS)
    {
        allow_bitmask =
                WLAN_IF_ROLE_UP_IN_PROGRESS|
                WLAN_IF_PERIODIC_SCAN_IN_PROGRESS;

        if (g_oper_bitmap & WLAN_IF_PERIODIC_SCAN_IN_PROGRESS)
        {
            allow_bitmask |=
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
        }
    }
    else if ((bit_val == WLAN_IF_CONNECT_IN_PROGRESS) || (bit_val == WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS))
    {
        allow_bitmask =
                WLAN_IF_ROLE_UP_IN_PROGRESS |
                WLAN_IF_ROLE_DOWN_IN_PROGRESS |
                WLAN_IF_SET_IN_PROGRESS |
                WLAN_IF_GET_IN_PROGRESS |
                WLAN_IF_GET_EXCLUDE_IN_PROGRESS |
                WLAN_IF_SET_EXCLUDE_IN_PROGRESS;

    }
    else if ((bit_val == WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS) || (bit_val == WLAN_IF_PERIODIC_SCAN_IN_PROGRESS))
    {
        allow_bitmask =
                WLAN_IF_ROLE_UP_IN_PROGRESS|
                WLAN_IF_ROLE_DOWN_IN_PROGRESS|
                WLAN_IF_SET_IN_PROGRESS|
                WLAN_IF_GET_IN_PROGRESS|
                WLAN_IF_GET_EXCLUDE_IN_PROGRESS|
                WLAN_IF_SET_EXCLUDE_IN_PROGRESS|
                WLAN_IF_CONNECT_IN_PROGRESS|
                WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    }


    if ((g_oper_bitmap & (~(allow_bitmask)))== 0)
    {
        GTRACE(GRP_CME, "is_wlan_oper_in_progress: setting bit_val 0x%x, g_oper_bitmap: 0x%x", bit_val, g_oper_bitmap);
        g_oper_bitmap |= bit_val;
        ret = OSI_OK;
    }
    else
    {
        if(isRetryPrint)
        {
            GTRACE(GRP_CME, "operation is in process : g_oper_bitmap: 0x%x bit_val: 0x%x", g_oper_bitmap,bit_val);
            CME_PRINT_REPORT("\r\n !!!! operation is in process : g_oper_bitmap: 0x%x bit_val: 0x%x",
                   g_oper_bitmap, bit_val );
        }
        ret = -1;
    }
    return ret;
}

/// wlan_start
int32_t set_cond_in_process_wlan_start()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_START_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
    return ret;
}
void set_finish_wlan_start()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_START_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

/// wlan_stop
int32_t set_cond_in_process_wlan_stop()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_STOP_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
    return ret;
}

void set_finish_wlan_stop()
{
#ifdef WLAN_PROTECTION
    int32_t ret = OSI_OK;
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_STOP_IN_PROGRESS;
    wlan_if_unlock();
    ret = osi_LockObjDelete(&g_wlan_if_lockObj);
    if (ret != OSI_OK)
    {
        CME_PRINT_REPORT_ERROR("\n\rfailed to delete lock object:g_wlan_if_lockObj");
        assert(0);
    }
    g_wlan_if_lockObj = NULL;
#endif
}

// wlan_roleup
uint32_t set_cond_in_process_wlan_roleup()
{
	uint32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_ROLE_UP_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
    return ret;
}

void set_finish_wlan_roleup()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_ROLE_UP_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

/// wlan_roledown
int32_t set_cond_in_process_wlan_roledown()
{
	int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_ROLE_DOWN_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
	return ret;
}
void set_finish_wlan_roledown()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_ROLE_DOWN_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

/// wlan_connect
int32_t set_cond_in_process_wlan_connect()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_CONNECT_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
	return ret;
}
void set_finish_wlan_connect()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~(WLAN_IF_CONNECT_IN_PROGRESS);
    wlan_if_unlock();
#endif
}

// wlan_one_shot_scan
int32_t set_cond_in_process_wlan_one_shot_scan()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
	return ret;
}

void set_finish_wlan_one_shot_scan()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_ONE_SHOT_SCAN_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

// wlan_periodic_scan
int32_t set_cond_in_process_wlan_periodic_scan()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_PERIODIC_SCAN_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
	return ret;
}

void set_finish_wlan_periodic_scan()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_PERIODIC_SCAN_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

// wlan_supplicant_operation
int32_t set_cond_in_process_wlan_supplicant_operation()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS,1);
    wlan_if_unlock();
#endif
	return ret;
}

void set_finish_wlan_supplicant_operation()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    wlan_if_unlock();
#endif
}

int32_t is_wlan_supplicant_operation_in_progress()
{
    int32_t ret;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = g_oper_bitmap & WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS;
    wlan_if_unlock();
#endif
    return ret;
}

// wlan_discconnect
int32_t set_cond_in_process_wlan_discconnect(uint8_t isRetryPrint)
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_DISCONNECT_IN_PROGRESS,isRetryPrint);
wlan_if_unlock();
#endif
    return ret;
}
void set_finish_wlan_disconnect()
{
#ifdef WLAN_PROTECTION
    wlan_if_lock();
    g_oper_bitmap &= ~(WLAN_IF_DISCONNECT_IN_PROGRESS|WLAN_IF_CONNECT_IN_PROGRESS|WLAN_IF_SUPPLICANT_OPERATION_IN_PROGRESS);
    wlan_if_unlock();
#endif
}

//wlan_scan
int32_t set_cond_in_process_wlan_survey_scan()
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION

    wlan_if_lock();
    ret = is_wlan_oper_in_progress(WLAN_IF_SURVEY_SCAN_IN_PROCESS,1);
    wlan_if_unlock();
#endif
	return ret;
}

void set_finish_wlan_survey_scan()
{
#ifdef WLAN_PROTECTION
	wlan_if_lock();
	g_oper_bitmap &= ~WLAN_IF_SURVEY_SCAN_IN_PROCESS;
	wlan_if_unlock();
#endif
}

//wlan_set
int32_t set_cond_in_process_wlan_set(WlanSet_e wlanSet)
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    uint32_t bit_val;

    switch (wlanSet)
    {
        case WLAN_SET_MACADDRESS:
        case WLAN_SET_VENDOR_IE:
        case WLAN_SET_EXTERNAL:
        case WLAN_SET_POWER_SAVE:
            bit_val = WLAN_IF_SET_EXCLUDE_IN_PROGRESS;//enable while connect in progress
            break;
        default:
            bit_val = WLAN_IF_SET_IN_PROGRESS;
            break;
    }
    //this function can be called before/after the lock is created/deleted
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(bit_val,1);
    wlan_if_unlock();
#endif
    return ret;
}

void set_finish_wlan_set(WlanSet_e wlanSet)
{
#ifdef WLAN_PROTECTION
    uint32_t bit_val;

    switch (wlanSet)
    {
        case WLAN_SET_MACADDRESS:
        case WLAN_SET_VENDOR_IE:
        case WLAN_SET_EXTERNAL:
        case WLAN_SET_POWER_SAVE:
            bit_val = WLAN_IF_SET_EXCLUDE_IN_PROGRESS;//enable while connect in progress
            break;
        default:
            bit_val = WLAN_IF_SET_IN_PROGRESS;
            break;
    }
    //this function can be called before/after the lock is created/deleted
    wlan_if_lock();
    g_oper_bitmap &= ~bit_val;
    wlan_if_unlock();
#endif
}

//wlan_get
int32_t set_cond_in_process_wlan_get(WlanGet_e wlanGetType)
{
    int32_t ret = OSI_OK;
#ifdef WLAN_PROTECTION
    uint32_t bit_val;

    switch (wlanGetType)
    {
        case WLAN_GET_DEVICE_INFO:
        case WLAN_GET_FWVERSION:
        case WLAN_GET_RSSI:
        case WLAN_GET_ROLE_CHANNEL_NUMBER:
        case WLAN_GET_HOST_VERSION:
        case WLAN_GET_EXTERNAL:
        case WLAN_GET_MACADDRESS:
            bit_val = WLAN_IF_GET_EXCLUDE_IN_PROGRESS;//enable while connect in progress
            break;
        default:
            bit_val = WLAN_IF_GET_IN_PROGRESS;
            break;
    }
    //this function can be called before/after the lock is created/deleted
    wlan_if_lock();
    ret = is_wlan_oper_in_progress(bit_val,1);
    wlan_if_unlock();
#endif
    return ret;
}

void set_finish_wlan_get(WlanGet_e wlanGetType)
{
#ifdef WLAN_PROTECTION
    uint32_t bit_val;
	wlan_if_lock();
    switch (wlanGetType)
    {
        case WLAN_GET_DEVICE_INFO:
        case WLAN_GET_FWVERSION:
        case WLAN_GET_RSSI:
        case WLAN_GET_ROLE_CHANNEL_NUMBER:
        case WLAN_GET_HOST_VERSION:
        case WLAN_GET_EXTERNAL:
        case WLAN_GET_MACADDRESS:
            bit_val = WLAN_IF_GET_EXCLUDE_IN_PROGRESS;//enable while connect in progress
            break;
        default:
            bit_val = WLAN_IF_GET_IN_PROGRESS;
            break;
    }

	g_oper_bitmap &= ~bit_val;
	wlan_if_unlock();
#endif
}


// ============================================================================
//      Data path Functions
// ============================================================================

int Wlan_EtherPacketSend(WlanRole_e roleType, uint8_t *inbuf, uint32_t inbuf_len,uint32_t flags)
{
    TTxCtrlBlk *pPktCtrlBlk;
    uint32_t uNetIfId;
    uint8_t *internalFrame;
    int status;
    uint64_t current_sample, diff;
    uint32_t current_data, dataLen,total_len;
    TEthernetHeader* pEthHead = NULL;
    uint32_t    uHlid;


    HOOK(HOOK_WLAN_IF);

    TX_DATA_SEND_PRINT("\n\rWlan_EtherPacketSend");

    /* Send the packet to the driver for transmission. */
    if(WLAN_ROLE_STA == roleType)
    {
        uNetIfId = TIWDRV_NETIF_ID_STA;
    }
    else // AP
    {
        uNetIfId = TIWDRV_NETIF_ID_SAP;
    }
    uHlid = drv_getDriverLink(uNetIfId, ((TEthernetHeader*)inbuf)->dst);

    txCtrlParams_SetStackCounters(uHlid,inbuf_len);
    pEthHead  = os_malloc(sizeof(TEthernetHeader));
    if (!pEthHead)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\rERROR ti_driver_send_l2_data: Failed to allocate TEthernetHeader for Tx data packet:%s\n\r", __FUNCTION__);
        return -1;
    }
    os_memcpy(pEthHead, inbuf, ETHERNET_HDR_LEN);

    dataLen = inbuf_len-ETHERNET_HDR_LEN;
    total_len = sizeof(NAB_tx_header_t)+ sizeof(TxIfDescriptor_t) + ETHERNET_HDR_LEN + dataLen;
    /* allocate mgmt packet descriptor and buffers */
    pPktCtrlBlk = udata_AllocTxDataPacket(dataLen,ETHERNET_HDR_LEN,pEthHead);

    if (!pPktCtrlBlk)
    {
        os_free(pEthHead);
        TX_FRAME_FLOW_CNTRL_PRINT_MUST("\n\rERROR Wlan_EtherPacketSend: Failed to allocate TxCtrlBlk");
        return -1;
    }
    set_nab_tx_header(&pPktCtrlBlk->aPktNabHdr, total_len );

    /* copy payload to new buffers - the Ethernet header is dropped later on and replaced with wlan header*/
    os_memcpy(pPktCtrlBlk->tTxPktParams.pInputPkt, inbuf+ETHERNET_HDR_LEN, dataLen);

    /* if ip_summed is set to PARTIAL by NS,
     * it means the NS agrees & expects the HW to do
     * the checksum for tcp/udp packets only. */
    /*if TCP/UDP and Checksum offload enabled*/

#if 0 // TODO: Need to implement
    if (skb->ip_summed == CHECKSUM_PARTIAL)
    {
        pPktCtrlBlk->tTxDescriptor.csumData = *((TI_UINT8*)(skb_network_header(skb) + IP_PROTOCOL_OFFSET));
    }
    else
#endif
    {
        pPktCtrlBlk->tTxDescriptor.csumData = 0;
    }


    /* Send the packet to the driver for transmission. */
    status = udataNet_InsertDataPacket(pPktCtrlBlk, uNetIfId, D_TAG_CLSFR /* TODO:  need to implement */);

    return status;

}

void _recvNetworkPacket(uint32_t netifid, uint8_t *inbuf, uint32_t inbuf_len)
{
    WlanRole_e roleType;

    HOOK(HOOK_WLAN_IF);

    if(netifid == TIWDRV_NETIF_ID_STA)
    {
        roleType = WLAN_ROLE_STA;
    }
    else
    {
        roleType = WLAN_ROLE_AP;
    }

    if(RecvCallBack[netifid] != NULL)
    {
        RecvCallBack[netifid](roleType,inbuf,inbuf_len);
    }
}

int Wlan_EtherPacketRecvRegisterCallback(WlanRole_e roleType, WlanNetworkDataRecvCB_t cb)
{
    int retVal = -1;

    HOOK(HOOK_WLAN_IF);

    if(roleType == WLAN_ROLE_STA)
    {
        RecvCallBack[TIWDRV_NETIF_ID_STA] = cb;
        retVal = 0;
    }
    else if(roleType == WLAN_ROLE_AP)
    {
        RecvCallBack[TIWDRV_NETIF_ID_SAP] = cb;
        retVal = 0;
    }
    return retVal;
}




// ============================================================================
//      USER API Function
// ============================================================================
int Wlan_Start(WlanEventHandlerCB_t eventHandlerCB)
{
    int32_t ret = OSI_OK;


    ret = set_cond_in_process_wlan_start();
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Start-retry---");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }

    CME_PRINT_REPORT("\n\r ---Wlan_Start---");

    GTRACE(1, " Supplicant 2.10 !!!!!!\n\r");
    //Check if wlan_start is already active
    if(TRUE == gWlanState)
    {
	    GTRACE(1, " Wlan already started !!!!!!\n\r");
        Report("\n\rWlan already started!!");
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__WLAN_ALREADY_STARTED);
        goto fail;
    }

    // Init params
    gRoleAppsParams.hostConfiguredRolesBitmap = 0;
    gRoleAppsParams.devicePowerSaveMode = WLAN_STATION_ACTIVE_MODE;
    gRoleAppsParams.eventHandlerCB = eventHandlerCB;

    ret = cme_init();
    if(ret != OSI_OK)
    {
        ret = -1;
        assert(0);
        goto fail;
    }
    ret = InitHostDriver();

    if (ret < 0)
    {
    	goto fail;
    }

    l2_cfg_Init();

    // test event handler 
#ifdef EVENT_TEST
    testEventHandler(WLAN_EVENT_CONNECT);
    testEventHandler(WLAN_EVENT_DISCONNECT);
    testEventHandler(WLAN_EVENT_SCAN_RESULT);
#endif
    {
        MemoryMap_t mem_map = {0};
        ret = ctrlCmdFw_GetMemMap(&mem_map);
        if(ret < 0 )
        {
            Report("\n\rcouldn't Get mem map");
            goto fail;
        }
        else
        {
            CME_CON_PRINT("\n\rMemory map :: "
                    "numRxMemBlks:%d "
                    "numTxDescriptor:%d "
                    "numTxMemBlks:%d\n",
                    mem_map.numRxMemBlks,
                    mem_map.numTxDescriptor,
                    mem_map.numTxMemBlks);

            txHwQueue_SetInitializeHwBlocks(mem_map.numTxMemBlks,mem_map.numTxDescriptor);
        }
    }
    set_finish_wlan_start();
    gWlanState = TRUE;
    return OSI_OK;
fail:
	set_finish_wlan_start();
	return ret;
}


int  Wlan_Stop(uint32_t flags)
{
    int32_t ret = OSI_OK;
    gIsRecovery = flags & 0x1; //Recovery is not enabled. After enabling Recovery, use gIsRecovery to check if device is under recovery

    if(TRUE == gIsRecovery)
    {
        Report("\n\r Recovery is not available\r\n");
        return -1;
    }
    

    CME_PRINT_REPORT("\n\r ---Wlan_Stop-Wlan_RoleDown STA ---\n\r");

    /* Sanity check before stop all the system process */
    ret = Wlan_RoleDown(WLAN_ROLE_STA, WLAN_WAIT_TIME_ROLE_SWITCH);
    if(ret != OSI_OK)
    {
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }

    CME_PRINT_REPORT("\n\r ---Wlan_Stop-Wlan_RoleDown uAP---\n\r");

    ret = Wlan_RoleDown(WLAN_ROLE_AP, WLAN_WAIT_TIME_ROLE_SWITCH);
    if(ret != OSI_OK)
    {
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }

    ret = set_cond_in_process_wlan_stop();
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Stop - retry---");
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }
    CME_PRINT_REPORT("\n\r ---Wlan_Stop---");

    ret = DeInitHostDriver();
    if (ret < 0)
    {
        ASSERT_GENERAL(0);
        goto fail;
    }
    
    // cme deint
    ret = cme_deinit();
    if (ret < 0)
    {
        ASSERT_GENERAL(0);
        goto fail;
    }

    //Report("\n\r====================== DEINITIALIZATION DONE! ======================\n\r");
    HOOK(HOOK_WLAN_IF);

    wlan_TurnOffWlan();

    gWlanState = FALSE;
    set_finish_wlan_stop();
    return OSI_OK;

    fail:
        set_finish_wlan_stop();
    	return ret;
}

int Wlan_RoleUp(WlanRole_e roleType, void *params, unsigned long int timeout)
{
    int ret = 0;
    uint32_t role_bitmap;


    ret = set_cond_in_process_wlan_roleup();
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_RoleUp-rety-- %d",roleType);

        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }
   ret = roleUp_Inter(roleType, params, timeout);

    set_finish_wlan_roleup();
    return ret;
}

int Wlan_RoleDown(WlanRole_e roleType, unsigned long int timeout)
{
    uint32_t role_bitmap;
    int32_t ret = 0;

    HOOK(HOOK_WLAN_IF);

   ret = set_cond_in_process_wlan_roledown();
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_RoleDown-retry--- %d",roleType);
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);//not call to fail in purpose
    }

    ret = roleDown_inter(roleType, timeout);

    set_finish_wlan_roledown();
    return ret;
}

int Wlan_Connect(const signed char *pName, const int NameLen, const unsigned char *pMacAddr,
                 char SecType, const char *pPass, const char PassLen, unsigned int flags)
{
    int ret;
    int alloc_size = 0;
    CMEWlanConnectCommon_t *params;

    HOOK(HOOK_WLAN_IF);
    ret = set_cond_in_process_wlan_connect();
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Connect retry---");
    	return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);// not to go to fail in purpose
    }
    CME_PRINT_REPORT("\n\r ---Wlan_Connect---");

    alloc_size = M_ALIGN_TO_4_BYTES(sizeof(CMEWlanConnectCommon_t) + 1 + NameLen + PassLen );

    params = os_zalloc(alloc_size);

    if (!params)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\rWlan_Connect ERROR allocation failed");
        /* failed to allocate */
        ret = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__MALLOC);
        goto fail;
    }

    params->SecType = SecType;
    params->FastTransition = flags & WLAN_CONNECT_FLAG_FAST_TRANSITION_EN;

    /* Copy BSSID */
    if (pMacAddr != NULL)
    {
        IRQ_UtilCopyMacAddress(pMacAddr, params->Bssid);//the ap Bssid
    }

    /* Copy the SSID */
    params->SsidLen = NameLen;
    os_memcpy(SSID_STRING(params), pName, NameLen);

    /* Copy Password */
    params->PasswordLen = PassLen;
    os_memcpy(PASSWORD_STRING(params), pPass, PassLen);

    ret = CME_WlanConnect(params, TRUE);
    if(ret <  0)
    {
    	os_free(params);
    	goto fail;
    }
    os_free(params);
    HOOK(HOOK_WLAN_IF);
    return ret;

fail:
	set_finish_wlan_connect();
	return ret;
}

int Wlan_Disconnect(WlanRole_e roleType,void* params)
{
	int32 ret = OSI_OK;

	ret = set_cond_in_process_wlan_discconnect(1);
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Disconnect retry---");
    return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);// not to go to fail in purpose
    }
    CME_PRINT_REPORT("\n\r ---Wlan_Disconnect---");

    switch (roleType)
    {
    case WLAN_ROLE_AP:
    {
        CMEWlanApRemovePeer_t *pCmdRemovePeer =  (CMEWlanApRemovePeer_t *)params; 

        CME_PRINT_REPORT("\n\rWlan_if AP remove peer: MacAddr = %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n\r",
            pCmdRemovePeer->MacAddress[0],
            pCmdRemovePeer->MacAddress[1],
            pCmdRemovePeer->MacAddress[2],
            pCmdRemovePeer->MacAddress[3],
            pCmdRemovePeer->MacAddress[4],
            pCmdRemovePeer->MacAddress[5]);

        // Call the CME to start the disconnection 
        ret = CME_WlanApRemovePeer(pCmdRemovePeer);
        set_finish_wlan_disconnect();
    }
    break;
    default:
        ret = CME_WlanDisconnect(TRUE);
    }

    // Check ret value
    if(ret != OSI_OK)
    {
        goto fail;
    }
    else
    {
        return ret;
    }

fail:
	set_finish_wlan_disconnect();
    return ret;
}


//pSsidList can be up to MAX_SCAN_SSID
int Wlan_Scan(WlanRole_e role, void* params,const unsigned char ScanResultsSize)
{
    int i;
    scanCommon_t* pScanCommon = params;
    CMEWlanScanCommon_t scanCmeCommon;
    int32_t ret = OSI_OK;

    os_memset((void*)&scanCmeCommon, 0, sizeof(CMEWlanScanCommon_t));
    if(pScanCommon != NULL)
    {
        for(i=0; i<WLAN_MAX_SCAN_SSID; i++)
        {
            scanCmeCommon.CMEWlanSsid[i].ssidLen = pScanCommon->ssidLst[i].ssidLen;
            scanCmeCommon.CMEWlanSsid[i].mHidden = pScanCommon->ssidLst[i].mHidden;
            os_memcpy(scanCmeCommon.CMEWlanSsid[i].pSsid,pScanCommon->ssidLst[i].pSsid,WLAN_SSID_MAX_LENGTH);
        }
        scanCmeCommon.Band = pScanCommon->Band;
        scanCmeCommon.extWpsMode = pScanCommon->extWpsMode;
        scanCmeCommon.roleType = role;
    }

    // if the scan is not WPS or P2P related, start survey scan protection
    if (((scanCmeCommon.extWpsMode != WLAN_SEC_TYPE_WPS_PBC) && (scanCmeCommon.extWpsMode != WLAN_SEC_TYPE_WPS_PIN)) && 
        (role != WLAN_ROLE_DEVICE))
    {
        ret = set_cond_in_process_wlan_survey_scan();
        if(ret != OSI_OK)
        {
            CME_PRINT_REPORT("\n\r ---Wlan_Scan-retry---");
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);// not to go to fail in purpose
        }
    }

    CME_PRINT_REPORT("\n\r ---Wlan_Scan---");
    
    ret = CME_GetScanResults(0, ScanResultsSize, 0, &scanCmeCommon);
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT_ERROR("\n\r Wlan_Scan failed :%d---",ret);
    	goto fail;
    }
    return ret;
fail:
    if (((scanCmeCommon.extWpsMode != WLAN_SEC_TYPE_WPS_PBC) && (scanCmeCommon.extWpsMode != WLAN_SEC_TYPE_WPS_PIN)) && 
        (role != WLAN_ROLE_DEVICE))
    {
        set_finish_wlan_survey_scan();
    }
    return ret;

}

int Wlan_Get(WlanGet_e wlanGetType, void *params)
{

	int32_t ret;

    ret = set_cond_in_process_wlan_get(wlanGetType);
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Get Retry:%d---",(uint32_t) wlanGetType);
    	return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);// not to go to fail in purpose
    }

    CME_PRINT_REPORT("\n\r ---Wlan_Get:%d---",(uint32_t) wlanGetType);

    switch (wlanGetType)
    {
        case WLAN_GET_COUNTERS:
        {
            WlanRole_e role;
            dbg_counters_get_t* pCntGetParams= (dbg_counters_get_t *)params;
            role = pCntGetParams->inp_role;
            host_getCounters(role,&g_stat_trnpt);
            memcpy(&pCntGetParams->out_Param, &g_stat_trnpt, sizeof(dbg_cntr_trnspt_t));
            ret = 0;
        }
        break;
        case WLAN_GET_MACADDRESS:
        {
            WlanMacAddress_t *pMacParams = (WlanMacAddress_t *)params;

            ret = CME_GetMacAddress(pMacParams->roleType, pMacParams->pMacAddress);
        }
		break;
        case WLAN_GET_DEVICE_INFO:
        {
            device_info_t *pDeviceInfo = (device_info_t *)params;

            ret = CME_GetDeviceInfo(pDeviceInfo);
        }
        break;
        case WLAN_GET_POWER_SAVE:
        {
            WlanPowerSave_e *pMode = (WlanPowerSave_e *)params;
        #ifdef TODO //TODO , wlan_GetStateWlan
            if ( 0 == wlan_GetStateWlan())
            {
                //Report("\n\r[ERROR] Device is not started!!!\n\r");
                ret = -1;
                break;   
            }
        #endif
            *pMode = CME_GetPowerSaveMode();

            if(*pMode < WLAN_STATION_AUTO_PS_MODE || *pMode >= WLAN_STATION_NUM_OF_MODES)
            {
                ret = NOK;
            }
            else
            {
                ret = 0;
            }
        }
        break;
        case WLAN_GET_CALIBRATOR_RX_STATS:
        case WLAN_GET_CALIBRATOR_TX_PARAMS:
        case WLAN_GET_CALIBRATOR_BEACON_RSSI:
        {
            CalibratorCommandWrapper_t *calibratorCommand = (CalibratorCommandWrapper_t *)params;
            ret = ctrlCmdFw_CalibratorCommand(calibratorCommand->calibratorAction, calibratorCommand->calibratorCommandParams);
        }
        break;
        case WLAN_GET_SCAN_CHANNEL_UTILIZATION_RESULTS:
        {
            ret = ctrlCmdFw_GetChannelUtilizationResults((WlanChannel_utilize_res_t *)params);
        }
        break;
        case WLAN_GET_DECRYPTED_PACKETS_COUNT:
        {
            ret = ctrlCmdFw_GetDecryptedPacketCounts((WlanDecrypted_packetsCounters_t *)params);
        }
        break;
        case WLAN_GET_ROLE_CHANNEL_NUMBER:
        {
            ret = ctrlCmdFw_GetRoleChannelNumber((WlanRole_current_channel_number*)params);
        }
        break;
        case WLAN_GET_RSSI:
        {
            ret = ctrlCmdFw_GetRssi((BeaconRssi_t*)params);
        }
        break;
        case WLAN_GET_FWVERSION:
        {
            ret = ctrlCmdFw_GetFwVersion((FWVersions_t*)params);
        }
        break;
        case WLAN_GET_CONNECTION_KEY_MANAGEMENT:
        {
            char **key_mgmt = (char **) params;
            *key_mgmt = cmeWlanGetKeyMgmt();
            ret = 0;
        }
        break;
        case WLAN_GET_EXTERNAL:
        {
            WlanExternalApp_t *ext =  (WlanExternalApp_t *)params;
            ext->extP2P = isextP2P();
            ext->extWps = isextWPS();
            ext->extWpsDone = isextWPSDone();
            ext->extWpsInProgress = isextWPSInProgress();
			ret = 0;
        }
        break;
        case WLAN_GET_P2P_CONFIG_CHANNEL_PARAMS:
        {
            WlanP2pConfigChannelParam_t *pP2pConfigParam = (WlanP2pConfigChannelParam_t *)params;
            const P2pParameters_t *pP2pParameters;
            
            if(cfgGetP2pParameters(&pP2pParameters))
            {
                pP2pConfigParam->operChannel = pP2pParameters->p2pOperChannel;
                pP2pConfigParam->operClass = pP2pParameters->p2pOperRegClass;
                pP2pConfigParam->listenChannel = pP2pParameters->p2pListenChannel;
                pP2pConfigParam->listenClass = pP2pParameters->p2pListenRegClass;
                pP2pConfigParam->goIntent = pP2pParameters->p2pGoIntent;
                ret = 0;
            }
            else
            {
                ret = -1;
            }
        }
        break;
        case WLAN_GET_ANT_DIV_STATUS:
        {
            ret = ctrlCmdFw_GetAntennaStatus((uint8_t *)params);
        }
        break;
        case WLAN_GET_ANT_DIV_RSSI_THRESHOLD:
        {
            ret = ctrlCmdFw_GetAntennaRssiThreshold((int8_t *)params);
        }
        break;
        case WLAN_GET_DEFAULT_ANTENNA:
        {
            ret = ctrlCmdFw_GetDefaultAntenna((uint8_t*)params);
        }
        break;
        case WLAN_GET_HOST_VERSION:
        {
            wlanHostVersion_t *pWlanHostVersion = params;
            strncpy(pWlanHostVersion->pVersion, &version_upper_mac[VERSION_NUMBER_START_INDEX], UPPER_MAC_VERSION_MAX_SIZE);
            ret = 0;
        }
        break;
        
        case WLAN_GET_CSI:
        {
            WlanGetCSIData_t *csiData = (WlanGetCSIData_t *)params;
            ret = CSI_GetMessage(csiData);
        }
        break;
        default:
            return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__INVALID_PARAM_GET_TYPE);
		break;	
    }

    end:
        set_finish_wlan_get(wlanGetType);
        return ret;
}

int Wlan_Set(WlanSet_e wlanSetType, void *params)
{

    int32_t ret = 0;
    uint32_t role_bitmap;


    ret = set_cond_in_process_wlan_set(wlanSetType);
    if(ret != OSI_OK)
    {
        CME_PRINT_REPORT("\n\r ---Wlan_Set retry:%d---",(uint32_t) wlanSetType);
    	return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__RET_OPER_IN_PROGRESS);// not to go to fail in purpose
    }
    CME_PRINT_REPORT("\n\r ---Wlan_Set:%d--- \n\r",(uint32_t) wlanSetType);

    switch (wlanSetType)
    {
        case WLAN_SET_RESET_COUNTERS:
        {
            uint32_t role;
            COPY_WLAN_32BIT(&role, params);
            host_resetCounters(role,&g_stat_trnpt);
        }
        break;

        case WLAN_SET_MACADDRESS:
        {
            role_bitmap = CME_GetStartedRoleBitmap();

            WlanMacAddress_t *pMacParams = (WlanMacAddress_t *)params;

            if(WLAN_ROLE_STA == pMacParams->roleType &&
                    1 == (role_bitmap & BIT_x(ROLE_STA)))
            {
                ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__SET_MAC_ROLE_STA);
                break;
            }

            else if(WLAN_ROLE_AP == pMacParams->roleType &&
                    1 == (role_bitmap & BIT_x(ROLE_AP)))
            {
                ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__SET_MAC_ROLE_AP);
                break;
            }

            else if(WLAN_ROLE_P2P_GO == pMacParams->roleType &&
                    1 == (role_bitmap & BIT_x(ROLE_P2P_GO))) 
            {
                ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__SET_MAC_ROLE_P2P);;
                break;
            }

            else if(ROLE_DEVICE == pMacParams->roleType &&
                    1 == (role_bitmap & BIT_x(ROLE_DEVICE)))
            {
                ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__SET_MAC_ROLE_DEVICE);;
                break;
            }

            if( ret == 0 )
			{
            	ret = CME_SetMacAddress(pMacParams->roleType, pMacParams->pMacAddress);
			}

        }
        break;

        case WLAN_SET_POWER_SAVE:
        {
            ret = CME_WlanSetPSMode(*(unsigned char *)params);
        }
        break;

        case WLAN_SET_POWER_MANAGEMENT:
        {
            ret = ctrlCmdFw_SetSleepAuth(*(WlanPowerManagement_e *)params);
        }
        break;
#ifdef CC35XX
        case WLAN_SET_LSI:
        {
            ret = ctrlCmdFw_SetLSI(*(WlanLongSleepInterval *) params);  
        }
        break;
#endif

        case WLAN_SET_CALIBRATOR_CHANNEL_TUNE:
        case WLAN_SET_CALIBRATOR_TX_START:
        case WLAN_SET_CALIBRATOR_TX_STOP:
        case WLAN_SET_CALIBRATOR_START_RX:
        case WLAN_SET_CALIBRATOR_STOP_RX:
        case WLAN_SET_CALIBRATOR_TX_PARAMS:
        case WLAN_SET_CALIBRATOR_TB_TX_PARAMS:
        case WLAN_SET_CALIBRATOR_RATE_OVERRIDE:
        case WLAN_SET_CALIBRATOR_GI_LTF:
        case WLAN_SET_CALIBRATOR_UPLINK_MU:
        case WLAN_SET_CALIBRATOR_OPERATION_MODE_CONTROL:
        case WLAN_SET_CALIBRATOR_MCS_RATE:
        case WLAN_SET_CALIBRATOR_UPLINK_MU_DATA:
        case WLAN_SET_CALIBRATOR_PSM:
        case WLAN_SET_CALIBRATOR_UPLINK_POWER_HEADER:
        case WLAN_SET_CALIBRATOR_TRANSMIT_OSI:
        case WLAN_SET_CALIBRATOR_BA_SESSION:
        case WLAN_SET_CALIBRATOR_LINK_ADAPT:
        {
            CalibratorCommandWrapper_t *calibratorCommand = (CalibratorCommandWrapper_t *)params;
            ret = ctrlCmdFw_CalibratorCommand(calibratorCommand->calibratorAction, calibratorCommand->calibratorCommandParams);
        }
        break;

        case WLAN_SET_VENDOR_IE:
        {
            ret = ctrlCmdFw_SetVendorIE((wlanSetVendorInfo_t *)params);
        }
        break;
        case WLAN_SET_RESET_DECRYPT_PACKETS_COUNT:
        {
            ret = ctrlCmdFw_ResetDecryptedPacketsCounter(params);
        }
        break;
        case WLAN_SET_ENABLE_CHANNEL_UTILIZATION_NEXT_SCAN:
        {
             ret = ctrlCmdFw_EnableChannelUtilization();
        }
        break;
        case WLAN_SET_TX_CTRL:
        {
            /*
            WlanCtrlBlk_t *pCtrlBlk =  (WlanCtrlBlk_t *)params;
            txCtrl_t *pTxCtrl;
            pTxCtrl = os_malloc(sizeof(txCtrl_t));
            pTxCtrl->pUdata = os_malloc(sizeof(TUdata));

            pTxCtrl->pUdata->udataparams.TxSendPaceThresh = pCtrlBlk->TxSendPaceThresh;
            pTxCtrl->pUdata->udataparams.TxSendPaceTimeoutMsec = pCtrlBlk->TxSendPaceTimeoutMsec;
            pTxCtrl->tBackpressure.TransmitQOnTxComplete = pCtrlBlk->TransmitQOnTxComplete;

            txCtrlBlk_Set(pTxCtrl);
            os_free(pTxCtrl->pUdata);
            os_free(pTxCtrl);
            */
        }
        break;

        case WLAN_SET_EXTERNAL:
        {
            WlanExternalApp_t *ext =  (WlanExternalApp_t *)params;
            set_extP2P(ext->extP2P);
            set_extWPS(ext->extWps);
            set_extWPSDone(ext->extWpsDone);
        }
        break;
        case WLAN_SET_EXT_P2P_BUILD_ACTION_FRAME:
        {
            WlanBuildActionBuffer_t* pActionBuff = (WlanBuildActionBuffer_t *)params;
            switch( pActionBuff->msgType)
            {
                case WLAN_P2P_PROV_DISC_RESP:
                    CME_WlanExtP2pProcessProvDiscActionMsg(&pActionBuff->actionParam, 1);
                    break;
                case WLAN_P2P_DEV_DISC_REQ :
                case WLAN_P2P_PROV_DISC_REQ:
                case WLAN_P2P_DEV_DISC_RESP:
                    break;
                default:
                    break;
            }
        }
        break;

        case WLAN_SET_EXT_OFFCHANNEL_ROC:
        {

            WlanROCExt_t* pROC = (WlanROCExt_t *)params;
        	uint32_t is_croc_performed_due_to_timeout =0;

            if(pROC->enableROC)
            {
                ret = ti_driver_ext_set_ROC(pROC->channel, pROC->countryDomain);
            }
            else
            {
                ret  = ti_driver_ext_set_CROC(0,is_croc_performed_due_to_timeout);
            }

        }
        break;

		case WLAN_SET_EXT_OFFCHANNEL_SEND_RAW_ACTION:
        {
            WlanActionTxExt_t* pAction = (WlanActionTxExt_t *)params;
            ret =  ti_driver_ext_tx_send_action(
                        pAction->apDst, // Destination address
                        pAction->actionBuff.pBuff,
                        pAction->actionBuff.bufLen);
        }
        break;

		case WLAN_SET_EXT_WPS_SESSION:
        {
            wlanSetExtWpsSession_t *wpsParams = (wlanSetExtWpsSession_t *)params;
            ret = CME_SetExtWpsSession(wpsParams);
        }
        break;
        
	    case WLAN_SET_EXTENDED_SCAN_RESULTS:
	    {
	        scanResultTable_GetCmeScanDbPointer()->extendedScanResults = *((uint8_t *)params);
	    }
	    break;

        case WLAN_SET_STA_WIFI_BAND:
        {
            scanResultTable_GetCmeScanDbPointer()->wifi_band_cfg = *(uint8_t *)params;
            l2_StorePhyConfig(scanResultTable_GetCmeScanDbPointer()->wifi_band_cfg);
        }
        break;

	    case WLAN_SET_CSI:
	    {
	        WlanSetCSIParams_t csiParams;
	        BOOLEAN csi_enable = *(BOOLEAN *)params;
	        if (csi_enable)
	        {
	            csiParams.blocking = TRUE;
	            csiParams.queueSize = 50;
	            ret = CSI_Init(&csiParams);
	            if (ret == 0)
	            {
	                // Send command to FW
	                ret = ctrlCmdFw_EnableCsiCmd(TRUE);
	            }
	        }
	        else
	        {
	           // Send command to FW
	           ret = ctrlCmdFw_EnableCsiCmd(FALSE);
	           CSI_Deinit();
	        }
	    }
	    break;

		case WLAN_SET_BLE_ENABLE:
	    {
	        ret = CME_SetBLE_Enable();
	    }
	    break;

        case WLAN_SET_P2P_CMD:
        {
            WlanP2pCmd_t *pP2pCmdParam = (WlanP2pCmd_t *)params;
            
            ret = CME_SetP2pCmd(params);
        }
        break;

        case WLAN_SET_SCAN_RESULTS_SIZE:
        {
            scanResultTable_GetCmeScanDbPointer()->mNumDigestResultsMax = *(uint16_t *)params;
	    }
	    break;
        
        case WLAN_SET_NON_PREFFERED_CHANNELS:
        {
            WlanNonPrefChannels_t *pNonPrefChannels = (WlanNonPrefChannels_t *)params;
            
            ret = CME_SetNonPrefferedChannels(pNonPrefChannels);
        }
        break;

        case WLAN_SET_ENABLE_ANT_DIV:
        {
            ret = ctrlCmdFw_SetAntennaStatus(*(uint8_t *)params);
        }
        break;

        case WLAN_SET_ANT_DIV_RSSI_THRESHOLD:
        {
            ret = ctrlCmdFw_SetAntennaRssiThreshold(*(int8_t *)params);
        }
        break;

        case WLAN_SET_SELECT_DEFAULT_ANTENNA:
        {
            ret = ctrlCmdFw_SelectDefaultAntenna(*(uint8_t *)params);
        }
        break;

        case WLAN_SET_TRIGGER_FW_ASSERT:
        {
            ret = ctrlCmdFw_TriggerFwAssert();
        }
        break;

        case WLAN_SET_PSD_METHOD:
        {
            PSScheme_e psScheme = *(uint8_t*)params;

            // use legacy mode as default configuration
            AcPsMode_t acPsMode =
            {
                .wmeAcPsMode[AC_BE] = PS_SCHEME_LEGACY,
                .wmeAcPsMode[AC_BK] = PS_SCHEME_LEGACY,
                .wmeAcPsMode[AC_VI] = PS_SCHEME_LEGACY,
                .wmeAcPsMode[AC_VO] = PS_SCHEME_LEGACY
            };

            if (PS_SCHEME_UPSD_TRIGGER == psScheme)
            {
                acPsMode.wmeAcPsMode[AC_BE] = PS_SCHEME_UPSD_TRIGGER;
                acPsMode.wmeAcPsMode[AC_BK] = PS_SCHEME_UPSD_TRIGGER;
                acPsMode.wmeAcPsMode[AC_VI] = PS_SCHEME_UPSD_TRIGGER;
                acPsMode.wmeAcPsMode[AC_VO] = PS_SCHEME_UPSD_TRIGGER;
            }
            else if (PS_SCHEME_MIXED_MODE == psScheme)
            {
                acPsMode.wmeAcPsMode[AC_BE] = PS_SCHEME_LEGACY;
                acPsMode.wmeAcPsMode[AC_BK] = PS_SCHEME_LEGACY;
                acPsMode.wmeAcPsMode[AC_VI] = PS_SCHEME_UPSD_TRIGGER;
                acPsMode.wmeAcPsMode[AC_VO] = PS_SCHEME_UPSD_TRIGGER;
            }
            
            l2_cfg_Dynamic_set(L2_AC_PS_MODE, (uint8_t *)&acPsMode);
        }
        break;

        default:
            ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
            break;
    }

end:
    set_finish_wlan_set(wlanSetType);
    return ret;

}


// ============================================================================
//      Event Function
// ============================================================================
int wlanDispatcherSendEvent(uint16_t opcode, uint8_t *args, uint16_t argsLen)
{
    WlanEvent_t *pWlanEvent;
    pWlanEvent = os_zalloc(sizeof(WlanEvent_t));

    if (!pWlanEvent)
    {
        TX_DATA_SEND_PRINT_ERROR("\n\r[dispatcherSendEvent] ERROR NULL buffer,opcode:%d\n\r",opcode);
        return WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__FW_RESPONSE_NULL_BUF);
    }
    pWlanEvent->Id = opcode;
    switch (opcode)
    {
        case WLAN_EVENT_CONNECT:
        {
            set_finish_wlan_connect();
            os_memcpy((void *)&pWlanEvent->Data.Connect, args, sizeof(WlanEventConnect_t));
        }
        break;
        case WLAN_EVENT_DISCONNECT:
        {
            set_finish_wlan_disconnect();
            os_memcpy((void *)&pWlanEvent->Data.Disconnect, args, sizeof(WlanEventDisconnect_t));
        }
        break;
        case WLAN_EVENT_SCAN_RESULT:
        {
        	set_finish_wlan_survey_scan();
            if (argsLen > WLAN_MAX_SCAN_COUNT)
            {
                argsLen = WLAN_MAX_SCAN_COUNT;
            }
            pWlanEvent->Data.ScanResult.NetworkListResultLen = argsLen;
            os_memcpy((void *)&pWlanEvent->Data.ScanResult.NetworkListResult, args, sizeof(WlanNetworkEntry_t) * argsLen);
        }
        break;
        case WLAN_EVENT_EXTENDED_SCAN_RESULT:
        {
        	set_finish_wlan_survey_scan();
            if (argsLen > WLAN_EXTENDED_MAX_SCAN_COUNT)
            {
                argsLen = WLAN_EXTENDED_MAX_SCAN_COUNT;
            }
            pWlanEvent->Data.pExtendedScanResult = os_malloc(sizeof(WlanEventExtendedScanResult_t));//Memory allocation is needed because ExtendedScanResult is a pointer.
            pWlanEvent->Data.pExtendedScanResult->NetworkListResultLen = argsLen;
            if(argsLen > 0)
            {
                pWlanEvent->Data.pExtendedScanResult->NetworkListResult = os_malloc(sizeof(WlanNetworkEntryExtended_t) * argsLen);
                os_memcpy((void *)pWlanEvent->Data.pExtendedScanResult->NetworkListResult, args, sizeof(WlanNetworkEntryExtended_t) * argsLen);
            }
        }
        break;
        case WLAN_EVENT_ADD_PEER:
        {
            os_memcpy((void *)&pWlanEvent->Data.AddPeer, args, sizeof(WlanEventSTAAdded_t));
        }
        break;
        case WLAN_EVENT_REMOVE_PEER:
        {
            os_memcpy((void*)pWlanEvent->Data.RemovePeer.Mac, args, sizeof(pWlanEvent->Data.RemovePeer.Mac));
        }
        break;
        case WLAN_EVENT_CONNECTING:
        {
            os_memcpy((void *)&pWlanEvent->Data.Connecting, args, sizeof(WlanEventConnecting_t));
        }
        break;
        case WLAN_EVENT_ACTION_FRAME_RX://only for cc33xx
        {
            os_memcpy((void *)&pWlanEvent->Data.WfdActionFrame, args, sizeof(WlanEvenWfdMgmtFrame_t));
        }
        break;
        case WLAN_EVENT_ASSOCIATED:
        {
            os_memcpy((void *)&pWlanEvent->Data.Associated, args, sizeof(WlanEventAssociated_t));
        }
        break;
        
        case WLAN_EVENT_AP_EXT_WPS_SETTING_FAILED:
        {
            os_memcpy((void *)&pWlanEvent->Data.wpsFailCode, args, sizeof(int8_t));
        }
        break;
        case WLAN_EVENT_BLE_ENABLED:
        {
            os_memcpy((void *)&pWlanEvent->Data.bleEnableStatus, args, sizeof(int32_t));
        }
        break;
        case WLAN_EVENT_CS_FINISH:
        {
            os_memcpy((void *)&pWlanEvent->Data.newChannel, args, sizeof(uint8));
        }
        break;
        case WLAN_EVENT_CROC_DONE:
        	pWlanEvent->Data.dppCROCevenReasonTimeout = *((uint32_t *)args);
        	break;
        case WLAN_EVENT_ROC_DONE:
        case WLAN_EVENT_SEND_ACTION_DONE:
        {
            //no argument
        }
        break;
        case WLAN_EVENT_P2P_GROUP_STARTED:
        {
            os_memcpy((void *)&pWlanEvent->Data.FormationComplete, args, sizeof(WlanEventFormationComplete_t));
        }
        break;
        case WLAN_EVENT_P2P_GROUP_REMOVED:
        {
            os_memcpy((void *)&pWlanEvent->Data.GroupRemoved, args, sizeof(WlanEventGroupRemoved_t));
        }
        break;
#ifdef CC35XX
        case WLAN_EVENT_P2P_SCAN_COMPLETED:
        {
            //only if we are waiting for this syncObj
            if (g_wait_p2p_scan_complete)
            {
                g_wait_p2p_scan_complete = FALSE;
                Report("\n\rP2P Scan completed event arrived\n");
                osi_SyncObjSignal(&p2p_find_stopped_syncObj);
            }
        }
        break;
#endif
        case WLAN_EVENT_CONNECT_PERIODIC_SCAN_COMPLETE:
        case WLAN_EVENT_FW_CRASH:
        case WLAN_EVENT_BSS_TRANSITION_INITIATED:
        {
            //no argument
        }
        break;
        default:
        {
            Report("\n\r[WLAN EVENT] Unexpected event [0x%x]\n\r", opcode);
        }
        break;
    }
    // call to event handler
    gRoleAppsParams.eventHandlerCB(pWlanEvent);

    if (WLAN_EVENT_EXTENDED_SCAN_RESULT == opcode)
    {
        if(argsLen > 0)
        {
            os_free(pWlanEvent->Data.pExtendedScanResult->NetworkListResult);
            pWlanEvent->Data.pExtendedScanResult->NetworkListResult = NULL;
        }
        os_free(pWlanEvent->Data.pExtendedScanResult);
        pWlanEvent->Data.pExtendedScanResult = NULL;
    }
    os_free(pWlanEvent);
    return 0;
}


int roleUp_Inter(WlanRole_e roleType, void *params, unsigned long int timeout)
{
    int ret = 0;
    uint32_t role_bitmap;


    CME_PRINT_REPORT("\n\r ---Wlan_RoleUp internal--- %d",roleType);

    HOOK(HOOK_WLAN_IF);

#ifdef TODO //TODO isri wlan_GetStateWlan
    if (wlan_GetStateWlan() == DEVICE_OFF)
    {
        //  Device is turn off
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__ROLE_IS_NOT_UP);
        goto fail;
    }
#endif

    role_bitmap = CME_GetStartedRoleBitmap();

    /* If transceiver role is active, don't allow starting any other role */
    if ((role_bitmap & BIT_x(ROLE_TRANSCEIVER)) > 0)
    {
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__ROLE_TRANCIEVER_IS_UP);
        goto fail;
    }

    if (ROLE_IS_TYPE_STA(roleType))
    {
        if (NULL != params)
        {
            RoleUpApCmd_t *domainParams = (RoleUpApCmd_t *)params;
            regulatoryDomain_SetCountry(domainParams->countryDomain);
            regulatoryDomain_SetChannels();
            CME_SetStaParams(params);
        }

        role_bitmap |= (uint32_t)BIT_x(ROLE_STA);
    }
    else if (ROLE_IS_TYPE_AP(roleType))
    {
        if (NULL != params)
        {
            RoleUpApCmd_t *domainParams = (RoleUpApCmd_t *)params;
            if (domainParams->countryDomain[0] != '\0')
            {
                regulatoryDomain_SetCountry(domainParams->countryDomain);
            }
        }

        CME_SetApParams(params);

        role_bitmap |= (uint32_t)BIT_x(ROLE_AP);

    }
    else if (ROLE_IS_TYPE_TRANSCEIVER(roleType))
    {
        /* If any other role is active, don't allow using PLT */
        if (role_bitmap != 0)
        {
            GTRACE(GRP_DRIVER_CC33,"Can't enable calibrator when any other role is up!\r\n");
            Report("\n\rCan't enable calibrator when any other role is up!\r\n");
            ret =  WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__OTHER_ROLE_IS_UP);
            goto fail;
        }

        ret = ctrlCmdFw_pltInit();
        if (ret < 0)
        {
            goto fail;
        }
        role_bitmap |= (uint32_t)BIT_x(ROLE_TRANSCEIVER);

        CME_SetStartedRoleBitmap(role_bitmap);

    }
    else if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        GTRACE(GRP_DRIVER_CC33,"CME: Role UP DEVICE");
        if (NULL != params)
        {
            CME_SetStaParams(params);
        }

        role_bitmap |= (uint32_t)BIT_x(ROLE_DEVICE);
    }
    else
    {
        Report("\n\rERROR! role not supported roleType:%d" , roleType);
        GTRACE(GRP_DRIVER_CC33,"ERROR! role not supported roleType:%d" , roleType);
        ret =  WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__ROLE_NOT_SUPPORTED);;
        goto fail;
    }

    ret = CME_WlanSetMode(0,role_bitmap, (uint32_t)timeout, 0);

    if (ret < 0)
    {
        goto fail;
    }

    return ret;
fail:
    return ret;
}

int roleDown_inter(WlanRole_e roleType, unsigned long int timeout)
{
    uint32_t role_bitmap;
    int32_t ret = 0;

    HOOK(HOOK_WLAN_IF);

    CME_PRINT_REPORT("\n\r ---Wlan_RoleDown_internal--- %d",roleType);

    role_bitmap = CME_GetStartedRoleBitmap();

    if (ROLE_IS_TYPE_STA(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_STA);

        ret = CME_WlanSetMode(0,role_bitmap, timeout, 0);
    }
    else if (ROLE_IS_TYPE_AP(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_AP);

        ret = CME_WlanSetMode(0,role_bitmap, timeout, 0);
    }
    else if (ROLE_IS_TYPE_TRANSCEIVER(roleType))
    {
        if (0 == (role_bitmap & BIT_x(ROLE_TRANSCEIVER)))
        {
            ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__ROLE_IS_NOT_UP);
            goto fail;
        }

        ret = ctrlCmdFw_pltStop();
        if (ret < 0)
        {
            goto fail;
        }

        role_bitmap &= ~(uint32_t)BIT_x(ROLE_TRANSCEIVER);

        CME_SetStartedRoleBitmap(role_bitmap);
        role_bitmap = CME_GetStartedRoleBitmap();
    }
    else if (ROLE_IS_TYPE_DEVICE(roleType))
    {
        role_bitmap &= ~(uint32_t)BIT_x(ROLE_DEVICE);

        ret = CME_WlanSetMode(0,role_bitmap, timeout, 0);
        if (ret < 0)
        {
            goto fail;
        }
    }
    HOOK(HOOK_WLAN_IF);
    CME_PRINT_REPORT("\r\nWlan_RoleDown internal, for role :%d complete\n\r",roleType);

    return ret;

    fail:
        CME_PRINT_REPORT("\r\nWlan_RoleDown internal, for role :%d complete with fail\n\r",roleType);
        return ret;
}


// ============================================================================
//      Unit testing
// ============================================================================
#ifdef EVENT_TEST
// test event handler
void testEventHandler(uint16_t opcode)
{
    int i;
    HOOK(HOOK_WLAN_IF);

    switch (opcode)
    {
    case WLAN_EVENT_CONNECT:
    {
        WlanEventConnect_t *args;
        args = (WlanEventConnect_t *)os_zalloc(sizeof(WlanEventConnect_t));
        args->Bssid[0] = '\x8c';
        args->Bssid[1] = 'S';
        args->Bssid[2] = '\xc3';
        args->Bssid[3] = '\xee';
        args->Bssid[4] = '\xd9';
        args->Bssid[5] = '\xea';
        args->Channel = '\x01';
        args->SsidLen = '\x05';
        args->SsidName[0] = 't';
        args->SsidName[1] = 'e';
        args->SsidName[2] = 's';
        args->SsidName[3] = 't';
        args->SsidName[4] = '0';

        wlanDispatcherSendEvent(WLAN_EVENT_CONNECT, (uint8_t *)args, sizeof(WlanEventConnect_t));
        os_free(args);
    }
    break;
    case WLAN_EVENT_DISCONNECT:
    {
        WlanEventDisconnect_t *args;
        args = (WlanEventDisconnect_t *)os_zalloc(sizeof(WlanEventDisconnect_t));
        args->Bssid[0] = '\x8c';
        args->Bssid[1] = 'S';
        args->Bssid[2] = '\xc3';
        args->Bssid[3] = '\xee';
        args->Bssid[4] = '\xd9';
        args->Bssid[5] = '\xea';
        args->ReasonCode = 200;
        args->SsidLen = '\x05';
        args->SsidName[0] = 't';
        args->SsidName[1] = 'e';
        args->SsidName[2] = 's';
        args->SsidName[3] = 't';
        args->SsidName[4] = '0';

        args->IsStaIsDiscnctInitiator = 0;
        wlanDispatcherSendEvent(WLAN_EVENT_DISCONNECT, (uint8_t *)args, sizeof(WlanEventDisconnect_t));
        os_free(args);
    }
    break;

    case WLAN_EVENT_SCAN_RESULT:
    {
        WlanEventScanResult_t args;
        args.NetworkListResultLen = 2;
        args.NetworkListResult = os_malloc(args.NetworkListResultLen * sizeof(WlanNetworkEntry_t));
        WlanNetworkEntry_t netEntry;
        for (i = 0; i < args.NetworkListResultLen; ++i)
        {
            args.NetworkListResult[i].Bssid[0] = '\x8c';
            args.NetworkListResult[i].Bssid[1] = 'S';
            args.NetworkListResult[i].Bssid[2] = '\xc3';
            args.NetworkListResult[i].Bssid[3] = '\xee';
            args.NetworkListResult[i].Bssid[4] = '\xd9';
            args.NetworkListResult[i].Bssid[5] = '\xea';

            args.NetworkListResult[i].Ssid[0] = 't';
            args.NetworkListResult[i].Ssid[1] = 'e';
            args.NetworkListResult[i].Ssid[2] = 's';
            args.NetworkListResult[i].Ssid[3] = 't';
            args.NetworkListResult[i].Ssid[4] = i + '0';

            args.NetworkListResult[i].SsidLen = '\x05';
            args.NetworkListResult[i].Rssi = '\xde';
            args.NetworkListResult[i].SecurityInfo = 5828;
            args.NetworkListResult[i].Channel = '\0x01';
            args.NetworkListResult[i].Reserved[0] = '\0x00';
        }

        wlanDispatcherSendEvent(WLAN_EVENT_SCAN_RESULT, (uint8_t *)&args, sizeof(WlanEventScanResult_t));
        os_free(args.NetworkListResult);
    }
    break;

    default:
        break;
    }
}
#endif /* EVENT_TEST */

#endif /* USER_INTEFACE_WLAN_IF_C_ */
