/******************************************************************************

 @file  ctrl_stub_rssi_monitor.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_rssi_monitor.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_RSSI_MONITOR_H_
#define CTRL_RSSI_MONITOR_H_

#include "ti/ble/controller/ll/ll_rssi_monitor.h"
#include "ti/ble/controller/hci/hci.h"
#include "ti/ble/controller/ll/ll.h"

// Function prototypes for the actual implementations
extern llStatus_t LL_RssiMon_Open(void);
extern llStatus_t LL_RssiMon_Close(void);
extern llStatus_t LL_RssiMon_GetRssiStat(uint8_t connId, int8_t* pRssiStat);
extern llRssiMonCbHandle_t LL_RssiMon_Reg(uint8_t connId, int8_t lowRssiThresh, int8_t highRssiThresh, pfnRssiMonThreshCB_t pfnCB);
extern llStatus_t LL_RssiMon_Unreg(llRssiMonCbHandle_t regHandle);
extern llStatus_t LL_RssiMon_UnregByConnId(uint8_t connId);
extern llStatus_t LL_RssiMon_SetConfig(int8_t incomeRssiWeight, uint8_t minRssiSamples);
extern llStatus_t LL_RssiMon_GetConfig(int8_t* pIncomeRssiWeight, uint8_t* pMinRssiSamples);
extern llStatus_t LL_RssiMon_Execute(uint8_t connId);
extern llStatus_t LL_RssiMon_ClearConnData(uint8_t connId);
extern void HCI_EXT_RssiMon_ReportCB(uint8_t handle, int8_t threshPass);
extern hciStatus_t hci_ext_RssiMon_RegCmd(uint16_t connHandle, int8_t lowRssiThresh, int8_t highRssiThresh);
extern hciStatus_t hci_ext_RssiMon_UnregCmd(llRssiMonCbHandle_t regHandle);
extern hciStatus_t hci_ext_RssiMon_SetConfigCmd(int8_t incomeRssiWeight, uint8_t minRssiSamples);
extern hciStatus_t hci_ext_RssiMon_GetConfigCmd(void);
extern hciStatus_t hci_ext_RssiMon_GetRssiStatCmd(uint16_t connHandle);

// Wrapper functions for the feature implementations
llStatus_t OPT_LL_RssiMon_Open(void);
llStatus_t OPT_LL_RssiMon_Close(void);
llStatus_t OPT_LL_RssiMon_GetRssiStat(uint8_t connId, int8_t* pRssiStat);
llRssiMonCbHandle_t OPT_LL_RssiMon_Reg(uint8_t connId, int8_t lowRssiThresh, int8_t highRssiThresh, pfnRssiMonThreshCB_t pfnCB);
llStatus_t OPT_LL_RssiMon_Unreg(llRssiMonCbHandle_t regHandle);
llStatus_t OPT_LL_RssiMon_UnregByConnId(uint8_t connId);
llStatus_t OPT_LL_RssiMon_SetConfig(int8_t incomeRssiWeight, uint8_t minRssiSamples);
llStatus_t OPT_LL_RssiMon_GetConfig(int8_t* pIncomeRssiWeight, uint8_t* pMinRssiSamples);
llStatus_t OPT_LL_RssiMon_Execute(uint8_t connId);
llStatus_t OPT_LL_RssiMon_ClearConnData(uint8_t connId);
void OPT_HCI_EXT_RssiMon_ReportCB(uint8_t handle, int8_t threshPass);
hciStatus_t OPT_hci_ext_RssiMon_RegCmd(uint16_t connHandle, int8_t lowRssiThresh, int8_t highRssiThresh);
hciStatus_t OPT_hci_ext_RssiMon_UnregCmd(llRssiMonCbHandle_t regHandle);
hciStatus_t OPT_hci_ext_RssiMon_SetConfigCmd(int8_t incomeRssiWeight, uint8_t minRssiSamples);
hciStatus_t OPT_hci_ext_RssiMon_GetConfigCmd(void);
hciStatus_t OPT_hci_ext_RssiMon_GetRssiStatCmd(uint16_t connHandle);

#endif /* CTRL_RSSI_MONITOR_H_ */
