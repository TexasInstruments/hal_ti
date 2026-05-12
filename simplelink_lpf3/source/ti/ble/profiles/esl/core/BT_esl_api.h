
/**
 *  \file BT_esl_api.h
 *  \brief This file defines the EtherMind Electronic Shelf Label Interfaces
 *  its Data Structures and Methods.
 */

/*
 *  Copyright (C) 2025. LTIMindtree Limited.
 *  All rights reserved.
 */

#ifndef _H_BT_ESL_
#define _H_BT_ESL_

/**
 * \defgroup EtherMind_ESL_Modules EtherMind ESL Modules
 * \brief This section describes various different components that stitch
 * together and makeup the EtherMind ESL Implementation all-together. The
 * various modules within the EtherMind ESL Implementation, the interfaces
 * exposed by each of them are captured in this section.
 */

/**
 * \defgroup EtherMind_ESL_Core ESL Core
 * \ingroup EtherMind_ESL_Modules
 * \brief ESL Core block comprises of Access Point and Tag/Label modules as
 * described in the ESL Service and Profile Specifications. This sections
 * captures the interfaces & APIs offered by these modules to the application.
 * Visit the below URL from Bluetooth SIG for the current supported
 * version of
 * 1. Electronic Shelf Label Service Specification
 * https://www.bluetooth.com/specifications/specs/electronic-shelf-label-service-1-0/
 * 2. Electronic Shelf Label Profile Specification
 * https://www.bluetooth.com/specifications/specs/electronic-shelf-label-profile-1-0/
 */

/**
 * \defgroup EtherMind_ESL_Access_Point ESL Access Point
 * \ingroup EtherMind_ESL_Core
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * ESL Access Point module to the Application.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_AP_Defines Defines
 * \ingroup EtherMind_ESL_Access_Point
 * \brief This section describes the various Defines in EtherMind ESL Access
 * Point module.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_AP_Constants Constants
 * \ingroup EtherMind_ESL_AP_Defines
 * \brief This section describes all the Constants that are exposed by EtherMind
 * ESL Access Point module.
 */

/**
 * \defgroup EtherMind_ESL_AP_Macros Macros
 * \ingroup EtherMind_ESL_AP_Defines
 * \brief This section describes all the Macros that are exposed by EtherMind
 * ESL Access Point module.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_AP_Events Events
 * \ingroup EtherMind_ESL_AP_Defines
 * \brief This section describes all the Asynchronous Event codes that are
 * exposed and received by EtherMind ESL Access Point module.
 */
/**
 * \endcond
 */

/**
 * \defgroup EtherMind_ESL_AP_Error_Codes Error Codes
 * \ingroup EtherMind_ESL_AP_Defines
 * \brief This section describes all the Error Codes that are reported by
 * EtherMind ESL Access Point module.
 */

/**
 * \defgroup EtherMind_ESL_AP_Structures Structures
 * \ingroup EtherMind_ESL_AP_Defines
 * \brief This section describes the various Data-Types and Structures used in
 * EtherMind ESL Access Point module.
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_AP_CB Application Callbacks
 * \ingroup EtherMind_ESL_Access_Point
 * \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind ESL Access Point.
 */

/**
 * \defgroup EtherMind_ESL_AP_api_defs API Definitions
 * \ingroup EtherMind_ESL_Access_Point
 * \brief This section describes the EtherMind ESL Access Point APIs.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_AP_cli_cmds CLI Commands
 * \ingroup EtherMind_ESL_Access_Point
 * \brief This section describes the EtherMind ESL Access Point CLI Commands.
 */
/**
 * \endcond
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_Tag ESL Tag/Label
 * \ingroup EtherMind_ESL_Core
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * ESL Tag/Label module to the Application.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_TAG_Defines Defines
 * \ingroup EtherMind_ESL_Tag
 * \brief This section describes the various Defines in EtherMind ESL Tag/Label
 * module.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_TAG_Constants Constants
 * \ingroup EtherMind_ESL_TAG_Defines
 * \brief This section describes all the Constants that are exposed by EtherMind
 * ESL Tag/Label module.
 */

/**
 * \defgroup EtherMind_ESL_TAG_Macros Macros
 * \ingroup EtherMind_ESL_TAG_Defines
 * \brief This section describes all the Macros that are exposed by EtherMind
 * ESL Tag/Label module.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_TAG_Events Events
 * \ingroup EtherMind_ESL_TAG_Defines
 * \brief This section describes all the Asynchronous Event codes that are
 * exposed and received by EtherMind ESL Tag/Label module.
 */
/**
 * \endcond
 */

/**
 * \defgroup EtherMind_ESL_TAG_Error_Codes Error Codes
 * \ingroup EtherMind_ESL_TAG_Defines
 * \brief This section describes all the Error Codes that are reported by
 * EtherMind ESL Tag/Label module.
 */

/**
 * \defgroup EtherMind_ESL_TAG_Structures Structures
 * \ingroup EtherMind_ESL_TAG_Defines
 * \brief This section describes the various Data-Types and Structures used in
 * EtherMind ESL Tag/Label module.
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_TAG_CB Application Callbacks
 * \ingroup EtherMind_ESL_Tag
 * \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind ESL Tag/Label.
 */

/**
 * \defgroup EtherMind_ESL_TAG_api_defs API Definitions
 * \ingroup EtherMind_ESL_Tag
 * \brief This section describes the EtherMind ESL Tag/Label APIs.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_TAG_cli_cmds CLI Commands
 * \ingroup EtherMind_ESL_Tag
 * \brief This section describes the EtherMind ESL Tag/Label CLI Commands.
 */
/**
 * \endcond
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_Common ESL Common
 * \ingroup EtherMind_ESL_Core
 * \brief This section describes the interfaces & APIs offered by the
 * EtherMind ESL Common module to the Application.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_Common_Defines Defines
 * \ingroup EtherMind_ESL_Common
 * \brief This section describes the various Defines in EtherMind ESL Common
 * module.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_Common_Constants Constants
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes all the Constants that are exposed by EtherMind
 * ESL Common module.
 */

/**
 * \defgroup EtherMind_ESL_Common_Macros Macros
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes all the Macros that are exposed by EtherMind
 * ESL Common module.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_Common_Events Events
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes all the Asynchronous Event codes that are
 * exposed and received by EtherMind ESL Common module.
 */
/**
 * \endcond
 */

/**
 * \defgroup EtherMind_ESL_Common_Error_Codes Error Codes
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes all the Error Codes that are reported by
 * EtherMind ESL Common module.
 * <p>
 * \anchor esl_error_code_overview
 * <b>Theory:</b>
 * <p>
 *   Most APIs under ESL Profile Suite returns \ref API_RESULT,
 *   which is a 2 Byte Unsigned short-int variable. The higher order byte
 *   signifies the Module from which the Error has been generated, and
 *   the lower order byte encodes the actual reason of Error.
 *   <p>
 *   Each module under ESL Profile Suite is given unique
 *   Error ID (the higher order byte). Also, for each module the Error
 *   Code (the lower order byte) signifies an unique error situation.
 *   <p>
 *   For ESL Modules (e.g., Access Point, Tag etc.), Error IDs are
 *   assigned from the range 0x01 to 0x0F.
 *   <p>
 *   The definition of \ref BT_ESL_API_SUCCESS is 0x0000 - which is the 'Success'
 *   return value for an API returning \ref API_RESULT. All other values for
 *   should be treated as Errors.
 *   <p>
 *   The definition of \ref BT_ESL_API_FAILURE is 0xFFFF - which stands for
 *   "Unknown Error Situation".
 *   <p>
 * <b>Note:</b>
 *   <p>
 *   The applications using native/profile ESL API should NOT do
 *   any check on the basis of \ref BT_ESL_API_FAILURE - rather, the correct way to
 *   detect an error situation is by doing a negative check on \ref
 *   BT_ESL_API_SUCCESS.
 *   <p>
 *   For example,
 *   \code if ( BT_ESL_AP_FAILURE == BT_esl_ap_init(x, y) ) \endcode
 *   ... Wrong !
 *   <p>
 *   <p>
 *   \code if ( BT_ESL_AP_SUCCESS != BT_esl_ap_init(x, y) ) \endcode
 *   ... Correct !
 */

/**
 * \defgroup EtherMind_ESL_Common_Structures Structures
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes the various Data-Types and Structures used in
 * EtherMind ESL Common module.
 */

/**
 * \defgroup EtherMind_ESL_Common_Features Feature Flags
 * \ingroup EtherMind_ESL_Common_Defines
 * \brief This section describes the various Compilation Feature Flags used in
 * EtherMind ESL Common module.
 */

 /**
  * \defgroup EtherMind_ESL_Common_Limits Configurable Limits
  * \ingroup EtherMind_ESL_Common_Defines
  * \brief This section describes all the Configurable that are exposed by
  * EtherMind ESL Common module.
  */

/** \} */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_Common_CB Application Callbacks
 * \ingroup EtherMind_ESL_Common
 * \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind ESL Common.
 */

/**
 * \endcond
 */

/**
 * \defgroup EtherMind_ESL_Common_api_defs API Definitions
 * \ingroup EtherMind_ESL_Common
 * \brief This section describes the EtherMind ESL Common APIs.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_Common_cli_cmds CLI Commands
 * \ingroup EtherMind_ESL_Common
 * \brief This section describes the EtherMind ESL Common CLI Commands.
 */

/**
 * \endcond
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_BAL ESL Bluetooth Bearer Abstraction
 * \ingroup EtherMind_ESL_Modules
 * \brief This section describes the interfaces & APIs offered by the
 * EtherMind ESL Bluetooth Bearer Abstraction module to the Application.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_BAL_Defines Defines
 * \ingroup EtherMind_ESL_BAL
 * \brief This section describes the various Defines in EtherMind ESL
 * Bluetooth Bearer Abstraction module.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_BAL_Constants Constants
 * \ingroup EtherMind_ESL_BAL_Defines
 * \brief This section describes all the Constants that are exposed by
 * EtherMind ESL Bluetooth Bearer Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_BAL_Macros Macros
 * \ingroup EtherMind_ESL_BAL_Defines
 * \brief This section describes all the Macros that are exposed by EtherMind
 * ESL Bluetooth Bearer Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_BAL_Events Events
 * \ingroup EtherMind_ESL_BAL_Defines
 * \brief This section describes all the Asynchronous Event codes that are
 * exposed and received by EtherMind ESL Bluetooth Bearer Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_BAL_Error_Codes Error Codes
 * \ingroup EtherMind_ESL_BAL_Defines
 * \brief This section describes all the Error Codes that are reported by
 * EtherMind ESL Bluetooth Bearer Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_BAL_Structures Structures
 * \ingroup EtherMind_ESL_BAL_Defines
 * \brief This section describes the various Data-Types and Structures used in
 * EtherMind ESL Bluetooth Bearer Abstraction module.
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_BAL_CB Application Callbacks
 * \ingroup EtherMind_ESL_BAL
 * \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind ESL Bluetooth Bearer Abstraction.
 */

/**
 * \defgroup EtherMind_ESL_BAL_api_defs API Definitions
 * \ingroup EtherMind_ESL_BAL
 * \brief This section describes the EtherMind ESL Bluetooth Bearer
 * Abstraction APIs.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_BAL_cli_cmds CLI Commands
 * \ingroup EtherMind_ESL_BAL
 * \brief This section describes the EtherMind ESL Bluetooth Bearer Abstraction
 * CLI Commands.
 */
/**
 * \endcond
 */

/** \} */

/**
 * \defgroup EtherMind_ESL_PAL ESL Platform Abstraction
 * \ingroup EtherMind_ESL_Modules
 * \brief This section describes the interfaces & APIs offered by the
 * EtherMind ESL Platform Abstraction module to the Application.
 * The Platform Abstraction Module typically consists of the following:
 *   1. Operating System Abstraction Layer (OSAL)
 *      This includes things related to data-types, Task & Thread creation
 *      Synchronization etc.
 *   2. Memory management abstractions
 *   3. Timer Module abstractions
 *   4. Any persistent storage or Non-Volatile memory management abstractions
 *   5. Debug Interfaces
 *   6. Peripherals and other utilities related abstractions, e.g.: LED
 *      abstractions etc.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_PAL_Defines Defines
 * \ingroup EtherMind_ESL_PAL
 * \brief This section describes the various Defines in EtherMind ESL
 * Platform Abstraction module.
 * \{
 */

/**
 * \defgroup EtherMind_ESL_PAL_Constants Constants
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes all the Constants that are exposed by
 * EtherMind ESL Platform Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_PAL_Macros Macros
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes all the Macros that are exposed by EtherMind
 * ESL Platform Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_PAL_Events Events
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes all the Asynchronous Event codes that are
 * exposed and received by EtherMind ESL Platform Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_PAL_Error_Codes Error Codes
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes all the Error Codes that are reported by
 * EtherMind ESL Platform Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_PAL_Structures Structures
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes the various Data-Types and Structures used in
 * EtherMind ESL Platform Abstraction module.
 */

/**
 * \defgroup EtherMind_ESL_PAL_Features Feature Flags
 * \ingroup EtherMind_ESL_PAL_Defines
 * \brief This section describes the various Compilation Feature Flags used in
 * EtherMind ESL Platform Abstraction module.
 */

/** \} */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_PAL_CB Application Callbacks
 * \ingroup EtherMind_ESL_PAL
 * \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind ESL Platform Abstraction.
 */

/**
 * \endcond
 */

/**
 * \defgroup EtherMind_ESL_PAL_api_defs API Definitions
 * \ingroup EtherMind_ESL_PAL
 * \brief This section describes the EtherMind ESL Platform Abstraction APIs.
 */

/**
 * \cond ignore_this Ignore this function while generating Doxygen document
 */

