/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the LP_EM_CC2340R53_WCSP
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
