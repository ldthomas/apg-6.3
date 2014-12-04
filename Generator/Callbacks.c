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
#include "SABNFGrammar.h"
#include "Generator.h"
#include <ctype.h>

#define MAX_RULENAME 256
static char* g_cpMemError = "memory or vector error";
#define MEMASSERT(cond) if(!(cond)){vMsgAssert(g_cpMemError, __LINE__, __FILE__);}

static char g_caBuffer[4096];
static char* g_cpBuffer = &g_caBuffer[0];

static char* g_cpStringTable = NULL;
static int iCompRule(const void* vpLeft, const void* vpRight){
	G_RULE* spLeft = (G_RULE*)vpLeft;
	G_RULE* spRight = (G_RULE*)vpRight;
	char* cpLeftName = g_cpStringTable + spLeft->uiNameOffset;
	char* cpRightName = g_cpStringTable + spRight->uiNameOffset;
	return apg_stricmp(cpLeftName, cpRightName);
}
static int iCompUdt(const void* vpLeft, const void* vpRight){
	G_UDT* spLeft = (G_UDT*)vpLeft;
	G_UDT* spRight = (G_UDT*)vpRight;
	char* cpLeftName = g_cpStringTable + spLeft->uiNameOffset;
	char* cpRightName = g_cpStringTable + spRight->uiNameOffset;
	return apg_stricmp(cpLeftName, cpRightName);
}

