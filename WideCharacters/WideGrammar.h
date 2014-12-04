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
#ifndef WIDEGRAMMAR_H
#define WIDEGRAMMAR_H

// rule ids
#define RULE_WIDEGRAMMAR_CHEROKEE_CHAR 6 // cherokee-char
#define RULE_WIDEGRAMMAR_CHEROKEE_EXAMPLE 5 // cherokee-example
#define RULE_WIDEGRAMMAR_CYRILLIC_CHAR 4 // cyrillic-char
#define RULE_WIDEGRAMMAR_CYRILLIC_EXAMPLE 3 // cyrillic-example
#define RULE_WIDEGRAMMAR_END 9 // end
#define RULE_WIDEGRAMMAR_ERROR_CHAR 8 // error-char
#define RULE_WIDEGRAMMAR_ERROR_EXAMPLE 7 // error-example
#define RULE_WIDEGRAMMAR_GREEK_CHAR 2 // greek-char
#define RULE_WIDEGRAMMAR_GREEK_EXAMPLE 1 // greek-example
#define RULE_WIDEGRAMMAR_UTF32_EXAMPLES 0 // UTF32-examples
#define RULE_COUNT_WIDEGRAMMAR 10

// Parser initialization data
extern void* vpParserInit_WideGrammar;

#endif // WIDEGRAMMAR_H

//**** SABNF GRAMMAR ****
//;
//; Wide Characters Example
//;  Each "line" defines an example of characters from
//;  the UNICODE code charts (http://www.unicode.org/charts/)
//;  Three charts are included in this example - Cherokee, Greek and Cyrillic.
//;  An "error" chart is included to accept any example that has errors
//;  so that the parser may continue to accept the next example.
//;
//UTF32-examples   = 1*((greek-example / cyrillic-example / cherokee-example / error-example) end)
//
//greek-example    = "Greek" 1*greek-char
//greek-char       = %x0370-03ff
//
//cyrillic-example = "Cyrillic" 1*cyrillic-char
//cyrillic-char    = %x0400-04ff
//
//cherokee-example = "Cherokee" 1*cherokee-char
//cherokee-char    = %x13a0-13ff
//
//error-example    = *error-char
//error-char       = %xb-ffffffff / %x0-9
//
//end              = %xa
////**** SABNF GRAMMAR ***

