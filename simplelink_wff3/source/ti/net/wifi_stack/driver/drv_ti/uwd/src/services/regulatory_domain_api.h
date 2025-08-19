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
/** \file regulatory_domain_api.h
 *  \brief regulatoryDomain module interface header file
 *
 *  \see regulatory_domain.c & regulatory_domain.h
 */

/***************************************************************************/
/*                                                                         */
/*    MODULE:   regulatory_domain_api.h                                    */
/*    PURPOSE:  regulatoryDomain module interface header file              */
/*                                                                         */
/***************************************************************************/
#ifndef __REGULATORY_DOMAIN_API_H__
#define __REGULATORY_DOMAIN_API_H__


#include "802_11defs.h"
#include "paramOut.h"
#include "drv_ti_internal.h"

#include <public_types.h>//temporary for ERadioBand

#define CHANNEL_VALIDITY_TS_THRESHOLD   10000   /*10 seconds*/

/*
* macro to convert Dbm units into Dbm/10 units. This macro is important
* in order to avoid over-flow of Dbm units bigger than 25
*/
#define DBM2DBMDIV10(uTxPower) \
	((uTxPower) > (MAX_TX_POWER / DBM_TO_TX_POWER_FACTOR) ? \
		MAX_TX_POWER : (uTxPower) * DBM_TO_TX_POWER_FACTOR)

#define DBM_DIV_10_2_DBM(uTxPower) (uTxPower / DBM_TO_TX_POWER_FACTOR)


typedef struct
{
    Bool32    channelValidityPassive; /*TI_TRUE-valid, TI_FALSE-invalid */
    Bool32    channelValidityActive; /*TI_TRUE-valid, TI_FALSE-invalid */
    uint32_t  uFlags;
    uint8_t   uMaxTxPowerDomain;     /*
									  * Holds ONLY the default limitation (Application) 
									  * or according to 11d country code IE	
									  * Updated on init phase or upon receiving new country code IE				  
									  */ 
	uint32_t  timestamp;
}   channelCapability_t;

typedef struct
{
	uint16_t 		channelNum;
	Bool32			channelValidity;
//	ERadioBand		band;
} channelValidity_t;

typedef struct
{
    uint32_t   uChannel;
//    ERadioBand  eBand;
    Bool32     bDfsChannel;
} TDfsChannel;

typedef struct
{
    uint8_t       minTxPower;
    uint8_t       maxTxPower;
} powerCapability_t;

typedef struct
{
//	regulatoryDomain_scanOption_e 	scanOption;	/**< Desired scan type (passive or active)		*/
	uint8_t						channelNum; /**< Channel on which scan is to be performed	*/
//	ERadioBand                     	band; 		/**< Band on which scan is to be performed		*/
}	channelCapabilityReq_t;

/** \struct channelCapabilityRet_t
 * \brief Channel Capability Response
 *
 * \par Description
 * Defines scan capabilities information, which is given as a response to a scan capabilities query.
 *
 * \sa
 */
typedef struct
{
    Bool32 	channelValidity;	/**< Indicates whether the channel is valid for the requested scan type.
									* TRUE: channel is valid; FALSE: not valid
									*/
	uint8_t	maxTxPowerDbm; 		/**< Maximum TX power level allowed on this channel from 1 to 5,
									* where 1 is the highest and 5 is the lowest. Units: Dbm/10
									*/
	Bool32 	dfsChannel;
}	channelCapabilityRet_t;


/** \struct channelCapabilityReq_t
 * \brief Channel Capability Resuest
 *
 * \par Description
 * Defines the regulatory domain scan capability query information
 *
 * \sa
 */

typedef struct
{
    uint8_t    Channel[REG_DOMAIN_MAX_CHAN_NUM];
//    BandType_e  band;
}RegClassChannelList_t;

typedef int32_t (*RoleSetTxPowerCb)(uint8_t uTxPower, void * hRoleContext);

/* note: if some output paramter is not needed, it may be null */
typedef int32_t (*RoleGetCurrentChannelCb)(void * hRoleContext, uint8_t *currentChannel,
        RadioBand_e *radioBand);

//typedef int32_t (*RoleGetConnectionStatusCb)(void * hRoleContext,
//                                               TIWLN_DOT11_STATUS *connectionStatus);

/*
 * structure provided by role containing callbacks and a context passed
 * to each callback.
 */
typedef struct
{
    RoleSetTxPowerCb          setTxPower;
    RoleGetCurrentChannelCb   getCurrentChannel;
//    RoleGetConnectionStatusCb getConnectionStatus;

    void *               hRoleContext;
} regulatoryDomainCallbacks_t;




