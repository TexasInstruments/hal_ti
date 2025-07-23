/******************************************************************************

 @file  ctrl_stub_adv_conn.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_adv_conn.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_ADV_CONN_H_
#define CTRL_ADV_CONN_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_ble.h"
#include "ti/ble/controller/ll/ll_ae.h"
#include "ti/ble/controller/hci/hci.h"

// Function prototypes for the actual implementations
extern void llProcessPeripheralConnectionCreated(void);
extern void llProcessPeripheralControlPacket(llConnState_t* connPtr, uint8_t* pPkt);
extern uint8_t llCheckPeripheralTerminate(uint8_t connId);
extern RCL_Callback LL_GetRfPeripheralCallback(void);
extern void llAlignToNextEvent(llConnState_t* connPtr);
extern uint8_t llLastCmdDoneEventHandleConnectRequest(void);
extern void llPeripheral_TaskEnd(void);
extern void llBuildCtrlPktPeri(llConnState_t* connPtr, uint8_t* pData, uint8_t ctrlPkt);
extern void llPostSetupCtrlPktPeri(llConnState_t* connPtr, uint8_t ctrlPkt);
extern hciStatus_t hciCmdParserPeripheral(uint8_t* pData, uint16_t cmdOpCode);
extern hciStatus_t hciCmdParserVendorSpecificPeripheral(uint8_t* pData, uint16_t cmdOpCode);
extern void llAdv_TaskConnect(void);
extern void llSetTaskPeripheral(uint8_t connId, void* nextConnCmd);
extern uint8_t llCheckAdvEventType(advSet_t* pAdvSet);
extern void llupdateAdvCmdForHDC(advSet_t* pAdvSet, aeLegacyRf_t* pRf);
extern void llSendRejectInd(llConnState_t* connPtr, uint8_t errorCode);
extern void LL_setAdvConnDefualtValues(void);
extern void LE_SetExtAdvParamsAdvConn(aeSetParamCmd_t* pCmdParams, advSet_t* pAdvSet);
extern llStatus_t LE_checkAdvConnStatus(advSet_t* pAdvSet, aeEnableCmd_t* pCmdParams);
extern bool ll_AdvConnIsEnable(void);
extern void llCmdAdvStartedEventHandle(void);

// Wrapper functions for the feature implementations
void OPT_llProcessPeripheralConnectionCreated(void);
void OPT_llProcessPeripheralControlPacket(llConnState_t* connPtr, uint8_t* pPkt);
uint8_t OPT_llCheckPeripheralTerminate(uint8_t connId);
RCL_Callback OPT_LL_GetRfPeripheralCallback(void);
void OPT_llAlignToNextEvent(llConnState_t* connPtr);
uint8_t OPT_llLastCmdDoneEventHandleConnectRequest(void);
void OPT_llPeripheral_TaskEnd(void);
void OPT_llBuildCtrlPktPeri(llConnState_t* connPtr, uint8_t* pData, uint8_t ctrlPkt);
void OPT_llPostSetupCtrlPktPeri(llConnState_t* connPtr, uint8_t ctrlPkt);
hciStatus_t OPT_hciCmdParserPeripheral(uint8_t* pData, uint16_t cmdOpCode);
hciStatus_t OPT_hciCmdParserVendorSpecificPeripheral(uint8_t* pData, uint16_t cmdOpCode);
void OPT_llAdv_TaskConnect(void);
void OPT_llSetTaskPeripheral(uint8_t connId, void* nextConnCmd);
uint8_t OPT_llCheckAdvEventType(advSet_t* pAdvSet);
void OPT_llupdateAdvCmdForHDC(advSet_t* pAdvSet, aeLegacyRf_t* pRf);
void OPT_llSendRejectInd(llConnState_t* connPtr, uint8_t errorCode);
void OPT_LL_setAdvConnDefualtValues(void);
void OPT_LE_SetExtAdvParamsAdvConn(aeSetParamCmd_t* pCmdParams, advSet_t* pAdvSet);
llStatus_t OPT_LE_checkAdvConnStatus(advSet_t* pAdvSet, aeEnableCmd_t* pCmdParams);
bool OPT_ll_AdvConnIsEnable(void);
void OPT_llCmdAdvStartedEventHandle(void);

#endif /* CTRL_ADV_CONN_H_ */
