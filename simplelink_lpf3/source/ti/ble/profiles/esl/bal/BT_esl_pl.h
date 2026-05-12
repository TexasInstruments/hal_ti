/**
 *  \file BT_esl_pl.h
 *
 *  Module Internal Header File contains structure definitions including tables
 *  maintained by the module
 */

 /*
  *  Copyright (C) 2025. Mindtree Ltd.
  *  All rights reserved.
  */

#ifndef _H_BT_ESL_PL_
#define _H_BT_ESL_PL_

/* --------------------------------------------- Header File Inclusion */
#include "BT_esl_api.h"

/* --------------------------------------------- Global Definitions */
/**
 * \brief Incomplete list of 16-bit Service Class UUIDs.
 *
 * \par Description
 * This data type indicates that the advertising or scan response data contains
 * an incomplete list of 16-bit Service Class UUIDs. Additional UUIDs may be
 * available but are not included in the current data.
 */
/**
 * \addtogroup EtherMind_ESL_BAL_Constants
 * \{
 */
/**
 * \name ESL Bluetooth SIG Assigned Numbers
 * \{
 */
#define BT_ESL_HCI_EIR_DATA_TYPE_INCOMPLETE_16_BIT_UUIDS     0x02U

/**
 * \brief Complete list of 16-bit Service Class UUIDs.
 *
 * \par Description
 * This data type indicates that the advertising or scan response data contains
 * a complete list of 16-bit Service Class UUIDs. No additional UUIDs are expected
 * beyond those included in the current data.
 */
#define BT_ESL_HCI_EIR_DATA_TYPE_COMPLETE_16_BIT_UUIDS       0x03U

