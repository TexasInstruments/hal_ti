/*
 * Copyright (c) 2022-2026 Texas Instruments Incorporated
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
/*
 *  ======== ble_cs.c ========
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ti/log/Log.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>

#include <ti/drivers/rcl/hal/RCL_Hal.h>
#include <ti/drivers/rcl/commands/ble_cs.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdtxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfds2r.h)
#include DeviceFamily_constructPath(inc/rfe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble5_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble_cs_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble_cs_regdef_regs.h)

#ifndef OCTOPUS
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_gpio.h)
#include DeviceFamily_constructPath(inc/hw_ioc.h)
#include DeviceFamily_constructPath(inc/hw_ckmd.h)
#endif

#define BLE_CS_BASE_FREQ_MHZ                2402U
#define BLE_CS_MAX_CHANNEL                  78U
#define BLE_CS_MID_CHANNEL                  40U
#define BLE_CS_NUM_CHANNELS                 79U
#define BLE_CS_NUM_INVALID_CHANNELS         7U
#define BLE_CS_SILENT_CHANNEL               100U
#define BLE_CS_NUM_PERMUTATION              24U
#define BLE_CS_S2R_OVERSAMPLE_RATE          4U
#define BLE_CS_S2R_MEMORY_OFFSET            0x0C00U
#define BLE_CS_TXRXFIFO_BASE_ADDR           128U
#define BLE_CS_TXRXFIFO_SIZE                (384U - BLE_CS_TXRXFIFO_BASE_ADDR)
#define BLE_CS_FIRST_BATCH_SIZE             2U
#define BLE_CS_TONE_QUALITY_HIGH_THR        20U
#define BLE_CS_TONE_QUALITY_NA              255U
#define BLE_CS_TONE_EXTENSION_INITIATOR_TX  0b01U
#define BLE_CS_TONE_EXTENSION_REFLECTOR_TX  0b10U
#define BLE_CS_RX_GAIN_AUTO_DEFAULT         0x0EC9
#define BLE_CS_RX_GAIN_DB_TO_OVERRIDE(x)    (((x) / 3U) << 8U)
#define BLE_CS_FOFF_COMP_TO_OVERRIDE(x)     ((x) * 4U)
#define BLE_CS_FOFF_NUM_OVERRIDE            ((1 << 15U) | 1U)     // [15]=Enable, [1]=NUM hardcoded to 1
#define BLE_CS_COMBINE_IQ(i, q)             ((((int32_t) i) & 0xFFFF) | ((((int32_t) q) & 0xFFFF) << 16))
/* The radio applies inline PCT phase in units of 2*pi/2^15, while PCT compensation phase is in units of 2*pi/2^16 */
#define BLE_CS_PCT_PHASE_TO_INLINE(x)       (uint16_t) ((((uint32_t) (x) + 1U) >> 1U) & 0x7FFFU)
#define DECODE_ANTENNA(x, y)                (uint8_t) (((x) >> ((y)*2U)) & 0x03U)
#define ENCODE_ANTENNA(x, y)                (((x) << ((y)*4U)))
#define INT16_MSB(x)                        (uint8_t) (((uint16_t) (x) >> 8U) & 0xFFU)
#define INT16_LSB(x)                        (uint8_t) ((uint16_t) (x) & 0xFFU)
#define INT32_H(x)                          (uint16_t) (((uint32_t) (x) >> 16U) & 0xFFFFU)
#define INT32_L(x)                      (uint16_t) ((uint32_t) (x) & 0xFFFFU)

/* Prepare constant terms for step specific calculations */
#define T1US  RCL_BLE_CS_US_TO_MCE_TIMER(1U)
#define T3US  RCL_BLE_CS_US_TO_MCE_TIMER(3U)
#define TRD   RCL_BLE_CS_US_TO_MCE_TIMER(5U)
#define TGD   RCL_BLE_CS_US_TO_MCE_TIMER(10U)
#define TPLT  RCL_BLE_CS_US_TO_MCE_TIMER(20U)
#define TFM   RCL_BLE_CS_US_TO_MCE_TIMER(80U)
#define TPYL  0U   // Unknown at this point

/* Define Antenna Indexes */
#define A1 (0)
#define A2 (1)
#define A3 (2)
#define A4 (3)

/*
 *  ======== Execution status ========
 */
struct
{
    struct {
        RCL_CommandStatus endStatus;
    } common;
    struct {
        bool     rxGainCacheValid;
        uint16_t rxGainCache;
        bool     foffCacheValid;
        int16_t  foffCache;
        bool     firstBuffer;
    } ble_cs;
} bleCsHandlerState;

/* Storage to decompress data */
RCL_CmdBleCs_Step_Internal       step;
RCL_CmdBleCs_StepResult_Internal stepResult;

/* Precalculated base terms */
uint32_t tStepLut[RCL_CmdBleCs_StepMode_Length];
int16_t  tPllRx[RCL_CmdBleCs_StepMode_Length];
int16_t  tAdjALut[RCL_CmdBleCs_StepMode_Length];
int16_t  tAdjBLut[RCL_CmdBleCs_StepMode_Length];
int16_t  tAntBLut[RCL_CmdBleCs_StepMode_Length];
int16_t  tAntALut[RCL_CmdBleCs_StepMode_Length];
int16_t  tRttAdjustLut[RCL_CmdBleCs_StepMode_Length];

/*
 *  ======== Type for indexing antenna sequence ========
 */
typedef union {
    struct {
        uint8_t a0 : 2;
        uint8_t a1 : 2;
        uint8_t a2 : 2;
        uint8_t a3 : 2;
    } a;
    uint8_t apn;
} RCL_AntennaPath_t;

/*
 *  ======== Type for mapping antenna permutation to antenna sequence ========
 */
typedef struct {
    uint8_t numPath : 3;    /*!< Total number of antenna path */
    uint8_t numPerm : 5;    /*!< Total number of permutation possible with this configuration */
    RCL_AntennaPath_t ap[2];
} RCL_AntennaConfig_t;

/*
 *  ======== Antenna permutation table ========
 */
const RCL_AntennaPath_t antennaPermutation[BLE_CS_NUM_PERMUTATION] = {
    /*[ 0:5 ]=*/{{A1,A2,A3,A4}}, {{A2,A1,A3,A4}}, {{A1,A3,A2,A4}}, {{A3,A1,A2,A4}}, {{A3,A2,A1,A4}}, {{A2,A3,A1,A4}},
    /*[ 6:11]=*/{{A1,A2,A4,A3}}, {{A2,A1,A4,A3}}, {{A1,A4,A2,A3}}, {{A4,A1,A2,A3}}, {{A4,A2,A1,A3}}, {{A2,A4,A1,A3}},
    /*[12:17]=*/{{A1,A4,A3,A2}}, {{A4,A1,A3,A2}}, {{A1,A3,A4,A2}}, {{A3,A1,A4,A2}}, {{A3,A4,A1,A2}}, {{A4,A3,A1,A2}},
    /*[18:23]=*/{{A4,A2,A3,A1}}, {{A2,A4,A3,A1}}, {{A4,A3,A2,A1}}, {{A3,A4,A2,A1}}, {{A3,A2,A4,A1}}, {{A2,A3,A4,A1}}
};

/*
 *  ======== Antenna permutation selection mapping ========
 */
const RCL_AntennaConfig_t antennaConfig[RCL_CmdBleCs_AntennaConfig_Length] = {
    /*1x1=*/{.numPath=1, .numPerm=1,  .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*2x1=*/{.numPath=2, .numPerm=2,  .ap={/*initiator=*/{{0,1,0,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*3x1=*/{.numPath=3, .numPerm=6,  .ap={/*initiator=*/{{0,1,2,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*4x1=*/{.numPath=4, .numPerm=24, .ap={/*initiator=*/{{0,1,2,3}}, /*reflector=*/{{0,0,0,0}}}},
    /*1x2=*/{.numPath=2, .numPerm=2,  .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,0,0}}}},
    /*1x3=*/{.numPath=3, .numPerm=6,  .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,2,0}}}},
    /*1x4=*/{.numPath=4, .numPerm=24, .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,2,3}}}},
    /*2x2=*/{.numPath=4, .numPerm=24, .ap={/*initiator=*/{{0,0,1,1}}, /*reflector=*/{{0,1,0,1}}}}
};

/*
 *  ======== Type of configuration of MCE and FIDC accumulator used for PCT measurement ========
 */
typedef union {
    struct {
        uint8_t period       : 2;   /*!< Configures the accumulation period of DEMFIDC module */
        uint8_t numIteration : 2;   /*!< Configures how many times to run the accumulator period */
        uint8_t fracWaitAdj  : 4;
        uint8_t fracWait;
    };
    uint16_t val;
} RCL_PctConfig_t;

typedef union {
    struct {
        uint8_t magnIteration;
        uint8_t reserved;
    };
    uint16_t val;
} RCL_MagnConfig_t;

typedef struct {
    int16_t mode0[2];
    int16_t mode1[2];
    int16_t mode2[2];
    int16_t mode3[2];
} RCL_Tadjust_t;

/*
 *  ======== Type of configuration for phy specific settings ========
 */
typedef struct {
    /* Modem specific registers */
    uint16_t        baud;
    uint16_t        symmap;
    uint16_t        demmisc2;
    uint16_t        demmisc3;
    uint16_t        rssioffset;

    /* Timing parameters [48 MHz units unless specified otherwise] */
    uint16_t        tPostProcessDiv1;   /*!<  Duration set aside for post processing */
    uint16_t        tPostProcessDiv4;   /*!<  Duration set aside for post processing */
    uint16_t        tRxTimeoutI0;       /*!<  Initiator must terminate packet reception before end of step */
    uint16_t        tRxTimeoutI3;       /*!<  Initiator must terminate packet reception before end of step */
    uint16_t        tStartup;           /*!<  Duration set aside for starting up the topSMs and start to emit a tone on the antenna */
    uint16_t        tPacket;            /*!<  Duration of packet [preamble + AA + Trailer] */
    uint16_t        tRxTimeoutRn;       /*!<  Reception timeout on reflector side */
    uint16_t        tInfiniteRx;        /*!<  Correction of step duration when packet reception is used as anchor point */
    uint16_t        tTr;                /*!<  Duration of trailer bits */
    uint16_t        tCorr;              /*!<  Time between signal on antenna and correlation event */
    uint16_t        tDem;               /*!<  Time between signal on antenna and demodulation completed*/
    uint16_t        tFidc;              /*!<  Time between signal on antenna and FIDC */
    uint16_t        tTxModDelay;        /*!<  Time between modulator and signal on antenna (mostly shaper delay) */
    uint16_t        tTimestampDelay1;   /*!<  Sum of delays between signal on antenna vs capture on timer by HW for mode-1 */
    uint16_t        tTimestampDelay3;   /*!<  Sum of delays between signal on antenna vs capture on timer by HW for mode-3 */

    /* Accumulator period and iteration number in order to fit into the same TPM period. */
    RCL_PctConfig_t pctConfig[RCL_CmdBleCs_Tpm_Length];

    /* Magnitude accumulator configuration used by RFE for tone quality estimation */
    RCL_MagnConfig_t magnConfig[RCL_CmdBleCs_Tpm_Length];

    /* Adjustment of TIP period per mode */
    RCL_Tadjust_t tAdj[RCL_CmdBleCs_Role_Length];

    /* Adjustment of RTT per mode/rate. Used in removing nominal values from report. */
    RCL_Tadjust_t tRtt;

    /* Adjustment of antenna timings for mode 2 & 3 */
    RCL_Tadjust_t tAnt[RCL_CmdBleCs_Role_Length];
} RCL_PhyConfig_t;

//#define FE_8MHZ 1
/*
 *  ======== Configuration per PHY ========
 */
