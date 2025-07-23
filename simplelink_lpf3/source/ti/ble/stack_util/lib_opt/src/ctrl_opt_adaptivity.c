/******************************************************************************

 @file  ctrl_opt_adaptivity.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project SDAA_ENABLE defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_adaptivity.h"

#if defined(SDAA_ENABLE)



uint8 OPT_LL_SDAA_ControlTxAndGetStartType(taskInfo_t* nextConnTask, taskInfo_t* secTask, uint8 startTaskType)
{
    return LL_SDAA_ControlTxAndGetStartType(nextConnTask, secTask, startTaskType);
}

taskInfo_t* OPT_LL_SDAA_GetChnlAssessmentTask(void)
{
    return LL_SDAA_GetChnlAssessmentTask();
}

void OPT_LL_SDAA_RecordTxUsageExtAdv(advSet_t* pAdvSet)
{
    LL_SDAA_RecordTxUsageExtAdv(pAdvSet);
}

void OPT_LL_rclChannelAssessmentCallback(RCL_Command* cmd, LRF_Events lrfEvents, RCL_Events events)
{
    LL_rclChannelAssessmentCallback(cmd, lrfEvents, events);
}

void OPT_LL_SDAA_RecordTxUsageConnection(llConnState_t* connPtr, uint8_t lastPayloadLen)
{
    LL_SDAA_RecordTxUsageConnection(connPtr, lastPayloadLen);
}

void OPT_LL_SDAA_RecordTxUsagePeriodic(llPeriodicAdvSet_t* pPeriodicAdv)
{
    LL_SDAA_RecordTxUsagePeriodic(pPeriodicAdv);
}

void OPT_LL_SDAA_HandleLastCmdDone(uint32 event, taskInfo_t* const pCurrTask)
{
    LL_SDAA_HandleLastCmdDone(event, pCurrTask);
}

void OPT_LL_SDAA_Init(void)
{
    LL_SDAA_Init();
}

void OPT_LL_SDAA_FreeDynamicMemory(void)
{
    LL_SDAA_FreeDynamicMemory();
}

void OPT_LL_SDAA_PostProcess(void)
{
    LL_SDAA_PostProcess();
}

#endif /* defined(SDAA_ENABLE) */
