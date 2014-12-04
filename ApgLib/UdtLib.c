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
/** \file UdtLib.c \brief A small UDT callback function library.

All functions take an APG_CBDATA struct passed to them by the Parser as input.
They return the result in the struct member uiPhraseLength.
The returned value of uiPhraseLength is interpreted by the Parser as follows:
<pre>
uiPhraseLength = 0,             an empty phrase was matched. Only returned by UDT functions beginning with "e_".
uiPhraseLength > 0,             a non-empty phrase was matched.
uiPhraseLength = APG_UNDEFINED, no phrase was matched
</pre>
@see APG_CBDATA
@see APG_CALLBACK
*/

#include "Apg.h"

/** \cond NODISPLAY */
#define UDTLIB_TAB			(apg_achar)9
#define UDTLIB_LF 			(apg_achar)10
#define UDTLIB_CR 			(apg_achar)13
#define UDTLIB_SP 			(apg_achar)32
#define UDTLIB_DOUBLE_QUOTE	(apg_achar)34
#define UDTLIB_SINGLE_QUOTE	(apg_achar)39
#define UDTLIB_STAR 		(apg_achar)42
#define UDTLIB_SLASH 		(apg_achar)47
#define UDTLIB_SEMI 		(apg_achar)59
#define UDTLIB_HYPHEN		(apg_achar)45
#define UDTLIB_0			(apg_achar)48
#define UDTLIB_9			(apg_achar)57
#define UDTLIB_UPPER_A		(apg_achar)65
#define UDTLIB_UPPER_F		(apg_achar)70
#define UDTLIB_UPPER_Z		(apg_achar)90
#define UDTLIB_UNDERSCORE	(apg_achar)95
#define UDTLIB_LOWER_A		(apg_achar)97
#define UDTLIB_LOWER_F		(apg_achar)102
#define UDTLIB_LOWER_X		(apg_achar)120
#define UDTLIB_LOWER_Z		(apg_achar)122
#define UDTLIB_PRINT_MIN	(apg_achar)32
#define UDTLIB_PRINT_MAX	(apg_achar)127
/** \endcond */
///////////////////////////////////////////////////////////////////////////////
// UDT STATIC HELPERS
///////////////////////////////////////////////////////////////////////////////
static apg_uint uiIsAlpha(apg_achar acChar){
	return ((acChar >= UDTLIB_UPPER_A && acChar <= UDTLIB_UPPER_Z) ||
			(acChar >= UDTLIB_LOWER_A && acChar <= UDTLIB_LOWER_Z));
}
static apg_uint uiIsDigit(apg_achar acChar){
	return ((acChar >= UDTLIB_0 && acChar <= UDTLIB_9));
}
static apg_uint uiIsHexDigit(apg_achar acChar){
	return ((acChar >= UDTLIB_0 && acChar <= UDTLIB_9) ||
			(acChar >= UDTLIB_UPPER_A && acChar <= UDTLIB_UPPER_F) ||
			(acChar >= UDTLIB_LOWER_A && acChar <= UDTLIB_LOWER_F));
}
static apg_uint uiLineEnd(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiRet = 0;
	if(uiMaxPhraseLength > 0){
		if(acpPhrase[0] == UDTLIB_LF){uiRet = 1;}
		else if(acpPhrase[0] == UDTLIB_CR){
			if(uiMaxPhraseLength > 1 && acpPhrase[1] == UDTLIB_LF){uiRet = 2;}
			else{uiRet = 1;}
		}
	}
	return uiRet;
}
//static apg_uint uiLineContinue(apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
//	apg_uint uiRet = 0;
//	apg_uint uiTest;
//	if((0 < uiMaxPhraseLength) && (uiTest = uiLineEnd(&acpPhrase[0], uiMaxPhraseLength))){
//		if((uiTest < uiMaxPhraseLength) && acpPhrase[uiTest] == UDTLIB_SP){
//			uiRet = uiTest + 1;
//		}
//	}
//	return uiRet;
//}
static apg_uint uiAny(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_achar cAChar;
	while(uiPhraseCount < uiMaxPhraseLength){
		cAChar = acpPhrase[uiPhraseCount];
		if(cAChar == UDTLIB_TAB || (cAChar >= UDTLIB_PRINT_MIN && cAChar <= UDTLIB_PRINT_MAX)){
			uiPhraseCount++;
		} else{break;}
	}
	return uiPhraseCount;
}
static apg_uint uiAlphaNum(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	if(uiPhraseCount < uiMaxPhraseLength && uiIsAlpha(acpPhrase[0])){
		uiPhraseCount++;
		while(uiPhraseCount < uiMaxPhraseLength){
			if(uiIsAlpha(acpPhrase[uiPhraseCount]) ||
					uiIsDigit(acpPhrase[uiPhraseCount])){
				uiPhraseCount++;
			} else{break;}
		}
	}
	return uiPhraseCount;
}
static apg_uint uiAlphaNumPlus(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength, apg_achar acExtraChar){
	apg_uint uiPhraseCount = 0;
	if(uiPhraseCount < uiMaxPhraseLength && uiIsAlpha(acpPhrase[0])){
		uiPhraseCount++;
		while(uiPhraseCount < uiMaxPhraseLength){
			if((acpPhrase[uiPhraseCount] == acExtraChar) ||
					uiIsAlpha(acpPhrase[uiPhraseCount]) ||
					uiIsDigit(acpPhrase[uiPhraseCount])){
				uiPhraseCount++;
			} else{break;}
		}
	}
	return uiPhraseCount;
}
static apg_uint uiSingleQuotedString(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_achar cAChar;
	if(uiPhraseCount < uiMaxPhraseLength && (acpPhrase[0] == UDTLIB_SINGLE_QUOTE)){
		uiPhraseCount++;
		while(uiPhraseCount < uiMaxPhraseLength){
			cAChar = acpPhrase[uiPhraseCount];
			if(cAChar == UDTLIB_TAB ||
					(cAChar >= UDTLIB_PRINT_MIN && cAChar < UDTLIB_SINGLE_QUOTE) ||
					(cAChar >UDTLIB_SINGLE_QUOTE && cAChar < UDTLIB_PRINT_MAX)){uiPhraseCount++;}
			else{break;}
		}
		if(uiPhraseCount < uiMaxPhraseLength && (acpPhrase[uiPhraseCount] == UDTLIB_SINGLE_QUOTE)){uiPhraseCount++;}
		else{uiPhraseCount = 0;}
	}
	return uiPhraseCount;
}
static apg_uint uiDoubleQuotedString(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_achar cAChar;
	if(uiPhraseCount < uiMaxPhraseLength && (acpPhrase[0] == UDTLIB_DOUBLE_QUOTE)){
		uiPhraseCount++;
		while(uiPhraseCount < uiMaxPhraseLength){
			cAChar = acpPhrase[uiPhraseCount];
			if(cAChar == UDTLIB_TAB ||
					(cAChar >= UDTLIB_PRINT_MIN && cAChar < UDTLIB_DOUBLE_QUOTE) ||
					(cAChar >UDTLIB_DOUBLE_QUOTE && cAChar < UDTLIB_PRINT_MAX)){uiPhraseCount++;}
			else{break;}
		}
		if(uiPhraseCount < uiMaxPhraseLength && (acpPhrase[uiPhraseCount] == UDTLIB_DOUBLE_QUOTE)){uiPhraseCount++;}
		else{uiPhraseCount = 0;}
	}
	return uiPhraseCount;
}
static apg_uint uiSemiComment(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_uint uiLeft = uiMaxPhraseLength;
	apg_uint uiTest;
	if(uiLeft > 0 && acpPhrase[0] == UDTLIB_SEMI){
		uiPhraseCount++;
		uiLeft--;
		while(uiPhraseCount < uiMaxPhraseLength){
			if((uiTest = uiAny(&acpPhrase[uiPhraseCount], uiLeft))){
				uiLeft -= uiTest;
				uiPhraseCount += uiTest;
			} else{break;}
		}
	}
	return uiPhraseCount;
}
static apg_uint uiCppComment(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_uint uiLeft = uiMaxPhraseLength;
	apg_uint uiTest;
	if(uiLeft > 1 && acpPhrase[0] == UDTLIB_SLASH && acpPhrase[1] == UDTLIB_SLASH){
		uiPhraseCount += 2;
		uiLeft -= 2;
		while(uiPhraseCount < uiMaxPhraseLength){
			if((uiTest = uiAny(&acpPhrase[uiPhraseCount], uiLeft))){
				uiLeft -= uiTest;
				uiPhraseCount += uiTest;
			} else{break;}
		}
	}
	return uiPhraseCount;
}
static apg_uint uiAnyButStarSlash(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_achar cAChar;
	while(uiPhraseCount < uiMaxPhraseLength){
		cAChar = acpPhrase[uiPhraseCount];
		if(uiPhraseCount+1<uiMaxPhraseLength && cAChar == UDTLIB_STAR && acpPhrase[uiPhraseCount+1] == UDTLIB_SLASH){break;}
		if(cAChar == UDTLIB_TAB || (cAChar >= UDTLIB_PRINT_MIN && cAChar <= UDTLIB_PRINT_MAX)){
			uiPhraseCount++;
		} else{break;}
	}
	return uiPhraseCount;
}
static apg_uint uiCComment(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_uint uiLeft = uiMaxPhraseLength;
	apg_uint uiTest;
	if(uiLeft > 1 && acpPhrase[0] == UDTLIB_SLASH && acpPhrase[1] == UDTLIB_STAR){
		uiPhraseCount += 2;
		uiLeft -= 2;
		while(uiPhraseCount < uiMaxPhraseLength){
			if(uiLeft > 1 && acpPhrase[uiPhraseCount] == UDTLIB_STAR && acpPhrase[uiPhraseCount + 1] == UDTLIB_SLASH){
				uiPhraseCount += 2;
				break;
			}
			if((uiTest = uiAnyButStarSlash(&acpPhrase[uiPhraseCount], uiLeft))){
				uiLeft -= uiTest;
				uiPhraseCount += uiTest;
			} else if(uiLeft > 0 && (acpPhrase[uiPhraseCount] == UDTLIB_CR || acpPhrase[uiPhraseCount] == UDTLIB_LF)){
				uiLeft--;
				uiPhraseCount++;
			} else{break;}

		}
	}
	return uiPhraseCount;
}
static apg_uint uiWsp(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_uint uiLeft = uiMaxPhraseLength;
//	apg_uint uiTest;
	while(uiLeft > 0){
		if(acpPhrase[uiPhraseCount] == UDTLIB_SP){uiLeft--;}
		else if(acpPhrase[uiPhraseCount] == UDTLIB_TAB){uiLeft--;}

		// uncomment to include line continuations as white space
//		else if((uiTest = uiLineContinue(&acpPhrase[uiPhraseCount], uiLeft))){uiLeft -= uiTest;}

		// uncomment any or all of the following to include comments as white space
//		else if((uiTest = uiSemiComment(&acpPhrase[uiPhraseCount], uiLeft))){uiLeft -= uiTest;}
//		else if((uiTest = uiCppComment(&acpPhrase[uiPhraseCount], uiLeft))){uiLeft -= uiTest;}
//		else if((uiTest = uiCComment(&acpPhrase[uiPhraseCount], uiLeft))){uiLeft -= uiTest;}
		else{break;}
		uiPhraseCount = uiMaxPhraseLength - uiLeft;
	}

	return uiPhraseCount;
}

