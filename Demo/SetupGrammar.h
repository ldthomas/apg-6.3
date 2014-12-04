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
#ifndef SETUPGRAMMAR_H
#define SETUPGRAMMAR_H

// rule ids
#define RULE_SETUPGRAMMAR_ALPHANUM 17 // alphanum
#define RULE_SETUPGRAMMAR_ALTERNATION 6 // Alternation
#define RULE_SETUPGRAMMAR_ALTOP 8 // AltOp
#define RULE_SETUPGRAMMAR_ANY 11 // Any
#define RULE_SETUPGRAMMAR_BLANKLINE 1 // BlankLine
#define RULE_SETUPGRAMMAR_CATOP 9 // CatOp
#define RULE_SETUPGRAMMAR_CBEG 26 // CBeg
#define RULE_SETUPGRAMMAR_CCOMMENT 25 // CComment
#define RULE_SETUPGRAMMAR_CEND 27 // CEnd
#define RULE_SETUPGRAMMAR_COMMENT 22 // Comment
#define RULE_SETUPGRAMMAR_CONCATENATION 7 // Concatenation
#define RULE_SETUPGRAMMAR_CPPCOMMENT 24 // CppComment
#define RULE_SETUPGRAMMAR_DECNUM 12 // DecNum
#define RULE_SETUPGRAMMAR_DEFINEDAS 5 // DefinedAs
#define RULE_SETUPGRAMMAR_DOUBLEQUOTEDSTRING 16 // DoubleQuotedString
#define RULE_SETUPGRAMMAR_ELEMENT 10 // Element
#define RULE_SETUPGRAMMAR_FILE 0 // File
#define RULE_SETUPGRAMMAR_HEXNUM 13 // HexNum
#define RULE_SETUPGRAMMAR_LINE 2 // Line
#define RULE_SETUPGRAMMAR_LINECONTINUE 29 // LineContinue
#define RULE_SETUPGRAMMAR_LINEEND 28 // LineEnd
#define RULE_SETUPGRAMMAR_LINEERROR 3 // LineError
#define RULE_SETUPGRAMMAR_LINENAME 4 // LineName
#define RULE_SETUPGRAMMAR_OWSP 18 // owsp
#define RULE_SETUPGRAMMAR_QUOTEDSTRING 14 // QuotedString
#define RULE_SETUPGRAMMAR_SEMICOMMENT 23 // SemiComment
#define RULE_SETUPGRAMMAR_SINGLEQUOTEDSTRING 15 // SingleQuotedString
#define RULE_SETUPGRAMMAR_SP 20 // sp
#define RULE_SETUPGRAMMAR_SPACE 21 // space
#define RULE_SETUPGRAMMAR_WSP 19 // wsp
#define RULE_COUNT_SETUPGRAMMAR 30

// Parser initialization data
extern void* vpParserInit_SetupGrammar;

#endif // SETUPGRAMMAR_H

//**** SABNF GRAMMAR ****
//;
//; Demo Grammar - simplified, pseudo ABNF for SABNF
//;
//File				= 1*(BlankLine / Line / LineError)
//BlankLine			= owsp LineEnd
//Line				= LineName owsp DefinedAs owsp Alternation owsp LineEnd
//LineError			= Any LineEnd
//LineName			= alphanum
//DefinedAs			= "="
//Alternation			= Concatenation *(owsp AltOp owsp Concatenation)
//Concatenation		= Element *(CatOp Element)
//AltOp				= "/"
//CatOp				= wsp
//Element				= alphanum /
// 					  HexNum /
//  					  DecNum /
// 					  QuotedString
//Any					= *(%d9 / %d32-127)
//DecNum				= %d49-57 *%d48-57
//HexNum				= %d48.120 1*(%d48-75 / %d65-70 / %d97-102)
//QuotedString		= SingleQuotedString / DoubleQuotedString
//SingleQuotedString	= %d39 *(%d9 / %d32-38 / %d40-127) %d39
//DoubleQuotedString	= %d34 *(%d9 / %d32-33 / %d35-127) %d34
//
//
//; Basics
//alphanum			= (%d97-122/%d65-90) *(%d97-122/%d65-90/%d48-57/%d45)
//owsp				= *space
//wsp					= 1*space
//sp					= %d9 / %d32
//space				= sp      /
// 					  Comment /
// 					  LineContinue
//Comment				= SemiComment / CppComment / CComment
//SemiComment			= %d59 *(sp / %d33-126)
//CppComment			= "//" *(sp / %d33-126)
//CComment			= CBeg *(!CEnd (%d9 / %d32-127 / LineEnd)) CEnd
//CBeg				= "/*"
//CEnd				= "*/"
//LineEnd				= %d13.10 / %d10 / %d13
//LineContinue		= (%d13.10 / %d10 / %d13) %d32
////**** SABNF GRAMMAR ***

