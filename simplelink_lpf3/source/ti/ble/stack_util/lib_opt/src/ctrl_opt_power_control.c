/******************************************************************************

 @file  ctrl_opt_power_control.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project POWER_CONTROL defines
        The real functions must be implemented in the linked library.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#include "ti/ble/stack_util/lib_opt/opt_dependencies.h"
#include "ti/ble/stack_util/lib_opt/ctrl_stub_power_control.h"

#if defined(POWER_CONTROL)



void OPT_LL_PwrCtrl_Close(void)
{
    LL_PwrCtrl_Close();
}

void OPT_LL_PwrCtrl_CloseConn(uint8_t connId)
{
    LL_PwrCtrl_CloseConn(connId);
}

llStatus_t OPT_LL_PwrCtrl_Open(void)
{
    return LL_PwrCtrl_Open();
}

void OPT_LL_PwrCtrl_HandlePhyChangeEvent(llConnState_t* connPtr)
{
    LL_PwrCtrl_HandlePhyChangeEvent(connPtr);
}

llStatus_t OPT_LL_PwrCtrl_HandleProcedure(llConnState_t* connPtr, uint8_t ctrlPktType)
{
    return LL_PwrCtrl_HandleProcedure(connPtr, ctrlPktType);
}

void OPT_LL_PwrCtrl_SetupPwrCtrlPkt(const llConnState_t* connPtr, uint8_t ctrlPktType, uint8_t* pCtrlPktPayload)
{
    LL_PwrCtrl_SetupPwrCtrlPkt(connPtr, ctrlPktType, pCtrlPktPayload);
}

void OPT_LL_PwrCtrl_OpenConn(uint8_t connId)
{
    LL_PwrCtrl_OpenConn(connId);
}

void OPT_LL_PwrCtrl_UpdatePwrLevelAllConn(void)
{
    LL_PwrCtrl_UpdatePwrLevelAllConn();
}

llStatus_t OPT_LL_PwrCtrl_SetFeatureBit(void)
{
    return LL_PwrCtrl_SetFeatureBit();
}

void OPT_LL_PwrCtrl_HandleRxPackets(llConnState_t* connPtr, const uint8_t* pCtrlPktPayload, uint8_t opcode)
{
    LL_PwrCtrl_HandleRxPackets(connPtr, pCtrlPktPayload, opcode);
}

llStatus_t OPT_LL_PwrCtrl_ReadRemoteTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy)
{
    return LL_PwrCtrl_ReadRemoteTransPwrLevelCmd(connHandle, txPhy);
}

llStatus_t OPT_LL_PwrCtrl_EnhancedReadTransPwrLevelCmd(uint16_t connHandle, uint8_t txPhy, int8_t* pCurrentTxPower, int8_t* pMaxTxPower)
{
    return LL_PwrCtrl_EnhancedReadTransPwrLevelCmd(connHandle, txPhy, pCurrentTxPower, pMaxTxPower);
}

llStatus_t OPT_LL_PwrCtrl_SetTransPwrRptEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable)
{
    return LL_PwrCtrl_SetTransPwrRptEnableCmd(connHandle, localEnable, remoteEnable);
}

llStatus_t OPT_LL_EXT_PwrCtrl_SendPwrCtrlReqCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable)
{
    return LL_EXT_PwrCtrl_SendPwrCtrlReqCmd(connHandle, txPhy, deltaPowerDb, aprEnable);
}

void OPT_HCI_TransPwrRptCB(uint8_t status, uint8_t connHandle, uint8_t reason, uint8_t txPhy, int8_t txPowerLevel, uint8_t txPowerMaxMinReached, int8_t delta)
{
    HCI_TransPwrRptCB(status, connHandle, reason, txPhy, txPowerLevel, txPowerMaxMinReached, delta);
}

hciStatus_t OPT_hci_ext_SendPowerControlRequestCmd(uint16_t connHandle, uint8_t txPhy, int8_t deltaPowerDb, uint8_t aprEnable)
{
    return hci_ext_SendPowerControlRequestCmd(connHandle, txPhy, deltaPowerDb, aprEnable);
}

hciStatus_t OPT_hci_le_SetTransmitPowerReportingEnableCmd(uint16_t connHandle, uint8_t localEnable, uint8_t remoteEnable)
{
    return hci_le_SetTransmitPowerReportingEnableCmd(connHandle, localEnable, remoteEnable);
}

hciStatus_t OPT_hci_le_EnhancedReadTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy)
{
    return hci_le_EnhancedReadTransmitPowerLevelCmd(connHandle, txPhy);
}

hciStatus_t OPT_hci_le_ReadRemoteTransmitPowerLevelCmd(uint16_t connHandle, uint8_t txPhy)
{
    return hci_le_ReadRemoteTransmitPowerLevelCmd(connHandle, txPhy);
}

#endif /* defined(POWER_CONTROL) */
