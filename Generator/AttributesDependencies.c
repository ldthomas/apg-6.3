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

static void vScanRule(ATTRS_CTX* spCtx, ATTRS* spAttrsI, G_UINT uiJ);
static G_UINT uiDisplayMRRules(ATTRS_CTX* spCtx);

void vRuleDependencies(ATTRS_CTX* spCtx){
	G_UINT i, j;
	ATTRS* spAttri;
	ATTRS* spAttrj;

	// get the list of dependencies for each rule
	for(i = 0; i < spCtx->uiRuleCount; i++){
		vScanRule(spCtx, &spCtx->spAttrs[i], i);
	}

	// get the recursive & non-recursive rules
	for(i = 0; i < spCtx->uiRuleCount; i++){
		spCtx->spAttrs[i].uiRecursiveType = N_RECURSIVE; // default to non-recursive
		if(spCtx->spAttrs[i].uipRefCount[i]){spCtx->spAttrs[i].uiRecursiveType = R_RECURSIVE;}
	}

	// get the mutually recursive rules
	for(i = 0; i < spCtx->uiRuleCount; i++){
		spAttri = &spCtx->spAttrs[i];
		if(spAttri->uiRecursiveType == R_RECURSIVE){
			for(j = 0; j < spCtx->uiRuleCount; j++){
				if(j != i){
					spAttrj = &spCtx->spAttrs[j];
					if(spAttrj->uiRecursiveType == R_RECURSIVE){
						if(spAttri->uipRefCount[j] && spAttrj->uipRefCount[i]){
							spAttri->uiRecursiveType = MR_RECURSIVE;
							spAttrj->uiRecursiveType = MR_RECURSIVE;
						}
					}
				}
			}
		}
	}

	// get the rules which refer to MR_RECURSIVE
	for(i = 0; i < spCtx->uiRuleCount; i++){
		spAttri = &spCtx->spAttrs[i];
		for(j = 0; j < spCtx->uiRuleCount; j++){
			spAttrj = &spCtx->spAttrs[j];
			if(spAttri->uipRefCount[j] && (spAttrj->uiRecursiveType == MR_RECURSIVE)){
				if(spAttri->uiRecursiveType == N_RECURSIVE){spAttri->uiRecursiveType = NMR_RECURSIVE;}
				else if(spAttri->uiRecursiveType == R_RECURSIVE){spAttri->uiRecursiveType = RMR_RECURSIVE;}
			}
		}
	}

}
void vDisplayRuleDependencyTypes(ATTRS_CTX* spCtx){
	G_UINT i;
	ATTRS* spAttrs;
	char* cpTranslatedName;
	G_UINT uiTranslatedRule;
	G_UINT uiCount;
	G_UINT uiTotal = 0;

	printf("N_RECURSIVE (non-recursive, never refers to itself)\n");
	for(i = 0, uiCount = 0; i < spCtx->uiRuleCount; i++){if(spCtx->spAttrs[i].uiRecursiveType == N_RECURSIVE){uiCount++;}}
	if(uiCount){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			uiTranslatedRule = spCtx->spQsort[i].uiRuleIndex;
			cpTranslatedName = spCtx->spQsort[i].cpRuleName;
			spAttrs = spCtx->spAttrs + uiTranslatedRule;
			if(spAttrs->uiRecursiveType == N_RECURSIVE){
				printf("%4lu | %s\n", (G_UINT)uiTranslatedRule, cpTranslatedName);
				uiTotal++;
			}
		}
	} else{printf("<none>\n");}
	printf("\n");
	printf("R_RECURSIVE (recursive, refers to itself)\n");
	for(i = 0, uiCount = 0; i < spCtx->uiRuleCount; i++){
		if((spCtx->spAttrs[i].uiRecursiveType == R_RECURSIVE)){uiCount++;}
	}
	if(uiCount){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			uiTranslatedRule = spCtx->spQsort[i].uiRuleIndex;
			cpTranslatedName = spCtx->spQsort[i].cpRuleName;
			spAttrs = spCtx->spAttrs + uiTranslatedRule;
			if(spAttrs->uiRecursiveType == R_RECURSIVE){
				printf("%4lu | %s\n", (G_UINT)uiTranslatedRule, cpTranslatedName);
				uiTotal++;
			}
		}
	} else{printf("<none>\n");}
	printf("\n");
	printf("MR_RECURSIVE (mutually-recursive, within each set(i), each rule refers to every other rule in set(i) including itself)\n");
	for(i = 0, uiCount = 0; i < spCtx->uiRuleCount; i++){
		if((spCtx->spAttrs[i].uiRecursiveType == MR_RECURSIVE)){uiCount++;}
	}
	if(uiCount){
		uiTotal += uiDisplayMRRules(spCtx);
	} else{printf("<none>\n\n");}
	printf("NMR_RECURSIVE (non-recursive but refers to one or more mutually-recursive rules)\n");
	for(i = 0, uiCount = 0; i < spCtx->uiRuleCount; i++){
		if((spCtx->spAttrs[i].uiRecursiveType == NMR_RECURSIVE)){uiCount++;}
	}
	if(uiCount){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			uiTranslatedRule = spCtx->spQsort[i].uiRuleIndex;
			cpTranslatedName = spCtx->spQsort[i].cpRuleName;
			spAttrs = spCtx->spAttrs + uiTranslatedRule;
			if(spAttrs->uiRecursiveType == NMR_RECURSIVE){
				printf("%4lu | %s\n", (G_UINT)uiTranslatedRule, cpTranslatedName);
				uiTotal++;
			}
		}
	} else{printf("<none>\n");}
	printf("\n");
	printf("RMR_RECURSIVE (recursive but refers to one or more mutually-recursive rules)\n");
	for(i = 0, uiCount = 0; i < spCtx->uiRuleCount; i++){
		if((spCtx->spAttrs[i].uiRecursiveType == RMR_RECURSIVE)){uiCount++;}
	}
	if(uiCount){
		for(i = 0; i < spCtx->uiRuleCount; i++){
			uiTranslatedRule = spCtx->spQsort[i].uiRuleIndex;
			cpTranslatedName = spCtx->spQsort[i].cpRuleName;
			spAttrs = spCtx->spAttrs + uiTranslatedRule;
			if(spAttrs->uiRecursiveType == RMR_RECURSIVE){
				printf("%4lu | %s\n", (G_UINT)uiTranslatedRule, cpTranslatedName);
				uiTotal++;
			}
		}
	} else{printf("<none>\n");}
	printf("\n");
}

