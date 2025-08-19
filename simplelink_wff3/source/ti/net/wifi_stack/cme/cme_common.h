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
/*
 * cme_common.h
 *
 *  Created on: Jan 31, 2021
 *      Author: a0387677
 */

#ifndef CME_CME_COMMON_H_
#define CME_CME_COMMON_H_

#include "wlan_if.h"

typedef struct
{
    uint8_t     SsidLen;
    uint8_t     SsidName[32];
    uint8_t     Bssid[6];
    uint8_t     ReasonCode;
} CMEWlanEventDisconnect_t;


typedef struct{
    uint16_t    SecType;
    uint8_t     SsidLen;
    uint8_t     Priority;
    uint8_t     Bssid[6];
    uint8_t     PasswordLen;
    uint8_t     WepKeyId;
    uint8_t     FastTransition;
} CMEWlanAddGetProfile_t;


typedef struct{
    uint8_t SecType;
    uint8_t SsidLen;
    uint8_t Bssid[6];
    uint8_t PasswordLen;
    uint8_t FastTransition;
} CMEWlanConnectCommon_t;

#define CME_MAX_SCAN_SSID 5
#define CME_SSID_MAX_LENGTH               (32)

typedef struct
{
    uint8_t  ssidLen;
    uint8_t  pSsid[CME_SSID_MAX_LENGTH];
    uint8_t  mHidden;// 1 = SSID_TYPE_HIDDEN, 0 = SSID_TYPE_PUBLIC
    uint8_t  padding[2];
}CMEWlanSsid_t;

typedef struct
{
    CMEWlanSsid_t CMEWlanSsid[CME_MAX_SCAN_SSID];
    WlanBandCfg_e Band;//0  - 2.4, 1 = 5G , 2 = Both
    uint8_t extWpsMode;
    WlanRole_e roleType;
}CMEWlanScanCommon_t;


#define SSID_STRING(pCmd)       ((int8_t *)((CMEWlanConnectCommon_t *)(pCmd) + 1))
#define PASSWORD_STRING(pCmd)   (SSID_STRING(pCmd) + ((CMEWlanConnectCommon_t *)(pCmd))->SsidLen)

typedef enum
{
    CME_SEC_TYPE_OPEN,
    CME_SEC_TYPE_WEP,
    CME_SEC_TYPE_WPA_WPA2,
    CME_SEC_TYPE_WPS_PBC,
    CME_SEC_TYPE_WPS_PIN,
    CME_SEC_TYPE_WPA2_PLUS  = 11,
    CME_SEC_TYPE_WPA3       = 12,

    CME_SEC_TYPE_WPA2_WPA3 = 16,

    CME_SEC_TYPE_WEP_SHARED

} CMESecType_e;

typedef struct
{
    uint8_t   MacAddress[6];
    uint16_t  Reserved;
} CMEWlanApRemovePeer_t;



#endif /* CME_CME_COMMON_H_ */