/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_BAL_Macros
 * \{
 */
 /**
 * \name ESL Read Access Modes
 * \{
 */

/* Read Access Mode */
#define BT_ESL_READ_ACCESS_TYPE                   0U
#define BT_ESL_READ_LONG_ACCESS_TYPE              1U

/** \} */


#ifdef BT_ESL_SUPPORT_AP_ROLE
/**
 * \name Status of OTS Image upload
 * \{
 */
/** OTS image upload complete */
 #define OTS_IMAGE_UPLOAD_COMPLETED            0x00
/** OTS image upload object selection */
#define OTS_IMAGE_UPLOAD_OBJ_SELECTION_STATE   0x01
/** OTS image upload write state  */
#define OTS_IMAGE_UPLOAD_WRITE_STATE           0x02

/** \} */

#endif /* BT_ESL_SUPPORT_AP_ROLE */

#ifdef BT_ESL_SUPPORT_TAG_ROLE

/**
 * \name Maximum image name size
 * \{
 */
/** Maximum image name size  */
#define OBJ_IMG_NAME_MAX_SIZE 30U/*BT_OTS_OBJ_MAX_NAME_LEN*/

/** \} */

/**
 * \name OTS related ERROR codes
 * \{
 */

/** NO memory available */
#define BT_ESL_OTS_NO_MEM                       0x0001

/** \} */

#endif /* BT_ESL_SUPPORT_TAG_ROLE */

/**
 * \name ESL Platform Layer Macros
 * \{
 */
/* --------------------------------------------- Macros */
/** By default NO debug flag is enabled  */
#define ESL_PL_NO_DEBUG

/** ESL PL Module Debug Flags */
#if defined(CONFIG_ESL_PL_DEBUG_TO_CONSOLE)
#define ESL_PL_DEBUG_TO_CONSOLE
#endif /* CONFIG_BT_ESL_PL_DEBUG_TO_CONSOLE */

#ifndef ESL_PL_DEBUG_TO_CONSOLE
#ifdef ESL_PL_NO_DEBUG
/** ESL PL Error Logging Interface */
#define ESL_PL_ERR                EM_debug_null
#else /* ESL_PL_NO_DEBUG */
#ifdef VAR_ARG_IN_MACRO_NOT_SUPPORTED
/** ESL PL Error Logging Interface */
#define ESL_PL_ERR
#else /* VAR_ARG_IN_MACRO_NOT_SUPPORTED */
/** ESL PL Error Logging Interface */
#define ESL_PL_ERR(...)           EM_debug_error(BT_MODULE_ID_ESL, __VA_ARGS__)
#endif /* VAR_ARG_IN_MACRO_NOT_SUPPORTED */
#endif /* ESL_PL_NO_DEBUG */

#ifdef ESL_PL_DEBUG
#ifdef VAR_ARG_IN_MACRO_NOT_SUPPORTED
/** ESL PL Trace Logging Interface */
#define ESL_PL_TRC
/** ESL PL Information Logging Interface */
#define ESL_PL_INF

/** ESL PL Debug Dump Interface */
#define ESL_debug_dump_bytes(data, datalen)

#else /* VAR_ARG_IN_MACRO_NOT_SUPPORTED */
/** ESL PL Trace Logging Interface */
#define ESL_PL_TRC(...)           EM_debug_trace(BT_MODULE_ID_ESL,__VA_ARGS__)
/** ESL PL Information Logging Interface */
#define ESL_PL_INF(...)           EM_debug_info(BT_MODULE_ID_ESL,__VA_ARGS__)

/** ESL PL Debug Dump Interface */
#define ESL_debug_dump_bytes(data, datalen) EM_debug_dump_bytes(BT_MODULE_ID_ESL, (data), (datalen))

#endif /* VAR_ARG_IN_MACRO_NOT_SUPPORTED */
#else /* ESL_PL_DEBUG */
/** ESL PL Trace Logging Interface */
#define ESL_PL_TRC                EM_debug_null
/** ESL PL Information Logging Interface */
#define ESL_PL_INF                EM_debug_null

/** ESL PL Debug Dump Interface */
#define ESL_debug_dump_bytes(data, datalen)

#endif /* ESL_PL_DEBUG */

#else /* ESL_PL_DEBUG_TO_CONSOLE */
/** ESL PL Error Logging Interface */
#define ESL_PL_ERR(...)                                CONSOLE_ERR(__VA_ARGS__);CONSOLE_ERR("\n")
/** ESL PL Trace Logging Interface */
#define ESL_PL_TRC(...)                                CONSOLE_TRC(__VA_ARGS__);CONSOLE_TRC("\n")
/** ESL PL Information Logging Interface */
#define ESL_PL_INF(...)                                CONSOLE_INF(__VA_ARGS__);CONSOLE_INF("\n")
#endif /* ESL_PL_DEBUG_TO_CONSOLE */

#ifdef BT_ESL_SUPPORT_AP_ROLE
#endif /* BT_ESL_SUPPORT_AP_ROLE */

#ifdef BT_ESL_SUPPORT_TAG_ROLE
#endif /* BT_ESL_SUPPORT_TAG_ROLE */

/** ESL PL - ATT Status Codes */
/** ATT success response */
#define BT_ESL_ATT_SUCCESS                                   BT_ESL_API_SUCCESS
/** ESL PL - ATT Error codes */
/** ESL PL ERR ID */
#define BT_ESL_PL_ERR_ID                                      0x0300U
/** ATT parameter not allowed */
#define BT_ESL_ATT_PARAM_VAL_NOT_ALLOWED                     (0x0013U | BT_ESL_PL_ERR_ID)
/** ATT invalid offset */
#define BT_ESL_ATT_INVALID_OFFSET                            (0x0007U | BT_ESL_PL_ERR_ID)
/** ATT invalid attribute length  */
#define BT_ESL_ATT_INVALID_ATTRIBUTE_LEN                     (0x000DU | BT_ESL_PL_ERR_ID)

/** \} */

/** \} */

/**
 * \addtogroup EtherMind_ESL_BAL_Structures
 * \{
 */

/**
 * \name ESL Bluetooth Device Address Structure
 * \{
 */
/* --------------------------------------------- Data Types/ Structures */
/**
 * \brief Platform Initialization complete callback
 *
 * \par Description
 * Callback for notifying that PL has been initialized.
 *
 * \param err API_SUCESS on success or (negative) error code otherwise.
 *
 * \param blob stack specific error.
 */
typedef void (*PL_INIT_COMPLETE_CB)(UINT16 err, void * blob);

/**
 * \brief platform MTU exchange complete callback
 *
 * \par Description
 * Callback for notifying the result of the MTU exchange operation.
 *
 * \param peer_addr Pointer to the Bluetooth address of the peer device.
 * \param mtu Negotiated MTU size if the exchange was successful, or default MTU size otherwise.
 */
typedef void (*PL_MTU_EXCHANGE_COMPLETE_CB)(BT_ESL_BD_ADDR* peer_addr, UINT16 mtu);

#ifdef BT_ESL_SUPPORT_AP_ROLE
/**
 * \brief Parameters for configuring periodic advertising.
 *
 * \par Description
 * This structure defines the parameters used to configure periodic advertising,
 * including intervals, subevent details, and response slot timings.
 */
typedef struct _BT_ESL_PERIODIC_ADV_PARAMS
{
    /** Minimum advertising interval for periodic advertising (in 1.25 ms units). */
    UINT16 periodic_advertising_interval_min;

    /** Maximum advertising interval for periodic advertising (in 1.25 ms units). */
    UINT16 periodic_advertising_interval_max;

    /** Properties of the periodic advertisement (e.g., include Tx power). */
    UINT16 periodic_adv_prty;

    /** Number of subevents in each periodic advertising event. */
    UCHAR num_subevents;

    /** Interval between subevents (in 1.25 ms units). */
    UCHAR subevent_interval;

    /** Delay between the advertising packet in a subevent and the first response slot (in 1.25 ms units). */
    UCHAR response_slot_delay;

    /** Time between consecutive response slots (in 1.25 ms units). */
    UCHAR response_slot_spacing;

    /** Number of response slots in each subevent. */
    UCHAR num_response_slots;

} BT_ESL_PERIODIC_ADV_PARAMS;

/**
 * \brief Register OTS callback for ESL.
 *
 * \par Description
 * This function registers a callback for OTS operations in the ESL context.
 *
 * \param [in] bd_addr Pointer to the Bluetooth address of the ESL device.
 * \param [in] result  Status of the discovery operation.
 */
typedef void (*BT_ESL_OTS_DISCOVERY_COMPLETE) (BT_ESL_BD_ADDR * bd_addr, UINT16 result);

/**
 * \brief Callback for OTS image upload completion.
 *
 * \par Description
 * This function is called when an image upload operation is completed.
 *
 * \param [in] bd_addr Pointer to the Bluetooth address of the ESL device.
 * \param [in] state State of the image upload operation.
 * \param [in] blob Pointer to the image data blob.
 */
typedef void (*BT_ESL_OTS_IMAGE_UPLOAD_COMPLETE) (BT_ESL_BD_ADDR * bd_addr, UCHAR state, void * blob);

/** ESL Object Transfer Client Callbacks */
typedef struct _BT_ESL_OTS_CALLBACK
{
    /** OTS discovery complete callback */
    BT_ESL_OTS_DISCOVERY_COMPLETE discovery_complete;

    /** OTS image upload complete callback */
    BT_ESL_OTS_IMAGE_UPLOAD_COMPLETE image_upload_complete;

} BT_ESL_OTS_CALLBACK;

#endif /* BT_ESL_SUPPORT_AP_ROLE */

#ifdef BT_ESL_SUPPORT_TAG_ROLE

/**
 * \brief OTS server object selected callback for ESL Tag
 *
 * \par Description
 * This function is called when an object is selected on the OTS server.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device that selected the object.
 * \param image_index Index of the selected image.
 */
typedef void (*IMAGE_SELECTED_CB)(BT_ESL_BD_ADDR *bd_addr, UCHAR image_index);

/**
 * \brief OTS server image upload complete callback for ESL Tag
 *
 * \par Description
 * This function is called when an image upload is completed on the OTS server.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device that uploaded the image.
 * \param image_index Index of the uploaded image.
 * \param data Pointer to the uploaded image data.
 * \param len Length of the uploaded image data.
 */
typedef API_RESULT (*IMAGE_WRITE_CB) (BT_ESL_BD_ADDR *bd_addr, UCHAR image_index, void * data, UINT32 len, UINT32 offset, UINT32 rem);

/**
 * \brief OTS server callback structure for ESL Tag
 *
 * \par Description
 * This structure contains callbacks for image selection and image upload completion.
 */
typedef struct _BT_ESL_OTS_SERVER_CALLBACK
{
    /** Callback for image selection */
    IMAGE_SELECTED_CB image_selected;

    /** Callback for image upload completion */
    IMAGE_WRITE_CB image_write;

} BT_ESL_OTS_SERVER_CALLBACK;

/**
 * \brief OTS server metadata structure for ESL Tag
 */
typedef struct _BT_ESL_OTS_METADATA
{
    /** Name */
    CHAR name[OBJ_IMG_NAME_MAX_SIZE];

    /** Current size */
    UINT32 cur_size;

    /** Allocated size */
    UINT32 alloc_size;

} BT_ESL_OTS_METADATA;

/** \} */

/** \} */

#endif /* BT_ESL_SUPPORT_TAG_ROLE */


/* --------------------------------------------- Functions */
/**
 * \addtogroup EtherMind_ESL_BAL_api_defs
 * \{
 */

/**
 * \name ESL Platform Layer Functions
 * \{
 */

/**
 * \brief Initializes the ESL platform layer.
 *
 * \par Description
 * This function initializes the ESL platform layer and starts the Bluetooth stack.
 *
 * \param cb Callback function to notify the upper layer about the initialization result.
 *
 * \return BT_ESL_API_SUCCESS if the initialization starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_init_pl(PL_INIT_COMPLETE_CB cb);

/**
 * \brief Creates a connection with a specified device.
 *
 * \par Description
 * This function initiates a connection with the specified device using the provided
 * Bluetooth address.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to connect.
 *
 * \return BT_ESL_API_SUCCESS if the connection starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_create_connection_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Disconnects from a connected device.
 *
 * \par Description
 * This function initiates a disconnection from the specified device.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to disconnect.
 *
 * \return BT_ESL_API_SUCCESS if the disconnection starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_disconnect_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Gets the current absolute time in milliseconds.
 *
 * \par Description
 * This function fetches the current absolute time..
 *
 * \return The current absolute time in milliseconds as a UINT32.
 */
UINT32 BT_esl_get_current_time_pl(void);

/**
 * \brief Sets the current absolute time.
 *
 * \par Description
 * This function sets the current absolute time.
 *
 * \param current_absolute_time The absolute time in milliseconds to set.
 */
void BT_esl_set_current_time_pl(UINT32 current_absolute_time);

/**
 * \brief Initiates an MTU exchange with a connected device.
 *
 * \par Description
 * This function initiates the GATT MTU exchange procedure for a device specified
 * by its Bluetooth address.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device.
 * \param mtu Ignored parameter (MTU negotiation is handled automatically).
 * \param cb Callback function to inform the upper layer about the MTU exchange result.
 *
 * \return BT_ESL_API_SUCCESS if the MTU exchange starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_gatt_exchange_mtu_pl
           (
                BT_ESL_BD_ADDR             * peer_addr,
                UINT16                       mtu,
                PL_MTU_EXCHANGE_COMPLETE_CB  cb
           );

/**
 * \brief Encrypts data using the provided key material.
 *
 * \par Description
 * This function encrypts the input payload using the specified key material.
 * The encrypted output is stored in the provided buffer.
 *
 * \param key_material Pointer to the key material used for encryption.
 * \param payload Pointer to the data to be encrypted.
 * \param payload_datalen Length of the input payload data.
 * \param encrypted_data Pointer to the buffer where the encrypted data will be stored.
 *
 * \return BT_ESL_API_SUCCESS if encryption is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_encrypt_data_pl
           (
               /* IN */  BT_ESL_KEY_MATERIAL* key_material,
               /* IN */  UCHAR * payload,
               /* IN */  UINT16  payload_datalen,
               /* OUT */ UCHAR * encrypted_data
           );

