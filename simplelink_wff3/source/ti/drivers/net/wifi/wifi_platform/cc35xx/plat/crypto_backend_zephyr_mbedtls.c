/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <mbedtls/aes.h>
#include <zephyr/random/random.h>

#include "utils/common.h"
#include "crypto_backend.h"

#ifndef MBEDTLS_AES_BLOCK_SIZE
#define MBEDTLS_AES_BLOCK_SIZE 16
#endif

int crypto_backend_get_random(unsigned char *rand_buf, size_t rand_len)
{
	int ret = sys_csrand_get(rand_buf, rand_len);

	if (ret) {
		return -1;
	}

	return 0;
}

static void *aes_crypt_init_mode(const uint8_t *key, size_t len, int mode)
{
	mbedtls_aes_context *aes = os_malloc(sizeof(*aes));

	if (!aes) {
		return NULL;
	}

	mbedtls_aes_init(aes);
	if ((mode == MBEDTLS_AES_ENCRYPT ?
	     mbedtls_aes_setkey_enc(aes, key, len * 8) :
	     mbedtls_aes_setkey_dec(aes, key, len * 8)) == 0) {
		return aes;
	}

	mbedtls_aes_free(aes);
	os_free(aes);
	return NULL;
}

void *crypto_backend_aes_encrypt_init(const uint8_t *key, size_t len)
{
	return aes_crypt_init_mode(key, len, MBEDTLS_AES_ENCRYPT);
}

int crypto_backend_aes_encrypt(void *ctx, const uint8_t *plain, uint8_t *crypt)
{
	return mbedtls_aes_crypt_ecb(ctx, MBEDTLS_AES_ENCRYPT, plain, crypt);
}

void crypto_backend_aes_encrypt_deinit(void *ctx)
{
	if (!ctx) {
		return;
	}

	mbedtls_aes_free(ctx);
	os_free(ctx);
}

void *crypto_backend_aes_decrypt_init(const uint8_t *key, size_t len)
{
	return aes_crypt_init_mode(key, len, MBEDTLS_AES_DECRYPT);
}

int crypto_backend_aes_decrypt(void *ctx, const uint8_t *crypt, uint8_t *plain)
{
	return mbedtls_aes_crypt_ecb(ctx, MBEDTLS_AES_DECRYPT, crypt, plain);
}

void crypto_backend_aes_decrypt_deinit(void *ctx)
{
	if (!ctx) {
		return;
	}

	mbedtls_aes_free(ctx);
	os_free(ctx);
}

int crypto_backend_aes_128_cbc_oper(const uint8_t *key, const uint8_t *iv,
				    uint8_t *data, size_t data_len, int mode)
{
	unsigned char ivec[MBEDTLS_AES_BLOCK_SIZE];
	mbedtls_aes_context ctx;
	int ret;

	os_memcpy(ivec, iv, MBEDTLS_AES_BLOCK_SIZE);

	mbedtls_aes_init(&ctx);
	ret = (mode == MBEDTLS_AES_ENCRYPT ?
	       mbedtls_aes_setkey_enc(&ctx, key, 128) :
	       mbedtls_aes_setkey_dec(&ctx, key, 128)) ||
	      mbedtls_aes_crypt_cbc(&ctx, mode, data_len, ivec, data, data);
	mbedtls_aes_free(&ctx);

	return ret ? -1 : 0;
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
