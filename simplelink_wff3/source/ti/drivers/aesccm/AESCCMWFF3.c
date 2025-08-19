/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <ti/drivers/aesccm/AESCCMWFF3.h>
#include <ti/drivers/AESCCM.h>
#include <ti/drivers/AESCommon.h>
#include <ti/drivers/cryptoutils/aes/AESCommonWFF3.h>
#include <ti/drivers/cryptoutils/cryptokey/CryptoKey.h>
#include <ti/drivers/cryptoutils/utils/CryptoUtils.h>

#include <ti/drivers/dpl/DebugP.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)

#include <ti/drivers/cryptoutils/hsm/HSMWFF3.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_asset.h>

#if (defined(__IAR_SYSTEMS_ICC__) || defined(__TI_COMPILER_VERSION__))
    #include <arm_acle.h>
    #define REV32 __rev
#else
    #define REV32 __builtin_bswap32
#endif

#define PSA_SYM_MODE_GCM_NONE 0U

/* Size of state asset for GCM/CCM continuation */
#define KEY_TEMP_ASSET_SIZE 48U

/* Note: The AES-CCM one-step polling operations are specifically designed
 * to optimize execution speed at the expense of code re-use and size.
 */

#define B0_FLAGS_CCM_HAS_ADATA 0x40 /* bit 6 in the Flags field of B0 */

/**
 * This AES CCM implementation limits AAD length to 0xFEFF (65279-bytes) to
 * simplify the code and improve execution speed.
 */
/* 0xFEFF bytes, For 0 < l(a) <= (2^16 - 2^8) - 1 */
#define B1_AAD_LENGTH_SMALL_LIMIT ((1UL << 16) - (1UL << 8) - 1UL)

#define B1_AAD_LENGTH_SMALL_BYTES 2U /* If 0 < l(a) < (2^16 - 2^8), the length field is encoded as two octets */
#define B1_AAD_SMALL_BYTES        (AES_BLOCK_SIZE - B1_AAD_LENGTH_SMALL_BYTES)

/**
 * The threshold at which blocking and callback mode transfers will utilize DMA.
 * For data lengths below this threshold, polling CPU R/W will be used instead
 * of DMA. With task switching and interrupt overhead, it is inefficient to
 * utilize DMA for shorter length operations.
 * The threshold value must be a multiple of AES_BLOCK_SIZE.
 */
#define AESCCMWFF3_DMA_SIZE_THRESHOLD (1U * AES_BLOCK_SIZE)

/* Forward declarations */
static int_fast16_t AESCCMWFF3HSM_setupEncrypt(AESCCM_Handle handle,
                                               const CryptoKey *key,
                                               size_t totalAADLength,
                                               size_t totalPlaintextLength,
                                               size_t macLength);
static int_fast16_t AESCCMWFF3HSM_setupDecrypt(AESCCM_Handle handle,
                                               const CryptoKey *key,
                                               size_t totalAADLength,
                                               size_t totalPlaintextLength,
                                               size_t macLength);
static int_fast16_t AESCCMWFF3HSM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation);
static int_fast16_t AESCCMWFF3HSM_addData(AESCCM_Handle handle,
                                          AESCCM_OperationType operationType,
                                          AESCCM_OperationUnion *operation,
                                          const uint8_t *input,
                                          uint8_t *output,
                                          size_t inputLength);
static int_fast16_t AESCCMWFF3HSM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMWFF3HSM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMWFF3HSM_oneStepOperation(AESCCM_Handle handle,
                                                   AESCCM_OneStepOperation *operation,
                                                   AESCCM_OperationType operationType);
static int_fast16_t AESCCMWFF3HSM_performFinalizeChecks(const AESCCMWFF3_Object *object,
                                                        const AESCCM_SegmentedFinalizeOperation *operation);
static int_fast16_t AESCCMWFF3HSM_setupSegmentedOperation(AESCCMWFF3_Object *object,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength,
                                                          size_t macLength);
static int_fast16_t AESCCMWFF3HSM_createTempAssetID(AESCCM_Handle handle, AESCCM_Mode direction);
static inline int_fast16_t AESCCMWFF3HSM_processOneStepOperation(AESCCM_Handle handle);
static int_fast16_t AESCCMWFF3HSM_freeTempAssetID(AESCCM_Handle handle);

/*
 *  ======== AESCCMWFF3_getObject ========
 */
static inline AESCCMWFF3_Object *AESCCMWFF3_getObject(AESCCM_Handle handle)
{
    AESCCMWFF3_Object *object = (AESCCMWFF3_Object *)handle->object;
    DebugP_assert(object);

    return object;
}

/*
 *  ======== AESCCM_init ========
 */
void AESCCM_init(void)
{
    HSMWFF3_constructRTOSObjects();
}

/*
 *  ======== AESCCM_construct ========
 */