/**
 * \brief Decrypts encrypted data using the provided key material.
 *
 * \par Description
 * This function decrypts the input encrypted payload using the specified key material.
 * The decrypted output is stored in the provided buffer.
 *
 * \param key_material Pointer to the key material used for decryption.
 * \param encrypted_payload Pointer to the encrypted data to be decrypted.
 * \param encrypted_payload_datalen Length of the encrypted payload data.
 * \param decrypted_payload Pointer to the buffer where the decrypted data will be stored.
 * \param decrypted_payload_len Length of the buffer allocated for decrypted data.
 *
 * \return BT_ESL_API_SUCCESS if decryption is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_decrypt_data_pl
           (
               /* IN */  BT_ESL_KEY_MATERIAL* key_material,
               /* IN */  UCHAR  * encrypted_payload,
               /* IN */  UINT16   encrypted_payload_datalen,
               /* OUT */ UCHAR  * decrypted_payload,
               /* IN */  UINT16   decrypted_payload_len
           );


/**
 * \brief Initiates pairing/bonding with a connected device.
 *
 * \par Description
 * This function initiates the SMP pairing procedure with the specified device
 * to establish a bonded connection for secure communication.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device to pair with.
 *
 * \return BT_ESL_API_SUCCESS if pairing starts successfully, BT_ESL_API_FAILURE otherwise.
 *
 * \note Here we are using security level 2 (BT_SECURITY_L2) for pairing required for ESL.
 */
