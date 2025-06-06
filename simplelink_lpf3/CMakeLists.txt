# Copyright (c) 2024-2025, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# All targets in this file are for Cortex-M0P

option(USE_BLE_LIB "Use BLE libraries" ON)

add_subdirectory(source/ti/devices)
add_subdirectory(source/ti/boards)

include(${CMAKE_CURRENT_LIST_DIR}/CMakeSources.cmake)

if(CONFIG_HAS_CC23X0_SDK)

  if(CONFIG_SOC_CC2340R5)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  if(CONFIG_SOC_CC2340R53)
    zephyr_compile_definitions(DeviceFamily_CC23X0R5 ${COMPILER})
  endif()

  zephyr_include_directories(
    .
    source
    )

  if(USE_BLE_LIB STREQUAL "ON")
    zephyr_include_directories(source/ti/ble5stack_flash/inc)
  endif()

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    ${SOURCES_DRIVERS_LPF3}
    ${SOURCES_DRIVERS_CC23X0}
    ${SOURCES_KERNEL}
    )
  zephyr_link_libraries(
    ${CMAKE_CURRENT_SOURCE_DIR}/source/third_party/ecc/lib/gcc/m0p/ecc.a
    )
  zephyr_linker_sources(RAM_SECTIONS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ti/drivers/dma/dma.ld
  )

  # Radio Control Layer (RCL) driver
  if(CONFIG_SIMPLELINK_F3_RADIO_DRIVER)
    zephyr_library_sources(
        ${SOURCES_RCL}
        ${SOURCES_RCL_LPF3}
        ${SOURCES_RCL_CC23X0}
      )
  endif()

  function(add_prebuilt_library lib_name prebuilt_path)
    add_library(${lib_name} STATIC IMPORTED GLOBAL)
     set_target_properties(${lib_name} PROPERTIES
       IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/${prebuilt_path}
     )
    zephyr_link_libraries(${lib_name})
  endfunction()

  if(USE_BLE_LIB STREQUAL "ON")
  # prebuilt libs
    if (CONFIG_BT_PERIPHERAL AND (NOT (CONFIG_BT_MESH STREQUAL "y")))
      add_prebuilt_library(blecontroller      source/ti/ble5stack_flash/ble_controller_peripheral.a)
    else()
      add_prebuilt_library(blecontroller      source/ti/ble5stack_flash/ble_controller.a)
    endif()
  endif()

endif()

if(CONFIG_HAS_CC27XX_SDK)

  if(CONFIG_SOC_CC2745R10_Q1)
    zephyr_compile_definitions(DeviceFamily_CC27XX ${COMPILER})
  endif()

  zephyr_include_directories(
    .
    source
    )

  zephyr_library()
  zephyr_library_compile_definitions(${COMPILER})
  zephyr_library_sources(
    ${SOURCES_DRIVERS_LPF3}
    ${SOURCES_DRIVERS_CC27XX}
    ${SOURCES_KERNEL}
    )

endif()
