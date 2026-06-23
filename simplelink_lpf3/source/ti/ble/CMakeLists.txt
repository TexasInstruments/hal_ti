# Copyright (c) 2025 - 2026, Texas Instruments Incorporated
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

# ESL profile includes
if (CONFIG_BT_ESL_TAG OR CONFIG_BT_ESL_AP)
  zephyr_include_directories(profiles/esl/bal)
  zephyr_include_directories(profiles/esl/core)
  zephyr_include_directories(profiles/esl/config)
  zephyr_include_directories(profiles/esl/pal)
endif()

# Set CTRL_CONFIG bitmask based on enabled configs
set(ADV_NCONN_CFG     0x01)
set(ADV_CONN_CFG      0x02)
set(SCAN_CFG          0x04)
set(INIT_CFG          0x08)
set(CTRL_CONFIG       0)

# BT controller configurations
if (CONFIG_BT_HCI_RAW)
  math(EXPR CTRL_CONFIG "${CTRL_CONFIG} | ${ADV_NCONN_CFG} | ${ADV_CONN_CFG} | ${SCAN_CFG} | ${INIT_CFG}")
  zephyr_compile_definitions(
    -DUSE_AE
    -DPOWER_CONTROL
    -DUSE_PERIODIC_ADV
    -DUSE_PERIODIC_SCAN
    -DVENDOR_SPECIFIC_CMD
    -DUSE_PAST_RECEIVER
    -DUSE_PAST_SENDER
    -DUSE_PAWR_SCAN
    -DUSE_PAWR_ADV
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
if (CONFIG_BT_CTLR_LE_POWER_CONTROL)
  zephyr_compile_definitions(
    -DPOWER_CONTROL
  )
endif()
if (CONFIG_BT_HCI_VS)
  zephyr_compile_definitions(
    -DVENDOR_SPECIFIC_CMD
  )
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
if (CONFIG_BT_PER_ADV_RSP)
  zephyr_compile_definitions(
    -DUSE_PAWR_ADV
  )
endif()
if (CONFIG_BT_PER_ADV_SYNC_RSP)
  zephyr_compile_definitions(
    -DUSE_PAWR_SCAN
  )
endif()
if (CONFIG_BT_PER_ADV_SYNC_TRANSFER_SENDER)
  zephyr_compile_definitions(
    -DUSE_PAST_SENDER
  )
endif()
if (CONFIG_BT_PER_ADV_SYNC_TRANSFER_RECEIVER)
  zephyr_compile_definitions(
    -DUSE_PAST_RECEIVER
  )
endif()
if (CONFIG_BT_CHANNEL_SOUNDING)
  zephyr_compile_definitions(
    -DCHANNEL_SOUNDING
  )
endif()
if (CONFIG_RCL_COEX)
  zephyr_compile_definitions(
    -DUSE_COEX
  )
endif()

# BT TI vendor-specific configurations
if (CONFIG_BT_CTLR_TI_LEGACY_CMD)
  zephyr_compile_definitions(
    -DLEGACY_CMD
  )
endif()
if (CONFIG_BT_CTLR_TI_EXT_VS_CMD)
  zephyr_compile_definitions(
    -DEXT_VENDOR_SPECIFIC_CMD
  )
endif()
if (CONFIG_BT_CTRL_TI_VS_RSSI_MONITOR)
  zephyr_compile_definitions(
    -DRSSI_MONITOR
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

# Include source file list
include(BleAppCMakeLists.txt)

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
  if(CONFIG_BT_ESL_TAG OR CONFIG_BT_ESL_AP)
    add_prebuilt_library(esl_core         lib/m0p/esl_core.a)
  endif()
endif()

if(CONFIG_HAS_CC27XXX10_SDK OR CONFIG_HAS_CC27XXX20_SDK)
  add_prebuilt_library(blecontroller      lib/m33f/ble_controller.a)
  if(CONFIG_BT_ESL_TAG OR CONFIG_BT_ESL_AP)
    add_prebuilt_library(esl_core         lib/m33f/esl_core.a)
  endif()
endif()