//void * regulatoryDomain_create(void * hOs);
void    regulatoryDomain_init (/*TModuleHandleTable *pStadHandles*/);
void    regulatoryDomain_SetChannels (/*void *  hRegulatoryDomain,
//                                        regulatoryDomainInitParams_t *pRegulatoryDomainInitParams*/);
//int32_t regulatoryDomain_ConfigFw(void * hRegDomain, TRegDomainConfigCompleteCb RegDomainConfigCompleteCb,  void * hDrvMain);
//void regulatoryDomain_FwConfigurationCompleted(void * hRegDomain, TI_CHAR* str , uint32_t strLen, uint32_t uEventId);
//int32_t regulatoryDomain_setParam(void * hRegulatoryDomain, paramInfo_t *pParam);
//int32_t regulatoryDomain_getParam(void * hRegulatoryDomain, paramInfo_t *pParam);
//int32_t regulatoryDomain_RoleInit(void * hRegDomain, uint8_t netifId,
//                                    regulatoryDomainCallbacks_t *callbacks,
//                                    void * *phRegDomainRoleHandle);
//void regulatoryDomain_RoleDestroy(void * hRegDomain, void * hRegDomainRoleHandle);
//void * regulatoryDomain_GetRoleHandle(void * hRegDomain, uint8_t netifId);
//int32_t regulatoryDomain_destroy(void * hRegulatoryDomain);
void regulatoryDomain_UpdateChannelValidity(uint8_t uChannel, Bool32 updateFw);
//void regulatoryDomain_SetTempTxPower(void * hRegulatoryDomain, void * hRegDomRole, Bool32 bTempTxPowerEnable);
void regulatoryDomain_SetDisconnect(void * hRegulatoryDomain, void * hRegDomRole);
//int32_t regulatoryDomain_UpdateCurrTxPower(void * hRegulatoryDomain, void * hRegDomRole);
int32_t regulatoryDomain_GetPowerCapability(powerCapability_t *pPowerCapability);
//void regulatoryDomain_SetPowerConstraint(void * hRegulatoryDomain, void * hRegDomRole, uint8_t uPowerConstraint);
Bool32 regulatoryDomain_IsChannelSupported(uint8_t uChannel, Bool32 *isDfsChannel);
void regulatoryDomain_SetChannelValidity(channelValidity_t *tChannelValidity);
//void regulatoryDomain_SetExternTxPowerPreferred(void * hRegulatoryDomain, void * hRegDomRole, uint8_t uExternTxPowerPreferred);
//int32_t regulatoryDomain_GetChannelCapability(void * hRegulatoryDomain,
//                                                void * hRegDomRole,
//                                                channelCapabilityReq_t *pChannelCapabilityReq,
//												channelCapabilityRet_t *pChannelCapabilityRet);
//int32_t regulatoryDomain_GetRadioBandByRegClass(void * hRegulatoryDomain, uint8_t uRegClass, BandType_e *pBandType);
//int32_t regulatoryDomain_GetChannelsByRegClass(void * hRegulatoryDomain, uint8_t uRegClass, RegClassChannelList_t *pChannelList);
//uint8_t regulatoryDomain_GetRegClassByChannelAndBand(void * hRegulatoryDomain, BandType_e eBand, uint8_t uChannel);
//uint8_t regulatoryDomain_getMaxPowerAllowed(void * hRegulatoryDomain,
//                                             void * hRegDomRole,
//                                             uint8_t uChannel,
//                                             ERadioBand eBand,
//                                             Bool32 bServingChannel);
//void regulatoryDomain_GetActiveChannels(void * hRegulatoryDomain, tiwdrv_ap_chan_hw_info_t *pChanInfo);
int32_t regulatoryDomain_GetCapability(RadioBand_e band ,uint16_t channel,channelCapability_t *ChannelCapability);
void regulatoryDomain_GetCahnnelOnBand(RadioBand_e band,supportedChannels_t *supportedChannels);
int32_t regulatoryDomain_setSupportedChannelsAccording2CountryIe (dot11_COUNTRY_t *pCountry,
																	Bool32 band_2_4,
																	Bool32 updateFw);
//int32_t regulatoryDomain_ConfigRegulatoryTables(void * hRegDomain, uint8_t *pBuf, uint32_t uLength);
//void regulatoryDomain_ClearExternalConfig(void * hRegDomain);
int32_t regulatoryDomain_SetCountry(uint8_t *pCountryStr);
Bool_e regulatoryDomain_getChMaxPower(uint16_t channel, uint8_t *max_tx_power);
void regulatoryDomain_setFwMaxTxPower(int8_t maxTxPower);
void regulatoryDomain_setRoleMaxTxPower(ti_driver_ifData_t *pDrv,
										int8_t maxTxPower);
void regulatoryDomain_handlePowerConstraint(ti_driver_ifData_t *pDrv,
                               				uint16_t apCapabilities,
                               				dot11_COUNTRY_t *countryIE,
                               				dot11_POWER_CONSTRAINT_t *powerConstraintIE,
                               				dot11_CELL_TP_t *ciscoDtpcIE);

int32_t regulatoryDomain_getCountryString(uint8_t *pCountryStr);

#endif /* __REGULATORY_DOMAIN_API_H__*/