AESCCM_Handle AESCCM_construct(AESCCM_Config *config, const AESCCM_Params *params)
{
    DebugP_assert(config);

    AESCCM_Handle handle      = config;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* Initialize and boot HSM */
    if (HSMWFF3_init() != HSMWFF3_STATUS_SUCCESS)
    {
        /* Upon HSM Boot failure, the AES-CCM Driver stores the failure status in the object
         * This is done so that users of the AES-CCM Driver do not get a NULL handle and still can use
         * the driver in LAES mode.
         */
        object->hsmStatus = HSMWFF3_STATUS_ERROR;
    }
    else
    {
        object->hsmStatus = HSMWFF3_STATUS_SUCCESS;

        object->segmentedOperationInProgress = false;
    }

    if (object->hsmStatus == HSMWFF3_STATUS_ERROR)
    {
        handle = NULL;
    }

    /* If params are NULL, use defaults */
    if (params == NULL)
    {
        params = &AESCCM_defaultParams;
    }

    DebugP_assert((params->returnBehavior != AESCCM_RETURN_BEHAVIOR_CALLBACK) || (params->callbackFxn != NULL));

    object->callbackFxn    = params->callbackFxn;
    object->returnBehavior = (AES_ReturnBehavior)params->returnBehavior;

    if (object->returnBehavior == AES_RETURN_BEHAVIOR_BLOCKING)
    {
        object->semaphoreTimeout = params->timeout;
    }
    else
    {
        object->semaphoreTimeout = SemaphoreP_NO_WAIT;
    }

    return handle;
}

/*
 *  ======== AESCCM_close ========
 */
void AESCCM_close(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* Set callback function pointer to NULL.
     * Will set it to correct value in AESCBC_construct() */
    object->callbackFxn = NULL;
}

/*
 *  ======== AESCCM_oneStepEncrypt ========
 */
int_fast16_t AESCCM_oneStepEncrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    int_fast16_t status = AESCCM_STATUS_ERROR;

    if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) || (operation->key->encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_ENCRYPT);
    }

    return status;
}

/*
 *  ======== AESCCM_oneStepDecrypt ========
 */
int_fast16_t AESCCM_oneStepDecrypt(AESCCM_Handle handle, AESCCM_OneStepOperation *operation)
{
    int_fast16_t status = AESCCM_STATUS_ERROR;

    if ((operation->key->encoding == CryptoKey_PLAINTEXT_HSM) || (operation->key->encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_oneStepOperation(handle, operation, AESCCM_OP_TYPE_ONESTEP_DECRYPT);
    }

    return status;
}

/*
 *  ======== AESCCM_setupEncrypt ========
 */
int_fast16_t AESCCM_setupEncrypt(AESCCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength,
                                 size_t macLength)
{
    DebugP_assert(handle);
    int_fast16_t status = AESCCM_STATUS_ERROR;

    if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_setupEncrypt(handle, key, totalAADLength, totalPlaintextLength, macLength);
    }

    return status;
}

/*
 *  ======== AESCCM_setupDecrypt ========
 */
