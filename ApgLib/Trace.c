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
#ifdef _APG_CFG_TRACE
#include "Grammar.h"
#include "Private.h"
#include <stdio.h>

#define TASSERT(cond) if(!(cond)){spParserCtx->pfnAlertHandler(__LINE__, __FILE__);}

// just in case we want to provide more flexibility later
static FILE* spOut = NULL;

static apg_uint uiIndent(apg_uint uiIndent, char* cpBuffer, apg_uint uiBufferLen);
static void vTraceBegin(APG_TRACE_CTX* spCtx);
static void vTraceEnd(APG_TRACE_CTX* spCtx, apg_uint uiPhraseLen);
static void vTraceDown(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId, apg_uint uiOffset);
static void vTraceUp(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId, apg_uint uiOffset, apg_uint uiPhraseLen);
static void vTraceEnableOp(APG_TRACE_CTX* spCtx, apg_uint uiId, apg_uint uiEnable);
static void vTraceEnableRule(APG_TRACE_CTX* spCtx, apg_uint uiIndex, apg_uint uiEnable);
static void vTraceEnableUdt(APG_TRACE_CTX* spCtx, apg_uint uiIndex, apg_uint uiEnable);
static void vTraceSetRange(APG_TRACE_CTX* spCtx, apg_uint uiBegin, apg_uint uiCount);
static void vEnableRules(apg_uint* uipRules, apg_uint uiCount, apg_uint uiEnable);
static void vEnableDefault(APG_TRACE_CTX* spCtx);
static apg_uint uiDoTrace(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId);

static void vTraceOpRnm(void* vpBuf, char* cpName);
static void vTraceOpUdt(void* vpBuf, char* cpName);
static void vTraceOpAlt(void* vpBuf, apg_uint uiChildren);
static void vTraceOpCat(void* vpBuf, apg_uint uiChildren);
static void vTraceOpAnd(void* vpBuf);
static void vTraceOpNot(void* vpBuf);
static void vTraceOpRep(void* vpBuf, apg_uint uiMin, apg_uint uiMax);
static void vTraceOpTrg(void* vpBuf, apg_achar acMin, apg_achar acMax);
static void vTraceOpTbs(void* vpBuf, apg_achar* acpString, apg_uint uiLen);
static void vTraceOpTls(void* vpBuf, apg_achar* acpString, apg_uint uiLen);

void vTraceCtor(APG_PARSER_CTX* spParserCtx){
	if(!spParserCtx->vpTraceCtx){
		apg_uint uiSize;
		APG_TRACE_CTX* spCtx = (APG_TRACE_CTX*)vpMemAlloc(spParserCtx->vpMemCtx, sizeof(APG_TRACE_CTX));
		TASSERT(spCtx);
		memset((void*)spCtx, 0, sizeof(APG_TRACE_CTX));
		spOut = stdout;
		spCtx->spParserCtx = spParserCtx;
		spCtx->uiRecordNumber = 0;
		spCtx->uiTreeDepth = 0;
		spCtx->uiTraceRootIndex = spParserCtx->uiRuleCount;
		spCtx->vpVecRecordStack = vpVecCtor(spParserCtx->vpMemCtx, sizeof(apg_uint), 1028);
		TASSERT(spCtx->vpVecRecordStack);
		uiSize = sizeof(apg_uint) * spParserCtx->uiRuleCount;
		spCtx->uipRules = (apg_uint*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
		TASSERT(spCtx->uipRules);
		if(spParserCtx->uiUdtCount){
			uiSize = sizeof(apg_uint) * spParserCtx->uiUdtCount;
			spCtx->uipUdts = (apg_uint*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
			TASSERT(spCtx->uipUdts);
		}
		vEnableDefault(spCtx);
		spParserCtx->vpTraceCtx = (void*)spCtx;
	}
}

void vTraceDtor(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpTraceCtx){
		APG_TRACE_CTX* spCtx = (APG_TRACE_CTX*)spParserCtx->vpTraceCtx;
		vVecDtor(spCtx->vpVecRecordStack);
		vMemFree(spParserCtx->vpMemCtx, spCtx->uipRules);
		if(spParserCtx->uiUdtCount){vMemFree(spParserCtx->vpMemCtx, spCtx->uipUdts);}
		memset((void*)spCtx, 0, sizeof(APG_TRACE_CTX));
		vMemFree(spParserCtx->vpMemCtx, spParserCtx->vpTraceCtx);
		spParserCtx->vpTraceCtx = NULL;
	}
}

void vTraceClear(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpTraceCtx){
		APG_TRACE_CTX* spCtx = (APG_TRACE_CTX*)spParserCtx->vpTraceCtx;
		spCtx->uiRecordNumber = 0;
		spCtx->uiTreeDepth = 0;
		vVecClear(spCtx->vpVecRecordStack);
	}
}

