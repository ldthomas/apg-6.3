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
/******************************************************************************
   purpose: Private APG library header file. Required for building
            APG static library only. Not require for building applications.

*********************************************************************/
#ifndef PRIVATE_H_6_3_
#define PRIVATE_H_6_3_
#include "Apg.h"
#include "Grammar.h"

// used to convert all integers to unsigned long for compatibility with the format
//typedef unsigned long int lu_ulong;

//////////////////////////////////////////////////////////////////////////
// PRIVATE MEMORY COMPONENT
//////////////////////////////////////////////////////////////////////////
// a memory cell
struct APG_MEM_CELL_STRUCT{
  struct APG_MEM_CELL_STRUCT* spPrev;
  struct APG_MEM_CELL_STRUCT* spNext;
  apg_uint uiSize; // size (bytes) of memory allocation
  apg_uint uiSeq;  // sequence number of this cell
};

typedef struct APG_MEM_CELL_STRUCT APG_MEM_CELL;
typedef struct{
  apg_uint       uiActiveCellCount;  // number of cells on the active list
  PFN_ALLOCATOR   pfnAllocator;       // pointer to the allocator function
  PFN_DEALLOCATOR pfnDeAllocator;     // pointer to the de-allocator function
  APG_MEM_STATS   sStats;             // memory statistics
  void*           vpValidate;         // validation handle
  APG_MEM_CELL*   spActiveList;       // pointer to the first (and last) cell in a circularly, doubly linked list
} APG_MEM_CTX;

//////////////////////////////////////////////////////////////////////////
// PRIVATE PARSER COMPONENT
//////////////////////////////////////////////////////////////////////////
#define P_RNM	0
#define P_UDT	1
#define P_REP	2
#define P_ALT	3
#define P_CAT	4
#define P_AND	5
#define P_NOT	6
#define P_TRG	7
#define P_TBS	8
#define P_TLS	9

struct parserctx;
struct opcode;
typedef apg_uint (*PFN_OP)(struct parserctx* spCtx, struct opcode* spOp, apg_uint uioffset);

// rule list
typedef struct{
	char*			cpRuleName;     // pointer to the (null-terminated) ASCII rule name
	struct opcode*	spOp;           // pointer to the first opcode of the rule
	apg_uint		uiOpcodeCount;
	apg_uint		uiRuleIndex;
	APG_CALLBACK  	pfnCBSyntax;    // pointer to the syntax call back function for this rule
} APG_RULE;

// udt list
typedef struct{
	char*			cpUdtName;     // pointer to the (null-terminated) ASCII rule name
	apg_uint		uiEmpty;
	apg_uint		uiUdtIndex;
	APG_CALLBACK	pfnCBSyntax;    // pointer to the syntax call back function for this rule
} APG_UDT;

// opcodes
typedef struct{
	struct opcode*	spNext;
	APG_RULE*		spRule;
} APG_OP_RNM;

typedef struct{
	APG_UDT*		spUdt;
	apg_uint		uiEmpty;
} APG_OP_UDT;

typedef struct{
	struct opcode*	spNext;
	apg_uint		uiMin;
	apg_uint		uiMax;
} APG_OP_REP;

typedef struct{
	apg_uint*		uipChildList;
	apg_uint		uiChildCount;
} APG_OP_ALT;

typedef struct{
	apg_uint*		uipChildList;
	apg_uint		uiChildCount;
} APG_OP_CAT;

typedef struct{
	struct opcode*	spNext;
} APG_OP_AND;

typedef struct{
	struct opcode*	spNext;
} APG_OP_NOT;

typedef struct{
	apg_achar		acMin;
	apg_achar		acMax;
} APG_OP_TRG;

typedef struct{
	apg_achar*		acpStrTbl;
	apg_uint		uiStrLen;
} APG_OP_TBS;

typedef struct{
	apg_achar*		acpStrTbl;
	apg_uint		uiStrLen;
} APG_OP_TLS;

typedef union{
	APG_OP_RNM sRnm;
	APG_OP_UDT sUdt;
	APG_OP_REP sRep;
	APG_OP_ALT sAlt;
	APG_OP_CAT sCat;
	APG_OP_AND sAnd;
	APG_OP_NOT sNot;
	APG_OP_TRG sTrg;
	APG_OP_TBS sTbs;
	APG_OP_TLS sTls;
} APG_OP;

typedef struct opcode{
	PFN_OP	pfnOp;
	char* cpName;
	APG_OP	sUnion;
} APG_OPCODE;

// parser context
typedef struct parserctx{
	void*				vpMemCtx;
	void*				vpAstCtx;
	void*				vpTraceCtx;
	void*				vpStatsCtx;
	PFN_ALERT			pfnAlertHandler;
	char*				cpCharTable;
	apg_achar*			acpACharTable;
	apg_uint*			uipChildList;
	APG_RULE*			spRules;
	APG_UDT*			spUdts;
	APG_OPCODE*			spOpcodes;
	apg_uint			uiRuleCount;
	apg_uint			uiUdtCount;
	apg_uint			uiHaveAllUdtCallbacks;
	apg_uint   			uiStartRule;
	const apg_achar*	acpInputString;
	apg_uint			uiInputStringLen;
	APG_CBDATA			sCBData;
	APG_PARSER_STATE	sState;
	void*				vpValidate;
} APG_PARSER_CTX;