API_RESULT BT_esl_start_pairing_pl(BT_ESL_BD_ADDR * peer_addr);

/**
 * \brief Unpairs a device.
 *
 * \par Description
 * This function unpairs the specified device, removing any bonded information.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to unpair.
 *
 * \return BT_ESL_API_SUCCESS if unpairing is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_unpair_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Checks if a device is bonded.
 *
 * \par Description
 * This function checks if the device with the given Bluetooth address is bonded.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to check.
 * \param is_bonded BT_ESL_TRUE if the device is bonded, BT_ESL_FALSE otherwise.
 *
 * \return BT_ESL_API_SUCCESS if the check is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_device_is_bonded_pl
           (
               /* IN */  BT_ESL_BD_ADDR * bd_addr,
               /* OUT */ UCHAR          * is_bonded
           );

/**
 * \brief Finds an advertising element in the provided advertising data.
 *
 * \par Description
 * This function searches for an advertising element of the specified type
 * within the given advertising data buffer and copies the element's data
 * into the provided buffer.
 *
 * \param ad_type The advertising type to search for.
 * \param adv_data Pointer to the advertising data buffer.
 * \param adv_length Length of the advertising data buffer.
 * \param ad_element Pointer to the buffer where the advertising element data will be copied.
 * \param ad_element_data_length Pointer to store the length of the advertising element data.
 *
 * \return BT_ESL_API_SUCCESS if the advertising element is found else BT_ESL_API_FAILURE.
 */
