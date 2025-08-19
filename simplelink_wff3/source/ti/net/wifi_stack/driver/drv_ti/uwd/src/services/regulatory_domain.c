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
/** \file regulatoryDomain.c
 *  \brief regulatoryDomain module interface
 *
 *  \see regulatoryDomain.h
 */

/************************************************************************************************/
/*  												                                            */
/*		MODULE:		regulatory_domain.c					                                        */
/*		PURPOSE:	regulatoryDomain module interface.			                                */
/*                  This module calculated the channel that should be scanned and that are      */
/*                   supported. Moreover, he set the transmit power level according to the      */
/*                   regulatory domain requirements and the supported channel.                  */
/*								 			                                                    */
/************************************************************************************************/
//#define __FILE_ID__  FILE_ID_3
#include "paramOut.h"
#include "regulatory_domain.h"
#include "regulatory_domain_api.h"


#include <public_types.h>
#include "gtrace.h"
#include "string.h"
#include "osi_kernel.h"
#include "802_11defs.h"
#include "80211_utils.h"
#include "control_cmd_fw.h"

#include "macro_utils.h"

#define CHANNEL_VALIDITY_TS_THRESHOLD   10000 /* 10 sec */

#define WORLD_WIDE_ACTIVE_2_4_CHANNEL   11
#define WORLD_WIDE_2_4_CHANNEL_HT40_MIN 3
#define WORLD_WIDE_2_4_CHANNEL_HT40_MAX 7

#define FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G		(0x3FFF)
#define FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G	(0x3FFC0000)
#define FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G	(0x7FFFFFFF)

#define REG_DOMAIN_TIMEOUT_MSEC 5000 /* 5 sec*/

#define REG_DOMAIN_MAX_REGION 5

typedef struct
{
    uint8_t  band;
	uint8_t  txPowerPerRegion[REG_DOMAIN_MAX_REGION];
    uint8_t  DfsChannel;
    uint16_t minChannel;
    uint16_t maxChannel;
    uint8_t  numOfChannels;
    uint32_t chanBitmap; // bitmap instead of table of Channel[REG_DOMAIN_MAX_CHAN_NUM];
} ConfigChanPattern_t;

typedef struct
{
    uint8_t chanAmount;
    uint8_t chanPatternsList[REG_DOMAIN_MAX_ROWS_IN_COUNTRY];
} ConfigGroupChanPatterns_t;

typedef struct
{
    uint8_t CountryStr[REG_DOMAIN_COUNTRY_STR_LEN];
    uint8_t Region;
} ConfigCountryCompressed_t;

const ConfigChanPattern_t rom_gConfigChanPatternsTable[] = {
   //Bnd Tx(US  JP  WW  EU NoLimit  Dfs minCh MaxCh NumCh chanBitmap 		     Index Count      Bnd Tx   Dfs Num Channels:  
    { 0,  { 30, 0 , 20, 0 , 0},     0,   1,    11,    11, 0x000007ff }, 	//   0,    20 	    { 0,  20,  0,  11, 1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20, 20, 0},     1,   12,   13,    2,  0x00001800 }, 	//   1,     1 	    { 0,  20,  1,  2,  12,  13,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20, 0 , 0},     1,   14,   14,    1,  0x00002000 }, 	//   2,     1 	    { 0,  20,  1,  1,  14,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 20, 20, 20, 0},     1,   36,   48,    4,  0x0000000f }, 	//   3,     1 	    { 1,  20,  1,  4,  36,  40,  44,  48,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 20, 20, 20, 0},     1,   52,   64,    4,  0x000000f0 }, 	//   4,   160 	    { 1,  20,  1,  4,  52,  56,  60,  64,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 23, 20, 27, 0},     1,   100,  144,   12, 0x000fff00 }, 	//   5,   127 	    { 1,  20,  1,  11, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,0,  0,  0,   },
    { 1,  { 30, 23, 20, 0 , 0},     1,   149,  161,   4,  0x00f00000 }, 	//   6,     1 	    { 1,  20,  1,  4,  149, 153, 157, 161, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20, 20, 0},     0,   1,    13,    13, 0x00001fff }, 	//   7,   156 	    { 0,  20,  0,  13, 1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12, 13, 0,  0,   },
    { 1,  { 23, 20, 20, 20, 0},     0,   36,   48,    4,  0x0000000f }, 	//   8,   160 	    { 1,  20,  0,  4,  36,  40,  44,  48,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 30, 0 , 20, 0 , 0},     0,   149,  161,   4,  0x00f00000 }, 	//   9,    85 	    { 1,  20,  0,  4,  149, 153, 157, 161, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 30, 20, 20, 0 , 0},     0,   165,  165,   1,  0x01000000 }, 	//  10,     1 	    { 1,  20,  0,  1,  165, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 2,  { 23, 20, 20, 20, 0},     0,   184,  196,   4,  0x3c000000 }, 	//  11,     1 	    { 2,  20,  0,  4,  184, 188, 192, 196, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
};

const ConfigGroupChanPatterns_t rom_gConfigGroupChanPatternsTable[] = {
    /*Index  Count   Num of channels Channels:*/
    /*    0,    6 */    { 6, {  0,  8,  4,  5,  9,  10 } },
    /*    1,    6 */    { 6, {  7,  8,  4,  5,  6,  10 } },
    /*    2,    5 */    { 5, {  0,  8,  4,  5,  6 } },
    /*    3,    5 */    { 5, {  7,  8,  4,  5,  6 } }
};

const ConfigCountryCompressed_t rom_gConfigCountryCompressedTable[] = {
      //       Country   Rgn:
    { /* US */ 		'U','S',0}, // FCC - min of FCC/IC/Taiwan
    { /* JP */ 		'J','P',1}, // ROW(rest of the world) - Min of JP/EU
    { /* WW_SAFE*/  '0','0',2}, // WWS(worldwide safe) - Min of FCC&ROW
    { /* ID */ 		'I','D',3}  // Indonesia 

};

int                        gNumCompressedCountries       = sizeof(rom_gConfigCountryCompressedTable)/sizeof(ConfigCountryCompressed_t);
ConfigChanPattern_t       *gConfigChanPatternsTable      = (ConfigChanPattern_t *)rom_gConfigChanPatternsTable;
ConfigGroupChanPatterns_t *gConfigGroupChanPatternsTable = (ConfigGroupChanPatterns_t *)rom_gConfigGroupChanPatternsTable;
ConfigCountryCompressed_t *gConfigCountryCompressedTable = (ConfigCountryCompressed_t *)rom_gConfigCountryCompressedTable;
uint8_t                    gCountryDomainStr[3] = {0};//options are {0} as default {"US"} {"JP"} {"EU"} {"00"}


char rom_dot11g_channels[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
char rom_dot11a_channels[] = { 36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 149, 153, 157, 161,165};//, 165, 169, 184, 188, 192, 196, 254, 255 };


const uint8_t DefaultGBandChannels[NUM_OF_CHANNELS_24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,0};//removed ch14 not supported
const uint8_t DefaultABandChannels[A_5G_BAND_NUM_CHANNELS] = {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
	0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // channel 144,165 are now supported
const uint16_t JapanABandChannels[] = {34, 38, 42, 46, 0};
//
///*************************** Static Table for Regulatory Class **********************/
//
// This table is for fast roaming which is not supported and therefore no need to enable it
//
//RegDomainCalssesInfo_t RegClassTbl[REGULATORY_ZONE_MAX] = {
//                                  {REGULATORY_ZONE_USA, /* Country*/
//                                  {{1,1,4,30,BAND_TYPE_5_GHZ,5000,{36,40,44,48,0,0,0,0,0,0,0,0,0,0,0}}, /* min class, max class, num of channel,to power, base freq, channel list*/
//                                  {2,2,4,23,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {3,3,4,29,BAND_TYPE_5_GHZ,5000,{149,153,157,161,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {4,4,11,23,BAND_TYPE_5_GHZ,5000,{100,104,108,112,116,120,132,136,140,0,0,0,0,0,0}},
//                                  {5,5,5,30,BAND_TYPE_5_GHZ,5000,{149,153,157,161,165,0,0,0,0,0,0,0,0,0,0}},
//                                  {10,10,2,20,BAND_TYPE_4_9GHZ,4850,{20,25,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {11,11,2,33,BAND_TYPE_4_9GHZ,4850,{20,25,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {12,12,11,30,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_JAPAN,
//                                  {{1,1,4,13,BAND_TYPE_5_GHZ,5000,{34,38,42,46,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {2,6,3,13,BAND_TYPE_5_GHZ,5000,{8,12,16,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {7,11,4,13,BAND_TYPE_4_9GHZ,4000,{184,188,192,196,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {30,30,13,13,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {31,31,1,13,BAND_TYPE_2_4GHZ,2414,{14,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {32,32,4,13,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_RST, /* Europe + Rest of the world */
//                                  {{1,1,4,23,BAND_TYPE_5_GHZ,5000,{36,40,44,48,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {2,2,4,23,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {3,3,11,30,BAND_TYPE_5_GHZ,5000,{100,104,108,112,116,120,124,128,132,136,140,0,0,0,0}},
//                                  {4,4,13,20,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_NONE,
//                                  {{100,100,11,13,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}}
//                                  };
//


RegulatoryDomain_t          RegulatoryDomain;

///********************************************************************************/
///*						Internal functions prototypes.							*/
///********************************************************************************/
//static int32_t setSupportedChannelsAccording2confCountry(RegulatoryDomain_t *pRegulatoryDomain,
//														   uint8_t *pCountryString);
static void setWorldWideDomainSupportedChannels();
//static void getPowerTableMinMax (RegulatoryDomain_t *pRegulatoryDomain,
//                                                  powerCapability_t  *pPowerCapability);
//static void RegDomainConfigSentToFw(void * handle, uint16_t uMboxStatus, Bool32 *pSuspendRequired);
//static void RegDomainTmrExpiry(void * hRegDomain, Bool32 bTwdInitOccured);
static void sendRegDomainCmdToFw();
static void verifyDfsChannelValidity(channelCapability_t *pSupportedChannels, uint8_t channelIndex);
//static uint32_t readNumOfConfiguredCountries(RegulatoryDomain_t *pRegulatoryDomain, uint8_t *pBuf,
//											  uint32_t uBuffLen, uint16_t idxTLV);
static int32_t getCountryIdInTable(uint8_t *pCountryStr, uint32_t *pCountryID);
static Bool32 isDfsChannelInCountry(uint32_t cntrId, uint32_t uChannel);
static Bool32 setChannelAsFwBitmap(uint16_t channelNumber, Bool32 band_2_4, Bool32 shouldSet);
static int8_t getChannelIndexTranslation(uint16_t chNumber, Bool32 band_2_4);

static int8_t setSupportedChannelsAccording2Domain(void);


///********************************************************************************/
///*						Interface functions Implementation.						*/
///********************************************************************************/
//
///************************************************************************
// *                        regulatoryDomain_create						*
// ************************************************************************
//DESCRIPTION: regulatoryDomain module creation function, called by the config mgr in creation phase
//				performs the following:
//				-	Allocate the regulatoryDomain handle
//
//INPUT:      hOs -			Handle to OS
//
//
//OUTPUT:
//
//RETURN:     Handle to the regulatoryDomain module on success, NULL otherwise
//
//************************************************************************/
//void * regulatoryDomain_create()
//{
//	RegulatoryDomain_t			*pRegulatoryDomain = NULL;
//
//	/* allocating the regulatoryDomain object */
//	pRegulatoryDomain = os_memoryAlloc(hOs,sizeof(RegulatoryDomain_t));
//
//	if (pRegulatoryDomain == NULL)
//		return NULL;
//
//    os_memoryZero(hOs, pRegulatoryDomain, sizeof(RegulatoryDomain_t));
//
//	return(pRegulatoryDomain);
//}


///************************************************************************
// *                        regulatoryDomain_init							*
// ************************************************************************
//DESCRIPTION: Module init function, Called by the DrvMain in init phase
//				performs the following:
//				-	Reset & initializes local variables
//				-	Init the handles to be used by the module
//
//INPUT:      pStadHandles - List of handles to be used by the module
//
//OUTPUT:
//
//RETURN:     void
//************************************************************************/
void regulatoryDomain_init (/*TModuleHandleTable *pStadHandles*/)
{
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)(pStadHandles->hRegulatoryDomain);
//    int i;
//
//    /* Init handlers */
//    pRegulatoryDomain->hTWD	          = pStadHandles->hTWD;
//	pRegulatoryDomain->hReport	      = pStadHandles->hReport;
//	pRegulatoryDomain->hOs	          = pStadHandles->hOs;
//    pRegulatoryDomain->hEvHandler     = pStadHandles->hEvHandler;
//	pRegulatoryDomain->hTimer		  = pStadHandles->hTimer;
//    pRegulatoryDomain->hHealthMonitor = pStadHandles->hHealthMonitor;
//
//    for (i = 0; i < DRIVER_ROLE_ID_NUM; i++)
//        pRegulatoryDomain->ifaces[i] = NULL;

    // TODO: need to implement ZeroMem??
    //ZeroMem(&RegulatoryDomain, sizeof(RegulatoryDomain_t));
    os_memset(&RegulatoryDomain, 0x00, sizeof(RegulatoryDomain_t));

    regulatoryDomain_SetChannels();
}


///************************************************************************
// *                        regulatoryDomain_SetChannels					*
// ************************************************************************
//DESCRIPTION: regulatoryDomain module configuration function, called by the config mgr in configuration phase
//				performs the following:
//				-	Reset & initializes local variables
//				-	Init the handles to be used by the module
//
//INPUT:      hRegulatoryDomain	-	regulatoryDomain handle
//			List of handles to be used by the module
//			pRegulatoryDomainInitParams	-	Init table of the module.
//
//
//OUTPUT:
//
//RETURN:     OK on success,-1 otherwise
//
//************************************************************************/
void regulatoryDomain_SetChannels (/*void * 	hRegulatoryDomain,
                                        regulatoryDomainInitParams_t *pRegulatoryDomainInitParams*/)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);
	
