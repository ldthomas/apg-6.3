/*******************************************************************************
  APG Version 6.3
  Copyright (C) 2005 - 2012 Lowell D. Thomas, all rights reserved

  author:  Lowell D. Thomas
  email:   lowell@coasttocoastresearch.com
  website: http://www.coasttocoastresearch.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
  or write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*******************************************************************************/
#include "Apg.h"
#if defined(_APG_CFG_STATS)
#include "Private.h"

#define SASSERT(cond) if(!(cond)){spParserCtx->pfnAlertHandler(__LINE__, __FILE__);}

static void	vStatsCtor(APG_PARSER_CTX* spCtx);
static void	vStatsDtor(APG_PARSER_CTX* spCtx);
static void	vStatsClear(APG_PARSER_CTX* spCtx);
static void	vStatsGet(APG_PARSER_CTX* spParserCtx, void* vpInputOutput, apg_uint* uipSize);
static void vStatsGetNameAddresses(APG_PARSER_CTX* spParserCtx, APG_PARSER_STATS* spPublicStats);
static apg_uint uiStatsGetNames(APG_PARSER_CTX* spParserCtx, APG_PARSER_STATS* spPublicStats);
static int iCompAlpha(const void* vpLhs, const void* vpRhs);
static int iCompCount(const void* vpLhs, const void* vpRhs);

static void vStatsCtor(APG_PARSER_CTX* spParserCtx){
	APG_STATS_CTX* spCtx;
	APG_PARSER_STATS* spPublicStats;
	apg_uint uiSize, uiNameSize, uiNameStatsSize, uiNameCount, uiParserStatsSize;
	if(!spParserCtx->vpStatsCtx){
		apg_uint i;
		// compute sizes
		uiNameCount = spParserCtx->uiRuleCount + spParserCtx->uiUdtCount;
		uiNameStatsSize = uiNameCount * sizeof(APG_NAME_STAT);
		uiNameSize = uiStatsGetNames(spParserCtx, NULL);
		uiParserStatsSize = sizeof(APG_PARSER_STATS) + uiNameSize + (3 * uiNameStatsSize);
		uiSize = sizeof(APG_STATS_CTX) + uiParserStatsSize;

		// allocate memory
		spCtx = (APG_STATS_CTX*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
		SASSERT(spCtx);
		memset((void*)spCtx, 0, uiSize);

		// initialize APG_STATS_CTX
		spCtx->uiSize = uiSize;
		spCtx->uiNameSize = uiNameSize;
		spCtx->uiNameStatsSize = uiNameStatsSize;
		spCtx->spPublicStats = (APG_PARSER_STATS*)((char*)spCtx + sizeof(APG_STATS_CTX));

		// initialize APG_PARSER_STATS
		spPublicStats = spCtx->spPublicStats;
		spPublicStats->uiSize = sizeof(APG_PARSER_STATS) + uiNameSize + (3 * uiNameStatsSize);
		spPublicStats->uiNameCount = spParserCtx->uiRuleCount + spParserCtx->uiUdtCount;
		spPublicStats->uiRuleCount = spParserCtx->uiRuleCount;
		spPublicStats->uiUdtCount = spParserCtx->uiUdtCount;
		spPublicStats->spNameStats = (APG_NAME_STAT*)((char*)spPublicStats + sizeof(APG_PARSER_STATS));
		spPublicStats->spNameStatsAlpha = (APG_NAME_STAT*)((char*)spPublicStats->spNameStats + uiNameStatsSize);
		spPublicStats->spNameStatsCount = (APG_NAME_STAT*)((char*)spPublicStats->spNameStatsAlpha + uiNameStatsSize);
		spPublicStats->cpNames = (char*)spCtx->spPublicStats + sizeof(APG_PARSER_STATS) + (3 * uiNameStatsSize);

		// initialize the spNameStats
		uiStatsGetNames(spParserCtx, spPublicStats);
		vStatsGetNameAddresses(spParserCtx, spPublicStats);

		// sort alphabetically
		for(i = 0; i < uiNameCount; i++){spPublicStats->spNameStatsAlpha[i] = spPublicStats->spNameStats[i];}
		qsort((void*)spPublicStats->spNameStatsAlpha, uiNameCount, sizeof(APG_NAME_STAT), iCompAlpha);

		spParserCtx->vpStatsCtx = (void*)spCtx;
	} else{vStatsClear(spParserCtx);}
}

static void vStatsDtor(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpStatsCtx){
		APG_STATS_CTX* spCtx = (APG_STATS_CTX*)spParserCtx->vpStatsCtx;
		memset((void*)spCtx, 0, sizeof(APG_PARSER_STATS));
		vMemFree(spParserCtx->vpMemCtx, (void*)spCtx);
		spParserCtx->vpStatsCtx = NULL;
	}
}

