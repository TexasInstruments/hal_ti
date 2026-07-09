/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utils/common.h"
#include "crypto_backend.h"

#include <mbedtls/aes.h>
#include <mbedtls/md.h>
#include <mbedtls/pkcs5.h>
#include <psa/crypto.h>

#define TI_PSA_AES_KEY_LIFETIME \
	PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION( \
		PSA_KEY_PERSISTENCE_HSM_ASSET_STORE, \
		PSA_KEY_LOCATION_HSM_ASSET_STORE)

typedef struct {
	psa_key_id_t key_id;
	psa_cipher_operation_t operation;
	uint8_t iv[16];
} ti_wifi_aes_context;

int crypto_backend_get_random(unsigned char *rand_buf, size_t rand_len)
{
	psa_status_t status;

	status = psa_crypto_init();
	if (status != PSA_SUCCESS) {
		return -1;
	}

	status = psa_generate_random(rand_buf, rand_len);
	return status == PSA_SUCCESS ? 0 : -1;
}

int crypto_backend_pbkdf2_sha1(const char *passphrase, const uint8_t *ssid,
			       size_t ssid_len, int iterations, uint8_t *buf,
			       size_t buflen)
{
#if MBEDTLS_VERSION_NUMBER >= 0x03030000
	return mbedtls_pkcs5_pbkdf2_hmac_ext(MBEDTLS_MD_SHA1,
					     (const uint8_t *)passphrase,
					     os_strlen(passphrase), ssid,
					     ssid_len, iterations, buflen,
					     buf) ? -1 : 0;
#else
	const mbedtls_md_info_t *md_info;
	mbedtls_md_context_t ctx;
	int ret;

	md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
	if (!md_info) {
		return -1;
	}

	mbedtls_md_init(&ctx);
	ret = mbedtls_md_setup(&ctx, md_info, 1) ||
	      mbedtls_pkcs5_pbkdf2_hmac(&ctx, (const uint8_t *)passphrase,
					os_strlen(passphrase), ssid, ssid_len,
					iterations, buflen, buf);
	mbedtls_md_free(&ctx);

	return ret ? -1 : 0;
#endif
}

void *crypto_backend_aes_encrypt_init(const uint8_t *key, size_t len)
{
	psa_status_t status;
	ti_wifi_aes_context *ctx = os_calloc(1, sizeof(ti_wifi_aes_context));
	psa_key_lifetime_t lifetime = TI_PSA_AES_KEY_LIFETIME;

	if (!ctx) {
		return NULL;
	}

	status = psa_crypto_init();
	if (status != PSA_SUCCESS) {
		os_free(ctx);
		return NULL;
	}

	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_ENCRYPT);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECB_NO_PADDING);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_AES);
	psa_set_key_bits(&key_attributes, len * 8);
	psa_set_key_lifetime(&key_attributes, lifetime);

	psa_key_id_t keyID = PSA_KEY_ID_USER_MIN;
	psa_set_key_id(&key_attributes, keyID);
	status = psa_destroy_key(keyID);

	status = psa_import_key(&key_attributes, key, len, &ctx->key_id);
	if (status != PSA_SUCCESS) {
		os_free(ctx);
		return NULL;
	}
	ctx->operation = psa_cipher_operation_init();
	status = psa_cipher_encrypt_setup(&ctx->operation, ctx->key_id,
					  PSA_ALG_ECB_NO_PADDING);
	if (status != PSA_SUCCESS) {
		psa_destroy_key(ctx->key_id);
		os_free(ctx);
		return NULL;
	}

	os_memset(ctx->iv, 0, sizeof(ctx->iv));
	return ctx;
}

void crypto_backend_aes_encrypt_deinit(void *ctx)
{
	ti_wifi_aes_context *aes_ctx = (ti_wifi_aes_context *)ctx;

	if (aes_ctx) {
		psa_cipher_abort(&aes_ctx->operation);
		psa_destroy_key(aes_ctx->key_id);
		os_free(aes_ctx);
	}
}

