cmake_minimum_required(VERSION 3.26)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME    TARGET_NAME)

#restrict this target for allowed build types only
validate_target(${TARGET_NAME})


message(STATUS "Generating target           ${TARGET_NAME}")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/app_entry/init_host.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app_entry/wlan_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_ap_access_list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_ap_flow.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_device_flow.c    
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_connection_mng.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_role_activation.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_scan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_station_flow.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cme/cme_tester.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/data_service/tx_ctrl_blk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/data_service/tx_hw_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/tw_driver/tw_driver_tx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/fw_transfer/txResult.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/fw_transfer/txXfer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/Tx_data_clsfr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/rx_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/rx_stack.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/tx_ctrl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/tx_ctrl_params.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/tx_data_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/tx_mgmt_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/udata.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_cc33xx/config_cc33xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_cc33xx/driver_cc35xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_cc33xx/driver_osprey_mx_scan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_cc33xx/driver_ti_wifi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_cc33xx/l2_packet_ti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/eloop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/l2_cfg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/wlan_links.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/drv_ti_ap_specific.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/drv_ti_mlme.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/drv_ti_sta_specific.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/drv_ti_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/drv_ext_app.c    
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/rsn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services/80211_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services/ie_parser_util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services/mlme_parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services/regulatory_domain.c
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services/scan_result_table.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fw_control_cmd/control_cmd_fw.c

)

set (${TARGET_NAME}_HEADERS

     $<TARGET_PROPERTY:hostap,PRECOMPILE_HEADERS>
)

set (${TARGET_NAME}_INCLUDES

     ${CMAKE_CURRENT_SOURCE_DIR}
     ${CMAKE_CURRENT_SOURCE_DIR}/cme
     ${CMAKE_CURRENT_SOURCE_DIR}/driver
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/export_inc
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/drv_ti/uwd/src/services
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/udata/export_inc
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/tw_driver
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/data_service/export_inc
     ${CMAKE_CURRENT_SOURCE_DIR}/driver/data_path/twd/fw_transfer/export_inc
     ${CMAKE_CURRENT_SOURCE_DIR}/inc_common
     ${CMAKE_CURRENT_SOURCE_DIR}/inc_shared_w_fw
     ${CMAKE_CURRENT_SOURCE_DIR}/inc_shared_w_fw/inc_common_fw

     $<TARGET_PROPERTY:ble_interface,INCLUDE_DIRECTORIES>
     $<TARGET_PROPERTY:hostap,INCLUDE_DIRECTORIES>
     $<TARGET_PROPERTY:wifi_host_driver,INCLUDE_DIRECTORIES>

)

set (${TARGET_NAME}_LIBRARIES 

    hostap
)

set (${TARGET_NAME}_COMPILER_FLAGS 

     -Wno-address-of-packed-member
)

set (${TARGET_NAME}_DEFINITIONS     

)

#set mbedTLS sources to compile by consumers
if(CRYPTO_MBEDTLS)

    set (${TARGET_NAME}_INTERFACE_SOURCES

         ${CMAKE_CURRENT_SOURCE_DIR}/driver/tls_mbedtls.c
         ${CMAKE_CURRENT_SOURCE_DIR}/driver/crypto_mbedtls.c
    )

endif()


add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
target_link_libraries     (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_LIBRARIES})

set_target_properties     (${TARGET_NAME} PROPERTIES INTERFACE_SOURCES "${${TARGET_NAME}_INTERFACE_SOURCES}")