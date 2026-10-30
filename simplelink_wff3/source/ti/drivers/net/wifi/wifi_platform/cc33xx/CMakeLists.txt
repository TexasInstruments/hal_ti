zephyr_library()

zephyr_compile_definitions(DeviceFamily_CC33XX ${COMPILER})

zephyr_library_sources_ifdef(CONFIG_DT_HAS_TI_CC33XX_SPI_ENABLED plat/bus_spi.c)
zephyr_library_sources_ifdef(CONFIG_DT_HAS_TI_CC33XX_SDIO_ENABLED plat/bus_sdio.c)

zephyr_library_sources(
  plat/init_device.c
  plat/io.c
  ../platform/zephyr/crypto_mbedtls_zephyr.c
)

zephyr_library_compile_definitions_ifdef(CONFIG_WIFI_TI_CC33XX_USE_ZEPHYR_MBEDTLS
  TI_WIFI_CRYPTO_BACKEND_ZEPHYR_MBEDTLS)
zephyr_library_compile_definitions_ifdef(CONFIG_WIFI_TI_CC33XX_USE_ZEPHYR_PSA_AES
  TI_WIFI_CRYPTO_BACKEND_ZEPHYR_PSA)

zephyr_compile_definitions(
  TF_PSA_CRYPTO_CONFIG_CHECK_BYPASS
  MBEDTLS_ECP_C=
)

zephyr_include_directories(
  inc_adapt
  plat
  ../platform/zephyr
)

zephyr_library_link_libraries(mbedTLS)
