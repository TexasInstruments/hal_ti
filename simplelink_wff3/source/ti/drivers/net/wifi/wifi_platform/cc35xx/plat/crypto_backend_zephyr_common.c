/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "utils/common.h"
#include "crypto/sha1.h"
#include "crypto_backend.h"

static int crypto_backend_pbkdf2_sha1_f(const char *passphrase,
					const uint8_t *ssid, size_t ssid_len,
					int iterations, unsigned int count,
					uint8_t *digest)
{
	uint8_t tmp[SHA1_MAC_LEN];
	uint8_t tmp2[SHA1_MAC_LEN];
	uint8_t count_buf[4];
	const uint8_t *addr[2];
	size_t len[2];
	size_t passphrase_len = os_strlen(passphrase);
	int i;
	int j;

	addr[0] = ssid;
	len[0] = ssid_len;
	addr[1] = count_buf;
	len[1] = sizeof(count_buf);

	count_buf[0] = (count >> 24) & 0xff;
	count_buf[1] = (count >> 16) & 0xff;
	count_buf[2] = (count >> 8) & 0xff;
	count_buf[3] = count & 0xff;
	if (hmac_sha1_vector((uint8_t *)passphrase, passphrase_len, 2, addr,
			     len, tmp)) {
		return -1;
	}

	os_memcpy(digest, tmp, SHA1_MAC_LEN);

	for (i = 1; i < iterations; i++) {
		if (hmac_sha1((uint8_t *)passphrase, passphrase_len, tmp,
			      SHA1_MAC_LEN, tmp2)) {
			return -1;
		}

		os_memcpy(tmp, tmp2, SHA1_MAC_LEN);
		for (j = 0; j < SHA1_MAC_LEN; j++) {
			digest[j] ^= tmp2[j];
		}
	}

	return 0;
}

int crypto_backend_pbkdf2_sha1(const char *passphrase, const uint8_t *ssid,
			       size_t ssid_len, int iterations, uint8_t *buf,
			       size_t buflen)
{
	unsigned int count = 0;
	uint8_t digest[SHA1_MAC_LEN];
	uint8_t *pos = buf;
	size_t left = buflen;
	size_t plen;

	while (left > 0) {
		count++;
		if (crypto_backend_pbkdf2_sha1_f(passphrase, ssid, ssid_len,
						 iterations, count, digest)) {
			return -1;
		}

		plen = left > SHA1_MAC_LEN ? SHA1_MAC_LEN : left;
		os_memcpy(pos, digest, plen);
		pos += plen;
		left -= plen;
	}

	return 0;
}