//////////////////////////////////////////////////////////////////////////
// SABNF OPERATOR PROTOTYPES
//////////////////////////////////////////////////////////////////////////
apg_uint uiALT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiCAT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiREP(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiRNM(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiUDT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiAND(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiNOT(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiTRG(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiTBS(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);
apg_uint uiTLS(struct parserctx* spCtx, struct opcode* spOp, apg_uint uiOffset);

//////////////////////////////////////////////////////////////////////////
// TRACE
//////////////////////////////////////////////////////////////////////////
#define TRACE_ACTION_BEGIN		0
#define TRACE_ACTION_END		1
#define TRACE_ACTION_DOWN		2
#define TRACE_ACTION_UP			3
#define TRACE_ACTION_ENABLE		4
#define TRACE_ACTION_DISABLE	5
#define TRACE_ACTION_OP			6
#define TRACE_ACTION_RULE		7
#define TRACE_ACTION_UDT		8
#define TRACE_ACTION_RANGE		9

typedef struct{
	APG_PARSER_CTX* spParserCtx;
	void* vpVecRecordStack;
	apg_uint uiRecordNumber;
	apg_uint uiTreeDepth;
	apg_uint uiTraceRootIndex;
	apg_uint uiRangeBegin;
	apg_uint uiRangeCount;
	apg_uint uiCountOnly;
	apg_uint uiAlt;
	apg_uint uiCat;
	apg_uint uiRep;
	apg_uint uiRnm;
	apg_uint uiUdt;
	apg_uint uiAnd;
	apg_uint uiNot;
	apg_uint uiTrg;
	apg_uint uiTbs;
	apg_uint uiTls;
	apg_uint* uipRules;
	apg_uint* uipUdts;
} APG_TRACE_CTX;

void*	vpTraceCtor(APG_PARSER_CTX* spCtx);
void*	vpTraceDtor(APG_PARSER_CTX* spCtx);
void	vTraceClear(APG_PARSER_CTX* spCtx);
void	vTraceAdmin(APG_PARSER_CTX* spCtx, apg_uint uiAction, apg_uint uiId, apg_uint uiEnable, apg_uint* uipConfigured);
void	vTrace(APG_PARSER_CTX* spCtx, APG_OPCODE* spOp, apg_uint uiAction, apg_uint uiOpId, apg_uint uiOffset, apg_uint uiPhraseLen);

typedef struct{
	apg_uint			uiSize;
	apg_uint			uiNameSize;
	apg_uint			uiNameStatsSize;
	APG_PARSER_STATS*	spPublicStats;
} APG_STATS_CTX;

#define STATS_ACTION_COLLECT	1
#define STATS_ACTION_ENABLE		2
#define STATS_ACTION_DISABLE	3
#define STATS_ACTION_GETSTATS	4

void	vStatsAdmin(APG_PARSER_CTX* spCtx, apg_uint uiAction, void* vpInputOutput, apg_uint* uipReturn, apg_uint* uipConfigured);
void	vStats(APG_PARSER_CTX* spCtx, apg_uint uiAction, apg_uint uiState, apg_uint uiOpId, apg_uint uiRuleUdtId);

typedef struct{
	apg_uint uiState;
	apg_uint uiId;
	apg_uint uiThisRecord;
	apg_uint uiThatRecord;
	apg_uint uiPhraseOffset;
	apg_uint uiPhraseLength;
} APG_AST_RECORD;

typedef struct{
	void*			vpMemCtx;
	apg_uint*		uipNodes;
	apg_uint		uiNodeCount;
	apg_uint		uiRuleCount;
	apg_uint		uiUdtCount;
	APG_CALLBACK*	pfnCallbacks;
	APG_AST_RECORD*	spRecords;
	apg_uint		uiRecordCount;
	apg_uint		uiRecordEnd;
	apg_uint		uiIgnoreRecords;
	APG_PARSER_CTX* spParserCtx;
} APG_AST_CTX;

void	vAstCtor(APG_PARSER_CTX* spCtx);
void	vAstDtor(APG_PARSER_CTX* spCtx);
void	vAstClear(APG_PARSER_CTX* spCtx);
apg_uint uiAstTraverse(APG_AST_CTX* spCtx, APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, APG_CBDATA* spData);
void	vAstGrow(APG_AST_CTX* spCtx);
apg_uint uiAstGetNextRecord(APG_AST_CTX* spCtx);

// string buffer used for printing limited line length lines
typedef struct{
	char* cpBuffer;
	apg_uint uiBufLen;
	apg_uint uiBufCount;
	apg_uint uiBufIsTruncated;
	void* vpValidate;
} PRINTBUF;
void* vpStrBufInit(void* vpBuf, apg_uint uiBufLen);
apg_uint uiStrBufCat(void* vpBuf, char* cpString);
char* cpStrBufString(void* vpBuf);
apg_uint uiStrBufCount(void* vpBuf);
apg_uint uiStrBufSize(void* vpBuf);
apg_uint uiStrBufIsTruncated(void* vpBuf);

#endif // PRIVATE_H_6_3_