/**
 * \defgroup EtherMind_ESL_PAL_cli_cmds CLI Commands
 * \ingroup EtherMind_ESL_PAL
 * \brief This section describes the EtherMind ESL Platform Abstraction
 * CLI Commands.
 */
/**
 * \endcond
 */

/** \} */

/* --------------------------------------------- Header File Inclusion */
#include "BT_esl_common.h"

/* --------------------------------------------- Global Definitions */

/**
 * \addtogroup EtherMind_ESL_Common_Constants
 * \{
 */

/**
 * \name ESL Key Material Constants
 * \{
 */
/** ESL Session Key Length */
#define BT_ESL_SESSION_KEY_LEN                         16U
/** ESL Initialization Vector (IV) Length */
#define BT_ESL_IV_LEN                                  8U
/** \} */

/**
 * \name ESL Common Limits
 * \{
 */

/**
 * Maximum size of the Sensor Info of one sensor
 */
#define BT_ESL_MAX_SENSOR_INFO_LENGTH_PER_SENSOR       5U
/**
 * Maximum size of the Sensor Info
 */
#define BT_ESL_MAX_SENSOR_INFO_LENGTH  \
        (BT_ESL_MAX_SENSOR_SUPPORTED * BT_ESL_MAX_SENSOR_INFO_LENGTH_PER_SENSOR)

/**
 * Maximum Sensor data length
 * (Refer in ESL Bluetooth spec, in section 3.9.3.5)
 */
#define BT_ESL_MAX_SENSOR_DATA_LEN                     15U

/** Broadcast ESL ID */
#define BT_ESL_BROADCAST_ESL_ID                        0xFFU

/**
 * Maximum ESL ID supported in ESL Address
 * (Refer 3.1.1.2 in ESL Bluetooth spec)
 */
#define BT_ESL_MAX_ESL_ID_SUPPORTED                    254U

/**
 * Maximum Group ID supported in ESL Address
 * (Refer 3.1.1.2 in ESL Bluetooth spec)
 */
#define BT_ESL_MAX_GROUP_ID_SUPPORTED                  127U

/** Group ID Initialization value */
#define BT_ESL_GROUP_ID_INIT_VAL                       0xFFU

/** ESL ID Initialization value */
#define BT_ESL_ID_INIT_VAL                             0xFFU

/** Maximum Advertising Data Length */
#define BT_ESL_HCI_MAX_ADVERTISING_DATA_LENGTH         0x1FU
/** \} */

/**
 * \name ESL Control Point Command Opcodes
 * (Refer table 3.7 in section 3.9.2, in ESL Bluetooth spec)
 * \{
 */
/** ESL Ping Opcode */
#define BT_ESL_PING                                0x00U
/** ESL Un-associate from AP Opcode */
#define BT_ESL_UNASSOCIATE_FROM_AP                 0x01U
/** ESL Service Reset Opcode */
#define BT_ESL_SERVICE_RESET                       0x02U
/** ESL Factory Reset Opcode */
#define BT_ESL_FACTORY_RESET                       0x03U
/** ESL Update Complete Opcode */
#define BT_ESL_UPDATE_COMPLETE                     0x04U
/** ESL Read Sensor Data Opcode */
#define BT_ESL_READ_SENSOR_DATA                    0x10U
/** ESL Refresh Display Opcode */
#define BT_ESL_REFRESH_DISPLAY                     0x11U
/** ESL Display Image Opcode */
#define BT_ESL_DISPLAY_IMAGE                       0x20U
/** ESL Display Timed Image Opcode */
#define BT_ESL_DISPLAY_TIMED_IMAGE                 0x60U
/** ESL LED Control Opcode */
#define BT_ESL_LED_CONTROL                         0xB0U
/** ESL LED Timed Control Opcode */
#define BT_ESL_LED_TIMED_CONTROL                   0xF0U
#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
/** ESL Vendor Specific Command Base Opcode */
#define BT_ESL_VENDOR_SPECIFIC_TAG_BASE            0x0FU
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */
/** \} */


/**
 * \name ESL Response Opcodes
 * (Refer table 3.19 in section 3.9.3, in ESL Bluetooth spec)
 * \{
 */
/** ESL Error Response Opcode */
#define BT_ESL_ERROR                               0x00U
/** ESL LED State Response Opcode */
#define BT_ESL_LED_STATE                           0x01U
/** ESL Basic State Response Opcode */
#define BT_ESL_BASIC_STATE                         0x10U
/** ESL Display State Response Opcode */
#define BT_ESL_DISPLAY_STATE                       0x11U
/** ESL Sensor Value Response Opcode */
#define BT_ESL_SENSOR_VALUE                        0x0EU
#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
/** ESL Vendor Specific Base Response Opcode */
#define BT_ESL_VENDOR_SPECIFIC_RESPONSE_BASE       0x0FU
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */
/** \} */

/**
 * \name Basic State Bit-Positions
 * (Refer table 3.22 in section 3.9.3.3, in ESL Bluetooth spec)
 * \{
 */
/** Service Needed Bit */
#define BT_ESL_BASIC_STATE_SERV_NEEDED_BIT         0U
/** Synchronized Bit */
#define BT_ESL_BASIC_STATE_SYNCHRONISED_BIT        1U
/** Active LED Bit */
#define BT_ESL_BASIC_STATE_ACTIVE_LED_BIT          2U
/** Pending LED Update Bit */
#define BT_ESL_BASIC_STATE_PNDG_LED_UPDT_BIT       3U
/** Pending Display Update Bit */
#define BT_ESL_BASIC_STATE_PNDG_DISP_UPDT_BIT      4U
/** \} */

/**
 * \name ESL LED Type Mask
 * (Refer table 3.4 in section 3.8.1, in ESL Bluetooth spec)
 * \{
 */
/** BIT-7 is RESET and BIT-6 is RESET i.e. are 00b */
#define BT_ESL_SRGB                                0x00U
/** BIT-7 is RESET and BIT-6 is SET i.e. are 01b */
#define BT_ESL_MONOCHROME                          0x40U
/** \} */

/**
 * \name ESL LED Color level mask for sRGB LED type
 * (Refer table 3.5 in section 3.8.1.1, in ESL Bluetooth spec)
 * \{
 */
/** ESL sRGB Level - Blue */
#define BT_ESL_SRGB_BLUE_LEVEL                     0x30U
/** ESL sRGB Level - Green */
#define BT_ESL_SRGB_GREEN_LEVEL                    0x0CU
/** ESL sRGB Level - Red */
#define BT_ESL_SRGB_RED_LEVEL                      0x03U
/** \} */

/**
 * \name ESL LED Color level mask for Monochrome LED type
 * (Refer table 3.6 in section 3.8.1.2, in ESL Bluetooth spec)
 * \{
 */
/** ESL Monochrome Level - Blue */
#define BT_ESL_MONOCHROME_BLUE_LEVEL               0x30U
/** ESL Monochrome Level - Green */
#define BT_ESL_MONOCHROME_GREEN_LEVEL              0x0CU
/** ESL Monochrome Level - Red */
#define BT_ESL_MONOCHROME_RED_LEVEL                0x03U
/** \} */

/**
 * \name Sensor size types
 * (Refer table 3.3 in section 3.7.1, in ESL Bluetooth spec)
 * \{
 */
/** ESL Sensor info 2 octet size type */
#define BT_ESL_SENSOR_INFO_2_OCTET_SIZE_TYPE       0x00U
/** ESL Sensor info 4 octet size type */
#define BT_ESL_SENSOR_INFO_4_OCTET_SIZE_TYPE       0x01U
/** \} */


/**
 * TODO: Move to assigned numbers file
 */
/**
 * \name ESL Assigned Numbers
 * \{
 */
/** ESL (Electronic Shelf Label) GATT Service UUID */
#define BT_ESL_GATT_ESL_SERVICE                     0x1857U

/** ESL Address characteristic UUID */
#define BT_ESL_ADDRESS_CHARACTERISTIC               0x2BF6U
/** ESL AP Sync Key Material characteristic UUID */
#define BT_ESL_AP_SYNC_KEY_MATERIAL_CHARACTERISTIC  0x2BF7U
/** ESL Response Key Material characteristic UUID */
#define BT_ESL_RESPONSE_KEY_MATERIAL_CHARACTERISTIC 0x2BF8U
/** ESL Current Absolute Time characteristic UUID */
#define BT_ESL_CURRENT_ABSOLUTE_TIME_CHARACTERISTIC 0x2BF9U
/** ESL Display Information characteristic UUID */
#define BT_ESL_DISPLAY_INFORMATION_CHARACTERISTIC   0x2BFAU
/** ESL Image Information characteristic UUID */
#define BT_ESL_IMAGE_INFORMATION_CHARACTERISTIC     0x2BFBU
/** ESL Sensor Information characteristic UUID */
#define BT_ESL_SENSOR_INFORMATION_CHARACTERISTIC    0x2BFCU
/** ESL LED Information characteristic UUID */
#define BT_ESL_LED_INFORMATION_CHARACTERISTIC       0x2BFDU
/** ESL Control Point characteristic UUID */
#define BT_ESL_CONTROL_POINT_CHARACTERISTIC         0x2BFEU
/** \} */

/**
 * \name ESL Characteristic lengths
 * \{
 */
/** ESL Address characteristic length */
#define BT_ESL_ESL_ADDRESS_LEN                     2U
/** ESL Current Absolute Time characteristic length */
#define BT_ESL_CURRENT_ABSOLUTE_TIME_LEN           4U
/** ESL AP Sync Key Material characteristic length */
#define BT_ESL_AP_SYNC_KEY_LEN                     (BT_ESL_SESSION_KEY_LEN + BT_ESL_IV_LEN)
/** ESL Response Key Material characteristic length */
#define BT_ESL_RESPONSE_KEY_LEN                    (BT_ESL_SESSION_KEY_LEN + BT_ESL_IV_LEN)
/** \} */

/**
 * \name ESL Characteristic IDs
 * \{
 */
/** ESL LED information */
#define BT_ESL_LED_INFO_TYPE                       0U
/** ESL Display information */
#define BT_ESL_DISPLAY_INFO_TYPE                   1U
/** ESL Sensor information */
#define BT_ESL_SENSOR_INFO_TYPE                    2U
/** ESL Image information */
#define BT_ESL_IMAGE_INFO_TYPE                     3U
/** ESL Address */
#define BT_ESL_ESL_ADDRESS                         4U
/** AP Sync Key Material */
#define BT_ESL_AP_SYNC_KEY_MATERIAL                5U
/** ESL Response Key Material*/
#define BT_ESL_RESPONSE_KEY_MATERIAL               6U
/** ESL Current Absolute Time */
#define BT_ESL_CURRENT_ABSOLUTE_TIME               7U
/** ESL Control Point */
#define BT_ESL_CONTROL_POINT                       8U
/** \} */

/**
 * \name ESL CCCD values
 * \{
 */
/** ESL CCCD Enable Notification */
#define BT_ESL_CCCD_ENABLE_NOTIFY                 0x0001U
/** ESL CCCD Disable Notification */
#define BT_ESL_CCCD_DISABLE_NOTIFY                0x0000U
/** \} */

/**
 * \name ESL Encrypted Advertisement Data Constants
 * \{
 */
/** Encrypted ADV Data Header Length  */
#define BT_ESL_ENCRYPTED_DATA_AD_HEADER_LEN        2U
/** Encrypted ADV Data Tag Length  */
#define BT_ESL_ENCRYPTED_DATA_AD_TAG_LEN           1U
/** ESL ADV Data Header Length */
#define BT_ESL_AD_HEADER_LEN                       2U
/** ESL Tag length */
#define BT_ESL_AD_TAG_LEN                          1U
/** ESL Maximum Payload Length (Group ID + Multiple TLV`s) */
#define BT_ESL_SYNC_PKT_PAYLOAD_MAX_LEN            48U
/** Encrypted Data Randomizer Length */
#define BT_ESL_EAD_RANDOMIZER_LEN                  5U
/** ESL Synchronization Packet MIC Length */
#define BT_ESL_SYNC_PKT_MIC_LEN                    4U

/**
 * ESL Encrypted Advertisement Data Maximum Length
 *
 * ----------------------------------------------------------------
 * | Len | EDTag  | Encrypted Data                                |
 * ----------------------------------------------------------------
 * |              | Randomizer |  Payload                   | MIC |
 * ----------------------------------------------------------------
 * |                           | Len | ESLTag | ESL Payload |     |
 * ----------------------------------------------------------------
 */
#define BT_ESL_ENCRTYPTED_DATA_MAX_LEN         \
        (BT_ESL_ENCRYPTED_DATA_AD_HEADER_LEN + \
         BT_ESL_EAD_RANDOMIZER_LEN           + \
         BT_ESL_AD_HEADER_LEN                + \
         BT_ESL_SYNC_PKT_PAYLOAD_MAX_LEN     + \
         BT_ESL_SYNC_PKT_MIC_LEN)
/** \} */

/**
 * \name ESL Encrypted Advertisement Data Assigned Numbers
 * \{
 */
