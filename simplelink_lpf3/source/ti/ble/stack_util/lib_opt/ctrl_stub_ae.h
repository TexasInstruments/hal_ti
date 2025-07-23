/******************************************************************************

 @file  ctrl_stub_ae.h

 @brief This file contains prototype of default stub implementations for the
        feature wrapper functions.
        These weak placeholder implementations do nothing by default,
        allowing the feature to remain disabled without causing any issues in
        the build process.
        When the feature is enabled, these stubs are replaced by the actual
        implementations directed by ctrl_ae.c.

 Group: WCS, BTS
 $Target Device: DEVICES $

 ******************************************************************************
 $License: TI_TEXT 2025 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

#ifndef CTRL_AE_H_
#define CTRL_AE_H_

#include "ti/ble/controller/ll/ll_common.h"
#include "ti/ble/controller/ll/ll_ae.h"

// Function prototypes for the actual implementations
extern llStatus_t llSetExtendedAdvParams(advSet_t* pAdvSet, aeSetParamCmd_t* pCmdParams);
extern uint8_t llParseExtAdvPduInfo(llAdvPDUInfo* pAdvInfo, RCL_Buffer_DataEntry* const pDataEntry);
extern llStatus_t llSetupExtAdv(advSet_t * pAdvSet);
extern llStatus_t llPostProcessExtendedAdv(advSet_t* pAdvSet);
extern llProcessEntryStatus llSetExtendedAdvReport(aeExtAdvRptEvt_t* extAdvRpt, llAdvPDUInfo* pAdvPDUInfo);
extern llStatus_t llAddExtAdvPacketToTx(advSet_t* pAdvSet, uint8_t pktType, uint8_t payloadLen);
extern llStatus_t llBuildExtAdvPacket(aePacket* pPkt, comExtPktFormat_t* comPkt, uint8_t pktType, uint8_t payloadLen, uint8_t peerAddrType, uint8_t ownAddrType);
extern llStatus_t llupdateAuxHdrPacket(advSet_t* pAdvSet);
extern uint32_t llExtAdvTxTime(advSet_t* pAdvSet, uint8_t primPhy, uint8_t secPhy);
extern uint32_t llEstimateAuxOtaTime(advSet_t* pAdvSet, uint8_t secPhy);
extern void llSetExtHdrFlags(aeSetDataCmd_t* pCmdParams);
extern void LL_rclAdvTxFinished(void);
extern llStatus_t llValidateAEAdvDataLength(aeSetDataCmd_t* pCmdParams, advSet_t* pAdvSet);
extern void llAdvProcessExtendedAdv(advSet_t* pAdvSet);
extern void llAEProcessAuxAdvInd(advSet_t* pAdvSet, uint8_t numActiveAdvSets);
extern void llupdateAuxAdvHeader(sortedAdv_t* pNextAdvSet);
extern bool LL_AeEnable(void);
extern uint16_t llCalculateTotalExtAdvTime(sortedAdv_t* aeNode);
extern void llSetPeerAddress(uint8_t* advPkt, llConnState_t* connPtr);
extern void llSetupExtendedAdvData(advSet_t* pAdvSet);
extern void llResetExtScanStateMachine(uint8_t* scanState);
extern llStatus_t llValidateAEAdvDataLen(aeSetDataCmd_t* pCmdParams);
extern llStatus_t llValidateScanRspDataForAE(aeEnableCmd_t* pCmdParams, advSet_t* pAdvSet);
extern llStatus_t llSetupExtendedAdvertising(advSet_t* pAdvSet);
extern void llAESetFeatureBit(void);
extern bool llAE_NextAdvIsExtended(void);
extern uint8 LL_AE_GetNextChannel(void);
extern void LL_AE_GetTxUsageParams(llTxUsageParams_t* pExtAdvTxParams);

// Wrapper functions for the feature implementations
llStatus_t OPT_llSetExtendedAdvParams(advSet_t* pAdvSet, aeSetParamCmd_t* pCmdParams);
uint8_t OPT_llParseExtAdvPduInfo(llAdvPDUInfo* pAdvInfo, RCL_Buffer_DataEntry* const pDataEntry);
llStatus_t OPT_llSetupExtAdv(advSet_t * pAdvSet);
llStatus_t OPT_llPostProcessExtendedAdv(advSet_t* pAdvSet);
llProcessEntryStatus OPT_llSetExtendedAdvReport(aeExtAdvRptEvt_t* extAdvRpt, llAdvPDUInfo* pAdvPDUInfo);
llStatus_t OPT_llAddExtAdvPacketToTx(advSet_t* pAdvSet, uint8_t pktType, uint8_t payloadLen);
llStatus_t OPT_llBuildExtAdvPacket(aePacket* pPkt, comExtPktFormat_t* comPkt, uint8_t pktType, uint8_t payloadLen, uint8_t peerAddrType, uint8_t ownAddrType);
llStatus_t OPT_llupdateAuxHdrPacket(advSet_t* pAdvSet);
uint32_t OPT_llExtAdvTxTime(advSet_t* pAdvSet, uint8_t primPhy, uint8_t secPhy);
uint32_t OPT_llEstimateAuxOtaTime(advSet_t* pAdvSet, uint8_t secPhy);
void OPT_llSetExtHdrFlags(aeSetDataCmd_t* pCmdParams);
void OPT_LL_rclAdvTxFinished(void);
llStatus_t OPT_llValidateAEAdvDataLength(aeSetDataCmd_t* pCmdParams, advSet_t* pAdvSet);
void OPT_llAdvProcessExtendedAdv(advSet_t* pAdvSet);
void OPT_llAEProcessAuxAdvInd(advSet_t* pAdvSet, uint8_t numActiveAdvSets);
void OPT_llupdateAuxAdvHeader(sortedAdv_t* pNextAdvSet);
bool OPT_LL_AeEnable(void);
uint16_t OPT_llCalculateTotalExtAdvTime(sortedAdv_t* aeNode);
void OPT_llSetPeerAddress(uint8_t* advPkt, llConnState_t* connPtr);
void OPT_llSetupExtendedAdvData(advSet_t* pAdvSet);
void OPT_llResetExtScanStateMachine(uint8_t* scanState);
llStatus_t OPT_llValidateAEAdvDataLen(aeSetDataCmd_t* pCmdParams);
llStatus_t OPT_llValidateScanRspDataForAE(aeEnableCmd_t* pCmdParams, advSet_t* pAdvSet);
llStatus_t OPT_llSetupExtendedAdvertising(advSet_t* pAdvSet);
void OPT_llAESetFeatureBit(void);
bool OPT_llAE_NextAdvIsExtended(void);
uint8 OPT_LL_AE_GetNextChannel(void);
void OPT_LL_AE_GetTxUsageParams(llTxUsageParams_t* pExtAdvTxParams);

#endif /* CTRL_AE_H_ */
