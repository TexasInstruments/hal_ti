
/**
 *  \file BT_esl_features.h
 *
 *  \brief ESL Compilation Switches Configuration File.
 *
 *  This file lists all the Compilation Flags available in
 *  ESL module.
 */

/*
 *  Copyright (C) 2025. LTIMindtree Limited.
 *  All rights reserved.
 */

#ifndef _H_BT_ESL_FEATURES_
#define _H_BT_ESL_FEATURES_

/* ----------------------------------------------------------------------- */
/* ==== ESL v1.0.0 Feature Flags ========================================= */
/* ----------------------------------------------------------------------- */

#if defined(CONFIG_BT_ESL_AP)
/**
 *  BT_ESL_SUPPORT_AP_ROLE
 *
 *  This flag is used to enable support for ESL Access Point Role.
 *
 *  Dependency: None.
 */
#define BT_ESL_SUPPORT_AP_ROLE

#if defined(CONFIG_BT_ESL_SEPARATE_KEY_PER_GROUP)
/**
 *  BT_ESL_AP_SEPERATE_KEY_PER_GROUP
 *
 *  This flag is to be enabled when separate key per group are to be used
 *
 *  Dependency: BT_ESL_SUPPORT_AP_ROLE
 */
#define BT_ESL_AP_SEPERATE_KEY_PER_GROUP
#endif /* CONFIG_BT_ESL_SEPARATE_KEY_PER_GROUP */
#endif /* CONFIG_BT_ESL_AP */

#if defined(CONFIG_BT_ESL_TAG)
/**
 *  BT_ESL_SUPPORT_TAG_ROLE
 *
 *  This flag is used to enable support for ESL Tag Role.
 *
 *  Dependency: None.
 */
#define BT_ESL_SUPPORT_TAG_ROLE

#if defined(CONFIG_BT_ESL_LED)
/**
 *  BT_ESL_SUPPORTS_LEDS
 *
 *  This flag is to be enabled when ESL Tag supports LEDs.
 *
 *  Dependency: BT_ESL_SUPPORT_TAG_ROLE
 */
#define BT_ESL_SUPPORTS_LEDS
#endif /* CONFIG_BT_ESL_LED */

#if defined(CONFIG_BT_ESL_SENSOR)
/**
 *  BT_ESL_SUPPORTS_SENSORS
 *
 *  This flag is to be enabled when ESL Tag supports Sensors.
 *
 *  Dependency: BT_ESL_SUPPORT_TAG_ROLE
 */
#define BT_ESL_SUPPORTS_SENSORS
#endif /* CONFIG_BT_ESL_SENSOR */

#if defined(CONFIG_BT_ESL_DISPLAY)
/**
 *  BT_ESL_SUPPORTS_DISPLAYS
 *
 *  This flag is to be enabled when ESL Tag supports Displays.
 *
 *  Dependency: BT_ESL_SUPPORT_TAG_ROLE
 */
#define BT_ESL_SUPPORTS_DISPLAYS
#endif /* CONFIG_BT_ESL_DISPLAY */

#if defined(CONFIG_BT_ESL_WAIT_TIMEOUT)
/**
 *  BT_ESL_WAIT_TIMEOUT
 *
 *  This flag is to be enabled when ESL Tag supports wait
 *  activity Timer.
 *
 *  Dependency: BT_ESL_SUPPORT_TAG_ROLE
 */
#define BT_ESL_WAIT_TIMEOUT
#endif /* CONFIG_BT_ESL_WAIT_TIMEOUT */
#endif /* CONFIG_BT_ESL_TAG */

#if defined(CONFIG_BT_ESL_VENDOR_SPECIFIC_COMMANDS)
/**
 *  BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
 *
 *  This flag is used to enable support for any vendor specific opcodes
 *  that can be used by ESL implementation for both AP & Tag roles.
 *
 *  Dependency: None.
 */
#define BT_ESL_SUPPORT_VENDOR_SPECIFIC_COMMANDS
#endif /* CONFIG_BT_ESL_VENDOR_SPECIFIC_COMMANDS */

#if defined(CONFIG_BT_ESL_DYNAMIC_GLOBAL_CONFIGURATION)
/**
 *  BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY
 *
 *  This flag is used to enable support for Dynamic Configuration
 *  of Limits within the ESL implementation. When this flag is enabled, the global arrays
 *  can be resized dynamically at runtime to accommodate varying numbers of ESL related
 *  parameters such as groups, tags, displays, LEDs, and sensors. This allows for greater
 *  flexibility in the implementation, as the limits can be adjusted based on the specific
 *  requirements of the application or environment.
 *
 *  Dependency: None.
 */
#define BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY
#endif /* CONFIG_BT_ESL_DYNAMIC_GLOBAL_CONFIGURATION */

/* ----------------------------------------------------------------------- */
/* ==== ESL Version Feature Flags ======================================== */
/* ----------------------------------------------------------------------- */
/*
 *  BT_ESL_SUPPORT_VERSION_INFO
 *
 *  This flag enables EtherMind BT_esl_get_version_number() API.
 *
 *  This API is used to retrieve the current stack build version
 *  information
 *
 *  Dependency: None.
 */
#define BT_ESL_SUPPORT_VERSION_INFO

/* ----------------------------------------------------------------------- */
/* ==== ESL Thread Synchronization Flags ================================= */
/* ----------------------------------------------------------------------- */
/*
 *  BT_ESL_DISABLE_MUTEX
 *
 *  This flag disables the use of mutex and conditional variables from all
 *  ESL modules.
 *  This should be defined in EtherMind builds where synchronization
 *  primitives are not required.
 *
 * NOTE: This is to be disabled as default behaviour on Zephyr, later.
 *
 *  Dependency: None.
 */
#define BT_ESL_DISABLE_MUTEX

/* ----------------------------------------------------------------------- */
/* ==== Debug Specification Flags ======================================== */
/* ----------------------------------------------------------------------- */
/*
 *  Debug definitions for all the layers (protocol and profiles) should be
 *  defined in this section.
 */

/*
 * By default, the Error Logs of all the layers are enabled.
 * To disable error logging of a module, define <module>_NO_DEBUG flag.
 * Example: Define ESL_NO_DEBUG to disable error logging of ESL Core layer.
 *
 * By default, the Trace, Information, Data and other Logs
 * of all the layers are disabled.
 * To enable debug logging of a module, define <module>_DEBUG flag.
 * Example: Define ESL_DEBUG to enable debug logging (Trace and Information)
 * of ESL Core layer.
 */
/** ESL Core Module Debug Flags */
#define ESL_NO_DEBUG
/* #define ESL_DEBUG */
#endif /* _H_BT_ESL_FEATURES_ */