const RCL_PhyConfig_t phyConfigLut[RCL_CmdBleCs_Phy_Length] = {
    #ifdef FE_8MHZ
    {   /* Phy_1M @ 8MHZ*/
        .baud       = 0x4000,
        .symmap     = 0x001F,
        .demmisc2   = 0x15F8,
        .demmisc3   = 0x10A1,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 2112, // 8+32+4 bits = 44us
        .tTr               = 192,  // 4us

        /* Tuned */
        .tStartup          = 93,  // 1.937us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 245, // 5.109us (wait -> signal on shaper)
        .tPostProcessDiv1  = 936, // 19.5us
        .tPostProcessDiv4  = 234, // 19.5us
        .tInfiniteRx       = 60,  // 1.25us

        .tFidc             = 161, // 3.35us
        .tCorr             = 244, // 5.08us
        .tDem              = 783, // 16.31us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(65),
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(50),
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(64),


        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 9},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 2, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 5},
            /*TPM = 20US*/{.magnIteration = 14},
            /*TPM = 40US*/{.magnIteration = 30}
        },

        .tAdj = { /* { pkt-tn, tn-tn} */
            {
                /* Initiator */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            },
            {
                /* Reflector */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            }
        },

        /* Sum of demodulation and modulation delay (HW only) */
        .tRtt = {
                  /* Initiator / Reflector */
                 .mode1 = {0, 0},
                 .mode3 = {0, 0}
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            },
            {
                /* Reflector */
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            }
        }
    },
    #else
    {   /* Phy_1M @ 4MHZ*/
        .baud       = 0x4000,
        .symmap     = 0x001F,
        .demmisc2   = 0x05F8,
        .demmisc3   = 0x1082,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 2112, // 8+32+4 bits = 44us
        .tTr               = 192,  // 4us

        /* Tuned */
        .tStartup          = 93,  // 1.937us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 245, // 5.109us (wait -> signal on shaper)
        .tPostProcessDiv1  = 936, // 19.5us
        .tPostProcessDiv4  = 234, // 19.5us
        .tInfiniteRx       = 60,  // 1.25us

        .tFidc             = 264, // 5.5us
        .tCorr             = 377, // 7.85us
        .tDem              = 914, // 19.05us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(65U), // MCE
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(49U), // MCE
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(64U), // MCE

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 1, .fracWait = 32,  .fracWaitAdj = 0},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 3},
            /*TPM = 20US*/{.magnIteration = 6},
            /*TPM = 40US*/{.magnIteration = 14}
        },

        .tAdj = { /* { pkt-tn, tn-tn} */
            {
                /* Initiator */
                .mode0 = {-293, 0},
                .mode1 = {-293, 0},
                .mode2 = {-149, +112},
                .mode3 = {-293, +26}
            },
            {
                /* Reflector */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {-48, -456},
                .mode3 = {0, -504}
            }
        },

        /* Sum of demodulation and modulation delay (HW only) */
        .tRtt = {
                  /* Initiator / Reflector */
                 .mode1 = {601, 607},
                 .mode3 = {601, 607}
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {+48, 0},
                .mode3 = {+48, 0}
            },
            {
                /* Reflector */
                .mode2 = {+84, 0},
                .mode3 = {+84, 0}
            }
        }
    },
    #endif
    {   /* Phy_2M */
        .baud       = 0x8000,
        .symmap     = 0x002E,
        .demmisc2   = 0x04F8,
        .demmisc3   = 0x1081,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 1248, // 16+32+4bit = 26us
        .tTr               = 96,   // 2us

        /* Tuned */
        .tStartup          = 95,   // 1.979us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 142,  // 2.957us (wait -> signal on shaper)
        .tPostProcessDiv1  = 720,  // 15us
        .tPostProcessDiv4  = 180,  // 15us
        .tInfiniteRx       = 60,   // 1.25us

        .tFidc             = 146, // 3.05us
        .tCorr             = 204, // 4.25us
        .tDem              = 565, // 11.77us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(46U), // MCE
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(32U), // MCE
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(46U), // MCE

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 9},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 2, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 5},
            /*TPM = 20US*/{.magnIteration = 14},
            /*TPM = 40US*/{.magnIteration = 30}
        },

        .tAdj = {
            {
                /* Initiator */
                .mode0 = {-188, 0},
                .mode1 = {-188, 0},
                .mode2 = {-138, +59},
                .mode3 = {-188, 0}
            },
            {
                /* Reflector */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {-38, -512},
                .mode3 = {-60, -456}
            }
        },

        /* Sum of demodulation and modulation delay (HW only) */
        .tRtt = {
                  /* Initiator / Reflector */
                 .mode1 = {336, 338},
                 .mode3 = {336, 338}
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {+48, 0},
                .mode3 = {+48, 0}
            },
            {
                /* Reflector */
                .mode2 = {+84, 0},
                .mode3 = {+84, 0}
            }
        }
    },
    {   /* Phy_2M2BT */
        .baud       = 0x8000,
        .symmap     = 0x002E,
        .demmisc2   = 0x04F8,
        .demmisc3   = 0x1081,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 1248, // 16+32+4bit = 26us
        .tTr               = 96,   // 2us

        /* Tuned */
        .tStartup          = 95,   // 1.979us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 142,  // 2.957us (wait -> signal on shaper)
        .tPostProcessDiv1  = 720,  // 15us
        .tPostProcessDiv4  = 180,  // 15us
        .tInfiniteRx       = 60,   // 1.25us

        .tFidc             = 146, // 3.05us
        .tCorr             = 204, // 4.25us
        .tDem              = 565, // 11.77us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(46U), // MCE
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(32U), // MCE
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(46U), // MCE

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 9},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 2, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 5},
            /*TPM = 20US*/{.magnIteration = 14},
            /*TPM = 40US*/{.magnIteration = 30}
        },

        .tAdj = {
            {
                /* Initiator */
                .mode0 = {-188, 0},
                .mode1 = {-188, 0},
                .mode2 = {-138, +59},
                .mode3 = {-188, 0}
            },
            {
                /* Reflector */
                 .mode0 = {0, 0},
                 .mode1 = {0, 0},
                .mode2 = {-38, -512},
                .mode3 = {-60, -456}
            }
        },

        /* Sum of demodulation and modulation delay (HW only) */
        .tRtt = {
                  /* Initiator / Reflector */
                 .mode1 = {336, 338},
                 .mode3 = {336, 338}
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {+48, 0},
                .mode3 = {+48, 0}
            },
            {
                /* Reflector */
                .mode2 = {+84, 0},
                .mode3 = {+84, 0}
            }
        }
    }
};

/* Frequency compensation value due to the fixed CMIXN value use. Resolution is 4x FOFF unit.
   Calculated based on the formula:
   foffError = 4x ((((1<<21) * fif) / (BLE_CS_BASE_FREQ_MHZ + pStepI->channelIdx) / 1e3)
             - ((1<<21) * (1024 - pStepI->cmixn) / 288 / 1024)); */
const int8_t foffErrorLut[BLE_CS_NUM_CHANNELS] = {
    /*2402 MHz =*/  38, 34, 34, 34, 30, 30, 30, 26,
    /*2410 MHz =*/  26, 26, 26, 22, 22, 22, 18, 18, 18, 14,
    /*2420 MHz =*/  14, 14, 10, 10, 10, 10,  6,  6,  6,  2,
    /*2430 MHz =*/   2,  2, -2, -2, -2, -2, -6, -6, -6,-10,
    /*2440 MHz =*/ -10,-10,-14,-14,-14,-14,-18,-18,-18,-22,
    /*2450 MHz =*/ -22,-22,-26,-26,-26,-26,-30,-30,-30,-34,
    /*2460 MHz =*/ -34,-34,-34,-38,-38,-38,-42,-42,-42,-46,
    /*2470 MHz =*/ -46,-46,-46,-50,-50,-50,-54,-54,-54,-54
};

/* Look up table of payload length in units of MCE Timer at rate of [1M]. Scaling dynamically if needed. */
const uint16_t payloadLut[RCL_CmdBleCs_Payload_Length] = {
    /*0 bits =*/   RCL_BLE_CS_US_TO_MCE_TIMER(0U),
    /*32 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(32U),
    /*64 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(64U),
    /*96 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(96U),
    /*128 bits =*/ RCL_BLE_CS_US_TO_MCE_TIMER(128U)
};

/* Forward declarations */
static RCL_MultiBuffer* RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(List_List *pHead, uint16_t numBytes);
static void RCL_Handler_BLE_CS_configureTxRxFifo(RCL_CmdBleCs* pCmd);
static void RCL_Handler_BLE_CS_retrieveAndStoreNextResult(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState);
static void RCL_Handler_BLE_CS_fetchAndforwardNextStep(RCL_CmdBleCs* pCmd);
static RCL_Events RCL_Handler_BLE_CS_preFillTxBuffer(RCL_CmdBleCs* pCmd);
static RCL_Events RCL_Handler_BLE_CS_readWriteBuffer(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState);
static bool RCL_Handler_BLE_CS_transferFinishedBuffers(List_List *pSrc, List_List *pDst, bool forceBufferToFinishState);
static void RCL_Handler_BLE_CS_configureS2R(RCL_CmdBleCs *pCmd);
static RCL_Events RCL_Handler_BLE_CS_readS2RSamples(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_readStatistics(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_preprocessCommand(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_preprocessStep(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_Step *pStep, RCL_CmdBleCs_Step_Internal *pStepI);
static RCL_CmdBleCs_StepResult_Internal* RCL_Handler_BLE_CS_fetchNextStepResult(RCL_CmdBleCs *pCmd);
static int16_t RCL_Handler_BLE_CS_convertFreqOffset(int16_t foffMeasured, bool ceil);
static int16_t RCL_Handler_BLE_CS_convertRtt(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_StepMode mode, uint8_t channel, uint8_t payload, bool secondToneExtensionSlot, uint32_t rtt, uint16_t corrBefore, uint16_t corrPeak, uint16_t corrAfter);
static uint32_t RCL_Handler_BLE_CS_convertPct(const RCL_CmdBleCs_IQSample *pPct, const RCL_CmdBleCs_PctCompEntry *pComp);
static uint8_t RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna(const RCL_CmdBleCs *pCmd, uint8_t antennaPermIdx, uint8_t toneIdx);
static uint8_t RCL_Handler_BLE_CS_calcQ3(uint16_t qMin, uint16_t qMax, uint16_t qAvg);
static uint8_t RCL_Handler_BLE_CS_convertPctQuality(uint16_t qMin, uint16_t qMax, uint16_t qAvg, bool toneExtensionSlot, bool toneExpected, bool toneQualityOverride);
static uint16_t RCL_Handler_BLE_CS_estimateStepResultLength(RCL_CmdBleCs *pCmd,RCL_CmdBleCs_StepResult_Internal* src);
static uint16_t RCL_Handler_BLE_CS_convertStepResult(RCL_CmdBleCs* pCmd, uint8_t *dst, RCL_CmdBleCs_StepResult_Internal* src);
static RCL_CommandStatus RCL_Handler_BLE_CS_findPbeErrorEndStatus(uint16_t pbeEndStatus);
static bool RCL_Handler_BLE_CS_filterDC(uint16_t max, uint16_t min, uint16_t thr);
static void RCL_Handler_BLE_CS_rotateVector(int16_t *pct_i, int16_t *pct_q, int16_t theta);

/*
 *  ======== Traverse multibuffer list looking for space ========
 */
static RCL_MultiBuffer* RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(List_List *pHead, uint16_t numBytes)
{
    /* Start search from the head of list */
    RCL_MultiBuffer *pBuffer = RCL_MultiBuffer_head(pHead);

    /* Traverse the chain of buffers and find the first free one */
    do {
        pBuffer = RCL_MultiBuffer_findFirstWritableBuffer(pBuffer);

        /* Avoid NULL pointer dereferencing */
        if (pBuffer != NULL)
        {
            /* Check for available space */
            if (pBuffer->length - pBuffer->tailIndex >= numBytes)
            {
                /* Mark the buffer to be written */
                pBuffer->state = RCL_BufferStateInUse;

                break;
            }
            else
            {
                /* The buffer will not fit the incoming number of bytes */
                pBuffer->state = RCL_BufferStateFinished;
                bleCsHandlerState.ble_cs.firstBuffer = false;
            }
        }
    } while (pBuffer != NULL);

    return (pBuffer);
}

/*
 *  ======== Transfer all buffers marked as finished from one list to another ========
 */
static bool RCL_Handler_BLE_CS_transferFinishedBuffers(List_List *pSrc, List_List *pDst, bool forceBufferToFinishState)
{
    /* Initialize return value */
    bool callbackEvent = false;
    RCL_MultiBuffer *pBuffer = NULL;

    /* Transfer the used buffers */
    do
    {
        pBuffer = RCL_MultiBuffer_head(pSrc);

        if (pBuffer != NULL)
        {
            if (forceBufferToFinishState)
            {
                /* At the end of the subevent, we transfer all unused buffers to the done queue */
                pBuffer->state = RCL_BufferStateFinished;
            }

            if (pBuffer->state == RCL_BufferStateFinished)
            {
                /* Pop from list and add to done list */
                RCL_MultiBuffer *pBuff = RCL_MultiBuffer_get(pSrc);
                RCL_MultiBuffer_put(pDst, pBuff);

                /* Trigger callback side effect*/
                callbackEvent = true;
            }
            else
            {
                break;
            }
        }
    } while (pBuffer != NULL);

    return (callbackEvent);
}

/*
 *  ======== Configure the BUFRAM size and interrupts for BLE CS ========
 */
static void RCL_Handler_BLE_CS_configureTxRxFifo(RCL_CmdBleCs* pCmd)
{
    /* Calculate the common denominator: the number of steps in the TX and RX FIFO must be equal.
       This is to ensure that waking up only on the RX threshold event happens before the TX fifo underflows. */
    const uint16_t N = BLE_CS_TXRXFIFO_SIZE * sizeof(uint32_t) / (sizeof(RCL_CmdBleCs_Step_Internal) + sizeof(RCL_CmdBleCs_StepResult_Internal));

    const uint16_t txFifoSize = N * sizeof(RCL_CmdBleCs_Step_Internal) / sizeof(uint32_t);
    const uint16_t rxFifoSize = N * sizeof(RCL_CmdBleCs_StepResult_Internal) / sizeof(uint32_t);

    const uint16_t txFifoBase = BLE_CS_TXRXFIFO_BASE_ADDR;
    const uint16_t rxFifoBase = txFifoBase + txFifoSize;

    /* Override the FIFO location and size */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) = txFifoBase;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) = txFifoSize;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) = rxFifoBase;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) = rxFifoSize;

    /* Reset FIFOs to have a clean start */
    /* Writing to FCMD is safe since the PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = LRFDPBE_FCMD_DATA_FIFO_RESET;

    /* Calculate how many entries can be stored simultaneous in given size of tx/rx fifos */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWBTHRS) = (N - 1U) * sizeof(RCL_CmdBleCs_Step_Internal);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = (N - 1U) * sizeof(RCL_CmdBleCs_StepResult_Internal);

    /* FIFO pointers should auto-commit/auto-dealloc, enable threshold events */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0)   = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) | (LRFDPBE_FCFG0_TXACOM_M | LRFDPBE_FCFG0_TXADEAL_M | LRFDPBE_FCFG0_RXACOM_M | LRFDPBE_FCFG0_RXADEAL_M);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0)   = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) & (~(LRFDPBE_FCFG0_RXIRQMET_M | LRFDPBE_FCFG0_TXIRQMET_M));

    /* Clear any interrupts left from uninitialized fifos */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_EVTCLR1)  =  (LRFDPBE_EVTCLR1_RXRDBTHR_M |  LRFDPBE_EVTCLR1_RXWRBTHR_M | LRFDPBE_EVTCLR1_TXRDBTHR_M | LRFDPBE_EVTCLR1_TXWRBTHR_M);
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) | (LRFDDBELL_ICLR0_RXFIFO_M | LRFDDBELL_ICLR0_TXFIFO_M);
}

