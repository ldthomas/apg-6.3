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

#ifndef GENERATOR_H_
#define GENERATOR_H_
#include "Apg.h"
#include "ApgUtilities.h"
#include "CommandLine.h"
#include "Callbacks.h"

void vMainAlertHandler(unsigned int uiLine, const char* cpFile);
void vMsgAssert(char* cpMsg, unsigned int uiLine, char* cpFile);

#define GASSERT(cond) if(!(cond)){vMainAlertHandler(__LINE__, __FILE__);}
#define MSGASSERT(cond, msg) if(!(cond)){vMsgAssert((msg), __LINE__, __FILE__);}

typedef struct{
	G_UINT uiACharMin;
	G_UINT uiACharMax;
	G_UINT uiRuleCount;
	G_UINT uiUdtCount;
	G_UINT uiOpcodeCount;
	G_UINT uiAlt;
	G_UINT uiAltChildren;
	G_UINT uiCat;
	G_UINT uiCatChildren;
	G_UINT uiRep;
	G_UINT uiRnm;
	G_UINT uiUdt;
	G_UINT uiAnd;
	G_UINT uiNot;
	G_UINT uiTrg;
	G_UINT uiTbs;
	G_UINT uiTls;
}GRAMMAR_METRICS;

void vGrammarMetrics(CALLBACK_CTX* spCtx, GRAMMAR_METRICS* spMetrics);
void vDisplayGrammarMetrics(GRAMMAR_METRICS* spMetrics);
void vGenerateCHeader(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpGrammar, char* cpFileName, apg_uint uiFileNameLen);
void vGenerateCSource(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpFileName, apg_uint uiFileNameLen);
void vGenerateCppHeader(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpGrammar, char* cpFileName, apg_uint uiFileNameLen);
void vGenerateCppSource(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpFileName, apg_uint uiFileNameLen);

// bootstrap equivalents
void bs_vGrammarMetrics(CALLBACK_CTX* spCtx, GRAMMAR_METRICS* spMetrics);
void bs_vDisplayGrammarMetrics(GRAMMAR_METRICS* spMetrics);
void bs_vGenerateCHeader(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpGrammar);
void bs_vGenerateCSource(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName);

//-----------------------------------------------------------------------------
//-----ATTRIBUTES--------------------------------------------------------------
#define ATTRS_YES "t"
#define ATTRS_NO "f"
#define ATTRS_FATAL "x"
#define ATTRS_UNKNOWN "-"

#define N_RECURSIVE		0	// non-recursive
#define R_RECURSIVE		1	// recursive (but not mutually-recursive)
#define MR_RECURSIVE	2	// mutually-recursive
#define NMR_RECURSIVE	3	// N_RECURSIVE but refers to MR_RECURSIVE
#define RMR_RECURSIVE	4	// R_RECURSIVE but refers to MR_RECURSIVE

typedef struct{
	// recursive
	G_UINT		uiLeft;
	G_UINT		uiNested;
	G_UINT		uiRight;
	G_UINT		uiCyclic;

	// non-recursive
	G_UINT		uiFinite;
	G_UINT		uiEmpty;

	// admin
	char*			cpRuleName;
	G_UINT*		uipRefCount;
	G_UINT*		uipIsScanned;
	G_UINT		uiRecursiveType;
	G_UINT		uiIsOpen;
	G_UINT 		uiIsComplete;
} ATTRS;

typedef struct{
	G_UINT	uiRuleIndex;
	char*		cpRuleName;
}QSORT;

typedef struct{
	// grammar info
	G_UINT 		uiRuleCount;
	G_RULE* 		spRules;
	G_OPCODE* 		spOpcodes;
	G_UINT*         uipChildList;

	// attributes
	ATTRS*			spAttrs;

	// computational helper info
	void* 			vpMemCtx;
	void*			vpFrameCtx;
	void*			vpRuleAttrs;
	G_RULE* 		spStartRule;
	G_UINT 		uiStartRuleIndex;
	QSORT*			spQsort;
	G_UINT 		uiTreeDepth;
} ATTRS_CTX;
typedef void (*PFN_OPRNM)(ATTRS_CTX* spCtx, G_UINT uiRuleIndex, ATTRS* spAttrs);

