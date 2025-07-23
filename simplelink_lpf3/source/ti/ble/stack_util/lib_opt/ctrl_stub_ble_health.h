/******************************************************************************

 @file  ctrl_stub_ble_health.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_ble_health.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_BLE_HEALTH_H_
#define CTRL_BLE_HEALTH_H_

#include "ti/ble/stack_util/health_toolkit/debugInfo_internal.h"
#include "ti/ble/controller/ll/ll_scheduler.h"

// Function prototypes for the actual implementations
extern uint8_t llDbgInf_addSchedRec(taskInfo_t* const llTask);
extern uint8_t DbgInf_addSchedRec(DbgInf_schedNewRec_t* const newRec);
extern uint8_t DbgInf_addConnEst(uint16_t connId, uint8_t connRole, uint8_t encEnabled);
extern uint8_t llDbgInf_addConnTerm(uint16_t connHandle, uint8_t reasonCode);
extern uint8_t DbgInf_addConnTerm(DbgInf_connTermRec_t* const newRec);
extern uint8_t DbgInf_addErrorRec(uint16_t newError);
extern int32_t DbgInf_init(uint16_t domainBitmap);
extern int32_t DbgInf_clear(uint16_t domainBitmap);
extern uint16_t DbgInf_get(uint8_t* const pBuf, uint16_t len, uint16_t reqDomainBitmap);
extern int32_t DbgInf_halt(void);

// Wrapper functions for the feature implementations
uint8_t OPT_llDbgInf_addSchedRec(taskInfo_t* const llTask);
uint8_t OPT_DbgInf_addSchedRec(DbgInf_schedNewRec_t* const newRec);
uint8_t OPT_DbgInf_addConnEst(uint16_t connId, uint8_t connRole, uint8_t encEnabled);
uint8_t OPT_llDbgInf_addConnTerm(uint16_t connHandle, uint8_t reasonCode);
uint8_t OPT_DbgInf_addConnTerm(DbgInf_connTermRec_t* const newRec);
uint8_t OPT_DbgInf_addErrorRec(uint16_t newError);
int32_t OPT_DbgInf_init(uint16_t domainBitmap);
int32_t OPT_DbgInf_clear(uint16_t domainBitmap);
uint16_t OPT_DbgInf_get(uint8_t* const pBuf, uint16_t len, uint16_t reqDomainBitmap);
int32_t OPT_DbgInf_halt(void);

#endif /* CTRL_BLE_HEALTH_H_ */
