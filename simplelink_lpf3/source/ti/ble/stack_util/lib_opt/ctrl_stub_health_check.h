/******************************************************************************

 @file  ctrl_stub_health_check.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_health_check.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_HEALTH_CHECK_H_
#define CTRL_HEALTH_CHECK_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/hci/hci.h"
#include "ti/ble/controller/ll/ll.h"

// Function prototypes for the actual implementations
extern int8_t llHealthCheck(void);
extern void llHealthUpdate(uint8_t state);
extern void llHealthSetThreshold(uint32_t connTime, uint32_t scanTime, uint32_t initTime, uint32_t advTime);
extern void llHealthSetAESThreshold(uint32_t aesThreshold);
extern bool ll_healthCheckIsEnable(void);

// Wrapper functions for the feature implementations
int8_t OPT_llHealthCheck(void);
void OPT_llHealthUpdate(uint8_t state);
void OPT_llHealthSetThreshold(uint32_t connTime, uint32_t scanTime, uint32_t initTime, uint32_t advTime);
void OPT_llHealthSetAESThreshold(uint32_t aesThreshold);
bool OPT_ll_healthCheckIsEnable(void);

#endif /* CTRL_HEALTH_CHECK_H_ */
