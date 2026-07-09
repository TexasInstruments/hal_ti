zephyr_library()

zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})

zephyr_library_sources(
  plat/bus_hif.c
  plat/init_device.c
  plat/time_util.c
  plat/otfde_driver.c
  plat/wlan_irq_adapt.c
  plat/hif.c
  plat/crypto_mbedtls.c
)

if(CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_PSA)
  zephyr_library_compile_definitions(TI_WIFI_CRYPTO_BACKEND_ZEPHYR_PSA)
  zephyr_library_sources(
    plat/crypto_backend_zephyr_common.c
    plat/crypto_backend_zephyr_psa.c
  )
elseif(CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_MBEDTLS)
  zephyr_library_compile_definitions(TI_WIFI_CRYPTO_BACKEND_ZEPHYR_MBEDTLS)
  zephyr_library_sources(
    plat/crypto_backend_zephyr_common.c
    plat/crypto_backend_zephyr_mbedtls.c
  )
else()
  zephyr_library_sources(
    plat/crypto_backend.c
    plat/tls_mbedtls.c
  )
endif()

zephyr_include_directories(
  inc_common
  plat
)

if(CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_PSA OR CONFIG_WIFI_TI_CC35XX_USE_ZEPHYR_MBEDTLS)
  zephyr_library_link_libraries(mbedTLS)
else()
  ti_mbedtls_configure_target(${ZEPHYR_CURRENT_LIBRARY})
endif()
