set(SOURCES_RCL
    LRF.c
    RCL_Buffer.c
    RCL_Debug.c
    RCL_Feature.c
    RCL_Gpio.c
    RCL_Profiling.c
    RCL_Scheduler.c
    RCL.c
)

set(SOURCES_RCL_LPF3
    # Command handlers
    handlers/adc_noise.c
    handlers/ble_cs.c
    handlers/ble5.c
    handlers/generic.c
    handlers/ieee.c

    # Wrappers
    wrappers/RCL_AdcNoise.c

    # HAL
    hal/cc23x0/hal_cc23x0.c
    LRFCC23X0.c

    # RCL feature configuration file
    zephyr/rcl_driver_config.c
)

list(TRANSFORM SOURCES_RCL PREPEND source/ti/drivers/rcl/)
list(TRANSFORM SOURCES_RCL_LPF3 PREPEND source/ti/drivers/rcl/)

set(SOURCES_DRIVERS_LPF3
    # Utils
    utils/List.c

    # Drivers
    batterymonitor/BatMonSupportLPF3.c
    batterymonitor/BatteryMonitorLPF3.c
    Temperature.c
    temperature/TemperatureLPF3.c
)

set(SOURCES_DRIVERS_CC23X0
    # Default Simplelink configurations
    power/PowerCC23X0.c

    # Crypto drivers
    cryptoutils/cryptokey/CryptoKeyPlaintext.c
    cryptoutils/ecc/ECCInitLPF3SW.c
    cryptoutils/ecc/ECCParamsLPF3SW.c
    cryptoutils/sharedresources/CryptoResourceLPF3.c
    cryptoutils/utils/CryptoUtils.c
    ECDH.c
    ecdh/ECDHLPF3SW.c
)

set(SOURCES_DRIVERS_CC27XX
    # Default Simplelink configurations
    power/PowerCC27XX.c

    # Crypto drivers
    cryptoutils/cryptokey/CryptoKeyPlaintext.c
    cryptoutils/ecc/ECCInitLPF3SW.c
    cryptoutils/ecc/ECCParamsLPF3SW.c
    cryptoutils/sharedresources/CryptoResourceLPF3.c
    cryptoutils/utils/CryptoUtils.c
    ECDH.c
    ecdh/ECDHLPF3SW.c
)

list(TRANSFORM SOURCES_DRIVERS_LPF3 PREPEND source/ti/drivers/)
list(TRANSFORM SOURCES_DRIVERS_CC23X0 PREPEND source/ti/drivers/)
list(TRANSFORM SOURCES_DRIVERS_CC27XX PREPEND source/ti/drivers/)

set(SOURCES_KERNEL
    # DPL
    ClockP_zephyr.c
    dpl.c
    HwiP_zephyr.c
    MessageQueueP_zephyr.c
    MutexP_zephyr.c
    SemaphoreP_zephyr.c
    SwiP_zephyr.c
    TaskP_zephyr.c
)

set(SOURCES_KERNEL_EVENTS
    EventP_zephyr.c
)

if(CONFIG_EVENTS)
    set(SOURCES_KERNEL ${SOURCES_KERNEL} ${SOURCES_KERNEL_EVENTS})
endif()

list(TRANSFORM SOURCES_KERNEL PREPEND kernel/zephyr/dpl/)

set(SOURCES_OVERLOADS
    overloads/overloads.c
)
