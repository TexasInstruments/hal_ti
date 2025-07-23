/******************************************************************************

 @file  ctrl_stub_cs_test.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_cs_test.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_CS_TEST_H_
#define CTRL_CS_TEST_H_

#include "ti/ble/controller/ll/ll_cs_mgr.h"
#include "ti/ble/controller/ll/ll_cs_procedure.h"
#include "ti/ble/controller/ll/ll_cs_ctrl_pkt_mgr.h"
#include "ti/ble/controller/ll/ll_cs_rcl.h"

// Function prototypes for the actual implementations
extern csStatus_e LL_CS_Test(csTestParams_t* pParams);
extern csStatus_e LL_CS_TestEnd(void);
extern void HCI_CS_TestEndCompleteCback(uint8_t status);
extern uint8_t llCsInitChanIdxArrWrapper(uint8_t configId, uint16_t connId, const uint8_t* pCsConfig);
extern uint8_t llCsSelectStepChanWrapper(uint8_t stepMode, uint16_t connId, const uint8_t* pCsConfig);
extern uint8_t llCsGetNextAntennaPermutationWrapper(csACI_e ACI);
extern void llCsSelectAAWrapper(uint8_t csRole, uint32_t* aaRx, uint32_t* aaTx);
extern void llCsGetRandomSequenceWrapper(uint8_t csRole, uint32_t* pTx, uint32_t* pRx, uint8_t plLen);
extern uint8_t llCsGetToneExtentionWrapper(void);

// Wrapper functions for the feature implementations
csStatus_e OPT_LL_CS_Test(csTestParams_t* pParams);
csStatus_e OPT_LL_CS_TestEnd(void);
void OPT_HCI_CS_TestEndCompleteCback(uint8_t status);
uint8_t OPT_llCsInitChanIdxArrWrapper(uint8_t configId, uint16_t connId, const uint8_t* pCsConfig);
uint8_t OPT_llCsSelectStepChanWrapper(uint8_t stepMode, uint16_t connId, const uint8_t* pCsConfig);
uint8_t OPT_llCsGetNextAntennaPermutationWrapper(csACI_e ACI);
void OPT_llCsSelectAAWrapper(uint8_t csRole, uint32_t* aaRx, uint32_t* aaTx);
void OPT_llCsGetRandomSequenceWrapper(uint8_t csRole, uint32_t* pTx, uint32_t* pRx, uint8_t plLen);
uint8_t OPT_llCsGetToneExtentionWrapper(void);

#endif /* CTRL_CS_TEST_H_ */
