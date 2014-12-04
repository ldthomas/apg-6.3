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
static void vOpcodeAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vAltAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vCatAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);
static void vRepAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs);

static G_UINT uiIsCatLeft(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsCatNested(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsCatRight(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsCatCyclic(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsCatFinite(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsCatEmpty(ATTRS* spChildren, G_UINT uiCount);
static G_UINT uiIsEmptyOnly(ATTRS* spAttrs);
//static G_UINT uiIsUnparsable(ATTRS* spAttrs);


void vRecursiveAttributes(ATTRS_CTX* spCtx){
	G_UINT uiStartIndex;
	G_UINT uiRuleCount = spCtx->uiRuleCount;
	ATTRS* spAttrs;
	ATTRS* spFrame;
	ATTRS sComputedAttrs;
	G_UINT uiCount;

	// initialize all recursive attributes to leaf attributes, closed and incomplete
	// (assumes Finite and Empty attributes have already been computed)
	memset(&sComputedAttrs, 0, sizeof(ATTRS));
	spCtx->vpFrameCtx = vpFrameCtor(spCtx->vpMemCtx, uiRuleCount, spCtx->spAttrs);
	GASSERT(spCtx->vpFrameCtx);
	uiCount = 0;
	for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
		spAttrs = spCtx->spAttrs + uiStartIndex;
		spAttrs->uiIsOpen = APG_FALSE;
		spAttrs->uiIsComplete = APG_FALSE;
		if(spAttrs->uiRecursiveType == R_RECURSIVE || spAttrs->uiRecursiveType == MR_RECURSIVE){
			spAttrs->uiLeft = APG_TRUE;
			spAttrs->uiNested = APG_FALSE;
			spAttrs->uiRight = APG_TRUE;
			spAttrs->uiCyclic = APG_TRUE;
			uiCount++;
		} else{
			spAttrs->uiLeft = APG_FALSE;
			spAttrs->uiNested = APG_FALSE;
			spAttrs->uiRight = APG_FALSE;
			spAttrs->uiCyclic = APG_FALSE;
		}
	}

	if(uiCount){
		G_UINT j;
		spFrame = spFramePush(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		for(uiStartIndex = 0; uiStartIndex < uiRuleCount; uiStartIndex++){
			spAttrs = spCtx->spAttrs + uiStartIndex;
			if(spAttrs->uiRecursiveType == R_RECURSIVE || spAttrs->uiRecursiveType == MR_RECURSIVE){
				spCtx->uiStartRuleIndex = uiStartIndex;
				// initialize attributes on the frame for this start rule
				for(j = 0; j < uiRuleCount; j++){
					spFrame[j].uiLeft = APG_FALSE;
					spFrame[j].uiNested = APG_FALSE;
					spFrame[j].uiRight = APG_FALSE;
					spFrame[j].uiCyclic = APG_FALSE;
					spFrame[j].uiIsOpen = APG_FALSE;
					spFrame[j].uiIsComplete = APG_FALSE;
					spFrame[j].uiFinite = spCtx->spAttrs[j].uiFinite;
					spFrame[j].uiEmpty = spCtx->spAttrs[j].uiEmpty;
				}
				spFrame[uiStartIndex].uiLeft = APG_TRUE;
				spFrame[uiStartIndex].uiNested = APG_FALSE;
				spFrame[uiStartIndex].uiRight = APG_TRUE;
				spFrame[uiStartIndex].uiCyclic = APG_TRUE;

				// compute start rule's recursive attributes on the frame
				vRuleAttrs(spCtx, uiStartIndex, &sComputedAttrs);

				// save start rule result
				vAttrsRecursiveCopy(spAttrs, &spFrame[uiStartIndex]);
			}
		}
	}

	// clean up
	vFrameDtor(spCtx->vpFrameCtx);
}


static void vRuleAttrs(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs){
	ATTRS* spRuleAttrs;
	ATTRS* spFrame;
	ATTRS* spFrameAttrs;
	ATTRS* spFrameOpen;
	G_UINT i;
	G_OPCODE* spOp;
	G_RULE* spRule;

	spRuleAttrs = &spCtx->spAttrs[uiRuleIndex];
	ATTRS_TRACE(spCtx, WHICH_RULE, uiRuleIndex, NULL, spRuleAttrs);
	while(APG_TRUE){
		if(spRuleAttrs->uipRefCount[spCtx->uiStartRuleIndex] == 0){	// does not refer to start rule - use rule attrs
			vAttrsCopy(spAttrs, spRuleAttrs);
			break;
		}
		spFrame = spFramePeek(spCtx->vpFrameCtx);
		GASSERT(spFrame);
		spFrameAttrs = spFrame + uiRuleIndex;
		if(spFrameAttrs->uiIsComplete || spFrameAttrs->uiIsOpen){
			vAttrsCopy(spAttrs, spFrameAttrs);	// use leaf or previously calculated result
			break;
		}

//		// open the rule and traverse it
		// this rule is not complete or open - push a frame and copy up and traverse the rule
		spFrameOpen = spFramePush(spCtx->vpFrameCtx); // push a new frame for this rule
		GASSERT(spFrameOpen);
		spFrameAttrs = spFrameOpen + uiRuleIndex;
		spFrame = spFramePrev(spCtx->vpFrameCtx);// refresh the previous frame
		GASSERT(spFrame);
		for(i = 0; i < spCtx->uiRuleCount; i++){ // copy previous frame up to this frame for initialization
			spFrameOpen[i].uiIsOpen = spFrame[i].uiIsOpen;
			spFrameOpen[i].uiIsComplete = spFrame[i].uiIsComplete;
			spFrameOpen[i].cpRuleName = spFrame[i].cpRuleName;
			vAttrsCopy(&spFrameOpen[i], &spFrame[i]);
		}

		spRule = spCtx->spRules + uiRuleIndex;
		spOp = spCtx->spOpcodes + spRule->uiChildOffset;
		spFrameAttrs->uiIsOpen = APG_TRUE;
		spCtx->uiTreeDepth++;
		vOpcodeAttrs(spCtx, spOp, spAttrs);
		spCtx->uiTreeDepth--;

		// copy this rule only down to previous frame
		spFrameOpen = spFramePeek(spCtx->vpFrameCtx); // refresh top frame pointer
		GASSERT(spFrameOpen);
		spFrame = spFramePrev(spCtx->vpFrameCtx);// refresh the previous frame pointer
		GASSERT(spFrame);
		spFrameAttrs = spFrame + uiRuleIndex;
		spFrameAttrs->uiIsOpen = APG_FALSE;
		spFrameAttrs->uiIsComplete = APG_TRUE;
		vAttrsRecursiveCopy(spFrameAttrs, spAttrs);
		vAttrsNonRecursiveCopy(spFrameAttrs, spRuleAttrs);
		spFrame = spFramePop(spCtx->vpFrameCtx); // pop the unneeded frame for this rule
		GASSERT(spFrame);
		break;
	}
}

static void vOpcodeAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	ATTRS_TRACE(spCtx, WHICH_OP, spOpcode->uiType, spOpcode, spAttrs);
	spAttrs->uiLeft = APG_FALSE;	// default values
	spAttrs->uiNested = APG_FALSE;
	spAttrs->uiRight = APG_FALSE;
	spAttrs->uiCyclic = APG_FALSE;
	spAttrs->uiFinite = APG_UNDEFINED;
	spAttrs->uiEmpty = APG_UNDEFINED;
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
		vRuleAttrs(spCtx, spOpcode->sOpType.sRnm.uiRuleIndex, spAttrs);
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
	for(i = 0; i < spOpcode->sOpType.sAlt.uiChildCount; i++, spChildAttrs++){
		memset((void*)spChildAttrs, 0, sizeof(ATTRS));
		vAttrsClear(spChildAttrs, spCtx->uiRuleCount);
		spChildOp = spCtx->spOpcodes + spCtx->uipChildList[spOpcode->sOpType.sAlt.uiChildListOffset + i];
		vOpcodeAttrs(spCtx, spChildOp, spChildAttrs);
	}
	spChildAttrs = &saChildren[0];	// initialize ALT to first child
	vAttrsCopy(spAttrs, spChildAttrs);
	spChildAttrs++;
	for(i = 1; i < spOpcode->sOpType.sAlt.uiChildCount; i++, spChildAttrs++){
		if(spChildAttrs->uiLeft){spAttrs->uiLeft = APG_TRUE;}	// if any child is true ALT is true
		if(spChildAttrs->uiRight){spAttrs->uiRight = APG_TRUE;}
		if(spChildAttrs->uiNested){spAttrs->uiNested = APG_TRUE;}
		if(spChildAttrs->uiCyclic){spAttrs->uiCyclic = APG_TRUE;}
		if(spChildAttrs->uiFinite){spAttrs->uiFinite = APG_TRUE;}
		if(spChildAttrs->uiEmpty){spAttrs->uiEmpty = APG_TRUE;}
	}
}
static void vCatAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	G_UINT i, uiChildCount;
	G_OPCODE* spChildOp;
	ATTRS saChildren[spOpcode->sOpType.sCat.uiChildCount];
	ATTRS* spChildAttrs = &saChildren[0];
	GASSERT(spOpcode->sOpType.sCat.uiChildCount > 1);
	for(i = 0; i < spOpcode->sOpType.sCat.uiChildCount; i++, spChildAttrs++){
		memset((void*)spChildAttrs, 0, sizeof(ATTRS));
		vAttrsClear(spChildAttrs, spCtx->uiRuleCount);
		spChildOp = spCtx->spOpcodes + spCtx->uipChildList[spOpcode->sOpType.sCat.uiChildListOffset + i];
		vOpcodeAttrs(spCtx, spChildOp, spChildAttrs);
	}
	uiChildCount = spOpcode->sOpType.sCat.uiChildCount;
	spChildAttrs = &saChildren[0];
	spAttrs->uiLeft = uiIsCatLeft(spChildAttrs, uiChildCount);
	spAttrs->uiRight = uiIsCatRight(spChildAttrs, uiChildCount);
	spAttrs->uiNested = uiIsCatNested(spChildAttrs, uiChildCount);
	spAttrs->uiCyclic = uiIsCatCyclic(spChildAttrs, uiChildCount);
	spAttrs->uiFinite = uiIsCatFinite(spChildAttrs, uiChildCount);
	spAttrs->uiEmpty = uiIsCatEmpty(spChildAttrs, uiChildCount);
}
static void vRepAttrs(ATTRS_CTX* spCtx, G_OPCODE* spOpcode, ATTRS* spAttrs){
	G_OPCODE* spChildOp = spCtx->spOpcodes + spOpcode->sOpType.sRep.uiChildOffset;
	vOpcodeAttrs(spCtx, spChildOp, spAttrs);
}

static G_UINT uiIsEmptyOnly(ATTRS* spAttrs){
	return spAttrs->uiEmpty &&
			!(spAttrs->uiLeft || spAttrs->uiRight || spAttrs->uiNested || spAttrs->uiCyclic);
}
static G_UINT uiIsCatNested(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiNested = APG_FALSE;
	G_UINT uiFound, uiFoundRecursive;
	ATTRS* spChild;
	ATTRS* spEnd = spChildren + uiCount;
	while(APG_TRUE){
		// 1.) if any child is nested, CAT is nested
		for(spChild = spChildren; spChild < spEnd; spChild++){
			if(spChild->uiNested){uiNested = APG_TRUE; break;}
		}
		if(uiNested == APG_TRUE){break;}

		// 2.) the left-most, non-empty-only is right recursive and at least one non-empty only term follows it
		uiFoundRecursive = APG_FALSE;
		for(spChild = spChildren; spChild < spEnd; spChild++){
        	if(uiFoundRecursive){
        		if(!uiIsEmptyOnly(spChild)){uiNested = APG_TRUE; break;}
        	} else {
				if(spChild->uiRight && !spChild->uiLeft){uiFoundRecursive = APG_TRUE;}
				else{break;}
        	}
		}
		if(uiNested == APG_TRUE){break;}

    	// 3.) the right-most, non-empty-only is left-recursive and at least one non-empty only term follows it
		uiFoundRecursive = APG_FALSE;
		for(spChild = spEnd - 1; spChildren <= spEnd; spChild++){
        	if(uiFoundRecursive){
        		if(!uiIsEmptyOnly(spChild)){uiNested = APG_TRUE; break;}
        	} else {
				if(spChild->uiLeft && !spChild->uiRight){uiFoundRecursive = APG_TRUE;}
				else{break;}
        	}
		}
		if(uiNested == APG_TRUE){break;}

    	// 4.) there is at least one recursive term between the left-most and right-most non-empty-only terms
		uiFound = APG_FALSE;
		uiFoundRecursive = APG_FALSE;
		for(spChild = spChildren; spChild < spEnd; spChild++){
			if(uiFoundRecursive){
				if(!uiIsEmptyOnly(spChild)){uiNested = APG_TRUE; break;}
			} else{
				if(uiFound){
					if(spChild->uiLeft || spChild->uiRight || spChild->uiCyclic){uiFoundRecursive = APG_TRUE;}
				} else if(!uiIsEmptyOnly(spChild)){uiFound = APG_TRUE;}
			}
		}

		break;
	}
	return uiNested;
}

static G_UINT uiIsCatCyclic(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiRet = APG_TRUE;
	ATTRS* spEnd = spChildren + uiCount;
	for(; spChildren < spEnd; spChildren++){
		if(!spChildren->uiCyclic){uiRet = APG_FALSE; break;}	// if any child is NOT cyclic, CAT is not cyclic
																// (ie. S = S is cyclic & S = S S is also cyclic)
	}
	return uiRet;
}

static G_UINT uiIsCatLeft(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiRet = APG_FALSE;
	ATTRS* spEnd = spChildren + uiCount;
	for(; spChildren < spEnd; spChildren++){
		if(spChildren->uiLeft){uiRet = APG_TRUE; break;}    // if left-most, non-empty child is left, CAT is left
		if(!spChildren->uiEmpty){uiRet = APG_FALSE; break;}	// else if this child is not empty, CAT is not left
															// else this child is empty - keep looking
	}
	return uiRet;
}

static G_UINT uiIsCatFinite(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiRet = APG_TRUE;
	ATTRS* spBeg = spChildren;
	ATTRS* spEnd = spChildren + uiCount;
	for(; spBeg < spEnd; spBeg++){
		if(spBeg->uiFinite == APG_FALSE){
			uiRet = APG_FALSE;	// if any child is NOT finite, CAT is not finite
			break;
		}
	}
	return uiRet;
}

static G_UINT uiIsCatEmpty(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiRet = APG_FALSE;
	ATTRS* spBeg = spChildren;
	ATTRS* spEnd = spChildren + uiCount;
	for(; spBeg < spEnd; spBeg++){
		if(spBeg->uiEmpty == APG_FALSE){
			uiRet = APG_FALSE;	// if any child is NOT empty, CAT is not empty
			break;
		}
	}
	return uiRet;
}

static G_UINT uiIsCatRight(ATTRS* spChildren, G_UINT uiCount){
	G_UINT uiRet = APG_FALSE;
	ATTRS* spEnd = spChildren + uiCount - 1;
	for(; spChildren <= spEnd; spEnd--){
		if(spEnd->uiRight){uiRet = APG_TRUE; break;}	// if right-most, non-empty child is right, CAT is right
		if(!spEnd->uiEmpty){uiRet = APG_FALSE; break;}	// else if this child is not empty, CAT is not right
														// else this child is empty - keep looking
	}
	return uiRet;
}