static G_UINT uiDisplayMRRules(ATTRS_CTX* spCtx){
	G_UINT uiCount = 0;
	G_UINT i, it, j, jt, uiSet;
	ATTRS *spAttrsi, *spAttrsj;
	char *cpNamei, *cpNamej;

	for(i = 0; i < spCtx->uiRuleCount; i++){spCtx->spAttrs[i].uiIsComplete = APG_FALSE;}
	// display MR sets - each rule in set(i) refers to all other rules in set(i)
	for(i = 0, uiSet = 0; i < spCtx->uiRuleCount; i++){
		it = spCtx->spQsort[i].uiRuleIndex;
		cpNamei = spCtx->spQsort[i].cpRuleName;
		spAttrsi = &spCtx->spAttrs[it];
		if((!spAttrsi->uiIsComplete) && (spAttrsi->uiRecursiveType == MR_RECURSIVE)){
			printf("set: %lu\n", (G_UINT)uiSet++);
			printf("%4lu | %s\n", (G_UINT)it, cpNamei);
			spAttrsi->uiIsComplete = APG_TRUE;
			uiCount++;
			for(j = 0; j < spCtx->uiRuleCount; j++){
				jt = spCtx->spQsort[j].uiRuleIndex;
				cpNamej = spCtx->spQsort[j].cpRuleName;
				spAttrsj = &spCtx->spAttrs[jt];
				if((it != jt) && (spAttrsj->uiRecursiveType == MR_RECURSIVE) && (spAttrsi->uipRefCount[jt] > 0)){
					printf("%4lu | %s\n", (G_UINT)jt, cpNamej);
					spAttrsj->uiIsComplete = APG_TRUE;
					uiCount++;
				}
			}
			printf("\n");
		}
	}
	return uiCount;
}

///////////////////////////////////////////////////////////////////////////////
// STATIC HELPER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
static void vScanRule(ATTRS_CTX* spCtx, ATTRS* spAttrsI, G_UINT uiJ){
	G_OPCODE* spOp;
	G_OPCODE* spOpEnd;
	G_UINT uiDebug = 0;
	G_RULE* spRules = spCtx->spRules;
	spAttrsI->uipIsScanned[uiJ] = APG_TRUE;
	spOp = spCtx->spOpcodes + spRules[uiJ].uiChildOffset;
	spOpEnd = spOp + spRules[uiJ].uiChildCount;
	for(; spOp < spOpEnd; spOp++){
		// !!!! DEBUG !!!!
		if(++uiDebug > 10000){printf("vScanRule: DEBUG BREAK: too many iterations\n"); break;}
		// !!!! DEBUG !!!!

//		if(spOp->sRnm.uiType == G_TYPE_RNM){
		if(spOp->uiType == G_TYPE_RNM){
			G_UINT uiRnmIndex = spOp->sOpType.sRnm.uiRuleIndex;
			spAttrsI->uipRefCount[uiRnmIndex]++;
			if(!spAttrsI->uipIsScanned[uiRnmIndex]){
				vScanRule(spCtx, spAttrsI, uiRnmIndex);
			}
		}
	}
}

