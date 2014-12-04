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
#include "Generator.h"

static G_UINT uiIsUnparsable(ATTRS* spAttrs);
static void vDisplayAttrsHeader(void);
static void vDisplayAttrsLegend(void);
static int iComp(const void* vpLeft, const void* vpRight);

G_UINT uiAttributes(void* vpCtx){
    G_UINT uiRet = APG_FALSE;
	ATTRS_CTX* spCtx = (ATTRS_CTX*)vpCtx;
	G_UINT i, uiCount;
	if(spCtx){
		// compute rule dependencies
		vRuleDependencies(spCtx);

		// non-recursive attributes (Finite & Empty)
		vNonRecursiveAttributes(spCtx);

		// recursive attributes (Left, Nested, Right & Cyclic)
		vRecursiveAttributes(spCtx);

		for(uiCount = 0,i = 0; i < spCtx->uiRuleCount; i++){
			if(uiIsUnparsable(&spCtx->spAttrs[i])){uiCount++;}
		}
		if(uiCount == 0){uiRet = APG_TRUE;}
	}
	return uiRet;
}

void* vpAttrsCtor(CALLBACK_CTX* spCtx){
	void* vpRet = NULL;
	ATTRS_CTX* spAttrsCtx;
	G_UINT uiRuleCount;
	G_UINT i;
	ATTRS* spAttrs;
	QSORT* spQsort;
	char* cpCharTable;
	void* vpMemCtx;
	while(APG_TRUE){
		vpMemCtx = vpMemCtor();
		if(!vpMemCtx){break;}
		uiRuleCount = uiVecSize(spCtx->vpVecRuleTable);
		if(!uiRuleCount){break;}
		cpCharTable = (char*)vpVecFront(spCtx->vpVecCharTable);
		if(!cpCharTable){break;}
		spAttrsCtx = (ATTRS_CTX*)vpMemAlloc(vpMemCtx, sizeof(ATTRS_CTX));
		if(!spAttrsCtx){break;}
		spQsort = (QSORT*)vpMemAlloc(vpMemCtx, sizeof(QSORT) * uiRuleCount);
		if(!spQsort){break;}
		spAttrs = (ATTRS*)vpMemAlloc(vpMemCtx, sizeof(ATTRS) * uiRuleCount);
		if(!spAttrs){break;}
		memset((void*)spAttrsCtx, 0, sizeof(ATTRS_CTX));
		memset((void*)spQsort, 0, sizeof(QSORT) * uiRuleCount);
		memset((void*)spAttrs, 0, sizeof(ATTRS) * uiRuleCount);
		spAttrsCtx->vpMemCtx = vpMemCtx;
		spAttrsCtx->spAttrs = spAttrs;
		spAttrsCtx->spQsort = spQsort;
		spAttrsCtx->uiRuleCount = uiRuleCount;
		spAttrsCtx->spRules = (G_RULE*)vpVecFront(spCtx->vpVecRuleTable);
		if(!spAttrsCtx->spRules){break;}
		spAttrsCtx->spOpcodes = (G_OPCODE*)vpVecFront(spCtx->vpVecOpcodeTable);
		if(!spAttrsCtx->spOpcodes){break;}
		spAttrsCtx->uipChildList = (G_UINT*)vpVecFront(spCtx->vpVecChildList);
		for(i = 0; i < uiRuleCount; i++){
			G_RULE* spRules = spAttrsCtx->spRules;
			spAttrsCtx->spQsort[i].cpRuleName = cpCharTable + spRules[i].uiNameOffset;
			spAttrsCtx->spQsort[i].uiRuleIndex = i;
			spAttrsCtx->spAttrs[i].cpRuleName = cpCharTable + spRules[i].uiNameOffset;
			spAttrsCtx->spAttrs[i].uipRefCount = (G_UINT*)vpMemAlloc(vpMemCtx, sizeof(G_UINT) * uiRuleCount);
			if(!spAttrsCtx->spAttrs[i].uipRefCount){break;}
			spAttrsCtx->spAttrs[i].uipIsScanned = (G_UINT*)vpMemAlloc(vpMemCtx, sizeof(G_UINT) * uiRuleCount);
			if(!spAttrsCtx->spAttrs[i].uipIsScanned){break;}
			vAttrsClear(&spAttrsCtx->spAttrs[i], uiRuleCount);
		}
		if(i != uiRuleCount){break;}

		// success
		qsort((void*)spAttrsCtx->spQsort, spAttrsCtx->uiRuleCount, sizeof(QSORT), iComp);
		vpRet = (void*)spAttrsCtx;
		break;
	}
	return vpRet;
}