/** Advertisement Type for ESL (Assigned Number) */
#define BT_ESL_AD_TYPE                             0x34U
/* Advertisement type for Encrypted Data (Assigned Number) */
#define BT_ESL_ENCRYPTED_DATA_AD_TYPE              0x31U
/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_Common_Error_Codes
 * \{
 */

/**
 * \name ESL Specification defined Response Error Codes
 * (Refer table 3.20 in section 3.9.3.1, in ESL Bluetooth spec)
 * \{
 */
/** ESL Unspecified Error */
#define BT_ESL_UNSPECIFIED_ERROR                   0x01U
/** ESL Invalid Opcode Error */
#define BT_ESL_INVALID_OPCODE                      0x02U
/** ESL Invalid State Error */
#define BT_ESL_INVALID_STATE                       0x03U
/** ESL Invalid Image Index Error */
#define BT_ESL_INVALID_IMAGE_INDEX                 0x04U
/** ESL Image Not Available Error */
#define BT_ESL_IMAGE_NOT_AVAILABLE                 0x05U
/** ESL Invalid Parameters Error */
#define BT_ESL_INVALID_PARAMETERS                  0x06U
/** ESL Capacity Limit Reached Error */
#define BT_ESL_CAPACITY_LIMIT                      0x07U
/** ESL Insufficient Battery Error */
#define BT_ESL_INSUFFICIENT_BATTERY                0x08U
/** ESL Insufficient Resources Error */
#define BT_ESL_INSUFFICIENT_RESOURCES              0x09U
/** ESL Retry Error */
#define BT_ESL_RETRY                               0x0AU
/** ESL Queue Full Error */
#define BT_ESL_QUEUE_FULL                          0x0BU
/** ESL Implausible Absolute Time Error */
#define BT_ESL_IMPLAUSIBLE_ABSOLUTE_TIME           0x0CU
/** \} */

/** \} */

#ifdef BT_ESL_SUPPORT_AP_ROLE
/**
 * \addtogroup EtherMind_ESL_AP_Constants
 * \{
 */

/**
 * \name Access Point Limits
 * \{
 */

/** Attribute handle Initialization value */
#define BT_ESL_AP_ATTR_HANDLE_INIT_VAL             0xFFFFU
/** ESL Control point Max Length */
#define BT_ESL_AP_CP_COMMAND_MAX_LEN               17U
/** Flashing pattern Length */
#define BT_ESL_FLASHING_PATTERN_LENGTH             7U
/** ESL Group ID Length */
#define BT_ESL_AP_GROUP_ID_LEN                     1U
/** ESL ID Length */
#define BT_ESL_AP_ESL_ID_LEN                       1U
/** \} */

/**
 * \name Access Point States
 * \{
 */

/** ESL AP Unassociate State */
#define BT_ESL_AP_UNASSOCIATE                      0x00U
/** ESL AP Connected State */
#define BT_ESL_AP_CONNECTED                        0x01U
/** ESL AP Configuring State */
#define BT_ESL_AP_CONFIGURING                      0x02U
/** ESL AP In-Synchronizing State */
#define BT_ESL_AP_IN_SYNCRONIZING                  0x03U
/** ESL AP Synchronized State */
#define BT_ESL_AP_SYNCHRONIZED                     0x04U
/** ESL AP Unsynchronized State */
#define BT_ESL_AP_UNSYNCHRONIZED                   0x05U
/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_Error_Codes
 * \{
 */

/**
 * \name ESL AP Module Error ID
 * \{
 */
/** ESL AP core Error codes */
#define BT_ESL_AP_ERR_ID                          0x0100U
/** \} */

/**
 * \name ESL AP Implementation Error Codes
 * \{
 */

/** ESL Access Point Success Status Code */
#define BT_ESL_AP_SUCCESS                         BT_ESL_API_SUCCESS
/** ESL Access Point Failure Status Code*/
#define BT_ESL_AP_FAILURE                         BT_ESL_API_FAILURE
/** Timeout for any operation */
#define BT_ESL_AP_TIMEOUT                         (0x0001U | BT_ESL_AP_ERR_ID)
/** Failed for any operation */
#define BT_ESL_AP_FAILED                          (0x0002U | BT_ESL_AP_ERR_ID)
/** ESL AP busy */
#define BT_ESL_AP_BUSY                            (0x0004U | BT_ESL_AP_ERR_ID)
/** ESL AP invalid state */
#define BT_ESL_AP_INVALID_STATE                   (0x0005U | BT_ESL_AP_ERR_ID)
/** ESL AP invalid command */
#define BT_ESL_AP_INVALID_COMMAND                 (0x0006U | BT_ESL_AP_ERR_ID)
/** ESL AP not found */
#define BT_ESL_AP_NOT_FOUND                       (0x0007U | BT_ESL_AP_ERR_ID)
/** ESL AP Invalid Parameters */
#define BT_ESL_AP_INVALID_PARAMETER               (0x0008U | BT_ESL_AP_ERR_ID)
/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_Constants
 * \{
 */

/**
 * \name ESL AP Response status
 * \{
 */
/** ESL AP Response Complete */
#define BT_ESL_AP_RESPONSE_COMPLETE               0x0000U
/** ESL AP Response pending */
#define BT_ESL_AP_RESPONSE_PENDING                0x0001U
/** \} */

/**
 * \name ESL AP Configuring status
 * \{
 */
/** ESL AP Configure Control Point NTF status */
#define BT_ESL_AP_CP_CONFIGURE_NTF_STATE          0x00U
/** ESL AP Set ESL address */
#define BT_ESL_AP_SET_ESL_ADDRESS_STATE           0x01U
/** ESL AP Set AP sync key */
#define BT_ESL_AP_SET_AP_SYNC_KEY_STATE           0x02U
/** ESL AP Set tag response key */
#define BT_ESL_AP_SET_TAG_RESPONSE_KEY_STATE      0x03U
/** ESL AP Set current absolute time */
#define BT_ESL_AP_SET_CURRENT_ABS_TIME_STATE      0x04U
/** ESL AP Configuration complete */
#define BT_ESL_AP_CONFIGURATION_COMPLETE          0x05U
/** ESL AP Configuration IDLE */
#define BT_ESL_AP_CONFIGURATION_IDLE_STATE        0xFFU
/** \} */

/** \} */
#endif /* BT_ESL_SUPPORT_AP_ROLE */

#ifdef BT_ESL_SUPPORT_TAG_ROLE
/**
 * \addtogroup EtherMind_ESL_TAG_Constants
 * \{
 */

 /**
 * \name ESL Tag Limits
 * \{
 */
/** Basic state default Initialization Value */
#define BT_ESL_TAG_BASIC_STATE_INIT_VAL           0x0000U
/** \} */

/**
 * \name ESL TAG States
 * \{
 */
/** ESL Un-associate State */
#define BT_ESL_UNASSOCIATE_STATE                  0U
/** ESL Configuring State */
#define BT_ESL_CONFIGURING_STATE                  1U
/** ESL Configured State */
#define BT_ESL_CONFIGURED_STATE                   2U
/** ESL Synchronized State */
#define BT_ESL_SYNCHRONIZED_STATE                 3U
/** ESL Updating State */
#define BT_ESL_UPDATING_STATE                     4U
/** ESL Unsynchronized State */
#define BT_ESL_UNSYNCHRONIZED_STATE               5U
/** \} */

/**
 * \name ESL packet source
 * \{
 */
/** ESL Control Point */
#define BT_ESL_ECP                                0U
/** ESL Periodic advertisement with response */
#define BT_ESL_PAWR                               1U
/** \} */

/**
 * \name PAST modes
 * \{
 */
/** HCI LE PAST Mode No Synchronization */
#define BT_ESL_HCI_LE_PAST_MODE_NO_SYNC                0x00U
/** HCI LE PAST Mode No Reports */
#define BT_ESL_HCI_LE_PAST_MODE_NO_REPORTS             0x01U
/** HCI LE PAST Mode Synchronized */
#define BT_ESL_HCI_LE_PAST_MODE_SYNC                   0x02U
/** HCI LE PAST Mode Synchronization with Filter Duplicates */
#define BT_ESL_HCI_LE_PAST_MODE_SYNC_FILTER_DUPLICATES 0x03U
/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_TAG_Error_Codes
 * \{
 */

/**
 * \name ESL Tag Module Error ID
 * \{
 */
/** ESL Tag Module Error ID */
#define BT_ESL_TAG_ERR_ID                         0x0200U
/** \} */

/**
 * \name ESL Tag Implementation Error Codes
 * \{
 */
/** ESL Tag Success Status Code */
#define BT_ESL_TAG_SUCCESS                        BT_ESL_API_SUCCESS
/** ESL Tag Failure Status Code */
#define BT_ESL_TAG_FAILURE                        BT_ESL_API_FAILURE
/** ESL TAG Response capacity limit Exceeded */
#define BT_ESL_TAG_RSP_CAPACITY_EXCEEDED          (0x0001U | BT_ESL_TAG_ERR_ID)
/** ESL TAG Invalid parameter */
#define BT_ESL_TAG_INVALID_PARAMS                 (0x0002U | BT_ESL_TAG_ERR_ID)
/** ESL TAG NULL pointer not allowed */
#define BT_ESL_TAG_NULL_VALUE_NOT_ACCEPTABLE      (0x0003U | BT_ESL_TAG_ERR_ID)
/** ESL TAG Timeout */
#define BT_ESL_TAG_TIMEOUT                        (0x0004U | BT_ESL_TAG_ERR_ID)
/** \} */

/** \} */

#endif /* BT_ESL_SUPPORT_TAG_ROLE */


/* --------------------------------------------- Structures/Data Types */
/**
 * \addtogroup EtherMind_ESL_Common_Structures
 * \{
 */

/**
 * \name Common Data Structures for AP & Tag
 * \{
 */

/** Bluetooth Device Address */
typedef struct _BT_ESL_BD_ADDR
{
    /** Bluetooth MAC Address */
    UCHAR    addr[BT_ESL_BD_ADDR_SIZE];

    /** Bluetooth Address Type */
    UCHAR    type;

} BT_ESL_BD_ADDR;

/** ESL Address */
typedef struct _BT_ESL_ADDR
{
    /** Group ID */
    UCHAR group_id;

    /** ESL ID */
    UCHAR esl_id;

} BT_ESL_ADDR;

/**
 * This structure contains the key material used for Encryption and Decryption
 * of adv data
 */
typedef struct _BT_ESL_KEY_MATERIAL
{
    /** Session key */
    UCHAR session_key[BT_ESL_SESSION_KEY_LEN];

    /** IV */
    UCHAR iv[BT_ESL_IV_LEN];

} BT_ESL_KEY_MATERIAL;

/** ESL Display Type */
typedef struct _BT_ESL_DISPLAY
{
    /** Width of the Display */
    UINT16 width;

    /** Height of the Display */
    UINT16 height;

    /** Display Type */
    UCHAR display_type;

} BT_ESL_DISPLAY;

/** ESL LED Type */
typedef struct _BT_ESL_LED
{
    /** LED Type */
    UCHAR led_type;

} BT_ESL_LED;

/** ESL Sensor Type */
typedef struct _BT_ESL_SENSOR_TYPE
{
    /** 4 byte of ID that indicates a type of sensor */
    UINT32 type_32;

    /** 2 byte of ID that indicates a type of sensor */
    UINT16 type_16;

} BT_ESL_SENSOR_TYPE;

/** ESL Sensor related Data Structure */
typedef struct _BT_ESL_SENSOR
{
    /** Sensor Size */
    UCHAR   sensor_size;

    /** Sensor Type */
    BT_ESL_SENSOR_TYPE sensor_type;

} BT_ESL_SENSOR;

/** This structure contains the Sensor Information char value */
typedef struct _BT_ESL_SENSOR_INFO
{
    /** Reference to the list of ESL sensors */
    BT_ESL_SENSOR * esl_sensor;

    /** Number Sensors supported by ESL */
    UCHAR            no_of_sensors;

} BT_ESL_SENSOR_INFO;

/** This structure contains sensor data */
typedef struct _BT_ESL_SENSOR_DATA
{
    /** Sensor data buffer */
    UCHAR sensor_data[BT_ESL_MAX_SENSOR_DATA_LEN];

    /** Sensor data length */
    UCHAR data_length;

} BT_ESL_SENSOR_DATA;

/** This structure contains the LED Information char values */
typedef struct _BT_ESL_LED_INFO
{
    /** Reference to the list of ESL LEDs */
    BT_ESL_LED * esl_led;

    /** Number of LED's supported */
    UCHAR   no_of_leds;

} BT_ESL_LED_INFO;

/** This structure contains the Display Information char value */
typedef struct _BT_ESL_DISPLAY_INFO
{
    /** Reference to the list of display supported by ESL */
    BT_ESL_DISPLAY * esl_display;

    /** Number of displays supported */
    UCHAR  no_of_displays;

} BT_ESL_DISPLAY_INFO;

/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_Structures
 * \{
 */
#ifdef BT_ESL_SUPPORT_AP_ROLE
/** This structure contains the ESL tag attribute handles of ESL service */
typedef struct _BT_ESL_ATTR_HANDLES
{
    /** ESL address attribute handle */
    UINT16 address_hdl;

    /** ESL AP sync key attribute handle */
    UINT16 ap_sync_key_material_hdl;

    /** ESL response key attribute handle */
    UINT16 response_key_material_hdl;

    /** ESL current absolute time attribute handle */
    UINT16 current_absolute_time_hdl;

    /** ESL display info attribute handle */
    UINT16 display_info_hdl;

    /** ESL image info attribute handle */
    UINT16 image_info_hdl;

    /** ESL sensor info attribute handle */
    UINT16 sensor_info_hdl;

    /** ESL LED info attribute handle */
    UINT16 led_info_hdl;

    /** ESL control point attribute handle */
    UINT16 cp_hdl;

    /** ESL control point CCCD attribute handle */
    UINT16 cp_cccd_hdl;

} BT_ESL_ATTR_HANDLES;

/** This structure contains the info of the ESL tag */
typedef struct _BT_ESL_TAG
{
    /** ESL tag address */
    BT_ESL_ADDR           esl_address;

    /** ESL tag BD address */
    BT_ESL_BD_ADDR         esl_bd_addr;

    /** ESL tag state */
    UCHAR                  sm_state;

    /** ESL configuring state */
    UCHAR                  config_state;

    /** ESL tag ESL Attribute handles */
    BT_ESL_ATTR_HANDLES    esl_attr_handles;

} BT_ESL_TAG;

/** This structure contains info of the ESL group */
typedef struct _BT_ESL_GROUP
{
    /** List of ESL tags in the group */
    BT_ESL_TAG      * esl_tags;

#ifdef BT_ESL_AP_SEPERATE_KEY_PER_GROUP
    /**
     * ESL Response Key Material
     * This is the key which is used to encrypt/decrypt ESL response
     */
    BT_ESL_KEY_MATERIAL  rsp_key;

    /**
     * AP sync key Material
     * This is the key which is used to encrypt/decrypt the ESL requests
     */
    BT_ESL_KEY_MATERIAL  sync_key;

#endif /* BT_ESL_AP_SEPERATE_KEY_PER_GROUP */

} BT_ESL_GROUP;

/** This structure contains all the ESL group and its info */
typedef struct _BT_ESL_TAG_TABLE
{

    /** List of ESL groups in the table */
    BT_ESL_GROUP   * esl_groups;

    /** Number of groups in the table */
    UCHAR         no_of_groups;

    /** Number of ESL tags in a group */
    UCHAR         no_of_esl_tags_per_group;

#ifndef BT_ESL_AP_SEPERATE_KEY_PER_GROUP
    /**
     * ESL Response Key Material
     * This is the key which is used to encrypt/decrypt ESL response
     */
    BT_ESL_KEY_MATERIAL  rsp_key;

    /**
     * AP sync key Material
     * This is the key which is used to encrypt/decrypt the ESL requests
     */
    BT_ESL_KEY_MATERIAL  sync_key;

#endif /* BT_ESL_AP_SEPERATE_KEY_PER_GROUP */

} BT_ESL_TAG_TABLE;

/** This structure contains a ESL response */
typedef struct _BT_ESL_RSP
{
    /** Opcode of the response */
    UCHAR    response_opcode;

    /** Response data (length of the data is present in opcode) */
    UCHAR  * data;

} BT_ESL_RSP;

/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_CB
 * \{
 */

/**
 * \brief ESL Application Connection Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate connection event
 * occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param status
 *        Connection complete status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (* CONNECTED_IND_CB)
             (
                 BT_ESL_ADDR    * esl_addr,
                 UCHAR           status,
                 void           * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application Disconnection Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate Disconnection event
 * occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (* DISCONNECTED_IND_CB)
             (
                 BT_ESL_ADDR    * esl_addr,
                 void           * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application Discovery Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate Discovery event
 * occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param status
 *        Status of discovery.
 *
 * \param blob
 *        Blob of \ref BT_ESL_ATTR_HANDLES if any or NULL.
 */
typedef void (* DISCOVERED_IND_CB)
             (
                 BT_ESL_ADDR   esl_addr,
                 UINT16        status,
                 void        * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application Configuration Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate Configuration event
 * occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param error
 *        ATT error.
 *
 * \param result
 *        \ref BT_ESL_AP_SUCCESS on successful procedure completion, else
 * an Error Code.
 *
 * \param blob
 *        Blob of \ref BT_ESL_AP_CONFIGURE_INFO if any or NULL.
 */
typedef void (* CONFIGURED_IND_CB)
             (
                 BT_ESL_ADDR  * esl_addr,
                 UCHAR          error,
                 UINT16         result,
                 void         * blob
             )DECL_REENTRANT;


/**
 * \brief ESL Application Synchronized Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate Synchronized event
 * occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param status
 *        Status of synchronization.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (* SYNCHRONISED_IND_CB)
             (
                 BT_ESL_ADDR * esl_addr,
                 UINT16        status,
                 void        * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application response in connection Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate response received in
 * connection event occurred to the application.
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param esl_rsp
 *        ESL response received.
 *
 * \param no_of_esl_rsp
 *        Number of ESL response received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (* RESPONSE_IND_CB)
             (
                 BT_ESL_ADDR   * esl_addr,
                 BT_ESL_RSP    * esl_rsp,
                 UCHAR           no_of_esl_rsp,
                 void          * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application response in synchronization Event Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate response received in
 * synchronization event occurred to the application.
 *
 * \param group_id
 *        Group ID of the response received.
 *
 * \param response_slot
 *        Response slot of response received.
 *
 * \param esl_rsp
 *        ESL response received.
 *
 * \param no_of_esl_rsp
 *        Number of ESL response received.
 *
 * \param status
 *        status of the synchronization response.
 */
typedef void (* SYNCHRONISED_RESPONSE_IND_CB)
             (
                 UCHAR           group_id,
                 UCHAR           response_slot,
                 BT_ESL_RSP    * esl_rsp,
                 UCHAR           no_of_esl_rsp,
                 UINT16          status
             )DECL_REENTRANT;

/**
 * \brief ESL Application Device found Callback.
 *
 * \par Description
 * ESL core calls the registered callback to indicate Device found in
 * ADV reports occurred to the application.
 *
 * \param peer_add
 *        Reference to Peer address of the adv report.
 *
 * \param adv_data
 *        Advertisement data.
 *
 * \param adv_length
 *        Advertisement data length.
 */
typedef void (* ESL_DEVICE_FOUND_IND_CB)
             (
                 BT_ESL_BD_ADDR * peer_addr,
                 UCHAR          * adv_data,
                 UINT16           adv_length
             )DECL_REENTRANT;

/**
 * \brief ESL Application Info Indication Callback.
 *
 * \par Description
 * ESL core calls the registered callback to inform the upper layer
 * about the GATT-Read Response received from an ESL Tag for the identified ESL
 * Characteristic.
 *
 * | Info                   | Info Type                     | Data Type                |
 * |------------------------|-------------------------------|--------------------------|
 * | ESL Sensor Information | \ref BT_ESL_SENSOR_INFO_TYPE  | \ref BT_ESL_SENSOR_INFO  |
 * | ESL LED Information    | \ref BT_ESL_LED_INFO_TYPE     | \ref BT_ESL_LED_INFO     |
 * | ESL Image Information  | \ref BT_ESL_IMAGE_INFO_TYPE   | UCHAR                    |
 * | ESL Display Information| \ref BT_ESL_DISPLAY_INFO_TYPE | \ref BT_ESL_DISPLAY_INFO |
 *
 * \param esl_addr
 *        ESL address of the device.
 *
 * \param info_type
 *        Char info type.
 *
 * \param data
 *        data if any or NULL.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (* INFO_IND_CB)
             (
                 BT_ESL_ADDR   esl_addr,
                 UCHAR         info_type,
                 void        * data,
                 void        * blob
             )DECL_REENTRANT;
/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_Structures
 * \{
 */
/** This structure contains callbacks for the ESL AP Application */
typedef struct _BT_ESL_AP_CALLBACKS
{
    /**  ESL AP Connection indication callback */
    CONNECTED_IND_CB connected_ind_cb;

    /** ESL AP Disconnection indication callback */
    DISCONNECTED_IND_CB disconnected_ind_cb;

    /** ESL AP discovered indication callback */
    DISCOVERED_IND_CB discovered_ind_cb;

    /** ESL AP Configured indication callback */
    CONFIGURED_IND_CB configured_ind_cb;

    /** ESL AP Synchronized indication callback */
    SYNCHRONISED_IND_CB synchronised_ind_cb;

    /** ESL AP Response indication callback when in connected state*/
    RESPONSE_IND_CB response_ind_cb;

    /** ESL AP Response indication callback when in synchronized state */
    SYNCHRONISED_RESPONSE_IND_CB synchronised_response_ind_cb;

    /** ESL AP scan report indication callback when ESL device found advertising */
    ESL_DEVICE_FOUND_IND_CB esl_device_found_ind_cb;

    /** ESL AP read info indication callback */
    INFO_IND_CB info_ind_cb;

} BT_ESL_AP_CALLBACKS;

/** Configure info */
typedef struct _BT_ESL_AP_CONFIGURE_INFO
{
    /** BD address */
    BT_ESL_BD_ADDR bd_addr;

    /** State */
    UCHAR          state;

} BT_ESL_AP_CONFIGURE_INFO;

#endif /* BT_ESL_SUPPORT_AP_ROLE */

/** \} */


/**
 * \addtogroup EtherMind_ESL_TAG_CB
 * \{
 */
#ifdef BT_ESL_SUPPORT_TAG_ROLE
/**
 * \brief ESL Application Tag Connection Event Callback.
 *
 * \par Description
 * Called when LE connection is completed.
 *
 * \param status
 *        Connection status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_CONNECT_IND_CB)
             (
                 UCHAR status,
                 void  * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Application Tag Disconnection Event Callback.
 *
 * \par Description
 * Called when LE disconnection is completed.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_DISCONNECT_IND_CB)
             (
                 void * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Synchronization Complete Callback.
 *
 * \par Description
 * Called when ESL is synchronized with AP.
 *
 * \param status
 *        Synchronization status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_SYNCHRONIZED_IND_CB)
             (
                 UINT16 status,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Unsynchronized Callback.
 *
 * \par Description
 * Called when ESL loses synchronization with AP.
 * 1. When LE-ACL Link-Loss occurs
 * 2. When Periodic ADV Sync-Loss occurs
 *
 * \param status
 *        Reason for transitioning to Unsynchronized state.
 */
typedef void (*ESL_UNSYNCHRONIZED_IND_CB)
             (
                 UINT16 status
             )DECL_REENTRANT;

/**
 * \brief ESL Unassociated Callback.
 *
 * \par Description
 * Called when ESL is unassociated from AP.
 *
 * \param status
 *        Reason for transitioning to unassociated state.
 *
 * \note
 * - If this callback is triggered due to a **Factory Reset** command, the application can use
 *   \ref BT_esl_tag_post_factory_reset to complete the reset process.
 * - For an **Unassociate from AP** command or any other scenario leading to an unassociation,
 *   the application can use the generic reset API \ref BT_esl_tag_reset.
 */
typedef void (*ESL_UNASSOCIATED_IND_CB)
             (
                 UINT16 status
             )DECL_REENTRANT;


/**
 * \brief Callback for ESL Synchronization Termination.
 *
 * \details This function is invoked when ESL synchronization ends or is lost.
 *          The transition from the Synchronized state to the Update state can occur due to:
 *          - ESL Tag receiving an "Unassociate from AP" command (sync terminated)
 *          - ESL Tag not receiving periodic advertisements from the AP within the timeout period (sync lost)
 *
 * \param status
 *        Indicates the reason for synchronization termination.
 */

typedef void (*ESL_SYNC_TERMINATED_IND_CB)
             (
                 UINT16 status
             )DECL_REENTRANT;

/**
 * \brief ESL Read Info Request Callback.
 *
 * \par Description
 * Called when below ESL info characteristic is read.
 * > ESL Sensor Information
 * > ESL LED Information
 * > ESL Image Information
 * > ESL Display Information
 *
 * \param info_type
 *        Type of info requested.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_READ_ESL_INFO_IND_CB)
             (
                 UCHAR info_type,
                 void  * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Write ESL Address Callback.
 *
 * \par Description
 * Called when ESL address characteristic is written.
 *
 * \param status
 *        Write status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_WRITE_ESL_ADDR_IND_CB)
             (
                 UINT16 status,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Write AP Sync Key Callback.
 *
 * \par Description
 * Called when AP sync key material is written.
 *
 * \param status
 *        Write status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_WRITE_AP_SYNC_KEY_IND_CB)
             (
                 UINT16 status,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Write Response Key Callback.
 *
 * \par Description
 * Called when ESL response key material is written.
 *
 * \param status
 *        Write status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_WRITE_ESL_RSP_KEY_IND_CB)
             (
                 UINT16 status,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Write Absolute Time Callback.
 *
 * \par Description
 * Called when current absolute time is written.
 *
 * \param current_abs_time
 *        Absolute time value.
 *
 * \param status
 *        Write status.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_WRITE_ABS_TIME_IND_CB)
             (
                 UINT32 current_abs_time,
                 UINT16 status,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Control Point Configuration Callback.
 *
 * \par Description
 * Called when control point characteristic is configured.
 *
 * \param char_id
 *        Characteristic ID.
 *
 * \param cccd_value
 *        CCCD value.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_CONTROL_POINT_CONFIGURED_IND_CB)
             (
                 UCHAR  char_id,
                 UINT16 cccd_value,
                 void   * blob
             )DECL_REENTRANT;

/**
 * \brief ESL Configured Indication Callback.
 *
 * \par Description
 * Called on successful configuration of ESL tag.
 *      Configuration is complete when the following condition are met
 *      - ESL address is set
 *      - AP sync key is set
 *      - ESL response key is set
 *      - Current absolute time is set
 *      - Control Point is configured
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 */
typedef void (*ESL_CONFIGURED_IND_CB)
             (
                 void * blob
             )DECL_REENTRANT;

/**
 * \brief ESL LED Control Request Callback.
 *
 * \par Description
 * Called when LED control command is received.
 *
 * \param data
 *        Command data.
 *
 * \param datalen
 *        Length of command data.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 *  \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send LED state      | \ref BT_esl_tag_send_led_state         |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_LED_CONTROL_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 datalen,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Display Image Request Callback.
 *
 * \par Description
 * Called when Display Image or Display Timed Image command is received.
 *
 * \param data
 *        Command data.
 *
 * \param datalen
 *        Length of command data.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send display state  | \ref BT_esl_tag_send_display_state     |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */

typedef API_RESULT (*ESL_DISPLAY_IMAGE_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 datalen,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Read Sensor Data Request Callback.
 *
 * \par Description
 * Called when Read Sensor Data command is received.
 *
 * \param data
 *        Command data.
 *
 * \param data_length
 *        Length of command data.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send sensor value   | \ref BT_esl_tag_send_sensor_value      |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_READ_SENSOR_DATA_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_length,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Factory Reset Request Callback.
 *
 * \par Description
 * Called when Factory Reset command is received.
 *
 * \param command_source
 *        Source of the command (e.g., CP or sync packet).
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * When this callback is received, it is expected by the upper layer to
 * initiate disconnection. Upon disconnection, the ESL shall
 *  - become unassociated from any AP
 *  - revert to its original state before it was associated
 *    with an AP.
 *  - remove all bonding information with the AP;
 *    delete the values of the AP Sync Key Material,
 *    ESL Response Key Material, and
 *    ESL Address in internal storage;
 *  - and delete all stored commands
 *  - delete any stored image data that was written to the ESL
 *
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Factory reset command must be received in connection \ref BT_ESL_ECP,
 * If rejected/failure use \ref BT_esl_tag_send_esl_error_response to
 * send any error response.
 */
typedef API_RESULT (*ESL_FACTORY_RESET_CMD_CB)
                   (
                       UCHAR  command_source,
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Unassociate From AP Request Callback.
 *
 * \par Description
 * Called when Unassociate command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send basic state    | \ref BT_esl_tag_send_basic_state       |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_UNASSOCIATE_FROM_AP_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Service Reset Request Callback.
 *
 * \par Description
 * Called when Service Reset command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param command_source
 *        Source of the command.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send basic state    | \ref BT_esl_tag_send_basic_state       |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_SERVICE_RESET_CMD_CB)
                   (
                       UCHAR  command_source,
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Refresh Image Request Callback.
 *
 * \par Description
 * Called when Refresh Image command is received.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send display state  | \ref BT_esl_tag_send_display_state     |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_REFRESH_IMAGE_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Ping Request Callback.
 *
 * \par Description
 * Called when Ping command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response            | Reference API                          |
 * |--------------------------|-------------------|---------------------|----------------------------------------|
 * | Accepted                 | Non-broadcast     | Send basic state    | \ref BT_esl_tag_send_basic_state       |
 * | Rejected/Failure         | Non-broadcast     | Send error response | \ref BT_esl_tag_send_esl_error_response|
 * | Accepted/Rejected/Failure| Broadcast         | No response         | N/A                                    |
 */
typedef API_RESULT (*ESL_PING_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

/**
 * \brief ESL Update Complete Request Callback.
 *
 * \par Description
 * Called when Update Complete command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Update complete command will be received in connection,
 * If rejected/failure use \ref BT_esl_tag_send_esl_error_response to
 * send any error response.
 */
typedef API_RESULT(*ESL_UPDATE_COMPLETE_CMD_CB)
                  (
                      UCHAR  * data,
                      UINT16 data_len,
                      void   * blob
                  )DECL_REENTRANT;

/**
 * \brief ESL Unknown Command Callback.
 *
 * \par Description
 * Called when an unknown ESL command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * If unknown command callback is received in non broadcast packet type,
 * send error response using \ref BT_esl_tag_send_esl_error_response
 * with \ref BT_ESL_INVALID_OPCODE or any other appropriate upper layer error code.
 */
typedef API_RESULT (*ESL_UNKNOWN_CMD_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;

#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
/**
 * \brief ESL Vendor Specific Command Callback.
 *
 * \par Description
 * Called when a vendor-specific command is received.
 *
 * \param blob
 *        Blob of \ref BT_ESL_BD_ADDR if any or NULL.
 *
 * \param data
 *        Command data.
 *
 * \param data_len
 *        Length of command data.
 *
 * \return
 *  - \ref BT_ESL_API_SUCCESS - If command is accepted for processing
 *  - \ref BT_ESL_API_FAILURE - If command is rejected/ Factory reset is ongoing
 *
 * \note
 * The upper layer must ensure that any required response is sent before
 * returning from this callback.
 *
 * Below table describes the action to be taken at the upper layer based on the type of packet:
 *
 * | Command Status           | Packet Type       | Response                      | Reference API                                 |
 * |--------------------------|-------------------|-------------------------------|-----------------------------------------------|
 * | Accepted                 | Non-broadcast     | Send vendor specific response | \ref BT_esl_tag_send_vendor_specific_response |
 * | Rejected/Failure         | Non-broadcast     | Send error response           | \ref BT_esl_tag_send_esl_error_response       |
 * | Accepted/Rejected/Failure| Broadcast         | No response                   | N/A                                           |
 */
typedef API_RESULT (*ESL_VENDOR_SPECIFIC_COMMAND_CB)
                   (
                       UCHAR  * data,
                       UINT16 data_len,
                       void   * blob
                   )DECL_REENTRANT;
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */

/** \} */

/**
 * \addtogroup EtherMind_ESL_TAG_Structures
 * \{
 */

/**
 * Structure containing all ESL Tag-side application callbacks.
 * These callbacks are invoked by the ESL core to notify the application
 * about various events such as connection, synchronization, control commands, etc.
 */
typedef struct _BT_ESL_TAG_CALLBACKS
{
    /** Callback for LE connection complete event */
    ESL_CONNECT_IND_CB                     esl_connect_ind_cb;

    /** Callback for LE disconnection complete event */
    ESL_DISCONNECT_IND_CB                  esl_disconnect_ind_cb;

    /** Callback when ESL is synchronized with AP */
    ESL_SYNCHRONIZED_IND_CB                esl_synchronized_ind_cb;

    /** Callback when ESL becomes unsynchronized with AP */
    ESL_UNSYNCHRONIZED_IND_CB              unsynchronized_ind_cb;

    /** Callback when ESL is unassociated from AP */
    ESL_UNASSOCIATED_IND_CB                unassociated_ind_cb;

    /** Callback when synchronization is terminated */
    ESL_SYNC_TERMINATED_IND_CB             sync_terminated_ind_cb;

    /** Callback for incoming read request on ESL info characteristics */
    ESL_READ_ESL_INFO_IND_CB               els_read_esl_info_ind_cb;

    /** Callback for write request on ESL Address characteristic */
    ESL_WRITE_ESL_ADDR_IND_CB              els_write_esl_addr_ind_cb;

    /** Callback for write request on AP Sync Key Material characteristic */
    ESL_WRITE_AP_SYNC_KEY_IND_CB           els_write_ap_sync_key_ind_cb;

    /** Callback for write request on ESL Response Key Material characteristic */
    ESL_WRITE_ESL_RSP_KEY_IND_CB           esl_write_esl_rsp_key_ind_cb;

    /** Callback for write request on ESL Current Absolute Time characteristic */
    ESL_WRITE_ABS_TIME_IND_CB              esl_write_abs_time_ind_cb;

    /** Callback for ESL Configuration complete */
    ESL_CONFIGURED_IND_CB                  esl_configured_ind_cb;

    /** Callback when Control Point characteristic is configured */
    ESL_CONTROL_POINT_CONFIGURED_IND_CB    esl_control_point_configured_ind_cb;

    /** Callback for incoming LED Control or LED Timed Control command */
    ESL_LED_CONTROL_CMD_CB                 esl_led_control_cmd_cb;

    /** Callback for incoming Display Image or Display Timed Image command */
    ESL_DISPLAY_IMAGE_CMD_CB               esl_display_image_cmd_cb;

    /** Callback for incoming Read Sensor Data command */
    ESL_READ_SENSOR_DATA_CMD_CB            esl_read_sensor_data_cmd_cb;

    /** Callback for incoming Factory Reset command */
    ESL_FACTORY_RESET_CMD_CB               esl_factory_reset_cmd_cb;

    /** Callback for incoming Unassociate from AP command */
    ESL_UNASSOCIATE_FROM_AP_CMD_CB         esl_unassociate_from_ap_cmd_cb;

    /** Callback for incoming Service Reset command */
    ESL_SERVICE_RESET_CMD_CB               esl_service_reset_cmd_cb;

    /** Callback for incoming Refresh Image command */
    ESL_REFRESH_IMAGE_CMD_CB               esl_refresh_image_cmd_cb;

    /** Callback for incoming Ping command */
    ESL_PING_CMD_CB                        esl_ping_cmd_cb;

    /** Callback for incoming Update Complete command */
    ESL_UPDATE_COMPLETE_CMD_CB             esl_update_complete_cmd_cb;

    /** Callback for unknown ESL command */
    ESL_UNKNOWN_CMD_CB                     esl_unknown_cmd_cb;

#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
    /** Callback for vendor-specific ESL command */
    ESL_VENDOR_SPECIFIC_COMMAND_CB         esl_vendor_specific_command_cb;
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */

} BT_ESL_TAG_CALLBACKS;

/** ESL instance (To be given by the application) */
typedef struct _BT_ESL_INSTANCE
{
    /** Peer Bd Address */
    BT_ESL_BD_ADDR  peer_address;

    /** ESL Address */
    BT_ESL_ADDR     esl_address;

    /**
     * ESL Response Key Material
     * This is the key which is used to encrypt/decrypt ESL response
     */
    BT_ESL_KEY_MATERIAL  esl_rsp_key;

    /**
     * AP sync key Material
     * This is the key which is used to encrypt/decrypt the ESL requests
     */
    BT_ESL_KEY_MATERIAL ap_sync_key;

    /** ESL State Machine state */
    UCHAR               sm_state;

    /** Control CCCD */
    UINT16              cp_cccd_value;

    /** Below members to be filled by the application */
    /** ESL Basic state */
    UINT16              basic_state;

    /** ESL callbacks that the application register */
    BT_ESL_TAG_CALLBACKS  esl_cb;

#ifdef BT_ESL_SUPPORTS_DISPLAYS
    /** Max no of images that ESL supports */
    UCHAR              max_image_supported;

    /** ESL display information */
    BT_ESL_DISPLAY_INFO   display_info;
#endif /* BT_ESL_SUPPORTS_DISPLAYS */

#ifdef BT_ESL_SUPPORTS_LEDS
    /** ELS led information */
    BT_ESL_LED_INFO       led_info;
#endif /* BT_ESL_SUPPORTS_DISPLAYS */

#ifdef BT_ESL_SUPPORTS_SENSORS
    /** ESL sensor information */
    BT_ESL_SENSOR_INFO    sensor_info;
#endif /* BT_ESL_SUPPORTS_DISPLAYS */

} BT_ESL_INSTANCE;
#endif /* BT_ESL_SUPPORT_TAG_ROLE */

/**
 * This structure holds the parameters received in
 * HCI_LE_Periodic_Advertising_Report [v2] event
 * This event contains the ESL sync packet that is received
 * from the AP on the synced subevent
 *
 * Some of the parameter of this structure will be used
 * while sending LE Set Periodic Advertising Response Data command
 */
typedef struct _BT_ESL_PADV_REPORT_PARAMS
{
    /** The value of paEventCounter */
    UINT16         periodic_event_counter;

    /** The subevent Number */
    UCHAR          subevent;

    /** STatus of the Data received */
    UCHAR          data_status;

    /** Length of the Data field */
    UINT16         data_length;

    /** Data received from a Periodic Advertising packet */
    UCHAR          * data;

    /** Peer Address */
    BT_ESL_BD_ADDR peer_address;

    /** RSSI */
    INT8           rssi;

    /** TX Power */
    INT8           tx_power;

} BT_ESL_PADV_REPORT_PARAMS;


/** Structure to store the context of the subevent data to be set */
typedef struct _BT_ESL_SUBEVENT_DATA_PARAMS
{
    /** Subevent number */
    UCHAR subevent;

    /** subevent data */
    UCHAR* subevent_data;

    /** Subevent data length */
    UCHAR subevent_data_length;

} BT_ESL_SUBEVENT_DATA_PARAMS;

/** \} */

/* --------------------------------------------- Macros */
/**
 * \addtogroup EtherMind_ESL_Common_Macros
 * \{
 */
/**
 * \brief Macro to check basic state bit position enabled/disabled
 * \param [in] v Basic State Value
 * \param [in] p Bit Position to be checked
 * \return if Bit Position \a p is SET or RESET
 */
#define BT_ESL_CHECK_BASIC_STATE_BIT(v, p)                               \
        (BT_ESL_FALSE == ((v) & (1 << (p))) ? BT_ESL_FALSE : BT_ESL_TRUE)

/** Macro to check if the "Service Needed" bit is set in the ESL basic state */
#define BT_ESL_CHECK_SERVICE_NEEDED_BIT()                                \
        BT_ESL_CHECK_BASIC_STATE_BIT                                     \
        (                                                                \
            BT_esl_tag_get_basic_state(),                                \
            BT_ESL_BASIC_STATE_SERV_NEEDED_BIT                           \
        )

/** Macro to check if the "Synchronized" bit is set in the ESL basic state */
#define BT_ESL_CHECK_SYNCHRONISED_BIT()                                  \
        BT_ESL_CHECK_BASIC_STATE_BIT                                     \
        (                                                                \
            BT_esl_tag_get_basic_state(),                                \
            BT_ESL_BASIC_STATE_SYNCHRONISED_BIT                          \
        )

/** Macro to check if the "Active LED" bit is set in the ESL basic state */
#define BT_ESL_CHECK_ACTIVE_LED_BIT()                                    \
        BT_ESL_CHECK_BASIC_STATE_BIT                                     \
        (                                                                \
            BT_esl_tag_get_basic_state(),                                \
            BT_ESL_BASIC_STATE_ACTIVE_LED_BIT                            \
        )

/** Macro to check if the "Pending LED Update" bit is set in the ESL basic state */
#define BT_ESL_CHECK_PENDING_LED_UPDATE_BIT()                            \
        BT_ESL_CHECK_BASIC_STATE_BIT                                     \
        (                                                                \
            BT_esl_tag_get_basic_state(),                                \
            BT_ESL_BASIC_STATE_PNDG_LED_UPDT_BIT                         \
        )

/** Macro to check if the "Pending Display Update" bit is set in the ESL basic state */
#define BT_ESL_CHECK_PENDING_DISPLAY_UPDATE_BIT()                        \
        BT_ESL_CHECK_BASIC_STATE_BIT                                     \
        (                                                                \
            BT_esl_tag_get_basic_state(),                                \
            BT_ESL_BASIC_STATE_PNDG_DISP_UPDT_BIT                        \
        )

/**
 * \brief Macro to get length from opcode
 *
 * \par Description
 * Adding 2 to get (length from TLV + opcode(1 byte))
 * For Read Sensor Data: opcode is 0x10
 * total parameter for this opcode is 2 bytes.
 * parameter = (length + 1), 2 = (1 + 1). Hence length = 1,
 * control point write for this opcode will be
 * opcode + 2 bytes of parameter.= Total 3 bytes of data
 * Hence to get the total length added 2.
 * (length from TLV + opcode(1 byte)) = 1 + 2 = 3
 *
 * \param [in] x Opcode value
 * \return Length of the control point command/response
 */
#define BT_ESL_GET_CP_LEN(x) (UCHAR)(((x & 0xF0U) >> 4U) + 2U)

/**
 * \brief Macro to get control point command/response opcode base tag
 *
 * \par Description
 * Macro to get base tag used for sensor value response and
 * vendor specific command/response.
 *
 * \param [in] x Opcode value
 * \return Base tag of the control point command/response
 */
#define BT_ESL_GET_CP_BASE_TAG(x) (UCHAR)((x & 0x0FU))

/**
 * \brief Macro to get GRP ID from ESL Address
 * \param [in] x ESL Address \ref BT_ESL_ADDR
 * \return GRP ID corresponding to \ref BT_ESL_ADDR
 */
#define BT_ESL_GET_GRP_ID(x) (UCHAR)(((x) >> 8U) & 0xFFU)

/**
 * \brief Macro to get ESL ID from ESL Address
 * \param [in] x ESL Address \ref BT_ESL_ADDR
 * \return ESL ID corresponding to \ref BT_ESL_ADDR
 */
#define BT_ESL_GET_ESL_ID(x) (UCHAR)(x)

/**
 * \brief Check display info length
 *
 * \par Description
 * Macro to check if the display info length is valid.
 * The length should be a multiple of 5.
 *
 * \param [in] len Length of the display info
 * \return BT_ESL_TRUE if valid, BT_ESL_FALSE otherwise
 */
#define BT_ESL_VALIDATE_DISPLAY_INFO_LENGTH(len) \
        ((len) % 5U == 0U ? BT_ESL_TRUE : BT_ESL_FALSE)

/**
 * \brief Check Sensor info length
 *
 * \par Description
 * Macro to check if the sensor info length is valid.
 * The length should be at least 3 or 5.
 *
 * \param [in] len Length of the sensor info
 * \return BT_ESL_TRUE if valid, BT_ESL_FALSE otherwise
 */
#define BT_ESL_VALIDATE_SENSOR_INFO_LENGTH(len) \
        (((len) >= 3 || (len) >= 5) ? BT_ESL_TRUE : BT_ESL_FALSE)

/**
 * \brief Initialize ESL Address
 *
 * \par Description
 * This macro is used to initialize the ESL Address structure.
 *
 * \param [in] x Pointer to the ESL Address structure
 */
#define BT_ESL_INIT_ESL_ADDRESS(x)                                           \
        {                                                                    \
            (x)->group_id = BT_ESL_GROUP_ID_INIT_VAL;                        \
            (x)->esl_id = BT_ESL_ID_INIT_VAL;                                \
        }

/**
 * \brief Initialize Key material
 *
 * \par Description
 * This macro is used to initialize the key material structure.
 *
 * \param [in] x Pointer to the key material structure
 */
#define BT_ESL_INIT_KEY_MATERIAL(x)                                          \
        {                                                                    \
            BT_ESL_mem_set((x)->session_key, 0x00U, BT_ESL_SESSION_KEY_LEN); \
            BT_ESL_mem_set((x)->iv, 0x00U, BT_ESL_IV_LEN);                   \
        }

/**
 * \brief Initialize Display Info
 *
 * \par Description
 * This macro is used to initialize the display information structure.
 *
 * \param [in] x Pointer to the display information structure
 */
#define BT_ESL_INIT_DISPLAY_INFO(x)                                          \
        {                                                                    \
            BT_ESL_mem_set(((x)->esl_display), 0x00U,                        \
            sizeof(BT_ESL_DISPLAY)* BT_ESL_MAX_DISPLAY_SUPPORTED);           \
            (x)->no_of_displays = 0U;                                        \
        }

/**
 * \brief Initialize LED Info
 *
 * \par Description
 * This macro is used to initialize the LED information structure.
 *
 * \param [in] x Pointer to the LED information structure
 */
#define BT_ESL_INIT_LED_INFO(x)                                              \
        {                                                                    \
            BT_ESL_mem_set(((x)->esl_led), 0x00U,                            \
            sizeof(BT_ESL_LED)* BT_ESL_MAX_LED_SUPPORTED);                   \
            (x)->no_of_leds = 0U;                                            \
        }

/**
 * \brief Initialize Sensor Info
 *
 * \par Description
 * This macro is used to initialize the sensor information structure.
 *
 * \param [in] x Pointer to the sensor information structure
 */
#define BT_ESL_INIT_SENSOR_INFO(x)                                           \
        {                                                                    \
            BT_ESL_mem_set(((x)->esl_sensors), 0x00U,                        \
            sizeof(BT_ESL_SENSOR)* BT_ESL_MAX_SENSOR_SUPPORTED);             \
            (x)->no_of_sensors = 0U;                                         \
        }

/** \} */

/**
 * \addtogroup EtherMind_ESL_AP_Macros
 * \{
 */
#ifdef BT_ESL_SUPPORT_AP_ROLE
/**
 * \brief Macro to initialize ESL attribute handles
 *
 * \par Description
 * This macro initializes the ESL attribute handles to a predefined value.
 *
 * \param [in] x Pointer to the ESL attribute handles structure
 */
#define BT_ESL_AP_INIT_ESL_ATTR_HANDLES(x)                                   \
        {                                                                    \
            (x)->address_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;               \
            (x)->ap_sync_key_material_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;  \
            (x)->response_key_material_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL; \
            (x)->current_absolute_time_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL; \
            (x)->display_info_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;          \
            (x)->image_info_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;            \
            (x)->sensor_info_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;           \
            (x)->led_info_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;              \
            (x)->cp_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;                    \
            (x)->cp_cccd_hdl = BT_ESL_AP_ATTR_HANDLE_INIT_VAL;               \
        }

/**
 * \brief Macro to initialize ESL TAG structure
 *
 * \par Description
 * This macro initializes the ESL TAG structure to a predefined value.
 *
 * \param [in] x Pointer to the ESL TAG structure
 */
#define BT_ESL_AP_INIT_ESL_TAG(x)                                            \
        {                                                                    \
            BT_ESL_INIT_ESL_ADDRESS(&((x)->esl_address));                    \
            BT_ESL_AP_INIT_ESL_ATTR_HANDLES(&((x)->esl_attr_handles));       \
            BT_ESL_INIT_BD_ADDR(&((x)->esl_bd_addr));                        \
            BT_ESL_AP_SET_ESL_TAG_STATE((x), BT_ESL_AP_UNASSOCIATE);         \
            (x)->config_state = BT_ESL_AP_CONFIGURATION_IDLE_STATE;          \
        }

/**
 * \brief Macro to get the State of an ESL Tag entry maintained by the AP.
 *
 * \param [in] x Pointer to the ESL TAG structure (\ref BT_ESL_TAG *)
 * \return Current \c sm_state value of the ESL Tag entry
 */
#define BT_ESL_AP_GET_ESL_TAG_STATE(x)                                       \
        ((x)->sm_state)

/**
 * \brief Macro to set the State of an ESL Tag entry maintained by the AP.
 *
 * \par Description
 * This macro updates the \c sm_state field of the given \ref BT_ESL_TAG
 * entry (within the AP's tag table) to the supplied state value.
 *
 * \param [in] x Pointer to the ESL TAG structure (\ref BT_ESL_TAG *)
 * \param [in] s New state value (one of the AP States, e.g. \ref BT_ESL_AP_UNASSOCIATE,
 *               \ref BT_ESL_AP_CONNECTED, \ref BT_ESL_AP_CONFIGURING, etc.)
 */
#define BT_ESL_AP_SET_ESL_TAG_STATE(x, s)                                    \
        BT_ESL_AP_GET_ESL_TAG_STATE((x)) = (s);

#endif /* BT_ESL_SUPPORT_AP_ROLE */

/** \} */

/**
 * \addtogroup EtherMind_ESL_TAG_Macros
 * \{
 */
#ifdef BT_ESL_SUPPORT_TAG_ROLE

/**
 * \brief Macro to SET basic state bit position
 * \param [in] v Basic State Value
 * \param [in] p Bit Position to be SET
 */
#define BT_ESL_SET_BASIC_STATE_BIT(v, p) \
        ((v) |= (1 << (p)))

/**
 * \brief Macro to RESET basic state bit position
 * \param [in] v Basic State Value
 * \param [in] p Bit Position to be RESET
 */
#define BT_ESL_RESET_BASIC_STATE_BIT(v, p) \
        ((v) &= ~(1 << (p)))

/**
 * \brief Macro to update basic state
 *
 * \par Description
 * These macros updates the basic state of the ESL tag by setting or clearing
 * the specified bit.
 * Internally, it sets:
 * Bit position to be updated (in this case, the "Service Needed" bit)
 * Value to set (BT_ESL_TRUE to set the bit)
 */
/** Macro to set service needed bit in basic state */
#define BT_ESL_SET_SERVICE_NEEDED_BIT()                               \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_SERV_NEEDED_BIT,                       \
            BT_ESL_TRUE                                               \
        )

/** Macro to set Synchronized bit in basic state */
#define BT_ESL_SET_SYNCHRONISED_BIT()                                 \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_SYNCHRONISED_BIT,                      \
            BT_ESL_TRUE                                               \
        )

/** Macro to set Active LED bit in basic state */
#define BT_ESL_SET_ACTIVE_LED_BIT()                                   \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_ACTIVE_LED_BIT,                        \
            BT_ESL_TRUE                                               \
        )

/** Macro to set Pending LED update bit in basic state */
#define BT_ESL_SET_PENDING_LED_UPDATE_BIT()                           \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_PNDG_LED_UPDT_BIT,                     \
            BT_ESL_TRUE                                               \
        )

/** Macro to set Pending display update bit in basic state */
#define BT_ESL_SET_PENDING_DISPLAY_UPDATE_BIT()                       \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_PNDG_DISP_UPDT_BIT,                    \
            BT_ESL_TRUE                                               \
        )

/** Macro to reset service needed bit in basic state */
#define BT_ESL_RESET_SERVICE_NEEDED_BIT()                             \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_SERV_NEEDED_BIT,                       \
            BT_ESL_FALSE                                              \
        )

/** Macro to reset Synchronized bit in basic state */
#define BT_ESL_RESET_SET_SYNCHRONISED_BIT()                           \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_SYNCHRONISED_BIT,                      \
            BT_ESL_FALSE                                              \
        )

/** Macro to reset Active LED bit in basic state */
#define BT_ESL_RESET_ACTIVE_LED_BIT()                                 \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_ACTIVE_LED_BIT,                        \
            BT_ESL_FALSE                                              \
        )

/** Macro to reset Pending LED update bit in basic state */
#define BT_ESL_RESET_PENDING_LED_UPDATE_BIT()                         \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_PNDG_LED_UPDT_BIT,                     \
            BT_ESL_FALSE                                              \
        )

/** Macro to reset Pending display update bit in basic state */
#define BT_ESL_RESET_PENDING_DISPLAY_UPDATE_BIT()                     \
        BT_esl_tag_update_basic_state                                 \
        (                                                             \
            BT_ESL_BASIC_STATE_PNDG_DISP_UPDT_BIT,                    \
            BT_ESL_FALSE                                              \
        )

/**
 * \brief Macro to set sensor value response opcode
 *
 * \par Description
 * This macro sets the sensor value response opcode by combining
 * the length with the predefined sensor value constant.
 *
 * \param [in] l Length to be combined with the sensor value constant
 *
 * \return Sensor data opcode
 */
#define BT_ESL_SET_SENSOR_VALUE_OP(l)\
        ( ((l) << (4)) | (BT_ESL_SENSOR_VALUE))

/**
 * \brief Macro to set Vendor Specific response opcode
 *
 * \par Description
 * This macro sets the Vendor Specific response opcode by combining
 * the length with the predefined Vendor Specific response constant.
 *
 * \param [in] l Length to be combined with the Vendor Specific response constant
 *
 * \return Vendor Specific response opcode
 */
#define BT_ESL_SET_VENDOR_SPECIFIC_RSP_OP(l)\
        ( ((l) << (4)) | (BT_ESL_VENDOR_SPECIFIC_RESPONSE_BASE))

/**
 * \brief Macro to check flashing pattern bits
 *
 * \par Description
 * This macro checks if the specified bit position in the flashing pattern
 * is set or not.
 *
 * \param [in] v Flashing pattern value
 * \param [in] p Bit position to check
 *
 * \return BT_ESL_TRUE if the bit is set, BT_ESL_FALSE otherwise
 */
#define BT_ESL_CHECK_FLASHING_PATTERN_BIT(v,p) \
        (((v) & (1 << (p))) == (1 << (p)))? BT_ESL_TRUE : BT_ESL_FALSE

/**
 * \brief Macro to initialize ESL instance
 *
 * \par Description
 * This macro initializes the ESL instance by setting up the necessary
 * parameters and states.
 *
 * \param [in] x Pointer to the ESL instance structure
 */
#define BT_ESL_TAG_INIT_ESL_INST(x)                                          \
{                                                                            \
    BT_ESL_INIT_ESL_ADDRESS(&((x)->esl_address));                            \
    BT_ESL_INIT_BD_ADDR(&((x)->peer_address));                               \
    BT_ESL_INIT_KEY_MATERIAL(&((x)->ap_sync_key));                           \
    BT_ESL_INIT_KEY_MATERIAL(&((x)->esl_rsp_key));                           \
    (x)->sm_state = BT_ESL_UNASSOCIATE_STATE;                                \
    (x)->basic_state = BT_ESL_TAG_BASIC_STATE_INIT_VAL;                      \
    (x)->cp_cccd_value = BT_ESL_CCCD_DISABLE_NOTIFY;                         \
}
#endif /* BT_ESL_SUPPORT_TAG_ROLE */

/** \} */

/* --------------------------------------------- Internal Functions */

/* --------------------------------------------- API Declarations */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup EtherMind_ESL_AP_api_defs
 * \{
 */
#ifdef BT_ESL_SUPPORT_AP_ROLE

/**
 * \name ESL Access Point Interfaces to be invoked by Application Layer
 * \{
 */

/**
 *  \brief To initialize ESL AP Role
 *
 *  \par Description
 *  API to initialize the ESL Access Point role. The upper-layer registers
 *  the required callbacks \ref BT_ESL_AP_CALLBACKS through this interface.
 *  It also needs to create the required space in the list of ESL Tags
 *  \ref BT_ESL_TAG_TABLE that the access point needs to maintain
 *  and operate on.
 *
 *  \param [in] esl_ap_cb
 *         ESL Access Point Callback Structure
 *  \param [in] esl_tag_table
 *         Place holder for the ESL Tags that the AP needs to maintain.
 *
 *  \return BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_init
           (
               /* IN */ BT_ESL_AP_CALLBACKS * esl_ap_cb,
               /* IN */ BT_ESL_TAG_TABLE    * esl_tag_table
           );

/**
 *  \brief To start/stop scan for ESL Tags/Devices that are advertising.
 *
 *  \par Description
 *  API to Enable/Disable BLE Scanning at the Access Point to look/search or
 *  to stop looking/searching for ESL Tags/Devices
 *
 *  \param [in] flag Scan Enable or Scan Disable
 *
 *  \return BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_scan_esl_device (/* IN */ UCHAR flag);

/**
 *  \brief API to add ESL tag to the tag table
 *
 *  \par Description
 *  API to add ESL tag to the tag table
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] peer_addr Reference to Peer address \ref BT_ESL_BD_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_add_esl_tag
           (
               /* IN */ BT_ESL_ADDR    * esl_addr,
               /* IN */ BT_ESL_BD_ADDR * peer_addr
           );