/*
 *  ======== Fill the BLE CS step descriptors into the BUFRAM TX FIFO ========
 */
static RCL_Events RCL_Handler_BLE_CS_preFillTxBuffer(RCL_CmdBleCs* pCmd)
{
    /* Initialize return value */
    RCL_Events events = {.value = 0};

    /* Calculate how many additional step will fit (which might be all) */
    uint16_t nWritable  = (HWREGH_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE) / (uint16_t) sizeof(RCL_CmdBleCs_Step_Internal));
    uint16_t nRemaining = (pCmd->mode.repeatSteps) ? (pCmd->mode.nSteps) : (pCmd->mode.nSteps - pCmd->stats->nStepsWritten);
    uint16_t nBatch     = (nWritable < nRemaining) ? nWritable : nRemaining;

    /* Limited time is available when we start the command (ABS_START_TIME_OFFSET),
        so the first batch is reduced */
    if (pCmd->stats->nStepsWritten == 0U)
    {
        nBatch = ((nBatch < BLE_CS_FIRST_BATCH_SIZE) ? nBatch :  (uint16_t) BLE_CS_FIRST_BATCH_SIZE);
    }

    /* Transfer the calculated number of steps into the fifo */
    for (uint16_t i=0; i<nBatch; i++)
    {
        RCL_Handler_BLE_CS_fetchAndforwardNextStep(pCmd);
    }

    /* Transfer the used buffers, should trigger a callback if any */
    events.txBufferFinished =  RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->stepBuffers, &pCmd->stepBuffersDone, false) ? 1U : 0U;

    return (events);
}

/*
 *  ======== Write the BLE CS Steps to the BUFRAM TX fifo ========
 */
static void RCL_Handler_BLE_CS_fetchAndforwardNextStep(RCL_CmdBleCs* pCmd)
{
    /* Default return value */
    RCL_CmdBleCs_Step *pStep = NULL;

    /* Buffers are served on a FIFO basis */
    RCL_MultiBuffer *pStepBuffer = RCL_MultiBuffer_head(&pCmd->stepBuffers);

    /* Handle buffer boundaries within a batch */
    pStepBuffer = RCL_MultiBuffer_findFirstWritableBuffer(pStepBuffer);
    if (pStepBuffer != NULL)
    {
        /* Flag the buffer */
        if (pStepBuffer->state != RCL_BufferStateInUse)
        {
            /* Mark buffer that it is being consumed */
            pStepBuffer->state = RCL_BufferStateInUse;

            /* Update the total number of steps we are aware of at this point */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_MODE) = pCmd->mode.val;
        }

        /* Point to the beginning of step list */
        pStep = (RCL_CmdBleCs_Step *) &pStepBuffer->data[0];

        /* Verify that there is enough bytes in the buffer */
        if ((pStepBuffer->headIndex + sizeof(RCL_CmdBleCs_Step)) <= pStepBuffer->tailIndex)
        {
            /* Point to the next entry */
            pStep += pStepBuffer->headIndex/sizeof(RCL_CmdBleCs_Step);

            /* Decompress and calculate internal parameters on step */
            RCL_Handler_BLE_CS_preprocessStep(pCmd, pStep, &step);

            /* Send it to PBE */
            uint32_t *ptr = (uint32_t *) &step;
            for(uint8_t j=0; j<sizeof(RCL_CmdBleCs_Step_Internal)/sizeof(uint32_t); j++)
            {
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = *(ptr + j);
            }

            /* The step have been consumed */
            pCmd->stats->nStepsWritten++;

            pStepBuffer->headIndex += (uint16_t) sizeof(RCL_CmdBleCs_Step);

            /* This buffer is exhausted, or end of subevent */
            if (pStepBuffer->headIndex == pStepBuffer->tailIndex)
            {
                if ((bool)pCmd->mode.repeatSteps == false)
                {
                    /* Update state and move the buffer */
                    pStepBuffer->state = RCL_BufferStateFinished;
                }
                else
                {
                    /* Pretend that this is the beginning of the sequence */
                    pStepBuffer->headIndex = 0;
                    pCmd->stats->nStepsWritten = 0;
                }
            }
        }
    }
}

/*
 *  ======== Read the BLE CS Step results from the BUFRAM RX fifo ========
 */
static void RCL_Handler_BLE_CS_retrieveAndStoreNextResult(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState)
{
    uint32_t *ptr = (uint32_t *) &stepResult;
    for(uint8_t j=0; j<sizeof(RCL_CmdBleCs_StepResult_Internal)/sizeof(uint32_t); j++)
    {
        *(ptr+j) = HWREG_READ_LRF(LRFDRXF_BASE + LRFDRXF_O_RXD);
    }

    /* Update counters */
    if ((RCL_CmdBleCs_StepMode) stepResult.mode == RCL_CmdBleCs_StepMode_0)
    {
        pCmd->stats->nMode0++;
        if ((RCL_CmdBleCs_PacketResult) stepResult.pktResult != RCL_CmdBleCs_PacketResult_Lost)
        {
            pCmd->stats->nMode0Ok++;
        }
    }

    if (((RCL_CmdBleCs_StepMode) stepResult.mode == RCL_CmdBleCs_StepMode_2) ||
        ((RCL_CmdBleCs_PacketResult)stepResult.pktResult == RCL_CmdBleCs_PacketResult_Ok))
    {
        pCmd->stats->nRxOk++;
    }
    else
    {
        pCmd->stats->nRxNok++;
    }

    /* Pop and fill the next container */
    RCL_CmdBleCs_StepResult_Internal *pResult = RCL_Handler_BLE_CS_fetchNextStepResult(pCmd);
    if (pResult != NULL)
    {
        memcpy(pResult, (RCL_CmdBleCs_StepResult_Internal *) &stepResult, sizeof(RCL_CmdBleCs_StepResult_Internal));
    }

    /* Identify HCI compression size */
    uint16_t requiredSpaceInBytes = RCL_Handler_BLE_CS_estimateStepResultLength(pCmd, (RCL_CmdBleCs_StepResult_Internal *) &stepResult);

    /* Alternative HCI destination */
    RCL_MultiBuffer *pResultBuffer = RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(&pCmd->resultBuffers, requiredSpaceInBytes);

    /* Increment if either internal or HCI format is used */
    if (pResult || pResultBuffer)
    {
        pCmd->stats->nResultsRead++;
    }

    /* Avoid NULL pointer dereferencing */
    if (pResultBuffer != NULL)
    {
        if (bleCsHandlerState.ble_cs.firstBuffer)
        {
            /* Decode the start of the segment */
            RCL_CmdBleCs_SubeventResults *pSubeventResults = (RCL_CmdBleCs_SubeventResults *) pResultBuffer->data;

            /* Initialize header in an empty buffer */
            if (pResultBuffer->tailIndex == 0U)
            {
                /* Fill out the static frame info */
                pSubeventResults->subeventCode     = RCL_CMD_BLE_CS_SUBEVENT_RESULTS_OPCODE;
                pSubeventResults->numStepsReported = 0;
                pSubeventResults->numAntennaPath   = pCmd->stats->numAntennaPath;

                /* Increment tail with header length */
                RCL_MultiBuffer_commitBytes(pResultBuffer, sizeof(RCL_CmdBleCs_SubeventResults));
            }

            /* Update the HCI header */
            pSubeventResults->numStepsReported     += 1U;
            pSubeventResults->subeventDoneStatus   = (uint8_t) (pCmd->mode.nSteps != pCmd->stats->nResultsRead);

            /* Only available after AGC is locked
             * RPL = IQ[dBm] - 20*log(IQ/2048) */
            pSubeventResults->referencePowerLevel = -(int8_t) HWREGB_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_RFGAIN);

            /* Only available after last mode-0 step */
            pSubeventResults->frequencyCompensation = ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
                                                    ? RCL_Handler_BLE_CS_convertFreqOffset((int16_t) (HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP) << 2), true)
                                                    : (int16_t) RCL_CMD_BLE_CS_FREQCOMP_NA;
        }
        else
        {
            /* Decode the start of the segment */
           RCL_CmdBleCs_SubeventResultsContinue *pSubeventResultsContinue = (RCL_CmdBleCs_SubeventResultsContinue *) pResultBuffer->data;

           /* Initialize header in an empty buffer */
           if (pResultBuffer->tailIndex == 0U)
           {
               /* Fill out the static frame info */
               pSubeventResultsContinue->subeventCode     = RCL_CMD_BLE_CS_SUBEVENT_RESULTS_CONTINUE_OPCODE;
               pSubeventResultsContinue->numStepsReported = 0;
               pSubeventResultsContinue->numAntennaPath   = pCmd->stats->numAntennaPath;

               /* Increment tail with header length */
               RCL_MultiBuffer_commitBytes(pResultBuffer, sizeof(RCL_CmdBleCs_SubeventResultsContinue));
           }

           /* Update the HCI header */
           pSubeventResultsContinue->numStepsReported   += 1U;
           pSubeventResultsContinue->subeventDoneStatus  = (uint8_t) (pCmd->mode.nSteps != pCmd->stats->nResultsRead);
        }

        /* Decode the offset of data field */
        uint8_t *pResult = RCL_MultiBuffer_getNextWritableByte(pResultBuffer);

        /* Compress and write the data */
        uint32_t nBytes = RCL_Handler_BLE_CS_convertStepResult(pCmd, pResult, (RCL_CmdBleCs_StepResult_Internal *) &stepResult);

        /* Commit the pointers in the buffer */
        RCL_MultiBuffer_commitBytes(pResultBuffer, nBytes);

        /* Force close the multibuffer, even if there is more space left */
        if ( ((bool)pCmd->mode.repeatSteps == false) && (pCmd->mode.nSteps == pCmd->stats->nResultsRead) )
        {
            pResultBuffer->state = RCL_BufferStateFinished;
        }
        else if (forceBufferToFinishState)
        {
            pResultBuffer->state = RCL_BufferStateFinished;
        }
        else
        {
            /* Do nothing */
        }
    }
}

/*
 *  ======== Read the BLE CS Step results from the BUFRAM RX fifo ========
 */
