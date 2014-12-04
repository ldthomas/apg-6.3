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
#ifndef SABNFGRAMMAR_H
#define SABNFGRAMMAR_H

// rule ids
#define RULE_SABNFGRAMMAR_ALPHANUM 60 // alphanum
#define RULE_SABNFGRAMMAR_ALTERNATION 4 // Alternation
#define RULE_SABNFGRAMMAR_ALTOP 26 // AltOp
#define RULE_SABNFGRAMMAR_AND 12 // And
#define RULE_SABNFGRAMMAR_ANDOP 29 // AndOp
#define RULE_SABNFGRAMMAR_BIN 50 // Bin
#define RULE_SABNFGRAMMAR_BLANKLINE 1 // BlankLine
#define RULE_SABNFGRAMMAR_BMAX 54 // bmax
#define RULE_SABNFGRAMMAR_BMIN 53 // bmin
#define RULE_SABNFGRAMMAR_BNUM 58 // bnum
#define RULE_SABNFGRAMMAR_BSTRING 47 // bString
#define RULE_SABNFGRAMMAR_CATOP 27 // CatOp
#define RULE_SABNFGRAMMAR_COMMENT 65 // comment
#define RULE_SABNFGRAMMAR_CONCATENATION 7 // Concatenation
#define RULE_SABNFGRAMMAR_DEC 48 // Dec
#define RULE_SABNFGRAMMAR_DEFINEDAS 18 // DefinedAs
#define RULE_SABNFGRAMMAR_DMAX 52 // dmax
#define RULE_SABNFGRAMMAR_DMIN 51 // dmin
#define RULE_SABNFGRAMMAR_DNUM 57 // dnum
#define RULE_SABNFGRAMMAR_DSTRING 45 // dString
#define RULE_SABNFGRAMMAR_ELEMENT 14 // Element
#define RULE_SABNFGRAMMAR_FILE 0 // File
#define RULE_SABNFGRAMMAR_GROUP 15 // Group
#define RULE_SABNFGRAMMAR_HEX 49 // Hex
#define RULE_SABNFGRAMMAR_INCALT 19 // IncAlt
#define RULE_SABNFGRAMMAR_LINECONTINUE 67 // LineContinue
#define RULE_SABNFGRAMMAR_LINEEND 66 // LineEnd
#define RULE_SABNFGRAMMAR_LOPTION 37 // Loption
#define RULE_SABNFGRAMMAR_LPAREN 35 // Lparen
#define RULE_SABNFGRAMMAR_LTLS 43 // Ltls
#define RULE_SABNFGRAMMAR_MULTIPLEALT 6 // MultipleAlt
#define RULE_SABNFGRAMMAR_MULTIPLECAT 9 // MultipleCat
#define RULE_SABNFGRAMMAR_NOT 13 // Not
#define RULE_SABNFGRAMMAR_NOTOP 30 // NotOp
#define RULE_SABNFGRAMMAR_OPTION 16 // Option
#define RULE_SABNFGRAMMAR_OWSP 61 // owsp
#define RULE_SABNFGRAMMAR_PROSVAL 17 // ProsVal
#define RULE_SABNFGRAMMAR_REP 11 // Rep
#define RULE_SABNFGRAMMAR_REP_MAX 41 // rep-max
#define RULE_SABNFGRAMMAR_REP_MIN 39 // rep-min
#define RULE_SABNFGRAMMAR_REP_MIN_MAX 40 // rep-min-max
#define RULE_SABNFGRAMMAR_REP_NUM 42 // rep-num
#define RULE_SABNFGRAMMAR_REPETITION 10 // Repetition
#define RULE_SABNFGRAMMAR_REPOP 25 // RepOp
#define RULE_SABNFGRAMMAR_RNMOP 21 // RnmOp
#define RULE_SABNFGRAMMAR_ROPTION 38 // Roption
#define RULE_SABNFGRAMMAR_RPAREN 36 // Rparen
#define RULE_SABNFGRAMMAR_RTLS 44 // Rtls
#define RULE_SABNFGRAMMAR_RULE 2 // Rule
#define RULE_SABNFGRAMMAR_RULEERROR 3 // RuleError
#define RULE_SABNFGRAMMAR_RULENAME 20 // RuleName
#define RULE_SABNFGRAMMAR_SINGLEALT 5 // SingleAlt
#define RULE_SABNFGRAMMAR_SINGLECAT 8 // SingleCat
#define RULE_SABNFGRAMMAR_SP 63 // sp
#define RULE_SABNFGRAMMAR_SPACE 64 // space
#define RULE_SABNFGRAMMAR_STAROP 28 // StarOp
#define RULE_SABNFGRAMMAR_TBSOP 32 // TbsOp
#define RULE_SABNFGRAMMAR_TLSCHAR 34 // TlsChar
#define RULE_SABNFGRAMMAR_TLSOP 33 // TlsOp
#define RULE_SABNFGRAMMAR_TRGOP 31 // TrgOp
#define RULE_SABNFGRAMMAR_UDT_EMPTY 24 // udt-empty
#define RULE_SABNFGRAMMAR_UDT_NON_EMPTY 23 // udt-non-empty
#define RULE_SABNFGRAMMAR_UDTOP 22 // UdtOp
#define RULE_SABNFGRAMMAR_WSP 62 // wsp
#define RULE_SABNFGRAMMAR_XMAX 56 // xmax
#define RULE_SABNFGRAMMAR_XMIN 55 // xmin
#define RULE_SABNFGRAMMAR_XNUM 59 // xnum
#define RULE_SABNFGRAMMAR_XSTRING 46 // xString
#define RULE_COUNT_SABNFGRAMMAR 68

