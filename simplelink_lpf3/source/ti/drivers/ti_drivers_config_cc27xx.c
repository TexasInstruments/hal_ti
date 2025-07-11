
#include <ti/devices/DeviceFamily.h>

#include <stdint.h>
#include <stddef.h>

/*
 *  ======== ECDH ========
 */

extern const uint_least8_t              CONFIG_ECDH_0_CONST;
#define CONFIG_ECDH_0                   0
#define CONFIG_TI_DRIVERS_ECDH_COUNT    1

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include DeviceFamily_constructPath(driverlib/ckmd.h)
#include DeviceFamily_constructPath(driverlib/pmctl.h)

const PowerCC27XX_Config PowerCC27XX_config = {
    .policyInitFxn              = NULL,
    .policyFxn                  = NULL,
    .startInitialHfxtAmpCompFxn = NULL,
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