//    pRegulatoryDomain->japanChannelsEnabled = pRegulatoryDomainInitParams->japanChannelsEnabled;

    if (gCountryDomainStr[0] == '\0')
    {
        REG_DOMAIN_PRINT_REPORT("CountryDomainStr[0] is NULL set worldwide reg domain\n ");
        setWorldWideDomainSupportedChannels();
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_USA;
    }
    else
    {
        REG_DOMAIN_PRINT_REPORT("CountryDomainStr[0] has value \n");
        setSupportedChannelsAccording2Domain();
        pRegulatoryDomain->uNumOfCountriesInTable = REG_DOMAIN_MAX_REGION;
    }



//    pRegulatoryDomain->defDesiredTxPower = pRegulatoryDomainInitParams->desiredTxPower;
//    pRegulatoryDomain->defTemporaryTxPower = pRegulatoryDomainInitParams->uTemporaryTxPower;

	/* allocate OS timer memory */
//	pRegulatoryDomain->hRegDomainTimer = tmr_CreateTimer(pRegulatoryDomain->hTimer);
//	if (pRegulatoryDomain->hRegDomainTimer == NULL)
//	{
//		TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_SetChannels(): Failed to create hRegDomainTimer!\n");
//		regulatoryDomain_destroy(hRegulatoryDomain);
//		return-1;
//	}

//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INIT, ".....Regulatory domain configured successfully\n");
}


///************************************************************************
// *                        regulatoryDomain_ConfigFw                     *
// ************************************************************************
//DESCRIPTION: regulatoryDomain module fw configuration function,
//
//
//INPUT:
//
//
//OUTPUT:
//
//RETURN:     OK on success,-1 otherwise
//*/
//int32_t regulatoryDomain_ConfigFw(void * hRegDomain,TRegDomainConfigCompleteCb regDomainConfigCompleteCb,
//									 void * hRegDomainConfigCompleteCb)
//{
//    RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, " - regulatoryDomain register Called\n");
//
//    pRegulatoryDomain->regDomainConfigCompleteCb = regDomainConfigCompleteCb;
//    pRegulatoryDomain->hRegDomainConfigComplete = hRegDomainConfigCompleteCb;
//
//    TWD_RegisterEvent(pRegulatoryDomain->hTWD,
//					  TWD_OWN_REG_DOMAIN_CONFIG_COMPLETE,
//					  regulatoryDomain_FwConfigurationCompleted,
//					  hRegDomain,
//					  ROLE_NONE);
//
//    /* Update the FW with current regulatory domain values*/
//	if (TWD_SendCmd(pRegulatoryDomain->hTWD,
//					CMD_REG_DOMAIN_CHANNEL_CONFIG,
//					(void *)&pRegulatoryDomain->fwRegDomainChannelBitField,
//					sizeof(RegDomainChannelConfigBitField_t),
//					NULL, NULL) != OK)
//    {
//       TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR ,
//              "regulatoryDomain_ConfigFw(): Failed to configure REG domain channels to the FW\n");
//       return-1;
//    }
//
//    return OK;
//}
//
//
//void regulatoryDomain_FwConfigurationCompleted(void * hRegDomain, TI_CHAR* str , uint32_t strLen, uint32_t uEventId)
//{
//    RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, " - regulatoryDomain_ConfigFwCompleted: Called\n");
//
//    /* Reg domain configuration to FW completed - stop the timer*/
//	if (pRegulatoryDomain->hRegDomainTimer)
//		tmr_StopTimer(pRegulatoryDomain->hRegDomainTimer);
//
//    if (pRegulatoryDomain->regDomainConfigCompleteCb != NULL)
//    {
//		/* If CB was registered, this is init time - mbox not suspended*/
//		pRegulatoryDomain->regDomainConfigCompleteCb(pRegulatoryDomain->hRegDomainConfigComplete ,1);
//		pRegulatoryDomain->regDomainConfigCompleteCb = NULL;
//		pRegulatoryDomain->hRegDomainConfigComplete = NULL;
//    }
//	else
//	{
//        /* CB not registered - this is not init - resume the MBOX operation*/
//        TWD_ResumeCmdQueue(pRegulatoryDomain->hTWD);
//	}
//}
//
//
//int32_t regulatoryDomain_RoleInit(void * hRegDomain, uint8_t netifId,
//                                    regulatoryDomainCallbacks_t *callbacks,
//                                    void * *phRegDomainRoleHandle)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//    regulatoryDomainRole_t *pRegDomRole = NULL;
//
//    if (pRegulatoryDomain->ifaces[netifId] != NULL) {
//        GTRACE(GRP_GENERAL_ERROR,
//               "regulatoryDomain_RoleInit, ifaces %d is taken", netifId);
//        return-1;
//    }
//
//    /* check all the callbacks are implemented */
//    if (!callbacks->getConnectionStatus || !callbacks->setTxPower || !callbacks->getCurrentChannel) {
//        GTRACE(GRP_GENERAL_ERROR,
//               "regulatoryDomain_RoleInit - all role callbacks must be valid");
//        return-1;
//    }

//    pRegDomRole = os_memoryAlloc(pRegulatoryDomain->hOs, sizeof(regulatoryDomainRole_t));
//    if (!pRegDomRole) {
//        GTRACE(GRP_GENERAL_ERROR,
//               "could not allocate memory for role specific regdomain context");
//        return-1;
//    }
//
//    pRegulatoryDomain->ifaces[netifId] = (void *)pRegDomRole;
//    pRegDomRole->uNetifId = netifId;
//    memcpy(&pRegDomRole->callbacks, callbacks,
//                  sizeof(regulatoryDomainCallbacks_t));
//
//	/* User max Tx power for all channels */
//	pRegDomRole->uUserMaxTxPower = pRegulatoryDomain->defDesiredTxPower;
//
//    /* Temporary Tx Power control to be used */
//    pRegDomRole->uTemporaryTxPower = pRegulatoryDomain->defTemporaryTxPower;
//    pRegDomRole->uDesiredTemporaryTxPower = pRegulatoryDomain->defTemporaryTxPower;
//
//	pRegDomRole->uExternTxPowerPreferred	= MAX_TX_POWER;	/* i.e. no restriction */
//	pRegDomRole->uPowerConstraint			= MIN_TX_POWER;	/* i.e. no restriction */
//
//    *phRegDomainRoleHandle = (void *)pRegDomRole;
//    return OK;
//}
//
//
//void regulatoryDomain_RoleDestroy(void * hRegDomain, void * hRegDomainRoleHandle)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//	regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t *)hRegDomainRoleHandle;
//
//    if(pRegDomRole->uNetifId < TIWDRV_NETIF_NUM)
//    {
//        pRegulatoryDomain->ifaces[pRegDomRole->uNetifId] = NULL;
//        os_memoryFree(pRegulatoryDomain->hOs, (void *)hRegDomainRoleHandle,
//                      sizeof(regulatoryDomainRole_t));
//    }
//    else
//    {
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_RoleDestroy() invalid netif id %d\n", pRegDomRole->uNetifId);
//    }
//}
//
//
//void * regulatoryDomain_GetRoleHandle(void * hRegDomain, uint8_t netifId)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//
//    return (netifId < TIWDRV_NETIF_NUM ? pRegulatoryDomain->ifaces[netifId] : NULL);
//}
//
//
//int32_t regulatoryDomain_setParam(void * hRegulatoryDomain,
//									paramInfo_t	*pParam)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//
//    switch(pParam->paramType)
//	{
//		case TI_PARAM_CURRENT_TX_POWER_IN_DBM:
//		{
//			regulatoryDomainRole_t *pRegDomRole;
//
//            pRegDomRole = (void *)regulatoryDomain_GetRoleHandle(hRegulatoryDomain,
//																 pParam->content.txPowerParams.uNetIfId);
//			if (pRegDomRole == NULL)
//			{
//				TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR,
//					  "regulatoryDomain_setParam - TX power - invalid regdom context "
//                       "interface %d\n", pParam->content.txPowerParams.uNetIfId);
//                return-1;
//            }
//
//			/* This case is called when the desired Tx Power Level in Dbm is changed by the user */
//            if(pRegDomRole->uUserMaxTxPower != pParam->content.txPowerParams.desiredTxPower)
//            {
//				pRegDomRole->uUserMaxTxPower = pParam->content.txPowerParams.desiredTxPower;
//
//				/* Set new Tx power to TWD - only if needed ! */
//                return regulatoryDomain_UpdateCurrTxPower(hRegulatoryDomain,
//														  (void *)pRegDomRole);
//            }
//            break;
//        }
//
//		case TI_PARAM_COUNTRY:
//            /* Configuring country internally affects both bands */
//			TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, "REGULATORY_DOMAIN_COUNTRY_PARAM - %c%c\n",
//				  pParam->content.pCountryString[0],pParam->content.pCountryString[1]);
//
//            /* Update the channels according to the new country*/
//			return setSupportedChannelsAccording2confCountry(pRegulatoryDomain, pParam->content.pCountryString);
//
//        default:
//			TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "Set param, Params is not supported, %d\n\n", pParam->paramType);
//			return PARAM_NOT_SUPPORTED;
//	}
//
//	return OK;
//}
//
//
//int32_t regulatoryDomain_getParam(void * hRegulatoryDomain,
//									paramInfo_t	*pParam)
//{
//	RegulatoryDomain_t	*pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//
//	switch(pParam->paramType)
//	{
//
//	case TI_PARAM_TX_POWER_LEVEL_TABLE:
//        {
//            TFwInfo *pFwInfo = TWD_GetFWInfo (pRegulatoryDomain->hTWD);
//
//            os_memoryCopy(pRegulatoryDomain->hOs,
//                          (void *)&pParam->content.powerLevelTable,
//                          (void *)pFwInfo->txPowerTable,
//                          sizeof(pFwInfo->txPowerTable));
//        }
//		break;
//
//    case TI_PARAM_CURRENT_TX_POWER_IN_DBM:
//        {
//            regulatoryDomainRole_t *pRegDomRole;
//
//            pRegDomRole = (void *)regulatoryDomain_GetRoleHandle(hRegulatoryDomain,
//                                                                 pParam->content.txPowerParams.uNetIfId);
//            if (pRegDomRole == NULL) {
//                TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR,
//                       "regulatoryDomain_getParam - TX power - invalid regdom context "
//                       "interface %d\n", pParam->content.txPowerParams.uNetIfId);
//                return-1;
//            }
//
//            /* Get last configured Tx power from TWD */
//            TWD_GetTxPower(pRegulatoryDomain->hTWD, pRegDomRole->uNetifId,
//                           &pParam->content.txPowerParams.desiredTxPower);
//
//            TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION,
//                   "regulatoryDomain_getParam, CURRENT_TX_POWER_IN_DBM  = %d\n",
//                   pParam->content.txPowerParams.desiredTxPower);
//        break;
//        }
//
//    case TI_PARAM_COUNTRY:
//
//        if (!pRegulatoryDomain->country24.hdr[HDR_LENGTH_FIELD])
//			/*Countery was not set yet - report back the deafult domain (world-wide)*/
//            os_memoryCopy(pRegulatoryDomain->hOs, (void*)pParam->content.pCountryString, (void*)"WW ", 3);
//		else
//			/* Countery was set - report it back*/
//			os_memoryCopy(pRegulatoryDomain->hOs, (void*)pParam->content.pCountryString, (void*)pRegulatoryDomain->country24.countryIE.CountryString, DOT11_COUNTRY_STRING_LEN);
//
//		if (!pRegulatoryDomain->country5.hdr[HDR_LENGTH_FIELD])
//			/*Countery was not set yet - report back the deafult domain (world-wide)*/
//			os_memoryCopy(pRegulatoryDomain->hOs, (void*)&pParam->content.pCountryString[DOT11_COUNTRY_STRING_LEN], (void*)"WW ", 3);
//		else
//			/* Countery was set - report it back*/
//			os_memoryCopy(pRegulatoryDomain->hOs, (void*)&pParam->content.pCountryString[DOT11_COUNTRY_STRING_LEN], (void*)pRegulatoryDomain->country5.countryIE.CountryString, DOT11_COUNTRY_STRING_LEN);
//
//		break;
//
//	case TI_PARAM_GET_HW_CAP:
//			regulatoryDomain_GetActiveChannels(pRegulatoryDomain, &pParam->content.hwChannelInfo);
//			break;
//
//   	default:
//		TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "Get param, Params is not supported, %d\n\n", pParam->paramType);
//		return PARAM_NOT_SUPPORTED;
//	}
//
//	return OK;
//}
//
//
///************************************************************************
// *                        regulatoryDomain_destroy						*
// ************************************************************************
//DESCRIPTION: regulatoryDomain module destroy function, called by the config mgr in the destroy phase
//				performs the following:
//				-	Free all memory allocated by the module
//
//INPUT:      hRegulatoryDomain	-	regulatoryDomain handle.
//
//
//OUTPUT:
//
//RETURN:     OK on success,-1 otherwise
//
//************************************************************************/
//int32_t regulatoryDomain_destroy(void * hRegulatoryDomain)
//{
//	RegulatoryDomain_t	*pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//
//	if (pRegulatoryDomain == NULL)
//		return OK;
//
//    /* Release the reg domain timer*/
//	if (pRegulatoryDomain->hRegDomainTimer)
//		tmr_DestroyTimer(pRegulatoryDomain->hRegDomainTimer);
//
//    /* Release the reg domain table*/
//	if (pRegulatoryDomain->pRegDomainTable)
//		os_memoryFree(pRegulatoryDomain->hOs, pRegulatoryDomain->pRegDomainTable, sizeof(pRegulatoryDomain->pRegDomainTable));
//
//    os_memoryFree(pRegulatoryDomain->hOs, pRegulatoryDomain, sizeof(RegulatoryDomain_t));
//
//	return OK;
//}
//
//
void regulatoryDomain_UpdateChannelValidity(uint8_t uChannel, Bool32 updateFw)
{

	uint8_t	             channelIndex;
	channelCapability_t *pSupportedChannels;
	RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	if (pRegulatoryDomain==NULL)
		return;

    if (uChannel>=A_5G_BAND_MIN_CHANNEL && uChannel<A_5G_BAND_MAX_CHANNEL)
	{
		channelIndex = (uChannel-A_5G_BAND_MIN_CHANNEL);
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
	}
	else
		return;

    /* Update validity only if channel is a DFS channel in the current country*/
	if (pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS)
	{
		pSupportedChannels[channelIndex].timestamp = osi_GetTimeMS();//   os_timeStampMs(pRegulatoryDomain->hOs);
        pSupportedChannels[channelIndex].channelValidityActive = TRUE;

        if (setChannelAsFwBitmap(uChannel, FALSE, TRUE))
		{
			if (updateFw)
				sendRegDomainCmdToFw();
			else
				pRegulatoryDomain->bFwUpdateRequired = TRUE;
		}
	}
}
//
//
///* Temporary Tx Power control */
//void regulatoryDomain_SetTempTxPower(void * hRegulatoryDomain, void * hRegDomRole, Bool32 bTempTxPowerEnable)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t *)hRegDomRole;
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, "regulatoryDomain_SetTempTxPower: Temporary Tx power enable = %d, \n", bTempTxPowerEnable);
//	pRegDomRole->bTemporaryTxPowerEnable = bTempTxPowerEnable;
//
//	regulatoryDomain_UpdateCurrTxPower(pRegulatoryDomain, hRegDomRole);
//}


