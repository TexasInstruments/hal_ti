
/**
 *  \file BT_ESL_common.h
 *
 *
 *  Common Internal Header File contains basic typedefs and
 * memory management utilities
 */

 /*
  *  Copyright (C) 2025. Mindtree Ltd.
  *  All rights reserved.
  */

#ifndef _H_BT_ESL_COMMON_
#define _H_BT_ESL_COMMON_

/* -------------------------------------------- Header File Inclusion */
/** The EtherMind OS Abstraction */
#include "EM_os.h"

/** The EtherMind ESL Configuration Parameters */
#include "BT_esl_features.h"

/** The EtherMind ESL Tunable Constant */
#include "BT_esl_limits.h"

/** The EtherMind Debug Library */
#include "EM_debug.h"

/** For EM_assert() macro */
#include "EM_assert.h"

/** The EtherMind Timer Library */
#include "EM_timer.h"

/* -------------------------------------------- Global Definitions */

/**
 * \addtogroup EtherMind_ESL_Common_Constants
 * \{
 */

/**
 * \name ESL Common Status definitions
 * \{
 */
/** ESL - Success Status */
#define BT_ESL_API_SUCCESS                      EM_SUCCESS
/** ESL - Failure Status */
#define BT_ESL_API_FAILURE                      EM_FAILURE

/** \} */

/** \} */

#define BT_ESL_TIMER_HANDLE_INIT_VAL            EM_TIMER_HANDLE_INIT_VAL
#define BT_ESL_TIMEOUT_MILLISEC                 EM_TIMEOUT_MILLISEC

/* Definition for True/False */
#ifndef BT_ESL_FALSE
#define BT_ESL_FALSE                            (UINT8)0U
#endif /* BT_ESL_FALSE */

#ifndef BT_ESL_TRUE
#define BT_ESL_TRUE                             (UINT8)1U
#endif /* BT_ESL_TRUE */

/* Size of Bluetooth Device Address (BD_ADDR) in number of Octets */
#define BT_ESL_BD_ADDR_SIZE                     6U
#define BT_ESL_BD_ADDR_TYPE_SIZE                1U
#define BT_ESL_BD_DEV_ADDR_SIZE                 (BT_ESL_BD_ADDR_SIZE + BT_ESL_BD_ADDR_TYPE_SIZE)

/**
 * \name Stack States
 * \{
 */
/** ESL Stack Initialization State - Undefined */
#define BT_ESL_STACK_INIT_UNDEFINED             0x00U
/** ESL Stack Initialization State - Initialized */
#define BT_ESL_STACK_INIT_ESL_INIT              0x01U
/** \} */

/**
 * \name ESL Module States
 * \{
 */
/** ESL Module State - Invalid */
#define BT_ESL_MODULE_STATE_INVALID                0x00U
/** ESL Module State - Initialized */
#define BT_ESL_MODULE_STATE_INITIALIZED            0x01U
/** \} */

/** Page 2 - GATT based Profile Modules */
#define BT_ESL_MODULE_PAGE_2                       0x20000000U

/** Module - Bit Mask */
#define BT_MODULE_BIT_MASK_ESL                     0x00000001U

/** Module ID */
#define BT_MODULE_ID_ESL         (BT_ESL_MODULE_PAGE_2 | BT_MODULE_BIT_MASK_ESL)

/**
 * \name Module State Tracking Macros
 * \{
 */
 /** Define Global ESL Module State */
#define BT_ESL_DEFINE_MODULE_STATE(module_name) UINT8 g_esl_##module_name = BT_ESL_MODULE_STATE_INVALID;

/** Declare Global ESL Module State */
#define BT_ESL_DECLARE_MODULE_STATE(module_name) extern UINT8 g_esl_##module_name;

/** Set Global ESL Module State */
#define BT_ESL_SET_MODULE_STATE(module_name, s) g_esl_##module_name = BT_ESL_MODULE_STATE_##s;

/** Check the Global ESL Module State */
#define IF_ESL_MODULE_STATE(module_name, s) if(g_esl_##module_name == BT_ESL_MODULE_STATE_##s)
/** \} */

/* ================== EtherMind ESL Common Reason Error Codes ================= */

/**
 * \addtogroup EtherMind_ESL_Common_Error_Codes
 * \{
 */

/**
 * \name ESL Common OSAL Error Codes
 * \{
 */
