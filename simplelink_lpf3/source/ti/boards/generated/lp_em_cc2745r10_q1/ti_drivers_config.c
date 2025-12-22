/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the LP_EM_CC2745R10_Q1
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_CC27XX
#define DeviceFamily_CC27XX
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"


/*
 *  =============================== Key Store ===============================
 */
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_device.h)

uint8_t volatileAllocBuffer[KEYSTORE_VOLATILE_MEMORY_POOL_SIZE];
const size_t volatileAllocBufferSizeBytes  = KEYSTORE_VOLATILE_MEMORY_POOL_SIZE;

const size_t MBEDTLS_KEY_VOLATILE_COUNT    = KEYSTORE_VOLATILE_SLOT_COUNT;
const size_t MBEDTLS_KEY_ASSET_STORE_COUNT = KEYSTORE_ASSET_STORE_SLOT_COUNT;
/* For cache slots */
const size_t MBEDTLS_KEY_PERSISTENT_COUNT  = KEYSTORE_PERSISTENT_SLOT_COUNT;
/* For Key Store flash space */
const size_t FLASH_KEY_PERSISTENT_COUNT    = KEYSTORE_PERSISTENT_NUM_KEYS;
/* ITS flash area size */
const size_t FLASH_ITS_SIZE                = KEYSTORE_FLASH_SIZE;


psa_key_context_t gl_PSA_Key[KEYSTORE_TOTAL_SLOT_COUNT];

#if ((KEYSTORE_FLASH_OFFSET + KEYSTORE_FLASH_SIZE) > FLASH_MAIN_SW_SIZE)
    #error "The configured KeyStore flash region goes beyond the accessible flash addresses on the device."
#elif (KEYSTORE_FLASH_OFFSET < FLASH_MAIN_BASE)
    #error "The configured KeyStore flash region begins before the start of accessible flash on the device."
#endif


/* ITS flash area address, with 'Pointer' region type */
const void *FLASH_ITS_ADDRESS = (void *) 0xe6000;





/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/devices/cc27xx/inc/hw_memmap.h>

const UDMALPF3_Config UDMALPF3_config = {
        .CtrlBaseAddr = UDMALPF3_CONFIG_BASE,
};

/*
 *  =============================== ECDH ===============================
 */

#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHLPF3HSM.h>

#define CONFIG_ECDH_COUNT 1

ECDHLPF3HSM_Object ECDHLPF3HSM_objects[CONFIG_ECDH_COUNT];

/*
 *  ======== ECDHLPF3HSMHWAttrs ========
 */
const ECDHLPF3HSM_HWAttrs ECDHLPF3HSM_hwAttrs[CONFIG_ECDH_COUNT] = {
    {0},
};

