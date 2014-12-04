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

#ifndef GRAMMAR_H_6_3_
#define GRAMMAR_H_6_3_

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERATOR GRAMMAR DEFINITION TYPES, DEFINES AND VALUES
// To be shared with Generator and Parser.
// These data definitions are meant to be used by both the generator to create the grammar data,
// and the parser to initialize using the generated data.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned long int G_UINT;
//typedef unsigned int G_UINT;
// opcode types
#define G_TYPE_RNM	10
#define G_TYPE_UDT	20
#define G_TYPE_REP	30
#define G_TYPE_ALT	40
#define G_TYPE_CAT	41
#define G_TYPE_AND	50
#define G_TYPE_NOT	60
#define G_TYPE_TLS	70
#define G_TYPE_TBS	80
#define G_TYPE_TRG	90

typedef struct{
	G_UINT	uiMinSizeofACharMax;	// sizeof(apg_achar) <= uiMinSizeofACharMax
	G_UINT	uiMinSizeofUintMax;		// sizeof(apg_uint) <= uiMinSizeofUintMax
	G_UINT	uiSizeInBytes;			// total size, in bytes, of the grammar data, including this header
	G_UINT	uiACharMin;				// minimum alphabet character code
	G_UINT	uiACharMax;				// maximum alphabet character code (caution when writing UDTs!)
	G_UINT	uiUintMax;				// maximum integer used
	G_UINT	uiVersionOffset;        // offset to the version number
	G_UINT	uiVersionLen;           // length in bytes of the version length
	G_UINT	uiCharTableOffset;      // offset to the character table
	G_UINT	uiCharTableLen;         // length in bytes of the character table
	G_UINT	uiACharTableOffset;     // offset to the alphabet character table
	G_UINT	uiACharTableLen;        // number of characters iln the alphabet character table
	G_UINT	uiChildListOffset;      // offset to the child list
	G_UINT	uiChildListLen;         // number of indexes in the chile list
	G_UINT	uiRulesOffset;          // offset to the rule list
	G_UINT	uiRulesLen;             // number of rules
	G_UINT	uiUdtsOffset;           // offset to the UDT list
	G_UINT	uiUdtsLen;              // number of UDTs
	G_UINT	uiOpcodesOffset;        // offset to the opcode list
	G_UINT	uiOpcodesLen;           // number of opcodes
} G_HDR;

typedef struct{
	G_UINT	uiGrammarLineNo;
	G_UINT	uiGrammarPhraseOffset;
	G_UINT	uiGrammarPhraseLength;
	G_UINT	uiNameOffset;
	G_UINT	uiNameLen;
	G_UINT	uiRuleIndex;
	G_UINT	uiChildOffset;
	G_UINT	uiChildCount;
} G_RULE;

typedef struct{
	G_UINT	uiGrammarLineNo;
	G_UINT	uiGrammarPhraseOffset;
	G_UINT	uiGrammarPhraseLength;
	G_UINT	uiNameOffset;
	G_UINT	uiNameLen;
	G_UINT	uiUdtIndex;
	G_UINT	uiEmpty;
} G_UDT;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildOffset;
	G_UINT	uiRuleIndex;
} G_RNMOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiEmpty;
	G_UINT	uiUdtIndex;
} G_UDTOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildListOffset;
	G_UINT	uiChildCount;
} G_ALTOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildListOffset;
	G_UINT	uiChildCount;
} G_CATOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildOffset;
	G_UINT	uiMin;
	G_UINT	uiMax;
} G_REPOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildOffset;
} G_ANDOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiChildOffset;
} G_NOTOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiMin;
	G_UINT	uiMax;
} G_TRGOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiOffset;
	G_UINT	uiLen;
} G_TBSOP;

typedef struct{
//	G_UINT	uiType;
	G_UINT	uiOffset;
	G_UINT	uiLen;
} G_TLSOP;

typedef union{
	G_RNMOP	sRnm;
	G_UDTOP	sUdt;
	G_REPOP	sRep;
	G_ALTOP	sAlt;
	G_CATOP	sCat;
	G_ANDOP	sAnd;
	G_NOTOP	sNot;
	G_TRGOP	sTrg;
	G_TBSOP	sTbs;
	G_TLSOP	sTls;
} G_OPUNION;

typedef struct{
	G_UINT	uiType;
	G_UINT	uiGrammarLineNo;
	G_UINT	uiGrammarPhraseOffset;
	G_UINT	uiGrammarPhraseLength;
	G_OPUNION sOpType;
} G_OPCODE;

void      vGrammarSetHash(G_HDR* spHdr);
G_UINT uiGrammarValidateHash(G_HDR* spHdr);

#endif /* GRAMMAR_H_6_3_ */