/** Error Code for MUTEX Initialization Failure */
#ifndef MUTEX_INIT_FAILED
#define MUTEX_INIT_FAILED                       0x0001
#endif /* MUTEX_INIT_FAILED */
/** Error Code for Conditional Variable Initialization Failure */
#ifndef COND_INIT_FAILED
#define COND_INIT_FAILED                        0x0002
#endif /* COND_INIT_FAILED */
/** Error Code for MUTEX Lock Failure */
#ifndef MUTEX_LOCK_FAILED
#define MUTEX_LOCK_FAILED                       0x0003
#endif /* MUTEX_LOCK_FAILED */
/** Error Code for MUTEX Unlock Failure */
#ifndef MUTEX_UNLOCK_FAILED
#define MUTEX_UNLOCK_FAILED                     0x0004
#endif /* MUTEX_UNLOCK_FAILED */
/** Error Code for Memory Allocation Failure */
#ifndef MEMORY_ALLOCATION_FAILED
#define MEMORY_ALLOCATION_FAILED                0x0005
#endif /* MEMORY_ALLOCATION_FAILED */
/** \} */

/**
 * \name ESL Common Module Error ID
 * \{
 */
/** ESL Common Error codes */
#define BT_ESL_ERR_ID                           0x0100U
/** \} */

/**
 * \name ESL Layer OSAL Error Codes
 * \{
 */
/** ESL Error Code for MUTEX Initialization Failure */
#define ESL_MUTEX_INIT_FAILED                    \
        (MUTEX_INIT_FAILED | BT_ESL_ERR_ID)
/** ESL Error Code for Conditional Variable Initialization Failure */
#define ESL_COND_INIT_FAILED                     \
        (COND_INIT_FAILED | BT_ESL_ERR_ID)
/** ESL Error Code for MUTEX Lock Failure */
#define ESL_MUTEX_LOCK_FAILED                    \
        (MUTEX_LOCK_FAILED | BT_ESL_ERR_ID)
/** ESL Error Code for MUTEX Unlock Failure */
#define ESL_MUTEX_UNLOCK_FAILED                  \
        (MUTEX_UNLOCK_FAILED | BT_ESL_ERR_ID)
/** ESL Error Code for Memory Allocation Failure */
#define ESL_MEMORY_ALLOCATION_FAILED             \
        (MEMORY_ALLOCATION_FAILED | BT_ESL_ERR_ID)
/** \} */

/** \} */

/* -------------------------------------------- Structures/Data Types */
/**
 * \addtogroup EtherMind_ESL_Common_Structures
 * \{
 */

/**
 * \name ESL Layer Common Data Types
 * \{
 */
/* Time type */
typedef EM_time_type                            BT_ESL_time_type;

/** Function Return Value type for ESL APIs */
#ifndef API_RESULT_DEFINED
typedef EM_RESULT                               API_RESULT;
#define API_RESULT_DEFINED
#endif /* API_RESULT_DEFINED */

/** Mutex type */
typedef EM_thread_mutex_type                    BT_ESL_MUTEX_TYPE;

/** Conditional Variable type */
typedef EM_thread_cond_type                     BT_ESL_CONDVAR_TYPE;

/** Timer handle */
typedef EM_timer_handle                         BT_ESL_TIMER_HANDLE;

/**
 * Dynamic configuration of ESL.
 *  Used only if 'BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY' is defined.
 */
#ifdef BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY
typedef struct _BT_ESL_DYNAMIC_CONFIG
{
#ifdef BT_ESL_SUPPORT_AP_ROLE
    /** Max no of groups supported */
    UCHAR config_BT_ESL_MAX_GROUPS_SUPPORTED;

    /** Max no of tags per group supported */
    UCHAR config_BT_ESL_MAX_ESL_TAGS_SUPPORTED;

    /** Max displays supported */
    UCHAR config_BT_ESL_MAX_DISPLAY_SUPPORTED;

    /** Max led supported */
    UCHAR config_BT_ESL_MAX_LED_SUPPORTED;

    /** Max sensors supported */
    UCHAR config_BT_ESL_MAX_SENSOR_SUPPORTED;

    /** Max Image supported */
    UCHAR config_BT_ESL_MAX_IMAGE_SUPPORTED;

    /** Max no of responses for one subevent */
    UCHAR config_BT_ESL_MAX_NO_OF_RESPONSE;

    /** configuration timeout */
    UCHAR config_BT_ESL_AP_CONFIG_TIMEOUT;

    /** Max no of sync retries */
    UCHAR config_BT_ESL_AP_MAX_SYNC_RETRY_COUNT;

    /** Sync retry Interval */
    UINT32 config_BT_ESL_AP_SYNC_RETRY_INTERVAL_MS;
#endif /* BT_ESL_SUPPORT_AP_ROLE */
} BT_ESL_DYNAMIC_CONFIG;
#endif /* BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY */

/** \} */

/** \} */

/* --------------------------------------------------- Macros */

/** Timer macros */
#define BT_ESL_start_timer(h, t, c, a, s)       EM_start_timer((h), (t), (c), (a), (s))
#define BT_ESL_restart_timer(h, t)              EM_restart_timer((h), (t))
#define BT_ESL_stop_timer(h)                    EM_stop_timer(h)
#define BT_ESL_is_active_timer(h)               EM_is_active_timer(h)

