/*
 * Copyright (c) 2026, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file contains overloads of certain weak functions from the SimpleLink SDK */

#include <zephyr/random/random.h>
#include <stdint.h>

/*
 * RCL_Handler_BLE5_getRandomNumber is overloaded to call Zephyr's non-
 * cryptographically secure RNG API instead of the SimpleLink Random driver.
 * In the future, this function should call a DPL RNG layer.
 */
uint32_t RCL_Handler_BLE5_getRandomNumber(void)
{
	/* This function will fail if the entropy driver is not initialized */
	return sys_rand32_get();
}
