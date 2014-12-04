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
#ifndef UDTLIBGRAMMAR_H
#define UDTLIBGRAMMAR_H

// rule ids
#define RULE_UDTLIBGRAMMAR_BLANKLINE 1 // BlankLine
#define RULE_UDTLIBGRAMMAR_COMMENT 2 // Comment
#define RULE_UDTLIBGRAMMAR_DEFINEDAS 11 // DefinedAs
#define RULE_UDTLIBGRAMMAR_FILE 0 // File
#define RULE_UDTLIBGRAMMAR_LINE 3 // Line
#define RULE_UDTLIBGRAMMAR_LINEALPHA 4 // LineAlpha
#define RULE_UDTLIBGRAMMAR_LINEERROR 7 // LineError
#define RULE_UDTLIBGRAMMAR_LINEHYPHEN 5 // LineHyphen
#define RULE_UDTLIBGRAMMAR_LINENAMEALPHA 8 // LineNameAlpha
#define RULE_UDTLIBGRAMMAR_LINENAMEHYPHEN 9 // LineNameHyphen
#define RULE_UDTLIBGRAMMAR_LINENAMEUNDER 10 // LineNameUnder
#define RULE_UDTLIBGRAMMAR_LINEUNDER 6 // LineUnder
#define RULE_UDTLIBGRAMMAR_NUMBER 12 // Number
#define RULE_COUNT_UDTLIBGRAMMAR 13

// UDT ids
#define UDT_UDTLIBGRAMMAR_E_ANY 9 // e_Any
#define UDT_UDTLIBGRAMMAR_E_OWSP 0 // e_owsp
#define UDT_UDTLIBGRAMMAR_U_ALPHANUM 10 // u_alphanum
#define UDT_UDTLIBGRAMMAR_U_ALPHANUM_HYPHEN 11 // u_alphanum-hyphen
#define UDT_UDTLIBGRAMMAR_U_ALPHANUM_UNDER 12 // u_alphanum-under
#define UDT_UDTLIBGRAMMAR_U_CCOMMENT 2 // u_CComment
#define UDT_UDTLIBGRAMMAR_U_CPPCOMMENT 3 // u_CppComment
#define UDT_UDTLIBGRAMMAR_U_DECIMAL 14 // u_Decimal
#define UDT_UDTLIBGRAMMAR_U_DOUBLEQUOTEDSTRING 7 // u_DoubleQuotedString
#define UDT_UDTLIBGRAMMAR_U_HEXIDECIMAL 13 // u_Hexidecimal
#define UDT_UDTLIBGRAMMAR_U_LINEEND 1 // u_LineEnd
#define UDT_UDTLIBGRAMMAR_U_QUOTEDSTRING 8 // u_QuotedString
#define UDT_UDTLIBGRAMMAR_U_SEMICOMMENT 4 // u_SemiComment
#define UDT_UDTLIBGRAMMAR_U_SINGLEQUOTEDSTRING 5 // u_SingleQuotedString
#define UDT_UDTLIBGRAMMAR_U_WSP 6 // u_wsp
#define UDT_COUNT_UDTLIBGRAMMAR 15

// Parser initialization data
extern void* vpParserInit_UdtLibGrammar;

#endif // UDTLIBGRAMMAR_H

//**** SABNF GRAMMAR ****
//;
//; Demo Grammar - refers to all items in UdtLib
//; NOTES:
//;  1. u_wsp and e_owsp include space and tab only - line continuations and comments are not included
//;  2. alphanum, alphanum with hyphens and alphanum with underscore cannot be alternates,
//;       since either of the extra character types overlap the phrase space of the others.
//;       That is "name" will be recognized by either of the extra character types as a valid phrase.
//;  3. Line must appear in threes - Line, LineHyphen and LineUnder.
//;       This is an artificial construction simple to test and illustrate the different alphanum types. 
//;  4. Quotes are likewise a foursome of single, double and 2xeither in order to test them all
//;       without disambiguation problems.
//;
//File			= 1*(BlankLine / Comment / Line / LineError)
//BlankLine		= e_owsp u_LineEnd
//Comment			= (u_CComment / u_CppComment / u_SemiComment) u_LineEnd
//Line			= LineAlpha LineHyphen LineUnder
//LineAlpha		= LineNameAlpha e_owsp DefinedAs e_owsp (u_SingleQuotedString / (Number *(u_wsp Number))) e_owsp u_LineEnd
//LineHyphen		= LineNameHyphen e_owsp DefinedAs e_owsp (u_DoubleQuotedString / (Number *(u_wsp Number))) e_owsp u_LineEnd
//LineUnder		= LineNameUnder e_owsp DefinedAs e_owsp (u_QuotedString / (Number *(u_wsp Number))) e_owsp u_LineEnd
//LineError		= e_Any u_LineEnd
//LineNameAlpha	= u_alphanum
//LineNameHyphen	= u_alphanum-hyphen
//LineNameUnder	= u_alphanum-under
//DefinedAs		= "="
//Number			= u_Hexidecimal / u_Decimal ; order is important
////**** SABNF GRAMMAR ***

