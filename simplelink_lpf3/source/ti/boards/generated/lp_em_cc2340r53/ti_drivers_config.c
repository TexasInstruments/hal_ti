/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the LP_EM_CC2340R53
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_CC23X0R5
#define DeviceFamily_CC23X0R5
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  =============================== AESCCM ===============================
 */

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aesccm/AESCCMLPF3.h>

#define CONFIG_AESCCM_COUNT 1
AESCCMLPF3_Object AESCCMLPF3_objects[CONFIG_AESCCM_COUNT];

/*
 *  ======== AESCCMLPF3_hwAttrs ========
 */
const AESCCMLPF3_HWAttrs AESCCMLPF3_hwAttrs[CONFIG_AESCCM_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCCM_Config AESCCM_config[CONFIG_AESCCM_COUNT] = {
    {   /* CONFIG_AESCCM_0 */
        .object  = &AESCCMLPF3_objects[CONFIG_AESCCM_0],
        .hwAttrs = &AESCCMLPF3_hwAttrs[CONFIG_AESCCM_0]
    },
};

const uint_least8_t CONFIG_AESCCM_0_CONST = CONFIG_AESCCM_0;
const uint_least8_t AESCCM_count = CONFIG_AESCCM_COUNT;

/*
 *  =============================== AESCMAC ===============================
 */

#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/aescmac/AESCMACLPF3.h>

#define CONFIG_AESCMAC_COUNT 1
AESCMACLPF3_Object AESCMACLPF3_objects[CONFIG_AESCMAC_COUNT];

/*
 *  ======== AESCMACLPF3_hwAttrs ========
 */
const AESCMACLPF3_HWAttrs AESCMACLPF3_hwAttrs[CONFIG_AESCMAC_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCMAC_Config AESCMAC_config[CONFIG_AESCMAC_COUNT] = {
    {   /* CONFIG_AESCMAC_0 */
        .object  = &AESCMACLPF3_objects[CONFIG_AESCMAC_0],
        .hwAttrs = &AESCMACLPF3_hwAttrs[CONFIG_AESCMAC_0]
    },
};

const uint_least8_t CONFIG_AESCMAC_0_CONST = CONFIG_AESCMAC_0;
const uint_least8_t AESCMAC_count = CONFIG_AESCMAC_COUNT;

/*
 *  =============================== AESCTR ===============================
 */

#include <ti/drivers/AESCTR.h>
#include <ti/drivers/aesctr/AESCTRLPF3.h>

#define CONFIG_AESCTR_COUNT 1
AESCTRLPF3_Object AESCTRLPF3_objects[CONFIG_AESCTR_COUNT];

/*
 *  ======== AESCTRLPF3_hwAttrs ========
 */
const AESCTRLPF3_HWAttrs AESCTRLPF3_hwAttrs[CONFIG_AESCTR_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCTR_Config AESCTR_config[CONFIG_AESCTR_COUNT] = {
    {   /* CONFIG_AESCTR_0 */
        .object  = &AESCTRLPF3_objects[CONFIG_AESCTR_0],
        .hwAttrs = &AESCTRLPF3_hwAttrs[CONFIG_AESCTR_0]
    },
};

const uint_least8_t CONFIG_AESCTR_0_CONST = CONFIG_AESCTR_0;
const uint_least8_t AESCTR_count = CONFIG_AESCTR_COUNT;

/*
 *  =============================== AESCTRDRBG ===============================
 */

#include <ti/drivers/AESCTRDRBG.h>
#include <ti/drivers/aesctrdrbg/AESCTRDRBGXX.h>

#define CONFIG_AESCTRDRBG_COUNT 1

/*
 *  ======== aesctrdrbgXXObjects ========
 */
AESCTRDRBGXX_Object aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_COUNT];

/*
 *  ======== aesctrdrbgXXHWAttrs ========
 */
const AESCTRDRBGXX_HWAttrs aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .aesctrHWAttrs.intPriority = (~0)
    },
};

