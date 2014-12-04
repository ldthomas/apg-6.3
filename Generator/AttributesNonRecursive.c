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

static void vRuleAttrs(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs);
static void vMRRuleAttrs(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs);
static void vOpcodeAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vAltAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vCatAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vRepAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);

void vNonRecursiveAttributes(ATTRS_CTX* spCtx){
	ATTRS sComputedAttrs;
	ATTRS* spAttrs;
	ATTRS* spFrame;
	G_UINT uiStartIndex, uiCount;
	G_UINT uiRuleCount = spCtx->uiRuleCount;
	memset(&sComputedAttrs, 0, sizeof(ATTRS));
	spCtx->vpFrameCtx = vpFrameCtor(spCtx->vpMemCtx, uiRuleCount, spCtx->spAttrs);
	GASSERT(spCtx->vpFrameCtx);

	// initialize all rules as leaf and incomplete and closed
	for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
		spAttrs = spCtx->spAttrs + uiStartIndex;
		spAttrs->uiIsOpen = APG_FALSE;
		spAttrs->uiIsComplete = APG_FALSE;
		spAttrs->uiFinite = APG_FALSE;
		spAttrs->uiEmpty = APG_UNDEFINED;
		spAttrs->uiLeft = APG_UNDEFINED;
		spAttrs->uiNested = APG_UNDEFINED;
		spAttrs->uiRight = APG_UNDEFINED;
		spAttrs->uiCyclic = APG_UNDEFINED;
	}

	// 1. N_RECURSIVE & R_RECURSIVE
	uiCount = 0;
	spCtx->vpRuleAttrs = (void*)vRuleAttrs;
	spCtx->uiTreeDepth = 0;
	for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
		spAttrs = spCtx->spAttrs + uiStartIndex;
		if((spAttrs->uiRecursiveType == N_RECURSIVE) || (spAttrs->uiRecursiveType == R_RECURSIVE)){
			spCtx->uiStartRuleIndex = uiStartIndex;
			((PFN_OPRNM)spCtx->vpRuleAttrs)(spCtx, uiStartIndex, &sComputedAttrs);
			uiCount++;
			// !!!! DEBUG !!!!
			GASSERT(sComputedAttrs.uiIsComplete);
			GASSERT(!sComputedAttrs.uiIsOpen);
			// !!!! DEBUG !!!!
		}
	}

	// 2. MR_RECURSIVE
	uiCount = 0;
	for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
		if(spCtx->spAttrs[uiStartIndex].uiRecursiveType == MR_RECURSIVE){uiCount++;}
	}
	if(uiCount){
		// push a frame and copy attrs to it
		spFrame = spFramePush(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			spFrame[uiStartIndex].uiIsOpen = APG_FALSE;
			spFrame[uiStartIndex].uiIsComplete = APG_FALSE;
			spFrame[uiStartIndex].cpRuleName = spCtx->spAttrs[uiStartIndex].cpRuleName;
			vAttrsNonRecursiveCopy(&spFrame[uiStartIndex], &spCtx->spAttrs[uiStartIndex]);
		}

		// 2.1 MR_EWCURSIVE ROUND 1
		spCtx->vpRuleAttrs = (void*)vMRRuleAttrs;
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			spAttrs = spCtx->spAttrs + uiStartIndex;
			if(spAttrs->uiRecursiveType == MR_RECURSIVE){
				spCtx->uiStartRuleIndex = uiStartIndex;
				((PFN_OPRNM)spCtx->vpRuleAttrs)(spCtx, uiStartIndex, &sComputedAttrs);
				// !!!! DEBUG !!!!
				GASSERT(sComputedAttrs.uiIsComplete);
				GASSERT(!sComputedAttrs.uiIsOpen);
				// !!!! DEBUG !!!!
			}
		}

		// copy down to save result for comparison to round 2
		spFrame = spFramePeek(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			if(spCtx->spAttrs[uiStartIndex].uiRecursiveType == MR_RECURSIVE){
				vAttrsNonRecursiveCopy(&spCtx->spAttrs[uiStartIndex], &spFrame[uiStartIndex]);
			}
		}

		// 2.2 MR_EWCURSIVE ROUND 2 - use previous iteration results for leaf rules
		spFrame = spFramePeek(spCtx->vpFrameCtx);
		GASSERT(spFrame);

		// reset all rules to open and incomplete
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			spFrame[uiStartIndex].uiIsOpen = APG_FALSE;
			spFrame[uiStartIndex].uiIsComplete = APG_FALSE;
		}
		spCtx->vpRuleAttrs = (void*)vMRRuleAttrs;
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			spAttrs = spCtx->spAttrs + uiStartIndex;
			if(spAttrs->uiRecursiveType == MR_RECURSIVE){
				spCtx->uiStartRuleIndex = uiStartIndex;
				((PFN_OPRNM)spCtx->vpRuleAttrs)(spCtx, uiStartIndex, &sComputedAttrs);
				// !!!! DEBUG !!!!
				GASSERT(sComputedAttrs.uiIsComplete);
				GASSERT(!sComputedAttrs.uiIsOpen);
				// !!!! DEBUG !!!!
			}
		}

		// compare round 1 to round 2
		spFrame = spFramePop(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		uiCount = 0;
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			if(spCtx->spAttrs[uiStartIndex].uiRecursiveType == MR_RECURSIVE){
				if((spCtx->spAttrs[uiStartIndex].uiFinite != spFrame[uiStartIndex].uiFinite) ||
						(spCtx->spAttrs[uiStartIndex].uiEmpty != spFrame[uiStartIndex].uiEmpty)){uiCount++;}
			}
		}
		if(uiCount){
			// handle discrepancy
			printf("\nWARNING - RM_RECURSIVE RESULTS - ROUND 1 DIFFERS FROM ROUND 2\n");
			for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
				if(spCtx->spAttrs[uiStartIndex].uiRecursiveType == MR_RECURSIVE){
					printf("ROUND 1: ");
					vDisplayAttrsLine(&spCtx->spAttrs[uiStartIndex], spCtx->spAttrs[uiStartIndex].cpRuleName);
					printf("ROUND 2: ");
					vDisplayAttrsLine(&spFrame[uiStartIndex], spFrame[uiStartIndex].cpRuleName);
				}
			}
		}

		// save round 2 results
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			// copy down
			if(spCtx->spAttrs[uiStartIndex].uiRecursiveType == MR_RECURSIVE){
				vAttrsNonRecursiveCopy(&spCtx->spAttrs[uiStartIndex], &spFrame[uiStartIndex]);
			}
		}
	}

	// 3. NMR_ & RMR_RECURSIVE
	spCtx->vpRuleAttrs = (void*)vRuleAttrs;
	for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
		spAttrs = spCtx->spAttrs + uiStartIndex;
		if((spAttrs->uiRecursiveType == NMR_RECURSIVE) || (spAttrs->uiRecursiveType == RMR_RECURSIVE)){
			vAttrsClear(&sComputedAttrs, spCtx->uiRuleCount);
			spCtx->uiStartRuleIndex = uiStartIndex;
			((PFN_OPRNM)spCtx->vpRuleAttrs)(spCtx, uiStartIndex, &sComputedAttrs);
		}
	}

	vFrameDtor(spCtx->vpFrameCtx);
}

