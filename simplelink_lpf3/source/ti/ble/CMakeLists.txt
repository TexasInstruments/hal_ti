# Copyright (c) 2025, Texas Instruments Incorporated
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

zephyr_library()
zephyr_library_link_libraries(subsys__bluetooth)

zephyr_include_directories(controller/hci)
zephyr_include_directories(stack_util)

# Set CTRL_CONFIG bitmask based on enabled configs
set(ADV_NCONN_CFG     0x01)
set(ADV_CONN_CFG      0x02)
set(SCAN_CFG          0x04)
set(INIT_CFG          0x08)
set(CTRL_CONFIG       0)

if (CONFIG_BT_HCI_RAW)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${ADV_NCONN_CFG} | ${ADV_CONN_CFG} | ${SCAN_CFG} | ${INIT_CFG}")
  zephyr_compile_definitions(
    -DUSE_PERIODIC_ADV
    -DUSE_AE
  )
endif()
if (CONFIG_BT_BROADCASTER)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${ADV_NCONN_CFG}")
endif()
if (CONFIG_BT_OBSERVER)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${SCAN_CFG}")
endif()
if (CONFIG_BT_PERIPHERAL)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${ADV_NCONN_CFG} | ${ADV_CONN_CFG}")
endif()
if (CONFIG_BT_CENTRAL)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${SCAN_CFG} | ${INIT_CFG}")
endif()
if (CONFIG_BT_EXT_ADV)
  zephyr_compile_definitions(
    -DUSE_AE
  )
endif()
if (CONFIG_BT_PER_ADV)
  zephyr_compile_definitions(
    -DUSE_PERIODIC_ADV
  )
endif()
if (CONFIG_BT_PER_ADV_SYNC)
  zephyr_compile_definitions(
    -DUSE_PERIODIC_SCAN
  )
endif()

zephyr_compile_definitions(
  -DCONTROLLER_ONLY
  -DADV_NCONN_CFG=${ADV_NCONN_CFG}
  -DADV_CONN_CFG=${ADV_CONN_CFG}
  -DSCAN_CFG=${SCAN_CFG}
  -DINIT_CFG=${INIT_CFG}
  -DCTRL_CONFIG=${CTRL_CONFIG}
)

# BLE files that are used for library optimizations and should be part of the application
zephyr_library_sources(
  stack_util/lib_opt/src/ctrl_opt_padv.c
  stack_util/lib_opt/src/ctrl_opt_pscan.c
  stack_util/lib_opt/src/ctrl_opt_cs.c
  stack_util/lib_opt/src/ctrl_opt_cs_test.c
  stack_util/lib_opt/src/ctrl_opt_initiator.c
  stack_util/lib_opt/src/ctrl_opt_connectable.c
  stack_util/lib_opt/src/ctrl_opt_scanner.c
  stack_util/lib_opt/src/ctrl_opt_power_control.c
  stack_util/lib_opt/src/ctrl_opt_rssi_monitor.c
  #stack_util/lib_opt/src/ctrl_opt_legacy_cmd.c
  stack_util/lib_opt/src/ctrl_opt_health_check.c
  stack_util/lib_opt/src/ctrl_opt_adv_conn.c
  stack_util/lib_opt/src/ctrl_opt_adv_nconn.c
  stack_util/lib_opt/src/ctrl_opt_ae.c
  stack_util/lib_opt/src/ctrl_opt_adaptivity.c
  #stack_util/lib_opt/src/ctrl_opt_ble_health.c
  app_util/config/src/ble_config_zephyr.c
  app_util/config/src/hci_supported_cmd.c
)

function(add_prebuilt_library lib_name prebuilt_path)
  add_library(${lib_name} STATIC IMPORTED GLOBAL)
    set_target_properties(${lib_name} PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/${prebuilt_path}
    )
  zephyr_link_libraries(${lib_name})
endfunction()

# prebuilt libs

if(CONFIG_HAS_CC23X0_SDK)
  add_prebuilt_library(blecontroller      lib/m0p/ble_controller.a)
endif()

if(CONFIG_HAS_CC27XX_SDK)
  add_prebuilt_library(blecontroller      lib/m33f/ble_controller.a)
endif()