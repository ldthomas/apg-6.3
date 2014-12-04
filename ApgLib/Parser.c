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
/** \file Parser.c \brief The Parser component API. This is the heart of an APG parser. */

#include "Apg.h"
#include "Grammar.h"
#include "Private.h"

// error reporting and handling
#undef PASSERT

/** Used exclusively for terminal error detection and handling.

It is highly recommended that the user write his own alert handler and
install it at parser construction time. The default alert handler
simply exits.
@see vpParserCtor() */
#define PASSERT(cond) if(!(cond)){spCtx->pfnAlertHandler(__LINE__, __FILE__);}

// static declarations
static apg_uint uiConvertRules(APG_PARSER_CTX* spCtx, G_RULE* spGRules, apg_uint uiCount);
static apg_uint uiConvertUdts(APG_PARSER_CTX* spCtx, G_UDT* spGUddts, apg_uint uiCount);
static apg_uint uiConvertOpcodes(APG_PARSER_CTX* spCtx, G_OPCODE* spGOpcodes, apg_uint uiCount);
static apg_uint uiRunStartRule(APG_PARSER_CTX* spCtx, apg_uint uiStartRule);
static apg_uint uiValidate(APG_PARSER_CTX* spCtx);

//////////////////////////////////////////////////////////////////////////
// PARSER COMPONENT FUNCTIONS
//////////////////////////////////////////////////////////////////////////
/** Construct a new APG parser component.
@param vpParserInit the initialization data from APG
@param pfnAlertHandler the alert handler, called on terminal errors. NULL for default alert handler.
@see vParserDtor()
@return pointer to a parser component context.
*/
 void* vpParserCtor(void* vpParserInit ,
                     PFN_ALERT pfnAlertHandler
                     ){
	void*			vpReturn = NULL;
	void*			vpMemCtx = NULL;
	APG_PARSER_CTX*	spCtx = NULL;
	G_HDR*			spHdr = (G_HDR*)vpParserInit;
	apg_uint		i, uiTest;
	G_UINT*			g_uipData;
	char*			cpVersion;
	G_RULE*			spGRules;
	G_UDT*			spGUdts;
	G_OPCODE*		spGOpcodes;

	// set the alert handler - handles all terminal errors
	if(pfnAlertHandler == NULL){pfnAlertHandler = vDefaultAlertHandler;}
	if(!spHdr){pfnAlertHandler(__LINE__, __FILE__);}

	// get the memory context
	vpMemCtx = vpMemCtor();
	if(!vpMemCtx){pfnAlertHandler(__LINE__, __FILE__);}

	// validate the alphabet character width
	uiTest = sizeof(apg_achar);
	if(!(uiTest >= spHdr->uiMinSizeofACharMax)){pfnAlertHandler(__LINE__, __FILE__);}

	// validate the integer width
	uiTest = sizeof(apg_uint);
	if(!(uiTest >= spHdr->uiMinSizeofUintMax)){pfnAlertHandler(__LINE__, __FILE__);}

	// validate the version
	cpVersion = (char*)vpMemAlloc(vpMemCtx, sizeof(char) * spHdr->uiVersionLen);
	if(!cpVersion){pfnAlertHandler(__LINE__, __FILE__);}
	g_uipData = (G_UINT*)spHdr;
	g_uipData += spHdr->uiVersionOffset;
	for(i = 0; i < spHdr->uiVersionLen; i++){cpVersion[i] = (char)g_uipData[i];}
	uiTest = (apg_uint)strcmp(cpVersion, cpApgVersion());
	vMemFree(vpMemCtx, (void*)cpVersion);
	if(!(uiTest == 0)){pfnAlertHandler(__LINE__, __FILE__);}

	// allocate a context
	spCtx = (APG_PARSER_CTX*)vpMemAlloc(vpMemCtx, (apg_uint)sizeof(APG_PARSER_CTX));
	if(!spCtx){pfnAlertHandler(__LINE__, __FILE__);}
	memset((void*)spCtx, 0, sizeof(APG_PARSER_CTX));
	spCtx->vpMemCtx = vpMemCtx;
	spCtx->vpValidate = (void*)spCtx;
	spCtx->pfnAlertHandler = pfnAlertHandler;

	// string table
	spCtx->cpCharTable = (char*)vpMemAlloc(spCtx->vpMemCtx, sizeof(char) * spHdr->uiCharTableLen);
	PASSERT(spCtx->cpCharTable);
	g_uipData = (G_UINT*)spHdr;
	g_uipData += spHdr->uiCharTableOffset;
	for(i = 0; i < spHdr->uiCharTableLen; i++){
	  spCtx->cpCharTable[i] = (char)g_uipData[i];
	}

	// achar table
	spCtx->acpACharTable = (apg_achar*)vpMemAlloc(spCtx->vpMemCtx, sizeof(apg_achar) * spHdr->uiACharTableLen);
	PASSERT(spCtx->acpACharTable);
	g_uipData = (G_UINT*)spHdr;
	g_uipData += spHdr->uiACharTableOffset;
	for(i = 0; i < spHdr->uiACharTableLen; i++){
	  spCtx->acpACharTable[i] = (apg_achar)g_uipData[i];
	}

	// ALT/CAT child list
	spCtx->uipChildList = (apg_uint*)vpMemAlloc(spCtx->vpMemCtx, sizeof(apg_uint) * spHdr->uiChildListLen);
	PASSERT(spCtx->uipChildList);
	g_uipData = (G_UINT*)spHdr;
	g_uipData += spHdr->uiChildListOffset;
	for(i = 0; i < spHdr->uiChildListLen; i++){
	  spCtx->uipChildList[i] = (apg_uint)g_uipData[i];
	}

	// allocate opcodes
	spCtx->spOpcodes = (APG_OPCODE*)vpMemAlloc(spCtx->vpMemCtx, sizeof(APG_OPCODE) * spHdr->uiOpcodesLen);
	PASSERT(spCtx->spOpcodes);

	// convert rules
	spCtx->spRules = (APG_RULE*)vpMemAlloc(spCtx->vpMemCtx, sizeof(APG_RULE) * spHdr->uiRulesLen);
	PASSERT(spCtx->spRules);
	spCtx->uiRuleCount = spHdr->uiRulesLen;
	spGRules = (G_RULE*)((G_UINT*)spHdr + spHdr->uiRulesOffset);
	uiTest = uiConvertRules(spCtx, spGRules, spHdr->uiRulesLen);
	PASSERT(uiTest);

	// convert UDTs
	spCtx->spUdts = (APG_UDT*)vpMemAlloc(spCtx->vpMemCtx, sizeof(APG_UDT) * spHdr->uiUdtsLen);
	PASSERT(spCtx->spUdts);
	spCtx->uiUdtCount = spHdr->uiUdtsLen;
	spGUdts = (G_UDT*)((G_UINT*)spHdr + spHdr->uiUdtsOffset);
	uiTest = uiConvertUdts(spCtx, spGUdts, spHdr->uiUdtsLen);
	if(!spCtx->uiUdtCount){spCtx->uiHaveAllUdtCallbacks = APG_TRUE;}
	PASSERT(uiTest);

	// convert opcodes
	spGOpcodes = (G_OPCODE*)((G_UINT*)spHdr + spHdr->uiOpcodesOffset);
	uiTest = uiConvertOpcodes(spCtx, spGOpcodes, spHdr->uiOpcodesLen);
	PASSERT(uiTest);

	// success
	vpReturn = (void*)spCtx;
	return vpReturn;
}