static void vRuleAttrs(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs){
	ATTRS* spRuleAttrs;
	G_OPCODE* spOp;
	G_RULE* spRule;

	spRuleAttrs = &spCtx->spAttrs[uiRuleIndex];
	ATTRS_TRACE(spCtx, WHICH_RULE, uiRuleIndex, NULL, spRuleAttrs);
	while(APG_TRUE){
		if(spRuleAttrs->uiIsComplete || spRuleAttrs->uiIsOpen){
			// use initialized or final attributes
			spAttrs->uiIsComplete = APG_TRUE;
			spAttrs->uiIsOpen = APG_FALSE;
			vAttrsNonRecursiveCopy(spAttrs, spRuleAttrs);
			break;
		}
		// open the rule and traverse it
		memset((void*)spAttrs, 0, sizeof(ATTRS));
		spRule = spCtx->spRules + uiRuleIndex;
		spOp = spCtx->spOpcodes + spRule->uiChildOffset;
		spRuleAttrs->uiIsOpen = APG_TRUE;
		spCtx->uiTreeDepth++;
		vOpcodeAttrs(spCtx, spOp, spAttrs);
		spCtx->uiTreeDepth--;
		spAttrs->uiIsComplete = APG_TRUE;
		spAttrs->uiIsOpen = APG_FALSE;
		spRuleAttrs->uiIsOpen = spAttrs->uiIsOpen;
		spRuleAttrs->uiIsComplete = spAttrs->uiIsComplete;
		vAttrsNonRecursiveCopy(spRuleAttrs, spAttrs);
		break;
	}
}

