zephyr_library()

zephyr_compile_definitions(CONFIG_TI_BLE_TRANSPORT_SHARED)
ti_mbedtls_configure_target(${ZEPHYR_CURRENT_LIBRARY})

zephyr_library_sources(
  ble_transport_layer/ble_if.c
  ble_transport_layer/npi_if.c
  ble_transport_layer/ble_transport.c
  ble_transport_layer/hci_transport.c
)

zephyr_library_include_directories(
  .
  inc_adapt
  inc_common
  ${CMAKE_CURRENT_LIST_DIR}/../../../../third_party/mbedtls/ti/configs
  ${CMAKE_CURRENT_LIST_DIR}/../../../../third_party/mbedtls/include
)
