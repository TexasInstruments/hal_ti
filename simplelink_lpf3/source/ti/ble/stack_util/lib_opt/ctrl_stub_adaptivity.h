/******************************************************************************

 @file  ctrl_stub_adaptivity.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_adaptivity.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_ADAPTIVITY_H_
#define CTRL_ADAPTIVITY_H_

#include "ti/ble/controller/ll/ll_scheduler.h"
#include "ti/ble/controller/ll/ll_ae.h"

// Function prototypes for the actual implementations
extern uint8 LL_SDAA_ControlTxAndGetStartType(taskInfo_t* nextConnTask, taskInfo_t* secTask, uint8 startTaskType);
extern taskInfo_t* LL_SDAA_GetChnlAssessmentTask(void);
extern void LL_SDAA_RecordTxUsageExtAdv(advSet_t* pAdvSet);
extern void LL_rclChannelAssessmentCallback(RCL_Command* cmd, LRF_Events lrfEvents, RCL_Events events);
extern void LL_SDAA_RecordTxUsageConnection(llConnState_t* connPtr, uint8_t lastPayloadLen);
extern void LL_SDAA_RecordTxUsagePeriodic(llPeriodicAdvSet_t* pPeriodicAdv);
extern void LL_SDAA_HandleLastCmdDone(uint32 event, taskInfo_t* const pCurrTask);
extern void LL_SDAA_Init(void);
extern void LL_SDAA_FreeDynamicMemory(void);
extern void LL_SDAA_PostProcess(void);

// Wrapper functions for the feature implementations
uint8 OPT_LL_SDAA_ControlTxAndGetStartType(taskInfo_t* nextConnTask, taskInfo_t* secTask, uint8 startTaskType);
taskInfo_t* OPT_LL_SDAA_GetChnlAssessmentTask(void);
void OPT_LL_SDAA_RecordTxUsageExtAdv(advSet_t* pAdvSet);
void OPT_LL_rclChannelAssessmentCallback(RCL_Command* cmd, LRF_Events lrfEvents, RCL_Events events);
void OPT_LL_SDAA_RecordTxUsageConnection(llConnState_t* connPtr, uint8_t lastPayloadLen);
void OPT_LL_SDAA_RecordTxUsagePeriodic(llPeriodicAdvSet_t* pPeriodicAdv);
void OPT_LL_SDAA_HandleLastCmdDone(uint32 event, taskInfo_t* const pCurrTask);
void OPT_LL_SDAA_Init(void);
void OPT_LL_SDAA_FreeDynamicMemory(void);
void OPT_LL_SDAA_PostProcess(void);

#endif /* CTRL_ADAPTIVITY_H_ */