static RCL_Events RCL_Handler_BLE_CS_readWriteBuffer(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState)
{
    /* Initialize return value */
    RCL_Events events = {.value = 0};

    /* Calculate how many result entries are available in rx fifo (might be all that has left) */
    uint16_t nBatch  = HWREGH_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) /  ((uint16_t) sizeof(RCL_CmdBleCs_StepResult_Internal));

    /* Read out the calculated number of entries */
    for (uint16_t i = 0; i < nBatch; i++)
    {
        /* Retrieve all that's available and terminate*/
        bool forceTerminate = (forceBufferToFinishState && (i == nBatch - 1U));

        RCL_Handler_BLE_CS_fetchAndforwardNextStep(pCmd);
        RCL_Handler_BLE_CS_retrieveAndStoreNextResult(pCmd, forceTerminate);
    }

    /* Transfer the used buffers, should trigger a callback if any */
    events.rxBufferFinished = RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->resultBuffers, &pCmd->resultBuffersDone, forceBufferToFinishState) ? 1U : 0U;
    events.txBufferFinished = RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->stepBuffers, &pCmd->stepBuffersDone, false) ? 1U : 0U;

    /* Reduce the batch size if there is only a few entries missing */
    int16_t nRemaining = (int16_t) (pCmd->mode.nSteps - pCmd->stats->nResultsRead);
    if (nRemaining <= 0)
    {
        if ((bool) pCmd->mode.repeatSteps == false)
        {
            /* No more results expected, set the threshold to the max */
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = 0x3FFU;
        }
    }
    else
    {
        if ((pCmd->mode.nSteps - pCmd->stats->nResultsRead) < nBatch)
        {
            /* Reduce the Fifo threshold to number of remaining steps */
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = (nRemaining * (int16_t)(sizeof(RCL_CmdBleCs_StepResult_Internal)));
        }
    }

    return (events);
}


/*
 *  ======== Initialize the S2R engine ========
 */
static void RCL_Handler_BLE_CS_configureS2R(RCL_CmdBleCs *pCmd)
{
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_S2RRAM_M | LRFDDBELL_CLKCTL_S2R_M);

    /* Access the list of multibuffers */
    RCL_MultiBuffer *pS2rBuffer = RCL_MultiBuffer_head(&pCmd->s2rBuffers);

    /* Only set up S2R, if there is buffer on the list */
    if (pS2rBuffer != NULL)
    {
        uint8_t rate = (pCmd->mode.phy) ? (1U) : (0U);

        /* Store 32bit words in S2R (offset 3072) memory; don't arm yet */
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_START) = BLE_CS_S2R_MEMORY_OFFSET;
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_STOP)  = HWREG_READ_LRF(LRFDS2R_BASE + LRFDS2R_O_START) + (RCL_BLE_CS_MAX_S2R_LEN >> rate);
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_CFG)   = LRFDS2R_CFG_CTL_EN
                                                        | LRFDS2R_CFG_SEL_FRONTEND
                                                        | LRFDS2R_CFG_TRIGMODE_ONESHOT
                                                        | LRFDS2R_CFG_LAST0_DIS;
    }
}

/*
 *  ======== Read the S2R memory ========
 */
RCL_Events RCL_Handler_BLE_CS_readS2RSamples(RCL_CmdBleCs *pCmd)
{
    RCL_Events events = {.value = 0};

    uint16_t s2rLength  = (uint16_t) sizeof(S2RSample) * HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTWORDSIZE);
    uint16_t dataLength = (uint16_t) sizeof(RCL_CmdBleCs_S2r) + s2rLength;

    /* Access the list of multibuffers */
    RCL_MultiBuffer *pS2rBuffer = RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(&pCmd->s2rBuffers, dataLength);

    if (pS2rBuffer != NULL)
    {
        /* Decode the next free slot in the multibuffer */
        RCL_CmdBleCs_S2r *pS2rData = (RCL_CmdBleCs_S2r *) RCL_MultiBuffer_getNextWritableByte(pS2rBuffer);

        /* Store the step index */
        pS2rData->phy        = pCmd->mode.phy;
        pS2rData->idx        = HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTIDX);
        pS2rData->channel    = HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTCHIDX);
        pS2rData->payloadLen = HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOADLEN);
        /* 32 bit access */
        pS2rData->payload0   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD0L);
        pS2rData->payload1   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD1L);
        pS2rData->payload2   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD2L);
        pS2rData->payload3   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD3L);

        /* Number of valid samples to be copied out with 32bit operation
        Need to calculate with 0/32/64/96/128 bit @ 8MHz/4MHz front-end sampling */
        pS2rData->iqLength = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTWORDSIZE);

        /* Store the data, unwrap the loop for faster copying */
        uint32_t *src = (uint32_t *)S2R_RAM_BASE_ADDR;
        uint32_t *dst = (uint32_t *)&pS2rData->data;

        #ifdef NO_INLINE_ASM
            for(uint16_t i=0; i<(pS2rData->iqLength >> 3); i++)
            {
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
            }
        #else
            for(uint16_t i=0; i<(pS2rData->iqLength >> 2); i++)
            {
                __asm(
                "LDMIA %0!, {r4, r5, r6, r7} \n"
                "STMIA %1!, {r4, r5, r6, r7} \n"
                : "+r" (src), "+r" (dst) :
                : "r4", "r5", "r6", "r7");
            }
        #endif

        /* Flag the entry */
        RCL_MultiBuffer_commitBytes(pS2rBuffer, dataLength);

        /* Update the statistics */
        pCmd->stats->nS2RDone++;

        /* Force close the buffer, even if there is more space left */
        pS2rBuffer->state = RCL_BufferStateFinished;

        /* Transfer the used buffers, should trigger a callback if any */
        events.swTriggered = (uint8_t) (RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->s2rBuffers, &pCmd->s2rBuffersDone, false));
    }

    return (events);
}

/*
 *  ======== Read the statistics from the PBE ========
 */
static void RCL_Handler_BLE_CS_readStatistics(RCL_CmdBleCs *pCmd)
{
    if (pCmd->stats != NULL)
    {
        pCmd->stats->nStepsDone = (uint8_t) HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_NSTEPSDONE);
        pCmd->stats->lastRssi   = (int8_t) HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_RSSILAST);
        pCmd->stats->lastFoff   = (int16_t) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFLAST);
        pCmd->stats->foffComp   = (int16_t) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP);
        pCmd->stats->rxGain     = (uint16_t) HWREGH_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_RFGAIN);

        /* Convert to API units */
        pCmd->stats->rxGain   = BLE_CS_RX_GAIN_DB_TO_OVERRIDE(pCmd->stats->rxGain);
        pCmd->stats->foffComp = BLE_CS_FOFF_COMP_TO_OVERRIDE(pCmd->stats->foffComp);
    }
}

/*
 *  ======== Load the command and step descriptors into LRF REGISTERS/BUFRAM ========
 */
