/******************************************************************************

 @file  ctrl_opt_health_check.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project USE_HEALTH_CHECK defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_health_check.h"

#if defined(USE_HEALTH_CHECK)



int8_t OPT_llHealthCheck(void)
{
    return llHealthCheck();
}

void OPT_llHealthUpdate(uint8_t state)
{
    llHealthUpdate(state);
}

void OPT_llHealthSetThreshold(uint32_t connTime, uint32_t scanTime, uint32_t initTime, uint32_t advTime)
{
    llHealthSetThreshold(connTime, scanTime, initTime, advTime);
}

void OPT_llHealthSetAESThreshold(uint32_t aesThreshold)
{
    llHealthSetAESThreshold(aesThreshold);
}

bool OPT_ll_healthCheckIsEnable(void)
{
    return ll_healthCheckIsEnable();
}

#endif /* defined(USE_HEALTH_CHECK) */