void vAttrsDtor(void* vpCtx){
	ATTRS_CTX* spCtx = (ATTRS_CTX*)vpCtx;
	if(spCtx){
		void* vpMemCtx = spCtx->vpMemCtx;
		memset((void*)spCtx, 0, sizeof(*spCtx));
		vMemDtor(vpMemCtx);
	}
}

void vAttrsClear(ATTRS* spAttrs, G_UINT uiRuleCount){
	spAttrs->uiCyclic = APG_UNDEFINED;
	spAttrs->uiLeft = APG_UNDEFINED;
	spAttrs->uiRight = APG_UNDEFINED;
	spAttrs->uiNested = APG_UNDEFINED;
	spAttrs->uiFinite = APG_UNDEFINED;
	spAttrs->uiEmpty = APG_UNDEFINED;
	spAttrs->uiIsComplete = APG_FALSE;
	spAttrs->uiIsOpen = APG_FALSE;
	if(spAttrs->uipRefCount){memset((void*)spAttrs->uipRefCount, 0, sizeof(G_UINT) * uiRuleCount);}
	if(spAttrs->uipIsScanned){memset((void*)spAttrs->uipIsScanned, 0, sizeof(G_UINT) * uiRuleCount);}
// leave as is
//	spAttrs->uiRecursiveType;
//	spAttrs->cpRuleName = NULL;
}

void vAttrsCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs){
	spDstAttrs->uiCyclic = spSrcAttrs->uiCyclic;
	spDstAttrs->uiLeft = spSrcAttrs->uiLeft;
	spDstAttrs->uiRight = spSrcAttrs->uiRight;
	spDstAttrs->uiNested = spSrcAttrs->uiNested;
	spDstAttrs->uiFinite = spSrcAttrs->uiFinite;
	spDstAttrs->uiEmpty = spSrcAttrs->uiEmpty;
}

void vAttrsRecursiveCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs){
	spDstAttrs->uiCyclic = spSrcAttrs->uiCyclic;
	spDstAttrs->uiLeft = spSrcAttrs->uiLeft;
	spDstAttrs->uiRight = spSrcAttrs->uiRight;
	spDstAttrs->uiNested = spSrcAttrs->uiNested;
}

void vAttrsNonRecursiveCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs){
	spDstAttrs->uiFinite = spSrcAttrs->uiFinite;
	spDstAttrs->uiEmpty = spSrcAttrs->uiEmpty;
}