API_RESULT BT_esl_find_ad_element_pl
           (
                /* IN */  UCHAR     ad_type,
                /* IN */  UCHAR   * adv_data,
                /* IN */  UINT8     adv_length,
                /* OUT */ UCHAR   * ad_element,
                /* OUT */ UINT16  * ad_element_data_length
           );

#ifdef BT_ESL_SUPPORT_AP_ROLE
/**
 * \brief Registers the OTS callback for ESL.
 *
 * \par Description
 * This function registers the OTS callback for ESL operations.
 *
 * \param callback Pointer to the OTS callback structure.
 *
 * \return BT_ESL_API_SUCCESS if the registration is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_register_ots_callback_pl(BT_ESL_OTS_CALLBACK * callback);

/**
 * \brief Discovers the OTS service on a specified device.
 *
 * \par Description
 * This function initiates the discovery of the OTS service on the device specified by its Bluetooth address.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to discover.
 *
 * \return BT_ESL_API_SUCCESS if the discovery starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_discover_ots_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Configure the CCCD of OTS chars(OACP/OLCP) on a specified device.
 *
 * \par Description
 * This function Configure the CCCD of OTS chars(OACP/OLCP) on a specified device.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to discover.
 *
 * \return BT_ESL_API_SUCCESS if the discovery starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_config_ots_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Upload image to ESL by Image_Index
 *
 * \par Description
 * This function uploads image data to the ESL image slot specified by image_index.
 * It reads the Max_Image_Index from the ESL Image Information characteristic, checks bounds,
 * selects the corresponding OTS object, and writes the image data.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to discover.
 * \param image_index Index of the image slot to upload to (0..Max_Image_Index).
 * \param image_data Pointer to the image data buffer.
 * \param image_len Length of the image data buffer.
 * \return BT_ESL_API_SUCCESS if upload started, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_upload_image_pl
           (
                BT_ESL_BD_ADDR * bd_addr,
                UCHAR            image_index,
                const UCHAR    * image_data,
                UINT16           image_len
           );

/**
 * \brief Starts a passive BLE scan to discover devices.
 *
 * \par Description
 * Starts any ongoing scan and starts a new passive scan.
 *
 * \return BT_ESL_API_SUCCESS if the scan starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_start_scan_pl(void);

/**
 * \brief Stops an ongoing BLE scan.
 *
 * \par Description
 * This function stops any active BLE scan operation.
 *
 * \return BT_ESL_API_SUCCESS if the scan is stopped successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_stop_scan_pl(void);

/**
 * \brief Initiates a connection using PAwR.
 *
 * \par Description
 * This function starts the connection procedure using PAwR with the specified device.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to connect.
 * \param subevent Subevent number to be used for the connection.
 *
 * \return BT_ESL_API_SUCCESS if the connection starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_pawr_connect_pl(BT_ESL_BD_ADDR * bd_addr, UCHAR subevent);

/**
 * \brief Starts periodic advertising with the specified parameters.
 *
 * \par Description
 * This function initializes and starts a periodic advertising set using the provided
 * parameters.
 *
 * \param padv_params Structure containing the periodic advertising parameters.
 *
 * \return BT_ESL_API_SUCCESS if periodic advertising starts successfully, BT_ESL_API_FAILURE otherwise.
 *
 * \note If periodic advertising is already started, the function will return BT_ESL_API_FAILURE.
 *       Ensure that the Bluetooth stack is initialized before calling this function.
 */