int crypto_backend_aes_encrypt(void *ctx, const uint8_t *plain, uint8_t *crypt)
{
	ti_wifi_aes_context *aes_ctx = (ti_wifi_aes_context *)ctx;
	psa_status_t status;
	size_t output_length;
	static __attribute__((aligned(4))) uint8_t plainA[16];
	static __attribute__((aligned(4))) uint8_t cryptA[16];

	if (!ctx) {
		return -1;
	}

	os_memset(plainA, 0, 16);
	os_memset(cryptA, 0, 16);
	os_memcpy(plainA, plain, 16);

	status = psa_cipher_update(&aes_ctx->operation, plainA, 16, cryptA, 16,
				   &output_length);
	if (status != PSA_SUCCESS || output_length != 16) {
		return -1;
	}

	os_memcpy(crypt, cryptA, 16);

	return 0;
}

void *crypto_backend_aes_decrypt_init(const uint8_t *key, size_t len)
{
	psa_status_t status;
	ti_wifi_aes_context *ctx = os_calloc(1, sizeof(ti_wifi_aes_context));
	psa_key_lifetime_t lifetime = TI_PSA_AES_KEY_LIFETIME;

	if (!ctx) {
		return NULL;
	}

	status = psa_crypto_init();
	if (status != PSA_SUCCESS) {
		os_free(ctx);
		return NULL;
	}

	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_DECRYPT);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECB_NO_PADDING);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_AES);
	psa_set_key_bits(&key_attributes, len * 8);
	psa_set_key_lifetime(&key_attributes, lifetime);

	psa_key_id_t keyID = PSA_KEY_ID_USER_MIN + 1;
	psa_set_key_id(&key_attributes, keyID);
	status = psa_destroy_key(keyID);

	status = psa_import_key(&key_attributes, key, len, &ctx->key_id);
	if (status != PSA_SUCCESS) {
		os_free(ctx);
		return NULL;
	}

	ctx->operation = psa_cipher_operation_init();
	status = psa_cipher_decrypt_setup(&ctx->operation, ctx->key_id,
					  PSA_ALG_ECB_NO_PADDING);
	if (status != PSA_SUCCESS) {
		psa_destroy_key(ctx->key_id);
		os_free(ctx);
		return NULL;
	}

	os_memset(ctx->iv, 0, sizeof(ctx->iv));

	return ctx;
}

int crypto_backend_aes_decrypt(void *ctx, const uint8_t *crypt, uint8_t *plain)
{
	ti_wifi_aes_context *aes_ctx = (ti_wifi_aes_context *)ctx;
	psa_status_t status;
	size_t output_length;
	static __attribute__((aligned(4))) uint8_t plainA[16];
	static __attribute__((aligned(4))) uint8_t cryptA[16];

	if (!ctx) {
		return -1;
	}

	os_memset(plainA, 0, 16);
	os_memset(cryptA, 0, 16);
	os_memcpy(cryptA, crypt, 16);

	status = psa_cipher_update(&aes_ctx->operation, cryptA, 16, plainA, 16,
				   &output_length);
	if (status != PSA_SUCCESS || output_length != 16) {
		return -1;
	}

	os_memcpy(plain, plainA, 16);

	return 0;
}

void crypto_backend_aes_decrypt_deinit(void *ctx)
{
	ti_wifi_aes_context *aes_ctx = (ti_wifi_aes_context *)ctx;

	if (aes_ctx) {
		psa_cipher_abort(&aes_ctx->operation);
		psa_destroy_key(aes_ctx->key_id);
		os_free(aes_ctx);
	}
}