//void regulatoryDomain_SetExternTxPowerPreferred(void * hRegulatoryDomain, void * hRegDomRole, uint8_t uExternTxPowerPreferred)
//{
//    RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t *)hRegDomRole;
//
//    /* Convert to RegDomain units */
//    uint8_t uNewTPC = DBM2DBMDIV10(uExternTxPowerPreferred);
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION,
//           "REGULATORY_DOMAIN_EXTERN_TX_POWER_PREFERRED Old= %d New = %d\n",
//           pRegDomRole->uExternTxPowerPreferred, uNewTPC);
//
//    if ( uNewTPC != pRegDomRole->uExternTxPowerPreferred )
//    {
//        pRegDomRole->uExternTxPowerPreferred = uNewTPC;
//        /* Set new Tx power to TWD - only if needed ! */
//        regulatoryDomain_UpdateCurrTxPower(pRegulatoryDomain, hRegDomRole);
//    }
//
//}


void regulatoryDomain_SetDisconnect(void * hRegulatoryDomain, void * hRegDomRole)
{
	regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t *)hRegDomRole;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    GTRACE(GRP_REG_DOMAIN, "regulatoryDomain_SetDisconnect");

	pRegDomRole->uExternTxPowerPreferred = MAX_TX_POWER;	/* i.e. no restriction */
	pRegDomRole->uPowerConstraint = MIN_TX_POWER;           /* i.e. no restriction */
}


/***********************************************************************
 *              regulatoryDomain_updateCurrTxPower					   *
 ***********************************************************************
DESCRIPTION: Called when new Tx power should be calculated and configured.
			 Check if we are already joined to BSS/IBSS, calculate
			 new Tx power and configure it to TWD.

INPUT:		pRegulatoryDomain	- regulatoryDomain pointer.

RETURN:     OK - New value was configured to TWD,-1 - Can't configure value
			TX_POWER_SET_SAME_VALUE - Same value was already configured.

************************************************************************/
//int32_t regulatoryDomain_UpdateCurrTxPower(void * hRegulatoryDomain, void * hRegDomRole)
//{
//	RegulatoryDomain_t  *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t *)hRegDomRole;
//	int32_t			eStatus;
//	uint8_t			uCurrChannel, uNewTxPower;
//	uint8_t/*RadioBand_e*/			eRadioBand;
//	uint8_t			uTxPower;
//
//	TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, "regulatoryDomain_UpdateCurrTxPower\n");
//
//    eStatus = pRegDomRole->callbacks.getCurrentChannel(pRegDomRole->callbacks.hRoleContext,
//                                                       &uCurrChannel, &eRadioBand);
//	if ( eStatus != OK )
//	{
//		/* We are not joined yet - no meaning for new Tx power */
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION,
//               "regulatoryDomain_updateCurrTxPower, No site selected yet\n");
//		return-1;
//	}
//
//	/* Calculate maximum Tx power for the serving channel */
//	uNewTxPower = regulatoryDomain_getMaxPowerAllowed((void *)pRegulatoryDomain, hRegDomRole,
//                                                      uCurrChannel, eRadioBand, TRUE);
//
//	/* Verify that the Temporary TX Power Control doesn't violate the TX Power Constraint */
//	pRegDomRole->uTemporaryTxPower = TI_MIN(pRegDomRole->uDesiredTemporaryTxPower, uNewTxPower);
//
//    /* set TWD according to Temporary Tx Power Enable flag */
//    if (TRUE == pRegDomRole->bTemporaryTxPowerEnable)
//    {
//        uTxPower = pRegDomRole->uTemporaryTxPower;
//    }
//    else
//    {
//    	uTxPower = uNewTxPower;
//    }
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, "regulatoryDomain_updateCurrTxPower, Write to TWD TxPower = %d, channel=%d, bTemporaryTxPowerEnable = %d\n", uNewTxPower, uCurrChannel, pRegDomRole->bTemporaryTxPowerEnable);
//    if (pRegDomRole->callbacks.setTxPower)
//    {
//        return pRegDomRole->callbacks.setTxPower(uTxPower, pRegDomRole->callbacks.hRoleContext);
//    }
//    else
//    {
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_updateCurrTxPower, callbacks.setTxPower not initialized!\n", uNewTxPower, uCurrChannel, pRegDomRole->bTemporaryTxPowerEnable);
//		return-1;
//    }
//}


int32_t regulatoryDomain_GetPowerCapability(powerCapability_t *pPowerCapability)
{
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//
//    getPowerTableMinMax (pRegulatoryDomain, pPowerCapability);
	return 0;
}


//void regulatoryDomain_SetPowerConstraint(void * hRegulatoryDomain, void * hRegDomRole, uint8_t uPowerConstraint)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//    regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t*)hRegDomRole;
//
//    /* Convert to RegDomain units */
//	uint8_t uNewPowerConstraint = DBM2DBMDIV10(uPowerConstraint);
//
//	TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION,
//		  "regulatoryDomain_SetPowerConstraint: Old= %d New = %d (Only if bigger...)\n",
//		  pRegDomRole->uPowerConstraint, uNewPowerConstraint);
//
//	/* Update powerConstraint */
//	if ( pRegDomRole->uPowerConstraint != uNewPowerConstraint )
//	{
//		pRegDomRole->uPowerConstraint = uNewPowerConstraint;
//		/* Set new Tx power to TWD - only if needed ! */
//		regulatoryDomain_UpdateCurrTxPower(hRegulatoryDomain, hRegDomRole);
//	}
//}


/***********************************************************************
 *                        regulatoryDomain_isChannelSupprted		   *
 ***********************************************************************
DESCRIPTION:	The function checks if the input channel is supported.

INPUT:      pRegulatoryDomain	-	RegulatoryDomain pointer.
			channel				-	Channel number.


OUTPUT:

RETURN:     OK if channel is supported,-1 otherwise.

************************************************************************/
Bool32 regulatoryDomain_IsChannelSupported(uint8_t uChannel, Bool32 *isDfsChannel)
{


	uint8_t	             channelIndex;
	channelCapability_t *pSupportedChannels;
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	if (pRegulatoryDomain==NULL)
	{
		return FALSE;
	}

    if ((uChannel<BG_24G_BAND_MIN_CHANNEL) || (uChannel>A_5G_BAND_MAX_CHANNEL))
	{
		return FALSE;
	}
	if (uChannel>=A_5G_BAND_MIN_CHANNEL)
	{
		channelIndex = (uChannel-A_5G_BAND_MIN_CHANNEL);
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
	}
	else
	{
		channelIndex = (uChannel-BG_24G_BAND_MIN_CHANNEL);
		if (channelIndex >= NUM_OF_CHANNELS_24)
		{
			GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_isChannelSupprted(): 2.4G invalid channel # %u", uChannel );
			return FALSE;
		}
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
	}

	if (pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS)
	{
		*isDfsChannel = TRUE;
		verifyDfsChannelValidity(pSupportedChannels, channelIndex);
	}
	else
	{
		*isDfsChannel = FALSE;
	}

	return pSupportedChannels[channelIndex].channelValidityActive;
}


/************************************************************************
 *                        regulatoryDomain_setChannelValidity			*
 ************************************************************************/
/*
*
*
* \b Description:
*
* This function sets a channel as invalid or valid in the internal Regulatory Domain
 * database.
*
* \b ARGS:
*
*  I   - pData - pointer to the regDoamin SM context  \n
*  I   - channelNum - the invalid/valid channel number
*  I   - channelValidity - TRUE if channel is valid, FALSE channel is invalid
*
* \b RETURNS:
*
*  None.
*
*
*************************************************************************/
void regulatoryDomain_SetChannelValidity(channelValidity_t *pChannelValidity)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	channelCapability_t	*pSupportedChannels;
	uint8_t              channelIndex;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	if (pRegulatoryDomain == NULL)
	{
		return;
	}

    if ((pChannelValidity->channelNum == 0) || (pChannelValidity->channelNum > A_5G_BAND_MAX_CHANNEL))
	{
		GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_SetChannelValidity, invalid channelNum=%d", pChannelValidity->channelNum);
		return;
	}

	/* Validity can be changed for DFS channels only */
	if ((pChannelValidity->channelNum >= A_5G_BAND_MIN_CHANNEL) && (pChannelValidity->channelNum < A_5G_BAND_MAX_CHANNEL))
	{
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
		channelIndex = (pChannelValidity->channelNum - A_5G_BAND_MIN_CHANNEL);
	}
	else
		return;

	if (!(pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS))
	{
		GTRACE(GRP_REG_DOMAIN, "regulatoryDomain_SetChannelValidity: channelNum = %d isn't supported as DFS channel in the Country", pChannelValidity->channelNum);
		return;
	}

    /* If the validity change is allowed - update FW*/
    if (pChannelValidity->channelValidity != pSupportedChannels[channelIndex].channelValidityActive)
	{
		/* Note for the future!!!!: Must not close a serving channel of AP/GO when DFS master is implemented*/
		GTRACE(GRP_REG_DOMAIN, "regulatoryDomain_SetChannelValidity: channelNum=%d, validity=%d", pChannelValidity->channelNum, pChannelValidity->channelValidity);
		pSupportedChannels[channelIndex].channelValidityActive = pChannelValidity->channelValidity;
		pSupportedChannels[channelIndex].timestamp = osi_GetTimeMS();     //os_timeStampMs(pRegulatoryDomain->hOs);
		if (setChannelAsFwBitmap(pChannelValidity->channelNum, FALSE, pChannelValidity->channelValidity))
			sendRegDomainCmdToFw();
	}

}


///***********************************************************************
//*                        regulatoryDomain_getChannelCapability		   *
//************************************************************************
//DESCRIPTION:	This function returns the channel capability information
//
//INPUT:      pRegulatoryDomain		-	RegulatoryDomain pointer.
//			channelCapabilityReq	-	Channels parameters
//
//
//OUTPUT:		channelCapabilityRet	-   Channel capability information
//
//RETURN:     OK if information was retrieved,-1 otherwise.
//
//************************************************************************/
//int32_t regulatoryDomain_GetChannelCapability(void * hRegulatoryDomain,
//                                                void * hRegDomRole,
//                                                channelCapabilityReq_t *pChannelCapabilityReq,
//												channelCapabilityRet_t *pChannelCapabilityRet)
//{
//	channelCapability_t		*pSupportedChannels;
//	uint8_t				channelIndex;
//    Bool32                 bServingChannel= FALSE;
//    RegulatoryDomain_t      *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//    regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t*)hRegDomRole;
//
//	if ((pRegulatoryDomain == NULL) || (pChannelCapabilityRet == NULL))
//	{
//		return-1;
//	}
//
//    pChannelCapabilityRet->channelValidity = FALSE;
//	pChannelCapabilityRet->maxTxPowerDbm = 0;
//	if ((pChannelCapabilityReq->channelNum==0 ) || (pChannelCapabilityReq->channelNum > A_5G_BAND_MAX_CHANNEL))
//	{
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_getChannelCapability, invalid channelNum=%d \n", pChannelCapabilityReq->channelNum);
//		return-1;
//	}
//
//	if (pChannelCapabilityReq->band==RADIO_BAND_2_4GHZ)
//	{
//		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
//		channelIndex = (pChannelCapabilityReq->channelNum - BG_24G_BAND_MIN_CHANNEL);
//		if (channelIndex >= NUM_OF_CHANNELS_24)
//		{
//			TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_getChannelCapability(): 2.4G invalid channel # %u\n", pChannelCapabilityReq->channelNum );
//			return-1;
//		}
//	}
//	else if (pChannelCapabilityReq->band==RADIO_BAND_5_0GHZ)
//	{
//		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
//		channelIndex = (pChannelCapabilityReq->channelNum - A_5G_BAND_MIN_CHANNEL);
//		if (channelIndex >= A_5G_BAND_NUM_CHANNELS)
//		{
//			TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_getChannelCapability(): 5G invalid channel # %u\n", pChannelCapabilityReq->channelNum);
//			return-1;
//		}
//
//        verifyDfsChannelValidity(pRegulatoryDomain, pSupportedChannels, channelIndex);
//	}
//	else
//	{
//		TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_getChannelCapability, invalid band=%d \n", pChannelCapabilityReq->band);
//		return-1;
//	}
//
//
//   	/*
//	 * Set channelValidity according to ScanTable and whether 11d is enabled
//	 */
//	if (pChannelCapabilityReq->scanOption == ACTIVE_SCANNING)
//	{
//        uint8_t currentChannel;
//        int32_t eStatus;
//
//        pChannelCapabilityRet->channelValidity = pSupportedChannels[channelIndex].channelValidityActive;
//
//        /*
//         * Set Maximum Tx power for the channel - only for active scanning
//         */
//
//        eStatus = pRegDomRole->callbacks.getCurrentChannel(pRegDomRole->callbacks.hRoleContext,
//                                                           &currentChannel, NULL);
//
//        if (eStatus != OK)
//            bServingChannel = FALSE;
//        else
//            bServingChannel = ( currentChannel == pChannelCapabilityReq->channelNum ?
//                                TRUE : FALSE );
//
//        pChannelCapabilityRet->maxTxPowerDbm = regulatoryDomain_getMaxPowerAllowed((void *)pRegulatoryDomain,
//                                                                                   hRegDomRole,
//                                                                                   pChannelCapabilityReq->channelNum,
//                                                                                   pChannelCapabilityReq->band,
//                                                                                   bServingChannel);
//
//		if (bServingChannel)
//			pChannelCapabilityRet->channelValidity = TRUE;
//
//
//    }
//	else	/* Passive scanning */
//	{
//        pChannelCapabilityRet->channelValidity = pSupportedChannels[channelIndex].channelValidityPassive;
//	}
//
//    if (pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS)
//		pChannelCapabilityRet->dfsChannel = TRUE;
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, " Channel num= %d, scan option=%d validity = %d, TX power = %d \n", pChannelCapabilityReq->channelNum, pChannelCapabilityReq->scanOption, pChannelCapabilityRet->channelValidity, pChannelCapabilityRet->maxTxPowerDbm);
//	return OK;
//
//}


