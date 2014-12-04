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
#include "Private.h"

#define AASSERT(cond) if(!(cond)){spCtx->spParserCtx->pfnAlertHandler(__LINE__, __FILE__);}

void	vAstCtor(APG_PARSER_CTX* spParserCtx){
	if(!spParserCtx->vpAstCtx){
		apg_uint uiMaxRecords = 20 * (spParserCtx->uiRuleCount + spParserCtx->uiUdtCount);
		apg_uint uiSize, uiNodeCount, i;

		// context
		APG_AST_CTX* spCtx = (APG_AST_CTX*)vpMemAlloc(spParserCtx->vpMemCtx, sizeof(APG_AST_CTX));
		if(!spCtx){spParserCtx->pfnAlertHandler(__LINE__, __FILE__);}
		memset((void*)spCtx, 0, sizeof(APG_AST_CTX));

		// AST nodes
		uiNodeCount = spParserCtx->uiRuleCount +spParserCtx->uiUdtCount;
		uiSize = sizeof(apg_uint) * uiNodeCount;
		spCtx->uipNodes = (apg_uint*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
		AASSERT(spCtx->uipNodes);
		memset((void*)spCtx->uipNodes, 0, uiSize);

		// AST callbacks
		uiSize = uiNodeCount * sizeof(APG_CALLBACK);
		spCtx->pfnCallbacks = (APG_CALLBACK*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
		AASSERT(spCtx->pfnCallbacks);
		memset((void*)spCtx->pfnCallbacks, 0, uiSize);

		// AST records
		uiSize = sizeof(APG_AST_RECORD) * uiMaxRecords;
		spCtx->spRecords = (APG_AST_RECORD*)vpMemAlloc(spParserCtx->vpMemCtx, uiSize);
		AASSERT(spCtx->spRecords);
		memset((void*)spCtx->spRecords, 0, uiSize);
		spCtx->uiRecordEnd = uiMaxRecords;
		spCtx->uiRecordCount = 0;

		// default disables all nodes
		for(i = 0; i < spCtx->uiNodeCount; i++){
			spCtx->uipNodes[i] = APG_FALSE;
			spCtx->pfnCallbacks[i] = NULL;
		}

		// admin data
		spCtx->vpMemCtx = spParserCtx->vpMemCtx;
		spCtx->uiNodeCount = uiNodeCount;
		spCtx->uiRuleCount = spParserCtx->uiRuleCount;
		spCtx->uiUdtCount = spParserCtx->uiUdtCount;

		// success
		spParserCtx->vpAstCtx = (void*)spCtx;
	}
	vAstClear(spParserCtx);
}

void	vAstDtor(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpAstCtx){
		APG_AST_CTX* spCtx = (APG_AST_CTX*)spParserCtx->vpAstCtx;
		vMemFree(spParserCtx->vpMemCtx, (void*)spCtx->spRecords);
		vMemFree(spParserCtx->vpMemCtx, (void*)spCtx->uipNodes);
		vMemFree(spParserCtx->vpMemCtx, (void*)spCtx->pfnCallbacks);
		memset((void*)spCtx, 0, sizeof(APG_AST_CTX));
		vMemFree(spParserCtx->vpMemCtx, (void*)spCtx);
		spParserCtx->vpAstCtx = NULL;
	}
}

void	vAstClear(APG_PARSER_CTX* spParserCtx){
	if(spParserCtx->vpAstCtx){
		APG_AST_CTX* spCtx = (APG_AST_CTX*)spParserCtx->vpAstCtx;
		spCtx->uiRecordCount = 0;
		spCtx->uiIgnoreRecords = 0;
	}
}

//#include <stdio.h>
// traverses the AST nodes for which records have been previously defined by uiParserSyntaxAnalysis();
// calls any callback functions which may have been assigned to the nodes
// pfnRuleCallbacks - an array of override rule callback functions
//                  - array must be of at lease RuleCount in length
//                  - array members must be NULL or point to a valid callback function
//                  - may be NULL which would be the same as providing an all-NULL array
// pfnUdtCallbacks  - ditto for UDT override callback functions
// return - the number of callback functions defined for which no AST node records have been collected
//        - if non-zero, this is a warning user may want to re-define some of the callback functions
apg_uint uiAstTraverse(APG_AST_CTX* spCtx, APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, APG_CBDATA* spData){
	apg_uint uiRet = 0;
	APG_AST_RECORD* spRecord = spCtx->spRecords;
	APG_AST_RECORD* spRecordEnd = spRecord + spCtx->uiRecordCount;
	APG_CALLBACK pfnaCallbacks[spCtx->uiNodeCount];
	apg_uint i;

	for(i = 0; i < spCtx->uiNodeCount; i++){pfnaCallbacks[i] = NULL;}
	if(pfnRuleCallbacks){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			pfnaCallbacks[i] = pfnRuleCallbacks[i]; // override all rule callbacks
			if(pfnRuleCallbacks[i] && !spCtx->pfnCallbacks[i]){uiRet++;}
		}
	} else{
		for(i = 0; i < spCtx->uiRuleCount; i++){
			pfnaCallbacks[i] = spCtx->pfnCallbacks[i]; // use previously defined rule callbacks
		}
	}
	if(spCtx->uiUdtCount){
		if(pfnUdtCallbacks){
			for(i = 0; i < spCtx->uiUdtCount; i++){
				pfnaCallbacks[i + spCtx->uiRuleCount] = pfnUdtCallbacks[i]; // override all UDT callbacks
				if(pfnRuleCallbacks[i + spCtx->uiRuleCount] && !spCtx->pfnCallbacks[i + spCtx->uiRuleCount]){uiRet++;}
			}
		} else{
			for(i = 0; i < spCtx->uiUdtCount; i++){
				pfnaCallbacks[i + spCtx->uiRuleCount] = spCtx->pfnCallbacks[i + spCtx->uiRuleCount]; // use previously defined UDT callbacks
			}
		}
	}

	for(; spRecord < spRecordEnd; spRecord++){
		if(pfnaCallbacks[spRecord->uiId]){
			spData->uiPhraseOffset = spRecord->uiPhraseOffset;
			spData->uiPhraseLength = spRecord->uiPhraseLength;
			spData->uiState = spRecord->uiState;
			if(spRecord->uiState == PRE_AST){pfnaCallbacks[spRecord->uiId](spData);}
			else if(spRecord->uiState == POST_AST){pfnaCallbacks[spRecord->uiId](spData);}
		}
	}
	return uiRet;
}

void	vAstGrow(APG_AST_CTX* spCtx){
	apg_uint uiNewRecordEnd = spCtx->uiRecordEnd * 3;
	APG_AST_RECORD* spOldRecords = spCtx->spRecords;
	APG_AST_RECORD* spNewRecords = (APG_AST_RECORD*)vpMemAlloc(spCtx->vpMemCtx, sizeof(APG_AST_RECORD) * uiNewRecordEnd);
	AASSERT(spNewRecords);
	memcpy((void*)spNewRecords, (void*)spOldRecords, sizeof(APG_AST_RECORD) * spCtx->uiRecordEnd);
	spCtx->spRecords = spNewRecords;
	spCtx->uiRecordEnd = uiNewRecordEnd;
	vMemFree(spCtx->vpMemCtx, (void*)spOldRecords);
}