int crypto_backend_aes_128_cbc_oper(const uint8_t *key, const uint8_t *iv,
				    uint8_t *data, size_t data_len, int mode)
{
	psa_status_t status;
	psa_key_id_t key_id = PSA_KEY_ID_NULL;
	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;
	size_t output_len;
	psa_cipher_operation_t operation = PSA_CIPHER_OPERATION_INIT;
	psa_key_lifetime_t lifetime = TI_PSA_AES_KEY_LIFETIME;
	uint8_t *orig_data = data;
	uint8_t *tmp_buf = NULL;
	uint8_t *aligned_tmp_buf = NULL;

	status = psa_crypto_init();
	if (status != PSA_SUCCESS) {
		return -1;
	}

	psa_set_key_usage_flags(&key_attributes,
				PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_CBC_NO_PADDING);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_AES);
	psa_set_key_bits(&key_attributes, 128);
	psa_set_key_lifetime(&key_attributes, lifetime);

	if (mode == 1) {
		key_id = PSA_KEY_ID_USER_MIN + 2;
	} else {
		key_id = PSA_KEY_ID_USER_MIN + 3;
	}

	psa_set_key_id(&key_attributes, key_id);
	status = psa_destroy_key(key_id);

	status = psa_import_key(&key_attributes, key, 16, &key_id);
	if (status != PSA_SUCCESS) {
		goto exit;
	}

	if (((uintptr_t)data & 0x3) != 0) {
		tmp_buf = os_malloc(data_len + 3);
		if (!tmp_buf) {
			status = PSA_ERROR_INSUFFICIENT_MEMORY;
			goto exit;
		}

		aligned_tmp_buf = (uint8_t *)(((uintptr_t)tmp_buf + 3) & ~(uintptr_t)3);
		os_memcpy(aligned_tmp_buf, data, data_len);
		data = aligned_tmp_buf;
	}

	if (mode == MBEDTLS_AES_ENCRYPT) {
		status = psa_cipher_encrypt_setup(&operation, key_id,
						  PSA_ALG_CBC_NO_PADDING);
	} else {
		status = psa_cipher_decrypt_setup(&operation, key_id,
						  PSA_ALG_CBC_NO_PADDING);
	}

	if (status != PSA_SUCCESS) {
		goto exit;
	}

	status = psa_cipher_set_iv(&operation, iv, 16);
	if (status != PSA_SUCCESS) {
		psa_cipher_abort(&operation);
		goto exit;
	}

	status = psa_cipher_update(&operation, data, data_len, data, data_len,
				   &output_len);
	if (status != PSA_SUCCESS) {
		psa_cipher_abort(&operation);
		goto exit;
	}

	size_t final_output_len;
	status = psa_cipher_finish(&operation, data + output_len,
				   data_len - output_len, &final_output_len);
	output_len += final_output_len;
	psa_cipher_abort(&operation);

	if ((status == PSA_SUCCESS) && (output_len != data_len)) {
		status = PSA_ERROR_GENERIC_ERROR;
	}

exit:
	psa_destroy_key(key_id);

	if (tmp_buf) {
		if (status == PSA_SUCCESS) {
			os_memcpy(orig_data, aligned_tmp_buf, data_len);
		}
		os_free(tmp_buf);
	}

	return (status == PSA_SUCCESS) ? 0 : -1;
}

int crypto_backend_aes_ctr_encrypt(const uint8_t *key, size_t key_len,
				   const uint8_t *nonce, uint8_t *data,
				   size_t data_len)
{
	unsigned char counter[MBEDTLS_AES_BLOCK_SIZE];
	unsigned char stream_block[MBEDTLS_AES_BLOCK_SIZE];
	mbedtls_aes_context ctx;
	size_t nc_off = 0;
	int ret;

	os_memcpy(counter, nonce, sizeof(counter));

	mbedtls_aes_init(&ctx);
	ret = mbedtls_aes_setkey_enc(&ctx, key, key_len * 8) ||
	      mbedtls_aes_crypt_ctr(&ctx, data_len, &nc_off, counter,
				    stream_block, data, data);
	os_memset(stream_block, 0, sizeof(stream_block));
	mbedtls_aes_free(&ctx);

	return ret ? -1 : 0;
}