/* being used for the neighbor report response frame */
//int32_t regulatoryDomain_GetRadioBandByRegClass(void * hRegulatoryDomain, uint8_t uRegClass, BandType_e *pBandType)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	BandType_e         bandType = BAND_TYPE_NONE;
//    RegDomainCalssesInfo_t    *pRegDomainInfo = &RegClassTbl[pRegulatoryDomain->countryZone];
//    uint8_t           i = 0;
//
//    for (i=0; i< REG_DOMAIN_MAX_REG_CLASS_NUM ; i++)
//    {
//        if ((uRegClass >= pRegDomainInfo->DomainReg[i].MinClass) && (uRegClass <= pRegDomainInfo->DomainReg[i].MaxClass))
//        {/* The channel set for this regulatory class and Zone was found */
//            bandType = pRegDomainInfo->DomainReg[i].band;
//            break;
//        }
//    }
//
//    *pBandType = bandType;
//
//    return OK;
//}


//int32_t regulatoryDomain_GetChannelsByRegClass(void * hRegulatoryDomain, uint8_t uRegClass,
//                                                        RegClassChannelList_t *pChannelList)
//{
//    RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	RegDomainCalssesInfo_t    *pRegDomainInfo = &RegClassTbl[pRegulatoryDomain->countryZone];
//    uint8_t           i = 0, j=0;
//
//    for (i=0; i< REG_DOMAIN_MAX_REG_CLASS_NUM ; i++)
//    {
//        if ((uRegClass >= pRegDomainInfo->DomainReg[i].MinClass) && (uRegClass <= pRegDomainInfo->DomainReg[i].MaxClass))
//        {/* The channel set for this regulatory class and Zone was found */
//            pChannelList->band = pRegDomainInfo->DomainReg[i].band;
//
//            for (j=0; j< REG_DOMAIN_MAX_CHAN_NUM ; j++)
//            {
//                pChannelList->Channel[j] = pRegDomainInfo->DomainReg[i].Channel[j];
//            }
//
//            break;
//        }
//    }
//
//    if (i == REG_DOMAIN_MAX_REG_CLASS_NUM)
//    {
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "regulatoryDomain_getChannelsByRegClass: Channels set for zone=%d, regClass=%d has not found!!!! \n", uRegClass, pRegulatoryDomain->countryZone);
//
//        return-1;
//    }
//    return OK;
//}


//uint8_t regulatoryDomain_GetRegClassByChannelAndBand(void * hRegulatoryDomain, BandType_e eBand, uint8_t uChannel)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	uint8_t           i=0, j=0;
//    RegDomainCalssesInfo_t    *pRegDomainInfo = &RegClassTbl[pRegulatoryDomain->countryZone];
//
//    for (i=0; i< REG_DOMAIN_MAX_REG_CLASS_NUM ; i++)
//    {
//        for (j=0; j< REG_DOMAIN_MAX_CHAN_NUM ; j++)
//        {
//            if ((uChannel == pRegDomainInfo->DomainReg[i].Channel[j]) && (eBand == pRegDomainInfo->DomainReg[i].band))
//            {
//                return pRegDomainInfo->DomainReg[i].MinClass;
//            }
//        }
//    }
//
//    return 0;
//}


/* Note!
 * For now the following function is deprecated.
 * currently when a beacon with Country IE is found, we override the
 * entire regulatory domain context block and rely solely on the
 * data we received in the beacon.
 * Moreover, we don't update the regulatory domain database accordingly,
 * we just set a flag there that says so.
 * For more info see: regulatoryDomain_handlePowerConstraint().
 */
/***********************************************************************
 *                       setSupportedChannelsAccording2CountryIe	   *
 ***********************************************************************
DESCRIPTION:	Called when beacon/Probe Response with Country IE
				is found.
				The function sets the local countryIE per band with the CountryIE
				 that was detected in the last passive scan.
				 It is assumed that only one Country IE per band is allowed.
				 If Country is changed when the TNET is loaded, it should
				 be re-loaded in order to re-config the new Country domain.

INPUT:      hRegulatoryDomain	-	RegulatoryDomain handle.
			pCountry	-	pointer to the detected country IE.

OUTPUT:

RETURN:     OK - New country code was set (or the same one was already configured)
           -1 - The new country code could not be set

************************************************************************/
int32_t regulatoryDomain_setSupportedChannelsAccording2CountryIe(dot11_COUNTRY_t *pCountry,
																   Bool32 band_2_4,
																   Bool32 updateFw)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	channelCapability_t	*pSupportedChannels;
	uint8_t	             channelIndex;
	uint8_t              tripletChannelIndex, tripletChannelCnt;
	uint8_t              channelStep, numberOfChannels, minChannelNumber, maxChannelNumber;
	uint32_t			 baseFreq;
	uint32_t 			 countryID = 0xFFFFFFFF;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    /* If country override disabled - return*/
	/* For now, pRegulatoryDomain->uDontOverride is always set */
	if (pRegulatoryDomain->uDontOverride ||
		(!pCountry->countryIE.CountryString[0] && !pCountry->countryIE.CountryString[1]))
	{
        if (pRegulatoryDomain->bFwUpdateRequired)
			sendRegDomainCmdToFw();
        return OK;
	}

	/* Find the country in internal tables*/
	if (getCountryIdInTable(pCountry->countryIE.CountryString, &countryID) != OK)
	{
        /*New country not found in internal DB - Keep pervious country*/
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Trying to set country %c%c, but country not found in internal DB. Country wasn't saved",  pCountry->countryIE.CountryString[0],  pCountry->countryIE.CountryString[1]);
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Add the country to tiwlanRegDomain.ini");
        return-1;
	}

    if( band_2_4 == TRUE )
	{
		/* If same country - Nothing to do */
		if (!memcmp( (void *)&pCountry->countryIE,
					 (void *)&pRegulatoryDomain->country24.countryIE,
					 sizeof(dot11_countryIE_t)))
		{
            if (pRegulatoryDomain->bFwUpdateRequired)
				sendRegDomainCmdToFw();
			return OK;
		}

        /* New country for 2.4G - prepare for setting */
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
        channelStep = BG_24G_BAND_CHANNEL_HOPS;
		maxChannelNumber = NUM_OF_CHANNELS_24;
		minChannelNumber = BG_24G_BAND_MIN_CHANNEL;
		numberOfChannels = NUM_OF_CHANNELS_24;
		baseFreq = BASE_FREQ_2_4;

		/* save the country IE */
		memcpy((void*)&pRegulatoryDomain->country24, (void *)pCountry, sizeof(dot11_COUNTRY_t));

		/* Zero all the 2.4G channels configuration */
		pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G);

        GTRACE(GRP_REG_DOMAIN, "Country 2.4 =%c%c%c",pRegulatoryDomain->country24.countryIE.CountryString[0], pRegulatoryDomain->country24.countryIE.CountryString[1], pRegulatoryDomain->country24.countryIE.CountryString[2]);
	}
	else    /* band 5.0 */
	{
		/* If same country - Nothing to do */
		if (!memcmp( (void *)&pCountry->countryIE,
					 (void *)&pRegulatoryDomain->country5.countryIE,
					 sizeof(dot11_countryIE_t)))
		{
			if (pRegulatoryDomain->bFwUpdateRequired)
				sendRegDomainCmdToFw();
			return OK;
		}

		/* New country for 5G - prepare for setting */
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
        channelStep = A_5G_BAND_CHANNEL_HOPS;
		maxChannelNumber = A_5G_BAND_MAX_CHANNEL;
		minChannelNumber = A_5G_BAND_MIN_CHANNEL;
		numberOfChannels = A_5G_BAND_NUM_CHANNELS;
		baseFreq = BASE_FREQ_5_0;

		/* save the country IE */
		memcpy((void*)&pRegulatoryDomain->country5, (void*)pCountry, sizeof(dot11_COUNTRY_t));

        /* Zero all the 5G channels configuration */
        pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G);
        pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2 &= ~(FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G);

        GTRACE(GRP_REG_DOMAIN, "Country 5 =%c%c%c",pRegulatoryDomain->country5.countryIE.CountryString[0], pRegulatoryDomain->country5.countryIE.CountryString[1], pRegulatoryDomain->country5.countryIE.CountryString[2]);
	}

    /* 802.11k changes (to be used during the RRM) */
    if ((pCountry->countryIE.CountryString[0] == 'U') && (pCountry->countryIE.CountryString[1] == 'S'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_USA;
    }
    else if ((pCountry->countryIE.CountryString[0] == 'J') && (pCountry->countryIE.CountryString[1] == 'P'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_JAPAN;
    }
    else /* Europe and the rest of the World */
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_RST;
    }

    GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe: Zone updated to %d (0=US, 1=JAPAN, 2=RestOfTheWorld)", pRegulatoryDomain->countryZone);


	/* New Country IE was saved - update the supported channels and update FW */

	/* Clear the validity of all channels */
	for (channelIndex=0; channelIndex<numberOfChannels; channelIndex++)
	{
		pSupportedChannels[channelIndex].channelValidityActive = FALSE;
		pSupportedChannels[channelIndex].channelValidityPassive = FALSE;
		pSupportedChannels[channelIndex].uFlags = 0;
		pSupportedChannels[channelIndex].uMaxTxPowerDomain = MIN_TX_POWER;
	}

	/* Set validity of the channels according to triplets in IE */
	tripletChannelCnt = (pCountry->hdr.eleLen - DOT11_COUNTRY_STRING_LEN) / 3;
    for (tripletChannelIndex = 0; tripletChannelIndex < tripletChannelCnt ; tripletChannelIndex++)
	{
		uint8_t	firstChannelNumInTriplet;
		uint32_t	minFreqInTriplet, maxFreqInTriplet;

		firstChannelNumInTriplet = pCountry->countryIE.tripletChannels[tripletChannelIndex].firstChannelNumber;
		minFreqInTriplet = firstChannelNumInTriplet*5 + baseFreq;
		maxFreqInTriplet = (firstChannelNumInTriplet+((pCountry->countryIE.tripletChannels[tripletChannelIndex].numberOfChannels-1)*channelStep))*5 + baseFreq;
        GTRACE(GRP_REG_DOMAIN, "firstChannelNumInTriplet=%d,channelStep=%d", firstChannelNumInTriplet, channelStep);

		for (channelIndex=0; channelIndex<pCountry->countryIE.tripletChannels[tripletChannelIndex].numberOfChannels; channelIndex++)
		{
			uint16_t	channelNumber;

			channelNumber = firstChannelNumInTriplet+(channelIndex*channelStep);
            GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe of channel=%d", channelNumber);

			if (channelNumber <= maxChannelNumber)
			{
				uint8_t 	channelIndex4Band;
				uint32_t	channelFreq;

				channelIndex4Band = (channelNumber-minChannelNumber);
				channelFreq = channelNumber*5 + baseFreq;
				if (channelIndex4Band < numberOfChannels)
				{
					pSupportedChannels[channelIndex4Band].channelValidityPassive = TRUE;

                    /* If this is a DFS channel it is not valid for active yet */
					if (!isDfsChannelInCountry(countryID, channelNumber))
					{
						pSupportedChannels[channelIndex4Band].channelValidityActive = TRUE;
						if (setChannelAsFwBitmap(channelNumber, band_2_4, TRUE) == FALSE)
						{
							GTRACE(GRP_GENERAL_ERROR, "ERROR: Channel to index translation failed, received channel : = %d, channelIndex4Band = %d, CountryString = %c%c ",
								  channelNumber, channelIndex4Band, pCountry->countryIE.CountryString[0], pCountry->countryIE.CountryString[1]);
						}
					}
					else
					{
						pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_DFS;
					}

					#if 0//we dont support HT40
					/*Set HT40 attributes for the channel*/
					if (channelNumber != 14)
					{
						if (channelFreq - 30 >= minFreqInTriplet && channelFreq - 10 <= maxFreqInTriplet)
							pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
						if (channelFreq + 10 >= minFreqInTriplet && channelFreq + 30 <= maxFreqInTriplet)
							pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
					}
                    #endif
					/* set the TX power in DBM/10 units */
					pSupportedChannels[channelIndex4Band].uMaxTxPowerDomain =
						DBM2DBMDIV10(pCountry->countryIE.tripletChannels[tripletChannelIndex].maxTxPowerLevel);

                    GTRACE(GRP_REG_DOMAIN, "channel = %d uMaxTxPowerDomain=%d", channelNumber, pSupportedChannels[channelIndex4Band].uMaxTxPowerDomain);
				}
				else
				{
					GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe index out of bounds=%d numberOfChannels = %d", channelIndex4Band, numberOfChannels);
				}
			}
		}
	}

    /* Update fw with new configuration*/
	if (updateFw)
		sendRegDomainCmdToFw();
	else
		pRegulatoryDomain->bFwUpdateRequired = TRUE;

	return OK;
}