API_RESULT BT_esl_start_periodic_adv_pl(BT_ESL_PERIODIC_ADV_PARAMS padv_params);

/**
 * \brief Stops periodic advertising and deletes the advertising set.
 *
 * \par Description
 * This function stops both extended and periodic advertising for the current advertising set
 * and deletes the advertising set to free resources.
 *
 * \return BT_ESL_API_SUCCESS if periodic advertising is stopped and the advertising set is deleted successfully,
 *         BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_stop_periodic_adv_pl(void);

/**
 * \brief Sets subevent data for periodic advertising.
 *
 * \par Description
 * This function configures subevent data for periodic advertising.
 *
 * \param subevent_data_params Pointer to an array of subevent data parameters.
 * \param num_subevents Number of subevents to configure.
 *
 * \return BT_ESL_API_SUCCESS if subevent data is set successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_set_subevent_data_pl
           (
                BT_ESL_SUBEVENT_DATA_PARAMS * subevent_data_params,
                UCHAR                         num_subevents
           );

/**
 * \brief Performs periodic advertising information transfer.
 *
 * \par Description
 * This function initiates a periodic advertising information transfer
 * on a device specified by its Bluetooth address.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to perform the transfer.
 * \param uuid The UUID of the service.
 *
 * \return BT_ESL_API_SUCCESS if the transfer operation starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_padv_set_info_transfer_pl
           (
               BT_ESL_BD_ADDR * bd_addr,
               UINT16           uuid
           );

/**
 * \brief Discovers the ESL service on a connected device.
 *
 * \par Description
 * This function initiates GATT service discovery for the ESL service on a device
 * specified by its Bluetooth address.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to discover the ESL service.
 *
 * \return BT_ESL_API_SUCCESS if service discovery starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_discover_esl_service_pl(BT_ESL_BD_ADDR * bd_addr);

/**
 * \brief Reads a GATT characteristic from a connected device.
 *
 * \par Description
 * This function initiates a GATT read operation for a specific attribute handle
 * on a device specified by its Bluetooth address.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device to read the characteristic.
 * \param attr_handle The handle of the characteristic to read.
 * \param read_mode The mode of the read operation.
 *
 * \return BT_ESL_API_SUCCESS if the read operation starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_gatt_read_characteristic_pl
           (
               BT_ESL_BD_ADDR * peer_addr,
               UINT16           attr_handle,
               UCHAR            read_mode
           );

/**
 * \brief Writes data to a GATT characteristic on a connected device.
 *
 * \par Description
 * This function initiates a GATT write operation for a specific attribute handle
 * on a device specified by its Bluetooth address.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device to write the characteristic.
 * \param attr_handle The handle of the characteristic to write.
 * \param data Pointer to the data to be written.
 * \param length Length of the data to be written.
 *
 * \return BT_ESL_API_SUCCESS if the write operation starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_gatt_write_characteristic_pl
           (
               BT_ESL_BD_ADDR * peer_addr,
               UINT16           attr_handle,
               UCHAR          * data,
               UINT16           length
           );

/**
 * \brief Writes data to a GATT characteristic on a connected device without expecting a response.
 *
 * \par Description
 * This function initiates a GATT write operation for a specific attribute handle
 * on a device specified by its Bluetooth address. The operation does not expect
 * a response from the device.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device to write the characteristic.
 * \param attr_handle The handle of the characteristic to write.
 * \param data Pointer to the data to be written.
 * \param length Length of the data to be written.
 *
 * \return BT_ESL_API_SUCCESS if the write operation starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_gatt_write_without_response_pl
           (
               BT_ESL_BD_ADDR * peer_addr,
               UINT16           attr_handle,
               UCHAR          * data,
               UINT16           length
           );

/**
 * \brief Writes to a CCCD (Client Characteristic Configuration Descriptor).
 *
 * \par Description
 * This function initiates a GATT write operation for a specific CCCD handle
 * on a device specified by its Bluetooth address.
 *
 * \param peer_addr Pointer to the Bluetooth address of the device to write the CCCD.
 * \param attr_handle The handle of the Attribute
 * \param cccd_handle The handle of the CCCD to write.
 * \param cccd_value The value to write to the CCCD (e.g., enable notifications or indications).
 *
 * \return BT_ESL_API_SUCCESS if the write operation starts successfully, BT_ESL_API_FAILURE otherwise.\
 */