///////////////////////////////////////////////////////////////////////////////
// UDT CALLBACK LIBRARY
///////////////////////////////////////////////////////////////////////////////
/** Phrase recognizer for optional white space

Equivalent SABNF syntax:
<pre>
WSP   = *(TAB / SPACE)
TAB   = \%d9
SPACE = \%d32
</pre>

NOTE: see UdtLib.c for the static function uiWsp() for more options.
Line continuations and various types of comments may also be easily included as white space.
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_e_owsp(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiWsp(acpPhrase, uiMaxPhraseLength);
	return 0;
}

/** Phrase recognizer for required white space

Equivalent SABNF syntax:
<pre>
WSP   = 1*(TAB / SPACE)
TAB   = \%d9
SPACE = \%d32
</pre>

NOTE: see UdtLib.c for the static function uiWsp() for more options.
Line continuations and various types of comments may also be easily included as white space.
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_wsp(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiWsp(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for line ending. This is a "forgiving" line end allowing for the most commonly used values.

Equivalent SABNF syntax:
<pre>
LINEEND = CR LF / CR / LF
CR      = \%d13
LF      = \%d10
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_lineend(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiLineEnd(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a string of any printing characters, including TAB.

Equivalent SABNF syntax:
<pre>
ANY = *(\%d9 / \%d32-127)
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_e_any(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiAny(acpPhrase, uiMaxPhraseLength);
	return 0;
}

/** Phrase recognizer for a semicolon initialized comment. Comment runs from semicolon to end of line.

Equivalent SABNF syntax:
<pre>
SEMICOMMENT = ";" ANY
ANY         = *(\%d9 / \%d32-127)
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_semi_comment(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiSemiComment(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a C++-style comment. Comment runs from "//" to end of line.

Equivalent SABNF syntax:
<pre>
CPPCOMMENT = "//" ANY
ANY        = *(\%d9 / \%d32-127)
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_cpp_comment(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiCppComment(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a C-style comment. Comment runs from "/ *" to "* /".

Equivalent SABNF syntax:
<pre>
CCOMMENT = BEGIN *(!END ANY) END
BEGIN    = \%d47.42
END      = \%d42.47
ANY      = TAB / CR / LF / \%d32-127
TAB      = \%d9
LF       = \%d10
CF       = \%d13
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_c_comment(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiCComment(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for an alphanumeric string.

Equivalent SABNF syntax:
<pre>
ALPHANUM = ALPHA *(ALPHA / DIGIT)
ALPHA    = \%d65-90 / \%d97-122
DIGIT    = \%d48-57
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_alphanum(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiAlphaNum(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for an alphanumeric string, including hyphen.

Equivalent SABNF syntax:
<pre>
ALPHANUM = ALPHA *(ALPHA / DIGIT / HYPHEN)
ALPHA    = \%d65-90 / \%d97-122
DIGIT    = \%d48-57
HYPHEN   = \%d45
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_alphanum_hyphen(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiAlphaNumPlus(acpPhrase, uiMaxPhraseLength, UDTLIB_HYPHEN);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for an alphanumeric string, including underscore.

Equivalent SABNF syntax:
<pre>
ALPHANUM = ALPHA *(ALPHA / DIGIT / UNDER)
ALPHA    = \%d65-90 / \%d97-122
DIGIT    = \%d48-57
UNDER    = \%d95
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_alphanum_under(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiAlphaNumPlus(acpPhrase, uiMaxPhraseLength, UDTLIB_UNDERSCORE);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a decimal number.

Equivalent SABNF syntax:
<pre>
DECNUM = 1*DIGIT
DIGIT  = \%d48-57
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_decnum(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		if(uiIsDigit(acpPhrase[uiPhraseCount])){uiPhraseCount++;}
		else{break;}
	}
	if(uiPhraseCount){spData->uiPhraseLength = uiPhraseCount;}
	else{spData->uiPhraseLength = APG_UNDEFINED;};
	return 0;
}

/** Phrase recognizer for a hexidecimal number.

Equivalent SABNF syntax:
<pre>
HEXNUM   = "0x" 1*HEXDIGIT
HEXDIGIT = \%d48-57 / \%d65-70 / \%d97-102
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_hexnum(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	if((uiPhraseCount + 1) < uiMaxPhraseLength){
		if((acpPhrase[uiPhraseCount] == UDTLIB_0) &&
		(acpPhrase[uiPhraseCount + 1] == UDTLIB_LOWER_X)){
			uiPhraseCount += 2;
			while(uiPhraseCount < uiMaxPhraseLength){
				if(uiIsHexDigit(acpPhrase[uiPhraseCount])){uiPhraseCount++;}
				else{break;}
			}
		}
	}
	if(uiPhraseCount){spData->uiPhraseLength = uiPhraseCount;}
	else{spData->uiPhraseLength = APG_UNDEFINED;};
	return 0;
}

/** Phrase recognizer for a quoted string, a string beginning and ending with a single (') or double (") quote.

Equivalent SABNF syntax:
<pre>
QUOTEDSTRING = SINGLEQUOTE / DOUBLEQUOTE
SINGLEQUOTE  = \%d39 *(\%d9 / \%d32-38 / \%d40-127) \%d39
DOUBLEQUOTE  = \%d34 *(\%d9 / \%d32-33 / \%d35-127) \%d34
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_quotedstring(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiTest;
	if((uiTest = uiSingleQuotedString(acpPhrase, uiMaxPhraseLength))){spData->uiPhraseLength = uiTest;}
	else if((uiTest = uiDoubleQuotedString(acpPhrase, uiMaxPhraseLength))){spData->uiPhraseLength = uiTest;}
	else{spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a single-quoted string, a string beginning and ending with a single quote (').

Equivalent SABNF syntax:
<pre>
SINGLEQUOTE = \%d39 *(\%d9 / \%d32-38 / \%d40-127) \%d39
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_singlequotedstring(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiSingleQuotedString(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}

/** Phrase recognizer for a double-quoted string, a string beginning and ending with a double quote (").

Equivalent SABNF syntax:
<pre>
DOUBLEQUOTE = \%d34 *(\%d9 / \%d32-33 / \%d35-127) \%d34
</pre>
@param spData data struct passed to this function by the Parser
@return 0 - return ignored by Parser
*/
apg_uint uiUdtLib_u_doublequotedstring(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiDoubleQuotedString(acpPhrase, uiMaxPhraseLength);
	if(!spData->uiPhraseLength){spData->uiPhraseLength = APG_UNDEFINED;}
	return 0;
}