void vDisplayAttrs(void* vpCtx){
	ATTRS_CTX* spCtx = (ATTRS_CTX*)vpCtx;
	G_UINT i, uiIndex, uiCount;
	char* cpName;
	if(vpCtx){

		// display unparsable rules, if any, first
		for(uiCount = 0,i = 0; i < spCtx->uiRuleCount; i++){
			if(uiIsUnparsable(&spCtx->spAttrs[i])){uiCount++;}
		}
		if(uiCount){
			printf("\n// UNPARSABLE ATTRIBUTES\n");
            vDisplayAttrsLegend();
			vDisplayAttrsHeader();
			for(i = 0; i < spCtx->uiRuleCount; i++){
				uiIndex = spCtx->spQsort[i].uiRuleIndex;
				if(uiIsUnparsable(&spCtx->spAttrs[uiIndex])){
					cpName = spCtx->spQsort[i].cpRuleName;
					vDisplayAttrsLine(&spCtx->spAttrs[uiIndex], cpName);
				}
			}
		}

		// display mutually-recursive rules
		for(uiCount = 0,i = 0; i < spCtx->uiRuleCount; i++){
			if(!uiIsUnparsable(&spCtx->spAttrs[i]) && spCtx->spAttrs[i].uiRecursiveType == MR_RECURSIVE){uiCount++;}
		}
		if(uiCount){
			printf("\n// MUTUALLY-RECURSIVE ATTRIBUTES\n");
            vDisplayAttrsLegend();
			vDisplayAttrsHeader();
			for(i = 0; i < spCtx->uiRuleCount; i++){
				uiIndex = spCtx->spQsort[i].uiRuleIndex;
				if(!uiIsUnparsable(&spCtx->spAttrs[uiIndex]) && spCtx->spAttrs[uiIndex].uiRecursiveType == MR_RECURSIVE){
					cpName = spCtx->spQsort[i].cpRuleName;
					vDisplayAttrsLine(&spCtx->spAttrs[uiIndex], cpName);
				}
			}
		}

		// display recursive rules
		for(uiCount = 0,i = 0; i < spCtx->uiRuleCount; i++){
			if(!uiIsUnparsable(&spCtx->spAttrs[i]) &&
					(spCtx->spAttrs[i].uiRecursiveType == R_RECURSIVE ||
							spCtx->spAttrs[i].uiRecursiveType == RMR_RECURSIVE)){uiCount++;}
		}
		if(uiCount){
			printf("\n// RECURSIVE ATTRIBUTES\n");
            vDisplayAttrsLegend();
			vDisplayAttrsHeader();
			for(i = 0; i < spCtx->uiRuleCount; i++){
				uiIndex = spCtx->spQsort[i].uiRuleIndex;
				if(!uiIsUnparsable(&spCtx->spAttrs[uiIndex]) &&
						(spCtx->spAttrs[uiIndex].uiRecursiveType == R_RECURSIVE ||
								spCtx->spAttrs[uiIndex].uiRecursiveType == RMR_RECURSIVE)){
					cpName = spCtx->spQsort[i].cpRuleName;
					vDisplayAttrsLine(&spCtx->spAttrs[uiIndex], cpName);
				}
			}
		}

		// display non-recursive rules
		for(uiCount = 0,i = 0; i < spCtx->uiRuleCount; i++){
			if(!uiIsUnparsable(&spCtx->spAttrs[i]) &&
					(spCtx->spAttrs[i].uiRecursiveType == N_RECURSIVE ||
							spCtx->spAttrs[i].uiRecursiveType == NMR_RECURSIVE)){uiCount++;}
		}
		if(uiCount){
			printf("\n// NON-RECURSIVE ATTRIBUTES\n");
            vDisplayAttrsLegend();
			vDisplayAttrsHeader();
			for(i = 0; i < spCtx->uiRuleCount; i++){
				uiIndex = spCtx->spQsort[i].uiRuleIndex;
				if(!uiIsUnparsable(&spCtx->spAttrs[uiIndex]) &&
						(spCtx->spAttrs[uiIndex].uiRecursiveType == N_RECURSIVE ||
								spCtx->spAttrs[uiIndex].uiRecursiveType == NMR_RECURSIVE)){
					cpName = spCtx->spQsort[i].cpRuleName;
					vDisplayAttrsLine(&spCtx->spAttrs[uiIndex], cpName);
				}
			}
		}
	}
}