/**
 *  \brief API to remove ESL tag from tag table
 *
 *  \par Description
 *  API to remove ESL tag from tag table
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_remove_esl_tag (/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to connect to ESL tag
 *
 *  \par Description
 *  API to connect to ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_connect_esl(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to disconnect an ESL tag
 *
 *  \par Description
 *  API to disconnect an ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_disconnect_esl(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to configure connected ESL tag
 *
 *  \par Description
 *  API to configure connected ESL tag
 *  This takes care of discovery, configure NTF of CP, write ESL address,
 *  write response key and sync key and write current absolute time.
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_config(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to discover ESL service characteristics of a ESL tag
 *
 *  \par Description
 *  API to discover ESL service characteristics of a ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_discover_esl_service(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to get the current absolute time from ESL AP core
 *
 *  \par Description
 *  API to get the current absolute time from ESL AP core
 *
 *  \return Current absolute time or invalid value if failure.
 */
UINT32 BT_esl_ap_get_current_abs_time(void);

/**
 *  \brief API to sync with ESL tag
 *
 *  \par Description
 *  API to sync with ESL tag. This takes care of sending update complete
 *  command and initiate past procedure
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_sync_with_esl(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to get ESL display information from ESL tag
 *
 *  \par Description
 *  API to get ESL display information from ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_get_display_information(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to get LED information from ESL tag
 *
 *  \par Description
 *  API to get LED information from ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_get_led_information(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to get sensor information from ESL tag
 *
 *  \par Description
 *  API to get sensor information from ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_get_sensor_information(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to get image information from ESL tag
 *
 *  \par Description
 *  API to get image information from ESL tag
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_get_image_information(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to send ping command
 *
 *  \par Description
 *  API to send ping command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together.
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_ping
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR         multiple_commands_flag
           );

/**
 *  \brief API to send Un-associate command
 *
 *  \par Description
 *  API to send Un-associate command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together.
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_unassociate
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send service reset command
 *
 *  \par Description
 *  API to send service reset command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together.
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_service_reset
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send factory reset command
 *
 *  \par Description
 *  API to send factory reset command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_factory_reset
           (
               /* IN */ BT_ESL_ADDR * esl_addr
           );

