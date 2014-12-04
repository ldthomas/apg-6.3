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

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

typedef struct{
	G_UINT uiRuleDefinitionNo;
	G_UINT uiLineNo;
	G_UINT uiACharMin;
	G_UINT uiACharMax;
	G_UINT uiUintMax;
	PFN_ALERT	pfnAlertHandler;
	void* vpLineCatalogCtx;
	void* vpErrCtx;
	void* vpWarnCtx;
	void* vpVecCharTable;
	void* vpVecACharTable;
	void* vpVecRuleTable;
	void* vpVecUdtTable;
	void* vpVecRuleTableAlphabetical;
	void* vpVecUdtTableAlphabetical;
	void* vpVecRnmRuleTable;
	void* vpVecRnmCharTable;
	void* vpVecOpcodeTable;
	void* vpVecChildList;
	void* vpVecStack;
	void* vpMemCtx;
} CALLBACK_CTX;

typedef struct{
	// frame info
	G_UINT uiOpType;
	G_UINT uiThisFrameIndex;
	G_UINT uiParentFrameIndex;
	G_UINT uiThisOpcodeIndex;
	G_UINT uiNumber;
	G_UINT uiInfinite;

	// rule info
	G_UINT uiRuleIndex;
	G_UINT uiUdtEmpty;

	// alternation info
	void* vpVecAltChild;

	// concatenation info
	void* vpVecCatChild;

	// repetition info
	G_UINT uiRepMin;
	G_UINT uiRepMax;

	// trg info
	G_UINT uiTrgMin;
	G_UINT uiTrgMax;

	// tbs, tls info
	void* vpVecString;
} STACK_FRAME;

STACK_FRAME* spPushOp(CALLBACK_CTX* spCtx, G_UINT uiType);
void vPopOp(APG_CBDATA* spData, G_UINT uiType);
void vCallbackInit(void* vpMemCtx, CALLBACK_CTX* spCallbackCtx);
void vSemanticInit(APG_CALLBACK* spSemantic);
G_UINT uiRuleLookup(void* vpRuleTable, void* vpStrTable, char* cpRuleName, G_UINT uiNameLen);
G_UINT uiUdtLookup(void* vpUdtTable, void* vpStrTable, char* cpUdtName, G_UINT uiNameLen);
void vProcessRnmOpcodes(CALLBACK_CTX* spCtx);
void vGeneratorDisplayRules(CALLBACK_CTX* spCtx);
void vGeneratorDisplayOpcodes(CALLBACK_CTX* spCtx);
G_UINT uibTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uiNum);
G_UINT uidTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uiNum);
G_UINT uixTranslateDigits(G_UINT uiMax, char* cpString, G_UINT uiLen, G_UINT *uiNum);

#endif /* CALLBACKS_H_ */