void	vTraceAdmin(APG_PARSER_CTX* spParserCtx, apg_uint uiAction, apg_uint uiId, apg_uint uiEnable, apg_uint* uipConfigured){
	if(uipConfigured){*uipConfigured = APG_TRUE;}
	switch(uiAction){
	case TRACE_ACTION_ENABLE:
		vTraceDtor(spParserCtx);
		vTraceCtor(spParserCtx);
		break;
	case TRACE_ACTION_DISABLE:
		vTraceDtor(spParserCtx);
		break;
	case TRACE_ACTION_OP:
		if(spParserCtx->vpTraceCtx){vTraceEnableOp((APG_TRACE_CTX*)spParserCtx->vpTraceCtx, uiId, uiEnable);}
		break;
	case TRACE_ACTION_RULE:
		if(spParserCtx->vpTraceCtx){vTraceEnableRule((APG_TRACE_CTX*)spParserCtx->vpTraceCtx, uiId, uiEnable);}
		break;
	case TRACE_ACTION_UDT:
		if(spParserCtx->vpTraceCtx){vTraceEnableUdt((APG_TRACE_CTX*)spParserCtx->vpTraceCtx, uiId, uiEnable);}
		break;
	case TRACE_ACTION_RANGE:
		if(spParserCtx->vpTraceCtx){vTraceSetRange((APG_TRACE_CTX*)spParserCtx->vpTraceCtx, uiId, uiEnable);}
		break;
	default:
		TASSERT(APG_FALSE);
		break;
	}
}

void vTrace(APG_PARSER_CTX* spParserCtx, APG_OPCODE* spOp, apg_uint uiAction, apg_uint uiId, apg_uint uiOffset, apg_uint uiPhraseLen){
	APG_TRACE_CTX* spCtx = (APG_TRACE_CTX*)spParserCtx->vpTraceCtx;
	apg_uint uiState, uiStrLen;
	const apg_achar* acpPhrase;

	if(spParserCtx->vpTraceCtx){
		if(uiPhraseLen == APG_UNDEFINED){uiState = NOMATCH;}
		else if(uiPhraseLen == 0){uiState = EMPTY;}
		else{uiState = MATCH;}
		uiStrLen = (uiOffset < spParserCtx->uiInputStringLen) ? spParserCtx->uiInputStringLen - uiOffset: 0;
		acpPhrase = spParserCtx->acpInputString + uiOffset;
		switch(uiAction){
		case TRACE_ACTION_BEGIN:
			vTraceBegin(spCtx);
			break;
		case TRACE_ACTION_DOWN:
			vTraceDown(spCtx, spOp, uiId, uiOffset);
			break;
		case TRACE_ACTION_UP:
			vTraceUp(spCtx, spOp, uiId, uiOffset, uiPhraseLen);
			break;
		case TRACE_ACTION_END:
			vTraceEnd(spCtx, uiPhraseLen);
			break;
		default:
			TASSERT(APG_FALSE);
			break;
		}
		fflush(spOut);
	}
}

