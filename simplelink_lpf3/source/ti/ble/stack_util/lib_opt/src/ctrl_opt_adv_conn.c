/******************************************************************************

 @file  ctrl_opt_adv_conn.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project CTRL_ADV_CONN_CFG defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_adv_conn.h"

#if defined(CTRL_ADV_CONN_CFG)

#if !defined(CTRL_ADV_NCONN_CFG)
#error "One or more dependencies are missing! Please add them."
#endif

void OPT_llProcessPeripheralConnectionCreated(void)
{
    llProcessPeripheralConnectionCreated();
}

void OPT_llProcessPeripheralControlPacket(llConnState_t* connPtr, uint8_t* pPkt)
{
    llProcessPeripheralControlPacket(connPtr, pPkt);
}

uint8_t OPT_llCheckPeripheralTerminate(uint8_t connId)
{
    return llCheckPeripheralTerminate(connId);
}

RCL_Callback OPT_LL_GetRfPeripheralCallback(void)
{
    return LL_GetRfPeripheralCallback();
}

void OPT_llAlignToNextEvent(llConnState_t* connPtr)
{
    llAlignToNextEvent(connPtr);
}

uint8_t OPT_llLastCmdDoneEventHandleConnectRequest(void)
{
    return llLastCmdDoneEventHandleConnectRequest();
}

void OPT_llPeripheral_TaskEnd(void)
{
    llPeripheral_TaskEnd();
}

void OPT_llBuildCtrlPktPeri(llConnState_t* connPtr, uint8_t* pData, uint8_t ctrlPkt)
{
    llBuildCtrlPktPeri(connPtr, pData, ctrlPkt);
}

void OPT_llPostSetupCtrlPktPeri(llConnState_t* connPtr, uint8_t ctrlPkt)
{
    llPostSetupCtrlPktPeri(connPtr, ctrlPkt);
}

hciStatus_t OPT_hciCmdParserPeripheral(uint8_t* pData, uint16_t cmdOpCode)
{
    return hciCmdParserPeripheral(pData, cmdOpCode);
}

hciStatus_t OPT_hciCmdParserVendorSpecificPeripheral(uint8_t* pData, uint16_t cmdOpCode)
{
    return hciCmdParserVendorSpecificPeripheral(pData, cmdOpCode);
}

void OPT_llAdv_TaskConnect(void)
{
    llAdv_TaskConnect();
}

void OPT_llSetTaskPeripheral(uint8_t connId, void* nextConnCmd)
{
    llSetTaskPeripheral(connId, nextConnCmd);
}

uint8_t OPT_llCheckAdvEventType(advSet_t* pAdvSet)
{
    return llCheckAdvEventType(pAdvSet);
}

void OPT_llupdateAdvCmdForHDC(advSet_t* pAdvSet, aeLegacyRf_t* pRf)
{
    llupdateAdvCmdForHDC(pAdvSet, pRf);
}

void OPT_llSendRejectInd(llConnState_t* connPtr, uint8_t errorCode)
{
    llSendRejectInd(connPtr, errorCode);
}

void OPT_LL_setAdvConnDefualtValues(void)
{
    LL_setAdvConnDefualtValues();
}

void OPT_LE_SetExtAdvParamsAdvConn(aeSetParamCmd_t* pCmdParams, advSet_t* pAdvSet)
{
    LE_SetExtAdvParamsAdvConn(pCmdParams, pAdvSet);
}

llStatus_t OPT_LE_checkAdvConnStatus(advSet_t* pAdvSet, aeEnableCmd_t* pCmdParams)
{
    return LE_checkAdvConnStatus(pAdvSet, pCmdParams);
}

bool OPT_ll_AdvConnIsEnable(void)
{
    return ll_AdvConnIsEnable();
}

void OPT_llCmdAdvStartedEventHandle(void)
{
    llCmdAdvStartedEventHandle();
}

#endif /* defined(CTRL_ADV_CONN_CFG) */