/** Parser component destructor
@param vpCtx pointer to parser component context (returned from vpParserCtor())
@see vpParserCtor()
*/
void vParserDtor(void* vpCtx){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	if(uiValidate(spCtx)){
		void* vpMemCtx = spCtx->vpMemCtx;
		memset((void*)spCtx, 0, sizeof(APG_PARSER_CTX));
		vMemDtor(vpMemCtx);
	}
}

/** Defined the syntax callback functions to the parser.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param spRuleCallbacks an array of pointers to the rule callback functions. May be NULL.
@param spUdtCallbacks an array of pointers to the UDT callback functions, if any. May be NULL if the grammar defines no UDTs.
Each UDT defined in the grammar <i>must</i> have a callback function defined here. Otherwise, this function
will return false and the parser syntax analysis will fail.
@see vpParserCtor()
@see uiParserSyntaxAnalysis()
@return true if all UDTs defined in the grammar have a callback function defined here. false otherwise.
*/
apg_uint uiParserSyntaxInitCallbacks(void* vpCtx, APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	apg_uint uiIndex;
	APG_RULE* spRules = (APG_RULE*)spCtx->spRules;
	APG_UDT* spUdts = (APG_UDT*)spCtx->spUdts;
	PASSERT(uiValidate(spCtx));
	if(spRuleCallbacks){
		for(uiIndex = 0; uiIndex < spCtx->uiRuleCount; ++uiIndex){spRules[uiIndex].pfnCBSyntax = spRuleCallbacks[uiIndex];}
	} else{
		for(uiIndex = 0; uiIndex < spCtx->uiRuleCount; ++uiIndex){spRules[uiIndex].pfnCBSyntax = NULL;}
	}
	spCtx->uiHaveAllUdtCallbacks = APG_TRUE;
	if(spCtx->uiUdtCount){
		if(spUdtCallbacks){
			for(uiIndex = 0; uiIndex < spCtx->uiUdtCount; ++uiIndex){
				if(!spUdtCallbacks[uiIndex]){spCtx->uiHaveAllUdtCallbacks = APG_FALSE;}
				spUdts[uiIndex].pfnCBSyntax = spUdtCallbacks[uiIndex];
			}
		} else{spCtx->uiHaveAllUdtCallbacks = APG_FALSE;}
	}
	return spCtx->uiHaveAllUdtCallbacks;
}