static void vEnableRules(apg_uint* uipRules, apg_uint uiCount, apg_uint uiEnable){
	apg_uint i = 0;
	for(; i < uiCount; i++){uipRules[i] = uiEnable;}
}
static void vEnableDefault(APG_TRACE_CTX* spCtx){
	// non-rules off
	spCtx->uiRangeBegin = 0;
	spCtx->uiRangeCount = APG_INFINITE;
	spCtx->uiAlt = APG_FALSE;
	spCtx->uiCat = APG_FALSE;
	spCtx->uiRep = APG_FALSE;
	spCtx->uiAnd = APG_FALSE;
	spCtx->uiNot = APG_FALSE;
	spCtx->uiTrg = APG_FALSE;
	spCtx->uiTbs = APG_FALSE;
	spCtx->uiTls = APG_FALSE;

	// rules on
	spCtx->uiRnm = APG_TRUE;
	vEnableRules(spCtx->uipRules, spCtx->spParserCtx->uiRuleCount, APG_TRUE);
	spCtx->uiUdt = APG_TRUE;
	if(spCtx->spParserCtx->uiUdtCount){vEnableRules(spCtx->uipUdts, spCtx->spParserCtx->uiUdtCount, APG_TRUE);}
}
static void vTraceEnableOp(APG_TRACE_CTX* spCtx, apg_uint uiId, apg_uint uiEnable){
	switch(uiId){
	case APG_TRACE_ALL:
		spCtx->uiAlt = uiEnable;
		spCtx->uiCat = uiEnable;
		spCtx->uiRep = uiEnable;
		spCtx->uiRnm = uiEnable;
		vEnableRules(spCtx->uipRules, spCtx->spParserCtx->uiRuleCount, uiEnable);
		spCtx->uiUdt = uiEnable;
		if(spCtx->spParserCtx->uiUdtCount){vEnableRules(spCtx->uipUdts, spCtx->spParserCtx->uiUdtCount, uiEnable);}
		spCtx->uiAnd = uiEnable;
		spCtx->uiNot = uiEnable;
		spCtx->uiTrg = uiEnable;
		spCtx->uiTbs = uiEnable;
		spCtx->uiTls = uiEnable;
		break;
	case APG_TRACE_TRG:
		spCtx->uiTrg = uiEnable;
		break;
	case APG_TRACE_TBS:
		spCtx->uiTbs = uiEnable;
		break;
	case APG_TRACE_TLS:
		spCtx->uiTls = uiEnable;
		break;
	case APG_TRACE_AND:
		spCtx->uiAnd = uiEnable;
		break;
	case APG_TRACE_NOT:
		spCtx->uiNot = uiEnable;
		break;
	case APG_TRACE_CAT:
		spCtx->uiCat = uiEnable;
		break;
	case APG_TRACE_ALT:
		spCtx->uiAlt = uiEnable;
		break;
	case APG_TRACE_REP:
		spCtx->uiRep = uiEnable;
		break;
	case APG_TRACE_RNM:
		spCtx->uiRnm = uiEnable;
		vEnableRules(spCtx->uipRules, spCtx->spParserCtx->uiRuleCount, uiEnable);
		break;
	case APG_TRACE_UDT:
		spCtx->uiUdt = uiEnable;
		if(spCtx->spParserCtx->uiUdtCount){vEnableRules(spCtx->uipUdts, spCtx->spParserCtx->uiUdtCount, uiEnable);}
		break;
	case APG_TRACE_COUNT:
		spCtx->uiCountOnly= uiEnable;
		break;
	}
}
static void vTraceEnableRule(APG_TRACE_CTX* spCtx, apg_uint uiIndex, apg_uint uiEnable){
	if(uiIndex < spCtx->spParserCtx->uiRuleCount){spCtx->uipRules[uiIndex] = uiEnable;}
}
static void vTraceEnableUdt(APG_TRACE_CTX* spCtx, apg_uint uiIndex, apg_uint uiEnable){
	if(uiIndex < spCtx->spParserCtx->uiUdtCount){spCtx->uipUdts[uiIndex] = uiEnable;}
}
static void vTraceSetRange(APG_TRACE_CTX* spCtx, apg_uint uiBegin, apg_uint uiCount){
	spCtx->uiRangeBegin = uiBegin;
	spCtx->uiRangeCount = uiCount;
}
static void vTraceBegin(APG_TRACE_CTX* spCtx){
	APG_OPCODE sOp;
	APG_RULE sRule;
	sRule.cpRuleName = "_TRACE_ROOT";
	sRule.uiRuleIndex = spCtx->spParserCtx->uiRuleCount;
	sOp.sUnion.sRnm.spRule = &sRule;
	fprintf(spOut, "\n  ***: TRACING PARSE TREE ***\n");
	fprintf(spOut, "    a: this  record number\n");
	fprintf(spOut, "    b: other record number\n");
	fprintf(spOut, "    c: tree depth\n");
	fprintf(spOut, "    d: state: M=MATCH, N=NOMATCH, E=EMPTY\n");
	fprintf(spOut, "    e: indented operator\n");
	fprintf(spOut, "    f: phrase length (if any)\n");
	fprintf(spOut, "    g: phrase (... = truncated\n");
	fprintf(spOut, "%5s:%5s:%3s:%s:%s:%s:%s\n", "a", "b", "c", "d", " e", "f", "g");
	fprintf(spOut, "%5s:%5s:%3s:%s:%s:%s:%s\n", "-----", "-----", "---", "-", "--", "-", "---");
	vTraceDown(spCtx, &sOp, P_RNM, 0);
}
static void vTraceEnd(APG_TRACE_CTX* spCtx, apg_uint uiPhraseLen){
	APG_OPCODE sOp;
	APG_RULE sRule;
	sRule.cpRuleName = "_TRACE_ROOT";
	sRule.uiRuleIndex = spCtx->spParserCtx->uiRuleCount;
	sOp.sUnion.sRnm.spRule = &sRule;
	vTraceUp(spCtx, &sOp, P_RNM, 0, uiPhraseLen);
	fprintf(spOut, "%5s:%5s:%3s:%s:%s:%s:%s\n", "-----", "-----", "---", "-", "--", "-", "---");
	fprintf(spOut, "%5s:%5s:%3s:%s:%s:%s:%s\n", "a", "b", "c", "d", " e", "f", "g");
	fprintf(spOut, "    a: this  record number\n");
	fprintf(spOut, "    b: other record number\n");
	fprintf(spOut, "    c: tree depth\n");
	fprintf(spOut, "    d: state: M=MATCH, N=NOMATCH, E=EMPTY\n");
	fprintf(spOut, "    e: indented operator\n");
	fprintf(spOut, "    f: phrase length (if any)\n");
	fprintf(spOut, "    g: phrase (... = truncated)\n");
}


