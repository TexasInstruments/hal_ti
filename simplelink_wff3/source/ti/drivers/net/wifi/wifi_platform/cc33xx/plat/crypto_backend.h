/*
 * Copyright (c) 2026, Texas Instruments Incorporated
 * Copyright (c) 2026, Conclusive Engineering Sp. z o.o.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CRYPTO_BACKEND_H
#define CRYPTO_BACKEND_H

#include <stddef.h>
#include <stdint.h>

int crypto_backend_get_random(unsigned char *rand_buf, size_t rand_len);

void *crypto_backend_aes_encrypt_init(const uint8_t *key, size_t len);
int crypto_backend_aes_encrypt(void *ctx, const uint8_t *plain, uint8_t *crypt);
void crypto_backend_aes_encrypt_deinit(void *ctx);

void *crypto_backend_aes_decrypt_init(const uint8_t *key, size_t len);
int crypto_backend_aes_decrypt(void *ctx, const uint8_t *crypt, uint8_t *plain);
void crypto_backend_aes_decrypt_deinit(void *ctx);

int crypto_backend_aes_128_cbc_oper(const uint8_t *key, const uint8_t *iv,
				    uint8_t *data, size_t data_len, int mode);

#endif /* CRYPTO_BACKEND_H */