/**
 *  \brief API to send read sensor data command
 *
 *  \par Description
 *  API to send read sensor data command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] sensor_index Index of the Sensor that is to be addressed
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together.
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_read_sensor_data
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       sensor_index,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send refresh display command
 *
 *  \par Description
 *  API to send refresh display command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] display_index Index of the Display that is to be addressed
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_refresh_display
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       display_index,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send display image command
 *
 *  \par Description
 *  API to send display image command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] display_index Index of the Display that is to be addressed
 *  \param [in] image_index Index of the Image
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_display_image
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       display_index,
               /* IN */ UCHAR       image_index,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send display timed image command
 *
 *  \par Description
 *  API to send display timed image command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] display_index Index of the Display that is to be addressed
 *  \param [in] image_index Index of the Image
 *  \param [in] absolute_time Absolute Time at which Image is to be Displayed
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_display_timed_image
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       display_index,
               /* IN */ UCHAR       image_index,
               /* IN */ UINT32      absolute_time,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send LED control command
 *
 *  \par Description
 *  API to send LED control command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] led_index Index of LED
 *  \param [in] color_brightness Color & Brightness Values
 *  \param [in] flashing_pattern Reference to LED Flashing Pattern
 *  \param [in] repeat_type LED Flashing repeat pattern
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_led_control
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       led_index,
               /* IN */ UCHAR       color_brightness,
               /* IN */ UCHAR       * flashing_pattern,
               /* IN */ UINT16      repeat_type,
               /* IN */ UCHAR       multiple_commands_flag
           );

