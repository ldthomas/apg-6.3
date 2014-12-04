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
#include "Grammar.h"
#include "Private.h"

#undef PASSERT
#define PASSERT(cond) if(!(cond)){spCtx->pfnAlertHandler(__LINE__, __FILE__);}

//NOTE: returns phrase length on success, APG_UNDEFINED on failure
apg_uint uiALT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiHaveAst;
	APG_AST_CTX* spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	apg_uint uiPhraseLength = APG_UNDEFINED;
	apg_uint uiAstRecord = APG_UNDEFINED;
	APG_OPCODE* spChildOp;
	apg_uint* uipChildList = spOp->sUnion.sAlt.uipChildList;
	apg_uint* uipEnd = uipChildList + spOp->sUnion.sAlt.uiChildCount;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_ALT, uiOffset, 0);
	uiHaveAst = spAstCtx && !spAstCtx->uiIgnoreRecords;
	for(; uipChildList < uipEnd; uipChildList++){
		if(uiHaveAst){uiAstRecord = spAstCtx->uiRecordCount;}
		spChildOp = spCtx->spOpcodes + *uipChildList;
		uiPhraseLength = spChildOp->pfnOp(spCtx, spChildOp, uiOffset);
		if(uiPhraseLength != APG_UNDEFINED){break;}
		if(uiHaveAst){uiAstRecord = spAstCtx->uiRecordCount;}
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_ALT, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_ALT, 0);
	return uiPhraseLength;
}

apg_uint uiCAT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	APG_AST_CTX* spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	apg_uint uiHaveAst;
	apg_uint uiPhraseLength = 0;
	apg_uint uiAstRecord = APG_UNDEFINED;
	apg_uint uiChildOffset = uiOffset;
	apg_uint uiChildLength;
	APG_OPCODE* spChildOp;
	apg_uint* uipChildList = spOp->sUnion.sCat.uipChildList;
	apg_uint* uipEnd = uipChildList + spOp->sUnion.sCat.uiChildCount;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_CAT, uiOffset, 0);
	uiHaveAst = spAstCtx && !spAstCtx->uiIgnoreRecords;
	if(uiHaveAst){uiAstRecord = spAstCtx->uiRecordCount;}
	for(; uipChildList < uipEnd; uipChildList++){
		spChildOp = spCtx->spOpcodes + *uipChildList;
		uiChildLength = spChildOp->pfnOp(spCtx, spChildOp, uiChildOffset);
		if(uiChildLength == APG_UNDEFINED){uiPhraseLength = APG_UNDEFINED; break;}
		uiPhraseLength += uiChildLength;
		uiChildOffset += uiChildLength;
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_CAT, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_CAT, 0);
	if(uiHaveAst && uiPhraseLength == APG_UNDEFINED){spAstCtx->uiRecordCount = uiAstRecord;}
	return uiPhraseLength;
}

apg_uint uiREP(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	APG_AST_CTX* spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	apg_uint uiHaveAst;
	apg_uint uiPhraseLength = 0;
	apg_uint uiAstRecord = APG_UNDEFINED;
	apg_uint uiChildAstRecord = 0;
	apg_uint uiChildLength;
	apg_uint uiChildOffset = uiOffset;
	apg_uint uiChildMatches = 0;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_REP, uiOffset, 0);
	uiHaveAst = spAstCtx && !spAstCtx->uiIgnoreRecords;
	if(uiHaveAst){uiAstRecord = spAstCtx->uiRecordCount;}
	while(APG_TRUE){
		if(uiHaveAst){uiChildAstRecord = spAstCtx->uiRecordCount;}
		uiChildLength = spOp->sUnion.sRep.spNext->pfnOp(spCtx, spOp->sUnion.sRep.spNext, uiChildOffset);
		if(uiChildLength == 0){break;}	// child empty success, REP success regardless of min/max
		if(uiChildLength == APG_UNDEFINED){  // child failure - consider whether min/max allows success
			if(uiHaveAst){spAstCtx->uiRecordCount = uiChildAstRecord;} // child failed
			if(uiChildMatches < spOp->sUnion.sRep.uiMin){
				if(uiHaveAst){spAstCtx->uiRecordCount = uiAstRecord;} // REP failed
				uiPhraseLength = APG_UNDEFINED;
			}
			break;  // else success
		} else{  // child non-empty success, consider whether we have max successes
			uiPhraseLength += uiChildLength;
			uiChildOffset += uiChildLength;
			uiChildMatches++;
			if(uiChildMatches == spOp->sUnion.sRep.uiMax){break;} // REP success
			// else repeat child
		}
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_REP, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_REP, 0);
	return uiPhraseLength;
}