static void RCL_Handler_BLE_CS_preprocessCommand(RCL_CmdBleCs *pCmd)
{
    /* Force antenna switching time to zero for single antenna path per spec */
    if (pCmd->antennaConfig.select == 0U)
    {
        pCmd->timing.tSw = 0;
    }

    /* Decode mapping of configuration to antennas */
    const RCL_AntennaConfig_t *antennaEntry = &antennaConfig[pCmd->antennaConfig.select];

    /* Decode the Phy specific settings */
    const RCL_PhyConfig_t *config = &phyConfigLut[pCmd->mode.phy];

    /* Clear output statistics */
    if (pCmd->stats != NULL)
    {
        (void) memset((void *)pCmd->stats, 0, sizeof(RCL_CmdBleCs_Stats));

        pCmd->stats->lastRssi = LRF_RSSI_INVALID;
        pCmd->stats->numAntennaPath = antennaEntry->numPath;

        bleCsHandlerState.ble_cs.firstBuffer = true;
    }

    /* Mode */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_MODE)   = pCmd->mode.val;

    /* Antenna */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANTN)   = antennaEntry->numPath;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANTMSK) = pCmd->antennaConfig.gpoMask;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT0)   = pCmd->antennaConfig.gpoVal[0];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT1)   = pCmd->antennaConfig.gpoVal[1];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT2)   = pCmd->antennaConfig.gpoVal[2];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT3)   = pCmd->antennaConfig.gpoVal[3];

    /* Timing */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TFCS)    = (uint16_t) (pCmd->timing.tFcs - (TPLT + config->tStartup)); // Pilot tone + startup time is included into the TFCS budget
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPM)     = pCmd->timing.tPm;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TIP1)    = pCmd->timing.tIp1;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TIP2)    = pCmd->timing.tIp2;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSW)     = pCmd->timing.tSw;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSWADJA) = pCmd->timing.tSwAdjustA;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSWADJB) = pCmd->timing.tSwAdjustB;

    /* Frequency dependent config (2402MHz + channel dependent correction by RFE */
    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC1_DEMFRAC0) = 0x0D800000;     // P: Constant
    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC3_DEMFRAC2) = 0x0000399A;     // Q: Being dynamically scaled by RFE per channel

    /* Shaper gain */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) = 0x1824;

    /* Configure Rx Gain Policy */
    uint16_t rfGain = BLE_CS_RX_GAIN_AUTO_DEFAULT;
    switch (pCmd->rxGainPolicy)
    {
        /* SPARE0 register format:
           [0:7]   = Max gain RSSI threshold
           [8:11]  = Max gain index
           [12]    = 3/6 dB step selection */
        case (RCL_CmdBleCs_Policy_Cache):
                if (bleCsHandlerState.ble_cs.rxGainCacheValid == true)
                {
                    rfGain = bleCsHandlerState.ble_cs.rxGainCache;
                }
                else
                {
                    /* If no valid cache, fall back to auto mode */
                    pCmd->rxGainPolicy = RCL_CmdBleCs_Policy_Auto;
                }
                break;
        case (RCL_CmdBleCs_Policy_Manual):
                rfGain = pCmd->rxGainVal;
                break;
        case (RCL_CmdBleCs_Policy_Auto):
        default:
                bleCsHandlerState.ble_cs.rxGainCacheValid = false;
                break;
    }
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE0) = rfGain;

    /* Configure Frequency Offset Compensation Policy */
    uint16_t foffSum = 0;
    uint16_t foffNum = 0;
    switch (pCmd->foffPolicy)
    {
        /* FOFFSUM = 4xFOFF */
        case (RCL_CmdBleCs_Policy_Cache):
                if (bleCsHandlerState.ble_cs.foffCacheValid == true)
                {
                    foffSum = (uint16_t) bleCsHandlerState.ble_cs.foffCache;
                    foffNum = BLE_CS_FOFF_NUM_OVERRIDE;
                }
                else
                {
                    /* If no valid cache, fall back to auto mode */
                    pCmd->foffPolicy = RCL_CmdBleCs_Policy_Auto;
                }
                break;
        case (RCL_CmdBleCs_Policy_Manual):
                foffSum = (uint16_t) pCmd->foffVal;
                foffNum = BLE_CS_FOFF_NUM_OVERRIDE;
                break;
        case (RCL_CmdBleCs_Policy_Auto):
        default:
                bleCsHandlerState.ble_cs.foffCacheValid = false;
                break;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFSUM) = foffSum;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFNUM) = foffNum;

    RCL_CmdBleCs_Tpm lutIdx = RCL_CmdBleCs_Tpm_40us;
    if (pCmd->timing.tPm <= RCL_BLE_CS_US_TO_MCE_TIMER(20U))
    {
        lutIdx = RCL_CmdBleCs_Tpm_20us;
    }
    if (pCmd->timing.tPm <= RCL_BLE_CS_US_TO_MCE_TIMER(10U))
    {
        lutIdx = RCL_CmdBleCs_Tpm_10us;
    }

    /* MAFC gain */
    #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        /* Workaround for IQ swap */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC2) = config->demmisc2 | LRFDMDM_DEMMISC2_PDIFIQCONJEN;
    #else
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC2) = config->demmisc2;
    #endif

    /* Channel filter = 0.33 */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC1) = 0x0001;

    /* Fife IIR adaptation rate = 64 (provides good mode-0 frequency tolerance for both PHYs) */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMFIFE0) = 0x0007;

    /* Baudrate specific settings */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SPARE0)                      = config->pctConfig[lutIdx].val;
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUD)                        = config->baud;
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODSYMMAP0)                  = config->symmap;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE3)                      = config->magnConfig[lutIdx].val;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIOFFSET)                  = config->rssioffset;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_DEMMISC3)        = config->demmisc3;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPOSTPROCESS)    = config->tPostProcessDiv1;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPOSTPROCESSDIV) = config->tPostProcessDiv4;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTI0)    = config->tRxTimeoutI0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTI3)    = config->tRxTimeoutI3;

    /* Alias for dynamic parameters for calculations */
    uint16_t tIp1  = pCmd->timing.tIp1;
    uint16_t tIp2  = pCmd->timing.tIp2;
    uint16_t tPm   = pCmd->timing.tPm;
    uint16_t tFcs  = pCmd->timing.tFcs;
    uint16_t tSw   = pCmd->timing.tSw;
    uint16_t nPath = antennaEntry->numPath;

    /* Phy specific delays */
    uint16_t tStartup    = config->tStartup;
    uint16_t tPkt        = config->tPacket;
    uint16_t tCorr       = config->tCorr;
    uint16_t tDem        = config->tDem;
    uint16_t tTr         = config->tTr;
    uint16_t tFidc       = config->tFidc;
    uint16_t tTxModDelay = config->tTxModDelay;
    uint16_t tInfiniteRx = config->tInfiniteRx;

    /* Calculate base terms of step duration for each mode.
       Later can be extended with optional payload per step before sending it over to the PBE. */
    tStepLut[RCL_CmdBleCs_StepMode_0] = (tFcs + ((tPkt + TRD) << 1U) + TGD + tIp1 + TFM);
    tStepLut[RCL_CmdBleCs_StepMode_1] = (tFcs + ((tPkt + TPYL + TRD) << 1U) + tIp1);
    tStepLut[RCL_CmdBleCs_StepMode_2] = (tFcs + ((((tPm + tSw) * (nPath + 1U)) + TRD) << 1) + tIp2);
    tStepLut[RCL_CmdBleCs_StepMode_3] = (tFcs + ((tPkt + TPYL + TGD + ((tPm + tSw) * (nPath + 1U)) + TRD) << 1U) + tIp2);

    /* Adjustment of MCE timegrid */
    const RCL_Tadjust_t *tAdj = &config->tAdj[pCmd->mode.role];
    const RCL_Tadjust_t *tRtt = &config->tRtt;

    if ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
    {
        /* Calculate base terms of interlude period. Later will scale with payload. */

        /* TX */
        tAdjALut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[0];
        tAdjALut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[0];
        tAdjALut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[0]; // No packet
        tAdjALut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[0];

        /* RX */
        tAdjBLut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[1] + TRD + tIp1 - TPLT;
        tAdjBLut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[1] + TRD + tIp1 - TPLT;
        tAdjBLut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[1] + TRD + tIp2 + tSw + tFidc;
        tAdjBLut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[1] + TRD + tIp2 + tSw + tFidc;

        /* ToAD common term */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_1] = TPYL + TRD + tIp1 + tPkt + tRtt->mode1[0];
        tRttAdjustLut[RCL_CmdBleCs_StepMode_2] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_3] = TPYL + (TGD << 1) + (((tPm + tSw) * ((nPath << 1) + 1U))) + TRD + tIp2 + tPkt + tRtt->mode3[0];

        /* LIF */
        tPllRx[RCL_CmdBleCs_StepMode_0] = 0xFFFF;
        tPllRx[RCL_CmdBleCs_StepMode_1] = 0xFFFF;
        tPllRx[RCL_CmdBleCs_StepMode_2] = 0xFFFF;
        tPllRx[RCL_CmdBleCs_StepMode_3] = 0xFFFF;

        /* Initiator: timeout is hardcoded in the MCE in order to comply with the static timegrid.
           This parameter is therefor ignored.  */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTR013)   = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXWIDENINGR0)    = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPREMAININGR0) = 0;
    }
    else
    {
        /* RX */
        tAdjALut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[0] - tCorr + tTr + TRD + tIp1 - TPLT - tTxModDelay;
        tAdjALut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[0] - tCorr + tTr + TRD + tIp1 - TPLT - tTxModDelay;
        tAdjALut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[0] + tStartup + TPLT + tSw + tFidc;
        tAdjALut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[0] - tCorr + tTr + TGD + tSw + tFidc;

        /* TX */
        tAdjBLut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[1];
        tAdjBLut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[1];
        tAdjBLut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[1] - tFidc + TRD  + tIp2 - TPLT - tTxModDelay;
        tAdjBLut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[1] - tFidc + TRD  + tIp2 - TPLT - tTxModDelay;

        /* ToAD common term */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_1] = TPYL + TRD + tIp1 + tPkt - tRtt->mode1[1];
        tRttAdjustLut[RCL_CmdBleCs_StepMode_2] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_3] = TPYL + (TGD << 1) + (((tPm + tSw) * ((nPath << 1) + 1))) + TRD + tIp2 + tPkt - tRtt->mode3[1];

        /* LIF */
        tPllRx[RCL_CmdBleCs_StepMode_0] = 0xFFFF;
        tPllRx[RCL_CmdBleCs_StepMode_1] = 0xFFFF;
        tPllRx[RCL_CmdBleCs_StepMode_2] = RCL_BLE_CS_MCE_TIMER_TO_PREFREF(TPLT- tStartup + (tPm + tSw) * (nPath + 1));
        tPllRx[RCL_CmdBleCs_StepMode_3] = RCL_BLE_CS_MCE_TIMER_TO_PREFREF(TPLT- tStartup + (tPm + tSw) * (nPath + 1));

        /* The miminum value is defined by the static timegrid. Different for each datarate and implemented by the MCE. */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTR013) = config->tRxTimeoutRn;

        /* Handle infinite/extended RX timeout implemented by PBE */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXWIDENINGR0)
            = (pCmd->timing.tRxWideningR0 == 0xFFFFU)
            ? 0xFFFFU
            : RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(tFcs + (tPkt - tTr) + tDem + T3US + pCmd->timing.tRxWideningR0);

        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPREMAININGR0) =
          RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(0U - tDem + tTr + TRD + tIp1 + tPkt + TGD + TFM + TRD - tInfiniteRx);
    }

    /* Adjustment of antenna control per mode per phy */
    const RCL_Tadjust_t *tAnt = &config->tAnt[pCmd->mode.role & 1U];

    tAntALut[RCL_CmdBleCs_StepMode_0] = 0; /* NA - no antenna */
    tAntALut[RCL_CmdBleCs_StepMode_1] = 0; /* NA - no antenna */
    tAntALut[RCL_CmdBleCs_StepMode_2] = tAnt->mode2[0] + TPLT;
    tAntALut[RCL_CmdBleCs_StepMode_3] = tAnt->mode3[0] + TPLT + tPkt + TGD;

    tAntBLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA - no antenna */
    tAntBLut[RCL_CmdBleCs_StepMode_1] = 0; /* NA - no antenna */
    tAntBLut[RCL_CmdBleCs_StepMode_2] = tAnt->mode2[1];
    tAntBLut[RCL_CmdBleCs_StepMode_3] = tAnt->mode3[1];

    /* Enforce modulator and demodulator clock. RTL bug with automatic control. */
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_DEM_M | LRFDDBELL_CLKCTL_MOD_M);
}

/*
 *  ======== Preprocess the step ========
 */
