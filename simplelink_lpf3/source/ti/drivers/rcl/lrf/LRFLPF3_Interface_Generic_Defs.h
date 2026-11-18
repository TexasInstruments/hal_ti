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
#ifndef ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic_Defs__include
#define ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic_Defs__include

#include <ti/devices/DeviceFamily.h>
#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC23X0) && \
    (DeviceFamily_PARENT != DeviceFamily_PARENT_CC23X1) && \
    (DeviceFamily_PARENT != DeviceFamily_PARENT_CC27XX)
    #error "This LRFLPF3_Interface_Generic_Defs.h header file is only for CC23XX and CC27XX devices!"
#endif

#include <stdint.h>

#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)

/* Macros */

/*! @brief LRF FW defined API opcode definitions */

/*! @brief Generic FW API opcode: internal used only. */
#define LRF_INTERFACE_GENERIC_API_OP_PING                            ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_PING))
/*! @brief Generic FW API opcode: hard stop of active operation. */
#define LRF_INTERFACE_GENERIC_API_OP_STOP                            ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_STOP))
/*! @brief Generic FW API opcode: graceful stop of active operation. */
#define LRF_INTERFACE_GENERIC_API_OP_EOP_STOP                        ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_EOPSTOP))
/*! @brief Generic FW API opcode: start TX operation. */
#define LRF_INTERFACE_GENERIC_API_OP_TX                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_TX))
/*! @brief Generic FW API opcode: start RX operation. */
#define LRF_INTERFACE_GENERIC_API_OP_RX                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_RX))
/*! @brief Generic FW API opcode: start frequency synthesizer. */
#define LRF_INTERFACE_GENERIC_API_OP_FS                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_FS))
/*! @brief Generic FW API opcode: stop frequency synthesizer. */
#define LRF_INTERFACE_GENERIC_API_OP_STOP_FS                         ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_STOPFS))

#endif /* ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic_Defs__include */