apg_uint uiRNM(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	APG_AST_CTX* spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	apg_uint uiHaveAst = APG_FALSE;
	apg_uint uiHaveAstRecord = APG_FALSE;
	apg_uint uiPhraseLength, uiAstCloseRecord;
	apg_uint uiAstOpenRecord = APG_UNDEFINED;
	APG_AST_RECORD* spOpenRecord;
	APG_AST_RECORD* spCloseRecord;
	apg_uint uiOverride;
	APG_OP_RNM* spRnm = &spOp->sUnion.sRnm;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_RNM, uiOffset, 0);
	if(spAstCtx != NULL){
		uiHaveAst = APG_TRUE;
		uiHaveAstRecord = (!spAstCtx->uiIgnoreRecords &&
				(spAstCtx->uipNodes[spRnm->spRule->uiRuleIndex] || spAstCtx->pfnCallbacks[spRnm->spRule->uiRuleIndex]));
	}
	if(uiHaveAst){uiAstOpenRecord = spAstCtx->uiRecordCount;}
	if(uiHaveAstRecord){
		// add pre-branch AST record
		spAstCtx->uiRecordCount++;
		if(uiAstOpenRecord >= spAstCtx->uiRecordEnd){vAstGrow(spAstCtx);}
		spOpenRecord = spAstCtx->spRecords + uiAstOpenRecord;
		spOpenRecord->uiState = PRE_AST;
		spOpenRecord->uiId = spRnm->spRule->uiRuleIndex;
		spOpenRecord->uiThisRecord = uiAstOpenRecord;
	}
	while(APG_TRUE){
		if(spRnm->spRule->pfnCBSyntax){
			spCtx->sCBData.uiState = PRE_PARSE;
			spCtx->sCBData.uiPhraseOffset = uiOffset;
			spCtx->sCBData.uiPhraseLength = 0;
			uiOverride = spRnm->spRule->pfnCBSyntax(&spCtx->sCBData);
			if(uiOverride){  // treat this as the rule result, return uiPhraseLength
				uiPhraseLength = spCtx->sCBData.uiPhraseLength;
				break;
			}
		}
		uiPhraseLength = spRnm->spNext->pfnOp(spCtx, spRnm->spNext, uiOffset); // otherwise, compute the phrase length normally
		break;
	}
	if(spRnm->spRule->pfnCBSyntax){
		if(uiPhraseLength == APG_UNDEFINED){spCtx->sCBData.uiState = NOMATCH;}
		else if(uiPhraseLength == 0){spCtx->sCBData.uiState = EMPTY;}
		else{spCtx->sCBData.uiState = MATCH;}
		spCtx->sCBData.uiPhraseOffset = uiOffset;
		spCtx->sCBData.uiPhraseLength = uiPhraseLength;
		uiOverride = spRnm->spRule->pfnCBSyntax(&spCtx->sCBData);
		if(uiOverride){uiPhraseLength = spCtx->sCBData.uiPhraseLength;}  // treat this as the rule result, return uiPhraseLength
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_RNM, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_RNM, spRnm->spRule->uiRuleIndex);
	if(uiPhraseLength == APG_UNDEFINED){
		if(uiHaveAst){spAstCtx->uiRecordCount = uiAstOpenRecord;} // remove any lower branch AST records
	} else if(uiHaveAstRecord){
		// add post-branch AST record
		uiAstCloseRecord = spAstCtx->uiRecordCount++;
		if(uiAstCloseRecord >= spAstCtx->uiRecordEnd){vAstGrow(spAstCtx);}
		spCloseRecord = spAstCtx->spRecords + uiAstCloseRecord;
		spCloseRecord->uiState = POST_AST;
		spCloseRecord->uiThisRecord = uiAstCloseRecord;
		spCloseRecord->uiThatRecord = uiAstOpenRecord;
		spCloseRecord->uiId = spRnm->spRule->uiRuleIndex;
		spCloseRecord->uiPhraseOffset = uiOffset;
		spCloseRecord->uiPhraseLength = uiPhraseLength;

		// complete the open record
		spOpenRecord = spAstCtx->spRecords + uiAstOpenRecord;
		spOpenRecord->uiThatRecord = uiAstCloseRecord;
		spOpenRecord->uiPhraseOffset = uiOffset;
		spOpenRecord->uiPhraseLength = uiPhraseLength;
	}
	return uiPhraseLength;
}