API_RESULT BT_esl_gatt_write_cccd_pl
           (
               BT_ESL_BD_ADDR * peer_addr,
               UINT16           attr_handle,
               UINT16           cccd_handle,
               UINT16           cccd_value
           );

/**
 * \brief Discovers the DIS service on a specified device.
 *
 * \par Description
 * This function initiates the discovery of the DIS service on the device specified by its Bluetooth address.
 *
 * \param bd_addr Pointer to the Bluetooth address of the device to discover.
 *
 * \return BT_ESL_API_SUCCESS if the discovery starts successfully, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_discover_dis_pl(BT_ESL_BD_ADDR * bd_addr);

#ifdef APPL_ESL_DO_NOT_USE_DEFAULT_CONN_PARAMS
/**
 * \brief Set preferred connection interval for LE connections.
 *
 * \param interval_min  Minimum connection interval (in units of 1.25 ms).
 * \param interval_max  Maximum connection interval (in units of 1.25 ms).
 */
void BT_esl_set_preferred_conn_interval_pl(UINT16 interval_min, UINT16 interval_max);
#endif /* APPL_ESL_DO_NOT_USE_DEFAULT_CONN_PARAMS */

#endif /* BT_ESL_SUPPORT_AP_ROLE */

#ifdef BT_ESL_SUPPORT_TAG_ROLE

/**
 * \brief Initializes the OTS server for ESL Tag
 *
 * \par Description
 * This function initializes the OTS server instance and sets up the OTS callbacks.
 *
 * \return return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_ots_init_pl(void);

/**
 * \brief Registers the OTS server callback for ESL Tag
 *
 * \par Description
 * This function registers the OTS server callback for ESL Tag operations.
 *
 * \param callback Pointer to the OTS server callback structure.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_register_ots_server_callback_pl(BT_ESL_OTS_SERVER_CALLBACK *callback);

/**
 * \brief Creates OTS objects for ESL Tag
 *
 * \par Description
 * This function creates OTS objects for ESL Tag based on the provided metadata.
 *
 * \param no_of_objects Number of objects to create.
 * \param obj_meta_data Reference to the array of metadata for the objects.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
*/
API_RESULT BT_esl_ots_create_obj_pl
           (
                UCHAR                 no_of_objects,
                BT_ESL_OTS_METADATA * obj_meta_data
           );