int_fast16_t AESCCM_setupDecrypt(AESCCM_Handle handle,
                                 const CryptoKey *key,
                                 size_t totalAADLength,
                                 size_t totalPlaintextLength,
                                 size_t macLength)
{
    DebugP_assert(handle);
    int_fast16_t status = AESCCM_STATUS_ERROR;

    if ((key->encoding == CryptoKey_PLAINTEXT_HSM) || (key->encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_setupDecrypt(handle, key, totalAADLength, totalPlaintextLength, macLength);
    }

    return status;
}

/*
 *  ======== AESCCM_setLengths ========
 */
int_fast16_t AESCCM_setLengths(AESCCM_Handle handle, size_t aadLength, size_t plaintextLength, size_t macLength)
{
    DebugP_assert(handle);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* This shouldn't be called after addXXX() or finalizeXXX() */
    DebugP_assert(object->operationType == AESCCM_OPERATION_TYPE_DECRYPT ||
                  object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT);

    /* Don't continue the segmented operation if there
     * was an error or a cancellation
     */
    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((aadLength == 0U) && (plaintextLength == 0U))
    {
        return AESCCM_STATUS_ERROR;
    }

    object->totalAADLength             = aadLength;
    object->totalDataLength            = plaintextLength;
    object->totalCBCMACLengthRemaining = plaintextLength;
    object->totalCTRLengthRemaining    = plaintextLength;
    object->macLength                  = (uint8_t)macLength;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCM_setNonce ========
 */
int_fast16_t AESCCM_setNonce(AESCCM_Handle handle, const uint8_t *nonce, size_t nonceLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

    /* The nonce length must be 7 to 13 bytes long */
    if ((nonceLength < 7U) || (nonceLength > 13U))
    {
        return AESCCM_STATUS_ERROR;
    }

    object->nonce       = nonce;
    object->nonceLength = (uint8_t)nonceLength;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCM_generateNonce ========
 */
int_fast16_t AESCCM_generateNonce(AESCCM_Handle handle, uint8_t *nonce, size_t nonceSize, size_t *nonceLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);
    DebugP_assert(nonceSize > 0U);
    DebugP_assert(nonceLength);

    /* This feature is not currently supported */
    return AESCCM_STATUS_FEATURE_NOT_SUPPORTED;
}

/*
 *  ======== AESCCM_addAAD ========
 */
int_fast16_t AESCCM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AES_STATUS_ERROR;

    if ((object->key.encoding == CryptoKey_PLAINTEXT_HSM) || (object->key.encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_addAAD(handle, operation);
    }

    return status;
}

/*
 *  ======== AESCCM_addData ========
 */
int_fast16_t AESCCM_addData(AESCCM_Handle handle, AESCCM_SegmentedDataOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;

    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

#if (AESCommonWFF3_UNALIGNED_IO_SUPPORT_ENABLE == 0)
    /* Check word-alignment of input & output pointers */
    if (!IS_WORD_ALIGNED(operation->input) || !IS_WORD_ALIGNED(operation->output))
    {
        return AESCCM_STATUS_UNALIGNED_IO_NOT_SUPPORTED;
    }
#endif

    if ((object->key.encoding == CryptoKey_PLAINTEXT_HSM) || (object->key.encoding == CryptoKey_PLAINTEXT))
    {
        /* The input length must be a non-zero multiple of an AES block size
         * unless you are dealing with the last chunk of payload data
         */
        if ((operation->inputLength == 0U) || ((AES_NON_BLOCK_SIZE_MULTIPLE_LENGTH(operation->inputLength) > 0U) &&
                                               (operation->inputLength != object->totalDataLengthRemaining)))
        {
            return AESCCM_STATUS_ERROR;
        }

        /* The total input length must not exceed the lengths specified in
         * AESCCM_setLengths() or setupXXXX().
         */
        if (operation->inputLength > object->totalDataLengthRemaining)
        {
            return AESCCM_STATUS_ERROR;
        }
    }

    /* The AAD input length specified so far must match the total length
     * specified in the setLengths() or setupXXXX() calls.
     * All AAD input must be processed at this point.
     */
    if ((object->aadBytesProcessed != object->totalAADLength) && (object->key.encoding == CryptoKey_KEYSTORE))
    {
        return AESCCM_STATUS_ERROR;
    }

    AESCCM_OperationType operationType = AESCCM_OP_TYPE_DATA_ENCRYPT;

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) || (object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT))
    {
        operationType = AESCCM_OP_TYPE_DATA_DECRYPT;
    }

    if ((object->key.encoding == CryptoKey_PLAINTEXT_HSM) || (object->key.encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_addData(handle,
                                       operationType,
                                       (AESCCM_OperationUnion *)operation,
                                       operation->input,
                                       operation->output,
                                       operation->inputLength);
    }

    return status;
}

/*
 *  ======== AESCCM_finalizeEncrypt ========
 */
int_fast16_t AESCCM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;

    if ((object->key.encoding == CryptoKey_PLAINTEXT_HSM) || (object->key.encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_finalizeEncrypt(handle, operation);
    }

    return status;
}

/*
 *  ======== AESCCM_finalizeDecrypt ========
 */
int_fast16_t AESCCM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AES_STATUS_ERROR;

    if ((object->key.encoding == CryptoKey_PLAINTEXT_HSM) || (object->key.encoding == CryptoKey_PLAINTEXT))
    {
        status = AESCCMWFF3HSM_finalizeDecrypt(handle, operation);
    }

    return status;
}

/*
 *  ======== AESCCM_cancelOperation ========
 */
int_fast16_t AESCCM_cancelOperation(AESCCM_Handle handle)
{
    DebugP_assert(handle);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status;

    /* Cancellation is only supported in callback mode */
    if (object->returnBehavior != AES_RETURN_BEHAVIOR_CALLBACK)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Since the HSM cannot cancel an in-progress token, we must wait for the result to allow for
     * subsequent token submissions to succeed.
     */
    (void)HSMWFF3_cancelOperation();

    object->segmentedOperationInProgress = false;

    status = AESCCMWFF3HSM_freeTempAssetID(handle);
    if (status != AESCCM_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Operation pointer could be NULL if a segmented operation was setup
     * but neither AESCCM_addData or AESCCM_finalize was called.
     */
    if ((object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK) && (object->operation != NULL))
    {
        /* Call the callback function provided by the application */
        object->callbackFxn(handle, AESCCM_STATUS_CANCELED, object->operation, object->operationType);
    }

    (void)memset(object->output, 0, object->totalDataLength);

    object->aad       = NULL;
    object->input     = NULL;
    object->output    = NULL;
    object->nonce     = NULL;
    object->mac       = NULL;
    object->operation = NULL;

    object->inputLength                = 0;
    object->totalCBCMACLengthRemaining = 0;
    object->totalCTRLengthRemaining    = 0;
    object->totalAADLength             = 0;
    object->totalDataLength            = 0;
    object->aadBytesProcessed          = 0;

    object->macLength   = 0;
    object->nonceLength = 0;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMWFF3HSM_setMac ========
 */
int_fast16_t AESCCMWFF3HSM_setMac(AESCCM_Handle handle, const uint8_t *mac, size_t macLength)
{
    DebugP_assert(handle);
    DebugP_assert(nonce);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* This function cannot be called after addXXX() or finalizeXXX() */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error during setup.
     */
    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

    object->mac       = (uint8_t *)mac;
    object->macLength = (uint8_t)macLength;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMWFF3HSM_createAssetPostProcessing ========
 */
static inline void AESCCMWFF3HSM_createAssetPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int8_t tokenResult        = HSMWFF3_getResultCode() & HSMWFF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = HSMWFF3_getResultAssetID();
        status              = AESCCM_STATUS_SUCCESS;
    }

    object->returnStatus = status;

    HSMWFF3_releaseLock();

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);
}

