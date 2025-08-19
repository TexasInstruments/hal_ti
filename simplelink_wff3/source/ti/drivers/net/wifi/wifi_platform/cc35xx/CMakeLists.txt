cmake_minimum_required(VERSION 3.26)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_PATH)
cmake_path(GET PARENT_PATH              FILENAME    PARENT_NAME)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME    TARGET_NAME)
set(TARGET_NAME ${PARENT_NAME}_${TARGET_NAME})

#restrict this target for allowed build types only
validate_target(${TARGET_NAME})


message(STATUS "Generating target           ${TARGET_NAME}")

set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/plat/bus_hif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/plat/init_device.c
    ${CMAKE_CURRENT_SOURCE_DIR}/plat/time_util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/plat/wlan_irq_adapt.c

)

set(${TARGET_NAME}_INCLUDES

    ${CMAKE_CURRENT_SOURCE_DIR}/inc_common

    #external includes
    ${CORESDK_WFF3}/source

    $<TARGET_PROPERTY:wifi_host_driver,INCLUDE_DIRECTORIES>

)

set (${TARGET_NAME}_COMPILER_FLAGS )

set (${TARGET_NAME}_DEFINITIONS )

set (${TARGET_NAME}_HEADERS )


add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