/**
 *  \brief API to send LED timed control command
 *
 *  \par Description
 *  API to send LED timed control command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] led_index Index of LED
 *  \param [in] color_brightness Color & Brightness Values
 *  \param [in] flashing_pattern Reference to LED Flashing Pattern
 *  \param [in] repeat_type LED Flashing repeat pattern
 *  \param [in] absolute_time Absolute Time at which LED Flashing is to
 *  be Started
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_led_timed_control
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       led_index,
               /* IN */ UCHAR       color_brightness,
               /* IN */ UCHAR       * flashing_pattern,
               /* IN */ UINT16      repeat_type,
               /* IN */ UINT32      absolute_time,
               /* IN */ UCHAR       multiple_commands_flag
           );

#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
/**
 *  \brief API to send vendor specific command
 *
 *  \par Description
 *  API to send vendor specific command
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [in] opcode Vendor Specific Command Opcode
 *  \param [in] data Vendor Specific Command Data
 *  \param [in] data_len Vendor Specific Command Data Length
 *  \param [in] multiple_commands_flag Flag to set if Multiple ESL Commands
 *  are to be stitched together
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_vendor_specific_command
           (
               /* IN */ BT_ESL_ADDR * esl_addr,
               /* IN */ UCHAR       opcode,
               /* IN */ UCHAR       * data,
               /* IN */ UINT16      data_len,
               /* IN */ UCHAR       multiple_commands_flag
           );
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */

/**
 *  \brief API to send commands in the ESL AP core command buffer
 *
 *  \par Description
 *  API to send commands in the ESL AP core command buffer
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_send_esl_command(void);

/**
 *  \brief API to clear commands in the ESL AP core command buffer
 *
 *  \par Description
 *  API to clear commands in the ESL AP core command buffer
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_clear_esl_command_buf(void);

/**
 *  \brief API to Un-associate a ESL Tag
 *
 *  \par Description
 *  API to reset the ESL tag after the command unassociated
 *  has been sent and disconnected
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_post_unassociate(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to Factory Reset a ESL Tag
 *
 *  \par Description
 *  API to reset the ESL tag after the command factory reset
 *  has been sent and disconnected
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_post_factory_reset (/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief API to reset the ESL AP internally
 *
 *  \par Description
 *  API to Locally initiate reset of the ESL AP
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_reset(void);

/**
 *  \brief API to reset the ESL Tag Internally/Locally
 *
 *  \par Description
 *  API to reset the ESL AP internally/Locally.
 *  To be used in situations where Reset command need to be sent to the ESL Tag
 *  over the Air. For scenarios where ESL Tag is not responding or is found
 *  to be defective etc.
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_reset_esl_tag(/* IN */ BT_ESL_ADDR * esl_addr);

/**
 *  \brief Get ESL tag state
 *
 *  \par Description
 *  API to get the current state of the ESL tag.
 *
 *  \param [in] esl_addr Reference to ESL Address Structure \ref BT_ESL_ADDR
 *  \param [out] state Reference to variable to hold the ESL tag state
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_ap_get_esl_tag_state
           (
                /* IN */  BT_ESL_ADDR * esl_addr,
                /* OUT */ UCHAR       * state
           );

/**
 *  \brief Conditionally set ESL tag state (only if currently in expected state)
 *
 *  \par Description
 *  API to update the current state of an ESL tag maintained
 *  in the AP's tag table to \a new_state, but only when the tag's existing
 *  state matches \a expected_state. Tags whose current state does not match
 *  \a expected_state are left untouched.
 *
 *  Typical use-case: when the periodic advertising train is stopped, the
 *  application/platform layer needs to demote only those tags that are
 *  currently in \ref BT_ESL_AP_SYNCHRONIZED state to
 *  \ref BT_ESL_AP_UNSYNCHRONIZED, without disturbing tags that are in
 *  other states (e.g. \ref BT_ESL_AP_CONNECTED, \ref BT_ESL_AP_CONFIGURING,
 *  \ref BT_ESL_AP_UNASSOCIATE).
 *
 *  \param [in] esl_addr      Reference to ESL Address Structure \ref BT_ESL_ADDR.
 *                            If \c NULL is provided, every ESL tag entry in
 *                            every group of the AP's tag table is evaluated
 *                            (broadcast conditional set).
 *  \param [in] expected_state State value the tag must currently be in for
 *                             the update to occur. Must be one of the AP
 *                             ESL Tag States (e.g. \ref BT_ESL_AP_SYNCHRONIZED).
 *  \param [in] new_state     New state value to be assigned to qualifying
 *                            ESL tag(s). Must be one of the AP ESL Tag States.
 *
 *  \return \ref BT_ESL_API_SUCCESS if the call completed successfully (note
 *          that success is returned even if no tag matched
 *          \a expected_state), or an error code indicating reason for
 *          failure (invalid parameters, tag table not initialised, etc.).
 *
 *  \note This API directly updates the internal state of the ESL tag entry
 *        in the AP tag table without any over-the-air procedure. It is
 *        intended for recovery / housekeeping scenarios.
 */
API_RESULT BT_esl_ap_set_esl_tag_state
           (
                /* IN */ BT_ESL_ADDR * esl_addr,
                /* IN */ UCHAR         expected_state,
                /* IN */ UCHAR         new_state
           );

/** \} */

/**
 * \name ESL Access Point Interfaces to be invoked by Bluetooth Abstraction Layer
 * \{
 */

/**
 * \brief API to handle Adv report event
 *
 * \par Description
 * This API is called when an advertisement report is received.
 *
 * \param [in] bd_addr Reference to the Bluetooth address of the device.
 * \param [in] adv_data Reference to the advertisement data.
 * \param [in] adv_data_length Length of the advertisement data.
 */
void BT_esl_ap_adv_report_handler
     (
         /* IN */ BT_ESL_BD_ADDR * bd_addr,
         /* IN */ UCHAR          * adv_data,
         /* IN */ UINT16           adv_data_length
     );


/**
 * \brief API to handle connection event
 *
 * \par Description
 * This API is called when a connection event occurs.
 *
 * \param [in] status Status of the connection event.
 * \param [in] peer_bd_addr Reference to the Bluetooth address of the peer device.
 *
 * \return BT_ESL_API_SUCCESS or an error code indicating reason for failure.
 */
API_RESULT BT_esl_ap_connection_handler
           (
               /* IN */ UCHAR            status,
               /* IN */ BT_ESL_BD_ADDR * peer_bd_addr
           );

/**
 * \brief API to handle disconnection event
 *
 * \par Description
 * This API is called when a disconnection event occurs.
 *
 * \param [in] peer_bd_addr Reference to the Bluetooth address of the peer device.
 * \param [in] reason Reason for disconnection.
 *
 * \return BT_ESL_API_SUCCESS or an error code indicating reason for failure.
 */
API_RESULT BT_esl_ap_disconnection_handler
           (
                /* IN */ BT_ESL_BD_ADDR * peer_bd_addr,
                /* IN */ UCHAR            reason
           );
/**
 * \brief API to handle discovery complete event
 *
 * \par Description
 * This API is called when the discovery of ESL attributes is complete.
 *
 * \param [in] bd_addr Pointer to the Bluetooth address of the device.
 * \param [in] esl_attr_handles Pointer to the ESL attribute handles structure.
 *
 * \return BT_ESL_API_SUCCESS or an error code indicating reason for failure.
 */