/** Parses an input string of alphabet characters.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiStartRule index of the grammar rule to be used as the start rule.
0 will always be the index of the first rule defined by the grammar.
Good usage practice is to always use an index defined in the ProjectName.h header file generated by apg, the parser generator.
This will be a #define of the form "RULE_PROJECTNAME_RULENAME".
@param acpSrc pointer to the array of alphabet character codes defining the string to be parsed.
@param uiSrcLen the number of alphabet characters in the input string.
@param vpData optional pointer to user-defined data. This pointer, which may be NULL, will be passed on to the user-defined callback functions.
It will be the vpUserData member of the APG_CBDATA structs passed to the callback functions.
It is otherwise ignored by the parser.
@see vpParserCtor()
@see uiParserState()
@see APG_CALLBACK
@see APG_CBDATA
@return true if the parser accepted <b>all</b> characters in the input string. false otherwise.
It is the same as the uiSuccess variable in the APG_PARSER_STATE struct.
*/
apg_uint uiParserSyntaxAnalysis(void* vpCtx, apg_uint uiStartRule, const apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData)
{
  apg_uint           uiReturn = APG_FALSE;
  apg_uint           uiState = PRE_PARSE;
  apg_uint           uiPhraseLength;
  APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
  PASSERT(acpSrc);
  PASSERT(uiStartRule < spCtx->uiRuleCount);
  PASSERT(spCtx->uiHaveAllUdtCallbacks);

  // set up for this parse
  spCtx->acpInputString = acpSrc;
  spCtx->uiInputStringLen = uiSrcLen;
  spCtx->sCBData.vpCtx = (void*)spCtx;
  spCtx->sCBData.acpSrc = acpSrc;
  spCtx->sCBData.uiSrcLen = uiSrcLen;
  spCtx->sCBData.vpUserData = vpData;
  memset((void*)&spCtx->sState, 0, sizeof(spCtx->sState));

  vAstClear(spCtx);
  APG_TRACE(spCtx, NULL, TRACE_ACTION_BEGIN, P_RNM, 0, 0);

  // run the start rule
  spCtx->uiStartRule = uiStartRule;
  uiPhraseLength = uiRunStartRule(spCtx, uiStartRule);
  if(uiPhraseLength == APG_UNDEFINED){uiState = NOMATCH;}
  else if(uiPhraseLength == 0){uiState = EMPTY;}
  else{uiState = MATCH;}

  // return the parser state
  spCtx->sState.uiStringLength = spCtx->uiInputStringLen;
  spCtx->sState.uiState = uiState;
  spCtx->sState.uiPhraseLength = (uiPhraseLength == APG_UNDEFINED) ? 0: uiPhraseLength;
  spCtx->sState.uiSuccess = ((uiState != NOMATCH) && (spCtx->sState.uiPhraseLength == spCtx->uiInputStringLen)) ? APG_TRUE: APG_FALSE;

  APG_TRACE(spCtx, NULL, TRACE_ACTION_END, P_RNM, 0, (spCtx->sState.uiSuccess)?spCtx->uiInputStringLen:APG_UNDEFINED);

  // success
  uiReturn = spCtx->sState.uiSuccess;
  return uiReturn;
}

