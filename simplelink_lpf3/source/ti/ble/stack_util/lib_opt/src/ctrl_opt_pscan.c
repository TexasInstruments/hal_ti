/******************************************************************************

 @file  ctrl_opt_pscan.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project USE_PERIODIC_SCAN defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_pscan.h"

#if defined(USE_PERIODIC_SCAN)

#if !defined(CTRL_SCANNER_CFG)
#error "One or more dependencies are missing! Please add them."
#endif

void OPT_llSetTaskPeriodicScan(void)
{
    llSetTaskPeriodicScan();
}

taskInfo_t * OPT_llSelectTaskPeriodicScan(uint8_t secTaskID, uint32_t timeGap)
{
    return llSelectTaskPeriodicScan(secTaskID, timeGap);
}

bool OPT_llCheckSyncInfoCriteria(llAdvPDUInfo * pAdvPDUInfo)
{
    return llCheckSyncInfoCriteria(pAdvPDUInfo);
}

void OPT_llProcessPeriodicScanSyncInfo(llExtAdvPDUInfo * pExtAdvInfo, aeExtAdvRptEvt_t * advEvent, uint32_t timeStamp)
{
    llProcessPeriodicScanSyncInfo(pExtAdvInfo, advEvent, timeStamp);
}

void OPT_llEndPeriodicScanTask(llPeriodicScanSet_t* pPeriodicScan)
{
    llEndPeriodicScanTask(pPeriodicScan);
}

void OPT_llPeriodicScan_PostProcess(void)
{
    llPeriodicScan_PostProcess();
}

void OPT_llProcessPeriodicScanRxFIFO(void)
{
    llProcessPeriodicScanRxFIFO();
}

void * OPT_llFindNextPeriodicScan(void)
{
    return llFindNextPeriodicScan();
}

void OPT_llTerminatePeriodicScan(void)
{
    llTerminatePeriodicScan();
}

llPeriodicScanSet_t* OPT_llGetCurrentPeriodicScan(uint8_t state)
{
    return llGetCurrentPeriodicScan(state);
}

llPeriodicScanSet_t* OPT_llGetPeriodicScan(uint16_t handle)
{
    return llGetPeriodicScan(handle);
}

void OPT_llClearPeriodicScanSets(void)
{
    llClearPeriodicScanSets();
}

void OPT_llUpdatePADVBParamsInScanCmd(void)
{
    llUpdatePADVBParamsInScanCmd();
}

hciStatus_t OPT_hciCmdParserPeriodicScan(uint8_t * pData, uint16_t cmdOpCode)
{
    return hciCmdParserPeriodicScan(pData, cmdOpCode);
}

uint32_t OPT_llReturnCurrentPeriodicStartTime(void)
{
    return llReturnCurrentPeriodicStartTime();
}

uint8_t OPT_llCheckPeriodicScanPriority(uint16_t taskID, uint8_t connPriority)
{
    return llCheckPeriodicScanPriority(taskID, connPriority);
}

bool OPT_LL_PeriodicScanIsEnable(void)
{
    return LL_PeriodicScanIsEnable();
}

taskInfo_t * OPT_llSelectTaskPeriodicScanHandle(uint32_t* timeGap, uint16_t* secTaskID)
{
    return llSelectTaskPeriodicScanHandle(timeGap, secTaskID);
}

void OPT_llUpdatePeriodicScanTimeGap(uint16_t taskID, uint32_t* timeGap)
{
    llUpdatePeriodicScanTimeGap(taskID, timeGap);
}

#endif /* defined(USE_PERIODIC_SCAN) */