/**
 * \brief Updates the complete name of the ESL image object.
 *
 * \par Description
 * This function sets the complete name for the ESL image object after upload.
 *
 * \param complete_name Pointer to the name string.
 * \param length Length of the name string.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_update_complete_name_pl(UCHAR * complete_name, UINT16 length);

/**
 * \brief Starts BLE advertising for ESL Tag.
 *
 * \par Description
 * This function initiates BLE advertising for the ESL Tag role.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_start_advertise_pl(void);

/**
 * \brief Stops BLE advertising for ESL Tag.
 *
 * \par Description
 * This function stops any ongoing BLE advertising for the ESL Tag role.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_stop_advertise_pl(void);

/**
 * \brief Synchronizes ESL Tag with subevent configuration.
 *
 * \par Description
 * This function initiates synchronization with the specified subevent configuration.
 *
 * \param periodic_adv_properties Properties of the periodic advertising.
 * \param num_subevents Number of subevents.
 * \param subevent Pointer to subevent data.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_sync_with_subevent_pl
           (
               UINT16    periodic_adv_properties,
               UCHAR     num_subevents,
               UCHAR   * subevent
           );

/**
 * \brief Sets response data for a specific subevent and slot.
 *
 * \par Description
 * This function sets the response data to be sent during a specific subevent and slot.
 *
 * \param periodic_event_counter Counter value for the periodic event.
 * \param request_subevent Subevent index for the request.
 * \param response_subevent Subevent index for the response.
 * \param response_slot Slot index for the response.
 * \param response_data_length Length of the response data.
 * \param response_data Pointer to the response data.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_set_response_data_pl
           (
               UINT16  periodic_event_counter,
               UCHAR   request_subevent,
               UCHAR   response_subevent,
               UCHAR   response_slot,
               UCHAR   response_data_length,
               UCHAR * response_data
           );

/**
 * \brief Terminates synchronization with the ESL AP.
 *
 * \par Description
 * This function stops synchronization with the Access Point.
 *
 * \return BT_ESL_API_SUCCESS if termination is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_terminate_sync_pl(void);

/**
 * \brief Unsubscribes from PAwR sync transfer.
 *
 * \par Description
 * This function unsubscribes the ESL Tag from periodic advertising sync transfer.
 *
 * \param peer_bd_address Pointer to the Bluetooth address of the peer device.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_padv_sync_transfer_unsubscribe_pl
           (
               BT_ESL_BD_ADDR * peer_bd_address
           );

/**
 * \brief Subscribes to PAwR sync transfer.
 *
 * \par Description
 * This function subscribes the ESL Tag to periodic advertising sync transfer.
 *
 * \param peer_bd_address Pointer to the Bluetooth address of the peer device.
 *
 * \return BT_ESL_API_SUCCESS if subscription is successful, BT_ESL_API_FAILURE otherwise.
 */
API_RESULT BT_esl_padv_sync_transfer_subscribe_pl
           (
               BT_ESL_BD_ADDR * peer_bd_address
           );

/**
 * \brief Sends a GATT notification to a connected device.
 *
 * \par Description
 * This function sends a GATT notification with the specified data.
 *
 * \param peer_addr Pointer to the Bluetooth address of the peer device.
 * \param data Pointer to the data to be notified.
 * \param datalen Length of the data.
 *
 * \return BT_ESL_API_SUCCESS on success, BT_ESL_API_FAILURE on failure.
 */
API_RESULT BT_esl_gatt_notify_pl
           (
               BT_ESL_BD_ADDR * peer_addr,
               UCHAR          * data,
               UINT16           datalen
           );
/** \} */

/** \} */

#endif /* BT_ESL_SUPPORT_TAG_ROLE */

#endif /* _H_BT_ESL_PL_ */