/** Defines which rule/UDT names are to be kept as nodes in the Abstract Syntax Tree (AST).

Note that defining the nodes to be kept is a separate issue from defining which nodes have callback functions.
The AST nodes may or may not be used for translation.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uipRules pointer to an array of integers defining the rule indexes of the rule name nodes to be kept in the AST. May be NULL.
@param uipUdts pointer to an array of integers defining the UDT indexes of the UDT nodes to be kept in the AST. May be NULL.
@see vpParserCtor()
@see uiParserAstTranslate()
@see uiAstToXml()
*/
// defines AST nodes
void vParserAstInitNodes(void* vpCtx, apg_uint* uipRules, apg_uint* uipUdts){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	APG_AST_CTX* spAstCtx;
	apg_uint i;
	PASSERT(uiValidate(spCtx));
	vAstDtor(spCtx);
	vAstCtor(spCtx);
	spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	if(uipRules){
		for(i = 0; i < spCtx->uiRuleCount; i++){spAstCtx->uipNodes[i] = uipRules[i];}
	} else{
		for(i = 0; i < spCtx->uiRuleCount; i++){spAstCtx->uipNodes[i] = APG_FALSE;}
	}
	if(spCtx->uiUdtCount){
		if(uipUdts){
			for(i = 0; i < spCtx->uiUdtCount; i++){spAstCtx->uipNodes[i + spCtx->uiRuleCount] = uipUdts[i];}
		} else{
			for(i = 0; i < spCtx->uiUdtCount; i++){spAstCtx->uipNodes[i + spCtx->uiRuleCount] = APG_FALSE;}
		}
	}
}

// defines AST callbacks
// node records will be generated for non-NULL callbacks whether the nodes are defined true/false or not
/** Defines which rule/UDT nodes are to be assigned callback functions in the AST.

These functions need only be assigned if translation with the function uiParserAstTranslate() is to be used.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param pfnRuleCallbacks pointer to an array of rule name callback function pointers. May be NULL.
@param pfnUdtCallbacks pointer to an array of UDT callback function pointers. May be NULL.
@see vpParserCtor()
@see uiParserAstTranslate()
*/
void vParserAstInitCallbacks(void* vpCtx, APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	APG_AST_CTX* spAstCtx;
	apg_uint i;
	PASSERT(uiValidate(spCtx));
	vAstDtor(spCtx);
	vAstCtor(spCtx);
	spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	APG_CALLBACK pfnTemp;
	if(pfnRuleCallbacks){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			if(pfnRuleCallbacks[i]){spAstCtx->pfnCallbacks[i] = pfnRuleCallbacks[i];}
			else{spAstCtx->pfnCallbacks[i] = NULL;}
			pfnTemp = spAstCtx->pfnCallbacks[i];
		}
	}
	if(spCtx->uiUdtCount && pfnUdtCallbacks){
		for(i = 0; i < spCtx->uiUdtCount; i++){
			if(pfnUdtCallbacks[i]){spAstCtx->pfnCallbacks[i + spCtx->uiRuleCount] = pfnUdtCallbacks[i];}
			else{spAstCtx->pfnCallbacks[i + spCtx->uiRuleCount] = NULL;}
			pfnTemp = spAstCtx->pfnCallbacks[i + spCtx->uiRuleCount];
		}
	}
}

//	void vParserAstTraslation(void* vpCtx, void* vpData);
/** Translates an AST.

Translation is done via user-written callback functions assigned to the AST nodes.
The callback functions may be defined with a previous call to vParserAstInitCallbacks() or may be assigned/overridden here.
A "depth first" traversal of the AST is done. The callback function defined for each node is called twice.
Once on the downward traversal (PRE_AST) of the node and again later on the upward traversal (POST_AST) of the node.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param pfnRuleCallbacks pointer to an array of rule name callback function pointers. May be NULL.
Will override any functions previously assigned in a call to vParserAstInitCallbacks().
@param pfnUdtCallbacks pointer to an array of UDT callback function pointers. May be NULL.
Will override any functions previously assigned in a call to vParserAstInitCallbacks().
@param vpData user-defined data to be passed to the callback functions. May be NULL. Ignored by Parser.
@see vpParserCtor()
@see vParserAstInitCallbacks()
@see PRE_AST
@see POST_AST
@return the number of callback functions defined for which no AST node records have been collected.
If non-zero, this is a warning user may want to re-define some of the callback functions
*/
apg_uint	uiParserAstTranslate(void* vpCtx, APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, void* vpData){
	apg_uint uiRet = 0;
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	if(spCtx->vpAstCtx){
		spCtx->sCBData.vpUserData = vpData;
		uiRet = uiAstTraverse((APG_AST_CTX*)spCtx->vpAstCtx, pfnRuleCallbacks, pfnUdtCallbacks, &spCtx->sCBData);
	}
	return uiRet;
}

