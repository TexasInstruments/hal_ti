/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utils/common.h"
#include "crypto_backend.h"

#include <psa/crypto.h>

#define TI_WIFI_AES_BLOCK_SIZE 16
#define TI_WIFI_AES_DECRYPT 0
#define TI_WIFI_AES_ENCRYPT 1

typedef struct {
	psa_key_id_t key_id;
} ti_wifi_aes_context;

static int crypto_backend_psa_init(void)
{
	psa_status_t status;

	status = psa_crypto_init();
	if (status != PSA_SUCCESS) {
		return -1;
	}

	return 0;
}

int crypto_backend_get_random(unsigned char *rand_buf, size_t rand_len)
{
	if (crypto_backend_psa_init()) {
		return -1;
	}

	psa_status_t status = psa_generate_random(rand_buf, rand_len);

	if (status != PSA_SUCCESS) {
		return -1;
	}

	return 0;
}

static void crypto_backend_set_aes_key_attrs(psa_key_attributes_t *attrs,
					     psa_key_usage_t usage,
					     psa_algorithm_t alg,
					     size_t bits)
{
	psa_set_key_usage_flags(attrs, usage);
	psa_set_key_algorithm(attrs, alg);
	psa_set_key_type(attrs, PSA_KEY_TYPE_AES);
	psa_set_key_bits(attrs, bits);
	psa_set_key_lifetime(attrs, PSA_KEY_LIFETIME_VOLATILE);
}

static void *crypto_backend_aes_init(const uint8_t *key, size_t len,
				     psa_key_usage_t usage,
				     int mode)
{
	psa_status_t status;
	psa_key_attributes_t key_attrs = PSA_KEY_ATTRIBUTES_INIT;
	ti_wifi_aes_context *ctx;

	if (crypto_backend_psa_init()) {
		return NULL;
	}

	ctx = os_calloc(1, sizeof(*ctx));
	if (!ctx) {
		return NULL;
	}

	crypto_backend_set_aes_key_attrs(&key_attrs, usage,
					 PSA_ALG_ECB_NO_PADDING, len * 8);

	status = psa_import_key(&key_attrs, key, len, &ctx->key_id);
	psa_reset_key_attributes(&key_attrs);
	if (status != PSA_SUCCESS) {
		os_free(ctx);
		return NULL;
	}

	return ctx;
}

static int crypto_backend_aes_ecb_block(psa_key_id_t key_id, const uint8_t *in,
					uint8_t *out, int mode)
{
	psa_cipher_operation_t operation = PSA_CIPHER_OPERATION_INIT;
	__attribute__((aligned(4))) uint8_t in_aligned[TI_WIFI_AES_BLOCK_SIZE];
	__attribute__((aligned(4))) uint8_t out_aligned[TI_WIFI_AES_BLOCK_SIZE];
	size_t output_len;
	size_t final_len;
	psa_status_t status;
	int ret = -1;

	if (mode == TI_WIFI_AES_ENCRYPT) {
		status = psa_cipher_encrypt_setup(&operation, key_id,
						  PSA_ALG_ECB_NO_PADDING);
	} else {
		status = psa_cipher_decrypt_setup(&operation, key_id,
						  PSA_ALG_ECB_NO_PADDING);
	}

	if (status != PSA_SUCCESS) {
		goto out;
	}

	os_memcpy(in_aligned, in, sizeof(in_aligned));
	status = psa_cipher_update(&operation, in_aligned, sizeof(in_aligned),
				   out_aligned, sizeof(out_aligned),
				   &output_len);
	if (status != PSA_SUCCESS || output_len != sizeof(out_aligned)) {
		goto out;
	}

	status = psa_cipher_finish(&operation, out_aligned + output_len,
				   sizeof(out_aligned) - output_len, &final_len);
	if (status != PSA_SUCCESS || final_len != 0) {
		goto out;
	}

	os_memcpy(out, out_aligned, sizeof(out_aligned));
	ret = 0;

out:
	psa_cipher_abort(&operation);
	return ret;
}

void *crypto_backend_aes_encrypt_init(const uint8_t *key, size_t len)
{
	return crypto_backend_aes_init(key, len, PSA_KEY_USAGE_ENCRYPT,
				       TI_WIFI_AES_ENCRYPT);
}

int crypto_backend_aes_encrypt(void *ctx, const uint8_t *plain, uint8_t *crypt)
{
	ti_wifi_aes_context *aes_ctx = ctx;
	if (!aes_ctx) {
		return -1;
	}

	return crypto_backend_aes_ecb_block(aes_ctx->key_id, plain, crypt,
					    TI_WIFI_AES_ENCRYPT);
}

void crypto_backend_aes_encrypt_deinit(void *ctx)
{
	ti_wifi_aes_context *aes_ctx = ctx;

	if (!aes_ctx) {
		return;
	}

	psa_destroy_key(aes_ctx->key_id);
	os_free(aes_ctx);
}