apg_uint uiUDT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	APG_AST_CTX* spAstCtx = (APG_AST_CTX*)spCtx->vpAstCtx;
	apg_uint uiPhraseLength; // state not needed, return value not needed
	apg_uint uiHaveAst = APG_FALSE;
	apg_uint uiHaveAstRecord = APG_FALSE;
	apg_uint uiAstCloseRecord;
	apg_uint uiId = APG_UNDEFINED;
	apg_uint uiAstOpenRecord = APG_UNDEFINED;
	APG_AST_RECORD* spOpenRecord;
	APG_AST_RECORD* spCloseRecord;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_UDT, uiOffset, 0);
	if(spAstCtx != NULL){
		uiId = spCtx->uiRuleCount + spOp->sUnion.sUdt.spUdt->uiUdtIndex;
		uiHaveAst = APG_TRUE;
		uiHaveAstRecord = (!spAstCtx->uiIgnoreRecords && (spAstCtx->uipNodes[uiId] ||	spAstCtx->pfnCallbacks[uiId]));
	}
	if(uiHaveAst){uiAstOpenRecord = spAstCtx->uiRecordCount;}
	if(uiHaveAstRecord){
		// add pre-branch AST record
		spAstCtx->uiRecordCount++;
		if(uiAstOpenRecord >= spAstCtx->uiRecordEnd){vAstGrow(spAstCtx);}
		spOpenRecord = spAstCtx->spRecords + uiAstOpenRecord;
		spOpenRecord->uiState = PRE_AST;
		spOpenRecord->uiId = uiId;
		spOpenRecord->uiThisRecord = uiAstOpenRecord;
	}
	spCtx->sCBData.uiState = PRE_PARSE;
	spCtx->sCBData.uiPhraseOffset = uiOffset;
	spCtx->sCBData.uiPhraseLength = 0;
	spOp->sUnion.sUdt.spUdt->pfnCBSyntax(&spCtx->sCBData);
	uiPhraseLength = spCtx->sCBData.uiPhraseLength;
	if(uiPhraseLength == 0){PASSERT(spOp->sUnion.sUdt.spUdt->uiEmpty);} // non-empty UDTS may not return empty
	if(uiPhraseLength != APG_UNDEFINED){
		PASSERT((uiOffset + uiPhraseLength) <= spCtx->uiInputStringLen); // phrase length may not be larger that remaining characters in string
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_UDT, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_UDT, spOp->sUnion.sUdt.spUdt->uiUdtIndex);
	if(uiPhraseLength == APG_UNDEFINED){
		if(uiHaveAst){spAstCtx->uiRecordCount = uiAstOpenRecord;}
	} else if(uiHaveAstRecord){
		// add post-branch AST record
		uiAstCloseRecord = spAstCtx->uiRecordCount++;
		if(uiAstCloseRecord >= spAstCtx->uiRecordEnd){vAstGrow(spAstCtx);}
		spCloseRecord = spAstCtx->spRecords + uiAstCloseRecord;
		spCloseRecord->uiState = POST_AST;
		spCloseRecord->uiThisRecord = uiAstCloseRecord;
		spCloseRecord->uiThatRecord = uiAstOpenRecord;
		spCloseRecord->uiId = uiId;
		spCloseRecord->uiPhraseOffset = uiOffset;
		spCloseRecord->uiPhraseLength = uiPhraseLength;

		// complete the open record
		spOpenRecord = spAstCtx->spRecords + uiAstOpenRecord;
		spOpenRecord->uiThatRecord = uiAstCloseRecord;
		spOpenRecord->uiPhraseOffset = uiOffset;
		spOpenRecord->uiPhraseLength = uiPhraseLength;
	}
	return uiPhraseLength;
}