/** Returns the parser state. Only meaningful after a call to uiParserSyntaxAnalysis().
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param spState pointer to a user-supplied APG_PARSER_STATE struct.
@see vpParserCtor()
@see uiParserSyntaxAnalysis()
@return true if the parser state uiSuccess is true. false otherwise.
*/
apg_uint	uiParserState(void* vpCtx, APG_PARSER_STATE* spState){
	apg_uint uiRet = APG_FALSE;
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	if(spState){
        *spState = spCtx->sState;
        uiRet = spState->uiSuccess;
	}
	return uiRet;
}

/** Enables/disables collection of parser statistics.

Statistics gathering will negatively affect the parser's performance.
Therefore, statistics gathering is disabled by default.

Note: a call to this function will have no affect unless _APG_CFG_STATS is defined.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiEnable true if statistics gathering is to be enabled, false to disable (default.)
@see vpParserCtor()
@see uiParserStatsGet()
@see _APG_CFG_STATS in the configuration of Apg.h.
@return true if _APG_CFG_STATS has been defined in Apg.h, false otherwise.
*/
apg_uint uiParserStatsEnable(void* vpCtx, apg_uint uiEnable){
	apg_uint uiRet = APG_FALSE;
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	if(uiEnable){APG_STATS_ADMIN(spCtx, STATS_ACTION_ENABLE, NULL, 0, &uiRet);}
	else{APG_STATS_ADMIN(spCtx, STATS_ACTION_DISABLE, NULL, 0, &uiRet);}
	return uiRet;
}

/** Retrieve the statistics collected by uiParserSyntaxAnalysis().
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param spStats pointer to a user-supplied statistics data buffer. If NULL, only the required buffer size is returned.
@param uipBufferSize pointer to the variable to receive the required buffer size.
@see vpParserCtor()
@see uiParserStatsEnable()
@see vDisplayOperatorStats()
@see vDisplayRuleStats()
@return true if _APG_CFG_STATS has been defined in Apg.h, false otherwise.
*/
apg_uint uiParserStatsGet(void* vpCtx, APG_PARSER_STATS* spStats, apg_uint* uipBufferSize){
	apg_uint uiRet = APG_FALSE;
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	APG_STATS_ADMIN(spCtx, STATS_ACTION_GETSTATS, (void*)spStats, uipBufferSize, &uiRet);
	return uiRet;
}

/** Enables/disables tracing.

Tracing will negatively affect the parser's performance.
Therefore, tracing is disabled by default.

If tracing is enabled, trace records will be printed to the standard output as
the parser traverses the syntax tree. By default, records are printed only for
rule and UDT nodes (RNM and UDT.) However,
prior to parsing, tracing can be configured to trace or not trace any type of node.
For tracing other than the default nodes:
@see vParserTraceOp()
@see vParserTraceRule()
@see vParserTraceUdt()
@see vParserTraceRange()

Note: a call to this function will have no affect unless _APG_CFG_TRACE is defined.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiEnable if true, enables tracing, if false, disables tracing
@see vpParserCtor()
@see uiParserStatsEnable()
@return true if _APG_CFG_TRACE has been defined in Apg.h, false otherwise.
*/
apg_uint uiParserTraceEnable(void* vpCtx, apg_uint uiEnable){
	apg_uint uiRet = APG_FALSE;
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	if(uiEnable){APG_TRACE_ADMIN(spCtx, TRACE_ACTION_ENABLE, 0, 0, &uiRet);}
	else{APG_TRACE_ADMIN(spCtx, TRACE_ACTION_DISABLE, 0, 0, &uiRet);}
	return uiRet;
}

