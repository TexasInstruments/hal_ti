/******************************************************************************

 @file  ctrl_stub_power_control.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_power_control.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_POWER_CONTROL_H_
#define CTRL_POWER_CONTROL_H_

#include "ti/ble/controller/ll/ll_power_control.h"
#include "ti/ble/controller/hci/hci.h"

// Function prototypes for the actual implementations
extern void LL_PwrCtrl_Close(void);
extern void LL_PwrCtrl_CloseConn(uint8_t connId);
extern llStatus_t LL_PwrCtrl_Open(void);
extern void LL_PwrCtrl_HandlePhyChangeEvent(llConnState_t* connPtr);
extern llStatus_t LL_PwrCtrl_HandleProcedure(llConnState_t* connPtr, uint8_t ctrlPktType);
extern void LL_PwrCtrl_SetupPwrCtrlPkt(const llConnState_t* connPtr, uint8_t ctrlPktType, uint8_t* pCtrlPktPayload);
extern void LL_PwrCtrl_OpenConn(uint8_t connId);
extern void LL_PwrCtrl_UpdatePwrLevelAllConn(void);
extern llStatus_t LL_PwrCtrl_SetFeatureBit(void);
extern void LL_PwrCtrl_HandleRxPackets(llConnState_t* connPtr, const uint8_t* pCtrlPktPayload, uint8_t opcode);
extern llStatus_t LL_PwrCtrl_ReadRemoteTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy);
extern llStatus_t LL_PwrCtrl_EnhancedReadTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy, int8_t* pCurrentTxPower, int8_t* pMaxTxPower);
extern llStatus_t LL_PwrCtrl_SetTransPwrRptEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable);
extern llStatus_t LL_EXT_PwrCtrl_SendPwrCtrlReqCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable);
extern void HCI_TransPwrRptCB(uint8_t status, uint8_t connHandle, uint8_t reason, uint8_t txPhy, int8_t txPowerLevel, uint8_t txPowerMaxMinReached, int8_t delta);
extern hciStatus_t hci_ext_SendPowerControlRequestCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable);
extern hciStatus_t hci_le_SetTransmitPowerReportingEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable);
extern hciStatus_t hci_le_EnhancedReadTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy);
extern hciStatus_t hci_le_ReadRemoteTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy);

// Wrapper functions for the feature implementations
void OPT_LL_PwrCtrl_Close(void);
void OPT_LL_PwrCtrl_CloseConn(uint8_t connId);
llStatus_t OPT_LL_PwrCtrl_Open(void);
void OPT_LL_PwrCtrl_HandlePhyChangeEvent(llConnState_t* connPtr);
llStatus_t OPT_LL_PwrCtrl_HandleProcedure(llConnState_t* connPtr, uint8_t ctrlPktType);
void OPT_LL_PwrCtrl_SetupPwrCtrlPkt(const llConnState_t* connPtr, uint8_t ctrlPktType, uint8_t* pCtrlPktPayload);
void OPT_LL_PwrCtrl_OpenConn(uint8_t connId);
void OPT_LL_PwrCtrl_UpdatePwrLevelAllConn(void);
llStatus_t OPT_LL_PwrCtrl_SetFeatureBit(void);
void OPT_LL_PwrCtrl_HandleRxPackets(llConnState_t* connPtr, const uint8_t* pCtrlPktPayload, uint8_t opcode);
llStatus_t OPT_LL_PwrCtrl_ReadRemoteTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy);
llStatus_t OPT_LL_PwrCtrl_EnhancedReadTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy, int8_t* pCurrentTxPower, int8_t* pMaxTxPower);
llStatus_t OPT_LL_PwrCtrl_SetTransPwrRptEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable);
llStatus_t OPT_LL_EXT_PwrCtrl_SendPwrCtrlReqCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable);
void OPT_HCI_TransPwrRptCB(uint8_t status, uint8_t connHandle, uint8_t reason, uint8_t txPhy, int8_t txPowerLevel, uint8_t txPowerMaxMinReached, int8_t delta);
hciStatus_t OPT_hci_ext_SendPowerControlRequestCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable);
hciStatus_t OPT_hci_le_SetTransmitPowerReportingEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable);
hciStatus_t OPT_hci_le_EnhancedReadTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy);
hciStatus_t OPT_hci_le_ReadRemoteTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy);

#endif /* CTRL_POWER_CONTROL_H_ */