API_RESULT BT_esl_ap_discovery_complete_handler
           (
               /* IN */ BT_ESL_BD_ADDR      * bd_addr,
               /* IN */ BT_ESL_ATTR_HANDLES * esl_attr_handles
           );

/**
 * \brief API to handle write response
 *
 * \par Description
 * This function is called when the GATT write operation completes.
 *
 * \param [in] bd_addr Pointer to the Bluetooth address of the device.
 * \param [in] attr_handle The handle of the characteristic that was written.
 * \param [in] error ATT Error code.
 *
 * \return BT_ESL_API_SUCCESS if the response is handled successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_ap_write_response_handler
           (
                /* IN */ BT_ESL_BD_ADDR * bd_addr,
                /* IN */ UINT16           attr_handle,
                /* IN */ UCHAR            error
           );

/**
 * \brief Handles the response of a GATT read operation.
 *
 * \par Description
 * This function is called when the GATT read operation completes.
 *
 * \param bd_addr Reference to the Bluetooth address of the device.
 * \param attr_handle The handle of the characteristic that was read.
 * \param error ATT Error code.
 * \param data Reference to the data read from the characteristic (NULL if error occurred).
 * \param data_length Length of the data read (0 if error occurred).
 *
 * \return BT_ESL_API_SUCCESS if the response is handled successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_ap_read_response_handler
           (
                /* IN */ BT_ESL_BD_ADDR * bd_addr,
                /* IN */ UINT16           attr_handle,
                /* IN */ UCHAR            error,
                /* IN */ UCHAR          * data,
                /* IN */ UINT16           data_length
           );

/**
 * \brief API to handle Notification
 *
 * \par Description
 * This function is called when a notification is received.
 *
 * \param [in] bd_addr Reference to the Bluetooth address of the device.
 * \param [in] attr_handle The handle of the characteristic that sent the notification.
 * \param [in] data Reference to the data contained in the notification.
 * \param [in] data_length Length of the data contained in the notification.
 *
 * \return BT_ESL_API_SUCCESS if the notification is handled successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_ap_notification_handler
           (
                /* IN */ BT_ESL_BD_ADDR * bd_addr,
                /* IN */ UINT16           attr_handle,
                /* IN */ UCHAR          * data,
                /* IN */ UINT16           data_length
           );

/**
 * \brief Subevent data request handler
 *
 * \par Description
 * This function is called when a subevent data request is received.
 *
 * \param [in] subevent_start The starting subevent index.
 * \param [in] subevent_count The number of subevents requested.
 *
 * \return BT_ESL_API_SUCCESS if the request is handled successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_ap_subevent_data_request_handler
           (
                /* IN */ UCHAR subevent_start,
                /* IN */ UCHAR subevent_count
           );

/**
 * \brief periodic advertisement response handler
 *
 * \par Description
 * This function is called when a periodic advertisement response is received.
 *
 * \param [in] subevent The subevent index.
 * \param [in] response_slot The response slot index.
 * \param [in] data_status The status of the data.
 * \param [in] response_data Pointer to the response data received.
 * \param [in] response_data_len Length of the response data in bytes.
 *
 * \return BT_ESL_API_SUCCESS if the response is handled successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_ap_response_event_handler
           (
                /* IN */ UCHAR   subevent,
                /* IN */ UCHAR   response_slot,
                /* IN */ UCHAR   data_status,
                /* IN */ UCHAR * response_data,
                /* IN */ UINT16  response_data_len
           );

/** \} */

#endif /* BT_ESL_SUPPORT_AP_ROLE */

/** \} */

/**
 * \addtogroup EtherMind_ESL_TAG_api_defs
 * \{
 */
#ifdef BT_ESL_SUPPORT_TAG_ROLE

/**
 * \name ESL Tag Interfaces to be invoked by Application Layer
 * \{
 */

/**
 *  \brief API to initialize the ESL tag core
 *
 *  \par Description
 *  API to initialize the ESL tag core
 *
 *  \param [in] esl_inst Reference to the ESL Instance Structure \ref BT_ESL_INSTANCE
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_init(/* IN */ BT_ESL_INSTANCE * esl_inst);

/**
 *  \brief API to register callbacks for ESL tag events
 *
 *  \par Description
 *  API to register callbacks for ESL tag events
 *
 *  \param [in] esl_tag_cb Reference to the ESL Tag Callbacks Structure \ref BT_ESL_TAG_CALLBACKS
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_register_cb(/* IN */ BT_ESL_TAG_CALLBACKS * esl_tag_cb);

/**
 *  \brief API to initiate disconnect to ESL AP
 *
 *  \par Description
 *  API to initiate disconnect to ESL AP
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_disconnect(void);

/**
 *  \brief API to send basic state response
 *
 *  \par Description
 *  API to send basic state response
 *
 *  \param [in] basic_state Basic State's Value
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_basic_state
           (
               /* IN */ UINT16 basic_state
           );

/**
 *  \brief API to send error response
 *
 *  \par Description
 *  API to send error response
 *
 *  \param [in] error_code Reason/Code for Error Response
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_esl_error_response
           (
               /* IN */ UCHAR error_code
           );

/**
 *  \brief API to send LED state response
 *
 *  \par Description
 *  API to send LED state response
 *
 *  \param [in] led_index LED Index for which State Response to be sent
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_led_state
           (
               /* IN */ UCHAR led_index
           );

/**
 *  \brief API to send display state response
 *
 *  \par Description
 *  API to send display state response
 *
 *  \param [in] display_index Display Index for which State Response to be sent
 *  \param [in] image_index Image Index for which State Response to be sent
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_display_state
           (
                /* IN */ UCHAR display_index,
                /* IN */ UCHAR image_index
            );

/**
 *  \brief API to send sensor data response
 *
 *  \par Description
 *  API to send sensor data response
 *
 *  \param [in] sensor_index Index of Sensor for which response to be sent
 *  \param [in] sensor_data Sensor Data to be sent as response
 *  \param [in] sensor_data_length Sensor Data Length to be sent as response
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_sensor_value
           (
               /* IN */ UCHAR  sensor_index,
               /* IN */ UCHAR  * sensor_data,
               /* IN */ UINT16 sensor_data_length
           );

#ifdef BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
/**
 *  \brief API to send vendor specific response
 *
 *  \par Description
 *  API to send vendor specific response
 *
 *  \param [in] response_opcode Vendor Specific Response code
 *  \param [in] response_data Vendor Specific Response Data
 *  \param [in] response_data_length Length of Vendor Specific Response Data
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_send_vendor_specific_response
           (
               /* IN */ UCHAR  response_opcode,
               /* IN */ UCHAR  * response_data,
               /* IN */ UINT16 response_data_length
           );
#endif /* BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS */

/**
 *  \brief API to setup ESL Tag Factory Reset
 *
 *  \par Description
 *  This API is used to remove all bonding information with
 *  the AP, delete the values of the AP Sync Key Material, ESL Response
 *  Key Material, and ESL Address in internal storage; and
 *  delete all stored commands.(Refer section 3.9.2.4 in
 *  ESLS V1.0 spec)
 *
 *  It shall be invoked
 *  - After receiving factory reset command in control point
 *  and link is disconnected
 *
 *  \return \ref BT_ESL_API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT BT_esl_tag_post_factory_reset(void);

/**
 *  \brief API to reset the ESL tag
 *
 *  \par Description
 *  This interface is used to reset the ESL Tag
 */
void BT_esl_tag_reset(void);

/**
 *  \brief API to update the max image supported
 *
 *  \par Description
 *  Interface to update the Maximum number of supported
 *  images in ESL Tag.
 *
 *  \param [in] num_of_images
 *         Maximum Images supported by ESL
 *
 *  \return returns nothing.
 */
void BT_esl_tag_update_max_image_supported(/* IN */ UCHAR num_of_images);

/**
 *  \brief API to update Basic State
 *
 *  \par Description
 *  This API is used to update the Basic State of the ESL Tag.
 *
 *  \param [in] bit_pos Position of the bit in the Basic State to be updated.
 *
 *  \param [in] flag Value to set for the bit.
 *
 *  \return returns nothing.
 */
void BT_esl_tag_update_basic_state(UCHAR bit_pos, UCHAR flag);

/**
 * \brief API to get the current Basic State of the ESL Tag
 *
 * \par Description
 *  This API is used to retrieve the current Basic State of the ESL Tag.
 *
 * \return The current Basic State of the ESL Tag.
 */
UINT16 BT_esl_tag_get_basic_state(void);

/** \} */

/**
 * \name ESL Tag Interfaces to be invoked by Bluetooth Abstraction Layer
 * \{
 */

/**
 * \brief API to handle incoming write request for CCCD
 *
 * \par Description
 * This function is called when a write request for
 * the Client Characteristic Configuration Descriptor (CCCD) is received.
 *
 * \param [in] peer_addr Reference to the Bluetooth address of the peer device.
 * \param [in] char_id Characteristic ID of the CCCD.
 * \param [in] value New value to be written to the CCCD.
 *
 * \return BT_ESL_API_SUCCESS if the write is handled successfully,
 * ATT ERROR otherwise.
 */
API_RESULT BT_esl_tag_write_cccd_handler
           (
               /* IN */ BT_ESL_BD_ADDR * peer_addr,
               /* IN */ UCHAR   char_id,
               /* IN */ UINT16  value
           );

/**
 * \brief API to handle incoming write request for a characteristic
 *
 * \par Description
 * This function is called when a write request for a characteristic
 *
 * \param [in] peer_addr Reference to the Bluetooth address of the peer device.
 * \param [in] char_id Characteristic ID of the characteristic being written.
 * \param [in] buffer Pointer to the data buffer containing the value to be written.
 * \param [in] buffer_length Length of the data buffer.
 *
 * \return BT_ESL_API_SUCCESS if the write is handled successfully,
 * ATT ERROR otherwise.
 */
API_RESULT BT_esl_tag_write_request_handler
           (
               /* IN */ BT_ESL_BD_ADDR * peer_addr,
               /* IN */ UCHAR            char_id,
               /* IN */ UCHAR          * buffer,
               /* IN */ UINT16           buffer_length
           );

/**
 * \brief API to handle incoming read request for a characteristic
 *
 * \par Description
 * This function is called when a read request for a characteristic
 *
 * \param [in] peer_addr Reference to the Bluetooth address of the peer device.
 * \param [in] service_uuid UUID of the service containing the characteristic.
 * \param [in] char_type Type of the characteristic being read.
 * \param [in] offset Offset from which to read the characteristic value.
 * \param [in] mtu_size Maximum Transmission Unit size for the read operation.
 * \param [out] buffer Reference to the buffer where the read value will be stored.
 * \param [out] buffer_len Reference to the length of the buffer.
 *
 * \return BT_ESL_API_SUCCESS if the read is handled successfully,
 * ATT ERROR otherwise.
 */
API_RESULT BT_esl_tag_read_request_handler
           (
               /* IN */   BT_ESL_BD_ADDR * peer_addr,
               /* IN */   UINT16           service_uuid,
               /* IN */   UCHAR            char_type,
               /* IN */   UCHAR            offset,
               /* IN */   UINT16           mtu_size,
               /* OUT */  UCHAR          * buffer,
               /* OUT */  UINT16         * buffer_len
            );

/**
 * \brief API to handle HCI connection complete event
 *
 * \par Description
 * This function is called when a connection to the ESL Access Point
 * is established.
 *
 * \param [in] status Status of the connection.
 * \param [in] peer_address Reference to the Bluetooth address of the peer device.
 *
 * \return BT_ESL_API_SUCCESS if the connection is established successfully,
 * BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_tag_hci_connection_complete_handler
           (
               UCHAR            status,
               BT_ESL_BD_ADDR * peer_address
           );

/**
 * \brief API to handle periodic advertising sync transfer TX received event
 *
 * \par Description
 * This function is called when the periodic advertising sync transfer
 * TX received event occurs.
 *
 * \param [in] status Status of the sync transfer.
 * \param [in] connection_handle Connection handle for the sync transfer.
 * \param [in] advertiser_addr Reference to the Bluetooth address of the advertiser.
 *
 * \return BT_ESL_API_SUCCESS if the sync transfer is handled successfully,
 * BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_tag_padv_sync_tx_received_handler
           (
               UCHAR            status,
               UINT16           connection_handle,
               BT_ESL_BD_ADDR * advertiser_addr
           );

/**
 * \brief API to handle periodic advertising report event
 *
 * \par Description
 * This function is called when a periodic advertising report event occurs.
 *
 * \param [in] padv_report_evt Reference to the periodic advertising report parameters.
 *
 * \return BT_ESL_API_SUCCESS if the report is handled successfully,
 * BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_tag_periodic_adv_report_handler
           (
               BT_ESL_PADV_REPORT_PARAMS * padv_report_evt
           );

/**
 * \brief API to handle periodic advertising sync lost event
 *
 * \par Description
 * This function is called when a periodic advertising sync lost event occurs
 *      or when sync is terminated
 *
 * \return BT_ESL_API_SUCCESS if the sync lost event is handled successfully,
 * BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_tag_periodic_adv_sync_lost_handler(void);

/**
 * \brief API to handle disconnect complete event
 *
 * \par Description
 * This function is called when a disconnect complete event occurs.
 *
 * \param [in] peer_address Reference to the Bluetooth address of the peer device.
 * \param [in] reason Reason for the disconnection.
 *
 * \return BT_ESL_API_SUCCESS if the disconnect complete event is handled successfully,
 * BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_tag_disconnect_complete_handler
           (
               BT_ESL_BD_ADDR * peer_address,
               UCHAR            reason
           );

/** \} */

#endif /* BT_ESL_SUPPORT_TAG_ROLE */

/** \} */

#ifdef __cplusplus
};
#endif

#endif /* _H_BT_ESL_ */