/** Configures the types of operator nodes to trace.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiOpId should be one of the following:
<pre>
APG_TRACE_ALL - trace all operator nodes
APG_TRACE_TRG - trace the TRG nodes
APG_TRACE_TBS - trace the TBS nodes
APG_TRACE_TLS - trace the TLS nodes
APG_TRACE_AND - trace the AND nodes
APG_TRACE_NOT - trace the NOT nodes
APG_TRACE_ALT - trace the ALT nodes
APG_TRACE_CAT - trace the CAT nodes
APG_TRACE_REP - trace the REP nodes
APG_TRACE_RNM - trace the RNM nodes
APG_TRACE_UDT - trace the UDT nodes
APG_TRACE_COUNT - count the trace records only, none are printed
</pre>
@param uiEnable if true, the specified operators are printed, if false, not
@see vpParserCtor()
@see uiParserTraceEnable()
*/
void vParserTraceOp(void* vpCtx, apg_uint uiOpId, apg_uint uiEnable){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	APG_TRACE_ADMIN(spCtx, TRACE_ACTION_OP, uiOpId, uiEnable, NULL);
}

/** Configures which rule names to trace. By default all rule names are traced.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiIndex rule index of the rule name to trace
@param uiEnable if true, the specified rule name records are printed, if false, not
@see vpParserCtor()
@see uiParserTraceEnable()
*/
void vParserTraceRule(void* vpCtx, apg_uint uiIndex, apg_uint uiEnable){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	APG_TRACE_ADMIN(spCtx, TRACE_ACTION_RULE, uiIndex, uiEnable, NULL);
}

/** Configures which UDT names to trace. By default all UDT names are traced.
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiIndex UDT index of the UDT name to trace
@param uiEnable if true, the specified UDT name records are printed, if false, not
@see vpParserCtor()
@see uiParserTraceEnable()
*/
void vParserTraceUdt(void* vpCtx, apg_uint uiIndex, apg_uint uiEnable){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	APG_TRACE_ADMIN(spCtx, TRACE_ACTION_UDT, uiIndex, uiEnable, NULL);
}

/** Configures the trace record range to print.

Trace records can be voluminous. This configuration can reduce the number printed to a managable set.
In this context, it may be useful to first trace the parse with APG_TRACE_COUNT configured in vParserTraceOp().
@param vpCtx pointer to a parser context, returned by vpParserCtor().
@param uiBegin the record number of the first trace record to print
@param uiCount the number of trace records to print
@see vpParserCtor()
@see uiParserTraceEnable()
*/
void vParserTraceRange(void* vpCtx, apg_uint uiBegin, apg_uint uiCount){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)vpCtx;
	PASSERT(uiValidate(spCtx));
	APG_TRACE_ADMIN(spCtx, TRACE_ACTION_RANGE, uiBegin, uiCount, NULL);
}

/** To be called only from callback functions.
Executes the specified rule as if it were the following node in the syntax tree.
@param spData the data supplied to the callback function by the parser
@param uiId index of the rule to execute
@param uiOffset offset into the input string of the first character of the phrase to match
@see APG_CALLBACK
*/
void vExecuteRule(APG_CBDATA* spData, apg_uint uiId, apg_uint uiOffset){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)spData->vpCtx;
	APG_OPCODE sOp;
	PASSERT(uiId < spCtx->uiRuleCount);
	PASSERT(uiOffset < spData->uiSrcLen);

	// create a dummy RNM opcode
	sOp.pfnOp = uiRNM;
	sOp.sUnion.sRnm.spRule = &spCtx->spRules[uiId];
	sOp.sUnion.sRnm.spNext = sOp.sUnion.sRnm.spRule->spOp;

	// execute the start rule
	spData->uiPhraseLength = sOp.pfnOp(spCtx, &sOp, uiOffset);
}

/** To be called only from callback functions.
Executes the specified UDT as if it were the following node in the syntax tree.
@param spData the data supplied to the callback function by the parser
@param uiId index of the UDT to execute
@param uiOffset offset into the input string of the first character of the phrase to match
@see APG_CALLBACK
*/
void vExecuteUdt(APG_CBDATA* spData, apg_uint uiId, apg_uint uiOffset){
	APG_PARSER_CTX* spCtx = (APG_PARSER_CTX*)spData->vpCtx;
	APG_OPCODE sOp;
	PASSERT(uiId < spCtx->uiUdtCount);
	PASSERT(uiOffset < spData->uiSrcLen);

	// create a dummy UDT opcode
	sOp.pfnOp = uiUDT;
	sOp.sUnion.sUdt.spUdt = &spCtx->spUdts[uiId];
	sOp.sUnion.sUdt.uiEmpty = spCtx->spUdts[uiId].uiEmpty;

	// execute the start rule
	spData->uiPhraseLength = sOp.pfnOp(spCtx, &sOp, uiOffset);
}