static void RCL_Handler_BLE_CS_preprocessStep(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_Step *pStep, RCL_CmdBleCs_Step_Internal *pStepI)
{
    /* Decompress the HCI format into PBE internal format */
    pStepI->channelIdx     = pStep->channelIdx;
    pStepI->mode           = pStep->mode;
    pStepI->antennaPacket  = pStep->antennaPacket;
    pStepI->antennaPermIdx = pStep->antennaPermIdx;
    pStepI->toneExtension  = pStep->toneExtension;
    pStepI->payloadLen     = pStep->payloadLen;
    pStepI->aaTx           = pStep->aaTx;
    pStepI->aaRx           = pStep->aaRx;

    for (uint8_t i=0; i<RCL_BLE_CS_MAX_PAYLOAD_SIZE; i++)
    {
        pStepI->payloadTx[i] = pStep->payloadTx[i];
        pStepI->payloadRx[i] = pStep->payloadRx[i];
    }

    /* Decode the base term for the complete duration of the step */
    uint32_t tStep = tStepLut[pStepI->mode];
    int16_t tAdjA = tAdjALut[pStepI->mode];
    int16_t tAdjB = tAdjBLut[pStepI->mode];

    /* Scale with bit length and 1M/2M rate */
    uint8_t  rate = (pCmd->mode.phy) ? (1U) : (0U);
    int16_t tPyl = (payloadLut[pStepI->payloadLen]) >> rate;

    /* Extend with timing of optional payload */
    if (pStepI->payloadLen != 0U)
    {
        /* Adjustment only on Reflector */
        int16_t tAdj = ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                     ? (tPyl)
                     : (0U);

        /* Payload is only allowed for certain modes. */
        if ((RCL_CmdBleCs_StepMode) pStepI->mode == RCL_CmdBleCs_StepMode_1 ||
            (RCL_CmdBleCs_StepMode) pStepI->mode == RCL_CmdBleCs_StepMode_3)
        {
            /* Multiplied by two for combined effect of TX and RX */
            tStep += ((uint32_t) tPyl << 1);

            /* The duration from AA sync until the next activity scales with payload on reflector only */
            tAdjA += tAdj;
        }
        else
        {
            /* Enforce no payload for mode 0 & 2 */
            pStepI->payloadLen = 0;

            /* No adjustment needed */
            tPyl = 0;
        }
    }

    /* Configure the PBE with the scaled step duration */
    pStepI->tStep = RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(tStep);

    /* Configure the MCE with the scaled intermediate timegrid parameters */
    pStepI->tAdjustA = tAdjA;
    pStepI->tAdjustB = tAdjB;

    /* Antenna timing from beginning of step */
    pStepI->tAntennaA = tAntALut[pStepI->mode] + tPyl;
    pStepI->tAntennaB = tAntBLut[pStepI->mode];

    /* LIF duration per step */
    pStepI->tPllRx = (uint16_t) tPllRx[pStepI->mode];

    /* DC compensation */
    if ((pCmd->precalTable) && (pCmd->precalTable->valid))
    {
        pCmd->precalTable->callback(pCmd->precalTable,
                                    pStepI->channelIdx,
                                    &pStepI->dcComp[0],  /* High gain compensation */
                                    &pStepI->dcComp[1]); /* Low gain compensation */
    }
    else
    {
        pStepI->dcComp[0].i = 0;
        pStepI->dcComp[0].q = 0;
        pStepI->dcComp[1].i = 0;
        pStepI->dcComp[1].q = 0;
    }

    /* Antenna calculations */
    pStepI->antennaSequence = 0;

    /* Decode mapping of configuration to antennas */
    const RCL_AntennaConfig_t *antennaEntry = &antennaConfig[pCmd->antennaConfig.select];

    /*  Avoid indexing out of range */
    if (pStepI->antennaPermIdx < antennaEntry->numPerm)
    {
        /* Find the proper permutation pattern based on generic config and random step related selection.
            The same table is used, but we index the entries differently */
        uint8_t apn = antennaPermutation[pStepI->antennaPermIdx].apn;

        /* We reuse the same permutation table for 1:1, 1:N, N:1 and 2:2,
            but only use the appropriate number of entries from each row */
        for(uint8_t k1=0; k1<antennaEntry->numPath; k1++)
        {
            uint8_t apm = antennaEntry->ap[pCmd->mode.role & 1U].apn;

            /* Decode bitfields */
            uint8_t k2 = DECODE_ANTENNA(apn, k1);
            uint8_t k3 = DECODE_ANTENNA(apm, k2);

            /* Antenna sequence is stored as [15:12]=A4, [11:8]=A3, [7:4]=A2, [3:0]=A1.
                The PBE will decode it accordingly. */
            pStepI->antennaSequence |= ENCODE_ANTENNA(k3, k1);
        }
    }

    /* Look up the frequency offset actuation error (only used by mode 0) */
    pStepI->foffErr = (int16_t) foffErrorLut[pStepI->channelIdx];

    /* PCT phase compensation per antenna path (chronological order), applied by the radio
       when the reflector transmits with Inline PCT Transfer. Unused entries are left at zero. */
    for (uint8_t path = 0; path < RCL_BLE_CS_MAX_NUM_ANT; path++)
    {
        pStepI->inlinePctPhaseComp[path] = 0;
    }

    if (((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Reflector) && pCmd->mode.inlinePhase &&
        ((RCL_CmdBleCs_StepMode) pStepI->mode == RCL_CmdBleCs_StepMode_2 ||
         (RCL_CmdBleCs_StepMode) pStepI->mode == RCL_CmdBleCs_StepMode_3))
    {
        /* Only the phase is needed now. The magnitude is compensated when the result is read out. */
        RCL_CmdBleCs_PctComp pctComp = RCL_CMD_BLE_CS_PCT_COMP_DEFAULT;
        RCL_Handler_BLE_CS_getPctComp(pStepI->channelIdx, RCL_BLE_CS_PCT_COMP_SEL_PHASE, &pctComp);

        for (uint8_t toneIdx = 0; toneIdx < antennaEntry->numPath; toneIdx++)
        {
            uint8_t ant = RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna(pCmd, pStepI->antennaPermIdx, toneIdx);
            pStepI->inlinePctPhaseComp[toneIdx] = BLE_CS_PCT_PHASE_TO_INLINE(pctComp.ant[ant].phase);
        }
    }
}

/*
 *  ======== Fetch the next available step result container in the list and return a pointer to it ========
 */
static RCL_CmdBleCs_StepResult_Internal* RCL_Handler_BLE_CS_fetchNextStepResult(RCL_CmdBleCs *pCmd)
{
    RCL_CmdBleCs_StepResult_Internal *pResult = NULL;

    if ((pCmd->stats->nResultsRead < pCmd->mode.nSteps) && pCmd->results)
    {
        pResult = &pCmd->results[pCmd->stats->nResultsRead];
    }

    return (pResult);
}

/*
 *  ======== Update the rx gain and frequency compensation cache for later use ========
 */
static void RCL_Handler_BLE_CS_updateCache(RCL_CmdBleCs *pCmd)
{
    /* Only update the cache if the subevent executed in automatic gain control
       or frequency offset measurement mode, and at least 1 mode-0 step succeeded */
    if (pCmd->stats->nMode0Ok > 0)
    {
        if (pCmd->rxGainPolicy == RCL_CmdBleCs_Policy_Auto)
        {
            bleCsHandlerState.ble_cs.rxGainCache      = pCmd->stats->rxGain;
            bleCsHandlerState.ble_cs.rxGainCacheValid = true;
        }

        if (pCmd->foffPolicy == RCL_CmdBleCs_Policy_Auto)
        {
            bleCsHandlerState.ble_cs.foffCache      = pCmd->stats->foffComp;
            bleCsHandlerState.ble_cs.foffCacheValid = true;
        }
    }
}

/*
 *  ======== RCL_Handler_BLE_CS_convertFreqOffset ========
 */
static int16_t RCL_Handler_BLE_CS_convertFreqOffset(int16_t foffMeasured, bool ceil)
{
    /* Intermediate arithmetics on 32bit
       freqOffset = foff * 100 * 1e6 / 2^23
                  = foff * (100 * 1e6 / 2^7) / 2^16
                  = foff * 0xBEBC2 / 2^16 [0.01 ppm] */
    int32_t freqOffset = (int32_t) foffMeasured;
    freqOffset *= 0xBEBC2;
    freqOffset >>= 16;

    if (ceil == true)
    {
        /* Scale to 15 bit signed integer, as per the spec for certain HCI fields */
    freqOffset &= 0x7FFF;
    }

    return (int16_t)(freqOffset);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertRtt ========
 */
static int16_t RCL_Handler_BLE_CS_convertRtt(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_StepMode mode, uint8_t channel, uint8_t payloadLen, bool secondToneExtensionSlot,
                                             uint32_t rtt, uint16_t corrBefore, uint16_t corrPeak, uint16_t corrAfter)
{
    /* Raw RTT need to be compensated with:
       1) Remove nominal turn-around time T = TSY + TIP + TEXT + TPYL + ...
       2) Adjust with correlator before/after fractional approximation
       3) Initiator only: rebase onto the reflectors timegrid based on FFO
       4) Initiator only: Adjust with channel specific delays */
    int32_t toAD = (int32_t) rtt;

    /* Conversion from 2M/1M baudrate to 48M clock tick */
    uint8_t rateDiv = (pCmd->mode.phy) ? (1U) : (0U);

    /* Remove nominal turn-around time (adjust to the signal on the antenna) */
    toAD -= (int32_t) tRttAdjustLut[mode];

    /* Adjust with optional payload duration */
    toAD -= (int32_t)((payloadLut[payloadLen] >> rateDiv));

    /* Adjust with optional tone-extension slot for mode-3 */
    if (secondToneExtensionSlot == true)
    {
         toAD -= (int32_t)((pCmd->timing.tPm + pCmd->timing.tSw));
    }

    /* Compensation based on fractional information */
    float tCorr = 0.0f;

    if (corrBefore != corrAfter)
    {
        #if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            /* Due to missing HW on the CC27xx device, the LRF returns with constant value of 64.
               We approximate the true peak from the before/after values: peak = 64 - 0.5x abs(before - after) */
            if (corrAfter < corrBefore) corrPeak -= ((corrBefore - corrAfter) >> 1);
            else                        corrPeak -= ((corrAfter - corrBefore) >> 1);
        #endif

        /* 2M @ 8MHz / 1M @ 4Mhz */
        int16_t baud2tick_div2 = (pCmd->mode.phy) ? (3) : (6);
        int16_t corrB = (int16_t) corrBefore;
        int16_t corrA = (int16_t) corrAfter;
        int16_t corrP = (int16_t) corrPeak;

        /* Quadratic interpolation */
        tCorr = (float) (baud2tick_div2 * (corrB - corrA));
        tCorr /= (float)((corrB + corrA - (corrP << 1U)));
    }

    /* Due to the varying clock rates used in the front-end stage,
       the time need to be further compensated per channel */
    float c[3] = { /*1M*/0.12f, /*2M*/0.15f, /*2M2BT*/0.15f };

    float tChannel = c[pCmd->mode.phy] * (BLE_CS_MAX_CHANNEL - channel);

    /* Start with 48MHz ticks */
    float t = (float) toAD;

    /* Adjust initiator */
    if ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
    {
        /* Adjust with correlator before/after fractional detail */
        t += tCorr;

        /* Need to rebase to the reflector's timeframe based on FFO */
        int16_t foffComp = (int16_t) HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP);

        /* Convert to reflectors time frame:
           toAD = (1 + FFO) (ToA-ToD)
                = (1 + foff/2^21) (ToA-ToD) */
        t += ((float)foffComp) * t / (float)0x200000;

        /* Adjust per channel */
        t -= tChannel;
    }
    else
    {
        /* Adjust with correlator before/after fractional details */
        t -= tCorr;

        /* Adjust per channel */
        t += tChannel;
    }

    /* Convert from 48MHz ticks to 0.5ns units (HCI format) */
    t *= 41.6666f;

    /* Round */
    t += 0.5f;

    /* Return the adjusted timeticks */
    return ((int16_t) t);
}

/*
 *  ======== RCL_Handler_BLE_CS_rotateVector ========
 */
void RCL_Handler_BLE_CS_rotateVector(int16_t *pct_i, int16_t *pct_q, int16_t theta)
{
    /* Quickly return if nothing to do */
    if (theta != 0)
    {
        /* CORDIC implementation of rotating a vector with given angle
        *
        * theta = 16bit representation of the angle in [-pi = -32768, +pi = 32767] range to rotate the PCT with
        * pct_i = I component of PCT
        * pct_q = Q component of PCT
        * */
        #define PI_div2 (int16_t) (1 << (16-2))

        /* The LUT and normalization factor is generated by the following python expression:
        *
        * f = 1.0
        * for i in range(NBITS):
        *     x = np.arctan(1 / 2**i) / (np.pi/2) * (2**NBITS)
        *     atanLut += [ (np.floor)(x + 0.5) ]
        *
        *     f = (f * (2**(2*i) + 1)) / 2**(2*i)
        *
        * f = 1/np.sqrt(f) * (2**NBITS)
        * K = (np.floor) (f + 0.5)
        * */
        #define NBITS  (14U)
        #define K14    (9949)
        const uint16_t atanLut[NBITS] = { 8192, 4836, 2555, 1297, 651, 326, 163, 81, 41, 20, 10, 5, 3, 1 };

        /* Swap coordinates when angle is between [-pi,-pi/2] or [pi/2,pi] */
        int32_t x = ((int32_t) *pct_i);
        int32_t y = ((int32_t) *pct_q);
        if (theta > PI_div2)
        {
            theta -= PI_div2;
            x = -((int32_t) *pct_q);
            y = +((int32_t) *pct_i);
        }
        else if (theta < (-PI_div2))
        {
            theta += PI_div2;
            x = +((int32_t) *pct_q);
            y = -((int32_t) *pct_i);
        }
        else
        {
            /* Do nothing */
        }
        x *= K14;
        y *= K14;

        /* Initialize local variables */
        int32_t x1  = 0;
        int32_t y1  = 0;

        /* The direction follows the mathematical positive direction */
        int32_t phi = (int32_t)(-theta);

        /* Rotate iteratively */
        for (uint8_t i = 0; i < NBITS; i++)
        {
            if (phi < 0)
            {   /* Counter-clockwise */
                phi += (int32_t) atanLut[i];
                y1 = y + (x >> i);
                x1 = x - (y >> i);
            }
            else
            {   /* Clockwise */
                phi -= (int32_t) atanLut[i];
                y1 = y - (x >> i);
                x1 = x + (y >> i);
            }

            x = x1;
            y = y1;
        }

        /* Scale according to LUT normalization weight */
        *pct_i = (int16_t) (x >> NBITS);
        *pct_q = (int16_t) (y >> NBITS);
    }
}

/*
 *  ======== RCL_Handler_BLE_CS_getPctComp ========
 *
 *  Default implementation: the same constant delay (RCL_BLE_CS_PHASE_DELAY_PS) on all antennas and
 *  channels, unity magnitude. Can be overridden by the application.
 */
__attribute__((weak)) void RCL_Handler_BLE_CS_getPctComp(uint8_t channelIdx, uint8_t compSelect, RCL_CmdBleCs_PctComp *pComp)
{
    /* Caller has already initialized magnitude to unity, and phase to zero */
    if ((compSelect & RCL_BLE_CS_PCT_COMP_SEL_PHASE) != 0U)
    {
        /* Report phase compensation, calculated from a constant phase-delay */

        const uint32_t PERIOD_UNITS = 1000000UL;
        uint32_t freqMHz = 2402UL + channelIdx;

        /* 1. Calculate the raw product (freqMHz * t_ps) */
        uint32_t product = freqMHz * RCL_BLE_CS_PHASE_DELAY_PS;

        /* 2. Optimized Modulo: cycles = product % 1,000,000
         * We use the magic constant for 1/1000000 in 32.32 fixed-point:
         * (2^32 / 1000000) = 4294.967296 -> rounded down to 4294, so that the quotient is never
         * too large (which would make 'cycles' underflow). It can be one too small, which is
         * corrected below.
         * Note: 'product' must not exceed 999,999,999 for 32-bit math to not overflow.
         */
        uint32_t quotient = (uint32_t)(((uint64_t)product * 4294UL) >> 32);
        uint32_t cycles   = product - (quotient * PERIOD_UNITS);

        /* Safeguard for edge cases due to fixed-point rounding */
        if (cycles >= PERIOD_UNITS) {
            cycles -= PERIOD_UNITS;
        }

        /* 3. Optimized Division: phase = ((cycles * 4096) + 31250) / 62500 */
        uint32_t numerator = (cycles * 4096UL) + 31250UL;

        /* We use the magic constant for 1/62500 in 32.32 fixed-point:
         * (2^32 / 62500) = 68719.476736 -> 68719
         * This completely eliminates the final division.
         */
        uint16_t phase = (uint16_t)(((uint64_t)numerator * 68719UL) >> 32);

        for (uint8_t ant = 0; ant < RCL_BLE_CS_MAX_NUM_ANT; ant++)
        {
            pComp->ant[ant].phase = phase;
        }
    }
}

/*
 *  ======== RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna ========
 *
 *  Same decoding as the antenna sequence in preprocessStep, but returns the physical antenna
 *  (0..3 = A1..A4) used for a given chronological tone index of a step.
 *  NOTE: 'toneIdx' must not exceed number of antenna paths, e.g. toneIdx for tone extension slot
 *  is not supported. The physical antenna for tone extension slot is same as the preceeding tone.
 */
static uint8_t RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna(const RCL_CmdBleCs *pCmd, uint8_t antennaPermIdx, uint8_t toneIdx)
{
    const RCL_AntennaConfig_t *antennaEntry = &antennaConfig[pCmd->antennaConfig.select];
    uint8_t antenna = 0;

    if (antennaPermIdx < antennaEntry->numPerm)
    {
        uint8_t apn = antennaPermutation[antennaPermIdx].apn;
        uint8_t apm = antennaEntry->ap[pCmd->mode.role & 1U].apn;

        antenna = DECODE_ANTENNA(apm, DECODE_ANTENNA(apn, toneIdx));
    }

    return (antenna);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertPct ========
 *
 *  Applies the phase rotation (skipped when 0) and the magnitude scaling (skipped when unity).
 *  A reflector reporting in inline-PCT format has already applied the phase in the radio, so it
 *  passes an entry with phase = 0 and only the magnitude is compensated. The inline PCT is
 *  real-valued (A + j*0), so the scaling keeps it real.
 *  pComp = NULL: no compensation.
 */
static uint32_t RCL_Handler_BLE_CS_convertPct(const RCL_CmdBleCs_IQSample *pPct, const RCL_CmdBleCs_PctCompEntry *pComp)
{
    if (pPct == NULL)
    {
        return (0);
    }

    int16_t  pct_i = pPct->i;
    int16_t  pct_q = pPct->q;

    /* Wide enough to hold the result of magnitude scaling before saturation */
    int32_t  iq_i = (int32_t) pct_i;
    int32_t  iq_q = (int32_t) pct_q;

    if (pComp != NULL)
    {
        /* Adjust the phase to the signal on the antenna (group delay and layout).
           The cast to int16_t wraps [0, 2*pi) to [-pi, pi), as expected by the rotation. */
        if (pComp->phase != 0U)
        {
            RCL_Handler_BLE_CS_rotateVector(&pct_i, &pct_q, (int16_t) pComp->phase);
        }

        iq_i = pct_i;
        iq_q = pct_q;

        if (pComp->magn != RCL_BLE_CS_PCT_MAGN_UNITY)
        {
            /* Scale I/Q magnitudes with k = magn / 2^15 (Q1.15) */
            const uint32_t MAGN_FRAC_BITS = 15U;
            const int32_t  MAGN_ROUND     = (int32_t) (1UL << (MAGN_FRAC_BITS - 1U));
            iq_i = ((iq_i * (int32_t) pComp->magn) + MAGN_ROUND) >> MAGN_FRAC_BITS;
            iq_q = ((iq_q * (int32_t) pComp->magn) + MAGN_ROUND) >> MAGN_FRAC_BITS;
        }
    }

    /* Rounding before saturation and downscaling to 12bit */
    iq_i += 1;
    iq_q += 1;

    /* Will need saturation check to avoid overflow of signed 13-bit I and Q */
    const int32_t IQ_MAX_VAL = (+4095);
    const int32_t IQ_MIN_VAL = (-4096);

    iq_i = (iq_i > IQ_MAX_VAL) ? IQ_MAX_VAL : iq_i;
    iq_i = (iq_i < IQ_MIN_VAL) ? IQ_MIN_VAL : iq_i;
    iq_q = (iq_q > IQ_MAX_VAL) ? IQ_MAX_VAL : iq_q;
    iq_q = (iq_q < IQ_MIN_VAL) ? IQ_MIN_VAL : iq_q;

    /* Scale down from 13bit to 12bit by using the most significant bits */
    uint32_t pct = (((iq_q >> 1U) & 0x0FFF) << 12)
                 | ( (iq_i >> 1U) & 0x0FFF);

    return (pct);
}

/*
 *  ======== RCL_Handler_BLE_CS_calcQ3 ========
 */
static uint8_t RCL_Handler_BLE_CS_calcQ3(uint16_t qMin, uint16_t qMax, uint16_t qAvg)
{
    /* The Q3 metric checks the instantaneous variation of the signal magnitude.
       The lower the value is, the better the quality. */
    uint8_t Q3 = BLE_CS_TONE_QUALITY_NA;

    /* Avoid zero-division. */
    if (qAvg != 0U)
    {
        /* Calculate Q3 metric on 16bit scale */
        uint16_t Q16 = 100U * (qMax - qMin)/qAvg;

        /* Saturate */
        Q3 = (Q16 < 0xFFU) ? (uint8_t) Q16 : 0xFFU;
    }

    return (Q3);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertPctQuality ========
 */
static uint8_t RCL_Handler_BLE_CS_convertPctQuality(uint16_t qMin, uint16_t qMax, uint16_t qAvg, bool toneExtensionSlot, bool toneExpected, bool toneQualityOverride)
{
    /* Calculate Q3 linear scale. */
    uint8_t Q3 = RCL_Handler_BLE_CS_calcQ3(qMin, qMax, qAvg);

    /* Classify based on threshold. The lower the better. */
    uint8_t tnQ = (Q3 < BLE_CS_TONE_QUALITY_HIGH_THR)
                ? (uint8_t)(RCL_CmdBleCs_ToneQuality_High)
                : (uint8_t)(RCL_CmdBleCs_ToneQuality_Low);

    /* Override the value to unavailable for initiator mode-3 w/o second tone extension */
    if (toneQualityOverride)
    {
        tnQ = (uint8_t) RCL_CmdBleCs_ToneQuality_Unavailable;
    }

    /* Add additional flag for the tone extension slot */
    if (toneExtensionSlot)
    {
        uint8_t toneExtensionFlag = (toneExpected)
                                  ? (uint8_t) (RCL_CmdBleCs_ToneExtensionSlot_Enabled_ToneExpected)
                                  : (uint8_t) (RCL_CmdBleCs_ToneExtensionSlot_Enabled_NoToneExpected);

        tnQ |= (toneExtensionFlag << 4);
    }
    else
    {
        /* Do nothing */
    }

    return (tnQ);
}

/*
 *  ======== RCL_Handler_BLE_CS_estimateStepResultLength ========
 */
static uint16_t RCL_Handler_BLE_CS_estimateStepResultLength(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_StepResult_Internal* src)
{
    /* Information extracted from registers */
    RCL_CmdBleCs_Role role = (RCL_CmdBleCs_Role) pCmd->mode.role;

    /* Number of bytes will scale with number of tones. +1 = tone extension */
    uint8_t numTone = pCmd->stats->numAntennaPath + 1U;

    /* First two fields are mandatory */
    uint16_t length = 0;

    /* Dataformat varies based on the mode. Constants are known from the spec */
    switch ((RCL_CmdBleCs_StepMode) src->mode)
    {
        case (RCL_CmdBleCs_StepMode_0):
            /* Initiator also contains the measured frequency offset */
            length = (uint16_t) ((role == RCL_CmdBleCs_Role_Initiator) ?
                    sizeof(RCL_CmdBleCs_ResultI0) : sizeof(RCL_CmdBleCs_ResultR0));
            break;
        case (RCL_CmdBleCs_StepMode_1):
            length = (uint16_t) sizeof(RCL_CmdBleCs_ResultIR1);
            break;
        case (RCL_CmdBleCs_StepMode_2):
            length = (uint16_t) (sizeof(RCL_CmdBleCs_ResultIR2) + numTone * sizeof(RCL_CmdBleCs_Tone));
            break;
        case (RCL_CmdBleCs_StepMode_3):
            length = (uint16_t) (sizeof(RCL_CmdBleCs_ResultIR3) + numTone * sizeof(RCL_CmdBleCs_Tone));
            break;
        default:
            length = 0;
            break;
    }

    return (length);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertStepResult ========
 */
static uint16_t RCL_Handler_BLE_CS_convertStepResult(RCL_CmdBleCs* pCmd, uint8_t *dst, RCL_CmdBleCs_StepResult_Internal* src)
{
    /* Calculate number of tones to be measured. +1 = tone extension */
    uint8_t numTone = pCmd->stats->numAntennaPath + 1U;

    /* Determine the format of the report */
    uint8_t reportFormat = pCmd->mode.reportFormat;

    /* Determine whether the reflector has already adjusted the phase inline */
    bool inlinePhase = (pCmd->mode.role == RCL_CmdBleCs_Role_Reflector) && (pCmd->mode.inlinePhase);

    /* Dataformat varies based on the mode */
    uint8_t mode          = src->mode;
    uint8_t channel       = src->channelIdx;
    uint8_t payloadLen    = src->payloadLen;
    uint8_t toneExtension = src->toneExtension;

    /* PCT compensation for antenna/front-end delay and gain imbalance, for all antennas of this channel.
       Only needed for steps with tones. A reflector with inline phase has already applied the phase
       in the radio, so only the magnitude is compensated then. */
    RCL_CmdBleCs_PctComp pctComp = RCL_CMD_BLE_CS_PCT_COMP_DEFAULT;
    if ((RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_2 ||
        (RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_3)
    {
        uint8_t compSelect = (inlinePhase)
                           ? RCL_BLE_CS_PCT_COMP_SEL_MAGN
                           : (RCL_BLE_CS_PCT_COMP_SEL_PHASE | RCL_BLE_CS_PCT_COMP_SEL_MAGN);
        RCL_Handler_BLE_CS_getPctComp(channel, compSelect, &pctComp);
    }

    /* Mode independent fields */
    *dst++ = mode;
    *dst++ = channel;

    /* Remember the address of field 'datalength' and skip it for now, will be filled later */
    uint8_t *dataLength = dst++;

    if ((RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_0)
    {
        *dst++ = src->pktResult;             /* Packet_AA_Quality */
        *dst++ = (uint8_t) src->pktRssi;     /* Packet_RSSI */
        *dst++ = src->antennaPacket;         /* Packet_Antenna */

        if ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
        {
            int16_t freqOffset = ((RCL_CmdBleCs_PacketResult) src->pktResult != RCL_CmdBleCs_PacketResult_Ok)
                               ? (int16_t) RCL_CMD_BLE_CS_FREQCOMP_NA
                               : RCL_Handler_BLE_CS_convertFreqOffset(src->foffMeasured, true);
            *dst++ = INT16_LSB(freqOffset);
            *dst++ = INT16_MSB(freqOffset);
        }
    }
    else if ((RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_1)
    {
        /* RTT calculation using correlator values if the packet was received */
        int16_t toAD = ((RCL_CmdBleCs_PacketResult) src->pktResult != RCL_CmdBleCs_PacketResult_Ok)
                     ? RCL_CMD_BLE_CS_TOAD_NA
                     : (int16_t) RCL_Handler_BLE_CS_convertRtt(pCmd,
                                                     RCL_CmdBleCs_StepMode_1,
                                                     channel,
                                                     payloadLen,
                                                     false, /* secondToneExtensionSlot=NA, there are no tones in mode-1 */
                                                     src->rtt, src->corr[0], src->corr[1], src->corr[2]);

        *dst++ = src->pktResult;                       /* Packet_AA_Quality */
        *dst++ = (uint8_t) RCL_CmdBleCs_Nadm_Unknown;  /* Packet_NADM */
        *dst++ = (uint8_t) src->pktRssi;               /* Packet_RSSI */
        *dst++ =  INT16_LSB(toAD);                     /* Time_Of_Flight */
        *dst++ =  INT16_MSB(toAD);
        *dst++ = src->antennaPacket;                   /* Packet_Antenna */
    }
    else if ((RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_2)
    {
        /* Tone related data */
        *dst++ = src->antennaPermIdx;          /* Antenna_Permutation_Index*/
        for (uint8_t j = 0; j < numTone; j++)
        {
            /* The tone extension slot is measured on the antenna of the last antenna path */
            uint8_t path = (j < pCmd->stats->numAntennaPath) ? (j) : (j-1);
            uint8_t antenna = RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna(pCmd, src->antennaPermIdx, path);
            const RCL_CmdBleCs_PctCompEntry *pComp = &pctComp.ant[antenna];

            /* Compress PCT to 24bits */
            uint32_t pct = RCL_Handler_BLE_CS_convertPct(&src->pct[j], pComp);
            *dst++       = (uint8_t)((pct) & 0xFF);
            *dst++       = (uint8_t)((pct >> 8) & 0xFF);
            *dst++       = (uint8_t)((pct >> 16) & 0xFF);

            /* Calculate PCT quality */
            bool toneExtensionSlot = (bool)(j == (numTone - 1U));
            bool toneExpected = (bool) (((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                              ? (toneExtension & BLE_CS_TONE_EXTENSION_INITIATOR_TX)
                              : (toneExtension & BLE_CS_TONE_EXTENSION_REFLECTOR_TX));

            uint16_t min = src->magn[j].magnMin;
            uint16_t max = src->magn[j].magnMax;
            uint16_t avg = src->magn[j].magnAvg;

            /* Vendor specific format? */
            if ((RCL_CmdBleCs_ReportFormat) reportFormat == RCL_CmdBleCs_ReportFormat_HCI)
            {
                *dst++ = RCL_Handler_BLE_CS_convertPctQuality(min, max, avg, toneExtensionSlot, toneExpected, false);
            }
            else
            {
                *dst++ = RCL_Handler_BLE_CS_calcQ3(min, max, avg);
            }
        }
    }
    else if ((RCL_CmdBleCs_StepMode) mode == RCL_CmdBleCs_StepMode_3)
    {
        /* RTT calculation using correlator values if the packet was received */
        int16_t toAD = ((RCL_CmdBleCs_PacketResult) src->pktResult != RCL_CmdBleCs_PacketResult_Ok)
                     ? RCL_CMD_BLE_CS_TOAD_NA
                     : RCL_Handler_BLE_CS_convertRtt(pCmd,
                                                     RCL_CmdBleCs_StepMode_3,
                                                     channel,
                                                     payloadLen,
                                                     (bool)(toneExtension & 2U),
                                                     src->rtt, src->corr[0], src->corr[1], src->corr[2]);

        /* Packet related data */
        *dst++ = src->pktResult;                       /* Packet_AA_Quality */
        *dst++ = (uint8_t) RCL_CmdBleCs_Nadm_Unknown;  /* Packet_NADM */
        *dst++ = (uint8_t) src->pktRssi;               /* Packet_RSSI */
        *dst++ = INT16_LSB(toAD);                      /* Time_Of_Flight */
        *dst++ = INT16_MSB(toAD);
        *dst++ = src->antennaPacket;                   /* Packet_Antenna */

        /* Tone related data */
        *dst++ = src->antennaPermIdx;        /* Antenna_Permutation_Index*/
        for (uint8_t j = 0; j < numTone; j++)
        {
            /* The tone extension slot is measured on the antenna of the last antenna path */
            uint8_t path = (j < pCmd->stats->numAntennaPath) ? (j) : (j-1);
            uint8_t antenna = RCL_Handler_BLE_CS_toneIdxToPhysicalAntenna(pCmd, src->antennaPermIdx, path);
            const RCL_CmdBleCs_PctCompEntry *pComp = &pctComp.ant[antenna];

            /* Compress PCT to 24bits */
            uint32_t pct = RCL_Handler_BLE_CS_convertPct(&src->pct[j], pComp);
            *dst++       = (uint8_t)((pct) & 0xFF);
            *dst++       = (uint8_t)((pct >> 8) & 0xFF);
            *dst++       = (uint8_t)((pct >> 16) & 0xFF);

            /* Calculate PCT quality */
            bool toneExtensionSlot = (bool)(j == (numTone - 1U));

            /* Mode-3 may or may not have the R->I tone extension present */
            bool toneExpected = (bool) (((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                              ? (toneExtension & BLE_CS_TONE_EXTENSION_INITIATOR_TX)
                              : (toneExtension & BLE_CS_TONE_EXTENSION_REFLECTOR_TX));

            /* Special case where we need to report unavailable */
            bool toneQualityOverride = ((RCL_CmdBleCs_Role) pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
                                     && (toneExtensionSlot)
                                     && (!toneExpected);

            uint16_t min = src->magn[j].magnMin;
            uint16_t max = src->magn[j].magnMax;
            uint16_t avg = src->magn[j].magnAvg;

            /* Vendor specific format? */
            if ((RCL_CmdBleCs_ReportFormat) reportFormat == RCL_CmdBleCs_ReportFormat_HCI)
            {
                *dst++ = RCL_Handler_BLE_CS_convertPctQuality(min, max, avg, toneExtensionSlot, toneExpected, toneQualityOverride);
            }
            else
            {
                *dst++ = RCL_Handler_BLE_CS_calcQ3(min, max, avg);
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    /* Fill the Step_Data_Length based on difference of addresses */
    *dataLength = (uint8_t)(dst - dataLength - 1U);

    /* Return the number of bytes written (+3 = mode & channel & dataLength) */
    return (*dataLength + 3U);
}

/*
 *  ======== RCL_Handler_BLE_CS_findPbeErrorEndStatus ========
 */
static RCL_CommandStatus RCL_Handler_BLE_CS_findPbeErrorEndStatus(uint16_t pbeEndStatus)
{
    RCL_CommandStatus status;
    switch (pbeEndStatus)
    {
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_RXF:
        status = RCL_CommandStatus_Error_RxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_TXF:
        status = RCL_CommandStatus_Error_TxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_SYNTH:
        status = RCL_CommandStatus_Error_Synth;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_PAR:
        status = RCL_CommandStatus_Error_Param;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP:
        status = RCL_CommandStatus_Error_UnknownOp;
        break;
    default:
        Log_printf(LogModule_RCL, Log_ERROR, "RCL_Handler_BLE_CS_findPbeErrorEndStatus: Unexpected error 0x%04X from PBE", pbeEndStatus);
        status = RCL_CommandStatus_Error;
        break;
    }
    return (status);
}

/*
 *  ======== RCL_Handler_BLE_CS ========
 */
RCL_Events RCL_Handler_BLE_CS(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBleCs *pCmd = (RCL_CmdBleCs *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

#ifndef OCTOPUS
        /* TODO: The following lines should be a power driver call, which should allow to restore
        the default HFTRACKCTL value if no constraints are set */
        if (Power_getConstraintCount(PowerLPF3_DISALLOW_SWTCXO) == 0)
        {
            HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) = 0x80400000;
        }
#endif
        /* Make sure SWTCXO does not adjust clock while radio is running */
        RCL_Hal_powerSetSwTcxoUpdateConstraint();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        /* Default end status */
        bleCsHandlerState.common.endStatus = RCL_CommandStatus_Finished;

        /* Enable radio */
        LRF_enable();

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts (LRF_EventMdmsoft0 => "S2R samples available") */
            HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
                            HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            | LRF_EventOpDone.value
                            | LRF_EventOpError.value
                            | LRF_EventMdmsoft0.value
                            | LRF_EventRxfifo.value;

            /* Initialize BLE CS specific registers and FIFO */
            RCL_Handler_BLE_CS_preprocessCommand(pCmd);

            /* Configure TX power. Use special frequency value to indicate that no compensation should be applied */
            if (LRF_programTxPower(pCmd->txPower, LRF_TXPOWER_BYPASS_FREQUENCY_BACKOFF) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Configure the BUFRAM fifo size and interrupts */
                RCL_Handler_BLE_CS_configureTxRxFifo(pCmd);

                /* Configure S2R size and mode */
                RCL_Handler_BLE_CS_configureS2R(pCmd);

                /* Fill the first batch of step descriptors into the BUFRAM TX fifo */
                rclEvents.value |= RCL_Handler_BLE_CS_preFillTxBuffer(pCmd).value;

                /* Post command */
                LRF_waitForTopsmReady();
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE_CS_REGDEF_API_OP_BLE_CS;

                /* Forward fill more steps */
                rclEvents.value |= RCL_Handler_BLE_CS_preFillTxBuffer(pCmd).value;
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        /* Read the statistics */
        RCL_Handler_BLE_CS_readStatistics(pCmd);

        if (rclEventsIn.timerStart != 0U)
        {
            rclEvents.cmdStarted = 1;
        }

        if (lrfEvents.opDone != 0U || lrfEvents.opError != 0U)
        {
            /* Drain the rx fifo of the final batch of results. Force close the buffer. */
            rclEvents.value |= RCL_Handler_BLE_CS_readWriteBuffer(pCmd, true).value;
        }
        else
        {
            if (lrfEvents.rxfifo != 0U)
            {
                /* Read the available results, and issue event if multibuffer is exhausted */
                rclEvents.value |= RCL_Handler_BLE_CS_readWriteBuffer(pCmd, false).value;
            }
        }

        if (lrfEvents.mdmsoft0 != 0U)
        {
            /* Read S2R samples upon MCE event */
            rclEvents.value |= RCL_Handler_BLE_CS_readS2RSamples(pCmd).value;
        }

        if (lrfEvents.opDone != 0U)
        {
            RCL_Handler_BLE_CS_updateCache(pCmd);

            cmd->status = bleCsHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0U)
        {
            RCL_CommandStatus endStatus = bleCsHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE_CS_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
        /* Allow SWTCXO again */
        RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
    }
    return (rclEvents);
}

/*
 *  ======== RCL_Handler_BLE_CS_filterDC ========
 */
static bool RCL_Handler_BLE_CS_filterDC(uint16_t max, uint16_t min, uint16_t thr)
{
    return (bool)((max-min) < thr);
}

/*
 *  ======== RCL_Handler_BLE_CS_Precal ========
 */
RCL_Events RCL_Handler_BLE_CS_Precal(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBleCs_Precal *pCmd = (RCL_CmdBleCs_Precal *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0U)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();
#ifndef OCTOPUS
        /* TODO: The following lines should be a power driver call, which should allow to restore
        the default HFTRACKCTL value if no constraints are set */
        if (Power_getConstraintCount(PowerLPF3_DISALLOW_SWTCXO) == 0)
        {
            HWREG(CKMD_BASE + CKMD_O_HFTRACKCTL) = 0x80400000;
        }
#endif
        /* Make sure SWTCXO does not adjust clock while radio is running*/
        RCL_Hal_powerSetSwTcxoUpdateConstraint();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        /* Default end status */
        bleCsHandlerState.common.endStatus = RCL_CommandStatus_Finished;

        /* Enable radio */
        LRF_enable();

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts */
            HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            | LRF_EventOpDone.value
                            | LRF_EventOpError.value;

            RCL_Handler_BLE_CS_configureTxRxFifo(NULL);

            /* Number of channels to calibrate on */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_MODE) = (((uint16_t) pCmd->table->numEntries << PBE_BLE_CS_RAM_MODE_NUM_STEPS_S) & PBE_BLE_CS_RAM_MODE_NUM_STEPS_M);

            for (uint8_t j = 0; j < pCmd->table->numEntries; j++)
            {
                /* 32bit aperture */
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = pCmd->table->entries[j].channel;
            }

            /* The calibration is only valid around the current temperature */
            pCmd->table->temperature = RCL_Hal_getTemperature();

            /* Post command */
            LRF_waitForTopsmReady();
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE_CS_REGDEF_API_OP_PRECAL;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0U)
        {
            volatile uint32_t data;
            for (uint8_t j=0; j<pCmd->table->numEntries; j++)
            {
                /* uint32_t FIFO read -> uint16_t store */
                uint16_t *dst = (uint16_t *) &pCmd->table->entries[j].high;

                /*  x2 = high/low entries */
                for (uint8_t k= 0; k < (2U * sizeof(RCL_CmdBleCs_DCSample) / sizeof(uint32_t)); k++)
                {
                    data = HWREG_READ_LRF(LRFDRXF_BASE + LRFDRXF_O_RXD);
                    *dst++ = INT32_L(data);
                    *dst++ = INT32_H(data);
                }

                /* Post process/validate the entry */
                pCmd->table->entries[j].highValid = (uint8_t)
                    (RCL_Handler_BLE_CS_filterDC(pCmd->table->entries[j].high.magnMax,
                                                pCmd->table->entries[j].high.magnMin,
                                                pCmd->table->highThreshold));

                pCmd->table->entries[j].lowValid = (uint8_t)
                    (RCL_Handler_BLE_CS_filterDC(pCmd->table->entries[j].low.magnMax,
                                                pCmd->table->entries[j].low.magnMin,
                                                pCmd->table->lowThreshold));
            }

            /* Validate the table */
            pCmd->table->valid = 1;

            cmd->status = bleCsHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0U)
        {
            /* Invalidate the table */
            pCmd->table->valid = 0;

            RCL_CommandStatus endStatus = bleCsHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE_CS_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
           /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0U)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
        /* Allow SWTCXO again */
        RCL_Hal_powerReleaseSwTcxoUpdateConstraint();
    }
    return (rclEvents);
}

/*
 *  ======== RCL_Handler_BLE_CS_PrecalDefaultCallback ========
 */
void RCL_Handler_BLE_CS_PrecalDefaultCallback(RCL_CmdBleCs_PrecalTable *table, uint8_t channel, RCL_CmdBleCs_IQSample *pHigh, RCL_CmdBleCs_IQSample *pLow)
{
    /* Initialize return values to 0 in case no matching calibration found */
    pHigh->i = pHigh->q = pLow->i = pLow->q = 0;

    /* Verify that it is a valid BLE channel */
    if (channel <= BLE_CS_MAX_CHANNEL)
    {
        /* Find the bin in the table, assuming equal spacing */
        uint8_t k = channel / table->chSpacing;

        /* Verification that the channel is covered by the table */
        uint8_t N = table->numEntries;
        if (k < N)
        {
            /* Initialize to measured value before filtering */
            pHigh->i = table->entries[k].high.i;
            pHigh->q = table->entries[k].high.q;
            pLow->i  = table->entries[k].low.i;
            pLow->q  = table->entries[k].low.q;

            #define DCFILTER 1
            #ifdef DCFILTER
                /* LUT for search pattern (start with correct bin) */
                int8_t search[] = { 0, +1, -1, +2, -2, +3, -3, +4, -4, +5, -5, +6, -6, +7, -7};

                /* Internal search state */
                bool highValid = false;
                bool lowValid  = false;

                /* Search in both direction according to the given pattern */
                for (uint8_t s = 0; s < sizeof(search); s++)
                {
                    int8_t i = (int8_t) k + search[s];
                    if ((i >= 0) && (i < (int8_t) N))
                    {
                        if ((highValid == false) && ((bool) table->entries[i].highValid == true))
                        {
                            highValid = true;
                            pHigh->i  = table->entries[i].high.i;
                            pHigh->q  = table->entries[i].high.q;
                        }

                        if ((lowValid == false) && ((bool) table->entries[i].lowValid == true))
                        {
                            lowValid = true;
                            pLow->i  = table->entries[i].low.i;
                            pLow->q  = table->entries[i].low.q;
                        }
                    }

                    /* Break the loop early if both entries were found */
                    if (highValid && lowValid) break;
                }
            #endif
        }
    }
}