/*
 *  ======== AESCCMWFF3HSM_createTempAssetID ========
 */
static int_fast16_t AESCCMWFF3HSM_createTempAssetID(AESCCM_Handle handle, AESCCM_Mode direction)
{
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int_fast16_t hsmRetval    = HSMWFF3_STATUS_ERROR;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    uint64_t assetPolicy      = 0U;

    if (!HSMWFF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }
    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* Lower 16-bit */
    assetPolicy |= EIP130_ASSET_POLICY_MODIFIABLE;
    assetPolicy |= EIP130_ASSET_POLICY_SOURCESECURE;
    assetPolicy |= EIP130_ASSET_POLICY_NOTCROSSDOMAIN;
    assetPolicy |= EIP130_ASSET_POLICY_PRIVATEDATA;
    assetPolicy |= EIP130_ASSET_POLICY_TEMPORARY;
    assetPolicy |= EIP130_ASSET_POLICY_SYMCRYPTO;

    /* Upper 16-bit */
    assetPolicy |= EIP130_ASSET_POLICY_SCUICIPHERAUTH;
    if (direction == AESCCM_MODE_DECRYPT)
    {
        assetPolicy |= EIP130_ASSET_POLICY_SCDIRDECVRFY;
    }
    else
    {
        assetPolicy |= EIP130_ASSET_POLICY_SCDIRENCGEN;
    }
    assetPolicy |= EIP130_ASSET_POLICY_SCACAES;

    HSMWFF3_constructCreateAssetToken(assetPolicy, KEY_TEMP_ASSET_SIZE);

    hsmRetval = HSMWFF3_submitToken(HSMWFF3_RETURN_BEHAVIOR_POLLING,
                                    AESCCMWFF3HSM_createAssetPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMWFF3_waitForResult();

        if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    if (hsmRetval != HSMWFF3_STATUS_SUCCESS)
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();
    }
    return status;
}

/*
 *  ======== AESCCMWFF3HSM_oneStepPostProcessing ========
 */
static inline void AESCCMWFF3HSM_oneStepPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle                      = (AESCCM_Handle)arg0;
    AESCCMWFF3_Object *object                 = AESCCMWFF3_getObject(handle);
    AESCCM_OneStepOperation *oneStepOperation = (AESCCM_OneStepOperation *)object->operation;
    int_fast16_t status                       = AESCCM_STATUS_ERROR;
    int32_t physicalResult                    = HSMWFF3_getResultCode();
    int8_t tokenResult                        = physicalResult & HSMWFF3_RETVAL_MASK;

    /* The HSM IP will throw an error when operation->macLength is zero despite it producing a correct
     * ciphertext/plaintext for both encrypt/decrypt operations and will compute a mac anyways.
     */
    if ((tokenResult == EIP130TOKEN_RESULT_INVALID_LENGTH) && (oneStepOperation->macLength == 0U))
    {
        tokenResult = EIP130TOKEN_RESULT_SUCCESS;
    }

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        if (object->operationType == AESCCM_OP_TYPE_ONESTEP_ENCRYPT)
        {
            HSMWFF3_getAESEncryptTag((void *)&oneStepOperation->mac[0]);
        }

        status = AESCCM_STATUS_SUCCESS;
    }
    else if ((object->operationType == AESCCM_OP_TYPE_ONESTEP_DECRYPT) ||
             (tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR))
    {
        status = AESCCM_STATUS_MAC_INVALID;
    }

    object->postReturnStatus = status;

    HSMWFF3_releaseLock();

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    if (object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, object->postReturnStatus, object->operation, object->operationType);
    }
}

/*
 *  ======== AESCCWFF3HSM_processOneStepHSM ========
 */