#define BT_ESL_sleep(t)                         EM_sleep(t)
#define BT_ESL_usleep(t)                        EM_usleep(t)
#define BT_ESL_get_current_time(x)              EM_get_current_time(x)

/* Abstractions for String library functions */
#define BT_ESL_str_len(s)                       EM_str_len(s)
#define BT_ESL_str_n_len(s, sz)                 EM_str_n_len(s, sz)
#define BT_ESL_str_copy(d, s)                   EM_str_copy(d, s)
#define BT_ESL_str_n_copy(d, s, n)              EM_str_n_copy(d, s, n)
#define BT_ESL_str_cmp(s1, s2)                  EM_str_cmp(s1, s2)
#define BT_ESL_str_n_cmp(s1, s2, n)             EM_str_n_cmp(s1, s2, n)
#define BT_ESL_str_cat(d, s)                    EM_str_cat(d, s)
#define BT_ESL_str_n_cat(d, s, sz)              EM_str_n_cat(d, s, sz)
#define BT_ESL_str_str(s, ss)                   EM_str_str(s, ss)
#define BT_ESL_str_chr(s, ch)                   EM_str_chr(s, ch)
#define BT_ESL_str_n_casecmp(s1, s2, n)         EM_str_n_casecmp(s1, s2, n)
#define BT_ESL_str_print(...)                   EM_str_print(...)

/* Abstractions for memory functions */
#define BT_ESL_mem_move(d, s, n)                EM_mem_move(d, s, n)
#define BT_ESL_mem_cmp(p1, p2, n)               EM_mem_cmp(p1, p2, n)
#define BT_ESL_mem_set(p, v, n)                 EM_mem_set(p, v, n)
#define BT_ESL_mem_copy(p1, p2, n)              EM_mem_copy(p1, p2, n)

/**
 * \name ESL Task Synchronization Macros
 * \{
 */

#ifndef BT_ESL_DISABLE_MUTEX

/** Macro to define a Mutex Variable */
#define BT_ESL_DEFINE_MUTEX(mutex) EM_thread_mutex_type mutex;

/** Macro to define a Mutex Variable with a type qualifier */
#define BT_ESL_DEFINE_MUTEX_TYPE(type, mutex) type EM_thread_mutex_type mutex;

/** Macro to define a Conditional Variable */
#define BT_ESL_DEFINE_COND(cond) EM_thread_cond_type cond;

/** Macro to define a Conditional Variable with a type qualifier */
#define BT_ESL_DEFINE_COND_TYPE(type, cond) type EM_thread_cond_type cond;

/**
 *  Macro to Initialize Mutex.
 *  To be used in void functions as it returns no error.
 */