// Parser initialization data
extern void* vpParserInit_SABNFGrammar;

#endif // SABNFGRAMMAR_H

//**** SABNF GRAMMAR ****
//;*******************************************************************************
//;  Version 6.3
//;  APG - an ABNF Parser Generator
//;  Copyright (C) 2005 - 2012 Lowell D. Thomas, all rights reserved
//;
//;  author:  Lowell D. Thomas
//;  email:   lowell@coasttocoastresearch.com
//;
//;  This program is free software: you can redistribute it and/or modify
//;  it under the terms of the GNU General Public License as published by
//;  the Free Software Foundation, either version 2 of the License, or
//;  (at your option) any later version.
//;
//;  This program is distributed in the hope that it will be useful,
//;  but WITHOUT ANY WARRANTY; without even the implied warranty of
//;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//;  GNU General Public License for more details.
//;
//;  You should have received a copy of the GNU General Public License
//;  along with this program.  If not, see
//;  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
//;  or write to the Free Software Foundation, Inc.,
//;  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//;*******************************************************************************
//;
//; ABNF for APG 6.3 SABNF
//; Symbol alphabet is ASCII (code points 10, 13, 32-126).
//; SABNF variations from RFC 4234:
//;  restrictions:
//;    incremental alternates, rule2 =/ rule1, are not allowed
//;    prose values, <prose value>, are not allowed
//;    only the first successful alternate, left to right, is accepted (the "prioritized choice" rule)
//;    only the longest possible match to repetitions is accepted
//;
//;  relaxations: 
//;    forgiving line endings - CRLF / LF / CR
//;
//;  super set additions:
//;    syntactic predicate operators, & and !, have been added
//;    User-Defined Terminals of the form, u_rule and e_rule, have been added
//;
//File          = *(BlankLine/Rule/RuleError)
//BlankLine     = LineEnd / (%d59/sp) *(sp / %d33-126) LineEnd
//Rule          = RuleName owsp (IncAlt/DefinedAs) owsp Alternation owsp LineEnd
//RuleError     = *(sp / %d33-126 / LineContinue) LineEnd
//Alternation   = MultipleAlt / SingleAlt
//SingleAlt     = Concatenation
//MultipleAlt   = Concatenation 1*(AltOp Concatenation)
//Concatenation = owsp (MultipleCat / SingleCat)
//SingleCat     = Repetition
//MultipleCat   = Repetition 1*(CatOp Repetition)
//Repetition    = Rep / And / Not / Element
//Rep           = RepOp Element
//And           = AndOp Element
//Not           = NotOp Element
//Element       = TrgOp   /
//                TbsOp   /
//                TlsOp   /
//                UdtOp  /
//                RnmOp   /
//                Group   /
//                Option  /
//                ProsVal
//Group         = Lparen  Alternation Rparen
//Option        = Loption Alternation Roption
//ProsVal       = %d60 *(%d32-61/%d63-126) %d62
//DefinedAs     = %d61
//IncAlt        = %d61.47
//
//RuleName      = alphanum
//RnmOp         = alphanum
//UdtOp         = udt-empty / udt-non-empty
//udt-non-empty = %d117.95 alphanum
//udt-empty     = %d101.95 alphanum
//RepOp         = (rep-min StarOp rep-max) /
//                (rep-min StarOp)         /
//                (StarOp rep-max)         /
//                 StarOp                  /
//                 rep-min-max
//AltOp         = owsp %d47
//CatOp         = wsp
//StarOp        = %d42
//AndOp         = %d38
//NotOp         = %d33
//TrgOp         = %d37 ((Dec dmin %d45 dmax) / (Hex xmin %d45 xmax) / (Bin bmin %d45 bmax))
//TbsOp         = %d37 ((Dec dString *(%d46 dString)) / (Hex xString *(%d46 xString)) / (Bin bString *(%d46 bString)))
//TlsOp         = Ltls *TlsChar Rtls
//TlsChar       = %d32-33/%d35-126 ; tab not allowed
//
//Lparen        = %d40 owsp
//Rparen        = owsp %d41
//Loption       = %d91 owsp
//Roption       = owsp %d93
//rep-min       = rep-num
//rep-min-max   = rep-num
//rep-max       = rep-num
//rep-num       = 1*(%d48-57)
//Ltls          = %d34
//Rtls          = %d34
//dString       = dnum
//xString       = xnum
//bString       = bnum
//Dec           = (%d68/%d100)
//Hex           = (%d88/%d120)
//Bin           = (%d66/%d98)
//dmin          = dnum
//dmax          = dnum
//bmin          = bnum
//bmax          = bnum
//xmin          = xnum
//xmax          = xnum
//dnum          = 1*(%d48-57)
//bnum          = 1*%d48-49
//xnum          = 1*(%d48-57 / %d65-70 / %d97-102)
//
//; Basics
//alphanum      = (%d97-122/%d65-90) *(%d97-122/%d65-90/%d48-57/%d45)
//owsp          = *space
//wsp           = 1*space
//sp            = %d9 / %d32
//space         = sp      /
//                comment /
//                LineContinue
//comment       = %d59 *(sp / %d33-126)
//LineEnd       = %d13.10 / %d10 / %d13
//LineContinue  = (%d13.10 / %d10 / %d13) %d32
//
////**** SABNF GRAMMAR ***

