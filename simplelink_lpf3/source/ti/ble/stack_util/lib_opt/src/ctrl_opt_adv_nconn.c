/******************************************************************************

 @file  ctrl_opt_adv_nconn.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project CTRL_ADV_NCONN_CFG defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_adv_nconn.h"

#if defined(CTRL_ADV_NCONN_CFG)



void OPT_llProcessAdvAddrResolutionTimeout(void)
{
    llProcessAdvAddrResolutionTimeout();
}

void OPT_llSetTaskAdv(uint8_t startType, void* nextSecCmd)
{
    llSetTaskAdv(startType, nextSecCmd);
}

taskInfo_t* OPT_llSelectTaskAdv(uint8_t secTaskID, uint32_t timeGap)
{
    return llSelectTaskAdv(secTaskID, timeGap);
}

llStatus_t OPT_LL_ClearAdvSets(void)
{
    return LL_ClearAdvSets();
}

uint8_t OPT_LL_CountAdvSets(uint8_t type)
{
    return LL_CountAdvSets(type);
}

advSet_t* OPT_LL_GetAdvSet(uint8_t handle, uint8_t allocFlag)
{
    return LL_GetAdvSet(handle, allocFlag);
}

llStatus_t OPT_LL_SetSecAdvChanMap(uint8_t* chanMap)
{
    return LL_SetSecAdvChanMap(chanMap);
}

void OPT_llExtAdv_PostProcess(void)
{
    llExtAdv_PostProcess();
}

hciStatus_t OPT_hciCmdParserAdvertiser(uint8_t* pData, uint16_t cmdOpCode)
{
    return hciCmdParserAdvertiser(pData, cmdOpCode);
}

hciStatus_t OPT_hciCmdParserVendorSpecificBroadcaster(uint8_t* pData, uint16_t cmdOpCode)
{
    return hciCmdParserVendorSpecificBroadcaster(pData, cmdOpCode);
}

void OPT_LL_rclAdvRxEntryDone(void)
{
    LL_rclAdvRxEntryDone();
}

uint8_t OPT_LL_IsAdvertizeWithRandomAddress(void)
{
    return LL_IsAdvertizeWithRandomAddress();
}

void OPT_LL_UpdateAdvSCAValue(uint16_t scaInPPM)
{
    LL_UpdateAdvSCAValue(scaInPPM);
}

uint8_t OPT_llCheckAdvEvtType(uint8_t advEvtType)
{
    return llCheckAdvEvtType(advEvtType);
}

uint8_t OPT_llHandoverDisableAdv(uint8_t advHandle)
{
    return llHandoverDisableAdv(advHandle);
}

uint8_t OPT_llCheckAdvHealth(uint32_t* currentTime, volatile uint32_t* advTime)
{
    return llCheckAdvHealth(currentTime, advTime);
}

void* OPT_llFindNextAdvSet(void)
{
    return llFindNextAdvSet();
}

void OPT_LL_DisableAdvSets(void)
{
    LL_DisableAdvSets();
}

uint8_t OPT_llCmDisableCurAdv(void)
{
    return llCmDisableCurAdv();
}

uint8_t OPT_llCompareSecondaryPrimaryTasksQoSParam_adv(llConnState_t* primConnPtr)
{
    return llCompareSecondaryPrimaryTasksQoSParam_adv(primConnPtr);
}

void OPT_llSelectTasksetTimeGapForAdv(uint32_t* timeGap)
{
    llSelectTasksetTimeGapForAdv(timeGap);
}

void OPT_llFreeTaskAdv(void)
{
    llFreeTaskAdv();
}

void OPT_llCalculateAdvTimeGap(uint32_t* timeGap)
{
    llCalculateAdvTimeGap(timeGap);
}

void OPT_hci_tl_ClearAdvSet(void)
{
    hci_tl_ClearAdvSet();
}

uint8_t OPT_processAdvExtraHCICmd(hciPacket_t* pMsg)
{
    return processAdvExtraHCICmd(pMsg);
}

#endif /* defined(CTRL_ADV_NCONN_CFG) */
