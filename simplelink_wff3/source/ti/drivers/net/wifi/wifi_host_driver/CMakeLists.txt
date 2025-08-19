cmake_minimum_required(VERSION 3.26)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME    TARGET_NAME)
message(STATUS "Generating target           ${TARGET_NAME}")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/commands.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/fw_event_handle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/fw_event_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/rx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/trnspt_if.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/trnspt_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer/txn_bus_drv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/ip_utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/osi_common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/w_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/timer.c

)

set (${TARGET_NAME}_INCLUDES

    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc_common
    ${CMAKE_CURRENT_SOURCE_DIR}/inc_adapt
    ${CMAKE_CURRENT_SOURCE_DIR}/trnspt_layer

)

set (${TARGET_NAME}_COMPILER_FLAGS )

set (${TARGET_NAME}_DEFINITIONS     

)

set (${TARGET_NAME}_HEADERS )

add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