void vIndent(G_UINT uiIndent){
	G_UINT i = 0;
	for(; i < uiIndent; i++){printf(" ");}
}
void vAttrsTrace(ATTRS_CTX* spCtx, G_UINT uiWhich, G_UINT uiRuleIndex, G_OPCODE* spOpcode, ATTRS* spAttrs){
	vIndent(spCtx->uiTreeDepth);
	switch(uiWhich){
	case WHICH_OP:
	{
		char* cpType = NULL;
		switch(uiRuleIndex){
		case G_TYPE_RNM: cpType = "G_TYPE_RNM"; break;
		case G_TYPE_UDT: cpType = "G_TYPE_UDT"; break;
		case G_TYPE_REP: cpType = "G_TYPE_REP"; break;
		case G_TYPE_ALT: cpType = "G_TYPE_ALT"; break;
		case G_TYPE_CAT: cpType = "G_TYPE_CAT"; break;
		case G_TYPE_AND: cpType = "G_TYPE_AND"; break;
		case G_TYPE_NOT: cpType = "G_TYPE_NOT"; break;
		case G_TYPE_TRG: cpType = "G_TYPE_TRG"; break;
		case G_TYPE_TBS: cpType = "G_TYPE_TBS"; break;
		case G_TYPE_TLS: cpType = "G_TYPE_TLS"; break;
		}
		printf("vAttrsTrace: vOpcodeAttrs: %s\n", cpType);
	}
		break;
	case WHICH_RULE:
	{
		printf("vAttrsTrace:   vRuleAttrs: %lu: %s\n", (G_UINT)uiRuleIndex, spAttrs->cpRuleName);
	}
		break;
	case WHICH_MR_RULE:
	{
		printf("vAttrsTrace: vMRRuleAttrs: %lu: %s\n", (G_UINT)uiRuleIndex, spAttrs->cpRuleName);
	}
		break;
		break;
	default: GASSERT(APG_FALSE); break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// FRAME COMPONENT
///////////////////////////////////////////////////////////////////////////////
void* vpFrameCtor(void* vpMemCtx, G_UINT uiRuleCount, ATTRS* spAttrs){
	void* vpVecFrames = NULL;
	FRAME_CTX* spFrameCtx = NULL;
	while(APG_TRUE){
		if(!(vpMemCtx && uiRuleCount)){break;}
		spFrameCtx = (FRAME_CTX*)vpMemAlloc(vpMemCtx, sizeof(FRAME_CTX));
		if(!spFrameCtx){break;}
		memset((void*)spFrameCtx, 0, sizeof(FRAME_CTX));
		spFrameCtx->vpMemCtx = vpMemCtx;
		spFrameCtx->uiRuleCount = uiRuleCount;
		vpVecFrames = vpVecCtor(vpMemCtx, uiRuleCount * sizeof(ATTRS), 100);
		if(!vpVecFrames){break;}
		spFrameCtx->vpVecFrames = vpVecFrames;
		spFrameCtx->spAttrs = spAttrs;

		break;
	}
	if(!vpVecFrames && spFrameCtx){vMemFree(vpMemCtx, (void*)spFrameCtx);}
	return (void*)spFrameCtx;
}
void vFrameDtor(void* vpCtx){
	FRAME_CTX* spCtx = vpCtx;
	if(spCtx){
		void* vpMemCtx = spCtx->vpMemCtx;
		vVecDtor(spCtx->vpVecFrames);
		memset((void*)spCtx, 0, sizeof(FRAME_CTX));
		vMemFree(vpMemCtx, vpCtx);
	}
}
ATTRS* spFramePush(void* vpCtx){
	ATTRS* spFrame = NULL;
	FRAME_CTX* spCtx = vpCtx;
	G_UINT i;
	if(spCtx){
		spFrame = (ATTRS*)vpVecPush(spCtx->vpVecFrames, NULL);
		spCtx->uiFrameCount = uiVecSize(spCtx->vpVecFrames);
		for(i = 0; i < spCtx->uiRuleCount; i++){
			memset((void*)&spFrame[i], 0, sizeof(*spFrame));
			vAttrsClear(&spFrame[i], spCtx->uiRuleCount);
		}
	}
	return spFrame; // pointer to pushed frame, NULL on memory allocation failure
}
ATTRS* spFramePop(void* vpCtx){
	ATTRS* spFrame = NULL;
	FRAME_CTX* spCtx = vpCtx;
	if(spCtx){
		spFrame = (ATTRS*)vpVecPop(spCtx->vpVecFrames);
		spCtx->uiFrameCount = uiVecSize(spCtx->vpVecFrames);
	}
	return spFrame; // pointer to popped frame, NULL if vector is empty
}
ATTRS* spFramePeek(void* vpCtx){
	ATTRS* spFrame = NULL;
	FRAME_CTX* spCtx = vpCtx;
	if(spCtx){
		spFrame = (ATTRS*)vpVecBack(spCtx->vpVecFrames);
	}
	return spFrame; // pointer to popped frame, NULL if vector is empty
}
// find the frame previous to top frame
ATTRS* spFramePrev(void* vpCtx){
	ATTRS* spFrame = NULL;
	FRAME_CTX* spCtx = vpCtx;
	if(spCtx && spCtx->uiFrameCount > 1){ // uiFrameCount - 1 is the index of the top frame
		spFrame = (ATTRS*)vpVecAt(spCtx->vpVecFrames, spCtx->uiFrameCount - 2);
	}
	return spFrame;
}
///////////////////////////////////////////////////////////////////////////////
// STATIC HELPER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

static int iComp(const void* vpLeft, const void* vpRight){
	QSORT* spLeft = (QSORT*)vpLeft;
	QSORT* spRight = (QSORT*)vpRight;
	return apg_stricmp(spLeft->cpRuleName, spRight->cpRuleName);
}
static char* cpFmt = "%4s %6s %5s %5s %6s %6s  %s\n";
static void vDisplayAttrsHeader(void){
	printf(cpFmt, "LEFT", "NESTED", "RIGHT", "EMPTY", "FINITE", "CYCLIC", "Rule Name");
}
static void vDisplayAttrsLegend(void){
	printf("legend: %s = true, %s = false, %s = unparsable, %s = unknown\n", ATTRS_YES, ATTRS_NO, ATTRS_FATAL, ATTRS_UNKNOWN);
}

void vDisplayAttrsLine(ATTRS* spAttrs, char* cpName){
	char* l = (spAttrs->uiLeft) ? ATTRS_FATAL : ATTRS_NO;
	char* n = (spAttrs->uiNested) ? ATTRS_YES : ATTRS_NO;
	char* r = (spAttrs->uiRight) ? ATTRS_YES : ATTRS_NO;
	char* c = (spAttrs->uiCyclic) ? ATTRS_FATAL : ATTRS_NO;
	char* f;
	char* e;
	if(spAttrs->uiLeft == APG_UNDEFINED){l = ATTRS_UNKNOWN;}
	if(spAttrs->uiNested == APG_UNDEFINED){n = ATTRS_UNKNOWN;}
	if(spAttrs->uiRight == APG_UNDEFINED){r = ATTRS_UNKNOWN;}
	if(spAttrs->uiLeft == APG_UNDEFINED){c = ATTRS_UNKNOWN;}
	if(spAttrs->uiCyclic == APG_UNDEFINED){c = ATTRS_UNKNOWN;}
	if(spAttrs->uiFinite == APG_UNDEFINED){f = ATTRS_UNKNOWN; e = ATTRS_UNKNOWN;}
	else if(spAttrs->uiFinite == APG_FALSE){f = ATTRS_NO; e = ATTRS_UNKNOWN;}
	else{f = ATTRS_YES; e = (spAttrs->uiEmpty) ? ATTRS_YES : ATTRS_NO;}
	if(cpName == NULL){cpName = "<none>";}
	printf(cpFmt, l, n, r, e, f, c, cpName);
}
static G_UINT uiIsUnparsable(ATTRS* spAttrs){
	return spAttrs->uiLeft || spAttrs->uiCyclic || !spAttrs->uiFinite;
}