//////////////////////////////////////////////////////////////////////////
// STATIC HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////
static apg_uint uiConvertRules(APG_PARSER_CTX* spCtx, G_RULE* spGRules, apg_uint uiCount){
	apg_uint uiReturn = APG_FALSE;
	G_RULE* spGRule = spGRules;
	APG_RULE* spRule = spCtx->spRules;
	APG_RULE* spRuleEnd = spRule + uiCount;
	apg_uint uiIndex = 0;
	for(; spRule < spRuleEnd; spRule++, spGRule++, uiIndex++){
		spRule->cpRuleName = spCtx->cpCharTable + spGRule->uiNameOffset;
		spRule->pfnCBSyntax = NULL;
		spRule->spOp = spCtx->spOpcodes + spGRule->uiChildOffset;
		spRule->uiOpcodeCount = (apg_uint)spGRule->uiChildCount;
		spRule->uiRuleIndex = uiIndex;
	}
	uiReturn = APG_TRUE;
	return uiReturn;
}

static apg_uint uiConvertUdts(APG_PARSER_CTX* spCtx, G_UDT* spGUdts, apg_uint uiCount){
	apg_uint uiReturn = APG_FALSE;
	G_UDT* spGUdt = spGUdts;
	APG_UDT* spUdt = spCtx->spUdts;
	APG_UDT* spUdtEnd = spUdt + uiCount;
	apg_uint uiIndex = 0;
	for(; spUdt < spUdtEnd; spUdt++, spGUdt++, uiIndex++){
		spUdt->cpUdtName = spCtx->cpCharTable + spGUdt->uiNameOffset;
		spUdt->pfnCBSyntax = NULL;
		spUdt->uiEmpty = (apg_uint)spGUdt->uiEmpty;
		spUdt->uiUdtIndex = uiIndex;
	}
	uiReturn = APG_TRUE;
	return uiReturn;
}

