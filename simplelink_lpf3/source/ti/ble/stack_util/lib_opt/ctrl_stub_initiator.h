/******************************************************************************

 @file  ctrl_stub_initiator.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_initiator.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_INITIATOR_H_
#define CTRL_INITIATOR_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_ble.h"
#include "ti/ble/controller/ll/ll_scheduler.h"
#include "ti/ble/controller/ll/ll.h"
#include "ti/ble/controller/hci/hci.h"

// Function prototypes for the actual implementations
extern void llProcessCentralConnectionCreated(void);
extern void llProcessCentralControlPacket(llConnState_t* connPtr, uint8_t* pPkt);
extern void llSetTaskInit(uint8_t startType, taskInfo_t* nextSecTask, void* nextSecCmd, void* nextConnCmd);
extern void llSetTaskCentral(uint8_t connId, void* nextConnCmd);
extern taskInfo_t* llSelectTaskInit(uint8_t secTaskID, uint32_t timeGap);
extern llStatus_t LL_ChanMapUpdate(uint8_t* chanMap, uint16_t connID);
extern void llCentral_TaskEnd(void);
extern void llExtInit_PostProcess(void);
extern llStatus_t LL_CreateConnCancel(void);
extern void LL_SetConnIdInExtInit(uint8_t connId);
extern void llPostSetupCtrlPktCent(llConnState_t* connPtr, uint8_t ctrlPkt);
extern hciStatus_t hciCmdParserInitiator(uint8_t* pData, uint16_t cmdOpCode);
extern llStatus_t HCI_TL_create_conn(uint16_t opcode, uint8_t* pHciParams);
extern llStatus_t HCI_TL_ext_create_conn(uint16_t opcode, uint8_t* pHciParams);
extern hciStatus_t hciCmdParserVendorSpecificInitiator(uint8_t* pData, uint16_t cmdOpCode);
extern void LL_rclInitRxEntryDone(void);
extern void llInit_TaskConnect(void);
extern void llExtInit_ResolveConnRsp(void);
extern void llBuildCtrlPktCent(llConnState_t* connPtr, uint8_t* pData, uint8_t ctrlPkt);
extern void llCmdScanStartedEventHandle(void);
extern uint8_t llIsInitPriorityValid(uint16_t taskID, uint8_t priority, uint8_t connPriority);
extern llStatus_t llAllocExtInitInfo(void);
extern void llSecTaskInitiatorHandle(taskInfo_t* secTask, RCL_Command* secCmd, llConnState_t* nextConnPtr, uint32_t* timeGap, uint32_t curTime);
extern void llUpdateTimeGapForInitiator(uint32_t* timeGap);
extern uint8_t llChackInitiatorUseAcceptList(void);
extern uint8_t llCheckInitHealth(volatile uint32_t* initTime, volatile uint32_t* currentTime);
extern uint8_t LL_IsInitiatingWithRandomAddress(void);
extern void LL_UpdateInitiatorInfoScanValue(uint16_t scaInPPM);
extern void LL_DisableScanningForInitiator(void);
extern uint8_t LL_validateChannelMap(uint8_t* chanMap);
extern RCL_Callback LL_GetRfCentralCallback(void);
extern void LL_InitiatorReadSupportedStates(uint8_t* states);
extern uint8_t LL_PRIV_ValidatePeerAddress(uint8_t* peerAddr, uint8_t peerAddrType, uint8_t peerRLIndex);

// Wrapper functions for the feature implementations
void OPT_llProcessCentralConnectionCreated(void);
void OPT_llProcessCentralControlPacket(llConnState_t* connPtr, uint8_t* pPkt);
void OPT_llSetTaskInit(uint8_t startType, taskInfo_t* nextSecTask, void* nextSecCmd, void* nextConnCmd);
void OPT_llSetTaskCentral(uint8_t connId, void* nextConnCmd);
taskInfo_t* OPT_llSelectTaskInit(uint8_t secTaskID, uint32_t timeGap);
llStatus_t OPT_LL_ChanMapUpdate(uint8_t* chanMap, uint16_t connID);
void OPT_llCentral_TaskEnd(void);
void OPT_llExtInit_PostProcess(void);
llStatus_t OPT_LL_CreateConnCancel(void);
void OPT_LL_SetConnIdInExtInit(uint8_t connId);
void OPT_llPostSetupCtrlPktCent(llConnState_t* connPtr, uint8_t ctrlPkt);
hciStatus_t OPT_hciCmdParserInitiator(uint8_t* pData, uint16_t cmdOpCode);
llStatus_t OPT_HCI_TL_create_conn(uint16_t opcode, uint8_t* pHciParams);
llStatus_t OPT_HCI_TL_ext_create_conn(uint16_t opcode, uint8_t* pHciParams);
hciStatus_t OPT_hciCmdParserVendorSpecificInitiator(uint8_t* pData, uint16_t cmdOpCode);
void OPT_LL_rclInitRxEntryDone(void);
void OPT_llInit_TaskConnect(void);
void OPT_llExtInit_ResolveConnRsp(void);
void OPT_llBuildCtrlPktCent(llConnState_t* connPtr, uint8_t* pData, uint8_t ctrlPkt);
void OPT_llCmdScanStartedEventHandle(void);
uint8_t OPT_llIsInitPriorityValid(uint16_t taskID, uint8_t priority, uint8_t connPriority);
llStatus_t OPT_llAllocExtInitInfo(void);
void OPT_llSecTaskInitiatorHandle(taskInfo_t* secTask, RCL_Command* secCmd, llConnState_t* nextConnPtr, uint32_t* timeGap, uint32_t curTime);
void OPT_llUpdateTimeGapForInitiator(uint32_t* timeGap);
uint8_t OPT_llChackInitiatorUseAcceptList(void);
uint8_t OPT_llCheckInitHealth(volatile uint32_t* initTime, volatile uint32_t* currentTime);
uint8_t OPT_LL_IsInitiatingWithRandomAddress(void);
void OPT_LL_UpdateInitiatorInfoScanValue(uint16_t scaInPPM);
void OPT_LL_DisableScanningForInitiator(void);
uint8_t OPT_LL_validateChannelMap(uint8_t* chanMap);
RCL_Callback OPT_LL_GetRfCentralCallback(void);
void OPT_LL_InitiatorReadSupportedStates(uint8_t* states);
uint8_t OPT_LL_PRIV_ValidatePeerAddress(uint8_t* peerAddr, uint8_t peerAddrType, uint8_t peerRLIndex);

#endif /* CTRL_INITIATOR_H_ */