static apg_uint sem_file(APG_CBDATA* spData){
	G_UINT i;
	void* vpTest;
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	G_RULE* spRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRuleTable);
	G_UDT* spUdts = (G_UDT*)vpVecFront(spCallbackCtx->vpVecUdtTable);
	G_RULE* spRulesAlpha;
	G_UDT* spUdtsAlpha;
	if(spData->uiState == PRE_AST){
		spCallbackCtx->uiLineNo = 0;
		spCallbackCtx->uiRuleDefinitionNo = 0;
	} else if(spData->uiState == POST_AST){
		G_UINT uiRuleCount = uiVecSize(spCallbackCtx->vpVecRuleTable);
		G_UINT uiUdtCount = uiVecSize(spCallbackCtx->vpVecUdtTable);
		g_cpStringTable = (char*)vpVecFront(spCallbackCtx->vpVecCharTable);

		// alphabetize
		for(i = 0; i < uiRuleCount; i++){
			vpTest = vpVecPush(spCallbackCtx->vpVecRuleTableAlphabetical, (void*)&spRules[i]);
			MEMASSERT(vpTest);
		}
		for(i = 0; i < uiUdtCount; i++){
			vpTest = vpVecPush(spCallbackCtx->vpVecUdtTableAlphabetical, (void*)&spUdts[i]);
			MEMASSERT(vpTest);
		}
		spRulesAlpha = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRuleTableAlphabetical);
		spUdtsAlpha = (G_UDT*)vpVecFront(spCallbackCtx->vpVecUdtTableAlphabetical);
		qsort((void*)spRulesAlpha, uiRuleCount, sizeof(G_RULE), iCompRule);
		qsort((void*)spUdtsAlpha, uiUdtCount, sizeof(G_UDT), iCompUdt);


		// complete the RNM opcodes
		vProcessRnmOpcodes(spCallbackCtx);
	}
	return APG_UNDEFINED;
}
static apg_uint sem_rule(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame;
	  G_RULE* spRule = NULL;
	  G_UINT uiTest;
	  if(spData->uiState == PRE_AST){
		  // push a stack frame
		  spFrame = (STACK_FRAME*)vpVecPush(spCallbackCtx->vpVecStack, NULL);
		  MEMASSERT(spFrame);
		  memset((void*)spFrame, 0, sizeof(*spFrame));
		  spFrame->uiRuleIndex = uiVecSize(spCallbackCtx->vpVecRuleTable);
		  spRule = (G_RULE*)vpVecPush(spCallbackCtx->vpVecRuleTable, NULL);
		  MEMASSERT(spRule);
		  spRule->uiRuleIndex = spFrame->uiRuleIndex;
		  spRule->uiChildOffset = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
		  spRule->uiChildCount = APG_UNDEFINED;
	  } else if(spData->uiState == POST_AST){
		  spCallbackCtx->uiRuleDefinitionNo++;
		  spFrame = (STACK_FRAME*)vpVecPop(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);
		  uiTest = uiVecSize(spCallbackCtx->vpVecStack);
		  MEMASSERT(uiTest == 0);
		  spRule = (G_RULE*)vpVecAt(spCallbackCtx->vpVecRuleTable, spFrame->uiRuleIndex);
		  MEMASSERT(spRule);
		  spRule->uiChildCount = uiVecSize(spCallbackCtx->vpVecOpcodeTable) - spRule->uiChildOffset;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_rulename(APG_CBDATA* spData){
    char caCharBuf[MAX_RULENAME + 1];
	char* cpRuleName = &caCharBuf[0];
	G_UINT uiRuleNameLength;
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	G_RULE* spRule = NULL;
	G_UINT uiRuleIndex;
	G_UINT i;
	STACK_FRAME* spFrame;
	char* cpStr;
	if(spData->uiState == POST_AST){
		uiRuleNameLength =spData->uiPhraseLength;
		if(spData->uiPhraseLength >= MAX_RULENAME){
			sprintf(g_cpBuffer, "rule: %lu: line: %lu: rule name too long - truncated: rule name length: %lu: rule name length max: %lu",
					  (G_UINT)spCallbackCtx->uiRuleDefinitionNo,
					(G_UINT)spCallbackCtx->uiLineNo, (G_UINT)spData->uiPhraseLength, (G_UINT)MAX_RULENAME);
			vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
			uiRuleNameLength = MAX_RULENAME;
		}
		for(i = 0; i < uiRuleNameLength; i++){
			cpRuleName[i] = (char)acpString[i];
		}
		cpRuleName[uiRuleNameLength] = 0;
		uiRuleIndex = uiRuleLookup(spCallbackCtx->vpVecRuleTable, spCallbackCtx->vpVecCharTable,
				cpRuleName, uiRuleNameLength);
		if(uiRuleIndex != APG_UNDEFINED){
			sprintf(g_cpBuffer, "rule: %lu: rule: %lu: line: %lu: rule name: %s: defined multiple times",
					  (G_UINT)spCallbackCtx->uiRuleDefinitionNo,
					(G_UINT)spCallbackCtx->uiRuleDefinitionNo, (G_UINT)spCallbackCtx->uiLineNo, cpRuleName);
			vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
		}
		spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		MEMASSERT(spFrame);
		spRule = (G_RULE*)vpVecAt(spCallbackCtx->vpVecRuleTable, spFrame->uiRuleIndex);
		MEMASSERT(spRule);
		spRule->uiGrammarLineNo = spCallbackCtx->uiLineNo;
		spRule->uiGrammarPhraseOffset = spData->uiPhraseOffset;
		spRule->uiGrammarPhraseLength = spData->uiPhraseLength;
		spRule->uiNameOffset = uiVecSize(spCallbackCtx->vpVecCharTable);
		spRule->uiNameLen = uiRuleNameLength;
		spRule->uiRuleIndex = uiVecSize(spCallbackCtx->vpVecRuleTable) - 1;

		// convert rule name from achar to char and put it in the (char) string table
		cpStr = (char*)vpVecPushn(spCallbackCtx->vpVecCharTable, NULL, uiRuleNameLength + 1);
		MEMASSERT(cpStr);
		strcpy(cpStr, cpRuleName);
	}
	return APG_UNDEFINED;
}

static apg_uint sem_multiplealt(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_ALT);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_ALT);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_multiplecat(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_CAT);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_CAT);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_udtnonempty(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_UDT);
		  MEMASSERT(spFrame);
		  spFrame->uiUdtEmpty = APG_FALSE;
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_UDT);
	  }
	  return APG_UNDEFINED;
}
static apg_uint sem_udtempty(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_UDT);
		  MEMASSERT(spFrame);
		  spFrame->uiUdtEmpty = APG_TRUE;
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_UDT);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_rnmop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_RNM);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_RNM);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_andop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_AND);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_AND);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_notop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_NOT);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_NOT);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_option(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_REP);
		  MEMASSERT(spFrame);
		  spFrame->uiRepMin = 0;
		  spFrame->uiRepMax = 1;
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_REP);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_repop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_REP);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_REP);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_repmin(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest, uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uidTranslateDigits(spFrame->uiInfinite, (char*)acpString, spData->uiPhraseLength, (G_UINT*)&uiNum);
		  MSGASSERT(uiTest, "sem_repmin: unable to translate digits");

		  // set min
		  spFrame->uiRepMin = uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_repmax(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest, uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uidTranslateDigits(spFrame->uiInfinite, (char*)acpString, spData->uiPhraseLength, (G_UINT*)&uiNum);
		  MSGASSERT(uiTest, "sem_repmax: unable to translate digits");

		  // set max
		  spFrame->uiRepMax = uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_repminmax(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest, uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uidTranslateDigits(spFrame->uiInfinite, (char*)acpString, spData->uiPhraseLength, (G_UINT*)&uiNum);
		  MSGASSERT(uiTest, "sem_repminmax: unable to translate digits");

		  // set min = max
		  spFrame->uiRepMin = uiNum;
		  spFrame->uiRepMax = uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_trgop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_TRG);
		  MEMASSERT(spFrame);
		  spFrame->uiInfinite = (G_UINT)-1;
		  spFrame->uiTrgMin = 0;
		  spFrame->uiTrgMax = spFrame->uiInfinite;
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_TRG);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_bnum(APG_CBDATA* spData){
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest;
	  G_UINT uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uibTranslateDigits(spFrame->uiInfinite, (char*)acpString, spData->uiPhraseLength, &uiNum);
		  MSGASSERT(uiTest, "sem_bnum: unable to translate digits");

		  // set num
		  spFrame->uiNumber= uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_dnum(APG_CBDATA* spData){
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest;
	  G_UINT uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uidTranslateDigits(spFrame->uiInfinite, (char*)acpString, spData->uiPhraseLength, &uiNum);
		  MSGASSERT(uiTest, "sem_dnum: unable to translate digits");

		  // set num
		  spFrame->uiNumber= uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_xnum(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  G_UINT uiTest;
	  G_UINT uiNum = APG_UNDEFINED;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // translate the digit string
		  uiTest = uixTranslateDigits(spFrame->uiInfinite, (char*)acpString, (G_UINT)spData->uiPhraseLength, &uiNum);
		  MSGASSERT(uiTest, "sem_xnum: unable to translate digits");

		  // set num
		  spFrame->uiNumber= uiNum;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_trgmax(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // set num
		  spFrame->uiTrgMax = spFrame->uiNumber;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_trgmin(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // set num
		  spFrame->uiTrgMin = spFrame->uiNumber;
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_tbsop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_TBS);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_TBS);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_tbsstring(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  void* vpTest;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // set string char
		  if(spFrame->uiNumber < spCallbackCtx->uiACharMin){spCallbackCtx->uiACharMin = spFrame->uiNumber;}
		  if(spFrame->uiNumber > spCallbackCtx->uiACharMax){spCallbackCtx->uiACharMax = spFrame->uiNumber;}
		  vpTest = vpVecPush(spFrame->vpVecString, (void*)&spFrame->uiNumber);
		  MEMASSERT(vpTest);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_tlsop(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  STACK_FRAME* spFrame = NULL;
	  if(spData->uiState == PRE_AST){
		  // initialize an opcode
		  spFrame = spPushOp(spCallbackCtx, G_TYPE_TLS);
		  MEMASSERT(spFrame);
	  } else if(spData->uiState == POST_AST){
		  // finalize the opcode
		  vPopOp(spData, G_TYPE_TLS);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_tlschar(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  void* vpTest;
	  G_UINT uiChar;
	  STACK_FRAME* spFrame;
	  if(spData->uiState == POST_AST){
		  // get the frame
		  spFrame = (STACK_FRAME*)vpVecBack(spCallbackCtx->vpVecStack);
		  MEMASSERT(spFrame);

		  // set string char
		  uiChar = (G_UINT)*acpString;
		  if(uiChar < spCallbackCtx->uiACharMin){spCallbackCtx->uiACharMin = uiChar;}
		  if(uiChar > spCallbackCtx->uiACharMax){spCallbackCtx->uiACharMax = uiChar;}
		  vpTest = vpVecPush(spFrame->vpVecString, (void*)&uiChar);
		  MEMASSERT(vpTest);
	  }
	  return APG_UNDEFINED;
}

static apg_uint sem_lineend(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  spCallbackCtx->uiLineNo++;
	  }

	  return APG_UNDEFINED;
}

static apg_uint sem_linecontinue(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  spCallbackCtx->uiLineNo++;
	  }

	  return APG_UNDEFINED;
}

static apg_uint sem_ruleerror(APG_CBDATA* spData){
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	if(spData->uiState == POST_AST){
		G_UINT uiLine = spCallbackCtx->uiLineNo ? spCallbackCtx->uiLineNo - 1 : spCallbackCtx->uiLineNo;
		sprintf(g_cpBuffer, "rule: %lu: line: %lu: rule error",
				(G_UINT)spCallbackCtx->uiRuleDefinitionNo, (G_UINT)uiLine);
		vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
		spCallbackCtx->uiRuleDefinitionNo++;
	}
	return APG_UNDEFINED;
}

static apg_uint sem_prosval(APG_CBDATA* spData){
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	if(spData->uiState == POST_AST){
		sprintf(g_cpBuffer, "rule: %lu: line: %lu: prosval not supported",
				(G_UINT)spCallbackCtx->uiRuleDefinitionNo, (G_UINT)spCallbackCtx->uiLineNo);
		vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
	}
	return APG_UNDEFINED;
}

static apg_uint sem_incalt(APG_CBDATA* spData){
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	if(spData->uiState == POST_AST){
		sprintf(g_cpBuffer, "rule: %lu: line: %lu: incalt (\"=/\") not supported",
				(G_UINT)spCallbackCtx->uiRuleDefinitionNo, (G_UINT)spCallbackCtx->uiLineNo);
		vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
	}
	return APG_UNDEFINED;
}

void vCallbackInit(void* vpMemCtx, CALLBACK_CTX* spCallbackCtx){
	void* vpTest;
	char* cpVersion = cpApgVersion();
	G_UINT uiVersionLen = (G_UINT)strlen(cpVersion) + 1;
	memset((void*)spCallbackCtx, 0, sizeof(CALLBACK_CTX));
	spCallbackCtx->vpMemCtx = vpMemCtx;
	spCallbackCtx->uiLineNo = 0;
	spCallbackCtx->uiACharMax = 0;
	spCallbackCtx->uiACharMin = (G_UINT)-1;

	spCallbackCtx->vpVecCharTable = vpVecCtor(vpMemCtx, sizeof(char), 100);
	MEMASSERT(spCallbackCtx->vpVecCharTable);
	vpTest = vpVecPushn(spCallbackCtx->vpVecCharTable, (void*)cpVersion, uiVersionLen);
	MEMASSERT(vpTest);

	spCallbackCtx->vpVecACharTable = vpVecCtor(vpMemCtx, sizeof(G_UINT), 100);
	MEMASSERT(spCallbackCtx->vpVecACharTable);

	spCallbackCtx->vpVecChildList = vpVecCtor(vpMemCtx, sizeof(G_UINT), 100);
	MEMASSERT(spCallbackCtx->vpVecChildList);

	spCallbackCtx->vpVecStack = vpVecCtor(vpMemCtx, sizeof(STACK_FRAME), 100);
	MEMASSERT(spCallbackCtx->vpVecStack);

	spCallbackCtx->vpVecOpcodeTable = (G_OPCODE*)vpVecCtor(vpMemCtx, sizeof(G_OPCODE), 100);
	MEMASSERT(spCallbackCtx->vpVecOpcodeTable);

	spCallbackCtx->vpVecRnmRuleTable = (G_RULE*)vpVecCtor(vpMemCtx, sizeof(G_RULE), 100);
	MEMASSERT(spCallbackCtx->vpVecRnmRuleTable);

	spCallbackCtx->vpVecRnmCharTable = (char*)vpVecCtor(vpMemCtx, sizeof(char), 100);
	MEMASSERT(spCallbackCtx->vpVecRnmCharTable);

	spCallbackCtx->vpVecRuleTable = (G_RULE*)vpVecCtor(vpMemCtx, sizeof(G_RULE), 100);
	MEMASSERT(spCallbackCtx->vpVecRuleTable);

	spCallbackCtx->vpVecUdtTable = (G_UDT*)vpVecCtor(vpMemCtx, sizeof(G_UDT), 100);
	MEMASSERT(spCallbackCtx->vpVecUdtTable);

	spCallbackCtx->vpVecRuleTableAlphabetical = (G_RULE*)vpVecCtor(vpMemCtx, sizeof(G_RULE), 100);
	MEMASSERT(spCallbackCtx->vpVecRuleTable);

	spCallbackCtx->vpVecUdtTableAlphabetical = (G_UDT*)vpVecCtor(vpMemCtx, sizeof(G_UDT), 100);
	MEMASSERT(spCallbackCtx->vpVecUdtTable);
}

// NOTE: on initializing a semantic callback function
// (APG_CALLBACK)APG_UNDEFINED - ignore this AST node.
// NULL                        - create an AST node but no callback function is associated with it
// (APG_CALLBACK)pfnFunc       - create an AST node and associate the callback function pointer "pfnFunc" with it
void vSemanticInit(APG_CALLBACK* spSemantic)
{
	APG_CALLBACK* spBeg = spSemantic;
	APG_CALLBACK* spEnd = spSemantic + RULE_COUNT_SABNFGRAMMAR;
	for(; spBeg < spEnd; spBeg++){*spBeg = NULL;}
	spSemantic[RULE_SABNFGRAMMAR_FILE] = sem_file;
	spSemantic[RULE_SABNFGRAMMAR_RULE] = sem_rule;
	spSemantic[RULE_SABNFGRAMMAR_MULTIPLEALT] = sem_multiplealt;
	spSemantic[RULE_SABNFGRAMMAR_MULTIPLECAT] = sem_multiplecat;
	spSemantic[RULE_SABNFGRAMMAR_RULENAME] = sem_rulename;
	spSemantic[RULE_SABNFGRAMMAR_OPTION] = sem_option;
	spSemantic[RULE_SABNFGRAMMAR_REP] = sem_repop;
	spSemantic[RULE_SABNFGRAMMAR_REP_MIN] = sem_repmin;
	spSemantic[RULE_SABNFGRAMMAR_REP_MAX] = sem_repmax;
	spSemantic[RULE_SABNFGRAMMAR_REP_MIN_MAX] = sem_repminmax;
	spSemantic[RULE_SABNFGRAMMAR_RNMOP] = sem_rnmop;
	spSemantic[RULE_SABNFGRAMMAR_UDT_NON_EMPTY] = sem_udtnonempty;
	spSemantic[RULE_SABNFGRAMMAR_UDT_EMPTY] = sem_udtempty;
	spSemantic[RULE_SABNFGRAMMAR_AND] = sem_andop;
	spSemantic[RULE_SABNFGRAMMAR_NOT] = sem_notop;
	spSemantic[RULE_SABNFGRAMMAR_TRGOP] = sem_trgop;
	spSemantic[RULE_SABNFGRAMMAR_BNUM] = sem_bnum;
	spSemantic[RULE_SABNFGRAMMAR_DNUM] = sem_dnum;
	spSemantic[RULE_SABNFGRAMMAR_XNUM] = sem_xnum;
	spSemantic[RULE_SABNFGRAMMAR_DMIN] = sem_trgmin;
	spSemantic[RULE_SABNFGRAMMAR_DMAX] = sem_trgmax;
	spSemantic[RULE_SABNFGRAMMAR_XMIN] = sem_trgmin;
	spSemantic[RULE_SABNFGRAMMAR_XMAX] = sem_trgmax;
	spSemantic[RULE_SABNFGRAMMAR_BMIN] = sem_trgmin;
	spSemantic[RULE_SABNFGRAMMAR_BMAX] = sem_trgmax;
	spSemantic[RULE_SABNFGRAMMAR_TBSOP] = sem_tbsop;
	spSemantic[RULE_SABNFGRAMMAR_BSTRING] = sem_tbsstring;
	spSemantic[RULE_SABNFGRAMMAR_DSTRING] = sem_tbsstring;
	spSemantic[RULE_SABNFGRAMMAR_XSTRING] = sem_tbsstring;
	spSemantic[RULE_SABNFGRAMMAR_TLSOP] = sem_tlsop;
	spSemantic[RULE_SABNFGRAMMAR_TLSCHAR] = sem_tlschar;
	spSemantic[RULE_SABNFGRAMMAR_LINEEND] = sem_lineend;
	spSemantic[RULE_SABNFGRAMMAR_LINECONTINUE] = sem_linecontinue;
	spSemantic[RULE_SABNFGRAMMAR_RULEERROR] = sem_ruleerror;
	spSemantic[RULE_SABNFGRAMMAR_PROSVAL] = sem_prosval;
	spSemantic[RULE_SABNFGRAMMAR_INCALT] = sem_incalt;
}

G_UINT uiRuleLookup(void* vpRuleTable, void* vpStrTable, char* cpName, G_UINT uiNameLen){
	G_UINT uiReturn = APG_UNDEFINED;
	G_RULE* spNext;
	char* cpRuleName;
	char* spStrTbl = (char*)vpVecFront(vpStrTable);
	G_UINT i = 0, j;
	for(i = 0; ; i++){
		spNext =  (G_RULE*)vpVecAt(vpRuleTable, i);
		if(!spNext){break;}
		cpRuleName = spStrTbl + spNext->uiNameOffset;
		if(spNext->uiNameLen == uiNameLen){
			for(j = 0; j < uiNameLen; j++){
				if(tolower(cpName[j]) != tolower(cpRuleName[j])){break;}
			}
			if(j == uiNameLen){
				uiReturn = i;
				break;
			}
		}
	}

	return uiReturn;
}

G_UINT uiUdtLookup(void* vpUdtTable, void* vpStrTable, char* cpName, G_UINT uiNameLen){
	G_UINT uiReturn = APG_UNDEFINED;
	G_UDT* spNext;
	char* cpUdtName;
	char* spStrTbl = (char*)vpVecFront(vpStrTable);
	G_UINT i = 0, j;
	for(i = 0; ; i++){
		spNext =  (G_UDT*)vpVecAt(vpUdtTable, i);
		if(!spNext){break;}
		cpUdtName = spStrTbl + spNext->uiNameOffset;
		if(spNext->uiNameLen == uiNameLen){
			for(j = 0; j < uiNameLen; j++){
				if(tolower(cpName[j]) != tolower(cpUdtName[j])){break;}
			}
			if(j == uiNameLen){
				uiReturn = i;
				break;
			}
		}
	}

	return uiReturn;
}

STACK_FRAME* spPushOp(CALLBACK_CTX* spCallbackCtx, G_UINT uiType){
	STACK_FRAME* spFrame;
	STACK_FRAME* spParent;
	G_OPCODE* spOp;
	G_UINT uiThisFrameIndex = uiVecSize(spCallbackCtx->vpVecStack);

	// push and initialize a stack frame
	spFrame = (STACK_FRAME*)vpVecPush(spCallbackCtx->vpVecStack, NULL);
	MEMASSERT(spFrame);
	memset((void*)spFrame, 0, sizeof(STACK_FRAME));
	spFrame->uiThisFrameIndex = uiThisFrameIndex;
	MEMASSERT(uiThisFrameIndex > 0);
	spFrame->uiParentFrameIndex = uiThisFrameIndex - 1;
	spFrame->uiOpType = uiType;
	spFrame->uiInfinite = APG_UNDEFINED;

	// get the parent frame
	spParent = (STACK_FRAME*)vpVecAt(spCallbackCtx->vpVecStack, spFrame->uiParentFrameIndex);
	MEMASSERT(spParent);

	// push and initialize an opcode
	spFrame->uiThisOpcodeIndex = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
	spOp = (G_OPCODE*)vpVecPush(spCallbackCtx->vpVecOpcodeTable, NULL);
	MEMASSERT(spOp);
	memset((void*)spOp, 0, sizeof(*spOp));
	spOp->uiGrammarLineNo = spCallbackCtx->uiLineNo;
	memset((void*)spOp, 0, sizeof(spOp));
	if(spParent->vpVecAltChild){
	  // register with parent alt as alternate child
	  void* vpTest = vpVecPush(spParent->vpVecAltChild, (void*)&spFrame->uiThisOpcodeIndex);
	  MEMASSERT(vpTest);
	}
	if(spParent->vpVecCatChild){
	  // register with parent cat as concatenated child
	  void* vpTest = vpVecPush(spParent->vpVecCatChild, (void*)&spFrame->uiThisOpcodeIndex);
	  MEMASSERT(vpTest);
	}
	switch(uiType){
	case G_TYPE_ALT:
	{
		spOp->uiType = G_TYPE_ALT;
		spFrame->vpVecAltChild = vpVecCtor(spCallbackCtx->vpMemCtx, sizeof(G_UINT), 100);
		MEMASSERT(spFrame->vpVecAltChild);
	}
		break;
	case G_TYPE_CAT:
	{
		spOp->uiType = G_TYPE_CAT;
		spFrame->vpVecCatChild = vpVecCtor(spCallbackCtx->vpMemCtx, sizeof(G_UINT), 100);
		MEMASSERT(spFrame->vpVecCatChild);
	}
		break;
	case G_TYPE_REP:
	{
		spOp->uiType = G_TYPE_REP;
		spOp->sOpType.sRep.uiChildOffset = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
		spFrame->uiInfinite = (G_UINT)-1;
		spFrame->uiRepMin = 0;
		spFrame->uiRepMax = (G_UINT)spFrame->uiInfinite;
	}
		break;
	case G_TYPE_AND:
	{
		spOp->uiType = G_TYPE_AND;
		spOp->sOpType.sAnd.uiChildOffset = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
	}
		break;
	case G_TYPE_NOT:
	{
		spOp->uiType = G_TYPE_NOT;
		spOp->sOpType.sNot.uiChildOffset = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
	}
		break;
	case G_TYPE_RNM:
	{
		spOp->uiType = G_TYPE_RNM;
	}
		break;
	case G_TYPE_UDT:
	{
		spOp->uiType = G_TYPE_UDT;
	}
		break;
	case G_TYPE_TRG:
	{
		spOp->uiType = G_TYPE_TRG;
	}
		break;
	case G_TYPE_TBS:
	{
		spOp->uiType = G_TYPE_TBS;
		spFrame->vpVecString = vpVecCtor(spCallbackCtx->vpMemCtx, sizeof(G_UINT), 100);
		MEMASSERT(spFrame->vpVecString);
	}
		break;
	case G_TYPE_TLS:
	{
		spOp->uiType = G_TYPE_TLS;
		spFrame->vpVecString = vpVecCtor(spCallbackCtx->vpMemCtx, sizeof(G_UINT), 100);
		MEMASSERT(spFrame->vpVecString);
	}
		break;
	default:
		MSGASSERT(APG_FALSE, "unknown operator type");
		break;
	}
	return spFrame;
}

void vPopOp(APG_CBDATA* spData, G_UINT uiType){
	CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	G_OPCODE* spOp;
	STACK_FRAME* spParent;

	// get the current frame
	STACK_FRAME* spFrame = vpVecPop(spCallbackCtx->vpVecStack);
	MEMASSERT(spFrame);
	MSGASSERT(spFrame->uiOpType == uiType, "vPopOp: unexpected operator type");

	// get the parent
	spParent = (STACK_FRAME*)vpVecAt(spCallbackCtx->vpVecStack, spFrame->uiParentFrameIndex);
	MEMASSERT(spParent);

	// get the current opcode
	spOp = (G_OPCODE*)vpVecAt(spCallbackCtx->vpVecOpcodeTable, spFrame->uiThisOpcodeIndex);
	MEMASSERT(spOp);
	spOp->uiGrammarPhraseLength = spData->uiPhraseLength;
	spOp->uiGrammarPhraseOffset = spData->uiPhraseOffset;
	switch(uiType){
	case G_TYPE_ALT:
	{
		G_UINT uiChildOffset, uiChildCount, i;
		G_UINT* g_uipChildList;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type ALT");

		// copy child index list to vpVecAltChildList
		g_uipChildList = (G_UINT*)vpVecFront(spFrame->vpVecAltChild);
		MEMASSERT(g_uipChildList);
		uiChildCount = uiVecSize(spFrame->vpVecAltChild);
		uiChildOffset = uiVecSize(spCallbackCtx->vpVecChildList);
		for(i = 0; i < uiChildCount; i++){
		  G_UINT uiChild;
		  void* vpTest;
		  vpTest = vpVecAt(spFrame->vpVecAltChild, i);
		  MEMASSERT(vpTest);
		  uiChild = *((G_UINT*)vpTest);
		  vpTest = vpVecPush(spCallbackCtx->vpVecChildList, (void*)&uiChild);
		  MEMASSERT(vpTest);
		}

		// finish setting the opcode
		spOp->sOpType.sAlt.uiChildCount = uiChildCount;
		spOp->sOpType.sAlt.uiChildListOffset = uiChildOffset;

		// clean up resources
		vVecDtor(spFrame->vpVecAltChild);
	}
		break;
	case G_TYPE_CAT:
	{
		G_UINT uiChildOffset, uiChildCount, i;
		G_UINT* g_uipChildList;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type CAT");

		// copy child index list to vpVecAltChildList
		g_uipChildList = (G_UINT*)vpVecFront(spFrame->vpVecCatChild);
		MEMASSERT(g_uipChildList);
		uiChildCount = uiVecSize(spFrame->vpVecCatChild);
		uiChildOffset = uiVecSize(spCallbackCtx->vpVecChildList);
		for(i = 0; i < uiChildCount; i++){
		  G_UINT uiChild;
		  void* vpTest;
		  vpTest = vpVecAt(spFrame->vpVecCatChild, i);
		  MEMASSERT(vpTest);
		  uiChild = *((G_UINT*)vpTest);
		  vpTest = vpVecPush(spCallbackCtx->vpVecChildList, (void*)&uiChild);
		  MEMASSERT(vpTest);
		}

		// finish setting the opcode
		spOp->sOpType.sCat.uiChildCount = uiChildCount;
		spOp->sOpType.sCat.uiChildListOffset = uiChildOffset;

		// clean up resources
		vVecDtor(spFrame->vpVecCatChild);
	}
		break;
	case G_TYPE_REP:
	{
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type REP");
		spOp->sOpType.sRep.uiMin = spFrame->uiRepMin;
		spOp->sOpType.sRep.uiMax = spFrame->uiRepMax;
		if(spOp->sOpType.sRep.uiMin > spOp->sOpType.sRep.uiMax){
		  // report error
		  sprintf(g_cpBuffer, "rule: %lu: line: %lu: REP %lu*%lu: min must be <= max",
				  (G_UINT)spCallbackCtx->uiRuleDefinitionNo,
				  (unsigned long int)spOp->uiGrammarLineNo+1, (unsigned long int)spOp->sOpType.sRep.uiMin, (unsigned long int)spOp->sOpType.sRep.uiMax);
		  vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
//		  MSGASSERT(APG_FALSE, g_cpBuffer);
		} else if(spOp->sOpType.sRep.uiMin == spOp->sOpType.sRep.uiMax){
		  if(spOp->sOpType.sRep.uiMin == 0){
			  // 0*0 empty string warning
			  sprintf(g_cpBuffer, "rule: %lu: line: %lu: REP: 0 or 0*0 not accepted as empty string: use literal string \"\" instead",
					  (G_UINT)spCallbackCtx->uiRuleDefinitionNo,
					  (unsigned long int)spOp->uiGrammarLineNo+1);
			  vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
		  }
		  if(spOp->sOpType.sRep.uiMin == 1){
			  // omit 1*1 warning
			  sprintf(g_cpBuffer, "rule: %lu: line: %lu: redundant REP 1*1 omitted",
					  (G_UINT)spCallbackCtx->uiRuleDefinitionNo,
					  (unsigned long int)spOp->uiGrammarLineNo+1);
			  vErrorsReport(spCallbackCtx->vpWarnCtx, g_cpBuffer);
		  }
		}
	}
		break;
	case G_TYPE_AND:
	{
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type AND");
	}
		break;
	case G_TYPE_NOT:
	{
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type NOT");
	}
		break;
	case G_TYPE_RNM:
	{
		G_RULE* spRnm = NULL;
		G_UINT uiRnmIndex;
		G_UINT i;
		const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type RNM");
		uiRnmIndex = uiRuleLookup(spCallbackCtx->vpVecRnmRuleTable, spCallbackCtx->vpVecRnmCharTable,
				(char*)acpPhrase, spData->uiPhraseLength);
		if(uiRnmIndex == APG_UNDEFINED){
			char* cpStr;
			uiRnmIndex = uiVecSize(spCallbackCtx->vpVecRnmRuleTable);
			spRnm = (G_RULE*)vpVecPush(spCallbackCtx->vpVecRnmRuleTable, NULL);
			MEMASSERT(spRnm);
			spRnm->uiNameOffset = uiVecSize(spCallbackCtx->vpVecRnmCharTable);
			spRnm->uiNameLen = spData->uiPhraseLength;
			spRnm->uiRuleIndex = uiRnmIndex;

			// convert rule name from achar to char and put it in the (char) string table
			cpStr = (char*)vpVecPushn(spCallbackCtx->vpVecRnmCharTable, NULL, spData->uiPhraseLength + 1);
			MEMASSERT(cpStr);
			for(i = 0; i < spData->uiPhraseLength; i++){
				cpStr[i] = (char)acpPhrase[i];
			}
			cpStr[spData->uiPhraseLength] = 0;
		}
		spOp->sOpType.sRnm.uiChildOffset = APG_UNDEFINED;
		spOp->sOpType.sRnm.uiRuleIndex = uiRnmIndex;
	}
		break;
	case G_TYPE_UDT:
	{
		G_UDT* spUdt = NULL;
		G_UINT uiUdtIndex;
		const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
		G_UINT i;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type UDT");
		uiUdtIndex = uiUdtLookup(spCallbackCtx->vpVecUdtTable, spCallbackCtx->vpVecCharTable,
				(char*)acpPhrase, spData->uiPhraseLength);
		if(uiUdtIndex == APG_UNDEFINED){
			char* cpStr;
			// push a UDT struct on the list
			uiUdtIndex = (G_UINT)uiVecSize(spCallbackCtx->vpVecUdtTable);
			spUdt = (G_UDT*)vpVecPush(spCallbackCtx->vpVecUdtTable, NULL);
			spUdt->uiNameOffset = uiVecSize(spCallbackCtx->vpVecCharTable);
			spUdt->uiNameLen = spData->uiPhraseLength;
			spUdt->uiUdtIndex = uiUdtIndex;
			spUdt->uiEmpty = spFrame->uiUdtEmpty;

			// convert rule name from achar to char and put it in the (char) string table
			cpStr = (char*)vpVecPushn(spCallbackCtx->vpVecCharTable, NULL, spData->uiPhraseLength + 1);
			MEMASSERT(cpStr);
			for(i = 0; i < spData->uiPhraseLength; i++){
				cpStr[i] = (char)acpPhrase[i];
			}
			cpStr[spData->uiPhraseLength] = 0;
		}
		spOp->sOpType.sUdt.uiUdtIndex= uiUdtIndex;
		spOp->sOpType.sUdt.uiEmpty = spFrame->uiUdtEmpty;
	}
		break;
	case G_TYPE_TRG:
	{
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type TRG");
		spOp->sOpType.sTrg.uiMin = spFrame->uiTrgMin;
		spOp->sOpType.sTrg.uiMax = spFrame->uiTrgMax;
		if(spOp->sOpType.sTrg.uiMin < spCallbackCtx->uiACharMin){spCallbackCtx->uiACharMin = spOp->sOpType.sTrg.uiMin;}
		if(spOp->sOpType.sTrg.uiMax > spCallbackCtx->uiACharMax){spCallbackCtx->uiACharMax = spOp->sOpType.sTrg.uiMax;}
	}
		break;
	case G_TYPE_TBS:
	{
		G_UINT* g_uipString;
		void* vpTest;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type TBS");
		// move the temp string to the string table
		g_uipString = (G_UINT*)vpVecFront(spFrame->vpVecString);
		MEMASSERT(g_uipString);
		spOp->sOpType.sTbs.uiOffset = uiVecSize(spCallbackCtx->vpVecACharTable);
		spOp->sOpType.sTbs.uiLen = uiVecSize(spFrame->vpVecString);
		vpTest = vpVecPushn(spCallbackCtx->vpVecACharTable, (void*)g_uipString, spOp->sOpType.sTbs.uiLen);
		MEMASSERT(vpTest);
		vVecDtor(spFrame->vpVecString);
	}
		break;
	case G_TYPE_TLS:
	{
		G_UINT* g_uipString;
		void* vpTest;
		MSGASSERT(spOp->uiType == uiType, "vPopOp: expected operator type TLS");
		// move the temp string to the string table
		spOp->sOpType.sTls.uiOffset = uiVecSize(spCallbackCtx->vpVecACharTable);
		spOp->sOpType.sTls.uiLen = uiVecSize(spFrame->vpVecString);
		if(spOp->sOpType.sTls.uiLen > 0){
			g_uipString = (G_UINT*)vpVecFront(spFrame->vpVecString);
			MEMASSERT(g_uipString);
			vpTest = vpVecPushn(spCallbackCtx->vpVecACharTable, (void*)g_uipString, spOp->sOpType.sTbs.uiLen);
			MEMASSERT(vpTest);
		}
		vVecDtor(spFrame->vpVecString);
	}
		break;
	default:
		MSGASSERT(APG_FALSE, "vPopOp: unknown operator type");
		break;
	}
	memset((void*)spFrame, 0, sizeof(*spFrame));
}

G_UINT uidTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uipNum){
	G_UINT uiRet = APG_FALSE;
	G_UINT uiResult = 0;
	G_UINT uiBase = 10;
	G_UINT i, uiDigit;
	char cChar;
	if(cpString && uiLen){
		for(i = 0; i < uiLen; i++){
			cChar = cpString[i];
			if(cChar < '0' || cChar > '9'){break;}
			uiDigit = (G_UINT)(cChar - '0');
			if(uiResult > uiMax / uiBase){break;}
			uiResult *= uiBase;
			if(uiResult > uiMax - uiDigit){break;}
			uiResult += uiDigit;
		}
		if(i == uiLen){
			uiRet = APG_TRUE;
			*uipNum = uiResult;
		}
	}
	return APG_UNDEFINED;
}

G_UINT uixTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uipNum){
	G_UINT uiRet = APG_FALSE;
	G_UINT uiResult = 0;
	G_UINT uiBase = 16;
	G_UINT i, uiDigit;
	char cChar;
	if(cpString && uiLen){
		for(i = 0; i < uiLen; i++){
			cChar = cpString[i];
			if(cChar >= '0' && cChar <='9'){
				uiDigit = (G_UINT)(cChar - '0');
			} else if(cChar >= 'a' && cChar <= 'f'){
				uiDigit = 10 + (G_UINT)(cChar - 'a');
			} else if(cChar >= 'A' && cChar <= 'F'){
				uiDigit = 10 + (G_UINT)(cChar - 'A');
			} else{break;}
			if(uiResult > uiMax / uiBase){break;}
			uiResult *= uiBase;
			if(uiResult > uiMax - uiDigit){break;}
			uiResult += uiDigit;
		}
		if(i == uiLen){
			uiRet = APG_TRUE;
			*uipNum = uiResult;
		}
	}
	return APG_UNDEFINED;
}

G_UINT uibTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uipNum){
	G_UINT uiRet = APG_FALSE;
	G_UINT uiResult = 0;
	G_UINT uiBase = 2;
	G_UINT i, uiDigit;
	char cChar;
	if(cpString && uiLen){
		for(i = 0; i < uiLen; i++){
			cChar = cpString[i];
			if(cChar >= '0' && cChar <='1'){
				uiDigit = (G_UINT)(cChar - '0');
			} else{break;}
			if(uiResult > uiMax / uiBase){break;}
			uiResult *= uiBase;
			if(uiResult > uiMax - uiDigit){break;}
			uiResult += uiDigit;
		}
		if(i == uiLen){
			uiRet = APG_TRUE;
			*uipNum = uiResult;
		}
	}
	return APG_UNDEFINED;
}

void vProcessRnmOpcodes(CALLBACK_CTX* spCallbackCtx){
	char* cpStringTable;
	G_RULE* spRules;
	G_UINT uiRuleIndex;
	G_UINT uiRuleCount;
	G_RULE* spRnmRules;
	G_RULE* spRnmRule;
	char* cpRnmStringTable;
	char* cpRnmRuleName;
	G_UINT uiUdtCount;
	G_UDT* spUdtUdts;
	char* cpUdtStringTable;
	G_OPCODE* spOps;
	G_OPCODE* spOp;
	G_UINT i, uiOpCount;

	cpStringTable = (char*)vpVecFront(spCallbackCtx->vpVecCharTable);
	MEMASSERT(cpStringTable);

	spRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRuleTable);
	MEMASSERT(spRules);
	uiRuleCount = (G_UINT)uiVecSize(spCallbackCtx->vpVecRuleTable);
	spRnmRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRnmRuleTable);
	cpRnmStringTable = (char*)vpVecFront(spCallbackCtx->vpVecRnmCharTable);

	uiUdtCount = (G_UINT)uiVecSize(spCallbackCtx->vpVecUdtTable);
	spUdtUdts = (G_UDT*)vpVecFront(spCallbackCtx->vpVecUdtTable);
	cpUdtStringTable = (char*)vpVecFront(spCallbackCtx->vpVecCharTable);

	spOps = (G_OPCODE*)vpVecFront(spCallbackCtx->vpVecOpcodeTable);
	MEMASSERT(spOps);
	uiOpCount = uiVecSize(spCallbackCtx->vpVecOpcodeTable);
	for(i = 0; i < uiOpCount; i++){
		spOp = spOps + i;
		if(spOp->uiType == G_TYPE_RNM){
			spRnmRule = spRnmRules + spOp->sOpType.sRnm.uiRuleIndex;
			cpRnmRuleName = cpRnmStringTable + spRnmRule->uiNameOffset;
			uiRuleIndex = uiRuleLookup(spCallbackCtx->vpVecRuleTable, spCallbackCtx->vpVecCharTable,
					cpRnmRuleName, spRnmRule->uiNameLen);
			if(uiRuleIndex == APG_UNDEFINED){
				// report error
				sprintf(g_cpBuffer, "line: %lu: char: %lu: RNM operator: %s: used but not defined",
						(unsigned long int)spOp->uiGrammarLineNo, (unsigned long int)spOp->uiGrammarPhraseOffset,
						cpRnmRuleName);
				vErrorsReport(spCallbackCtx->vpErrCtx, g_cpBuffer);
			} else{
				// translate RNM op
				spOp->sOpType.sRnm.uiRuleIndex = uiRuleIndex;
			}
		}
	}
}

