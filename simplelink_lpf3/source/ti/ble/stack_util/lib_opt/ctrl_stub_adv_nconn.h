/******************************************************************************

 @file  ctrl_stub_adv_nconn.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_adv_nconn.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_ADV_NCONN_H_
#define CTRL_ADV_NCONN_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_ble.h"
#include "ti/ble/controller/ll/ll_ae.h"
#include "ti/ble/controller/hci/hci.h"

// Function prototypes for the actual implementations
extern void llProcessAdvAddrResolutionTimeout(void);
extern void llSetTaskAdv(uint8_t startType, void* nextSecCmd);
extern taskInfo_t* llSelectTaskAdv(uint8_t secTaskID, uint32_t timeGap);
extern llStatus_t LL_ClearAdvSets(void);
extern uint8_t LL_CountAdvSets(uint8_t type);
extern advSet_t* LL_GetAdvSet(uint8_t handle, uint8_t allocFlag);
extern llStatus_t LL_SetSecAdvChanMap(uint8_t* chanMap);
extern void llExtAdv_PostProcess(void);
extern hciStatus_t hciCmdParserAdvertiser(uint8_t* pData, uint16_t cmdOpCode);
extern hciStatus_t hciCmdParserVendorSpecificBroadcaster(uint8_t* pData, uint16_t cmdOpCode);
extern void LL_rclAdvRxEntryDone(void);
extern uint8_t LL_IsAdvertizeWithRandomAddress(void);
extern void LL_UpdateAdvSCAValue(uint16_t scaInPPM);
extern uint8_t llCheckAdvEvtType(uint8_t advEvtType);
extern uint8_t llHandoverDisableAdv(uint8_t advHandle);
extern uint8_t llCheckAdvHealth(uint32_t* currentTime, volatile uint32_t* advTime);
extern void* llFindNextAdvSet(void);
extern void LL_DisableAdvSets(void);
extern uint8_t llCmDisableCurAdv(void);
extern uint8_t llCompareSecondaryPrimaryTasksQoSParam_adv(llConnState_t* primConnPtr);
extern void llSelectTasksetTimeGapForAdv(uint32_t* timeGap);
extern void llFreeTaskAdv(void);
extern void llCalculateAdvTimeGap(uint32_t* timeGap);
extern void hci_tl_ClearAdvSet(void);
extern uint8_t processAdvExtraHCICmd(hciPacket_t* pMsg);

// Wrapper functions for the feature implementations
void OPT_llProcessAdvAddrResolutionTimeout(void);
void OPT_llSetTaskAdv(uint8_t startType, void* nextSecCmd);
taskInfo_t* OPT_llSelectTaskAdv(uint8_t secTaskID, uint32_t timeGap);
llStatus_t OPT_LL_ClearAdvSets(void);
uint8_t OPT_LL_CountAdvSets(uint8_t type);
advSet_t* OPT_LL_GetAdvSet(uint8_t handle, uint8_t allocFlag);
llStatus_t OPT_LL_SetSecAdvChanMap(uint8_t* chanMap);
void OPT_llExtAdv_PostProcess(void);
hciStatus_t OPT_hciCmdParserAdvertiser(uint8_t* pData, uint16_t cmdOpCode);
hciStatus_t OPT_hciCmdParserVendorSpecificBroadcaster(uint8_t* pData, uint16_t cmdOpCode);
void OPT_LL_rclAdvRxEntryDone(void);
uint8_t OPT_LL_IsAdvertizeWithRandomAddress(void);
void OPT_LL_UpdateAdvSCAValue(uint16_t scaInPPM);
uint8_t OPT_llCheckAdvEvtType(uint8_t advEvtType);
uint8_t OPT_llHandoverDisableAdv(uint8_t advHandle);
uint8_t OPT_llCheckAdvHealth(uint32_t* currentTime, volatile uint32_t* advTime);
void* OPT_llFindNextAdvSet(void);
void OPT_LL_DisableAdvSets(void);
uint8_t OPT_llCmDisableCurAdv(void);
uint8_t OPT_llCompareSecondaryPrimaryTasksQoSParam_adv(llConnState_t* primConnPtr);
void OPT_llSelectTasksetTimeGapForAdv(uint32_t* timeGap);
void OPT_llFreeTaskAdv(void);
void OPT_llCalculateAdvTimeGap(uint32_t* timeGap);
void OPT_hci_tl_ClearAdvSet(void);
uint8_t OPT_processAdvExtraHCICmd(hciPacket_t* pMsg);

#endif /* CTRL_ADV_NCONN_H_ */