static apg_uint uiIndent(apg_uint uiIndent, char* cpBuffer, apg_uint uiBufferLen){
	apg_uint i, uiLen = 0;
	if(cpBuffer && uiBufferLen){
		uiLen = uiIndent % (uiBufferLen/2);
		cpBuffer[0] = 0;
		for(i = 0; i < uiLen; i++){
			strcat(cpBuffer, "-");
		}
	}
	return uiLen;
}
static char cState(apg_uint uiState){
	char cRet = 'U';
	switch(uiState){
	case NOMATCH: cRet = 'N'; break;
	case MATCH: cRet = 'M'; break;
	case EMPTY: cRet = 'E'; break;
	case PRE_PARSE: cRet = ' '; break;
	default: cRet = 'U'; break;
	}
	return cRet;
}
static apg_uint uiDoTrace(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId){
	apg_uint uiRet = APG_FALSE;
	APG_PARSER_CTX* spParserCtx = spCtx->spParserCtx;
	apg_uint uiMax;
	if(uiId == P_RNM && spOp->sUnion.sRnm.spRule->uiRuleIndex == spCtx->uiTraceRootIndex){uiRet = APG_TRUE;}
	else if(!spCtx->uiCountOnly){
		uiMax = (spCtx->uiRangeBegin > APG_INFINITE - spCtx->uiRangeCount) ? APG_INFINITE: spCtx->uiRangeBegin + spCtx->uiRangeCount;
		if(spCtx->uiRecordNumber >= spCtx->uiRangeBegin && spCtx->uiRecordNumber <= uiMax){
			switch(uiId){
			case P_RNM:
				if(spCtx->uipRules[spOp->sUnion.sRnm.spRule->uiRuleIndex]){uiRet = APG_TRUE;}
				break;
			case P_UDT:
				if(spCtx->uipUdts[spOp->sUnion.sUdt.spUdt->uiUdtIndex]){uiRet = APG_TRUE;}
				break;
			case P_REP:
				if(spCtx->uiRep){uiRet = APG_TRUE;}
				break;
			case P_ALT:
				if(spCtx->uiAlt){uiRet = APG_TRUE;}
				break;
			case P_CAT:
				if(spCtx->uiCat){uiRet = APG_TRUE;}
				break;
			case P_AND:
				if(spCtx->uiAnd){uiRet = APG_TRUE;}
				break;
			case P_NOT:
				if(spCtx->uiNot){uiRet = APG_TRUE;}
				break;
			case P_TRG:
				if(spCtx->uiTrg){uiRet = APG_TRUE;}
				break;
			case P_TBS:
				if(spCtx->uiTbs){uiRet = APG_TRUE;}
				break;
			case P_TLS:
				if(spCtx->uiTls){uiRet = APG_TRUE;}
				break;
			default:
				TASSERT(APG_FALSE);
				break;
			}
		}
	}
	return uiRet;
}
static void vTraceDown(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId, apg_uint uiOffset){
	APG_PARSER_CTX* spParserCtx = spCtx->spParserCtx;
	char caPrtBuf[APG_DISPLAY_MAX_LINE + sizeof(PRINTBUF) + 1];
	void* vpPrtBuf = NULL;
	apg_uint uiIsTruncated = APG_FALSE;
	char caIndentBuf[APG_DISPLAY_MAX_LINE];
	char caScratchBuf[2*APG_DISPLAY_MAX_LINE];
	apg_uint uiAChars, uiPrintChars;
	void* vpTest;
	const apg_achar* acpPhrase;
	apg_uint uiPhraseLen;
	vpTest = vpVecPush(spCtx->vpVecRecordStack, (void*)&spCtx->uiRecordNumber);
	TASSERT(vpTest);
	if(uiDoTrace(spCtx, spOp, uiId)){
		vpPrtBuf = vpStrBufInit(&caPrtBuf[0], sizeof(caPrtBuf));
		while(APG_TRUE && vpPrtBuf){
			acpPhrase = spCtx->spParserCtx->acpInputString + uiOffset;
			uiPhraseLen = (uiOffset < spCtx->spParserCtx->uiInputStringLen) ? spCtx->spParserCtx->uiInputStringLen - uiOffset : 0;
			sprintf(&caScratchBuf[0], "%5lu:-----:%3lu:%c:", (unsigned long int)spCtx->uiRecordNumber, (unsigned long int)spCtx->uiTreeDepth, cState(PRE_PARSE));
			uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			uiIndent(spCtx->uiTreeDepth, caIndentBuf, sizeof(caIndentBuf));
			uiStrBufCat(vpPrtBuf, &caIndentBuf[0]);
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			switch(uiId){
			case P_RNM:
				vTraceOpRnm(vpPrtBuf, spOp->sUnion.sRnm.spRule->cpRuleName);
				break;
			case P_UDT:
				vTraceOpUdt(vpPrtBuf, spOp->sUnion.sUdt.spUdt->cpUdtName);
				break;
			case P_REP:
				vTraceOpRep(vpPrtBuf, spOp->sUnion.sRep.uiMin, spOp->sUnion.sRep.uiMax);
				break;
			case P_ALT:
				vTraceOpAlt(vpPrtBuf, spOp->sUnion.sAlt.uiChildCount);
				break;
			case P_CAT:
				vTraceOpCat(vpPrtBuf, spOp->sUnion.sCat.uiChildCount);
				break;
			case P_AND:
				vTraceOpAnd(vpPrtBuf);
				break;
			case P_NOT:
				vTraceOpNot(vpPrtBuf);
				break;
			case P_TRG:
				vTraceOpTrg(vpPrtBuf, (apg_uint)spOp->sUnion.sTrg.acMin, (apg_uint)spOp->sUnion.sTrg.acMax);
				break;
			case P_TBS:
				vTraceOpTbs(vpPrtBuf, spOp->sUnion.sTbs.acpStrTbl, spOp->sUnion.sTbs.uiStrLen);
				break;
			case P_TLS:
				vTraceOpTls(vpPrtBuf, spOp->sUnion.sTls.acpStrTbl, spOp->sUnion.sTls.uiStrLen);
				break;
			default:
				TASSERT(APG_FALSE);
				break;
			}
			uiPrintChars = uiStrBufCat(vpPrtBuf, ": :");
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			uiAChars = uiACharToString(&caScratchBuf[0], sizeof(caScratchBuf), acpPhrase, uiPhraseLen);
			uiPrintChars = uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
			if(uiAChars < uiPhraseLen){uiIsTruncated = APG_TRUE;break;}
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
	spCtx->uiTreeDepth++;
			break;
		}
		fprintf(spOut, "%s", cpStrBufString(vpPrtBuf));
		if(uiIsTruncated){fprintf(spOut, "...");}
		fprintf(spOut, "\n");
	}
	spCtx->uiRecordNumber++;
}