const ECDH_Config ECDH_config[CONFIG_ECDH_COUNT] = {
    {   /* CONFIG_ECDH_0 */
        .object  = &ECDHLPF3HSM_objects[CONFIG_ECDH_0],
        .hwAttrs = &ECDHLPF3HSM_hwAttrs[CONFIG_ECDH_0]
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
const uint_least8_t GPIO_pinUpperBound = 28;

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[29] = {
    GPIO_CFG_NO_DIR, /* DIO_0 */
    GPIO_CFG_NO_DIR, /* DIO_1 */
    GPIO_CFG_NO_DIR, /* DIO_2 */
    GPIO_CFG_NO_DIR, /* DIO_3 */
    GPIO_CFG_NO_DIR, /* DIO_4 */
    GPIO_CFG_NO_DIR, /* DIO_5 */
    GPIO_CFG_NO_DIR, /* DIO_6 */
    GPIO_CFG_NO_DIR, /* DIO_7 */
    GPIO_CFG_NO_DIR, /* DIO_8 */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_9 */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_10 */
    GPIO_CFG_NO_DIR, /* DIO_11 */
    GPIO_CFG_NO_DIR, /* DIO_12 */
    GPIO_CFG_NO_DIR, /* DIO_13 */
    GPIO_CFG_NO_DIR, /* DIO_14 */
    GPIO_CFG_NO_DIR, /* DIO_15 */
    GPIO_CFG_NO_DIR, /* DIO_16 */
    GPIO_CFG_NO_DIR, /* DIO_17 */
    GPIO_CFG_NO_DIR, /* DIO_18 */
    GPIO_CFG_NO_DIR, /* DIO_19 */
    GPIO_CFG_NO_DIR, /* DIO_20 */
    GPIO_CFG_NO_DIR, /* DIO_21 */
    GPIO_CFG_NO_DIR, /* DIO_22 */
    GPIO_CFG_NO_DIR, /* DIO_23 */
    GPIO_CFG_NO_DIR, /* DIO_24 */
    GPIO_CFG_NO_DIR, /* DIO_25 */
    GPIO_CFG_NO_DIR, /* DIO_26 */
    GPIO_CFG_NO_DIR, /* DIO_27 */
    GPIO_CFG_NO_DIR, /* DIO_28 */
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *  Change at runtime with GPIO_setCallback()
 */
GPIO_CallbackFxn gpioCallbackFunctions[29];

/*
 *  ======== gpioUserArgs ========
 *  Array of user argument pointers
 *  Change at runtime with GPIO_setUserArg()
 *  Get values with GPIO_getUserArg()
 */
void* gpioUserArgs[29];



/*
 *  ======== GPIO_config ========
 */
const GPIO_Config GPIO_config = {
    .configs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .userArgs = gpioUserArgs,
    .intPriority = (~0)
};

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


const PowerCC27XX_Config PowerCC27XX_config = {
    .policyInitFxn              = NULL,
    .policyFxn                  = customPolicyFxn,
    .startInitialHfxtAmpCompFxn = NULL,
};

/*
 *  =============================== RNG ===============================
 */

#include <ti/drivers/RNG.h>
#include <ti/drivers/rng/RNGLPF3HSM.h>

#define CONFIG_RNG_COUNT 0

#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=32
#else
__attribute__ ((aligned (32)))
#endif

const RNG_ReturnBehavior RNGLPF3HSM_returnBehavior = RNG_RETURN_BEHAVIOR_POLLING;

RNGLPF3HSM_Object RNGLPF3HSM_objects[CONFIG_RNG_COUNT];

/*
 *  ======== RNGLPF3HSMHWAttrs ========
 */
const RNGLPF3HSM_HWAttrs RNGLPF3HSM_hwAttrs[CONFIG_RNG_COUNT] = {
};

const RNG_Config RNG_config[CONFIG_RNG_COUNT] = {
};


const uint_least8_t RNG_count = CONFIG_RNG_COUNT;

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

#include <stdbool.h>

#include <ti/devices/cc27xx/driverlib/cpu.h>
#include <ti/devices/cc27xx/driverlib/hapi.h>

#include <ti/drivers/GPIO.h>

/* Board GPIO defines */
#define BOARD_EXT_FLASH_SPI_CS      19
#define BOARD_EXT_FLASH_SPI_CLK     3
#define BOARD_EXT_FLASH_SPI_PICO    5
#define BOARD_EXT_FLASH_SPI_POCI    4
/*
 *  ======== Board_sendExtFlashByte ========
 */
void Board_sendExtFlashByte(uint8_t byte)
{
    uint8_t i;

    /* SPI Flash CS */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 0);

    for (i = 0; i < 8; i++) {
        GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 0); /* SPI Flash CLK */

        /* SPI Flash PICO */
        GPIO_write(BOARD_EXT_FLASH_SPI_PICO, (byte >> (7 - i)) & 0x01);
        GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 1);  /* SPI Flash CLK */

        /* Waste a few cycles to keep the CLK high for at
         * least 45% of the period.
         * 3 cycles per loop: 16 loops @ 96 MHz = 0.5 us.
         */
        CPUDelay(16);
    }

    GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 0);  /* CLK */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 1);  /* CS */

    /* Keep CS high at least 40 us */
    HapiWaitUs(40);
}

/*
 *  ======== Board_wakeUpExtFlash ========
 */
void Board_wakeUpExtFlash(void)
{
    /* SPI Flash CS*/
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CS, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_HIGH | GPIO_CFG_OUT_STR_MED);

    /* To wake up we need to toggle the chip select at
     * least 20 ns and then wait at least 35 us.
     */

    /* Toggle chip select for ~20ns to wake ext. flash */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 0);
    /* 3 cycles per loop: 2 loop @ 96 MHz ~= 62 ns */
    CPUDelay(2);
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 1);
    /* Wait for 35 us */
    HapiWaitUs(35);
}

/*
 *  ======== Board_shutDownExtFlash ========
 */
void Board_shutDownExtFlash(void)
{
    /* To be sure we are putting the flash into sleep and not waking it,
     * we first have to make a wake up call
     */
    Board_wakeUpExtFlash();

    /* SPI Flash CS*/
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CS, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_HIGH | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash CLK */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CLK, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash PICO */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_PICO, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash POCI */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_POCI, GPIO_CFG_IN_PD);

    uint8_t extFlashShutdown = 0xB9;

    Board_sendExtFlashByte(extFlashShutdown);

    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_CS);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_CLK);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_PICO);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_POCI);
}


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */

    /* Set non-default cap array trims */
    CKMDSetInitialCapTrim(33, 33);
    CKMDSetTargetCapTrim(33, 33);

    Power_init();

    PowerLPF3_selectLFXT();

    PMCTLSetVoltageRegulator(PMCTL_VOLTAGE_REGULATOR_DCDC);


    PowerLPF3_initHFXTCompensation(61075777, /* floor(14.5616 * 2^22) */
                                   -1831946, /* floor(-0.43677 * 2^22) */
                                   -35777, /* floor(-0.00853 * 2^22) */
                                   419, /* floor(0.0001 * 2^22) */
                                   22,
                                   false);               /* FCFG trim-values available */

    /* HFXT temperature compensation will be performed as long as the measured temperature exceeds -50
     * degrees Celsius, and drifts 2 degrees or more.
     */
    PowerLPF3_enableHFXTCompensation(-50, 2);


    /* ==== /ti/drivers/GPIO initialization ==== */
    /* Setup GPIO module and default-initialise pins */
    GPIO_init();

    /* ==== /ti/drivers/DMA initialization ==== */
    UDMALPF3_init();

    RNG_init();

    Board_shutDownExtFlash();

    Board_initHook();
}

