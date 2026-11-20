/*
 * Copyright (c) 2026 Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ti_drivers_rcl_lrf_LRF_Interface_Generic__include
#define ti_drivers_rcl_lrf_LRF_Interface_Generic__include

/*!
 *  @file   LRF_Interface_Generic.h
 *  @brief  Device-family dispatcher for the generic firmware interface layer.
 *
 *  Command handlers include this header to access generic firmware operations
 *  without device-family knowledge.  Based on @c DeviceFamily_PARENT, it
 *  re-exports:
 *    - LPF3 (CC23X0, CC23X1, CC27XX): @c LRFLPF3_Interface_Generic.h
 *    - LPF4 (CC283X):                 @c LRFLPF4_Interface_Generic.h
 *
 *  @par  Required API contract
 *
 *  Every device-family implementation included by this dispatcher must define:
 *
 *  @b Types:
 *  @code
 *  struct LRF_SYNC_SEARCH_CTRL_t;   typedef ... LRF_SyncSearchCtrl;
 *  struct LRF_MODULATION_CTRL_t;    typedef ... LRF_ModulationCtrl;
 *  @endcode
 *
 *  @b Generic-Interface functions:
 *  @code
 *  void     LRF_Interface_Generic_sendOpFs(void);
 *  void     LRF_Interface_Generic_sendOpTx(void);
 *  void     LRF_Interface_Generic_sendOpRx(void);
 *  void     LRF_Interface_Generic_sendOpFsOff(void);
 *  void     LRF_Interface_Generic_sendOpStop(void);
 *  void     LRF_Interface_Generic_sendOpEopStop(void);
 *  void     LRF_Interface_Generic_configOpFs(void);
 *  void     LRF_Interface_Generic_configOpFsOff(void);
 *  void     LRF_Interface_Generic_configOpTx(uint8_t fsOff, uint32_t freqInHz);
 *  void     LRF_Interface_Generic_configOpTxRepeat(uint32_t freqInHz, uint8_t fsRecal);
 *  void     LRF_Interface_Generic_configOpTxTest(uint8_t fsOff, uint32_t freqInHz, uint16_t txWord);
 *  void     LRF_Interface_Generic_configOpRx(uint8_t fsOff, uint32_t freqInHz, uint8_t repeated, uint16_t maxPktLen);
 *  void     LRF_Interface_Generic_configNextOpTx(void);
 *  void     LRF_Interface_Generic_skipFreqProgramming(void);
 *  bool     LRF_Interface_Generic_isFreqSynthLocked(void);
 *  void     LRF_Interface_Generic_configOpNesbPtx(uint8_t fsOff, uint32_t freqInHz, uint8_t autoRetransmitMode);
 *  uint16_t LRF_Interface_Generic_getOpCfgNesbPrx(uint8_t fsOff, uint32_t freqInHz, uint8_t repeatNok, uint8_t repeatOk);
 *  void     LRF_Interface_Generic_configOpNesbPrx(uint16_t lrfOpCfg, uint8_t addrLen, const RCL_ConfigAddress *syncWordCfg);
 *  bool     LRF_Interface_Generic_shouldNesbListenForAck(uint8_t mode);
 *  uint32_t LRF_Interface_Generic_updateSyncWord(uint32_t syncWord);
 *  void     LRF_Interface_Generic_programSyncWordA(uint32_t syncWord);
 *  void     LRF_Interface_Generic_programSyncWordB(uint32_t syncWord);
 *  void     LRF_Interface_Generic_updateSyncWordCfg(RCL_ConfigAddress *syncWordCfg);
 *  void     LRF_Interface_Generic_configDualSyncWords(uint32_t syncWordA, uint32_t syncWordB,
 *                                                     bool disableSyncWordA, bool disableSyncWordB,
 *                                                     LRF_SyncSearchCtrl *syncSearchCtrl);
 *  void     LRF_Interface_Generic_restoreSyncSearch(const LRF_SyncSearchCtrl *syncSearchCtrl);
 *  void     LRF_Interface_Generic_setModulationMode(uint32_t sendCw, uint32_t whitenMode,
 *                                                   LRF_ModulationCtrl *modulationCtrl);
 *  void     LRF_Interface_Generic_restoreModulationMode(const LRF_ModulationCtrl *modulationCtrl);
 *  uint32_t LRF_Interface_Generic_maskEventsByFifoConf(uint32_t mask, uint16_t fifoCfg, bool activeUpdate);
 *  uint16_t LRF_Interface_Generic_getFifoCfg(void);
 *  uint32_t LRF_Interface_Generic_getLastPacketTimestamp(void);
 *  void     LRF_Interface_Generic_setLastPacketTimestamp(uint32_t timestamp);
 *  int8_t   LRF_Interface_Generic_getLastPacketRssi(void);
 *  uint16_t LRF_Interface_Generic_getNumOfRxOkPackets(void);
 *  void     LRF_Interface_Generic_setNumOfRxOkPackets(uint16_t numOfRxOkPackets);
 *  uint16_t LRF_Interface_Generic_getNumOfNotRxOkPackets(void);
 *  void     LRF_Interface_Generic_setNumOfNotRxOkPackets(uint16_t numOfNotRxOkPackets);
 *  uint16_t LRF_Interface_Generic_getNumOfTxPackets(void);
 *  void     LRF_Interface_Generic_setNumOfTxPackets(uint16_t numOfTxPackets);
 *  uint16_t LRF_Interface_Generic_getNumOfIgnoredRxPackets(void);
 *  void     LRF_Interface_Generic_setNumOfIgnoredRxPackets(uint16_t numOfIgnoredRxPackets);
 *  uint16_t LRF_Interface_Generic_getRxFifoFullCount(void);
 *  void     LRF_Interface_Generic_setRxFifoFullCount(uint16_t rxBufferFullCount);
 *  @endcode
 */

#include <ti/devices/DeviceFamily.h>
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #include <ti/drivers/rcl/lrf/LRFLPF3_Interface_Generic.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC283X)
    #include <ti/drivers/rcl/lrf/LRFLPF4_Interface_Generic.h>
#endif

#endif /* ti_drivers_rcl_lrf_LRF_Interface_Generic__include */