static void	vStatsClear(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpStatsCtx){
		APG_STATS_CTX* spCtx = (APG_STATS_CTX*)spParserCtx->vpStatsCtx;
		APG_PARSER_STATS* spPublicStats = (APG_PARSER_STATS*)spCtx->spPublicStats;
		apg_uint i;
		for(i = 0; i < spPublicStats->uiNameCount; i++){
			memset((void*)&spPublicStats->spNameStats[i], 0, sizeof(APG_STAT));
			memset((void*)&spPublicStats->spNameStatsAlpha[i], 0, sizeof(APG_STAT));
			memset((void*)&spPublicStats->spNameStatsCount[i], 0, sizeof(APG_STAT));
		}
		memset((void*)&spPublicStats->sRnm, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sUdt, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sRep, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sAlt, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sCat, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sAnd, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sNot, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sTrg, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sTbs, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sTls, 0, sizeof(APG_STAT));
		memset((void*)&spPublicStats->sTotal, 0, sizeof(APG_STAT));
	}
}

static void vStatsGetNameAddresses(APG_PARSER_CTX* spParserCtx, APG_PARSER_STATS* spPublicStats){
	apg_uint i, uiLen;
	char* cpNameBuffer = spPublicStats->cpNames;
	for(i = 0; i < spPublicStats->uiNameCount; i++){
		uiLen = strlen(cpNameBuffer) + 1;
		spPublicStats->spNameStats[i].cpName = cpNameBuffer;
		spPublicStats->spNameStats[i].uiIndex = i;
		cpNameBuffer += uiLen;
	}
}

static apg_uint uiStatsGetNames(APG_PARSER_CTX* spParserCtx, APG_PARSER_STATS* spPublicStats){
	apg_uint uiSize = 0;
	apg_uint i, j, uiLen;
	char* cpNameBuffer = spPublicStats ? spPublicStats->cpNames : NULL;
	for(i = 0; i < spParserCtx->uiRuleCount; i++){
		uiLen = strlen(spParserCtx->spRules[i].cpRuleName) + 1;
		uiSize += uiLen;
		if(cpNameBuffer){
			strcpy(cpNameBuffer, spParserCtx->spRules[i].cpRuleName);
			cpNameBuffer += uiLen;
		}
	}
	for(i = 0; i < spParserCtx->uiUdtCount; i++){
		uiLen = strlen(spParserCtx->spUdts[i].cpUdtName) + 1;
		uiSize += uiLen;
		if(cpNameBuffer){
			strcpy(cpNameBuffer, spParserCtx->spUdts[i].cpUdtName);
			j = i + spParserCtx->uiRuleCount;
			cpNameBuffer += uiLen;
		}
	}
	return uiSize;
}
static void	vStatsGet(APG_PARSER_CTX* spParserCtx, void* vpInputOutput, apg_uint* uipSize){
	APG_STATS_CTX* spCtx = (APG_STATS_CTX*)spParserCtx->vpStatsCtx;
	APG_PARSER_STATS* spPublicStats;
	APG_PARSER_STATS* spStats;
	apg_uint i;
	while(APG_TRUE){
		if(!spCtx){break;}
		if(!uipSize){break;}
		spPublicStats = spCtx->spPublicStats;
		*uipSize = spPublicStats->uiSize;
		if(!vpInputOutput){break;}

		// copy stats
		spStats = (APG_PARSER_STATS*)vpInputOutput;
		memcpy((void*)spStats, (void*)spPublicStats, spPublicStats->uiSize);

		// translate rule names in copied stats
		vStatsGetNameAddresses(spParserCtx, spStats);

		// sort on names
		for(i = 0; i < spPublicStats->uiNameCount; i++){spStats->spNameStatsAlpha[i] = spStats->spNameStats[i];}
		qsort((void*)spPublicStats->spNameStatsAlpha, spPublicStats->uiNameCount, sizeof(APG_NAME_STAT), iCompAlpha);

		// sort on counts
		for(i = 0; i < spPublicStats->uiNameCount; i++){spStats->spNameStatsCount[i] = spStats->spNameStats[i];}
		qsort((void*)spPublicStats->spNameStatsCount, spPublicStats->uiNameCount, sizeof(APG_NAME_STAT), iCompCount);
		break;
	}
}