#define BT_ESL_MUTEX_INIT_VOID(mutex, MODULE)                            \
    if (EM_thread_mutex_init(&(mutex), NULL) < 0)                        \
    {                                                                    \
        EM_debug_error(                                                  \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Mutex in " #MODULE ".\n");                 \
        return;                                                          \
    }

/**
 *  Macro to Initialize Mutex.
 *  This returns an error if mutex initialization fails.
 */
#define BT_ESL_MUTEX_INIT(mutex, MODULE)                                 \
    if (EM_thread_mutex_init(&(mutex), NULL) < 0)                        \
    {                                                                    \
        EM_debug_error(                                                  \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Mutex in " #MODULE ".\n");                 \
        return MODULE##_MUTEX_INIT_FAILED;                               \
    }

/**
 *  Macro to Initialize Conditional Variable.
 *  To be used in void function as it returns no error.
 */
#define BT_ESL_COND_INIT_VOID(cond, MODULE)                              \
    if (EM_thread_cond_init(&(cond), NULL) < 0)                          \
    {                                                                    \
        EM_debug_error(                                                  \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Conditional Variable in " #MODULE ".\n");  \
        return;                                                          \
    }

/**
 *  Macro to Initialize Conditional Variable.
 *  It returns an error if conditional variable initialization fails.
 */
#define BT_ESL_COND_INIT(cond, MODULE)                                   \
    if (EM_thread_cond_init(&(cond), NULL) < 0)                          \
    {                                                                    \
        EM_debug_error(                                                  \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Conditional Variable in " #MODULE ".\n");  \
        return MODULE##_COND_INIT_FAILED;                                \
    }

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. It returns an error if mutex lock fails.
 */
#define BT_ESL_MUTEX_LOCK(mutex, MODULE)                             \
    if (EM_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return MODULE##_MUTEX_LOCK_FAILED;                           \
    }

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. To be used in void function as it
 *  returns no error.
 */
#define BT_ESL_MUTEX_LOCK_VOID(mutex, MODULE)                        \
    if (EM_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return;                                                      \
    }

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function.
 *  It returns the error 'value' if mutex lock fails.
 */
#define BT_ESL_MUTEX_LOCK_RETURN_ON_FAILURE(mutex, MODULE, value)    \
    if (EM_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return (value);                                              \
    }

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. On failure, only an Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_ESL_MUTEX_LOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)     \
    if (EM_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
    }

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. It returns an error if mutex unlock fails.
 */
#define BT_ESL_MUTEX_UNLOCK(mutex, MODULE)                           \
    if (EM_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return MODULE##_MUTEX_UNLOCK_FAILED;                         \
    }

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. To be used in void functions as it returns
 *  no error.
 */
#define BT_ESL_MUTEX_UNLOCK_VOID(mutex, MODULE)                      \
    if (EM_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return;                                                      \
    }

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into.
 *  It returns the error 'value' if mutex unlock fails.
 */
#define BT_ESL_MUTEX_UNLOCK_RETURN_ON_FAILURE(mutex, MODULE, value)  \
    if (EM_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return (value);                                              \
    }

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. On failure, only Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_ESL_MUTEX_UNLOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)   \
    if (EM_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        EM_debug_error(                                              \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
    }

#else  /* BT_ESL_DISABLE_MUTEX */

/** Macro to define a Mutex Variable */
#define BT_ESL_DEFINE_MUTEX(mutex)

/** Macro to define a Mutex Variable with a type qualifier */
#define BT_ESL_DEFINE_MUTEX_TYPE(type, mutex)

/** Macro to define a Conditional Variable */
#define BT_ESL_DEFINE_COND(cond)

/** Macro to define a Conditional Variable with a type qualifier */
#define BT_ESL_DEFINE_COND_TYPE(type, cond)

/**
 *  Macro to Initialize Mutex.
 *  To be used in void function as it returns no error.
 */
#define BT_ESL_MUTEX_INIT_VOID(mutex, MODULE)

/**
 *  Macro to Initialize Mutex.
 *  It returns an error if mutex initialization fails.
 */
#define BT_ESL_MUTEX_INIT(mutex, MODULE)

/**
 *  Macro to Initialize Conditional Variable.
 *  To be used in void function as it returns no error.
 */
#define BT_ESL_COND_INIT_VOID(cond, MODULE)

/**
 *  Macro to Initialize Conditional Variable.
 *  It returns an error if conditional variable initialization fails.
 */
#define BT_ESL_COND_INIT(cond, MODULE)

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. It returns an error if mutex lock fails.
 */
#define BT_ESL_MUTEX_LOCK(mutex, MODULE)

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. To be used in void function as it
 *  returns no error.
 */
#define BT_ESL_MUTEX_LOCK_VOID(mutex, MODULE)

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function.
 *  It returns the error 'value' if mutex lock fails.
 */
#define BT_ESL_MUTEX_LOCK_RETURN_ON_FAILURE(mutex, MODULE, value)

/**
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. On failure, only an Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_ESL_MUTEX_LOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. It returns an error if mutex unlock fails.
 */
#define BT_ESL_MUTEX_UNLOCK(mutex, MODULE)

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. To be used in void functions as it returns
 *  no error.
 */
#define BT_ESL_MUTEX_UNLOCK_VOID(mutex, MODULE)

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into.
 *  It returns the error 'value' if mutex unlock fails.
 */
#define BT_ESL_MUTEX_UNLOCK_RETURN_ON_FAILURE(mutex, MODULE, value)

/**
 *  Unlocks the Module Specific Mutex which releases the global variables
 *  to be written into. On failure, only Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_ESL_MUTEX_UNLOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)

#endif /* BT_ESL_DISABLE_MUTEX */

/** \} */

/**
 * \name Bit-wise Operation Macros
 * \{
 */
/** Abstractions for bit-wise operation */
/** Macro to extract value of the corresponding bit number */
#define BT_ESL_EXTRACT_BITNUM(val, bitnum)        (((val) >> (bitnum)) & 1)
/** Macro to set the value of the corresponding bit number */
#define BT_ESL_SET_BITNUM(val, bitnum)            ((val) |= (1 << (bitnum)))
/** Macro to clear the value of the corresponding bit number */
#define BT_ESL_CLR_BITNUM(val, bitnum)            ((val) &= (~(1 << (bitnum))))
/** \} */


/**
 *  Packing Macros.
 *
 *  Syntax: BT_PACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE
 *
 *  Usage: Based on the endian-ness defined for each protocol/profile layer,
 *  appropriate packing macros to be used by each layer.
 *
 *  Example: HCI is defined as little endian protocol,
 *  so if HCI defines HCI_PACK_2_BYTE for packing a parameter of size 2 byte,
 *  that shall be mapped to BT_PACK_LE_2_BYTE
 *
 *  By default both the packing and unpacking macros uses pointer to
 *  a single or multi-octet variable which to be packed to or unpacked from
 *  a buffer (unsinged character array).
 *
 *  For the packing macro, another variation is available,
 *  where the single or multi-octet variable itself is used (not its pointer).
 *
 *  Syntax: BT_PACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE_VAL
 */

/* Little Endian Packing Macros */
#define BT_ESL_PACK_LE_1_BYTE(dst, src) \
    { \
        UCHAR val; \
        val = (UCHAR)(*(src)); \
        BT_ESL_PACK_LE_1_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_LE_1_BYTE_VAL(dst, src) \
    (dst)[0U] = (src);

#define BT_ESL_PACK_LE_2_BYTE(dst, src) \
    { \
        UINT16 val; \
        val = (UINT16)(*(src)); \
        BT_ESL_PACK_LE_2_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_LE_2_BYTE_VAL(dst, src) \
    (dst)[0U] = (UCHAR)(src); \
    (dst)[1U] = (UCHAR)((src) >> 8U);

#define BT_ESL_PACK_LE_3_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*(src)); \
        BT_ESL_PACK_LE_3_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_LE_3_BYTE_VAL(dst, src) \
    (dst)[0U] = (UCHAR)(src);\
    (dst)[1U] = (UCHAR)((src) >> 8U);\
    (dst)[2U] = (UCHAR)((src) >> 16U);

#define BT_ESL_PACK_LE_4_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*(src)); \
        BT_ESL_PACK_LE_4_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_LE_4_BYTE_VAL(dst, src) \
    (dst)[0U] = (UCHAR)(src);\
    (dst)[1U] = (UCHAR)((src) >> 8U);\
    (dst)[2U] = (UCHAR)((src) >> 16U);\
    (dst)[3U] = (UCHAR)((src) >> 24U);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_ESL_PACK_LE_8_BYTE(dst,val)\
        BT_ESL_mem_copy ((dst), (val), 8U)

#define BT_ESL_PACK_LE_16_BYTE(dst,val)\
        BT_ESL_mem_copy ((dst), (val), 16U)

#define BT_ESL_PACK_LE_N_BYTE(dst,val,n)\
        BT_ESL_mem_copy ((dst), (val), (n))

/* Big Endian Packing Macros */
#define BT_ESL_PACK_BE_1_BYTE(dst, src) \
    { \
        UCHAR val; \
        val = (UCHAR)(*((UCHAR *)(src))); \
        BT_ESL_PACK_BE_1_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_BE_1_BYTE_VAL(dst, src) \
    (dst)[0U] = (src);

#define BT_ESL_PACK_BE_2_BYTE(dst, src) \
    { \
        UINT16 val; \
        val = (UINT16)(*((UINT16 *)(src))); \
        BT_ESL_PACK_BE_2_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_BE_2_BYTE_VAL(dst, src) \
    (dst)[1U] = (UCHAR)(src); \
    (dst)[0U] = (UCHAR)((src) >> 8U);

#define BT_ESL_PACK_BE_3_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*((UINT32 *)(src))); \
        BT_ESL_PACK_BE_3_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_BE_3_BYTE_VAL(dst, src) \
    (dst)[2U] = (UCHAR)(src);\
    (dst)[1U] = (UCHAR)((src) >> 8U);\
    (dst)[0U] = (UCHAR)((src) >> 16U);

#define BT_ESL_PACK_BE_4_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*((UINT32 *)(src))); \
        BT_ESL_PACK_BE_4_BYTE_VAL((dst), val); \
    }

#define BT_ESL_PACK_BE_4_BYTE_VAL(dst, src) \
    (dst)[3U] = (UCHAR)(src);\
    (dst)[2U] = (UCHAR)((src) >> 8U);\
    (dst)[1U] = (UCHAR)((src) >> 16U);\
    (dst)[0U] = (UCHAR)((src) >> 24U);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_ESL_PACK_BE_8_BYTE(dst,val)\
        BT_ESL_mem_copy ((dst), (val), 8U)

#define BT_ESL_PACK_BE_16_BYTE(dst,val)\
        BT_ESL_mem_copy ((dst), (val), 16U)

#define BT_ESL_PACK_BE_N_BYTE(dst,val,n)\
        BT_ESL_mem_copy ((dst), (val), (n))


/**
 *  Unpacking Macros.
 *
 *  Syntax: BT_UNPACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE
 *
 *  Usage: Based on the endian-ness defined for each protocol/profile layer,
 *  appropriate unpacking macros to be used by each layer.
 *
 *  Example: HCI is defined as little endian protocol,
 *  so if HCI defines HCI_UNPACK_4_BYTE for unpacking a parameter of size 4 byte,
 *  that shall be mapped to BT_UNPACK_LE_4_BYTE
 */

/* Little Endian Unpacking Macros */
#define BT_ESL_UNPACK_LE_1_BYTE(dst,src)\
    *((UCHAR *)(dst)) = (UCHAR)(*((UCHAR *)(src)));

#define BT_ESL_UNPACK_LE_2_BYTE(dst,src)\
        *((UINT16 *)(dst))  = (src)[1U]; \
        *((UINT16 *)(dst))  = *((UINT16 *)(dst)) << 8U; \
        *((UINT16 *)(dst)) |= (src)[0U];

#define BT_ESL_UNPACK_LE_3_BYTE(dst,src)\
        *((UINT32 *)(dst))  = (src)[2U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[1U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[0U];

#define BT_ESL_UNPACK_LE_4_BYTE(dst,src)\
        *((UINT32 *)(dst))  = (src)[3U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[2U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[1U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[0U];

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_ESL_UNPACK_LE_8_BYTE(dst,src)\
        BT_ESL_mem_copy ((dst), (src), 8U)

#define BT_ESL_UNPACK_LE_16_BYTE(dst,src)\
        BT_ESL_mem_copy ((dst), (src), 16U)

#define BT_ESL_UNPACK_LE_N_BYTE(dst,src,n)\
        BT_ESL_mem_copy ((dst), (src), (n))

/* Big Endian Unpacking Macros */
#define BT_UNPACK_BE_1_BYTE(dst,src)\
    *((UCHAR *)(dst)) = (UCHAR)(*((UCHAR *)(src)));

#define BT_ESL_UNPACK_BE_2_BYTE(dst,src)\
        *((UINT16 *)(dst))  = (src)[0U]; \
        *((UINT16 *)(dst))  = *((UINT16 *)(dst)) << 8U; \
        *((UINT16 *)(dst)) |= (src)[1U];

#define BT_ESL_UNPACK_BE_3_BYTE(dst,src)\
        *((UINT32 *)(dst))  = (src)[0U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[1U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[2U];

#define BT_ESL_UNPACK_BE_4_BYTE(dst,src)\
        *((UINT32 *)(dst))  = (src)[0U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[1U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[2U];\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8U;\
        *((UINT32 *)(dst)) |= (src)[3U];

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_ESL_UNPACK_BE_8_BYTE(dst,src)\
        BT_ESL_mem_copy ((dst), (src), 8U)

#define BT_ESL_UNPACK_BE_16_BYTE(dst,src)\
        BT_ESL_mem_copy ((dst), (src), 16U)

#define BT_ESL_UNPACK_BE_N_BYTE(dst,src,n)\
        BT_ESL_mem_copy ((dst), (src), (n))

#define BT_ESL_DEVICE_ADDR_ONLY_FRMT_SPECIFIER\
       "ADDR: %02X:%02X:%02X:%02X:%02X:%02X (0x%02X%02X%02X%02X%02X%02X)"

#define BT_ESL_DEVICE_ADDR_ONLY_SPACED_FRMT_SPECIFIER\
       "ADDR: %02X %02X %02X %02X %02X %02X (0x%02X%02X%02X%02X%02X%02X)"

#define BT_ESL_DEVICE_ADDR_ONLY_PRINT_STR(ref)\
        (ref)[0U],(ref)[1U],(ref)[2U],(ref)[3U],(ref)[4U],(ref)[5U],\
        (ref)[5U],(ref)[4U],(ref)[3U],(ref)[2U],(ref)[1U],(ref)[0U]

#define BT_ESL_DEVICE_ADDR_FRMT_SPECIFIER\
        "ADDR: %02X:%02X:%02X:%02X:%02X:%02X, TYPE: %02X " \
        "(0x%02X%02X%02X%02X%02X%02X:%02X)"

#define BT_ESL_DEVICE_ADDR_SPACED_FRMT_SPECIFIER\
        "ADDR: %02X %02X %02X %02X %02X %02X, TYPE: %02X " \
        "(0x%02X%02X%02X%02X%02X%02X:%02X)"

#define BT_ESL_DEVICE_ADDR_PRINT_STR(ref)\
        (ref)->addr[0U],(ref)->addr[1U],(ref)->addr[2U],\
        (ref)->addr[3U],(ref)->addr[4U],(ref)->addr[5U],\
        (ref)->type,                                    \
        (ref)->addr[5U],(ref)->addr[4U],(ref)->addr[3U],\
        (ref)->addr[2U],(ref)->addr[1U],(ref)->addr[0U],\
        (ref)->type

/* Macro to Copy a BD_ADDR from a Source to Destination */
#define BT_ESL_COPY_BD_ADDR_AND_TYPE(dest,src)\
        BT_ESL_COPY_TYPE((dest)->type,(src)->type)\
        BT_ESL_COPY_BD_ADDR((dest)->addr,(src)->addr)

#define BT_ESL_COPY_TYPE(dest,src)\
        (dest) = (src);

#define BT_ESL_COMPARE_BD_ADDR_AND_TYPE(addr_a,addr_b)\
        ((BT_ESL_COMPARE_TYPE((addr_a)->type,(addr_b)->type)) &&\
         (BT_ESL_COMPARE_ADDR((addr_a)->addr,(addr_b)->addr)))

#define BT_ESL_COMPARE_TYPE(type_a,type_b)\
        (((type_a) == (type_b))?BT_ESL_TRUE:BT_ESL_FALSE)

#define BT_ESL_COMPARE_ADDR(addr_a,addr_b)\
        ((0 == BT_ESL_mem_cmp((addr_a), (addr_b), BT_ESL_BD_ADDR_SIZE))?BT_ESL_TRUE:BT_ESL_FALSE)

#define BT_ESL_INIT_BD_ADDR(bd_addr) \
        BT_ESL_mem_set ((bd_addr)->addr, 0, BT_ESL_BD_ADDR_SIZE); \
        (bd_addr)->type = 0U

#define BT_ESL_COPY_BD_ADDR(dest, src) \
        BT_ESL_mem_copy ((dest), (src), BT_ESL_BD_ADDR_SIZE);

#define BT_ESL_BD_ADDR_IS_NON_ZERO(addr)\
        ((0x00U == ((addr)[0U] | (addr)[1U] | (addr)[2U] | (addr)[3U] | (addr)[4U] | (addr)[5U]))?\
        BT_ESL_FALSE:BT_ESL_TRUE)

#define BT_ESL_IS_ARRAY_EMPTY(buffer, buffer_size) \
        (((0U == (buffer)[0U]) && (0 == BT_ESL_mem_cmp((buffer), &(buffer)[1U], ((buffer_size) - 1U)))) ? BT_ESL_TRUE : BT_ESL_FALSE)

/* Memory Management Primitives */
#define BT_ESL_alloc_mem(size)    EM_alloc_mem(size)
#define BT_ESL_free_mem(ptr)      EM_free_mem(ptr)


#ifdef BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY
/** Macro to Configure Limits */
#ifdef BT_ESL_SUPPORT_AP_ROLE
#define BT_ESL_INIT_DYNAMIC_CONFIG_LIMITS(x)                                                 \
       {                                                                                     \
           (x)->config_BT_ESL_MAX_GROUPS_SUPPORTED      = BT_ESL_MAX_GROUPS_SUPPORTED;       \
           (x)->config_BT_ESL_MAX_ESL_TAGS_SUPPORTED    = BT_ESL_MAX_ESL_TAGS_SUPPORTED;     \
           (x)->config_BT_ESL_MAX_DISPLAY_SUPPORTED     = BT_ESL_MAX_DISPLAY_SUPPORTED;      \
           (x)->config_BT_ESL_MAX_LED_SUPPORTED         = BT_ESL_MAX_LED_SUPPORTED;          \
           (x)->config_BT_ESL_MAX_SENSOR_SUPPORTED      = BT_ESL_MAX_SENSOR_SUPPORTED;       \
           (x)->config_BT_ESL_MAX_IMAGE_SUPPORTED       = BT_ESL_MAX_IMAGE_SUPPORTED;        \
           (x)->config_BT_ESL_MAX_NO_OF_RESPONSE        = BT_ESL_MAX_NO_OF_RESPONSE;         \
           (x)->config_BT_ESL_AP_CONFIG_TIMEOUT         = BT_ESL_AP_CONFIG_TIMEOUT;          \
           (x)->config_BT_ESL_AP_SYNC_RETRY_INTERVAL_MS = BT_ESL_AP_SYNC_RETRY_INTERVAL_MS;  \
           (x)->config_BT_ESL_AP_MAX_SYNC_RETRY_COUNT   = BT_ESL_AP_MAX_SYNC_RETRY_COUNT;    \
       }
#else /* BT_ESL_SUPPORT_AP_ROLE */
#define BT_ESL_INIT_DYNAMIC_CONFIG_LIMITS(x)
#endif /* BT_ESL_SUPPORT_AP_ROLE */

/** Macro to get Configured Limits */
#define BT_ESL_DYNAMIC_CONFIG_LIMITS(x)  \
        bt_esl_dynamic_config.config_##x

/** ESL Dynamic Global Array Definition Macro */
#define BT_ESL_DEFINE_GLOBAL_ARRAY(type, var, s) \
        type * var

/** ESL Dynamic Global Array Declaration Macro */
#define BT_ESL_DECLARE_GLOBAL_ARRAY(type, var, s) \
        extern type * var

/** ESL Dynamic Global Array Initialization Macro */
#define BT_ESL_INIT_GLOBAL_ARRAY(type, var, s, i)                 \
        {                                                         \
            (var) = (type *)BT_ESL_alloc_mem((s) * sizeof(type)); \
            EM_debug_trace(                                       \
            BT_MODULE_ID_ESL,                                     \
            "[ESL_GA]Allocated %lu bytes for %s. Ptr: %p\n",      \
            ((unsigned long)(s) * sizeof(type)),                  \
            #var, (void *)(var));                                 \
            BT_ESL_mem_set((var), (i), ((s) * sizeof(type)));     \
        }

/** ESL Dynamic Global Array De-Initialization Macro */
#define BT_ESL_DEINIT_GLOBAL_ARRAY(type, var, s)       \
        {                                              \
            if (NULL != (var))                         \
            {                                          \
                EM_debug_trace(                        \
                BT_MODULE_ID_ESL,                      \
                "[ESL_GA]Freeing %s with Allocated Ptr: %p\n", \
                #var, (void *)(var));                  \
                BT_ESL_free_mem((var));                \
                (var) = NULL;                          \
            }                                          \
        }

/** ESL Dynamic Local Array Definition Macro */
#define BT_ESL_DEFINE_LOCAL_ARRAY(type, var, s) \
        type * var

/** ESL Dynamic Local Array Declaration Macro */
#define BT_ESL_DECLARE_LOCAL_ARRAY(type, var, s) \
        extern type * var

/** ESL Dynamic Local Array Initialization Macro */
#define BT_ESL_INIT_LOCAL_ARRAY(type, var, s, i)                  \
        {                                                         \
            (var) = (type *)BT_ESL_alloc_mem((s) * sizeof(type)); \
            EM_debug_trace(                                       \
            BT_MODULE_ID_ESL,                                     \
            "[ESL_LA]: Allocated %lu bytes for %s. Ptr: %p\n",    \
            ((unsigned long)(s) * sizeof(type)),                  \
            #var, (void *)(var));                                 \
            BT_ESL_mem_set((var), (i), ((s) * sizeof(type)));     \
        }

/** ESL Dynamic Local Array De-Initialization Macro */
#define BT_ESL_DEINIT_LOCAL_ARRAY(type, var, s)        \
        {                                              \
            if (NULL != (var))                         \
            {                                          \
                EM_debug_trace(                        \
                BT_MODULE_ID_ESL,                      \
                "[ESL_LA]Freeing %s with Allocated Ptr: %p\n", \
                #var, (void *)(var));                  \
                BT_ESL_free_mem((var));                \
                (var) = NULL;                          \
            }                                          \
        }

#else /* BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY */
/** Macro to get Configured Limits */
#define BT_ESL_DYNAMIC_CONFIG_LIMITS(x) (x)

/** ESL Static Global Array Definition Macro */
#define BT_ESL_DEFINE_GLOBAL_ARRAY(type, var, s) \
        type var[(s)]

/** ESL Dynamic Global Array Declaration Macro */
#define BT_ESL_DECLARE_GLOBAL_ARRAY(type, var, s) \
        extern type var[(s)]

/** ESL Dynamic Global Array Initialization Macro */
#define BT_ESL_INIT_GLOBAL_ARRAY(type, var, s, i) \
        BT_ESL_mem_set(var, (i), ((s) * sizeof(type)))

/** ESL Dynamic Global Array De-Initialization Macro */
#define BT_ESL_DEINIT_GLOBAL_ARRAY(type, var, s)

/** ESL Dynamic Local Array Definition Macro */
#define BT_ESL_DEFINE_LOCAL_ARRAY(type, var, s) \
        type var[(s)]

/** ESL Dynamic Local Array Declaration Macro */
#define BT_ESL_DECLARE_LOCAL_ARRAY(type, var, s) \
        extern type var[(s)]

/** ESL Dynamic Local Array Initialization Macro */
#define BT_ESL_INIT_LOCAL_ARRAY(type, var, s, i) \
        BT_ESL_mem_set(var, (i), ((s) * sizeof(type)))

/** ESL Dynamic Global Array De-Initialization Macro */
#define BT_ESL_DEINIT_LOCAL_ARRAY(type, var, s)
#endif /* BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY */

/* Unreferenced variable macro to avoid compilation warnings */
#define BT_ESL_IGNORE_UNUSED_PARAM(v) (void)(v)

/* Loop for ever */
#define BT_ESL_LOOP_FOREVER() for(;;)

/* Unused return value to avoid compilation warning - MISRA C-2012 Rule 17.7 */
#define BT_ESL_IGNORE_RETURN_VALUE    void

/* -------------------------------------------- Data Structures */

/* -------------------------------------------- Function Declarations */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup EtherMind_ESL_Common_api_defs
 * \{
 */

/**
 * \name ESL common initialization routine
 * \{
 */

/**
 *  \brief To initialize Electronic Shelf Label Module.
 *
 *  \par Description
 *  API to initialize ESL Module. This is the first API that the
 *  application should call before any other API. This function
 *  initializes all the internal modules and data structures.
 *
 *  \param [in] blob
 *             this parameter shall be \ref BT_ESL_DYNAMIC_CONFIG
 *             only if \ref BT_ESL_HAVE_DYNAMIC_GLOBAL_ARRAY is defined
 *             else NULL.
 */
void BT_esl_init
     (
         /* IN */ void * blob
     );

/** \} */

/** \} */

#ifdef __cplusplus
};
#endif

#endif /* _H_BT_ESL_COMMON_ */