/**********************************************************************
*              regulatoryDomain_getMaxPowerAllowed					  *
***********************************************************************
DESCRIPTION: Get the maximum tx power allowed for the given channel.
				The final value is constructed by:
				1) User max value
				2) Domain restriction - 11d country code IE
				3) 11h power constraint - only on serving channel
				4) CCX TPC - only on serving channel

              If we get a NULL hRegDomRole context, we use the default
              parameters.


RETURN:     Max power in Dbm/10 for the given channel

************************************************************************/
//uint8_t regulatoryDomain_getMaxPowerAllowed(void * hRegulatoryDomain,
//                                             void * hRegDomRole,
//                                             uint8_t uChannel,
//                                             RadioBand_e eBand,
//                                             Bool32 bServingChannel)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t*)hRegulatoryDomain;
//    regulatoryDomainRole_t *pRegDomRole = (regulatoryDomainRole_t*)hRegDomRole;
//
//	channelCapability_t	*pSupportedChannels;
//	uint8_t				 uChannelIndex, uTxPower;
//
//    if( eBand == RADIO_BAND_2_4GHZ)
//	{
//		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
//		uChannelIndex = uChannel - BG_24G_BAND_MIN_CHANNEL;
//	}
//	else
//	{
//		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
//		uChannelIndex = uChannel - A_5G_BAND_MIN_CHANNEL;
//	}
//
//	/* We'll start with the "Domain restriction - 11d country code IE" */
//	uTxPower = pSupportedChannels[uChannelIndex].uMaxTxPowerDomain;
//
//	if (pRegDomRole && bServingChannel)
//	{
//		if (pRegDomRole->uPowerConstraint < uTxPower)
//		{
//			/* When 802.11h is disabled, uPowerConstraint is 0 anyway */
//			uTxPower -= pRegDomRole->uPowerConstraint;
//		}
//
//        /* Take CCX limitation too */
//        uTxPower = TI_MIN(uTxPower, pRegDomRole->uExternTxPowerPreferred);
//
//	}
//
//	/* Now make sure we are not exceeding the user maximum */
//    if (pRegDomRole)
//		uTxPower = TI_MIN(uTxPower, pRegDomRole->uUserMaxTxPower);
//	else
//		uTxPower = TI_MIN(uTxPower, pRegulatoryDomain->defDesiredTxPower);
//
//	TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_INFORMATION, " uChannel = %d bServingChannel = %d uTxPower = %d \n", uChannel, bServingChannel, uTxPower);
//
//	return uTxPower;
//}


/* for debug */
//void regulatoryDomain_PrintValidTables(void * hRegulatoryDomain)
//{
//	RegulatoryDomain_t  *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//	uint16_t channelIndex;
//
//	for (channelIndex=0; channelIndex<NUM_OF_CHANNELS_24; channelIndex++)
//	{
//		if (pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive)
//			WLAN_OS_REPORT(("channel num =%d is valid for passive \n", channelIndex+1));
//		if (pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityActive)
//		{
//			WLAN_OS_REPORT(("channel =%d is valid for active TX power=%d\n",
//							channelIndex+1, pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uMaxTxPowerDomain));
//		}
//	}
//
//	for (channelIndex=0; channelIndex<A_5G_BAND_NUM_CHANNELS; channelIndex++)
//    {
//		uint8_t	channelNum;
//		channelNum = channelIndex+A_5G_BAND_MIN_CHANNEL;
//		if (pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityPassive)
//			WLAN_OS_REPORT(("channel =%d is valid for passive \n", channelNum));
//		if (pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityActive)
//		{
//			WLAN_OS_REPORT(("channel =%d is valid for active TX power=%d\n",
//							channelNum,pRegulatoryDomain->supportedChannels_band_5[channelIndex].uMaxTxPowerDomain));
//		}
//	}
//
//}


//void regulatoryDomain_GetActiveChannels(void * hRegulatoryDomain, tiwdrv_ap_chan_hw_info_t *pChanInfo)
//{
//	RegulatoryDomain_t  *pRegulatoryDomain = (RegulatoryDomain_t *)hRegulatoryDomain;
//    int16_t i,index=0;
//
//	pChanInfo->mode = TIW_DRV_AP_DOT11_DUAL_MODE;
//
//    /* Get 2.4G active channels */
//	for (i=0; i<NUM_OF_CHANNELS_24; i++)
//	{
//		if (pRegulatoryDomain->supportedChannels_band_2_4[i].channelValidityActive)
//		{
//			pChanInfo->chan24List[index].chan = i + 1;
//			pChanInfo->chan24List[index].max_tx_power = DBM_DIV_10_2_DBM(pRegulatoryDomain->supportedChannels_band_2_4[i].uMaxTxPowerDomain);
//			pChanInfo->chan24List[index].flags = pRegulatoryDomain->supportedChannels_band_2_4[i].uFlags;
//			index++;
//		}
//	}
//    pChanInfo->numOfGChan = index;
//    pChanInfo->numOfBChan = index;
//
//
//	/* Get 5G active channels */
//	index = 0;
//    for (i=0; i<A_5G_BAND_NUM_CHANNELS; i++)
//    {
//		if (pRegulatoryDomain->supportedChannels_band_5[i].channelValidityActive &&
//			!(pRegulatoryDomain->supportedChannels_band_5[i].uFlags & TIW_REG_DOMAIN_DFS))
//		{
//            pChanInfo->chan5List[index].chan = i + A_5G_BAND_MIN_CHANNEL;
//			pChanInfo->chan5List[index].max_tx_power = DBM_DIV_10_2_DBM(pRegulatoryDomain->supportedChannels_band_5[i].uMaxTxPowerDomain);
//			pChanInfo->chan5List[index].flags = pRegulatoryDomain->supportedChannels_band_5[i].uFlags;
//			index++;
//		}
//	}
//	pChanInfo->numOfAChan = index;
//}


int32_t regulatoryDomain_GetCapability(RadioBand_e band ,uint16_t channel,channelCapability_t *ChannelCapability)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint16_t channelIndex;
	channelCapability_t* pSupportedChannels;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_5GHZ)
	{
		channelIndex = (channel-A_5G_BAND_MIN_CHANNEL);
		if (channelIndex > A_5G_BAND_NUM_CHANNELS)
		{
			GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_GetCapability: channelIndex = %d", channelIndex);
			return-1;
		}
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
	}
	else
	{
		channelIndex = (channel - BG_24G_BAND_MIN_CHANNEL);
		if (channelIndex > NUM_OF_CHANNELS_24)
		{
			GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_GetCapability: channelIndex = %d", channelIndex);
			return-1;
		}
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
	}

	verifyDfsChannelValidity(pSupportedChannels, channelIndex);

	ChannelCapability->uFlags = pSupportedChannels[channelIndex].uFlags;
	ChannelCapability->channelValidityActive = pSupportedChannels[channelIndex].channelValidityActive;
	ChannelCapability->channelValidityPassive = pSupportedChannels[channelIndex].channelValidityPassive;
	ChannelCapability->timestamp = pSupportedChannels[channelIndex].timestamp;
	ChannelCapability->uMaxTxPowerDomain = pSupportedChannels[channelIndex].uMaxTxPowerDomain;
	//REG_DOMAIN_PRINT_REPORT("capability on 2.4/5G channel uFlags= %d,validityActive=%d,validityPassive=%d,timestamp=%d,MAxTx=%d\n",ChannelCapability->uFlags,ChannelCapability->channelValidityActive,ChannelCapability->channelValidityPassive ,ChannelCapability->timestamp,ChannelCapability->uMaxTxPowerDomain);
	return OK;
}


void regulatoryDomain_GetCahnnelOnBand(RadioBand_e band, supportedChannels_t *supportedChannels)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
//	channelCapability_t *pSupportedChannelsCap = NULL;
	uint32_t i;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_2_4GHZ)
	{
		supportedChannels->listOfChannels = (uint8_t*)pRegulatoryDomain->supportedChannels_band_2_4;
		supportedChannels->sizeOfList = NUM_OF_CHANNELS_24;
//		pSupportedChannelsCap = pRegulatoryDomain->supportedChannels_band_2_4;
	}
	else
	{
		supportedChannels->listOfChannels = (uint8_t*)pRegulatoryDomain->supportedChannels_band_5;
		supportedChannels->sizeOfList = A_5G_BAND_NUM_CHANNELS;
//		pSupportedChannelsCap = pRegulatoryDomain->supportedChannels_band_5;

        /* Varify activity of DFS channels*/
		for (i=0; i<A_5G_BAND_NUM_CHANNELS; i++)
		{
			verifyDfsChannelValidity(pRegulatoryDomain->supportedChannels_band_5, i);
		}
	}
}

/*****************************************************************************
 * Module:    	regulatoryDomain module, 
 * API:         _FindCountry, _GetCountryData
 *
 * Description: decompress the rom/patch compressed country data tables
 * Callers:     
 * Input:       
 * Return: 
 ****************************************************************************/
uint16_t regulatoryDomain_GetCountryRegion(uint8_t *pCountryString)
{
    int countryIndex =0;//set country index defualt to 0 otherwise it will send out of range index.
	int i;
   
    HOOK(HOOK_IN_REGULATORY_DOMAIN);
    
    /* Find the country in internal table */
    for (i=0; i < gNumCompressedCountries; i++)
    {
        if (!os_memcmp((unsigned char *)gConfigCountryCompressedTable[i].CountryStr, (unsigned char *)pCountryString, REG_DOMAIN_COUNTRY_STR_LEN))
        {
            countryIndex = gConfigCountryCompressedTable[i].Region;
            break;
        }
    }

    return countryIndex;
}

int32_t regulatoryDomain_SetCountry(uint8_t *pCountryStr)
{

    if (regulatoryDomain_GetCountryRegion(pCountryStr) < 0)
    {
        /* country not found in internal DB - Keep pervious country*/
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Trying to set country %c%c, but country not supported. Country wasn't saved",  pCountryStr[0],  pCountryStr[1]);
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Add the country to tiwlanRegDomain.ini");
        return-1;
	}
    memcpy(gCountryDomainStr, pCountryStr, DOT11_COUNTRY_STRING_LEN);
    return OK;

}



//int32_t regulatoryDomain_ConfigRegulatoryTables(void * hRegDomain, uint8_t *pBuf, uint32_t uLength)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//	RegDomainCountryInfo_t *pRegDomainTable;
//    uint16_t idxTLV = 0;
//	uint16_t paramKey = 0;
//	uint16_t fieldLength = 0;
//	uint32_t i, j;
//
//    /* Read the driver version string and make sure it matches current version */
//	while (pBuf[idxTLV] != '\0')
//	{
//		idxTLV++;
//	}
//
//    if (idxTLV == 0 || os_memoryCompare(pRegulatoryDomain->hOs, pBuf, SW_VERSION_STR, idxTLV) != 0)
//	{
//		WLAN_OS_REPORT(("\n %s: Error!! Driver Version string in TLV (%s)  \n does not match the driver kernel version: %s \n",
//						__FUNCTION__, pBuf, SW_VERSION_STR));
//		return-1;
//	}
//	idxTLV++; /* skip the string termination char '\0' */
//
//    /* Read the number of countries conifigured in the input buffer*/
//	pRegulatoryDomain->uNumOfCountriesInTable = readNumOfConfiguredCountries(pRegulatoryDomain, pBuf, uLength, idxTLV);
//	if (!pRegulatoryDomain->uNumOfCountriesInTable)
//		return OK;
//
//    /* Allocate required memory for RegDomain table*/
//    pRegulatoryDomain->pRegDomainTable = os_memoryAlloc(pRegulatoryDomain->hOs, sizeof(RegDomainCountryInfo_t)*pRegulatoryDomain->uNumOfCountriesInTable);
//    if (NULL == pRegulatoryDomain->pRegDomainTable)
//    {
//        TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_FATAL_ERROR, "regulatoryDomain_ConfigRegulatoryTables(): Allocation for pInitTable has failed!\n");
//        return-1;
//    }
//    os_memoryZero(pRegulatoryDomain->hOs, pRegulatoryDomain->pRegDomainTable, sizeof(RegDomainCountryInfo_t)*pRegulatoryDomain->uNumOfCountriesInTable);
//	pRegDomainTable = pRegulatoryDomain->pRegDomainTable;
//
//    /* Read configuration from the TLV format buffer into the table*/
//	while(idxTLV < uLength)
//	{
//		i=0;
//
//		/* read the key param index */
//		os_memoryCopy(pRegulatoryDomain->hOs, &paramKey, &pBuf[idxTLV], sizeof(uint16_t));
//		idxTLV += 2;
//		os_memoryCopy(pRegulatoryDomain->hOs, &fieldLength, &pBuf[idxTLV], sizeof(uint16_t));
//		idxTLV += 2;
//
//		if (paramKey == REG_DOMAIN_KEY_COUNTRY_CONFIG)
//		{
//            while(pRegDomainTable[i].CountryStr[0] && pRegDomainTable[i].CountryStr[1])
//			{
//				if (!os_memoryCompare(pRegulatoryDomain->hOs, pRegDomainTable[i].CountryStr, &pBuf[idxTLV], REG_DOMAIN_COUNTRY_STR_LEN))
//					break;
//
//				i++;
//			}
//
//            if (i < pRegulatoryDomain->uNumOfCountriesInTable)
//			{
//                /*Save country code*/
//				os_memoryCopy(pRegulatoryDomain->hOs, pRegDomainTable[i].CountryStr, &pBuf[idxTLV], REG_DOMAIN_COUNTRY_STR_LEN);
//				pRegDomainTable[i].CountryStr[REG_DOMAIN_COUNTRY_STR_LEN] = 32;
//
//				/*Find first empty row in the country and copy the value*/
//				for(j=0; j<REG_DOMAIN_MAX_ROWS_IN_COUNTRY; j++)
//				{
//					if(!pRegDomainTable[i].DomainReg[j].NumOfChannels)
//					{
//                        os_memoryCopy(pRegulatoryDomain->hOs,
//									  &pRegDomainTable[i].DomainReg[j],
//									  &pBuf[idxTLV + REG_DOMAIN_COUNTRY_STR_LEN],
//									  fieldLength - REG_DOMAIN_COUNTRY_STR_LEN);
//						break;
//					}
//				}
//			}
//		}
//
//		idxTLV += fieldLength;
//	}
//
//	return OK;
//}


//void regulatoryDomain_ClearExternalConfig(void * hRegDomain)
//{
//	RegulatoryDomain_t *pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//
//    pRegulatoryDomain->uDontOverride--;
//}

