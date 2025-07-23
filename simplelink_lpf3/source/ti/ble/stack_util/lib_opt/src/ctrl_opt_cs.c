/******************************************************************************

 @file  ctrl_opt_cs.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project CHANNEL_SOUNDING defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_cs.h"

#if defined(CHANNEL_SOUNDING)



csStatus_e OPT_LL_CS_ReadLocalSupportedCapabilites(llCsCapabilities_t* pLocalCapabilities)
{
    return LL_CS_ReadLocalSupportedCapabilites(pLocalCapabilities);
}

csStatus_e OPT_LL_CS_ReadRemoteSupportedCapabilities(uint16_t connId)
{
    return LL_CS_ReadRemoteSupportedCapabilities(connId);
}

csStatus_e OPT_LL_CS_CreateConfig(uint16_t connId, const csConfigurationSet_t* pConfig, uint8_t createContext)
{
    return LL_CS_CreateConfig(connId, pConfig, createContext);
}

csStatus_e OPT_LL_CS_RemoveConfig(uint16_t connId, uint8_t configId)
{
    return LL_CS_RemoveConfig(connId, configId);
}

csStatus_e OPT_LL_CS_SecurityEnable(uint16_t connId)
{
    return LL_CS_SecurityEnable(connId);
}

csStatus_e OPT_LL_CS_SetDefaultSettings(uint16_t connId, csDefaultSettings_t* defaultSettings)
{
    return LL_CS_SetDefaultSettings(connId, defaultSettings);
}

csStatus_e OPT_LL_CS_ReadLocalFAETable(csFaeTbl_t* pFaeTable)
{
    return LL_CS_ReadLocalFAETable(pFaeTable);
}

csStatus_e OPT_LL_CS_ReadRemoteFAETable(uint16_t connId)
{
    return LL_CS_ReadRemoteFAETable(connId);
}

csStatus_e OPT_LL_CS_WriteRemoteFAETable(uint16_t connId, int8* pFaeTbl)
{
    return LL_CS_WriteRemoteFAETable(connId, pFaeTbl);
}

csStatus_e OPT_LL_CS_SetChannelClassification(uint8_t* pChannelClassification)
{
    return LL_CS_SetChannelClassification(pChannelClassification);
}

csStatus_e OPT_LL_CS_GetRole(uint16_t connId, uint8_t configId, uint8_t* role)
{
    return LL_CS_GetRole(connId, configId, role);
}

csStatus_e OPT_LL_CS_SetProcedureParameters(uint16_t connId, uint8_t configId, csProcedureParams_t* csProcParams)
{
    return LL_CS_SetProcedureParameters(connId, configId, csProcParams);
}

csStatus_e OPT_LL_CS_ProcedureEnable(uint16_t connId, uint8_t configId, uint8_t enable)
{
    return LL_CS_ProcedureEnable(connId, configId, enable);
}

void OPT_HCI_CS_SubeventResultContinueCback(void* hdr, const void* data, uint16_t dataLength)
{
    HCI_CS_SubeventResultContinueCback(hdr, data, dataLength);
}

csStatus_e OPT_llCsProcessCsControlPacket(uint8_t ctrlType, llConnState_t* connPtr, uint8_t* pBuf)
{
    return llCsProcessCsControlPacket(ctrlType, connPtr, pBuf);
}

uint8_t OPT_llCsProcessCsCtrlProcedures(llConnState_t* connPtr, uint8_t ctrlPkt)
{
    return llCsProcessCsCtrlProcedures(connPtr, ctrlPkt);
}

uint8_t OPT_llCsInit(void)
{
    return llCsInit();
}

uint8_t OPT_llCsDbIsCsCtrlProcedureInProgress(uint16_t connId)
{
    return llCsDbIsCsCtrlProcedureInProgress(connId);
}

uint8_t OPT_llCsDbGetProcedureDoneStatus(uint16_t connId)
{
    return llCsDbGetProcedureDoneStatus(connId);
}

uint8_t OPT_llCsInitDb(void)
{
    return llCsInitDb();
}

void OPT_llCsClearConnProcedures(uint16_t connId)
{
    llCsClearConnProcedures(connId);
}

void OPT_llCsFreeAll(void)
{
    llCsFreeAll();
}

void OPT_llCsSetFeatureBit(void)
{
    llCsSetFeatureBit();
}

csStatus_e OPT_llCsStartProcedure(llConnState_t* connPtr)
{
    return llCsStartProcedure(connPtr);
}

uint8_t OPT_llCsStartStepListGen(uint16_t connId)
{
    return llCsStartStepListGen(connId);
}

void OPT_llCsSubevent_PostProcess(void)
{
    llCsSubevent_PostProcess();
}

void OPT_llCsSteps_PostProcess(void)
{
    llCsSteps_PostProcess();
}

void OPT_llCsResults_PostProcess(void)
{
    llCsResults_PostProcess();
}

void OPT_llCsError_PostProcess(void)
{
    llCsError_PostProcess();
}

RCL_Command* OPT_llScheduler_FindPrimStartType(const taskInfo_t* pNextConnTask, uint8_t* startType)
{
    return llScheduler_FindPrimStartType(pNextConnTask, startType);
}

uint32_t OPT_llScheduler_getSwitchTime(uint16_t taskID)
{
    return llScheduler_getSwitchTime(taskID);
}

uint8_t OPT_hciCmdParserChannelSounding(uint8_t* pData, uint16_t cmdOpCode)
{
    return hciCmdParserChannelSounding(pData, cmdOpCode);
}

RCL_Handle OPT_llScheduler_getHandle(uint16_t taskID)
{
    return llScheduler_getHandle(taskID);
}

void OPT_llCsRcl_handleCsSubmitError(uint16_t taskID, RCL_Command * cmd)
{
    llCsRcl_handleCsSubmitError(taskID, cmd);
}

void OPT_llCsPrecal_postProcess(void)
{
    llCsPrecal_postProcess();
}

csStatus_e OPT_LL_CS_Handover_CnParseCnData(uint16 connHandle, const uint8_t * pParams)
{
    return LL_CS_Handover_CnParseCnData(connHandle, pParams);
}

void OPT_LL_CS_Handover_SnPopulateSnData(uint16 connHandle, uint8_t * pParams)
{
    LL_CS_Handover_SnPopulateSnData(connHandle, pParams);
}

#endif /* defined(CHANNEL_SOUNDING) */