static apg_uint uiConvertOpcodes(APG_PARSER_CTX* spCtx, G_OPCODE* spGOpcodes, apg_uint uiCount){
	apg_uint uiReturn = APG_FALSE;
	G_OPCODE* spGOp = spGOpcodes;
	APG_OPCODE* spOp = spCtx->spOpcodes;
	APG_OPCODE* spOpEnd = spCtx->spOpcodes + uiCount;
	for(; spOp < spOpEnd; spOp++, spGOp++){
//		switch(spGOp->sOpType.sRnm.uiType){
		switch(spGOp->uiType){
		case G_TYPE_RNM:
		{
			G_RNMOP* spG = &spGOp->sOpType.sRnm;
			APG_OP_RNM* spP = &spOp->sUnion.sRnm;
			spOp->pfnOp = uiRNM;
			spP->spRule = spCtx->spRules + spG->uiRuleIndex;
			spP->spNext = spP->spRule->spOp;
			spOp->cpName = "G_TYPE_RNM";
		}
			break;
		case G_TYPE_UDT:
		{
			G_UDTOP* spG = &spGOp->sOpType.sUdt;
			APG_OP_UDT* spP = &spOp->sUnion.sUdt;
			spOp->pfnOp = uiUDT;
			spP->spUdt = spCtx->spUdts + spG->uiUdtIndex;
			spP->uiEmpty = (apg_uint)spG->uiEmpty;

			spOp->cpName = "G_TYPE_UDT";
		}
			break;
		case G_TYPE_REP:
		{
			G_REPOP* spG = &spGOp->sOpType.sRep;
			APG_OP_REP* spP = &spOp->sUnion.sRep;
			spOp->pfnOp = uiREP;
			spP->spNext = spCtx->spOpcodes + spG->uiChildOffset;
			spP->uiMin = (apg_uint)spG->uiMin;
			spP->uiMax = (apg_uint)spG->uiMax;
			spOp->cpName = "G_TYPE_REP";
		}
			break;
		case G_TYPE_ALT:
		{
			G_ALTOP* spG = &spGOp->sOpType.sAlt;
			APG_OP_ALT* spP = &spOp->sUnion.sAlt;
			spOp->pfnOp = uiALT;
			spP->uipChildList = (apg_uint*)(spCtx->uipChildList + spG->uiChildListOffset);
			spP->uiChildCount = (apg_uint)spG->uiChildCount;
			spOp->cpName = "G_TYPE_ALT";
		}
			break;
		case G_TYPE_CAT:
		{
			G_CATOP* spG = &spGOp->sOpType.sCat;
			APG_OP_CAT* spP = &spOp->sUnion.sCat;
			spOp->pfnOp = uiCAT;
			spP->uipChildList = (apg_uint*)(spCtx->uipChildList + spG->uiChildListOffset);
			spP->uiChildCount = (apg_uint)spG->uiChildCount;
			spOp->cpName = "G_TYPE_CAT";
		}
			break;
		case G_TYPE_AND:
		{
			G_ANDOP* spG = &spGOp->sOpType.sAnd;
			APG_OP_AND* spP = &spOp->sUnion.sAnd;
			spOp->pfnOp = uiAND;
			spP->spNext = spCtx->spOpcodes + spG->uiChildOffset;
			spOp->cpName = "G_TYPE_AND";
		}
			break;
		case G_TYPE_NOT:
		{
			G_NOTOP* spG = &spGOp->sOpType.sNot;
			APG_OP_NOT* spP = &spOp->sUnion.sNot;
			spOp->pfnOp = uiNOT;
			spP->spNext = spCtx->spOpcodes + spG->uiChildOffset;
			spOp->cpName = "G_TYPE_NOT";
		}
			break;
		case G_TYPE_TRG:
		{
			G_TRGOP* spG = &spGOp->sOpType.sTrg;
			APG_OP_TRG* spP = &spOp->sUnion.sTrg;
			spOp->pfnOp = uiTRG;
			spP->acMin = (apg_achar)spG->uiMin;
			spP->acMax = (apg_achar)spG->uiMax;
			spOp->cpName = "G_TYPE_TRG";
		}
			break;
		case G_TYPE_TBS:
		{
			G_TBSOP* spG = &spGOp->sOpType.sTbs;
			APG_OP_TBS* spP = &spOp->sUnion.sTbs;
			spOp->pfnOp = uiTBS;
			spP->acpStrTbl= spCtx->acpACharTable + spG->uiOffset;
			spP->uiStrLen = (apg_uint)spG->uiLen;
			spOp->cpName = "G_TYPE_TBS";
		}
			break;
		case G_TYPE_TLS:
		{
			apg_achar* acpBeg;
			apg_achar* acpEnd;
			G_TLSOP* spG = &spGOp->sOpType.sTls;
			APG_OP_TLS* spP = &spOp->sUnion.sTls;
			spOp->pfnOp = uiTLS;
			spP->acpStrTbl = spCtx->acpACharTable + spG->uiOffset;
			spP->uiStrLen = spG->uiLen;
			acpBeg = spP->acpStrTbl;
			acpEnd = acpBeg + spP->uiStrLen;
			for(; acpBeg < acpEnd; acpBeg++){ // convert string to lower
				if(*acpBeg >= (apg_achar)65 && *acpBeg <= (apg_achar)90){*acpBeg += (apg_achar)32;}
			}
			spOp->cpName = "G_TYPE_TLS";
		}
			break;
		default:
			PASSERT(APG_FALSE);
			break;
		}
	}
	uiReturn = APG_TRUE;
	return uiReturn;
}

static apg_uint uiRunStartRule(APG_PARSER_CTX* spCtx, apg_uint uiStartRule){
	apg_uint uiRet;
  APG_OPCODE sOp;
  PASSERT(uiStartRule < spCtx->uiRuleCount);
  PASSERT(spCtx);

  // create a dummy RNM opcode
  sOp.pfnOp = uiRNM;
  sOp.sUnion.sRnm.spRule = &spCtx->spRules[uiStartRule];
  sOp.sUnion.sRnm.spNext = sOp.sUnion.sRnm.spRule->spOp;

  // execute the start rule
  uiRet = sOp.pfnOp(spCtx, &sOp, 0);
  return uiRet;
}

static apg_uint uiValidate(APG_PARSER_CTX* spCtx){
	return (spCtx && spCtx->vpValidate == (void*)spCtx);
}
