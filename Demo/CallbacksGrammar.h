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
#ifndef CALLBACKSGRAMMAR_H
#define CALLBACKSGRAMMAR_H

// rule ids
#define RULE_CALLBACKSGRAMMAR_ALPHANUM 16 // alphanum
#define RULE_CALLBACKSGRAMMAR_ALTERNATION 5 // Alternation
#define RULE_CALLBACKSGRAMMAR_ALTOP 7 // AltOp
#define RULE_CALLBACKSGRAMMAR_ANY 10 // Any
#define RULE_CALLBACKSGRAMMAR_BLANKLINE 1 // BlankLine
#define RULE_CALLBACKSGRAMMAR_CATOP 8 // CatOp
#define RULE_CALLBACKSGRAMMAR_CBEG 25 // CBeg
#define RULE_CALLBACKSGRAMMAR_CCOMMENT 24 // CComment
#define RULE_CALLBACKSGRAMMAR_CEND 26 // CEnd
#define RULE_CALLBACKSGRAMMAR_COMMENT 21 // Comment
#define RULE_CALLBACKSGRAMMAR_CONCATENATION 6 // Concatenation
#define RULE_CALLBACKSGRAMMAR_CPPCOMMENT 23 // CppComment
#define RULE_CALLBACKSGRAMMAR_DECNUM 11 // DecNum
#define RULE_CALLBACKSGRAMMAR_DEFINEDAS 4 // DefinedAs
#define RULE_CALLBACKSGRAMMAR_DOUBLEQUOTEDSTRING 15 // DoubleQuotedString
#define RULE_CALLBACKSGRAMMAR_ELEMENT 9 // Element
#define RULE_CALLBACKSGRAMMAR_FILE 0 // File
#define RULE_CALLBACKSGRAMMAR_HEXNUM 12 // HexNum
#define RULE_CALLBACKSGRAMMAR_LINE 2 // Line
#define RULE_CALLBACKSGRAMMAR_LINECONTINUE 28 // LineContinue
#define RULE_CALLBACKSGRAMMAR_LINEEND 27 // LineEnd
#define RULE_CALLBACKSGRAMMAR_LINENAME 3 // LineName
#define RULE_CALLBACKSGRAMMAR_OWSP 17 // owsp
#define RULE_CALLBACKSGRAMMAR_QUOTEDSTRING 13 // QuotedString
#define RULE_CALLBACKSGRAMMAR_SEMICOMMENT 22 // SemiComment
#define RULE_CALLBACKSGRAMMAR_SINGLEQUOTEDSTRING 14 // SingleQuotedString
#define RULE_CALLBACKSGRAMMAR_SP 19 // sp
#define RULE_CALLBACKSGRAMMAR_SPACE 20 // space
#define RULE_CALLBACKSGRAMMAR_WSP 18 // wsp
#define RULE_COUNT_CALLBACKSGRAMMAR 29

// UDT ids
#define UDT_CALLBACKSGRAMMAR_U_LINEERROR 0 // u_LineError
#define UDT_COUNT_CALLBACKSGRAMMAR 1

// Parser initialization data
extern void* vpParserInit_CallbacksGrammar;

#endif // CALLBACKSGRAMMAR_H

//**** SABNF GRAMMAR ****
//;
//; Ast Demonstration Grammar - simplified, pseudo ABNF for SABNF
//;
//File				= 1*(BlankLine / Line / u_LineError)
//BlankLine			= owsp LineEnd
//Line				= LineName owsp DefinedAs owsp Alternation owsp LineEnd
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
//LineContinue		= (%d13.10 / %d10 / %d13) sp
////**** SABNF GRAMMAR ***