// basics
void* vpAttrsCtor(CALLBACK_CTX* spCtx);
void vAttrsDtor(void* vpAttrsCtx);
void vAttrsClear(ATTRS* spAttrs, G_UINT ulRuleCount);
void vAttrsCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs);
void vAttrsRecursiveCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs);
void vAttrsNonRecursiveCopy(ATTRS* spDstAttrs, ATTRS* spSrcAttrs);

// computing attributes
G_UINT uiAttributes(void* vpCtx);
void vRuleDependencies(ATTRS_CTX* spCtx);
void vNonRecursiveAttributes(ATTRS_CTX* spCtx);
void vRecursiveAttributes(ATTRS_CTX* spCtx);

// frame component
typedef struct{
	G_UINT uiRuleCount;
	G_UINT uiFrameCount;
	ATTRS* spAttrs;
	void* vpVecFrames;
	void* vpMemCtx;
}FRAME_CTX;
void* vpFrameCtor(void* vpMemCtx, G_UINT uiRuleCount, ATTRS* spAttrs);
void vFrameDtor(void* vpCtx);
ATTRS* spFramePush(void* vpCtx);
ATTRS* spFramePop(void* vpCtx);
ATTRS* spFramePeek(void* vpCtx);
ATTRS* spFramePrev(void* vpCtx);

// displaying attributes
void vDisplayRuleDependencyTypes(ATTRS_CTX* spCtx);
void vDisplayAttrsLine(ATTRS* spAttrs, char* cpName);
void vDisplayAttrs(void* vpCtx);
void vAttrsTrace(ATTRS_CTX* spCtx, G_UINT uiWhich, G_UINT uiRuleIndex, G_OPCODE* spOpcode, ATTRS* spAttrs);
//#define ATTRS_TRACE(x, w, i, o, a) vAttrsTrace((x), (w), (i), (o), (a));
#define ATTRS_TRACE(x, w, i, o, a)
#define WHICH_OP ((G_UINT)-1)
#define WHICH_RULE ((G_UINT)1)
#define WHICH_MR_RULE ((G_UINT)2)

typedef struct
{
	  void* vpMemCtx;
	  void* vpVecMsgs;
	  void* vpVecMsgIndex;
	  G_UINT uiIterNext;
	  PFN_ALERT pfnAlertHandler;
} ERRORS_CTX;
void*	vpErrorsCtor(void* vpMemCtx, void* vpAlertHandler);
void	vErrorsDtor(void* vpErrorsCtx);
void	vErrorsReport(void* vpErrorsCtx, char* cpMsg);
G_UINT uiErrorsCount(void* vpErrorsCtx);
char*	cpErrorsIterInit(void* vpErrorsCtx);
char*	cpErrorsIterNext(void* vpErrorsCtx);


//////////////////////////////////////////////////////////////////////////
// LINE CATALOGING UTILITY
//////////////////////////////////////////////////////////////////////////
#define TAB (unsigned char)9
#define LF (unsigned char)10
#define CR (unsigned char)13
#define SP (unsigned char)32
#define ASCII_END (unsigned char)127
#define MAX_DISPLAY_LINE_LEN (G_UINT)128
typedef struct{
	G_UINT uiLineNo;
	G_UINT uiLineLen;
	G_UINT uiLineEndLen;
	G_UINT uiBegChar;
	G_UINT uiEndChar;
	char* cpBeg;
	char* cpEnd;
	char* cpLine;
}CATALOG_LINE;

typedef struct{
	void*	vpMemCtx;
	void*	vpVecLines;
	char*	cpSrc;
	G_UINT uiSrcLen;
	G_UINT uiIterNext;
	PFN_ALERT	pfnAlertHandler;
}CATALOG_CTX;

void* vpCatalogCtor(void* vpMemCtx, void* vpAlertHandler);
void vCatalogDtor();
G_UINT uiCatalogLines(void* vpCtx, char* cpSrc, G_UINT uiSrcLen);
G_UINT uiCatalogLineCount(void* vpCtx);
void vCatalogDisplay(void* vpCtx, FILE* spOut);
void vCatalogDisplayLine(CATALOG_LINE* spLine, char* cpBuffer, G_UINT uiBufLen);
CATALOG_LINE* spCatalogGetLine(void* vpCtx, G_UINT uiLineNo);
CATALOG_LINE* spCatalogIterInit(void* vpCtx);
CATALOG_LINE* spCatalogIterNext(void* vpCtx);


#endif /* GENERATOR_H_ */
