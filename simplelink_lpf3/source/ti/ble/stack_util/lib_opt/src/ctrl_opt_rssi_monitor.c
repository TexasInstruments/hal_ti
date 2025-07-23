/******************************************************************************

 @file  ctrl_opt_rssi_monitor.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project RSSI_MONITOR defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_rssi_monitor.h"

#if defined(RSSI_MONITOR)



llStatus_t OPT_LL_RssiMon_Open(void)
{
    return LL_RssiMon_Open();
}

llStatus_t OPT_LL_RssiMon_Close(void)
{
    return LL_RssiMon_Close();
}

llStatus_t OPT_LL_RssiMon_GetRssiStat(uint8_t connId, int8_t* pRssiStat)
{
    return LL_RssiMon_GetRssiStat(connId, pRssiStat);
}

llRssiMonCbHandle_t OPT_LL_RssiMon_Reg(uint8_t connId, int8_t lowRssiThresh, int8_t highRssiThresh, pfnRssiMonThreshCB_t pfnCB)
{
    return LL_RssiMon_Reg(connId, lowRssiThresh, highRssiThresh, pfnCB);
}

llStatus_t OPT_LL_RssiMon_Unreg(llRssiMonCbHandle_t regHandle)
{
    return LL_RssiMon_Unreg(regHandle);
}

llStatus_t OPT_LL_RssiMon_UnregByConnId(uint8_t connId)
{
    return LL_RssiMon_UnregByConnId(connId);
}

llStatus_t OPT_LL_RssiMon_SetConfig(int8_t incomeRssiWeight, uint8_t minRssiSamples)
{
    return LL_RssiMon_SetConfig(incomeRssiWeight, minRssiSamples);
}

llStatus_t OPT_LL_RssiMon_GetConfig(int8_t* pIncomeRssiWeight, uint8_t* pMinRssiSamples)
{
    return LL_RssiMon_GetConfig(pIncomeRssiWeight, pMinRssiSamples);
}

llStatus_t OPT_LL_RssiMon_Execute(uint8_t connId)
{
    return LL_RssiMon_Execute(connId);
}

llStatus_t OPT_LL_RssiMon_ClearConnData(uint8_t connId)
{
    return LL_RssiMon_ClearConnData(connId);
}

void OPT_HCI_EXT_RssiMon_ReportCB(uint8_t handle, int8_t threshPass)
{
    HCI_EXT_RssiMon_ReportCB(handle, threshPass);
}

hciStatus_t OPT_hci_ext_RssiMon_RegCmd(uint16_t connHandle, int8_t lowRssiThresh, int8_t highRssiThresh)
{
    return hci_ext_RssiMon_RegCmd(connHandle, lowRssiThresh, highRssiThresh);
}

hciStatus_t OPT_hci_ext_RssiMon_UnregCmd(llRssiMonCbHandle_t regHandle)
{
    return hci_ext_RssiMon_UnregCmd(regHandle);
}

hciStatus_t OPT_hci_ext_RssiMon_SetConfigCmd(int8_t incomeRssiWeight, uint8_t minRssiSamples)
{
    return hci_ext_RssiMon_SetConfigCmd(incomeRssiWeight, minRssiSamples);
}

hciStatus_t OPT_hci_ext_RssiMon_GetConfigCmd(void)
{
    return hci_ext_RssiMon_GetConfigCmd();
}

hciStatus_t OPT_hci_ext_RssiMon_GetRssiStatCmd(uint16_t connHandle)
{
    return hci_ext_RssiMon_GetRssiStatCmd(connHandle);
}

#endif /* defined(RSSI_MONITOR) */
