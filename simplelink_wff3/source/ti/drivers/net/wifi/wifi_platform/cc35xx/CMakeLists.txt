zephyr_library()

zephyr_compile_definitions(DeviceFamily_CC35XX ${COMPILER})

zephyr_library_sources(
  plat/bus_hif.c
  plat/init_device.c
  plat/time_util.c
  plat/wlan_irq_adapt.c
)

zephyr_include_directories(
  inc_common
)