/*
 *  ======== AESCTRDRBG_config ========
 */
const AESCTRDRBG_Config AESCTRDRBG_config[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .object = &aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_0],
        .hwAttrs = &aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_0]
    },
};

const uint_least8_t CONFIG_AESCTRDRBG_0_CONST = CONFIG_AESCTRDRBG_0;
const uint_least8_t AESCTRDRBG_count = CONFIG_AESCTRDRBG_COUNT;

/*
 *  =============================== AESECB ===============================
 */

#include <ti/drivers/AESECB.h>
#include <ti/drivers/aesecb/AESECBLPF3.h>

#define CONFIG_AESECB_COUNT 1
AESECBLPF3_Object AESECBLPF3_objects[CONFIG_AESECB_COUNT];

/*
 *  ======== AESECBLPF3_hwAttrs ========
 */
const AESECBLPF3_HWAttrs AESECBLPF3_hwAttrs[CONFIG_AESECB_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESECB_Config AESECB_config[CONFIG_AESECB_COUNT] = {
    {   /* CONFIG_AESECB_0 */
        .object  = &AESECBLPF3_objects[CONFIG_AESECB_0],
        .hwAttrs = &AESECBLPF3_hwAttrs[CONFIG_AESECB_0]
    },
};


const uint_least8_t CONFIG_AESECB_0_CONST = CONFIG_AESECB_0;
const uint_least8_t AESECB_count = CONFIG_AESECB_COUNT;

/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/devices/cc23x0r5/inc/hw_memmap.h>

const UDMALPF3_Config UDMALPF3_config = {
        .CtrlBaseAddr = UDMALPF3_CONFIG_BASE,
};

/*
 *  =============================== ECDH ===============================
 */

#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHLPF3SW.h>

#define CONFIG_ECDH_COUNT 1

ECDHLPF3SW_Object ecdhLpf3swObjects[CONFIG_ECDH_COUNT];

/*
 *  ======== ecdhLpf3swHWAttrs ========
 */
const ECDHLPF3SW_HWAttrs ecdhLpf3swHWAttrs[CONFIG_ECDH_COUNT] = {
    {0},
};

const ECDH_Config ECDH_config[CONFIG_ECDH_COUNT] = {
    {   /* CONFIG_ECDH_0 */
        .object         = &ecdhLpf3swObjects[CONFIG_ECDH_0],
        .hwAttrs        = &ecdhLpf3swHWAttrs[CONFIG_ECDH_0]
    },
};

const uint_least8_t CONFIG_ECDH_0_CONST = CONFIG_ECDH_0;
const uint_least8_t ECDH_count = CONFIG_ECDH_COUNT;

/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>

/* The range of pins available on this device */
const uint_least8_t GPIO_pinLowerBound = 0;
const uint_least8_t GPIO_pinUpperBound = 25;

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include "ti_drivers_config.h"
#include DeviceFamily_constructPath(driverlib/ckmd.h)
#include DeviceFamily_constructPath(driverlib/pmctl.h)

extern void customPolicyFxn(void);

const uint32_t PowerLPF3_capArrayP0 = 553648128; /* floor(8.25 * 2^26) */
const uint32_t PowerLPF3_capArrayP1 = 4697620; /* floor(0.07 * 2^26) */
const uint8_t  PowerLPF3_capArrayShift = 26;  /* shift-value to bring floating-point coefficients to fixed-point */


const PowerCC23X0_Config PowerCC23X0_config = {
    .policyInitFxn              = NULL,
    .policyFxn                  = customPolicyFxn,
    .startInitialHfxtAmpCompFxn = NULL,
};

/*
 *  =============================== BatMon Support ===============================
 */
#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(driverlib/evtsvt.h)

const BatMonSupportLPF3_Config BatMonSupportLPF3_config = {
    .intNum = INT_CPUIRQ2,
    .intPriority = (~0),
    .intSubscriberId = EVTSVT_SUB_CPUIRQ2,
};
