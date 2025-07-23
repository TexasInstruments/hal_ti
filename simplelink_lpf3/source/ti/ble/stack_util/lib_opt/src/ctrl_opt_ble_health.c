/******************************************************************************

 @file  ctrl_opt_ble_health.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project BLE_HEALTH defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_ble_health.h"

#if defined(BLE_HEALTH)



uint8_t OPT_llDbgInf_addSchedRec(taskInfo_t* const llTask)
{
    return llDbgInf_addSchedRec(llTask);
}

uint8_t OPT_DbgInf_addSchedRec(DbgInf_schedNewRec_t* const newRec)
{
    return DbgInf_addSchedRec(newRec);
}

uint8_t OPT_DbgInf_addConnEst(uint16_t connId, uint8_t connRole, uint8_t encEnabled)
{
    return DbgInf_addConnEst(connId, connRole, encEnabled);
}

uint8_t OPT_llDbgInf_addConnTerm(uint16_t connHandle, uint8_t reasonCode)
{
    return llDbgInf_addConnTerm(connHandle, reasonCode);
}

uint8_t OPT_DbgInf_addConnTerm(DbgInf_connTermRec_t* const newRec)
{
    return DbgInf_addConnTerm(newRec);
}

uint8_t OPT_DbgInf_addErrorRec(uint16_t newError)
{
    return DbgInf_addErrorRec(newError);
}

int32_t OPT_DbgInf_init(uint16_t domainBitmap)
{
    return DbgInf_init(domainBitmap);
}

int32_t OPT_DbgInf_clear(uint16_t domainBitmap)
{
    return DbgInf_clear(domainBitmap);
}

uint16_t OPT_DbgInf_get(uint8_t* const pBuf, uint16_t len, uint16_t reqDomainBitmap)
{
    return DbgInf_get(pBuf, len, reqDomainBitmap);
}

int32_t OPT_DbgInf_halt(void)
{
    return DbgInf_halt();
}

#endif /* defined(BLE_HEALTH) */
