/*
 * Copyright (c) 2026, Texas Instruments Incorporated
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

#if defined(CONFIG_SOC_CC2755P10)

#include <zephyr/kernel.h>
#include <ti/drivers/rcl/RCL_Feature.h>
#include <ti/drivers/rcl/zephyr/rcl_driver_config.h>

#define RCL_REGULATORY_MASK \
    ((IS_ENABLED(CONFIG_RCL_REGULATORY_DOMAIN_ETSI) ? (RCL_REGULATORY_DOMAIN_ETSI) : 0U) | \
     (IS_ENABLED(CONFIG_RCL_REGULATORY_DOMAIN_FCC)  ? (RCL_REGULATORY_DOMAIN_FCC) : 0U)  | \
     (IS_ENABLED(CONFIG_RCL_REGULATORY_DOMAIN_MIIT) ? (RCL_REGULATORY_DOMAIN_MIIT) : 0U))

const RCL_FeatureControl rclFeatureControl =
{
    .enableTemperatureMonitoring = true,
    .enablePaEsdProtection = false,
    .enableTxOutputPowerCompensation = true
};

#if defined(CONFIG_RCL_REGULATORY_DOMAIN_RUNTIME_MODIFIABLE)
uint8_t rclRegulatoryMask = RCL_REGULATORY_MASK;
#else
const uint8_t rclRegulatoryMask = RCL_REGULATORY_MASK;
#endif

#endif /* CONFIG_SOC_CC2755P10 */