static void vMRRuleAttrs(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs){
	ATTRS* spRuleAttrs;
	ATTRS* spFrame;
	ATTRS* spFrameOpen;
	G_UINT i;
	G_OPCODE* spOp;
	G_RULE* spRule;

	while(APG_TRUE){
		spFrame = spFramePeek(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		spRuleAttrs = &spFrame[uiRuleIndex];
		ATTRS_TRACE(spCtx, WHICH_MR_RULE, uiRuleIndex, NULL, spRuleAttrs);
		if(spRuleAttrs->uiIsComplete || spRuleAttrs->uiIsOpen){
			// use initialized or final attributes
			spAttrs->uiIsComplete = APG_TRUE;
			spAttrs->uiIsOpen = APG_FALSE;
			vAttrsNonRecursiveCopy(spAttrs, spRuleAttrs);
			break;
		}
		// this rule is not complete or open - push a frame and copy up and traverse the rule
		spFrameOpen = spFramePush(spCtx->vpFrameCtx); // push a new frame for this rule
		GASSERT(spFrameOpen);
		spFrame = spFramePrev(spCtx->vpFrameCtx);// refresh the previous frame
		GASSERT(spFrame);
		for(i = 0; i < spCtx->uiRuleCount; i++){ // copy previous frame up to this frame for initialization
			spFrameOpen[i].uiIsOpen = spFrame[i].uiIsOpen;
			spFrameOpen[i].uiIsComplete = spFrame[i].uiIsComplete;
			spFrameOpen[i].cpRuleName = spFrame[i].cpRuleName;
			vAttrsNonRecursiveCopy(&spFrameOpen[i], &spFrame[i]);
		}
		spFrame += uiRuleIndex;
		spRule = spCtx->spRules + uiRuleIndex;
		spOp = spCtx->spOpcodes + spRule->uiChildOffset;
		spFrameOpen[uiRuleIndex].uiIsOpen = APG_TRUE;
		spCtx->uiTreeDepth++;
		vOpcodeAttrs(spCtx, spOp, spAttrs); // traverse the rule
		spCtx->uiTreeDepth--;

		// copy this rule only down to previous frame
		spFrame = spFramePrev(spCtx->vpFrameCtx);// refresh the previous frame
		GASSERT(spFrame);
		spFrame += uiRuleIndex;
		spFrame->uiIsOpen = APG_FALSE;
		spFrame->uiIsComplete = APG_TRUE;
		vAttrsNonRecursiveCopy(spFrame, spAttrs);
		spFrame = spFramePop(spCtx->vpFrameCtx); // pop the unneeded frame for this rule
		GASSERT(spFrame);
		break;
	}
}

static void vOpcodeAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
//	ATTRS_TRACE(spCtx, WHICH_OP, spOpcode->sAlt.uiType, spOpcode, spAttrs);
	ATTRS_TRACE(spCtx, WHICH_OP, spOpcode->uiType, spOpcode, spAttrs);
//	switch(spOpcode->sAlt.uiType){
	switch(spOpcode->uiType){
	case G_TYPE_ALT:
		vAltAttrs(spCtx, spOpcode, spAttrs);
		break;
	case G_TYPE_CAT:
		vCatAttrs(spCtx, spOpcode, spAttrs);
		break;
	case G_TYPE_REP:
		vRepAttrs(spCtx, spOpcode, spAttrs);
		break;
	case G_TYPE_RNM:
		((PFN_OPRNM)spCtx->vpRuleAttrs)(spCtx, spOpcode->sOpType.sRnm.uiRuleIndex, spAttrs);
		break;
	case G_TYPE_UDT:
		spAttrs->uiFinite = APG_TRUE;
		spAttrs->uiEmpty = spOpcode->sOpType.sUdt.uiEmpty;
		break;
	case G_TYPE_AND:
	case G_TYPE_NOT:
		spAttrs->uiFinite = APG_TRUE;
		spAttrs->uiEmpty = APG_TRUE;
		break;
	case G_TYPE_TRG:
		spAttrs->uiEmpty = APG_FALSE;
		spAttrs->uiFinite = APG_TRUE;
		break;
	case G_TYPE_TBS:
		spAttrs->uiFinite = APG_TRUE;
		spAttrs->uiEmpty = APG_FALSE;
		break;
	case G_TYPE_TLS:
		spAttrs->uiFinite = APG_TRUE;
		spAttrs->uiEmpty = (spOpcode->sOpType.sTls.uiLen == 0) ? APG_TRUE:APG_FALSE;
		break;
	default:
		GASSERT(APG_FALSE);
		break;
	}
	spAttrs->uiIsComplete = APG_TRUE;
	spAttrs->uiIsOpen = APG_FALSE;
}
static void vAltAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	G_UINT i;
	G_OPCODE* spChildOp;
	ATTRS saChildren[spOpcode->sOpType.sAlt.uiChildCount];
	ATTRS* spChildAttrs = &saChildren[0];
	GASSERT(spOpcode->sOpType.sAlt.uiChildCount > 1);
	vAttrsClear(spAttrs, spCtx->uiRuleCount);
	for(i = 0; i < spOpcode->sOpType.sAlt.uiChildCount; i++, spChildAttrs++){
		memset((void*)spChildAttrs, 0, sizeof(ATTRS));
		vAttrsClear(spChildAttrs, spCtx->uiRuleCount);
		spChildOp = spCtx->spOpcodes + spCtx->uipChildList[spOpcode->sOpType.sAlt.uiChildListOffset + i];
		vOpcodeAttrs(spCtx, spChildOp, spChildAttrs);
	}
	spChildAttrs = &saChildren[0];
	spAttrs->uiFinite = APG_FALSE;	// false until proven otherwise
	spAttrs->uiEmpty = APG_FALSE;
	for(i = 0; i < spOpcode->sOpType.sAlt.uiChildCount; i++, spChildAttrs++){
		if(spChildAttrs->uiFinite == APG_TRUE){
			spAttrs->uiFinite = APG_TRUE;	// if any branch is Finite, ALT is Finite
			if(spChildAttrs->uiEmpty == APG_TRUE){
				spAttrs->uiEmpty = APG_TRUE;	// if any branch is Empty, ALT is Finite
				break; // once empty always empty
			} else{spAttrs->uiEmpty = APG_FALSE;}
		}
	}
}

