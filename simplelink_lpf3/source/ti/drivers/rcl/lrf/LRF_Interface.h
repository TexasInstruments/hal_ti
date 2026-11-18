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
#ifndef ti_drivers_rcl_lrf_LRF_Interface__include
#define ti_drivers_rcl_lrf_LRF_Interface__include

/*!
 *  @file   LRF_Interface.h
 *  @brief  Device-family dispatcher for the common LRF interface layer.
 *
 *  Command handlers include this header to access common LRF operations without
 *  device-family knowledge. Based on @c DeviceFamily_PARENT, it
 *  re-exports:
 *    - LPF3 (CC23X0, CC23X1, CC27XX): @c LRFLPF3_Interface_Generic.h
 *    - LPF4 (CC283X):                 @c LRFLPF4_Interface_Generic.h
 *
 *  @par  Required API contract
 *
 *  Every device-family implementation included by this dispatcher must define:
 *
 *  @b End-cause status macros (@c uint16_t):
 *  @code
 *  LRF_INTERFACE_ENDCAUSE_STAT_ENDOK
 *  LRF_INTERFACE_ENDCAUSE_STAT_RXTIMEOUT
 *  LRF_INTERFACE_ENDCAUSE_STAT_NOSYNC
 *  LRF_INTERFACE_ENDCAUSE_STAT_RXERR
 *  LRF_INTERFACE_ENDCAUSE_STAT_CONNECT
 *  LRF_INTERFACE_ENDCAUSE_STAT_MAXNAK
 *  LRF_INTERFACE_ENDCAUSE_STAT_SCANRSP
 *  LRF_INTERFACE_ENDCAUSE_STAT_EOPSTOP
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_RXF
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_TXF
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_SYNTH
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_STOP
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_PAR
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_BADOP
 *  LRF_INTERFACE_ENDCAUSE_STAT_ERR_INTERNAL
 *  @endcode
 *
 *  @b Common-Interface functions:
 *  @code
 *  void     LRF_Interface_sendOp(uint16_t op);
 *  void     LRF_Interface_programSyncWordA(uint32_t syncWord);
 *  void     LRF_Interface_programSyncWordB(uint32_t syncWord);
 *  uint16_t LRF_Interface_getCmdEndCause(void);
 *  @endcode
 */

#include <ti/devices/DeviceFamily.h>
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X0) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC23X1) || \
    (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    #include <ti/drivers/rcl/lrf/LRFLPF3_Interface.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC283X)
    #include <ti/drivers/rcl/lrf/LRFLPF4_Interface.h>
#endif

#endif /* ti_drivers_rcl_lrf_LRF_Interface__include */