static void vTraceUp(APG_TRACE_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiId, apg_uint uiOffset, apg_uint uiPhraseLen){
	APG_PARSER_CTX* spParserCtx = spCtx->spParserCtx;
	char caPrtBuf[APG_DISPLAY_MAX_LINE + sizeof(PRINTBUF) + 1];
	void* vpPrtBuf = NULL;
	apg_uint uiIsTruncated = APG_FALSE;
	char caIndentBuf[APG_DISPLAY_MAX_LINE];
	char caScratchBuf[2*APG_DISPLAY_MAX_LINE];
	apg_uint uiAChars, uiPrintChars;
	int uiState;
	const apg_achar* acpPhrase;
	apg_uint* uipOtherRecord;
	uipOtherRecord = (apg_uint*)vpVecPop(spCtx->vpVecRecordStack);
	TASSERT(uipOtherRecord);
	if(uiDoTrace(spCtx, spOp, uiId)){
		vpPrtBuf = vpStrBufInit(&caPrtBuf[0], sizeof(caPrtBuf));
		while(APG_TRUE && vpPrtBuf){
	spCtx->uiTreeDepth--;
			acpPhrase = spCtx->spParserCtx->acpInputString + uiOffset;
			if(uiPhraseLen == APG_UNDEFINED){uiState = NOMATCH;}
			else if(uiPhraseLen == 0){uiState = EMPTY;}
			else{uiState = MATCH;}
			sprintf(&caScratchBuf[0], "%5lu:%5lu:%3lu:%c:",
					(unsigned long int)spCtx->uiRecordNumber, (unsigned long int)*uipOtherRecord, (unsigned long int)spCtx->uiTreeDepth, cState(uiState));
			uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			uiIndent(spCtx->uiTreeDepth, caIndentBuf, sizeof(caIndentBuf));
			uiStrBufCat(vpPrtBuf, &caIndentBuf[0]);
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			switch(uiId){
			case P_RNM:
				vTraceOpRnm(vpPrtBuf, spOp->sUnion.sRnm.spRule->cpRuleName);
				break;
			case P_UDT:
				vTraceOpUdt(vpPrtBuf, spOp->sUnion.sUdt.spUdt->cpUdtName);
				break;
			case P_REP:
				vTraceOpRep(vpPrtBuf, spOp->sUnion.sRep.uiMin, spOp->sUnion.sRep.uiMax);
				break;
			case P_ALT:
				vTraceOpAlt(vpPrtBuf, spOp->sUnion.sAlt.uiChildCount);
				break;
			case P_CAT:
				vTraceOpCat(vpPrtBuf, spOp->sUnion.sCat.uiChildCount);
				break;
			case P_AND:
				vTraceOpAnd(vpPrtBuf);
				break;
			case P_NOT:
				vTraceOpNot(vpPrtBuf);
				break;
			case P_TRG:
				vTraceOpTrg(vpPrtBuf, (apg_uint)spOp->sUnion.sTrg.acMin, (apg_uint)spOp->sUnion.sTrg.acMax);
				break;
			case P_TBS:
				vTraceOpTbs(vpPrtBuf, spOp->sUnion.sTbs.acpStrTbl, spOp->sUnion.sTbs.uiStrLen);
				break;
			case P_TLS:
				vTraceOpTls(vpPrtBuf, spOp->sUnion.sTls.acpStrTbl, spOp->sUnion.sTls.uiStrLen);
				break;
			default:
				TASSERT(APG_FALSE);
				break;
			}
			if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			if(uiPhraseLen == APG_UNDEFINED){
				uiPrintChars = uiStrBufCat(vpPrtBuf, ": :");
			} else{
				sprintf(&caScratchBuf[0], ":%lu:", (unsigned long int)uiPhraseLen);
				uiPrintChars = uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
				uiAChars = uiACharToString(&caScratchBuf[0], sizeof(caScratchBuf), acpPhrase, uiPhraseLen);
				uiPrintChars = uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
				if(uiAChars < uiPhraseLen){uiIsTruncated = APG_TRUE;break;}
				if(uiStrBufIsTruncated(vpPrtBuf)){uiIsTruncated = APG_TRUE;break;}
			}
			break;
		}
		fprintf(spOut, "%s", cpStrBufString(vpPrtBuf));
		if(uiIsTruncated){fprintf(spOut, "...");}
		fprintf(spOut, "\n");
	}
	spCtx->uiRecordNumber++;
}
static void vTraceOpRnm(void* vpBuf, char* cpName){
	uiStrBufCat(vpBuf, "RNM(");
	uiStrBufCat(vpBuf, cpName);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpUdt(void* vpBuf, char* cpName){
	uiStrBufCat(vpBuf, "UDT(");
	uiStrBufCat(vpBuf, cpName);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpAlt(void* vpBuf, apg_uint uiChildren){
	char caBuf[1024];
	sprintf(caBuf, "%lu", (unsigned long int)uiChildren);
	uiStrBufCat(vpBuf, "ALT(");
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpCat(void* vpBuf, apg_uint uiChildren){
	char caBuf[1024];
	sprintf(caBuf, "%lu", (unsigned long int)uiChildren);
	uiStrBufCat(vpBuf, "CAT(");
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpAnd(void* vpBuf){
	uiStrBufCat(vpBuf, "AND");
}
static void vTraceOpNot(void* vpBuf){
	uiStrBufCat(vpBuf, "NOT");
}
static void vTraceOpRep(void* vpBuf, apg_uint uiMin, apg_uint uiMax){
	char caBuf[1024];
	sprintf(caBuf, "%lu", (unsigned long int)uiMin);
	uiStrBufCat(vpBuf, "REP(");
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ", ");
	if(uiMax == APG_UNDEFINED){
		uiStrBufCat(vpBuf, "inf");
	} else{
		sprintf(caBuf, "%lu", (unsigned long int)uiMax);
		uiStrBufCat(vpBuf, caBuf);
	}
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpTrg(void* vpBuf, apg_achar acMin, apg_achar acMax){
	char caBuf[1024];
	uiStrBufCat(vpBuf, "TRG(");
	sprintf(caBuf, "%lu", (unsigned long int)acMin);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ", ");
	sprintf(caBuf, "%lu", (unsigned long int)acMax);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpTbs(void* vpBuf, apg_achar* acpString, apg_uint uiLen){
	char caBuf[1024];
	uiStrBufCat(vpBuf, "TBS(");
	sprintf(caBuf, "%lu", (unsigned long int)uiLen);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ": ");
	uiACharToString(caBuf, sizeof(caBuf), acpString, uiLen);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ")");
}
static void vTraceOpTls(void* vpBuf, apg_achar* acpString, apg_uint uiLen){
	char caBuf[1024];
	uiStrBufCat(vpBuf, "TLS(");
	sprintf(caBuf, "%lu", (unsigned long int)uiLen);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ": ");
	uiACharToString(caBuf, sizeof(caBuf), acpString, uiLen);
	uiStrBufCat(vpBuf, caBuf);
	uiStrBufCat(vpBuf, ")");
}

#endif // _APG_CFG_TRACE