void *crypto_backend_aes_decrypt_init(const uint8_t *key, size_t len)
{
	return crypto_backend_aes_init(key, len, PSA_KEY_USAGE_DECRYPT,
				       TI_WIFI_AES_DECRYPT);
}

int crypto_backend_aes_decrypt(void *ctx, const uint8_t *crypt, uint8_t *plain)
{
	ti_wifi_aes_context *aes_ctx = ctx;
	if (!aes_ctx) {
		return -1;
	}

	return crypto_backend_aes_ecb_block(aes_ctx->key_id, crypt, plain,
					    TI_WIFI_AES_DECRYPT);
}

void crypto_backend_aes_decrypt_deinit(void *ctx)
{
	ti_wifi_aes_context *aes_ctx = ctx;

	if (!aes_ctx) {
		return;
	}

	psa_destroy_key(aes_ctx->key_id);
	os_free(aes_ctx);
}

int crypto_backend_aes_128_cbc_oper(const uint8_t *key, const uint8_t *iv,
				    uint8_t *data, size_t data_len, int mode)
{
	psa_key_attributes_t key_attrs = PSA_KEY_ATTRIBUTES_INIT;
	psa_cipher_operation_t operation = PSA_CIPHER_OPERATION_INIT;
	psa_key_id_t key_id = PSA_KEY_ID_NULL;
	psa_status_t status;
	uint8_t *tmp = NULL;
	size_t output_len;
	size_t final_len;
	int ret = -1;

	if (crypto_backend_psa_init()) {
		return -1;
	}

	tmp = os_malloc(data_len);
	if (!tmp) {
		return -1;
	}

	crypto_backend_set_aes_key_attrs(&key_attrs,
					 PSA_KEY_USAGE_ENCRYPT |
					 PSA_KEY_USAGE_DECRYPT,
					 PSA_ALG_CBC_NO_PADDING, 128);

	status = psa_import_key(&key_attrs, key, 16, &key_id);
	psa_reset_key_attributes(&key_attrs);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	if (mode == TI_WIFI_AES_ENCRYPT) {
		status = psa_cipher_encrypt_setup(&operation, key_id,
						  PSA_ALG_CBC_NO_PADDING);
	} else {
		status = psa_cipher_decrypt_setup(&operation, key_id,
						  PSA_ALG_CBC_NO_PADDING);
	}

	if (status != PSA_SUCCESS) {
		goto out;
	}

	status = psa_cipher_set_iv(&operation, iv, TI_WIFI_AES_BLOCK_SIZE);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	status = psa_cipher_update(&operation, data, data_len, tmp, data_len,
				   &output_len);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	status = psa_cipher_finish(&operation, tmp + output_len,
				   data_len - output_len, &final_len);
	if (status != PSA_SUCCESS || output_len + final_len != data_len) {
		goto out;
	}

	os_memcpy(data, tmp, data_len);
	ret = 0;

out:
	psa_cipher_abort(&operation);
	psa_destroy_key(key_id);
	os_free(tmp);

	return ret;
}

int crypto_backend_aes_ctr_encrypt(const uint8_t *key, size_t key_len,
				   const uint8_t *nonce, uint8_t *data,
				   size_t data_len)
{
	psa_key_attributes_t key_attrs = PSA_KEY_ATTRIBUTES_INIT;
	psa_cipher_operation_t operation = PSA_CIPHER_OPERATION_INIT;
	psa_key_id_t key_id = PSA_KEY_ID_NULL;
	uint8_t out[64];
	size_t offset = 0;
	psa_status_t status;
	int ret = -1;

	if (crypto_backend_psa_init()) {
		return -1;
	}

	crypto_backend_set_aes_key_attrs(&key_attrs, PSA_KEY_USAGE_ENCRYPT,
					 PSA_ALG_CTR, key_len * 8);

	status = psa_import_key(&key_attrs, key, key_len, &key_id);
	psa_reset_key_attributes(&key_attrs);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	status = psa_cipher_encrypt_setup(&operation, key_id, PSA_ALG_CTR);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	status = psa_cipher_set_iv(&operation, nonce, TI_WIFI_AES_BLOCK_SIZE);
	if (status != PSA_SUCCESS) {
		goto out;
	}

	while (offset < data_len) {
		size_t chunk_len = data_len - offset;
		size_t output_len;

		if (chunk_len > sizeof(out)) {
			chunk_len = sizeof(out);
		}

		status = psa_cipher_update(&operation, data + offset, chunk_len,
					   out, sizeof(out), &output_len);
		if (status != PSA_SUCCESS || output_len != chunk_len) {
			goto out;
		}

		os_memcpy(data + offset, out, output_len);
		offset += output_len;
	}

	{
		size_t final_len;

		status = psa_cipher_finish(&operation, out, sizeof(out),
					   &final_len);
		if (status != PSA_SUCCESS || final_len != 0) {
			goto out;
		}
	}

	ret = 0;

out:
	psa_cipher_abort(&operation);
	psa_destroy_key(key_id);

	return ret;
}
