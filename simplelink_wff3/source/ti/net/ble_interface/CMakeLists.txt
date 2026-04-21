zephyr_library()

zephyr_compile_definitions(CONFIG_TI_BLE_TRANSPORT_SHARED)

zephyr_library_sources(
  ble_transport_layer/ble_if.c
  ble_transport_layer/npi_if.c
  ble_transport_layer/ble_transport.c
  ble_transport_layer/hci_transport.c
)

zephyr_include_directories(
  .
  inc_adapt
  inc_common
)
