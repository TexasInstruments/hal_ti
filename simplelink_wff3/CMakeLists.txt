add_subdirectory(source/ti/devices)

if(CONFIG_HAS_CC35XX_SDK)
  if(CONFIG_SOC_SERIES_CC35XXE)
    zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})
    zephyr_include_directories(
      .
      source
      source/ti/drivers
      third_party/hsmddk/include/Kit/Log/incl/
      )

    zephyr_library()
    zephyr_library_compile_definitions(${COMPILER})
    zephyr_library_sources(
      kernel/zephyr/dpl/ClockP_zephyr.c
      kernel/zephyr/dpl/HwiP_zephyr.c
      kernel/zephyr/dpl/SwiP_zephyr.c
      kernel/zephyr/dpl/SemaphoreP_zephyr.c
      kernel/zephyr/dpl/QueueP_zephyr.c

      source/ti/drivers/UART2.c
      source/ti/drivers/uart2/UART2WFF3.c
      source/ti/devices/cc35xx/driverlib/uart.c
	  source/ti/devices/cc35xx/driverlib/spi.c
      source/ti/drivers/GPIO.c
      source/ti/drivers/gpio/GPIOWFF3.c
      source/ti/drivers/dma/DMAWFF3.c
      source/ti/devices/cc35xx/driverlib/dma.c
      source/ti/drivers/power/PowerWFF3.c
      source/ti/drivers/cryptoutils/hsm/HSMLPF3.c

      source/ti/drivers/utils/RingBuf.c
      source/ti/drivers/utils/List.c
      )
      if(CONFIG_ENTROPY_CC35XX_RNG)
        zephyr_library_sources(
          third_party/hsmddk/include/Integration/HSMSAL/HSMSAL.c
          third_party/hsmddk/include/Integration/Adapter_DriverInit/Driver/src/adapter_init.c
          third_party/hsmddk/include/Integration/Adapter_DriverInit/Driver/src/adapter_driver_init.c
          third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_init.c
          third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_device.c
          third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_physicaltoken.c
          third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_identity.c
          third_party/hsmddk/include/Integration/Adapter_VEX/src/adapter_vex_mailbox.c
          third_party/hsmddk/include/Integration/Adapter_Generic/src/adapter_interrupts.c
          third_party/hsmddk/include/Integration/DriverFramework/src/device_generic.c
          third_party/hsmddk/include/Integration/DriverFramework/src/hwpal_device_mb.c
          third_party/hsmddk/include/Kit/EIP130/MailboxControl/src/eip130.c
          third_party/hsmddk/include/Kit/EIP201/src/eip201.c
          third_party/hsmddk/include/Kit/Log/src/log.c
        )
      endif()
  endif()
endif()
