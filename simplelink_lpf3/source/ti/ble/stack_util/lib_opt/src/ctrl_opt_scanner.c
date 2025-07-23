/******************************************************************************

 @file  ctrl_opt_scanner.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project CTRL_SCANNER_CFG defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_scanner.h"

#if defined(CTRL_SCANNER_CFG)



void OPT_llProcessScanTimeout(void)
{
    llProcessScanTimeout();
}

void OPT_llSetTaskScan(uint8_t startType, taskInfo_t* nextSecTask, void* nextSecCommand, void* nextConnCmd)
{
    llSetTaskScan(startType, nextSecTask, nextSecCommand, nextConnCmd);
}

taskInfo_t* OPT_llSelectTaskScan(uint8_t secTaskID, uint32_t timeGap)
{
    return llSelectTaskScan(secTaskID, timeGap);
}

void OPT_llHandleScanRxEntry(RCL_Buffer_DataEntry* pDataEntry)
{
    llHandleScanRxEntry(pDataEntry);
}

void OPT_llExtScan_PostProcess(void)
{
    llExtScan_PostProcess();
}

void OPT_LL_rclScanRxEntryDone(void)
{
    LL_rclScanRxEntryDone();
}

uint8_t OPT_llChackScannerUseAcceptList(void)
{
    return llChackScannerUseAcceptList();
}

uint8_t OPT_llCheckScanHealth(uint32_t* currentTime, volatile uint32_t* scanTime)
{
    return llCheckScanHealth(currentTime, scanTime);
}

llStatus_t OPT_llAllocExtScanInfo(void)
{
    return llAllocExtScanInfo();
}

void OPT_LL_DisableScanning(void)
{
    LL_DisableScanning();
}

uint8_t OPT_LL_EXT_ValidateScanTaskType(uint8_t taskType, uint16_t taskHandle, llPeriodicScanSet_t** pPeriodicScan)
{
    return LL_EXT_ValidateScanTaskType(taskType, taskHandle, pPeriodicScan);
}

void OPT_LL_EXT_SetQOSParameters_scan(uint8_t taskType, uint32_t paramVal, llPeriodicScanSet_t* pPeriodicScan)
{
    LL_EXT_SetQOSParameters_scan(taskType, paramVal, pPeriodicScan);
}

uint8_t OPT_llCheckScanPriority(uint16_t taskID, uint8_t connPriority)
{
    return llCheckScanPriority(taskID, connPriority);
}

uint8_t OPT_LL_IsScannerWithRandomAddress(void)
{
    return LL_IsScannerWithRandomAddress();
}

void OPT_llUpdateScannSecTaskTimeGap(uint32_t* timeGap)
{
    llUpdateScannSecTaskTimeGap(timeGap);
}

void OPT_llUpdateTimeGapForScanWindow(taskInfo_t* secTask, llConnState_t* nextConnPtr, RCL_Command* secCmd, uint32_t* timeGap, uint32_t curTime)
{
    llUpdateTimeGapForScanWindow(secTask, nextConnPtr, secCmd, timeGap, curTime);
}

llStatus_t OPT_HCI_TL_set_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams)
{
    return HCI_TL_set_scan_param(opcode, pHciParams, hci_tl_cmdScanParams);
}

llStatus_t OPT_HCI_TL_set_ext_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams)
{
    return HCI_TL_set_ext_scan_param(opcode, pHciParams, hci_tl_cmdScanParams);
}

llStatus_t OPT_HCI_TL_set_ext_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams)
{
    return HCI_TL_set_ext_scan_enable(opcode, pHciParams, hci_tl_cmdScanEnable, hci_tl_cmdScanParams);
}

llStatus_t OPT_HCI_TL_set_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams)
{
    return HCI_TL_set_scan_enable(opcode, pHciParams, hci_tl_cmdScanEnable, hci_tl_cmdScanParams);
}

void OPT_llStopCurrentScan(void)
{
    llStopCurrentScan();
}

#endif /* defined(CTRL_SCANNER_CFG) */