apg_uint uiAND(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiPhraseLength;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_AND, uiOffset, 0);
	if(spCtx->vpAstCtx){((APG_AST_CTX*)spCtx->vpAstCtx)->uiIgnoreRecords++;}
	uiPhraseLength = spOp->sUnion.sAnd.spNext->pfnOp(spCtx, spOp->sUnion.sAnd.spNext, uiOffset);
	if(spCtx->vpAstCtx){((APG_AST_CTX*)spCtx->vpAstCtx)->uiIgnoreRecords--;}
	if(uiPhraseLength != APG_UNDEFINED){uiPhraseLength = 0;} // return empty string on child success
	// else return failure
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_AND, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_AND, 0);
	return uiPhraseLength;
}

apg_uint uiNOT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiPhraseLength;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_NOT, uiOffset, 0);
	if(spCtx->vpAstCtx){((APG_AST_CTX*)spCtx->vpAstCtx)->uiIgnoreRecords++;}
	uiPhraseLength = spOp->sUnion.sNot.spNext->pfnOp(spCtx, spOp->sUnion.sNot.spNext, uiOffset);
	if(spCtx->vpAstCtx){((APG_AST_CTX*)spCtx->vpAstCtx)->uiIgnoreRecords--;}
	if(uiPhraseLength != APG_UNDEFINED){uiPhraseLength = APG_UNDEFINED;} // return failure on child success
	else{uiPhraseLength = 0;} // return empty string success on child failure
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_NOT, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_NOT, 0);
	return uiPhraseLength;
}

apg_uint uiTRG(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiPhraseLength = APG_UNDEFINED;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_TRG, uiOffset, 0);
	if(uiOffset < spCtx->uiInputStringLen){
		apg_achar acChar = spCtx->acpInputString[uiOffset];
		if(acChar >= spOp->sUnion.sTrg.acMin && acChar <= spOp->sUnion.sTrg.acMax){uiPhraseLength = 1;} // success
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_TRG, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_TRG, 0);
	return uiPhraseLength;
}

apg_uint uiTBS(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiPhraseLength = APG_UNDEFINED;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_TBS, uiOffset, 0);
	if((uiOffset + spOp->sUnion.sTbs.uiStrLen) <= spCtx->uiInputStringLen){
		const apg_achar* acpChar = spCtx->acpInputString + uiOffset;
		apg_achar* acpBeg = spOp->sUnion.sTbs.acpStrTbl;
		apg_achar* acpEnd = acpBeg + spOp->sUnion.sTbs.uiStrLen;
		for(uiPhraseLength = 0; acpBeg < acpEnd; acpBeg++, acpChar++, uiPhraseLength++){
			if(*acpBeg != *acpChar){uiPhraseLength = APG_UNDEFINED; break;} // failure
		}
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_TBS, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_TBS, 0);
	return uiPhraseLength;
}

apg_uint uiTLS(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset){
	apg_uint uiPhraseLength = APG_UNDEFINED;
	APG_TRACE(spCtx, spOp, TRACE_ACTION_DOWN, P_TLS, uiOffset, 0);
	if((uiOffset + spOp->sUnion.sTls.uiStrLen) <= spCtx->uiInputStringLen){
		const apg_achar* acpChar = spCtx->acpInputString + uiOffset;
		apg_achar* acpBeg = spOp->sUnion.sTbs.acpStrTbl;
		apg_achar* acpEnd = acpBeg + spOp->sUnion.sTbs.uiStrLen;
		apg_achar acInput;
		for(uiPhraseLength = 0; acpBeg < acpEnd; acpBeg++, acpChar++, uiPhraseLength++){
			acInput = *acpChar;
			if(acInput >= 65 && acInput <= 90){acInput += 32;} // compare lower cases (TLS string already converted to lower)
			if(*acpBeg != acInput){uiPhraseLength = APG_UNDEFINED; break;} // failure
		}
	}
	APG_TRACE(spCtx, spOp, TRACE_ACTION_UP, P_TLS, uiOffset, uiPhraseLength);
	APG_STATS(spCtx, STATS_ACTION_COLLECT, uiPhraseLength, P_TLS, 0);
	return uiPhraseLength;
}


