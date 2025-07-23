/******************************************************************************

 @file  ctrl_stub_pscan.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_pscan.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_PSCAN_H_
#define CTRL_PSCAN_H_

#include "ti/ble/stack_util/comdef.h"
#include "ti/ble/controller/hci/hci.h"
#include "ti/ble/controller/ll/ll_scheduler.h"
#include "ti/ble/controller/ll/ll_ae.h"
#include "ti/ble/controller/ll/ll.h"

// Function prototypes for the actual implementations
extern void llSetTaskPeriodicScan(void);
extern taskInfo_t * llSelectTaskPeriodicScan(uint8_t secTaskID, uint32_t timeGap);
extern bool llCheckSyncInfoCriteria(llAdvPDUInfo * pAdvPDUInfo);
extern void llProcessPeriodicScanSyncInfo(llExtAdvPDUInfo * pExtAdvInfo, aeExtAdvRptEvt_t * advEvent, uint32_t timeStamp);
extern void llEndPeriodicScanTask(llPeriodicScanSet_t* pPeriodicScan);
extern void llPeriodicScan_PostProcess(void);
extern void llProcessPeriodicScanRxFIFO(void);
extern void * llFindNextPeriodicScan(void);
extern void llTerminatePeriodicScan(void);
extern llPeriodicScanSet_t* llGetCurrentPeriodicScan(uint8_t state);
extern llPeriodicScanSet_t* llGetPeriodicScan(uint16_t handle);
extern void llClearPeriodicScanSets(void);
extern void llUpdatePADVBParamsInScanCmd(void);
extern hciStatus_t hciCmdParserPeriodicScan(uint8_t * pData, uint16_t cmdOpCode);
extern uint32_t llReturnCurrentPeriodicStartTime(void);
extern uint8_t llCheckPeriodicScanPriority(uint16_t taskID, uint8_t connPriority);
extern bool LL_PeriodicScanIsEnable(void);
extern taskInfo_t * llSelectTaskPeriodicScanHandle(uint32_t* timeGap, uint16_t* secTaskID);
extern void llUpdatePeriodicScanTimeGap(uint16_t taskID, uint32_t* timeGap);

// Wrapper functions for the feature implementations
void OPT_llSetTaskPeriodicScan(void);
taskInfo_t * OPT_llSelectTaskPeriodicScan(uint8_t secTaskID, uint32_t timeGap);
bool OPT_llCheckSyncInfoCriteria(llAdvPDUInfo * pAdvPDUInfo);
void OPT_llProcessPeriodicScanSyncInfo(llExtAdvPDUInfo * pExtAdvInfo, aeExtAdvRptEvt_t * advEvent, uint32_t timeStamp);
void OPT_llEndPeriodicScanTask(llPeriodicScanSet_t* pPeriodicScan);
void OPT_llPeriodicScan_PostProcess(void);
void OPT_llProcessPeriodicScanRxFIFO(void);
void * OPT_llFindNextPeriodicScan(void);
void OPT_llTerminatePeriodicScan(void);
llPeriodicScanSet_t* OPT_llGetCurrentPeriodicScan(uint8_t state);
llPeriodicScanSet_t* OPT_llGetPeriodicScan(uint16_t handle);
void OPT_llClearPeriodicScanSets(void);
void OPT_llUpdatePADVBParamsInScanCmd(void);
hciStatus_t OPT_hciCmdParserPeriodicScan(uint8_t * pData, uint16_t cmdOpCode);
uint32_t OPT_llReturnCurrentPeriodicStartTime(void);
uint8_t OPT_llCheckPeriodicScanPriority(uint16_t taskID, uint8_t connPriority);
bool OPT_LL_PeriodicScanIsEnable(void);
taskInfo_t * OPT_llSelectTaskPeriodicScanHandle(uint32_t* timeGap, uint16_t* secTaskID);
void OPT_llUpdatePeriodicScanTimeGap(uint16_t taskID, uint32_t* timeGap);

#endif /* CTRL_PSCAN_H_ */