void vGeneratorDisplayRules(CALLBACK_CTX* spCallbackCtx){
	G_UINT i;
	char* cpStringTable;
	G_RULE* spRules;
	G_UDT* spUdts;
	G_UINT uiRuleCount, uiUdtCount;
	if(spCallbackCtx){
		cpStringTable = (char*)vpVecFront(spCallbackCtx->vpVecCharTable);
		MEMASSERT(cpStringTable);
		spRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRuleTableAlphabetical);
		MEMASSERT(spRules);
		uiRuleCount = uiVecSize(spCallbackCtx->vpVecRuleTableAlphabetical);
		printf("index : rulename\n");
		for(i = 0; i < uiRuleCount; i++){
			printf("%5lu : %s\n",
					(unsigned long int)spRules[i].uiGrammarLineNo, (cpStringTable + spRules[i].uiNameOffset));
//					(unsigned long int)spRules[i].uiRuleIndex, (unsigned long int)spRules[i].uiChildCount);
		}
		uiUdtCount = uiVecSize(spCallbackCtx->vpVecUdtTableAlphabetical);
		if(uiUdtCount){
			spUdts = (G_UDT*)vpVecFront(spCallbackCtx->vpVecUdtTableAlphabetical);
			MEMASSERT(spUdts);
			printf("\n");
			printf("   : udts\n");
			for(i = 0; i < uiUdtCount; i++){
				printf("   : %s: index: %lu\n",
						(cpStringTable + spUdts[i].uiNameOffset), (unsigned long int)spUdts[i].uiUdtIndex);
			}
		}
	}
}
void vDumpRnm(G_RNMOP* spOp, G_RULE* spRules, char* cpStringTable){
	G_RULE* spRule = spRules + spOp->uiRuleIndex;
	char* cpName = cpStringTable + spRule->uiNameOffset;
	printf("RNM: %s: index: %lu\n", cpName, (unsigned long int)spRule->uiRuleIndex);
}
void vDumpUdt(G_UDTOP* spOp, G_UDT* spUdts, char* cpStringTable){
	G_UDT* spUdt = spUdts + spOp->uiUdtIndex;
	char* cpName = cpStringTable + spUdt->uiNameOffset;
	printf("UDT: %s: index: %lu\n", cpName, (unsigned long int)spUdt->uiUdtIndex);
}
void vDumpAlt(G_ALTOP* spOp, G_UINT* uipChildList){
	G_UINT i;
	printf("ALT: opcodes(%lu): ", (unsigned long int)spOp->uiChildCount);
	for(i = 0; i < spOp->uiChildCount; i++){
		if(i == spOp->uiChildCount -1){
			printf("%lu ", (G_UINT)uipChildList[i + spOp->uiChildListOffset]);
		} else{
			printf("%lu, ", (G_UINT)uipChildList[i + spOp->uiChildListOffset]);
		}
	}
	printf("\n");
}
void vDumpCat(G_CATOP* spOp, G_UINT* uipChildList){
	G_UINT i;
	printf("CAT: opcodes(%lu): ", (unsigned long int)spOp->uiChildCount);
	for(i = 0; i < spOp->uiChildCount; i++){
		if(i == spOp->uiChildCount -1){
			printf("%lu ", (G_UINT)uipChildList[i + spOp->uiChildListOffset]);
		} else{
			printf("%lu, ", (G_UINT)uipChildList[i + spOp->uiChildListOffset]);
		}
	}
	printf("\n");
}
void vDumpRep(G_REPOP* spOp){
	if(spOp->uiMax == APG_INFINITE){
		printf("REP: min: %lu: max: inf\n",	(G_UINT)spOp->uiMin);
	} else{
		printf("REP: min: %lu: max: %lu\n",	(G_UINT)spOp->uiMin, (G_UINT)spOp->uiMax);
	}
}
void vDumpAnd(G_ANDOP* spOp){
//	printf("AND: child offset: %lu\n", spOp->uiChildOffset);
	printf("AND:\n");
}
void vDumpNot(G_NOTOP* spOp){
//	printf("NOT: child offset: %lu\n", spOp->uiChildOffset);
	printf("NOT:\n");
}
void vDumpTrg(G_TRGOP* spOp){
	printf("TRG: min: %lu: max: %lu\n", (unsigned long int)spOp->uiMin, (unsigned long int)spOp->uiMax);
}
void vDumpTbs(G_TBSOP* spOp, G_UINT* uipCharTable){
	G_UINT i;
	printf("TBS: len: %lu: chars: ", (unsigned long int)spOp->uiLen);
	for(i = 0; i < spOp->uiLen; i++){
		if(i == spOp->uiLen - 1){
			printf("%lu ", (G_UINT)uipCharTable[i + spOp->uiOffset]);
		} else{
			printf("%lu, ", (G_UINT)uipCharTable[i + spOp->uiOffset]);
		}
	}
	printf("\n");
}
void vDumpTls(G_TLSOP* spOp, G_UINT* uipCharTable){
	G_UINT i;
	printf("TLS: len: %lu: chars: ", (unsigned long int)spOp->uiLen);
	for(i = 0; i < spOp->uiLen; i++){
		if(i == spOp->uiLen - 1){
			printf("%lu ", (G_UINT)uipCharTable[i + spOp->uiOffset]);
		} else{
			printf("%lu, ", (G_UINT)uipCharTable[i + spOp->uiOffset]);
		}
	}
	printf("\n");
}
void vGeneratorDisplayOpcodes(CALLBACK_CTX* spCallbackCtx){
	char* cpStringTable;
	G_UINT* uipACharTable;
	G_RULE* spRules;
	G_RULE* spRule;
	G_UINT uiRuleCount, uiRuleOpsCount;
	char* cpRuleName;
	G_UDT* spUdts;
	G_RULE* spRnmRules;
	char* cpRnmStringTable;
	G_OPCODE* spOps;
	G_OPCODE* spOp;
	G_UINT uiType;
	G_UINT* g_uipAltChildList;
	G_UINT* g_uipCatChildList;
	G_UINT i, j;

	cpStringTable = (char*)vpVecFront(spCallbackCtx->vpVecCharTable);
	MEMASSERT(cpStringTable);

	uipACharTable = (G_UINT*)vpVecFront(spCallbackCtx->vpVecACharTable);

	uiRuleCount = (G_UINT)uiVecSize(spCallbackCtx->vpVecRuleTable);
	spRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRuleTable);
	MEMASSERT(spRules);

	spUdts = (G_UDT*)vpVecFront(spCallbackCtx->vpVecUdtTable);

	spRnmRules = (G_RULE*)vpVecFront(spCallbackCtx->vpVecRnmRuleTable);

	cpRnmStringTable = (char*)vpVecFront(spCallbackCtx->vpVecRnmCharTable);

	spOps = (G_OPCODE*)vpVecFront(spCallbackCtx->vpVecOpcodeTable);
	MEMASSERT(spOps);

	g_uipAltChildList = (G_UINT*)vpVecFront(spCallbackCtx->vpVecChildList);

	g_uipCatChildList = (G_UINT*)vpVecFront(spCallbackCtx->vpVecChildList);

	printf("%5lu: total opcodes\n", (G_UINT)uiVecSize(spCallbackCtx->vpVecOpcodeTable));
	printf("%5lu: character code min\n", (G_UINT)spCallbackCtx->uiACharMin);
	printf("%5lu: character code max\n", (G_UINT)spCallbackCtx->uiACharMax);
	for(i = 0; i < uiRuleCount; i++){
		spRule = spRules + i;
		uiRuleOpsCount = spRule->uiChildCount;
		cpRuleName = cpStringTable + spRule->uiNameOffset;
		printf("\n%3lu: %s: index: %lu: opcodes: %lu\n",
				(G_UINT)spRule->uiGrammarLineNo, cpRuleName, (G_UINT)spRule->uiRuleIndex, (G_UINT)spRule->uiChildCount);
		for(j = 0; j < uiRuleOpsCount; j++){
			G_UINT uiOffset = j + spRule->uiChildOffset;
			spOp = spOps + uiOffset;
			uiType = spOp->uiType;
			printf("    %3lu: %lu: ", (G_UINT)spOp->uiGrammarLineNo, (G_UINT)uiOffset);
			switch(spOp->uiType){
			case G_TYPE_RNM: vDumpRnm(&spOp->sOpType.sRnm, spRules, cpStringTable); break;
			case G_TYPE_UDT: vDumpUdt(&spOp->sOpType.sUdt, spUdts, cpStringTable); break;
			case G_TYPE_REP: vDumpRep(&spOp->sOpType.sRep); break;
			case G_TYPE_ALT: vDumpAlt(&spOp->sOpType.sAlt, g_uipAltChildList); break;
			case G_TYPE_CAT: vDumpCat(&spOp->sOpType.sCat, g_uipCatChildList); break;
			case G_TYPE_AND: vDumpAnd(&spOp->sOpType.sAnd); break;
			case G_TYPE_NOT: vDumpNot(&spOp->sOpType.sNot); break;
			case G_TYPE_TRG: vDumpTrg(&spOp->sOpType.sTrg); break;
			case G_TYPE_TBS: vDumpTbs(&spOp->sOpType.sTbs, uipACharTable); break;
			case G_TYPE_TLS: vDumpTls(&spOp->sOpType.sTls, uipACharTable); break;
			default: MSGASSERT(APG_FALSE, "unknown operator type"); break;
			}
		}
	}
}
