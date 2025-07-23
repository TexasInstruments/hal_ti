/******************************************************************************

 @file  ctrl_stub_scanner.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_scanner.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_SCANNER_H_
#define CTRL_SCANNER_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_scheduler.h"
#include "ti/ble/controller/ll/ll_ae.h"
#include "ti/ble/controller/hci/hci.h"

// Function prototypes for the actual implementations
extern void llProcessScanTimeout(void);
extern void llSetTaskScan(uint8_t startType, taskInfo_t* nextSecTask, void* nextSecCommand, void* nextConnCmd);
extern taskInfo_t* llSelectTaskScan(uint8_t secTaskID, uint32_t timeGap);
extern void llHandleScanRxEntry(RCL_Buffer_DataEntry* pDataEntry);
extern void llExtScan_PostProcess(void);
extern void LL_rclScanRxEntryDone(void);
extern uint8_t llChackScannerUseAcceptList(void);
extern uint8_t llCheckScanHealth(uint32_t* currentTime, volatile uint32_t* scanTime);
extern llStatus_t llAllocExtScanInfo(void);
extern void LL_DisableScanning(void);
extern uint8_t LL_EXT_ValidateScanTaskType(uint8_t taskType, uint16_t taskHandle, llPeriodicScanSet_t** pPeriodicScan);
extern void LL_EXT_SetQOSParameters_scan(uint8_t taskType, uint32_t paramVal, llPeriodicScanSet_t* pPeriodicScan);
extern uint8_t llCheckScanPriority(uint16_t taskID, uint8_t connPriority);
extern uint8_t LL_IsScannerWithRandomAddress(void);
extern void llUpdateScannSecTaskTimeGap(uint32_t* timeGap);
extern void llUpdateTimeGapForScanWindow(taskInfo_t* secTask, llConnState_t* nextConnPtr, RCL_Command* secCmd, uint32_t* timeGap, uint32_t curTime);
extern llStatus_t HCI_TL_set_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
extern llStatus_t HCI_TL_set_ext_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
extern llStatus_t HCI_TL_set_ext_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
extern llStatus_t HCI_TL_set_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
extern void llStopCurrentScan(void);

// Wrapper functions for the feature implementations
void OPT_llProcessScanTimeout(void);
void OPT_llSetTaskScan(uint8_t startType, taskInfo_t* nextSecTask, void* nextSecCommand, void* nextConnCmd);
taskInfo_t* OPT_llSelectTaskScan(uint8_t secTaskID, uint32_t timeGap);
void OPT_llHandleScanRxEntry(RCL_Buffer_DataEntry* pDataEntry);
void OPT_llExtScan_PostProcess(void);
void OPT_LL_rclScanRxEntryDone(void);
uint8_t OPT_llChackScannerUseAcceptList(void);
uint8_t OPT_llCheckScanHealth(uint32_t* currentTime, volatile uint32_t* scanTime);
llStatus_t OPT_llAllocExtScanInfo(void);
void OPT_LL_DisableScanning(void);
uint8_t OPT_LL_EXT_ValidateScanTaskType(uint8_t taskType, uint16_t taskHandle, llPeriodicScanSet_t** pPeriodicScan);
void OPT_LL_EXT_SetQOSParameters_scan(uint8_t taskType, uint32_t paramVal, llPeriodicScanSet_t* pPeriodicScan);
uint8_t OPT_llCheckScanPriority(uint16_t taskID, uint8_t connPriority);
uint8_t OPT_LL_IsScannerWithRandomAddress(void);
void OPT_llUpdateScannSecTaskTimeGap(uint32_t* timeGap);
void OPT_llUpdateTimeGapForScanWindow(taskInfo_t* secTask, llConnState_t* nextConnPtr, RCL_Command* secCmd, uint32_t* timeGap, uint32_t curTime);
llStatus_t OPT_HCI_TL_set_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
llStatus_t OPT_HCI_TL_set_ext_scan_param(uint16_t opcode, uint8_t* pHciParams, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
llStatus_t OPT_HCI_TL_set_ext_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
llStatus_t OPT_HCI_TL_set_scan_enable(uint16_t opcode, uint8_t* pHciParams, aeEnableScanCmd_t* hci_tl_cmdScanEnable, aeSetScanParamCmd_t* hci_tl_cmdScanParams);
void OPT_llStopCurrentScan(void);

#endif /* CTRL_SCANNER_H_ */