void vStatsAdmin(APG_PARSER_CTX* spParserCtx, apg_uint uiAction, void* vpInputOutput, apg_uint* uipReturn, apg_uint* uipConfigured){
	switch(uiAction){
	case STATS_ACTION_ENABLE:
		vStatsClear(spParserCtx);
		vStatsCtor(spParserCtx);
		break;
	case STATS_ACTION_DISABLE:
		vStatsDtor(spParserCtx);
		break;
	case STATS_ACTION_GETSTATS:
		vStatsGet(spParserCtx, vpInputOutput, uipReturn);
		break;
	default:
		SASSERT(APG_FALSE);
		break;
	}
	*uipConfigured = APG_TRUE;
}

void	vStats(APG_PARSER_CTX* spParserCtx, apg_uint uiAction, apg_uint uiPhraseLength, apg_uint uiOpId, apg_uint uiRuleUdtId){
	if(spParserCtx->vpStatsCtx){
		APG_STATS_CTX* spCtx = (APG_STATS_CTX*)spParserCtx->vpStatsCtx;
		APG_PARSER_STATS* spPublicStats = (APG_PARSER_STATS*)spCtx->spPublicStats;
		APG_STAT* spStat = NULL;
		APG_NAME_STAT* spRule = NULL;
		apg_uint uiState;
		if(uiAction == STATS_ACTION_COLLECT){
			switch(uiOpId){
			case P_RNM:
				spStat = &spPublicStats->sRnm;
				SASSERT(uiRuleUdtId < spParserCtx->uiRuleCount);
				spRule = &spPublicStats->spNameStats[uiRuleUdtId];
				break;
			case P_UDT:
				spStat = &spPublicStats->sUdt;
				SASSERT(uiRuleUdtId < spParserCtx->uiUdtCount);
				spRule = &spPublicStats->spNameStats[spPublicStats->uiRuleCount + uiRuleUdtId];
				break;
			case P_REP:
				spStat = &spPublicStats->sRep;
				break;
			case P_ALT:
				spStat = &spPublicStats->sAlt;
				break;
			case P_CAT:
				spStat = &spPublicStats->sCat;
				break;
			case P_AND:
				spStat = &spPublicStats->sAnd;
				break;
			case P_NOT:
				spStat = &spPublicStats->sNot;
				break;
			case P_TRG:
				spStat = &spPublicStats->sTrg;
				break;
			case P_TBS:
				spStat = &spPublicStats->sTbs;
				break;
			case P_TLS:
				spStat = &spPublicStats->sTls;
				break;
			default:
				SASSERT(APG_FALSE);
				break;
			}
			if(uiPhraseLength == APG_UNDEFINED){uiState = NOMATCH;}
			else if(uiPhraseLength == 0){uiState = EMPTY;}
			else {uiState = MATCH;}
			spStat->uiTotal++;
			spPublicStats->sTotal.uiTotal++;
			switch(uiState){
			case MATCH:
				spStat->uiMatch++;
				spPublicStats->sTotal.uiMatch++;
				break;
			case EMPTY:
				spStat->uiEmpty++;
				spPublicStats->sTotal.uiEmpty++;
				break;
			case NOMATCH:
				spStat->uiNoMatch++;
				spPublicStats->sTotal.uiNoMatch++;
				break;
			default:
				SASSERT(APG_FALSE);
				break;
			}
			if(spRule){
				spRule->sStat.uiTotal++;
				switch(uiState){
				case MATCH:
					spRule->sStat.uiMatch++;
					break;
				case EMPTY:
					spRule->sStat.uiEmpty++;
					break;
				case NOMATCH:
					spRule->sStat.uiNoMatch++;
					break;
				default:
					SASSERT(APG_FALSE);
					break;
				}
			}
		} else{SASSERT(APG_FALSE);}
	}
}

static int iCompAlpha(const void* vpLhs, const void* vpRhs){
	APG_NAME_STAT* spLhs = (APG_NAME_STAT*)vpLhs;
	APG_NAME_STAT* spRhs = (APG_NAME_STAT*)vpRhs;
	return apg_stricmp(spLhs->cpName, spRhs->cpName);
}

static int iCompCount(const void* vpLhs, const void* vpRhs){
	int iRet;
	APG_NAME_STAT* spLhs = (APG_NAME_STAT*)vpLhs;
	APG_NAME_STAT* spRhs = (APG_NAME_STAT*)vpRhs;
	if(spLhs->sStat.uiTotal < spRhs->sStat.uiTotal){iRet = 1;}
	else if(spLhs->sStat.uiTotal > spRhs->sStat.uiTotal){iRet = -1;}
	else{iRet = 0;}
	return iRet;
}
#endif	// #if defined(_APG_CFG_STATS)

