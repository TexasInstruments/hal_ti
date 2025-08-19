zephyr_include_directories(
  .
  )

zephyr_library()

zephyr_library_sources(
  # driverlib/aes_gcc.s
  # driverlib/udma.c
  driverlib/interrupt.c
  # driverlib/lrfd.c
  driverlib/setup.c
  # driverlib/uart.c
  # driverlib/spi.c
  # driverlib/vims.c
  # driverlib/adc.c
  driverlib/cpu.c
  # driverlib/i2c.c
  )