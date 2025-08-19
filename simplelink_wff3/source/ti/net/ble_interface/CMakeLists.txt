cmake_minimum_required(VERSION 3.26)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME    TARGET_NAME)

#restrict this target for allowed build types only
validate_target(${TARGET_NAME})


message(STATUS "Generating target           ${TARGET_NAME}")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/ble_hci_interface/hci_transport.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ble_transport_layer/ble_transport.c

)

set (${TARGET_NAME}_INCLUDES

    #local includes
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc_adapt
    ${CMAKE_CURRENT_SOURCE_DIR}/inc_common

    #external includes
    $<TARGET_PROPERTY:nimble,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:wifi_host_driver,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:wifi_stack,INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:wifi_interface,INCLUDE_DIRECTORIES>
    
)

set (${TARGET_NAME}_COMPILER_FLAGS )

set (${TARGET_NAME}_DEFINITIONS )

set (${TARGET_NAME}_HEADERS )

add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