static void vCatAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	G_UINT i;
	G_OPCODE* spChildOp;
	ATTRS saChildren[spOpcode->sOpType.sCat.uiChildCount];
	ATTRS* spChildAttrs = &saChildren[0];
	GASSERT(spOpcode->sOpType.sCat.uiChildCount > 1);
	vAttrsClear(spAttrs, spCtx->uiRuleCount);
	for(i = 0; i < spOpcode->sOpType.sCat.uiChildCount; i++, spChildAttrs++){
		memset((void*)spChildAttrs, 0, sizeof(ATTRS));
		vAttrsClear(spChildAttrs, spCtx->uiRuleCount);
		spChildOp = spCtx->spOpcodes + spCtx->uipChildList[spOpcode->sOpType.sCat.uiChildListOffset + i];
		vOpcodeAttrs(spCtx, spChildOp, spChildAttrs);
	}
	spChildAttrs = &saChildren[0];
	spAttrs->uiFinite = APG_TRUE;	// true until proven otherwise
	spAttrs->uiEmpty = APG_TRUE;
	for(i = 0; i < spOpcode->sOpType.sCat.uiChildCount; i++, spChildAttrs++){
		if(spChildAttrs->uiFinite == APG_FALSE){
			spAttrs->uiFinite = APG_FALSE;	// if any child is NOT finite, CAT is not finite
		}
		if(spChildAttrs->uiEmpty == APG_FALSE){
			spAttrs->uiEmpty = APG_FALSE;	// if any child is NOT empty, CAT is not empty
		}
	}
}

static void vRepAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	vAttrsClear(spAttrs, spCtx->uiRuleCount);
	if(spOpcode->sOpType.sRep.uiMin == 0){
		spAttrs->uiEmpty = APG_TRUE;
		spAttrs->uiFinite = APG_TRUE;
	} else{
		G_OPCODE* spChildOp = spCtx->spOpcodes + spOpcode->sOpType.sRep.uiChildOffset;
		vOpcodeAttrs(spCtx, spChildOp, spAttrs);
	}
}

