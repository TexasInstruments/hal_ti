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
/** \file regulatoryDomain.h
 *  \brief regulatoryDomain module internal header file
 *
 *  \see regulatoryDomain.c
 */

/***************************************************************************/
/*                                                                         */
/*    MODULE:   regulatory_domain.h                                        */
/*    PURPOSE:  regulatoryDomain module internal header file               */
/*                                                                         */
/***************************************************************************/


#ifndef __REGULATORY_DOMAIN_H__
#define __REGULATORY_DOMAIN_H__

#include "init_table_types.h"
#include "paramOut.h"
#include "802_11defs.h"
#include "regulatory_domain_api.h"

//#define REG_DOMAIN_LOG_REPORT
#ifdef REG_DOMAIN_LOG_REPORT
#define REG_DOMAIN_PRINT_REPORT Report
#define REG_DOMAIN_PRINT_REPORT_ERROR Report
#else
#define REG_DOMAIN_PRINT_REPORT(...)
#define REG_DOMAIN_PRINT_REPORT_ERROR Report
#endif

#define TIW_REG_DOMAIN_DFS 0x00000001
#define TIW_REG_DOMAIN_HT40PLUS 0x00000002
#define TIW_REG_DOMAIN_HT40MINUS 0x00000004


#define BG_24G_BAND_CHANNEL_HOPS    1
#define BG_24G_BAND_MIN_CHANNEL     1

#define A_5G_BAND_CHANNEL_HOPS      4

#define REG_DOMAIN_MAX_ROWS_IN_COUNTRY	7


/* Added for the 802.11k support  - Start*/
typedef enum
{
    REGULATORY_ZONE_USA = 0,
    REGULATORY_ZONE_JAPAN,
    REGULATORY_ZONE_RST, /* Europe + Rest of the world */
    REGULATORY_ZONE_NONE,
    REGULATORY_ZONE_MAX
} RegulatoryZone_e;

typedef volatile enum
{
  REG_DOMAIN_FCC_REGION =       0, 
  REG_DOMAIN_TELEC_REGION =     1,
  REG_DOMAIN_WORLDWIDE_REGION = 2, // minimum of all 3 regions will be used
  REG_DOMAIN_ETSI_REGION =      3,
  REG_DOMAIN_NOLIMIT_REGION =   4, // no reg limit : only ieee specs will be met
  REG_DOMAIN_MAX_REGION =       5
} RegDomainRegion_e;

typedef struct
{
    uint8_t    MinClass;
    uint8_t    MaxClass;
    uint8_t    NumChan;
    uint8_t    TxPower;
    uint8_t/*RadioBand_e*/  band;
    uint16_t   Freq;
    uint8_t    Channel[REG_DOMAIN_MAX_CHAN_NUM];
}RegDomainChanPerClass_t;

typedef struct
{
    RegulatoryZone_e            CountryZone;
    RegDomainChanPerClass_t     DomainReg[REG_DOMAIN_MAX_REG_CLASS_NUM];
}RegDomainCalssesInfo_t;

/* Added for the 802.11k support  - End*/

typedef struct
{
	char             CountryStr[DOT11_COUNTRY_STRING_LEN];
    RegDomainChan_t  DomainReg[REG_DOMAIN_MAX_ROWS_IN_COUNTRY];
}RegDomainCountryInfo_t;


/* A per-role context for using the regulatoryDomain module */
typedef struct
{
    /* if id associated with this context, for destroy */
    uint8_t uNetifId;

    /* Desired Temp Tx Power */
    uint8_t                            uDesiredTemporaryTxPower;
    /* Actual Temp Tx Power */
    uint8_t                            uTemporaryTxPower;
    /* User configuration for max Tx power */
    uint8_t                            uUserMaxTxPower;
    /* Tx Power Control adjustment flag on=TI_TRUE\off=TI_FALSE */
    Bool32                             bTemporaryTxPowerEnable;
    /* Power Constraint IE 32 in DBM/10, valid only when 802.11h is enabled  */
    uint8_t                            uPowerConstraint;
    /* External TX Power Control in DBM/10, valid only when 802.11h is disabled */
    uint8_t                            uExternTxPowerPreferred;

    /* role provided callbacks */
    regulatoryDomainCallbacks_t         callbacks;
} regulatoryDomainRole_t;

typedef struct 
{
    uint32_t chBitMap1;
    uint32_t chBitMap2;
} RegDomainChannelConfigBitField_t;

typedef struct
{
    /* Variables read from registry */
    /********************************/   
    /* 802.11h enabled or disabled */
    Bool32                            	spectrumManagementEnabled;

	Bool32                            	japanChannelsEnabled;
    
    /* default values for Tx power before override by the role */
    uint8_t                            defDesiredTxPower;
    uint8_t                            defTemporaryTxPower;

    RegulatoryZone_e                    countryZone;
    RegDomainRegion_e                   countryDomain;

	RegDomainCountryInfo_t				*pRegDomainTable;
	uint32_t							uNumOfCountriesInTable;
    
    /* Internal reg domain variables */
    /*********************************/

	uint32_t							uDontOverride; /* Not in use currently, should be set to zero */
	Bool32								bFwUpdateRequired;
    dot11_COUNTRY_t                		country24;   /* Detected County IE for 2.4 Ghz */
    dot11_COUNTRY_t                		country5;    /* Detected County IE for 5 Ghz */
    channelCapability_t             	supportedChannels_band_5[A_5G_BAND_NUM_CHANNELS];
    channelCapability_t             	supportedChannels_band_2_4[NUM_OF_CHANNELS_24];

    /* set the size of the array to max of B_G & A, so that the array doesnt overflow. +3 for word alignment */
	uint8_t                        	pDefaultChannels[A_5G_BAND_NUM_CHANNELS+3];
    
	RegDomainChannelConfigBitField_t	fwRegDomainChannelBitField;

    /* handler to the CB function when the TWD_OWN_DFS_CHANNELS_CONFIG_COMPLETE event is sent */
//    TRegDomainConfigCompleteCb          regDomainConfigCompleteCb;
    void *                           hRegDomainConfigComplete;

    /* Handles to other objects */
    void *                       	hTWD;
    void *                       	hReport;
    void *                       	hOs;
    void *                       	hRolesMngr;
	void *                       	hEvHandler;
    void *                           hTimer;
    void *                           hConfigTimer;
    void *                           hHealthMonitor;

	void *               			hRegDomainTimer;

    /* A mapping between if id and regulatoryDomainRole_t */
//    void * ifaces[TIWDRV_NETIF_NUM];
} RegulatoryDomain_t;



#endif /* __REGULATORY_DOMAIN_H__*/