/********************************************************************************/
/*						Internal functions implementation.						*/
/********************************************************************************/
// SL_CC33XX_MODIFY_START
#ifdef COMPILE_DEAD_FUNC
static int32_t setSupportedChannelsAccording2confCountry(uint8_t *pCountryString)
{
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	RegDomainCountryInfo_t *pCurrCountry = NULL;
	channelCapability_t	*pSupportedChannels;
	uint32_t i, j;
	uint8_t minChannelNumber;
	uint32_t minClassFreq, maxClassFreq, baseFreq;

    if (pRegulatoryDomain->uDontOverride)
	{
		if (!memcmp(pRegulatoryDomain->country24.countryIE.CountryString, pCountryString, REG_DOMAIN_COUNTRY_STR_LEN))
		{
			pRegulatoryDomain->uDontOverride++;
			return OK;
		}
		return-1;
	}

    /* Find the country in internal table*/
	for (i=0; i < pRegulatoryDomain->uNumOfCountriesInTable; i++)
	{
		if (!memcmp(pRegulatoryDomain->pRegDomainTable[i].CountryStr, pCountryString, REG_DOMAIN_COUNTRY_STR_LEN))
		{
            pCurrCountry = &pRegulatoryDomain->pRegDomainTable[i];
            break;
		}
	}
	if (!pCurrCountry)
		return-1;

    /*Country found in internal tables - configure new country parameters*/
	memcpy(pRegulatoryDomain->country24.countryIE.CountryString, pCountryString, DOT11_COUNTRY_STRING_LEN);
	memcpy(pRegulatoryDomain->country5.countryIE.CountryString, pCountryString, DOT11_COUNTRY_STRING_LEN);
	pRegulatoryDomain->country24.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;
	pRegulatoryDomain->country5.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;

	/* Zero FW channel configuration bitmap */
	os_memset(&pRegulatoryDomain->fwRegDomainChannelBitField, 0, sizeof(RegDomainChannelConfigBitField_t));

    /* Clear the validity of all channels */
	os_memset(&pRegulatoryDomain->supportedChannels_band_2_4, 0, sizeof(pRegulatoryDomain->supportedChannels_band_2_4));
	os_memset(&pRegulatoryDomain->supportedChannels_band_5, 0, sizeof(pRegulatoryDomain->supportedChannels_band_5));

	/* 802.11k changes (to be used during the RRM) */
    if ((pCountryString[0] == 'U') && (pCountryString[1] == 'S'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_USA;
    }
    else if ((pCountryString[0] == 'J') && (pCountryString[1] == 'P'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_JAPAN;
    }
    else
	{
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_RST;
    }

    /* Configure the supported channels of the new country for both bands*/
	for (i=0; i<REG_DOMAIN_MAX_ROWS_IN_COUNTRY; i++)
	{
		if (pCurrCountry->DomainReg[i].NumOfChannels)
		{
			if (pCurrCountry->DomainReg[i].band == RADIO_BAND_2_4GHZ)
			{
				pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
				minChannelNumber = BG_24G_BAND_MIN_CHANNEL;
				baseFreq = BASE_FREQ_2_4;
			}
			else if (pCurrCountry->DomainReg[i].band == RADIO_BAND_5GHZ)
			{
				pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
				minChannelNumber = A_5G_BAND_MIN_CHANNEL;
				baseFreq = BASE_FREQ_5_0;
			}
			else
				continue;

			minClassFreq = pCurrCountry->DomainReg[i].Channel[0]*5 + baseFreq - 10;
			maxClassFreq = pCurrCountry->DomainReg[i].Channel[pCurrCountry->DomainReg[i].NumOfChannels - 1]*5 + baseFreq + 10;

            for (j=0; j<pCurrCountry->DomainReg[i].NumOfChannels; j++)
			{
				uint8_t channelIndex = pCurrCountry->DomainReg[i].Channel[j] - minChannelNumber;
				uint32_t channelFreq = pCurrCountry->DomainReg[i].Channel[j]*5 + baseFreq;

				pSupportedChannels[channelIndex].channelValidityPassive = TRUE;
                /*Set DFS attribute for the channel*/
				if (pCurrCountry->DomainReg[i].DfsChannel)
					pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_DFS;

				/*Set HT40 attributes for the channel*/
				if (pCurrCountry->DomainReg[i].Channel[j] != 14)
				{
                    if (channelFreq - 30 >= minClassFreq && channelFreq - 10 <= maxClassFreq)
						pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
					if (channelFreq + 10 >= minClassFreq && channelFreq + 30 <= maxClassFreq)
						pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
				}

				/* If this is a DFS channel it is not valid for active yet */
				if (!pCurrCountry->DomainReg[i].DfsChannel)
				{
					pSupportedChannels[channelIndex].channelValidityActive = TRUE;
					setChannelAsFwBitmap(pCurrCountry->DomainReg[i].Channel[j],
										 pCurrCountry->DomainReg[i].band == RADIO_BAND_2_4GHZ ? TRUE : FALSE,
										 TRUE);
				}

				/* set the TX power in DBM/10 units */
				pSupportedChannels[channelIndex].uMaxTxPowerDomain =
					DBM2DBMDIV10(pCurrCountry->DomainReg[i].TxPower);
			}
		}
		else
		{
			break;
		}
	}

	pRegulatoryDomain->uDontOverride++;

    /* Update FW with the new configuration*/
	sendRegDomainCmdToFw();

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    return OK;
}
#endif // COMPILE_DEAD_FUNC
// SL_CC33XX_MODIFY_END

///************************************************************************
// *      setSupportedChannelsAccording2ScanControlTable 					*
// ************************************************************************/
///**
//*
//*
//* \b Description:
//*
//* This function is called in config and sets the supported channels according to
//* the scan control table read from registry and reg domain read from the chip.
//*
//* \b ARGS:
//*
//*  I   - pRegulatoryDomain - pointer to the regDoamin SM context  \n
//*
//* \b RETURNS:
//*
//*  None.
//*
//*
//*************************************************************************/
static void setWorldWideDomainSupportedChannels()
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint8_t 	channelIndex = 0;

	uint8_t localDefaultABandChannels[A_5G_BAND_NUM_CHANNELS];

	HOOK(HOOK_IN_REGULATORY_DOMAIN);

	GTRACE_NVIC(GRP_REG_DOMAIN, "setWorldWideDomainSupportedChannels");
	REG_DOMAIN_PRINT_REPORT("setWorldWideDomainSupportedChannels\n" );
	//work on local copy so that original copy can reside in ROM
	memcpy(localDefaultABandChannels, DefaultABandChannels, A_5G_BAND_NUM_CHANNELS);

	/* If Japan channels are NOT supported - remove from default A band channel list*/
	if (!pRegulatoryDomain->japanChannelsEnabled)
	{
		while (JapanABandChannels[channelIndex])
		{
		    localDefaultABandChannels[JapanABandChannels[channelIndex] - A_5G_BAND_MIN_CHANNEL] = 0;
			channelIndex++;
		}
	}

	/* Step 1: Set WW 2.4Ghz Active channels*/
	for (channelIndex = 0; channelIndex < WORLD_WIDE_ACTIVE_2_4_CHANNEL; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityActive = TRUE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = TRUE;
        #if 0//we dont support HT40
		if (channelIndex < WORLD_WIDE_2_4_CHANNEL_HT40_MAX)
			pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
		if (channelIndex > WORLD_WIDE_2_4_CHANNEL_HT40_MIN)
			pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
        #endif
		GTRACE_NVIC(GRP_REG_DOMAIN, "setWorldWideDomainSupportedChannels = %d", channelIndex);
		/* Update FW channel bitmap */
		setChannelAsFwBitmap ((TWD_CALIBRATION_CHANNEL_2_4_MIN + channelIndex), TRUE, TRUE);

		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uMaxTxPowerDomain = DBM2DBMDIV10(20);
	}

	/* Step 2: Set WW 2.4Ghz Passive channels*/
	for (channelIndex = WORLD_WIDE_ACTIVE_2_4_CHANNEL; channelIndex < NUM_OF_CHANNELS_24; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityActive = FALSE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = TRUE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags = 0;
	}
	if (!pRegulatoryDomain->japanChannelsEnabled)
	{
		/* Japan channels are not supported - remove channel 14 from 2.4Ghz channel list*/
		channelIndex--;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = FALSE;
	}

	/* Step 3: Set WW 5Ghz channels*/
	for (channelIndex = 0; channelIndex < A_5G_BAND_NUM_CHANNELS; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityActive = FALSE;
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityPassive = (Bool32)localDefaultABandChannels[channelIndex];
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].uMaxTxPowerDomain = DBM2DBMDIV10(20);
		if (pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityPassive)
		{
			pRegulatoryDomain->supportedChannels_band_5[channelIndex].uFlags = TIW_REG_DOMAIN_DFS;
		}
		else
			pRegulatoryDomain->supportedChannels_band_5[channelIndex].uFlags = 0;
	}

}

/**********************************************************************
*              regulatoryDomain_getPowerTableMinMax					  *
***********************************************************************
DESCRIPTION: Find the Tx-power-level table min & max values.
			 The table is made of 4 power levels and 5 bands/sub-bands.

RETURN:     void
************************************************************************/
//static void getPowerTableMinMax (RegulatoryDomain_t *pRegulatoryDomain,
//								 powerCapability_t  *pPowerCapability)
//{
//    TFwInfo  *pFwInfo = TWD_GetFWInfo (pRegulatoryDomain->hTWD);
//	uint8_t	i;
//
//    /* Init the min (max) to the opposite edge so the table values are below (above) this edge */
//	pPowerCapability->minTxPower = MAX_TX_POWER;
//	pPowerCapability->maxTxPower = MIN_TX_POWER;
//
//	/* Find Min and Max values of the table */
//	for (i = 0; i < NUMBER_OF_SUB_BANDS_E; i++)
//	{
//		pPowerCapability->minTxPower = TI_MIN (pPowerCapability->minTxPower,
//											   pFwInfo->txPowerTable[i][NUM_OF_POWER_LEVEL-1]);
//		pPowerCapability->maxTxPower = TI_MAX (pPowerCapability->maxTxPower,
//											   pFwInfo->txPowerTable[i][0]);
//	}
//}


//static void RegDomainConfigSentToFw(void * handle, uint16_t uMboxStatus, Bool32 *pSuspendRequired)
//{
//	/*Configuration was sent to FW - suspend the cmd queue operation
//	untill event complete received back from the FW*/
//
//    if (pSuspendRequired)
//		*pSuspendRequired = TRUE;
//}


//static void RegDomainTmrExpiry(void * hRegDomain, Bool32 bTwdInitOccured)
//{
//    RegulatoryDomain_t	*pRegulatoryDomain = (RegulatoryDomain_t *)hRegDomain;
//
//    TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR, "RegDomainTmrExpiry\n");
//
//    if (!bTwdInitOccured)
//    {
//        healthMonitor_sendFailureEvent(pRegulatoryDomain->hHealthMonitor, REG_DOMAIN_TIMEOUT);
//    }
//}


static void sendRegDomainCmdToFw()
{
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

//    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
//	pRegulatoryDomain->bFwUpdateRequired = FALSE;
//
//    /* Update applications on a channel list change*/
//    evHandler_HandleEvent(pRegulatoryDomain->hEvHandler, TIWDRV_NETIF_NUM, TIW_DRV_EV_CHANNEL_LIST_CHANGED, NULL, 0);
//
//    /* Update FW with the new channels configuration*/
//	if (TWD_SendCmd(pRegulatoryDomain->hTWD,
//					CMD_REG_DOMAIN_CHANNEL_CONFIG,
//					(void *)&pRegulatoryDomain->fwRegDomainChannelBitField,
//					sizeof(RegDomainChannelConfigBitField_t),
//					RegDomainConfigSentToFw,
//					(void *)pRegulatoryDomain) != OK)
//    {
//		TRACE(pRegulatoryDomain->hReport, REPORT_SEVERITY_ERROR , "Failed to configure REG domain channels to the FW\n");
//		return ;
//    }
//
//	/* Start complete timer */
//    tmr_StartTimer(pRegulatoryDomain->hRegDomainTimer, RegDomainTmrExpiry, pRegulatoryDomain, REG_DOMAIN_TIMEOUT_MSEC, FALSE);
}


static void verifyDfsChannelValidity(channelCapability_t *pSupportedChannels, uint8_t channelIndex)
{
//    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if ((pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS) &&
		((osi_GetTimeMS() - pSupportedChannels[channelIndex].timestamp) >= CHANNEL_VALIDITY_TS_THRESHOLD ))
	{
		/* If 802.11h is enabled, a DFS channel is valid only for 10 sec from the last Beacon/ProbeResponse */
        pSupportedChannels[channelIndex].channelValidityActive = FALSE;
        GTRACE(GRP_REG_DOMAIN,
			  "DFS channel (# %d) - last beacon/probe req was received more then %d msec !!",
			  channelIndex+A_5G_BAND_MIN_CHANNEL,
			  CHANNEL_VALIDITY_TS_THRESHOLD);
	}
}


//static uint32_t readNumOfConfiguredCountries(RegulatoryDomain_t *pRegulatoryDomain, uint8_t *pBuf, uint32_t uBuffLen, uint16_t idxTLV)
//{
//	uint16_t 	paramKey = 0;
//	uint16_t 	fieldLength = 0;
//	uint32_t	numOfCountries=0;
//
//	while(idxTLV < uBuffLen)
//	{
//		/* read the key param index */
//		os_memoryCopy(pRegulatoryDomain->hOs, &paramKey, &pBuf[idxTLV], sizeof(uint16_t));
//		idxTLV += 2;
//		os_memoryCopy(pRegulatoryDomain->hOs, &fieldLength, &pBuf[idxTLV], sizeof(uint16_t));
//		idxTLV += 2;
//
//		if (paramKey == REG_DOMAIN_KEY_NUM_OF_COUNTRIES)
//		{
//			os_memoryCopy(pRegulatoryDomain->hOs, &numOfCountries, &pBuf[idxTLV] , fieldLength); /* copy the field data */
//			break;
//		}
//		idxTLV += fieldLength;
//	}
//
//	return numOfCountries;
//}


