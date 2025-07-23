/******************************************************************************

 @file  ctrl_opt_cs_test.c

 @brief Implementation of the feature wrapper functions that direct to the full
        feature implementations.
        Enabling the feature by linking the wrapper functions to the real
        implementations defined in the library.

        Usage:
        Include this file in the build only when the feature is enabled.
        Add to the project CS_TEST defines
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
#include "ti/ble/stack_util/lib_opt/ctrl_stub_cs_test.h"

#if defined(CS_TEST)

#if !defined(CHANNEL_SOUNDING)
#error "One or more dependencies are missing! Please add them."
#endif

csStatus_e OPT_LL_CS_Test(csTestParams_t* pParams)
{
    return LL_CS_Test(pParams);
}

csStatus_e OPT_LL_CS_TestEnd(void)
{
    return LL_CS_TestEnd();
}

void OPT_HCI_CS_TestEndCompleteCback(uint8_t status)
{
    HCI_CS_TestEndCompleteCback(status);
}

uint8_t OPT_llCsInitChanIdxArrWrapper(uint8_t configId, uint16_t connId, const uint8_t* pCsConfig)
{
    return llCsInitChanIdxArrWrapper(configId, connId, pCsConfig);
}

uint8_t OPT_llCsSelectStepChanWrapper(uint8_t stepMode, uint16_t connId, const uint8_t* pCsConfig)
{
    return llCsSelectStepChanWrapper(stepMode, connId, pCsConfig);
}

uint8_t OPT_llCsGetNextAntennaPermutationWrapper(csACI_e ACI)
{
    return llCsGetNextAntennaPermutationWrapper(ACI);
}

void OPT_llCsSelectAAWrapper(uint8_t csRole, uint32_t* aaRx, uint32_t* aaTx)
{
    llCsSelectAAWrapper(csRole, aaRx, aaTx);
}

void OPT_llCsGetRandomSequenceWrapper(uint8_t csRole, uint32_t* pTx, uint32_t* pRx, uint8_t plLen)
{
    llCsGetRandomSequenceWrapper(csRole, pTx, pRx, plLen);
}

uint8_t OPT_llCsGetToneExtentionWrapper(void)
{
    return llCsGetToneExtentionWrapper();
}

#endif /* defined(CS_TEST) */
