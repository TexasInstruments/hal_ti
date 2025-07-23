/******************************************************************************

 @file  ctrl_stub_connectable.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_connectable.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_CONNECTABLE_H_
#define CTRL_CONNECTABLE_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_ble.h"
#include "ti/ble/controller/ll/ll_scheduler.h"
#include "ti/ble/controller/ll/ll.h"
#include "ti/ble/controller/hci/hci.h"
#include "ti/ble/controller/ll/ll_enc.h"

// Function prototypes for the actual implementations
extern llStatus_t LL_ConnActive(uint16_t connId);
extern uint8_t llGetNextConn(void);
extern llConnState_t* llDataGetConnPtr(uint8_t connId);
extern uint8 llConnExists(uint8_t* peerAddr, uint8_t peerAddrType);
extern hciStatus_t hciCmdParserConnection(uint8_t* pData, uint16_t cmdOpCode);
extern hciStatus_t hciCmdParserVendorSpecificConnection(uint8_t* pData, uint16_t cmdOpCode);
extern uint8_t llRxEntryDoneEventHandleStateConnection(void);
extern void llProcessTxData(void);
extern void LL_RxDataCompleteCback(uint16_t connHandle, uint8_t* pBuf, uint16_t len, uint8_t fragFlag, int8_t rssi);
extern uint8_t llCheckConnHealth(uint32_t* currentTime, volatile uint32_t* connTime);
extern llStatus_t llDynamicAlloc_connectable(void);
extern void llDynamicFree_connectable(void);
extern void llChannelAlgo2SetFeatureBit(void);
extern void llSchedulerConnectable(taskInfo_t* curTask);
extern uint8_t llSchedulerSecondaryTasksConn(taskInfo_t* nextSecTask, void* nextSecCmd);
extern uint32_t llHandleConnDisconnectedImmed(uint32_t events);
extern void LL_clearAllActiveConns(void);
extern void LL_setComplPktsDefualtValues(void);
extern void LL_GetNumActiveConns(uint8_t* numActiveConns);
extern void HCI_TL_SendDataPkt(uint8_t* pMsg);
extern llStatus_t LL_RemoteConnParamReqReply(uint16_t connHandle, uint16_t connIntervalMin, uint16_t connIntervalMax, uint16_t connLatency, uint16_t connTimeout, uint16_t minLen, uint16_t maxLen);
extern void ll_eccInit(void);
extern void llsdaaEnableConnTXData(uint16_t currConnId);
extern void llsdaaDisableConnTXData(uint16_t connId);
extern void llConnSetRejectIndExt(llConnState_t * connPtr, uint8 rejectOpcode, uint8 errorCode);
extern void LL_GetConnTxUsageParams(llTxUsageParams_t* pConnTxParams);

// Wrapper functions for the feature implementations
llStatus_t OPT_LL_ConnActive(uint16_t connId);
uint8_t OPT_llGetNextConn(void);
llConnState_t* OPT_llDataGetConnPtr(uint8_t connId);
uint8 OPT_llConnExists(uint8_t* peerAddr, uint8_t peerAddrType);
hciStatus_t OPT_hciCmdParserConnection(uint8_t* pData, uint16_t cmdOpCode);
hciStatus_t OPT_hciCmdParserVendorSpecificConnection(uint8_t* pData, uint16_t cmdOpCode);
uint8_t OPT_llRxEntryDoneEventHandleStateConnection(void);
void OPT_llProcessTxData(void);
void OPT_LL_RxDataCompleteCback(uint16_t connHandle, uint8_t* pBuf, uint16_t len, uint8_t fragFlag, int8_t rssi);
uint8_t OPT_llCheckConnHealth(uint32_t* currentTime, volatile uint32_t* connTime);
llStatus_t OPT_llDynamicAlloc_connectable(void);
void OPT_llDynamicFree_connectable(void);
void OPT_llChannelAlgo2SetFeatureBit(void);
void OPT_llSchedulerConnectable(taskInfo_t* curTask);
uint8_t OPT_llSchedulerSecondaryTasksConn(taskInfo_t* nextSecTask, void* nextSecCmd);
uint32_t OPT_llHandleConnDisconnectedImmed(uint32_t events);
void OPT_LL_clearAllActiveConns(void);
void OPT_LL_setComplPktsDefualtValues(void);
void OPT_LL_GetNumActiveConns(uint8_t* numActiveConns);
void OPT_HCI_TL_SendDataPkt(uint8_t* pMsg);
llStatus_t OPT_LL_RemoteConnParamReqReply(uint16_t connHandle, uint16_t connIntervalMin, uint16_t connIntervalMax, uint16_t connLatency, uint16_t connTimeout, uint16_t minLen, uint16_t maxLen);
void OPT_ll_eccInit(void);
void OPT_llsdaaEnableConnTXData(uint16_t currConnId);
void OPT_llsdaaDisableConnTXData(uint16_t connId);
void OPT_llConnSetRejectIndExt(llConnState_t * connPtr, uint8 rejectOpcode, uint8 errorCode);
void OPT_LL_GetConnTxUsageParams(llTxUsageParams_t* pConnTxParams);

#endif /* CTRL_CONNECTABLE_H_ */