static int32_t getCountryIdInTable(uint8_t *pCountryStr, uint32_t *pCountryID)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint32_t cntrId;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    for (cntrId =0; cntrId < pRegulatoryDomain->uNumOfCountriesInTable; cntrId++)
	{
        if (!memcmp(pRegulatoryDomain->pRegDomainTable[cntrId].CountryStr, pCountryStr, REG_DOMAIN_COUNTRY_STR_LEN))
		{
			*pCountryID = cntrId;
			return OK;
		}
	}
	return-1;
}


static Bool32 isDfsChannelInCountry(uint32_t cntrId, uint32_t uChannel)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	RegDomainCountryInfo_t *pRegDomainTable;
    uint32_t group, channel;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (cntrId >= pRegulatoryDomain->uNumOfCountriesInTable)
		return FALSE;

	pRegDomainTable = &pRegulatoryDomain->pRegDomainTable[cntrId];

    for (group=0; group < REG_DOMAIN_MAX_ROWS_IN_COUNTRY; group++)
	{
		for (channel=0; channel<REG_DOMAIN_MAX_CHAN_NUM; channel++)
		{
			if (pRegDomainTable->DomainReg[group].Channel[channel] == uChannel)
				return pRegDomainTable->DomainReg[group].DfsChannel;
		}
	}
	return FALSE;
}


/***********************************************************************
 *                       setChannelAsFwBitmap
 ***********************************************************************
DESCRIPTION:    Writes the appropriate bit to the FW bitmap

INPUT:      hRegulatoryDomain   -   RegulatoryDomain handle.
            channelNumber       -  desired channel
            band_2_4            - boolean - True if band is 2.4G

OUTPUT: pRegulatoryDomain->fwRegDomainChannelBitField - channel bitfield

RETURN: FALSE - No change was made to bitmap

************************************************************************/
static Bool32 setChannelAsFwBitmap(uint16_t channelNumber, Bool32 band_2_4, Bool32 shouldSet)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
    int8_t  channelFWIdx = getChannelIndexTranslation(channelNumber,band_2_4);
	uint32_t *pBitMap;
	Bool32 isBitSet;

	HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (channelFWIdx == -1)
    {
		/* We have received a bad channel !*/
        return FALSE;
    }

	/* meaning we are in the LOW bitmap */
    if (channelFWIdx <= 31)
    {
		pBitMap = &(pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1);
	}
	else
	{
		channelFWIdx = channelFWIdx -32;
		pBitMap = &(pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2);
	}

	isBitSet = IS_BIT_SET(*pBitMap, channelFWIdx);

    /* Change to bitmap is required*/
	if (shouldSet != isBitSet)
	{
		if (shouldSet)
		    SET_BIT_IN_BITMAP(*pBitMap, channelFWIdx)
		else
		    CLEAR_BIT_IN_BITMAP(*pBitMap, channelFWIdx)

		return TRUE;
	}

    return FALSE;
}


