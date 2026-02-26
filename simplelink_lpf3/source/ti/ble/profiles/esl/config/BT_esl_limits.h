
/**
 *  \file BT_esl_limits.h
 *
 *  \brief ESL Configurable Limits File.
 *
 *  This file lists all the configurable limits available in
 *  ESL module.
 */

/*
 *  Copyright (C) 2025. LTIMindtree Limited.
 *  All rights reserved.
 */

#ifndef _H_BT_ESL_LIMITS_
#define _H_BT_ESL_LIMITS_

/* ----------------------------------------------------------------------- */
/* ========== ESL v1.0.0 Configurable Limits ============================= */
/* ----------------------------------------------------------------------- */

/* Compile-time range checks for ESL limits (safeguard, main enforcement should be in Kconfig) */

/**
 *  BT_ESL_MAX_SENSOR_SUPPORTED
 *
 *  Maximum number of Sensors supported
 *  (Refer section 2.7.2.1.3, in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_SENSOR_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_SENSOR_SUPPORTED <= 256)
#define BT_ESL_MAX_SENSOR_SUPPORTED CONFIG_BT_ESL_MAX_SENSOR_SUPPORTED
#else
#define BT_ESL_MAX_SENSOR_SUPPORTED                                   256
#endif

/**
 *  BT_ESL_MAX_LED_SUPPORTED
 *
 *  Maximum number of LED supported
 *  (Refer section 2.7.2.1.2, in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_LED_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_LED_SUPPORTED <= 256)
#define BT_ESL_MAX_LED_SUPPORTED CONFIG_BT_ESL_MAX_LED_SUPPORTED
#else
#define BT_ESL_MAX_LED_SUPPORTED                                      256
#endif

/**
 *  BT_ESL_MAX_IMAGE_SUPPORTED
 *
 *  Maximum number of Images supported
 *  (Refer section 2.7.2.1.1, in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_IMAGE_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_IMAGE_SUPPORTED <= 256)
#define BT_ESL_MAX_IMAGE_SUPPORTED CONFIG_BT_ESL_MAX_IMAGE_SUPPORTED
#else
#define BT_ESL_MAX_IMAGE_SUPPORTED                                    256
#endif

/**
 *  BT_ESL_MAX_DISPLAY_SUPPORTED
 *
 *  Maximum number of Displays supported
 *  (Refer section 3.5.1, in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_DISPLAY_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_DISPLAY_SUPPORTED <= 102)
#define BT_ESL_MAX_DISPLAY_SUPPORTED CONFIG_BT_ESL_MAX_DISPLAY_SUPPORTED
#else
#define BT_ESL_MAX_DISPLAY_SUPPORTED                                  102
#endif

/**
 *  BT_ESL_MAX_NO_OF_RESPONSE
 *
 *  Maximum no of responses ESL tag can send is 24
 *  considering minimum length of response TLV is
 *  2(1 byte of rsp opcode + 1 byte of parameter)
 */
#if (CONFIG_BT_ESL_MAX_NO_OF_RESPONSE >= 1) && (CONFIG_BT_ESL_MAX_NO_OF_RESPONSE <= 24)
#define BT_ESL_MAX_NO_OF_RESPONSE CONFIG_BT_ESL_MAX_NO_OF_RESPONSE
#else
#define BT_ESL_MAX_NO_OF_RESPONSE                                     24
#endif

/**
 *  BT_ESL_MAX_GROUPS_SUPPORTED
 *
 *  Maximum number of Groups supported
 *  (Refer section 3.1.1.2 in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_GROUPS_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_GROUPS_SUPPORTED <= 128)
#define BT_ESL_MAX_GROUPS_SUPPORTED CONFIG_BT_ESL_MAX_GROUPS_SUPPORTED
#else
#define BT_ESL_MAX_GROUPS_SUPPORTED                                   128
#endif

/**
 *  BT_ESL_MAX_ESL_TAGS_SUPPORTED
 *
 *  Maximum number of ESL tags supported per group
 *  (Refer section 3.1.1.2 in ESL Bluetooth spec)
 */
#if (CONFIG_BT_ESL_MAX_ESL_TAGS_SUPPORTED >= 1) && (CONFIG_BT_ESL_MAX_ESL_TAGS_SUPPORTED <= 255)
#define BT_ESL_MAX_ESL_TAGS_SUPPORTED CONFIG_BT_ESL_MAX_ESL_TAGS_SUPPORTED
#else
#define BT_ESL_MAX_ESL_TAGS_SUPPORTED                                 255
#endif

#endif /* _H_BT_ESL_LIMITS_ */