static inline int_fast16_t AESCCMWFF3HSM_processOneStepOperation(AESCCM_Handle handle)
{
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval    = HSMWFF3_STATUS_ERROR;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    if (!HSMWFF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    HSMWFF3_constructAESCCMOneStepPhysicalToken(object);

    hsmRetval = HSMWFF3_submitToken((HSMWFF3_ReturnBehavior)object->returnBehavior,
                                    AESCCMWFF3HSM_oneStepPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMWFF3_waitForResult();

        if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
        {
            if ((HSMWFF3_ReturnBehavior)object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
            {
                /* Actual results of the Operation will be set in
                 * postReturnStatus when Hwi calls post process function for CALLBACK */
                status = object->returnStatus;
            }
            else
            {
                status = object->postReturnStatus;
            }
        }
    }

    if (hsmRetval != HSMWFF3_STATUS_SUCCESS)
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_oneStepOperation ========
 */
static int_fast16_t AESCCMWFF3HSM_oneStepOperation(AESCCM_Handle handle,
                                                   AESCCM_OneStepOperation *operation,
                                                   AESCCM_OperationType operationType)
{
    DebugP_assert(handle);
    DebugP_assert(operation);
    DebugP_assert(operation->key);
    /* Internally generated nonces aren't supported for now */
    DebugP_assert(!operation->nonceInternallyGenerated);
    DebugP_assert(operation->nonce && (operation->nonceLength >= 7U) && (operation->nonceLength <= 13U));
    DebugP_assert((operation->aad && (operation->aadLength > 0U)) ||
                  (operation->input && (operation->inputLength > 0U)));
    DebugP_assert(operation->mac && (operation->macLength <= 16U));
    /* Implementation only supports aadLength to 65,279 bytes */
    DebugP_assert(operation->aadLength <= B1_AAD_LENGTH_SMALL_LIMIT);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    /* The nonce length must be 7 to 13 bytes long */
    if ((operation->nonceLength < (uint8_t)7U) || (operation->nonceLength > (uint8_t)13U))
    {
        return AESCCM_STATUS_ERROR;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMWFF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* The combined length of AAD and payload data must be non-zero. */
    if ((operation->aadLength + operation->inputLength) == 0U)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCCM_STATUS_ERROR;
    }

    object->returnStatus = AESCCM_STATUS_SUCCESS;

    object->operation     = (AESCCM_OperationUnion *)operation;
    object->operationType = operationType;

    object->key    = *(operation->key);
    object->input  = operation->input;
    object->output = operation->output;
    object->mac    = operation->mac;
    object->aad    = operation->aad;
    object->nonce  = operation->nonce;

    object->inputLength     = operation->inputLength;
    object->totalDataLength = operation->inputLength;
    object->macLength       = operation->macLength;
    object->aadLength       = object->totalAADLength;
    object->totalAADLength  = operation->aadLength;
    object->nonceLength     = operation->nonceLength;

    object->totalDataLengthRemaining = object->totalDataLength;
    object->totalAADLengthRemaining  = object->totalAADLength;

    object->tempAssetID = 0U;

    /* Process all one-step operations with data length less than the DMA size
     * threshold as a polling mode operation.
     */
    return AESCCMWFF3HSM_processOneStepOperation(handle);
}

/*
 *  ======== AESCCMWFF3HSM_setupSegmentedOperation ========
 */
static int_fast16_t AESCCMWFF3HSM_setupSegmentedOperation(AESCCMWFF3_Object *object,
                                                          const CryptoKey *key,
                                                          size_t totalAADLength,
                                                          size_t totalDataLength,
                                                          size_t macLength)
{
    DebugP_assert(key);

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMWFF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* A segmented operation may have been started but not finalized yet */
    if (object->segmentedOperationInProgress)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Make internal copy of crypto key */
    object->key = *key;

    /* returnStatus is only changed in the case of an error or cancellation */
    object->returnStatus = AES_STATUS_SUCCESS;

    object->segmentedOperationInProgress = true;

    /* If the user doesn't provide the total lengths in the setupXXXX()
     * calls, they must provide the lengths in setLengths().
     */
    object->totalAADLength  = totalAADLength;
    object->totalDataLength = totalDataLength;
    object->macLength       = (uint8_t)macLength;

    object->totalCTRLengthRemaining    = totalDataLength;
    object->totalCBCMACLengthRemaining = totalDataLength;
    object->aadBytesProcessed          = 0U;
    object->bufferedAADLength          = (uint8_t)0U;

    object->totalDataLengthRemaining = totalDataLength;
    object->totalAADLengthRemaining  = totalAADLength;
    object->inputLength              = 0U;
    object->aadLength                = 0U;

    /* Initialize MAC pointer to NULL to avoid premature processing of the
     * MAC in the ISR.
     */
    object->mac = NULL;

    /* Initialize operation pointer to NULL in case AESCCM_cancelOperation
     * is called after AESCCM_setupXXXX and callback should be skipped.
     */
    object->operation = NULL;

    return AESCCM_STATUS_SUCCESS;
}

/*
 *  ======== AESCCMWFF3HSM_setupEncrypt ========
 */
int_fast16_t AESCCMWFF3HSM_setupEncrypt(AESCCM_Handle handle,
                                        const CryptoKey *key,
                                        size_t totalAADLength,
                                        size_t totalPlaintextLength,
                                        size_t macLength)
{
    DebugP_assert(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    status = AESCCMWFF3HSM_setupSegmentedOperation(object, key, totalAADLength, totalPlaintextLength, macLength);
    if (status == AESCCM_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_ENCRYPT;
        status                = AESCCMWFF3HSM_createTempAssetID(handle, AESCCM_MODE_ENCRYPT);
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_setupDecrypt ========
 */
int_fast16_t AESCCMWFF3HSM_setupDecrypt(AESCCM_Handle handle,
                                        const CryptoKey *key,
                                        size_t totalAADLength,
                                        size_t totalPlaintextLength,
                                        size_t macLength)
{
    DebugP_assert(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);

    status = AESCCMWFF3HSM_setupSegmentedOperation(object, key, totalAADLength, totalPlaintextLength, macLength);
    if (status == AESCCM_STATUS_SUCCESS)
    {
        object->operationType = AESCCM_OPERATION_TYPE_DECRYPT;
        status                = AESCCMWFF3HSM_createTempAssetID(handle, AESCCM_MODE_DECRYPT);
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_SegmentedPostProcessing ========
 */
static inline void AESCCMWFF3HSM_SegmentedPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    AESCCM_Mode direction     = AESCCM_MODE_ENCRYPT;
    int32_t physicalResult    = HSMWFF3_getResultCode();
    int8_t tokenResult        = physicalResult & HSMWFF3_RETVAL_MASK;

    /* The HSM IP will throw an error when operation->macLength is zero despite it producing a correct
     * ciphertext/plaintext for both encrypt/decrypt operations and will compute a mac anyways.
     */
    if ((tokenResult == EIP130TOKEN_RESULT_INVALID_LENGTH) && (object->macLength == 0U))
    {
        tokenResult = EIP130TOKEN_RESULT_SUCCESS;
    }

    if ((object->operationType == AESCCM_OP_TYPE_DATA_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        direction = AESCCM_MODE_DECRYPT;
    }

    if ((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) || (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT))
    {
        if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
        {
            object->totalAADLengthRemaining -= object->aadLength;
            object->aadLength = 0U;

            status = AESCCM_STATUS_SUCCESS;
        }
    }
    else
    {
        if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
        {
            object->totalAADLengthRemaining -= object->aadLength;
            object->totalDataLengthRemaining -= object->inputLength;

            if (direction == AESCCM_MODE_ENCRYPT)
            {
                HSMWFF3_getAESEncryptTag((uint8_t *)&object->intermediateTag[0]);

                if ((object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) &&
                    ((object->totalDataLengthRemaining == 0U) && (object->totalAADLengthRemaining == 0U)))
                {
                    (void)memcpy((void *)&object->mac[0], (void *)&object->intermediateTag[0], object->macLength);
                }
            }

            status = AESCCM_STATUS_SUCCESS;
        }
        else if ((tokenResult == EIP130TOKEN_RESULT_VERIFY_ERROR) &&
                 (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
        {
            object->totalAADLengthRemaining -= object->aadLength;
            object->totalDataLengthRemaining -= object->inputLength;

            status = AESCCM_STATUS_MAC_INVALID;
        }
    }

    Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

    HSMWFF3_releaseLock();

    if ((object->operationType == AESCCM_OP_TYPE_FINALIZE_ENCRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_FINALIZE_DECRYPT))
    {
        status = AESCCMWFF3HSM_freeTempAssetID(handle);

        object->segmentedOperationInProgress = false;
    }

    object->returnStatus = status;

    if (object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
    {
        object->callbackFxn(handle, status, object->operation, object->operationType);
    }
}

/*
 *  ======== AESCCMWFF3HSM_addAAD ========
 */
int_fast16_t AESCCMWFF3HSM_addAAD(AESCCM_Handle handle, AESCCM_SegmentedAADOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval    = HSMWFF3_STATUS_ERROR;

    object->operation = (AESCCM_OperationUnion *)operation;

    if (object->totalAADLengthRemaining == object->totalAADLength)
    {
        object->aad = operation->aad;
    }

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMWFF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    if (!HSMWFF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    /* This operation can be called after setup or after addAAD again. */
    DebugP_assert((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
                  (object->operationType == AESCCM_OPERATION_TYPE_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT));

    uint8_t aadBytesProcessed = object->totalAADLength - object->totalAADLengthRemaining;
    size_t calcAADLen         = aadBytesProcessed + operation->aadLength;

    /* The total AAD input length must not exceed the total length specified
     * in AESCCM_setLengths() or the setupXXXX() call.
     */
    if (calcAADLen > object->totalAADLength)
    {
        status = AESCCM_STATUS_ERROR;
    }

    if (status == AESCCM_STATUS_ERROR)
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();

        return status;
    }

    AESCCM_OperationType operationType = AESCCM_OP_TYPE_AAD_ENCRYPT;

    if ((object->operationType == AESCCM_OPERATION_TYPE_DECRYPT) ||
        (object->operationType == AESCCM_OP_TYPE_AAD_DECRYPT))
    {
        operationType = AESCCM_OP_TYPE_AAD_DECRYPT;
    }

    object->operationType = operationType;

    uint8_t aadBytesToProcess = operation->aadLength;
    uint8_t inputRemainder    = aadBytesToProcess % AES_BLOCK_SIZE;

    if (inputRemainder > 0U)
    {
        aadBytesToProcess -= inputRemainder;
    }

    if (aadBytesProcessed + aadBytesToProcess == object->totalAADLength)
    {
        aadBytesToProcess -= AES_BLOCK_SIZE;
    }

    object->aadLength   = aadBytesToProcess;
    object->inputLength = 0U;

    if (aadBytesToProcess > 0U)
    {
        HSMWFF3_constructAESCCMSegmentedAADPhysicalToken(object);

        hsmRetval = HSMWFF3_submitToken((HSMWFF3_ReturnBehavior)object->returnBehavior,
                                        AESCCMWFF3HSM_SegmentedPostProcessing,
                                        (uintptr_t)handle);
        if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
        {
            hsmRetval = HSMWFF3_waitForResult();

            if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
            {
                status = object->returnStatus;
            }
        }

        if (hsmRetval != HSMWFF3_STATUS_SUCCESS)
        {
            Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

            HSMWFF3_releaseLock();
        }

        object->returnStatus = status;
    }
    else
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();

        object->returnStatus = status;

        if (object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, operationType);

            /* Always return success in callback mode */
            status = AESCCM_STATUS_SUCCESS;
        }
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_addData ========
 */
static int_fast16_t AESCCMWFF3HSM_addData(AESCCM_Handle handle,
                                          AESCCM_OperationType operationType,
                                          AESCCM_OperationUnion *operation,
                                          const uint8_t *input,
                                          uint8_t *output,
                                          size_t inputLength)
{
    int_fast16_t status                               = AESCCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval                            = HSMWFF3_STATUS_ERROR;
    AESCCMWFF3_Object *object                         = AESCCMWFF3_getObject(handle);
    AESCCM_SegmentedDataOperation *segmentedOperation = (AESCCM_SegmentedDataOperation *)operation;

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMWFF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    if (!HSMWFF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
    {
        return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
    }

    Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);

    object->operationType = operationType;
    object->operation     = operation;

    if (object->totalDataLengthRemaining == object->totalDataLength)
    {
        object->input  = segmentedOperation->input;
        object->output = segmentedOperation->output;
    }

    object->aadLength   = object->totalAADLengthRemaining;
    object->inputLength = inputLength;

    HSMWFF3_constructAESCCMSegmentedDataPhysicalToken(object);

    hsmRetval = HSMWFF3_submitToken((HSMWFF3_ReturnBehavior)object->returnBehavior,
                                    AESCCMWFF3HSM_SegmentedPostProcessing,
                                    (uintptr_t)handle);
    if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
    {
        hsmRetval = HSMWFF3_waitForResult();

        if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
        {
            status = object->returnStatus;
        }
    }

    if (hsmRetval != HSMWFF3_STATUS_SUCCESS)
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();
    }

    object->returnStatus = status;

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_freeAssetPostProcessing ========
 */
static inline void AESCCMWFF3HSM_freeAssetPostProcessing(uintptr_t arg0)
{
    AESCCM_Handle handle      = (AESCCM_Handle)arg0;
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_ERROR;
    int8_t tokenResult        = HSMWFF3_getResultCode() & HSMWFF3_RETVAL_MASK;

    if (tokenResult == EIP130TOKEN_RESULT_SUCCESS)
    {
        object->tempAssetID = 0;
        status              = AESCCM_STATUS_SUCCESS;
    }

    object->returnStatus = status;

    if ((HSMWFF3_ReturnBehavior)object->returnBehavior == HSMWFF3_RETURN_BEHAVIOR_POLLING)
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();
    }
}

/*
 *  ======== AESCCMWFF3HSM_freeTempAssetID ========
 */
static int_fast16_t AESCCMWFF3HSM_freeTempAssetID(AESCCM_Handle handle)
{
    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status       = AESCCM_STATUS_SUCCESS;
    int_fast16_t hsmRetval    = HSMWFF3_STATUS_ERROR;

    if (object->tempAssetID != 0)
    {
        if ((HSMWFF3_ReturnBehavior)object->returnBehavior == HSMWFF3_RETURN_BEHAVIOR_POLLING)
        {
            if (!HSMWFF3_acquireLock(SemaphoreP_NO_WAIT, (uintptr_t)handle))
            {
                return AESCCM_STATUS_RESOURCE_UNAVAILABLE;
            }
            Power_setConstraint(PowerWFF3_DISALLOW_SLEEP);
        }

        HSMWFF3_constructDeleteAssetToken(object->tempAssetID);

        hsmRetval = HSMWFF3_submitToken(HSMWFF3_RETURN_BEHAVIOR_POLLING,
                                        AESCCMWFF3HSM_freeAssetPostProcessing,
                                        (uintptr_t)handle);
        if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
        {
            hsmRetval = HSMWFF3_waitForResult();

            if (hsmRetval == HSMWFF3_STATUS_SUCCESS)
            {
                status = object->returnStatus;
            }
        }
    }

    if (((HSMWFF3_ReturnBehavior)object->returnBehavior == HSMWFF3_RETURN_BEHAVIOR_POLLING) &&
        (hsmRetval != HSMWFF3_STATUS_SUCCESS))
    {
        Power_releaseConstraint(PowerWFF3_DISALLOW_SLEEP);

        HSMWFF3_releaseLock();
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_finalizeEncrypt ========
 */
int_fast16_t AESCCMWFF3HSM_finalizeEncrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status;

    status = AESCCMWFF3HSM_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->totalDataLengthRemaining == object->totalDataLength)
    {
        object->input  = operation->input;
        object->output = operation->output;
    }

    object->mac       = operation->mac;
    object->macLength = operation->macLength;

    if ((operation->inputLength > 0U) || (object->totalAADLengthRemaining > 0))
    {
        status = AESCCMWFF3HSM_addData(handle,
                                       AESCCM_OP_TYPE_FINALIZE_ENCRYPT,
                                       (AESCCM_OperationUnion *)operation,
                                       operation->input,
                                       operation->output,
                                       operation->inputLength);
    }
    else
    {
        (void)memcpy(operation->mac, (uint32_t *)&object->intermediateTag[0], operation->macLength);

        status = AESCCMWFF3HSM_freeTempAssetID(handle);

        object->segmentedOperationInProgress = false;

        if (object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_ENCRYPT);
        }
    }
    return status;
}

/*
 *  ======== AESCCMWFF3HSM_finalizeDecrypt ========
 */
int_fast16_t AESCCMWFF3HSM_finalizeDecrypt(AESCCM_Handle handle, AESCCM_SegmentedFinalizeOperation *operation)
{
    DebugP_assert(handle);
    DebugP_assert(operation);

    AESCCMWFF3_Object *object = AESCCMWFF3_getObject(handle);
    int_fast16_t status;

    status = AESCCMWFF3HSM_performFinalizeChecks(object, operation);

    if (status != AESCCM_STATUS_SUCCESS)
    {
        return status;
    }

    if (object->totalDataLengthRemaining == object->totalDataLength)
    {
        object->input  = operation->input;
        object->output = operation->output;
    }

    object->mac       = operation->mac;
    object->macLength = operation->macLength;

    if ((operation->inputLength > 0U) || (object->totalAADLengthRemaining > 0U))
    {
        status = AESCCMWFF3HSM_addData(handle,
                                       AESCCM_OP_TYPE_FINALIZE_DECRYPT,
                                       (AESCCM_OperationUnion *)operation,
                                       operation->input,
                                       operation->output,
                                       operation->inputLength);
    }
    else
    {
        status = AESCCMWFF3HSM_freeTempAssetID(handle);

        object->segmentedOperationInProgress = false;

        if (object->returnBehavior == AES_RETURN_BEHAVIOR_CALLBACK)
        {
            object->callbackFxn(handle, status, (AESCCM_OperationUnion *)operation, AESCCM_OP_TYPE_FINALIZE_DECRYPT);
        }
    }

    return status;
}

/*
 *  ======== AESCCMWFF3HSM_performFinalizeChecks ========
 */
static int_fast16_t AESCCMWFF3HSM_performFinalizeChecks(const AESCCMWFF3_Object *object,
                                                        const AESCCM_SegmentedFinalizeOperation *operation)
{
    /* This operation can be called after setupXXXX, addAAD, or addData */
    DebugP_assert((object->operationType == AESCCM_OP_TYPE_AAD_ENCRYPT) ||
                  (object->operationType == AESCCM_OP_TYPE_DATA_ENCRYPT));

    /* Don't continue the segmented operation if there
     * was an error or a cancellation.
     */
    if (object->returnStatus != AESCCM_STATUS_SUCCESS)
    {
        return object->returnStatus;
    }

    /* If the HSM IP and/or HSMSAL failed to boot then we cannot perform any HSM-related operation */
    if (object->hsmStatus != HSMWFF3_STATUS_SUCCESS)
    {
        return AESCCM_STATUS_ERROR;
    }

    /* Additional payload data can be passed in finalize */
    if (operation->inputLength != object->totalDataLengthRemaining)
    {
        return AESCCM_STATUS_ERROR;
    }

    return AESCCM_STATUS_SUCCESS;
}