/* Table that PHY uses for bitmap translation (all channels are divided into 9 Sub Bands)
        Bit#  chBitMap1                   chBitMap2
              channel, band , sub band
        0     {1,  API_BAND_2_4G,  0},    {64,  API_BAND_5G,    4},
        1     {2,  API_BAND_2_4G,  0},    {100, API_BAND_5G,   5},
        2     {3,  API_BAND_2_4G,  0},    {104, API_BAND_5G,   5},
        3     {4,  API_BAND_2_4G,  0},    {108, API_BAND_5G,   5},
        4     {5,  API_BAND_2_4G,  0},    {112, API_BAND_5G,   5},
        5     {6,  API_BAND_2_4G,  0},    {116, API_BAND_5G,   5},
        6     {7,  API_BAND_2_4G,  0},    {120, API_BAND_5G,   6},
        7     {8,  API_BAND_2_4G,  0},    {124, API_BAND_5G,   6},
        8     {9,  API_BAND_2_4G,  0},    {128, API_BAND_5G,   6},
        9     {10, API_BAND_2_4G,  0},    {132, API_BAND_5G,   6},
        10    {11, API_BAND_2_4G,  0},    {136, API_BAND_5G,   6},
        11    {12, API_BAND_2_4G,  0},    {140, API_BAND_5G,   6},
        12    {13, API_BAND_2_4G,  0},    {149, API_BAND_5G,   7},
        13    {14, API_BAND_2_4G,  0},    {153, API_BAND_5G,   7},
        14    {16, API_BAND_4_9G,  1},    {157, API_BAND_5G,   7},
        15    {12, API_BAND_4_9G,  1},    {161, API_BAND_5G,   7},
        16    {8,  API_BAND_4_9G,  1},    {165, API_BAND_5G,   7},
        17    {4,  API_BAND_4_9G,  1},    {171, API_BAND_5G,   8},
        18    {8,  API_BAND_5G,    2},    {172, API_BAND_5G,   8},
        19    {12, API_BAND_5G,    2},    {173, API_BAND_5G,   8},
        20    {16, API_BAND_5G,    2},    {174, API_BAND_5G,   8},
        21    {34, API_BAND_5G,    3},    {175, API_BAND_5G,   8},
        22    {36, API_BAND_5G,    3},    {176, API_BAND_5G,   8},
        23    {38, API_BAND_5G,    3},    {177, API_BAND_5G,   8},
        24    {40, API_BAND_5G,    3},    {178, API_BAND_5G,   8},
        25    {42, API_BAND_5G,    3},    {179, API_BAND_5G,   8},
        26    {44, API_BAND_5G,    3},    {180, API_BAND_5G,   8},
        27    {46, API_BAND_5G,    3},    {181, API_BAND_5G,   8},
        28    {48, API_BAND_5G,    3},    {182, API_BAND_5G,   8},
        29    {52, API_BAND_5G,    4},    {183, API_BAND_5G,   8},
        30    {56, API_BAND_5G,    4},    {184, API_BAND_5G,   8}
        31    {60, API_BAND_5G,    4},
*/
/***********************************************************************
 *                       getChannelIndexTranslation
 ***********************************************************************
DESCRIPTION:    Returns the bit index values according to the FW-values.
                  See full table above.
INPUT:
            channelNumber       -  desired channel
            band_2_4            - boolean - True if band is 2.4G

RETURN: int8_t - bit index value (0-61) as we treat the struct as a full 64 bitmap

************************************************************************/
static int8_t getChannelIndexTranslation(uint16_t chNumber, Bool32 band_2_4)
{
    int8_t idx = -1;
    uint8_t FIRST_5G_CHANNEL_IDX= 18;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    /* Bits (14-17) are relevant to 4.9 G and ignored here. as we don't have 4.9 band indication */
    if (band_2_4)
    {
        /* All the 2_4 channels are located in the First bitmap (Bits 0..13) */
        if (chNumber >= BG_24G_BAND_MIN_CHANNEL && chNumber <= NUM_OF_CHANNELS_24)
        {
            idx = chNumber - 1;
        }
        else
        {
            idx = -1;
        }
    }
    else
    {
        /* 5G channels are located in the first and second bitmap,
         * starting from position 18 for channel 8, up to 30 for channel 184
         * bits (..18-31) ==> channels (8-60)
         * Bits    (18,19,20) ==>
         * Channels(8,12,16)  (hops are 4)
         */
        if (chNumber >= 8 && chNumber <= 16)
        {
            idx = ((chNumber-8)/4 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 3
         * Bits    (21,22,23,24,25,26,27,28) ==>
         * Channels(34,36,38,40,42,44,46,48) (hops are 2)
         */
        else if (chNumber >= 34 && chNumber <= 48)
        {
            idx = ((chNumber-34)/2 + 3 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 11
         * Bits    (29,30,31,32) ==>
         * Channels(52,56,60,64) (hops are 4)
         */
        else if (chNumber >= 52 && chNumber <= 64)
        {
            idx = ((chNumber-52)/4 + 11 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 15
         * Bits    (33 ,34 ,35 ,36 ,37 ,38 ,39 ,40 ,41 ,42, 43) ==>
         * Channels(100,104,108,112,116,120,124,128,132,136,140) (hops are 4)
         */
        else if (chNumber >= 100 && chNumber <= 144)
        {
            idx = ((chNumber-100)/4 + 15 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 26
         * Bits    (44 ,45 ,46 ,47 ,48 ) ==>
         * Channels(149,153,157,161,165) (hops are 4)
         */
        else if (chNumber >= 149 && chNumber <= 165)
        {
            idx = ((chNumber-149)/4 + 26 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 31
         * Bits    (49 ,50 ,51 ,52 ,53, 54, 55, 56, 57, 58, 59, 60, 61, 62 ) ==>
         * Channels(171,172,173,174,175,176,177,178,179,180,181,182,183,184) (hops are 1)
         */
        else if (chNumber >= 171 && chNumber <= 184)
        {
            idx = ((chNumber-171) + 31 + FIRST_5G_CHANNEL_IDX);
        }
        else
        {
            idx = -1;
        }
    }

    return idx;
}


static int16_t getIndexChannelTranslation( uint8_t chIndex, uint8_t  band)
{

    uint16_t channel = -1;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_2_4GHZ)
    {
        if (chIndex >= 0 && chIndex < NUM_OF_CHANNELS_24)
        {
            /* rom_dot11g_channels holds the channel numbers for 2.4Ghz */
            channel = rom_dot11g_channels[chIndex];
        }
        else
        {
            channel = 0;
        }
    }
    else
    {
        if (chIndex >= 0 && chIndex <= 24)
        {
            /* rom_dot11a_channels holds the channel numbers for 5Ghz */
            channel = rom_dot11a_channels[chIndex];
        }
        else
        {
            channel = 0;
        }
    }

    return channel;
}

static int8_t setSupportedChannelsAccording2Domain(void)
{
   
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	channelCapability_t *pSupportedChannels;
	uint8_t              channelIndex = 0;
	uint8_t              groupPatternIndex;
    uint8_t              chanPatternIndex;
	uint32_t             channelBitmask;
    uint32_t             minClassFreq, maxClassFreq, baseFreq;
    uint32_t             channel;
    uint32_t             channelbit;
    uint32_t             channelFreq;
    uint32_t             i;
    
    ConfigChanPattern_t *pChanPattern;

    groupPatternIndex = regulatoryDomain_GetCountryRegion(gCountryDomainStr);
    pRegulatoryDomain->countryDomain = groupPatternIndex;
    pRegulatoryDomain->countryZone   = (RegulatoryZone_e)groupPatternIndex;

    if (pRegulatoryDomain->countryZone == REGULATORY_ZONE_JAPAN)
    {
        pRegulatoryDomain->japanChannelsEnabled = TRUE;
    }

    /*Country found in internal tables - configure new country parameters*/
	memcpy(pRegulatoryDomain->country24.countryIE.CountryString, gCountryDomainStr, DOT11_COUNTRY_STRING_LEN);
	memcpy(pRegulatoryDomain->country5.countryIE.CountryString, gCountryDomainStr, DOT11_COUNTRY_STRING_LEN);
	pRegulatoryDomain->country24.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;
	pRegulatoryDomain->country5.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;

	/* Zero FW channel configuration bitmap */
	os_memset(&pRegulatoryDomain->fwRegDomainChannelBitField, 0, sizeof(RegDomainChannelConfigBitField_t));

    /* Clear the validity of all channels */
	os_memset(&pRegulatoryDomain->supportedChannels_band_2_4, 0, sizeof(pRegulatoryDomain->supportedChannels_band_2_4));
	os_memset(&pRegulatoryDomain->supportedChannels_band_5, 0, sizeof(pRegulatoryDomain->supportedChannels_band_5));

	/* Zero all the 2.4G channels configuration */
	pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G);

    /* Zero all the 5G channels configuration */
    pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G);
    pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2 &= ~(FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G);

    /* Configure the supported channels of the new country for both bands */
    /* Collect all channels from all sub-bands */
    /* on same band - do OR between all sub-band masks */

    /* Configure the supported channels of the new country for both bands*/
    for (i=0; i<gConfigGroupChanPatternsTable[groupPatternIndex].chanAmount; i++)
    {

        /* Extract channel pattern index by group index and sub-band index */
        /* "US" example:     --    4,    13 --    {  0,  8,  4,  5,  9 },    US, group=4, chanPatternIndex = 0 and 8 and 4 and 5 and 9 */
        chanPatternIndex = gConfigGroupChanPatternsTable[groupPatternIndex].chanPatternsList[i];

        /* Extract channel pattern by channel pattern index */
        pChanPattern = &gConfigChanPatternsTable[chanPatternIndex];
        
        if (pChanPattern->band == RADIO_BAND_2_4GHZ)
        {
            pSupportedChannels = &pRegulatoryDomain->supportedChannels_band_2_4[0];
			baseFreq = BASE_FREQ_2_4;
        }
        else if (pChanPattern->band == RADIO_BAND_5GHZ)
        {
            pSupportedChannels = &pRegulatoryDomain->supportedChannels_band_5[0];
			baseFreq = BASE_FREQ_5_0;
        }
        else
            continue;

        channelbit = 0;
        channelBitmask = pChanPattern->chanBitmap;
     
		minClassFreq = pChanPattern->minChannel*5 + baseFreq - 10;
		maxClassFreq = pChanPattern->maxChannel*5 + baseFreq + 10;

        while (channelBitmask > 0)
        {
            channelIndex = 0;//reset channel index so before entering the first bitfield  - i also removed the else later only one is necessary to pervent overwrite of pSupportedChannels[channelIndex] in case bitmap is not active according to regualtory domain bitfields.
            if (channelBitmask & 1)
            {
                channel = getIndexChannelTranslation(channelbit, pChanPattern->band);
                channelFreq = channel*5 + baseFreq;

                if (pChanPattern->band == RADIO_BAND_5GHZ)
                {
                    channelIndex = channel - A_5G_BAND_MIN_CHANNEL;
                }
                else
                {
                    channelIndex = channel - BG_24G_BAND_MIN_CHANNEL;
                }

                pSupportedChannels[channelIndex].uFlags = 0;
                pSupportedChannels[channelIndex].channelValidityPassive = TRUE;

                /*Set DFS attribute for the channel*/
                if (pChanPattern->DfsChannel)
                {
                    pSupportedChannels[channelIndex].channelValidityActive = FALSE;
                    pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_DFS;
                }

                #if 0//we dont support HT40
				/*Set HT40 attributes for the channel*/
				if ( (channelIndex + 1) != 14) // Channel for 2.4GHz is channel index plus 1
				{
                    if (channelFreq - 30 >= minClassFreq && channelFreq - 10 <= maxClassFreq)
						pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
					if (channelFreq + 10 >= minClassFreq && channelFreq + 30 <= maxClassFreq)
						pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
				}
                #endif

                /* If this is a DFS channel it is not valid for active yet */
                if (!pChanPattern->DfsChannel)
                {
                    pSupportedChannels[channelIndex].channelValidityActive = TRUE;
					setChannelAsFwBitmap(channel, pChanPattern->band == RADIO_BAND_2_4GHZ ? TRUE : FALSE,
					 TRUE);
                }
                /* set the TX power in DBM/10 units */
                pSupportedChannels[channelIndex].uMaxTxPowerDomain = DBM2DBMDIV10(pChanPattern->txPowerPerRegion[groupPatternIndex]);

            }
            /*else	// this else cause bug before entering the valid channelBitmask bitfield. Luckily, we zero
					// this array for both bands earlier in this function, so this else-case isn't necessary and buggy.
            {
                pSupportedChannels[channelIndex].channelValidityPassive = FALSE;
                pSupportedChannels[channelIndex].channelValidityActive = FALSE;
                pSupportedChannels[channelIndex].uFlags = 0;
                pSupportedChannels[channelIndex].uMaxTxPowerDomain = DBM2DBMDIV10(MIN_TX_POWER);
            }*/
            channelBitmask>>=1;
            channelbit++;
        }
    }

    /* Update FW with the new configuration*/
    sendRegDomainCmdToFw();
    
    return OK;
}

/**********************************************************************
*              regulatoryDomain_getChMaxPower                   	  *
***********************************************************************
DESCRIPTION: Find the Max Tx power of selected channel.
             The value returned in dbm according to the channel and
			 country domain.

RETURN:      TRUE if valid channel TX power found, FALSE otherwise.
************************************************************************/
Bool_e regulatoryDomain_getChMaxPower(uint16_t channel, uint8_t *max_tx_power)
{
    channelCapability_t channelCapability;
    RadioBand_e temp_band;
    int32_t status;

    if (channel > 14)
    {
        temp_band = RADIO_BAND_5GHZ;
    }
    else
    {
        temp_band = RADIO_BAND_2_4GHZ;
    }

    status = regulatoryDomain_GetCapability(temp_band,
                                            channel,
                                            &channelCapability);

    if (status == OK)
    {
        *max_tx_power = DBM_DIV_10_2_DBM(channelCapability.uMaxTxPowerDomain);
        GTRACE(GRP_REG_DOMAIN, "max_tx_power for channel %d = %d dbm",
								channel,
								*max_tx_power);
        return TRUE;
    }
    else
    {
        GTRACE(GRP_GENERAL_ERROR, "max_tx_power for channel ERROR!!!");
        return FALSE;
    }
}


/**********************************************************************
*              regulatoryDomain_getCountryString                   	  *
***********************************************************************
DESCRIPTION: return the country code

RETURN:     void
************************************************************************/

int32_t regulatoryDomain_getCountryString(uint8_t *pCountryStr)
{
        if ((pCountryStr != NULL) && 
			(gCountryDomainStr[0] >= 'A') && (gCountryDomainStr[0] <= 'Z') &&
			(gCountryDomainStr[1] >= 'A')&&(gCountryDomainStr[1] <= 'Z') && 
			((gCountryDomainStr[2] == '\0') || (gCountryDomainStr[2] == 'I')))
        {
            memcpy(pCountryStr, gCountryDomainStr, 3);
            return OK;
        }
		else if ((pCountryStr != NULL) && 
				 (gCountryDomainStr[0] == '0') && (gCountryDomainStr[1] == '0') &&
				 ((gCountryDomainStr[2] == '\0') || (gCountryDomainStr[2] == 'I')))
		{
			pCountryStr[0] = '0';
			pCountryStr[1] = '0';
			pCountryStr[2] = gCountryDomainStr[2];
		}
        else
        {
            return -1;
        }
        return 0;
}

/***********************************************************************
 *            		getCountryElementTripletsCount					   *
 ***********************************************************************
DESCRIPTION: Returns the number of sub-band triplets in an IEEE80211d
			 country IE.

INPUT:		 dot11_COUNTRY_t *pIE - pointer to the country IE.

RETURN: 	 Number of triplets in IEEE80211d country IE.

************************************************************************/
uint8_t getCountryElementTripletsCount(dot11_COUNTRY_t *pIE)
{
	uint8_t infoElementLen = pIE->hdr.eleLen;
	uint8_t iePadLen = infoElementLen % 3;

	return (infoElementLen - iePadLen - DOT11_COUNTRY_STRING_LEN) / 3;
}

/***********************************************************************
 *            		getCountryElementMaxTxPower						   *
 ***********************************************************************
DESCRIPTION: Extract specific channel max TX power from 
			 IEEE80211d IE triplets.

INPUT:		 pCountryIE 	- IEEE80211d IE.
			 tripletsCount	- number of triplets.
			 channel 		- operating channel.
			 band 			- operating band.
			 channelPower	- output parameter. IEEE80211d IE power level.

RETURN: 	 TRUE if channel can be found in IEEE80211d IE, 
			 FALSE otherwise.

************************************************************************/
Bool_e getCountryElementMaxTxPower(dot11_COUNTRY_t *pIE,
								   uint8_t tripletsCount,
								   uint8_t channel,
								   uint8_t band,
								   int8_t *sta11dMaxTxPower)
{
	uint8_t channelStep, lastChannelNumber;
	dot11_TripletChannel_t *pCurrentTriplet;

	for (int i = 0;  i < tripletsCount;  i++)
	{
		pCurrentTriplet = &(pIE->countryIE.tripletChannels[i]);

		channelStep = (band == RADIO_BAND_2_4GHZ) ? BG_24G_BAND_CHANNEL_HOPS : \
												    A_5G_BAND_CHANNEL_HOPS;

		lastChannelNumber = pCurrentTriplet->firstChannelNumber + \
							((pCurrentTriplet->numberOfChannels - 1)* channelStep);

		if (channel >= pCurrentTriplet->firstChannelNumber &&
			channel <= lastChannelNumber)
		{
			*sta11dMaxTxPower = pCurrentTriplet->maxTxPowerLevel;
			return TRUE;
		}
	}

	return FALSE;
}

/***********************************************************************
 *            	 regulatoryDomain_getPowerFromCountryIE				   *
 ***********************************************************************
DESCRIPTION: This function receives a country IE as input, parses it and
			 finds the channel`s regulatory limit according to that
			 country IE.

INPUT:		 pCountryIE 	- IEEE80211d IE.
			 channel 		- operating channel.
			 band 			- operating band.
			 channelPower	- output parameter. IEEE80211d IE power level.

RETURN: 	 TRUE if successfully read country IE, FALSE otherwise.

************************************************************************/
Bool_e regulatoryDomain_getPowerFromCountryIE(dot11_COUNTRY_t *pCountryIE,
											  uint8_t channel,
											  uint8_t apBand,
											  int8_t *channelPower)
{
	uint8_t tripletsCount;
	Bool_e hasChannelPower = FALSE;

    tripletsCount = getCountryElementTripletsCount(pCountryIE);
	if (tripletsCount == 0)
	{
		return FALSE;
	}

    hasChannelPower = getCountryElementMaxTxPower(pCountryIE,
                                                  tripletsCount,
                                                  channel,
												  apBand,
												  channelPower);
	if (!hasChannelPower)
	{
		GTRACE(GRP_REG_DOMAIN, "ERROR: Operated channel %d can't be found "
							   "in country IE", channel);
	}

	return hasChannelPower;
}

/***********************************************************************
 *            				   findCiscoDtpc						   *
 ***********************************************************************
DESCRIPTION: Take a Cisco DTPC IE (Cisco vendor specific IE actualy),
			 validate it's a DTPC IE and not any other Cisco vendor
			 specific IE, return the value of DTPC.

INPUT:		 ciscoDtpcIE	 - Cisco DTPC IE.
			 powerLevelCisco - power level dictated by Cisco DTPC.

RETURN: 	 TRUE if IE is DTPC and is valid, else otherwise.

************************************************************************/
Bool_e findCiscoDtpc(dot11_CELL_TP_t *ciscoDtpcIE, int8_t *powerLevelCisco)
{

	if (ciscoDtpcIE->hdr.eleLen != 6)
	{
		return FALSE;
	}

	if (ciscoDtpcIE->oui[0] != 0x00 || ciscoDtpcIE->oui[1] != 0x40 ||
		ciscoDtpcIE->oui[2] != 0x96 || ciscoDtpcIE->oui[3] != 0x00)
	{
		return FALSE;
	}

	*powerLevelCisco = ciscoDtpcIE->power;
	
	return TRUE;
}

/***********************************************************************
 *            	   regulatoryDomain_setRoleMaxTxPower				   *
 ***********************************************************************
DESCRIPTION: Set a role`s max TX power. Send a FW command to register
			 this value to FW.

INPUT:		 pDrv		- role`s driver instance.
			 maxTxPower - desired max TX power level for the device.

RETURN: 	 N/A.

************************************************************************/
void regulatoryDomain_setRoleMaxTxPower(ti_driver_ifData_t *pDrv,
										int8_t maxTxPower)
{
	int ret = ctrlCmdFw_SetRoleMaxTxPower(pDrv->roleId, maxTxPower);

	if (ret == 0)
    {
        pDrv->fwMaxTxPower = maxTxPower;
		GTRACE(GRP_REG_DOMAIN, "roleId %d max TX power was set to %d dBm",
							   pDrv->roleId,
							   maxTxPower);
    }
	else
	{
		GTRACE(GRP_REG_DOMAIN, "Failed setting role max TX power to FW");
	}
}

/***********************************************************************
 *            	  regulatoryDomain_handlePowerConstraint			   *
 ***********************************************************************
DESCRIPTION: This function is used for interpreting the regulatory max
			 TX power that should be used for a STA. It takes into
			 account IEEE80211d IE, IEEE80211h IE and also Cisco`s
			 DTPC mechanism.

INPUT:		 pDrv				- role`s driver instance.
			 apCapabilities 	- desired max TX power for the device.
			 countryIE 			- IEEE80211d IE.
			 powerConstraintIE	- IEEE80211h TPC Power Constraint IE.
			 ciscoDtpcIE		- Cisco DTPC IE.

RETURN: 	 N/A.

************************************************************************/
void regulatoryDomain_handlePowerConstraint(ti_driver_ifData_t *pDrv,
                               				uint16_t apCapabilities,
                               				dot11_COUNTRY_t *countryIE,
                               				dot11_POWER_CONSTRAINT_t *powerConstraintIE,
                               				dot11_CELL_TP_t *ciscoDtpcIE)
{
    Bool_e hasChannelPower = FALSE, hasCiscoPower = FALSE, validChannelPower = FALSE;
    int8_t apPowerLevel, powerReduction80211h, powerLevelCisco;
    int8_t newApLevel, powerLevel80211d, newMaxPowerLevel;
    uint8_t apBssid[MAC_ADDR_LEN];
    uint8_t channel, apBand, channelTxPower;
    
    if (freq_to_chan(pDrv->freq, &channel, &apBand) < 0)
	{
		GTRACE(GRP_REG_DOMAIN, "ERROR: driver frequency is invalid");
		return;
	}

    if (countryIE &&
       (apCapabilities & WLAN_CAPABILITY_SPECTRUM_MGMT ||
        apCapabilities & WLAN_CAPABILITY_RADIO_MEASUREMENT))
    {
        hasChannelPower = regulatoryDomain_getPowerFromCountryIE(countryIE,
                                                                 channel,
                                                                 apBand,
                                                                 &powerLevel80211d);
        if (powerConstraintIE)
        {
			powerReduction80211h = powerConstraintIE->powerConstraint;
            apPowerLevel = MAX(0, powerLevel80211d - powerReduction80211h);
        }
		else
		{
			apPowerLevel = MAX(0, powerLevel80211d);
		}
    }

    if (ciscoDtpcIE)
    {
        hasCiscoPower = findCiscoDtpc(ciscoDtpcIE, &powerLevelCisco);
    }

    if (!hasChannelPower && !hasCiscoPower)
    {
        return;
    }

    if (ti_driver_get_bssid((void *)pDrv, apBssid) < 0)
	{
		return;
	}

    /* If we have both 802.11h and Cisco DTPC, apply both limits
	 * by picking the smallest of the two power levels advertised.
	 */
	if (hasChannelPower &&
	    (!hasCiscoPower || apPowerLevel <= powerLevelCisco))
    {
        newApLevel = apPowerLevel;

        if (newApLevel == pDrv->fwMaxTxPower)
        {
            return;
        }

        GTRACE(GRP_DRIVER_CC33, "Limiting TX power to %d (%d - %d) "
							    "as advertised by " MACSTR " (attenuating to "
							    "max of device`s power 21dBm, if necessary)",
							    apPowerLevel,
							    powerLevel80211d,
							    powerConstraintIE ? powerReduction80211h : 0,
							    MAC2STR(apBssid));
    } 
	else /* hasCiscoPower is always true here. */
	{ 
        newApLevel = powerLevelCisco;

        if (newApLevel == pDrv->fwMaxTxPower)
        {
            return;
        }

        GTRACE(GRP_DRIVER_CC33, "Limiting TX power to %d dBm "
							    "as advertised by " MACSTR " (DTPC) "
							    "(attenuating to max of device`s power 21dBm, "
								"if necessary)",
							    powerLevelCisco,
							    MAC2STR(apBssid));
    }

    pDrv->apPowerLevel = newApLevel;

    validChannelPower = regulatoryDomain_getChMaxPower((uint16_t )channel,
													   &channelTxPower);
	if (!validChannelPower)
	{
		return;
	}

	/* Take minimum of max TX power from reg domain DB and 11d
	 * reducing TPC power constraint.
	 */
	newMaxPowerLevel = MIN(channelTxPower, pDrv->apPowerLevel);
    
    if (newMaxPowerLevel != pDrv->fwMaxTxPower)
    {
        regulatoryDomain_setRoleMaxTxPower(pDrv, newMaxPowerLevel);
    }
}
