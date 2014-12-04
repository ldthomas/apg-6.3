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

#include "main.h"
/** \file SIP/SIPUdtLib.c \brief All of the UDTs used in all of the tests.

All of the UDT callback functions used for all six parsing stages can be found in this file.
*/

/** \cond NOSHOW */
#define UDTLIB_TAB			(apg_achar)9
#define UDTLIB_LF 			(apg_achar)10
#define UDTLIB_CR 			(apg_achar)13
#define UDTLIB_SP 			(apg_achar)32
#define UDTLIB_DOUBLE_QUOTE	(apg_achar)34
#define UDTLIB_SINGLE_QUOTE	(apg_achar)39
#define UDTLIB_STAR 		(apg_achar)42
#define UDTLIB_PERIOD		(apg_achar)46
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
static apg_uint uiLineContinue(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiRet = 0;
	apg_uint uiTest;
	if((0 < uiMaxPhraseLength) && (uiTest = uiLineEnd(&acpPhrase[0], uiMaxPhraseLength))){
		if((uiTest < uiMaxPhraseLength) && acpPhrase[uiTest] == UDTLIB_SP){
			uiRet = uiTest + 1;
		}
	}
	return uiRet;
}
static apg_uint uiWsp(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	apg_uint uiLeft = uiMaxPhraseLength;
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

static apg_uint uiOneOrMoreAlphaDigit(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount;
	for(uiPhraseCount = 0; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		if(!(uiIsAlpha(acpPhrase[uiPhraseCount]) || uiIsDigit(acpPhrase[uiPhraseCount]))){break;}
	}
	return uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
}
static apg_uint uiZeroOrMoreHyphenAlphaDigit(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiLen1, uiLen2;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		for(uiLen1 = uiPhraseCount; uiLen1 < uiMaxPhraseLength; uiLen1++){
			if(acpPhrase[uiLen1] != UDTLIB_HYPHEN){break;}
		}
		if(uiLen1 == uiPhraseCount){break;}

		// must be followed by one or more alpha/digit
		for(uiLen2 = uiLen1; uiLen2 < uiMaxPhraseLength; uiLen2++){
			if(!(uiIsAlpha(acpPhrase[uiLen2]) || uiIsDigit(acpPhrase[uiLen2]))){break;}
		}
		if(uiLen2 == uiLen1){break;}
		uiPhraseCount = uiLen2;
	}
	return uiPhraseCount;
}
static apg_uint uiAlphaNum(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	if(uiPhraseCount < uiMaxPhraseLength && uiIsAlpha(acpPhrase[uiPhraseCount])){
		uiPhraseCount++;
		for(; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
			if(!(uiIsAlpha(acpPhrase[uiPhraseCount]) || uiIsDigit(acpPhrase[uiPhraseCount]))){break;}
		}
	}
	return uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
}
static apg_uint uiZeroOrMoreAlphaDigit(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount;
	for(uiPhraseCount = 0; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		if(!(uiIsAlpha(acpPhrase[uiPhraseCount]) || uiIsDigit(acpPhrase[uiPhraseCount]))){break;}
	}
	return uiPhraseCount;
}
static apg_uint uiRFC1035label(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	if((uiPhraseCount < uiMaxPhraseLength) && uiIsAlpha(acpPhrase[uiPhraseCount])){
		uiPhraseCount++;
		if(uiPhraseCount < uiMaxPhraseLength){
			uiPhraseCount += uiZeroOrMoreAlphaDigit(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		}
		if(uiPhraseCount < uiMaxPhraseLength){
			uiPhraseCount += uiZeroOrMoreHyphenAlphaDigit(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		}
	}
	return uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
}
static apg_uint uiRFC1035subdomain(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPeriod;
	apg_uint uiLabel;
	apg_uint uiPhraseCount = uiRFC1035label(acpPhrase, uiMaxPhraseLength);
	if(uiPhraseCount == APG_UNDEFINED){uiPhraseCount = 0;}
	else{
		while(uiPhraseCount < uiMaxPhraseLength){
			uiPeriod = uiPhraseCount;
			if(acpPhrase[uiPeriod] == UDTLIB_PERIOD){
				uiPeriod++;
				if(uiPeriod < uiMaxPhraseLength){
					uiLabel = uiRFC1035label(&acpPhrase[uiPeriod], uiMaxPhraseLength-uiPeriod);
					if(uiLabel != APG_UNDEFINED){
						uiPhraseCount = uiPeriod + uiLabel;
						continue;
					} else{break;}
				}else{break;}
			}else{break;}
			break;
		}
	}
	return uiPhraseCount;
}
static apg_uint uiSws(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiCrlf = 0;
	apg_uint uiStart2;
	apg_uint uiWhiteSpace1;
	apg_uint uiWhiteSpace2;
	apg_uint uiPhraseCount;
	//[*WSP CRLF]
	for(uiWhiteSpace1 = 0; uiWhiteSpace1 < uiMaxPhraseLength; uiWhiteSpace1++){
		if(!((acpPhrase[uiWhiteSpace1] == UDTLIB_SP) || (acpPhrase[uiWhiteSpace1] == UDTLIB_TAB))){break;}
	}
	uiCrlf = uiLineEnd(&acpPhrase[uiWhiteSpace1], uiMaxPhraseLength-uiWhiteSpace1);
	if(uiCrlf > 0){
		uiWhiteSpace2 = uiWhiteSpace1 + uiCrlf;
		uiStart2 = uiWhiteSpace2;
	}else{
		uiWhiteSpace2 = 0;
		uiStart2 = 0;
	}

	//1*WSP
	for(; uiWhiteSpace2 < uiMaxPhraseLength; uiWhiteSpace2++){
		if(!((acpPhrase[uiWhiteSpace2] == UDTLIB_SP) || (acpPhrase[uiWhiteSpace2] == UDTLIB_TAB))){break;}
	}
	uiPhraseCount =(uiWhiteSpace2 > uiStart2) ?  uiWhiteSpace2 : uiWhiteSpace1;
	return uiPhraseCount;
}
///////////////////////////////////////////////////////////////////////////////
// SIP UDT CALLBACK LIBRARY
///////////////////////////////////////////////////////////////////////////////
apg_uint uiSIP_e_domainlabel(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiItLen, uiItCount;
	while(uiPhraseCount < uiMaxPhraseLength){
		uiItLen = uiOneOrMoreAlphaDigit(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiItLen == APG_UNDEFINED){break;}
		uiItCount = uiItLen + uiPhraseCount;
		uiItLen = uiZeroOrMoreHyphenAlphaDigit(&acpPhrase[uiItCount], uiMaxPhraseLength-uiItCount);
		uiItCount += uiItLen;
		if(uiItCount >= uiMaxPhraseLength){break;}
		if(acpPhrase[uiItCount] != UDTLIB_PERIOD){break;}
		uiItCount++;
		if(!(uiIsAlpha(acpPhrase[uiItCount]) || uiIsDigit(acpPhrase[uiItCount]))){break;}
		uiPhraseCount = uiItCount;
	}
	spData->uiPhraseLength = uiPhraseCount;
	return 0;
}
apg_uint uiSIP_u_toplabel(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiLen = uiAlphaNum(acpPhrase, uiMaxPhraseLength);
	while(APG_TRUE){
		if((uiLen == APG_UNDEFINED)){break;}
		uiLen += uiZeroOrMoreHyphenAlphaDigit(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
		if(uiLen >= uiMaxPhraseLength){uiPhraseCount = uiLen;break;}
		if(acpPhrase[uiLen] == UDTLIB_PERIOD){uiLen++;}
		uiPhraseCount = uiLen;
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_token(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount;
	for(uiPhraseCount = 0; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		apg_achar acChar = acpPhrase[uiPhraseCount];
		if(uiIsAlpha(acChar)){continue;}
		if(uiIsDigit(acChar)){continue;}
		if(acChar == (apg_achar)33){continue;}
		if(acChar == (apg_achar)37){continue;}
		if(acChar == (apg_achar)39){continue;}
		if(acChar == (apg_achar)42){continue;}
		if(acChar == (apg_achar)43){continue;}
		if(acChar == (apg_achar)45){continue;}
		if(acChar == (apg_achar)46){continue;}
		if(acChar == (apg_achar)95){continue;}
		if(acChar == (apg_achar)96){continue;}
		if(acChar == (apg_achar)126){continue;}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_unreserved(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	while(uiMaxPhraseLength > 0){
		apg_achar acChar = acpPhrase[0];
		if(uiIsAlpha(acChar)){uiPhraseCount = 1;break;}
		if(uiIsDigit(acChar)){uiPhraseCount = 1;break;}
		if(acChar == (apg_achar)33){uiPhraseCount = 1;break;}
		if(acChar >= (apg_achar)39 && acChar <= (apg_achar)42){uiPhraseCount = 1;break;}
		if(acChar == (apg_achar)45){uiPhraseCount = 1;break;}
		if(acChar == (apg_achar)46){uiPhraseCount = 1;break;}
		if(acChar == (apg_achar)95){uiPhraseCount = 1;break;}
		if(acChar == (apg_achar)126){uiPhraseCount = 1;break;}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}
apg_uint uiSIP_u_one_or_more_unreserved(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		apg_achar acChar = acpPhrase[uiPhraseCount];
		if(uiIsAlpha(acChar)){uiPhraseCount++;continue;}
		if(uiIsDigit(acChar)){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)33){uiPhraseCount++;continue;}
		if(acChar >= (apg_achar)39 && acChar <= (apg_achar)42){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)45){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)46){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)95){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)126){uiPhraseCount++;continue;}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_scheme(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	if(uiIsAlpha(acpPhrase[0])){
		uiPhraseCount++;
		for(; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
			apg_achar acChar = acpPhrase[uiPhraseCount];
			if(uiIsAlpha(acChar)){continue;}
			if(uiIsDigit(acChar)){continue;}
			if(acChar == (apg_achar)'+'){continue;}
			if(acChar == (apg_achar)'-'){continue;}
			if(acChar == (apg_achar)'.'){continue;}
			break;
		}
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_callid(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	while(APG_TRUE){
		for(; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
			apg_achar acChar = acpPhrase[uiPhraseCount];
			if(uiIsAlpha(acChar)){continue;}
			if(uiIsDigit(acChar)){continue;}
			if(acChar == (apg_achar)'-'){continue;}
			if(acChar == (apg_achar)'.'){continue;}
			if(acChar == (apg_achar)'!'){continue;}
			if(acChar == (apg_achar)'%'){continue;}
			if(acChar == (apg_achar)'*'){continue;}
			if(acChar == (apg_achar)'_'){continue;}
			if(acChar == (apg_achar)'+'){continue;}
			if(acChar == (apg_achar)'`'){continue;}
			if(acChar == (apg_achar)'\''){continue;}
			if(acChar == (apg_achar)'~'){continue;}
			if(acChar == (apg_achar)'('){continue;}
			if(acChar == (apg_achar)')'){continue;}
			if(acChar == (apg_achar)'<'){continue;}
			if(acChar == (apg_achar)'>'){continue;}
			if(acChar == (apg_achar)':'){continue;}
			if(acChar == (apg_achar)'\\'){continue;}
			if(acChar == (apg_achar)'"'){continue;}
			if(acChar == (apg_achar)'/'){continue;}
			if(acChar == (apg_achar)'+'){continue;}
			if(acChar == (apg_achar)'['){continue;}
			if(acChar == (apg_achar)']'){continue;}
			if(acChar == (apg_achar)'?'){continue;}
			if(acChar == (apg_achar)'{'){continue;}
			if(acChar == (apg_achar)'}'){continue;}
			break;
		}
		if(uiPhraseCount == 0){break;}
		if(uiPhraseCount >= uiMaxPhraseLength){break;}
		if(acpPhrase[uiPhraseCount] != (apg_achar)'@'){break;}
		uiPhraseCount++;
		for(; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
			apg_achar acChar = acpPhrase[uiPhraseCount];
			if(uiIsAlpha(acChar)){continue;}
			if(uiIsDigit(acChar)){continue;}
			if(acChar == (apg_achar)'-'){continue;}
			if(acChar == (apg_achar)'.'){continue;}
			if(acChar == (apg_achar)'!'){continue;}
			if(acChar == (apg_achar)'%'){continue;}
			if(acChar == (apg_achar)'*'){continue;}
			if(acChar == (apg_achar)'_'){continue;}
			if(acChar == (apg_achar)'+'){continue;}
			if(acChar == (apg_achar)'`'){continue;}
			if(acChar == (apg_achar)'\''){continue;}
			if(acChar == (apg_achar)'~'){continue;}
			if(acChar == (apg_achar)'('){continue;}
			if(acChar == (apg_achar)')'){continue;}
			if(acChar == (apg_achar)'<'){continue;}
			if(acChar == (apg_achar)'>'){continue;}
			if(acChar == (apg_achar)':'){continue;}
			if(acChar == (apg_achar)'\\'){continue;}
			if(acChar == (apg_achar)'"'){continue;}
			if(acChar == (apg_achar)'/'){continue;}
			if(acChar == (apg_achar)'+'){continue;}
			if(acChar == (apg_achar)'['){continue;}
			if(acChar == (apg_achar)']'){continue;}
			if(acChar == (apg_achar)'?'){continue;}
			if(acChar == (apg_achar)'{'){continue;}
			if(acChar == (apg_achar)'}'){continue;}
			break;
		}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_rfc1035domain(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	if(uiMaxPhraseLength > 0){
		uiPhraseCount = uiRFC1035subdomain(acpPhrase, uiMaxPhraseLength);
		if(uiPhraseCount == 0 && acpPhrase[0] == UDTLIB_SP){uiPhraseCount++;}

		// should fail if ends in "." or "-"
		if(uiPhraseCount > 0){
			if((acpPhrase[uiPhraseCount] == UDTLIB_PERIOD) || (acpPhrase[uiPhraseCount] == UDTLIB_HYPHEN)){uiPhraseCount = 0;}
		}
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_LWS(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiSws(acpPhrase, uiMaxPhraseLength);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_e_SWS(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	spData->uiPhraseLength = uiSws(acpPhrase, uiMaxPhraseLength);
	return 0;
}

apg_uint uiSIP_u_HColon(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiWspLen = 0;
	apg_uint uiSwsLen = 0;
	uiWspLen = uiWsp(acpPhrase, uiMaxPhraseLength);
	uiMaxPhraseLength -= uiWspLen;
	if(uiMaxPhraseLength){
		if(acpPhrase[uiWspLen] == (apg_uint)':'){
			uiMaxPhraseLength--;
			uiWspLen++;
			uiSwsLen = uiWspLen + uiSws(&acpPhrase[uiWspLen], uiMaxPhraseLength);
		}
	}
	spData->uiPhraseLength = uiSwsLen ? uiSwsLen : APG_UNDEFINED;
	return 0;
}

static apg_uint uiHLetter(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength, apg_achar acLetter){
	apg_uint uiSwsLen1 = 0;
	apg_uint uiSwsLen2 = 0;
	uiSwsLen1 = uiSws(acpPhrase, uiMaxPhraseLength);
	uiMaxPhraseLength -= uiSwsLen1;
	if(uiMaxPhraseLength){
		if(acpPhrase[uiSwsLen1] == acLetter){
			uiMaxPhraseLength--;
			uiSwsLen1++;
			uiSwsLen2 = uiSwsLen1 + uiSws(&acpPhrase[uiSwsLen1], uiMaxPhraseLength);
		}
	}
	return uiSwsLen2;
}

static apg_uint uiHLeftLetter(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength, apg_achar acLetter){
	apg_uint uiSwsLen1;
	uiSwsLen1 = uiSws(acpPhrase, uiMaxPhraseLength);
	uiMaxPhraseLength -= uiSwsLen1;
	if(uiMaxPhraseLength){
		if(acpPhrase[uiSwsLen1] == acLetter){
			uiSwsLen1++;
		} else{uiSwsLen1 = 0;}
	}
	return uiSwsLen1;
}

static apg_uint uiHRightLetter(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength, apg_achar acLetter){
	apg_uint uiSwsLen1 = 0;
	if(uiMaxPhraseLength){
		if(acpPhrase[uiSwsLen1] == acLetter){
			uiSwsLen1 = 1 + uiSws(&acpPhrase[uiSwsLen1], uiMaxPhraseLength);
		}
	}
	return uiSwsLen1;
}

apg_uint uiSIP_u_Comma(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)',');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_Semi(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)';');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_Slash(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'/');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_Equal(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'=');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_Star(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'*');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_Colon(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)':');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_LParen(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'(');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_RParen(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)')');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_RAQuot(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHRightLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'>');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_LAQuot(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLeftLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)'<');
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_RDQuot(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHRightLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)34);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_LDQuot(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiHLeftLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)34);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_LHEX(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	if(uiMaxPhraseLength){
		if(uiIsDigit(acpPhrase[0]) ||
				((acpPhrase[0] >= (apg_achar)97) && (acpPhrase[0]) <= (apg_achar)102)){uiPhraseCount++;}
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_nc_value(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		if(uiIsDigit(acpPhrase[uiPhraseCount]) ||
				((acpPhrase[uiPhraseCount] >= (apg_achar)97) && (acpPhrase[uiPhraseCount]) <= (apg_achar)102)){uiPhraseCount++;}
		else{break;}
	}
	spData->uiPhraseLength = (uiPhraseCount == 8) ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_request_digest(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiHex;
	apg_uint uiRDQuot;
	apg_uint uiLDQuot = uiHLeftLetter(acpPhrase, uiMaxPhraseLength, (apg_achar)34);
	if(uiLDQuot){
		uiHex = uiLDQuot;
		while(uiHex < uiMaxPhraseLength){
			if(uiIsDigit(acpPhrase[uiHex]) ||
					((acpPhrase[uiHex] >= (apg_achar)97) && (acpPhrase[uiHex]) <= (apg_achar)102)){uiHex++;}
			else{break;}
		}
		if(uiHex == (uiLDQuot + 32)){
			uiRDQuot = uiHRightLetter(&acpPhrase[uiHex], uiMaxPhraseLength-uiHex, (apg_achar)34);
			if(uiRDQuot){uiPhraseCount = uiHex + uiRDQuot;}
		}
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_e_MessageBody(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	for(; uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		if(acpPhrase[uiPhraseCount] > (apg_achar)255){break;}
	}
	spData->uiPhraseLength = uiPhraseCount;
	return 0;
}

static apg_uint uiEscaped(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiRet = 0;
	if(uiMaxPhraseLength >= 3){
		if((acpPhrase[0] == (apg_achar)'%') && uiIsHexDigit(acpPhrase[1])  && uiIsHexDigit(acpPhrase[2])){uiRet = 3;}
	}
	return uiRet;
}
static apg_uint uiParamChars(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiEscapedLen;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		apg_achar acChar = acpPhrase[uiPhraseCount];
		if(uiIsAlpha(acChar)){uiPhraseCount++;continue;}
		if(uiIsDigit(acChar)){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)33){uiPhraseCount++;continue;}
		if(acChar >= (apg_achar)39 && acChar <= (apg_achar)42){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)45){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)46){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)95){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)126){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'['){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)']'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'/'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)':'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'&'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'+'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'&'){uiPhraseCount++;continue;}
		// escaped
		uiEscapedLen = uiEscaped(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiEscapedLen){uiPhraseCount += uiEscapedLen;continue;}
		break;
	}
	return uiPhraseCount;
}
apg_uint uiSIP_u_escaped(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiEscaped(acpPhrase, uiMaxPhraseLength);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}
apg_uint uiSIP_u_pname(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiParamChars(acpPhrase, uiMaxPhraseLength);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}
apg_uint uiSIP_u_pvalue(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiParamChars(acpPhrase, uiMaxPhraseLength);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

static apg_uint uiUtf8Cont(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		apg_achar acChar = acpPhrase[uiPhraseCount];
		if(acChar >= 0x80 && acChar <= 0xbf){uiPhraseCount++;}
		else{break;}
	}
	return uiPhraseCount;
}


static apg_uint uiTextUtf8Char(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength){
	apg_uint uiLen, uiCont;
	apg_uint uiPhraseCount = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		apg_achar acChar = acpPhrase[uiPhraseCount];

		// ASCII
		if(acChar >= 0x21 && acChar <= 0x7e){uiPhraseCount++;}

		// UTF8-NONASCII
		else if(acChar >= 0xc0 && acChar <= 0xdf){
			uiLen = uiPhraseCount + 1;
			uiCont = uiUtf8Cont(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
			if(uiCont == 1){uiPhraseCount += 2;}
			else{break;}
		}else if(acChar >= 0xe0 && acChar <= 0xef){
			uiLen = uiPhraseCount + 1;
			uiCont = uiUtf8Cont(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
			if(uiCont == 2){uiPhraseCount += 3;}
			else{break;}
		}else if(acChar >= 0xf0 && acChar <= 0xf7){
			uiLen = uiPhraseCount + 1;
			uiCont = uiUtf8Cont(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
			if(uiCont == 3){uiPhraseCount += 4;}
			else{break;}
		}else if(acChar >= 0xf8 && acChar <= 0xfb){
			uiLen = uiPhraseCount + 1;
			uiCont = uiUtf8Cont(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
			if(uiCont == 4){uiPhraseCount += 5;}
			else{break;}
		}else if(acChar >= 0xfc && acChar <= 0xfd){
			uiLen = uiPhraseCount + 1;
			uiCont = uiUtf8Cont(&acpPhrase[uiLen], uiMaxPhraseLength-uiLen);
			if(uiCont == 5){uiPhraseCount += 6;}
			else{break;}
		}else{break;}
	}
	return uiPhraseCount;
}

apg_uint uiSIP_e_text_utf8trim(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiTextUtf8Char(acpPhrase, uiMaxPhraseLength);
	apg_uint uiLws, uiMoreText;
	while(uiPhraseCount < uiMaxPhraseLength){
		uiLws = uiSws(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiLws){
			uiMoreText = uiTextUtf8Char(&acpPhrase[uiPhraseCount+uiLws], uiMaxPhraseLength-uiPhraseCount-uiLws);
			if(uiMoreText){
				uiPhraseCount += uiLws + uiMoreText;
			}else{break;}
		}else{break;}
	}
	spData->uiPhraseLength = uiPhraseCount;
	return 0;
}

apg_uint uiSIP_u_extension_header(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiText;
	while(uiPhraseCount < uiMaxPhraseLength){
		uiText = uiTextUtf8Char(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiText){uiPhraseCount += uiText;continue;}
		uiText = uiUtf8Cont(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiText){uiPhraseCount += uiText;continue;}
		uiText = uiSws(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiText){uiPhraseCount += uiText;continue;}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_OneOrMoreDigit(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	for(;uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		if(!uiIsDigit(acpPhrase[uiPhraseCount])){break;}
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}
apg_uint uiSIP_e_digit(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	for(;uiPhraseCount < uiMaxPhraseLength; uiPhraseCount++){
		if(!uiIsDigit(acpPhrase[uiPhraseCount])){break;}
	}
	spData->uiPhraseLength = uiPhraseCount;
	return 0;
}
apg_uint uiSIP_u_CRLF(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = uiLineEnd(acpPhrase, uiMaxPhraseLength);
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_IPv4address(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint i;
	apg_uint uiLenEven = 0;
	apg_uint uiLenOdd = 0;
	while(uiPhraseCount < uiMaxPhraseLength){
		for(i = 0; i < 3 && uiLenEven < uiMaxPhraseLength; i++, uiLenEven++){
			if(!uiIsDigit(acpPhrase[uiLenEven])){break;}
		}
		if(uiLenEven == uiLenOdd){break;}
		if(!(acpPhrase[uiLenEven] != (apg_achar)':')){break;}

		uiLenOdd = uiLenEven + 1;
		for(i = 0; i < 3 && uiLenOdd < uiMaxPhraseLength; i++, uiLenOdd++){
			if(!uiIsDigit(acpPhrase[uiLenOdd])){break;}
		}
		if(uiLenEven == uiLenOdd){break;}
		if(!(acpPhrase[uiLenOdd] != (apg_achar)':')){break;}

		uiLenEven = uiLenOdd +1;
		for(i = 0; i < 3 && uiLenEven < uiMaxPhraseLength; i++, uiLenEven++){
			if(!uiIsDigit(acpPhrase[uiLenEven])){break;}
		}
		if(uiLenEven == uiLenOdd){break;}
		if(!(acpPhrase[uiLenEven] != (apg_achar)':')){break;}

		uiLenOdd = uiLenEven + 1;
		for(i = 0; i < 3 && uiLenOdd < uiMaxPhraseLength; i++, uiLenOdd++){
			if(!uiIsDigit(acpPhrase[uiLenOdd])){break;}
		}
		if(uiLenEven == uiLenOdd){break;}
		uiPhraseCount = uiLenOdd;
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_user(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiEscLen;
	while(uiPhraseCount < uiMaxPhraseLength){
		apg_achar acChar = acpPhrase[uiPhraseCount];

		// u_one-or-more-unreserved
		if(uiIsAlpha(acChar)){uiPhraseCount++;continue;}
		if(uiIsDigit(acChar)){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)33){uiPhraseCount++;continue;}
		if(acChar >= (apg_achar)39 && acChar <= (apg_achar)42){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)45){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)46){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)95){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)126){uiPhraseCount++;continue;}

		// user-unreserved
		if(acChar == (apg_achar)'&'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'='){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'+'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'$'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)','){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)';'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'?'){uiPhraseCount++;continue;}
		if(acChar == (apg_achar)'/'){uiPhraseCount++;continue;}

		// u_escaped
		uiEscLen = uiEscaped(&acpPhrase[uiPhraseCount], uiMaxPhraseLength-uiPhraseCount);
		if(uiEscLen){uiPhraseCount += uiEscLen;continue;}
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

apg_uint uiSIP_u_quoted_string(APG_CBDATA* spData){
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	const apg_achar* acpNextPhrase;
	apg_uint uiNextMax;
	apg_uint uiPhraseCount = 0;
	apg_uint uiLen;
	apg_uint uiQuotedPair, uiNonAscii, uiTest;
	apg_achar acChar;
	while(APG_TRUE){
		// e_SWS
		uiLen = uiSws(acpPhrase, uiMaxPhraseLength);
		if(uiLen >= uiMaxPhraseLength){break;}

		// %x22 ('"')
		if(acpPhrase[uiLen] != (apg_achar)'"'){break;}
		uiLen++;
		if(uiLen >= uiMaxPhraseLength){break;}

		// q-string
		while(uiLen < uiMaxPhraseLength){
			acpNextPhrase = &acpPhrase[uiLen];
			uiNextMax = uiMaxPhraseLength - uiLen;

			// qdtext
			uiTest = uiSws(acpNextPhrase, uiNextMax);
			if(uiTest){uiLen += uiTest;continue;}
			// ASCII except '"' and '\'
			acChar = acpPhrase[uiLen];
			if(acChar == (apg_achar)0x21){uiLen++;continue;}
			if(acChar >= (apg_achar)0x23 && acChar <= (apg_achar)0x5b){uiLen++;continue;}
			if(acChar >= (apg_achar)0x5d && acChar <= (apg_achar)0x7e){uiLen++;continue;}
			// UTF8-NONASCII
			uiNonAscii = uiLen;
			while(uiNonAscii < uiMaxPhraseLength){
				if(acChar >= 0xc0 && acChar <= 0xdf){
					uiTest = uiNonAscii + 1;
					acpNextPhrase = &acpPhrase[uiTest];
					uiNextMax = uiMaxPhraseLength - uiTest;
					uiTest = uiUtf8Cont(acpNextPhrase, uiNextMax);
					if(uiTest == 1){uiNonAscii += 2;}
					else{break;}
				}else if(acChar >= 0xe0 && acChar <= 0xef){
					uiTest = uiNonAscii + 1;
					acpNextPhrase = &acpPhrase[uiTest];
					uiNextMax = uiMaxPhraseLength - uiTest;
					uiTest = uiUtf8Cont(acpNextPhrase, uiNextMax);
					if(uiTest == 2){uiNonAscii += 3;}
					else{break;}
				}else if(acChar >= 0xf0 && acChar <= 0xf7){
					uiTest = uiNonAscii + 1;
					acpNextPhrase = &acpPhrase[uiTest];
					uiNextMax = uiMaxPhraseLength - uiTest;
					uiTest = uiUtf8Cont(acpNextPhrase, uiNextMax);
					if(uiTest == 3){uiNonAscii += 4;}
					else{break;}
				}else if(acChar >= 0xf8 && acChar <= 0xfb){
					uiTest = uiNonAscii + 1;
					acpNextPhrase = &acpPhrase[uiTest];
					uiNextMax = uiMaxPhraseLength - uiTest;
					uiTest = uiUtf8Cont(acpNextPhrase, uiNextMax);
					if(uiTest == 4){uiNonAscii += 5;}
					else{break;}
				}else if(acChar >= 0xfc && acChar <= 0xfd){
					uiTest = uiNonAscii + 1;
					acpNextPhrase = &acpPhrase[uiTest];
					uiNextMax = uiMaxPhraseLength - uiTest;
					uiTest = uiUtf8Cont(acpNextPhrase, uiNextMax);
					if(uiTest == 5){uiNonAscii += 6;}
					else{break;}
				}else{break;}
				break;
			}
			if(uiNonAscii > uiLen){uiLen = uiNonAscii;continue;}

			// quoted-pair
			uiQuotedPair = uiLen;
			while(APG_TRUE){
				acpNextPhrase = &acpPhrase[uiQuotedPair];
				uiNextMax = uiMaxPhraseLength - uiQuotedPair;
				if(*acpNextPhrase != (apg_achar)'\\'){break;}
				uiQuotedPair++;
				if(uiQuotedPair >= uiMaxPhraseLength){break;}
				acChar = acpPhrase[uiQuotedPair];
				if(acChar <= (apg_achar)0x09){uiQuotedPair++;break;}
				if(acChar >= (apg_achar)0x0b && acChar <= (apg_achar)0x0c){uiQuotedPair++;break;}
				if(acChar >= (apg_achar)0x0e && acChar <= (apg_achar)0x7f){uiQuotedPair++;break;}
				break;
			}
			if(uiQuotedPair != uiLen + 2){break;}
			uiLen += 2;
		}

		// %x22 ('"')
		if(uiLen >= uiMaxPhraseLength){break;}
		acChar = acpPhrase[uiLen];
		if(acpPhrase[uiLen] != (apg_achar)'"'){break;}
		uiPhraseCount = uiLen + 1;
		break;
	}
	spData->uiPhraseLength = uiPhraseCount ? uiPhraseCount : APG_UNDEFINED;
	return 0;
}

enum {
    MSG_HDR_Accept = 0
,    MSG_HDR_Accept_Encoding
,    MSG_HDR_Accept_Language
,    MSG_HDR_Alert_Info
,    MSG_HDR_Allow
,    MSG_HDR_Authentication_Info
,    MSG_HDR_Authorization
,    MSG_HDR_Call_ID
,    MSG_HDR_Call_Info
,    MSG_HDR_Contact
,    MSG_HDR_Content_Disposition
,    MSG_HDR_Content_Encoding
,    MSG_HDR_Content_Language
,    MSG_HDR_Content_Length
,    MSG_HDR_Content_Type
,    MSG_HDR_CSeq
,    MSG_HDR_Date
,    MSG_HDR_Error_Info
,    MSG_HDR_Expires
,    MSG_HDR_From
,    MSG_HDR_In_Reply_To
,    MSG_HDR_Max_Forwards
,    MSG_HDR_MIME_Version
,    MSG_HDR_Min_Expires
,    MSG_HDR_Organization
,    MSG_HDR_Priority
,    MSG_HDR_Proxy_Authenticate
,    MSG_HDR_Proxy_Authorization
,    MSG_HDR_Proxy_Require
,    MSG_HDR_Record_Route
,    MSG_HDR_Reply_To
,    MSG_HDR_Require
,    MSG_HDR_Retry_After
,    MSG_HDR_Route
,    MSG_HDR_Server
,    MSG_HDR_Subject
,    MSG_HDR_Supported
,    MSG_HDR_Timestamp
,    MSG_HDR_To
,    MSG_HDR_Unsupported
,    MSG_HDR_User_Agent
,    MSG_HDR_Via
,    MSG_HDR_Warning
,    MSG_HDR_WWW_Authenticate
,    MSG_HDR_extension_header
,    MSG_HDR_COUNT
};
typedef struct{
	char* cpName;
	apg_uint uiLength;
} BNAMES;
static BNAMES saHdrNames[] = {
		{"accept", 6},
		{"accept-encoding", 15},
		{"accept-language", 15},
		{"alert-info", 10},
		{"allow", 5},
		{"authentication-info", 19},
		{"authorization", 13},
		{"call-id", 7},
		{"call-info", 9},
		{"contact", 7},
		{"content-disposition", 19},
		{"content-encoding", 16},
		{"content-language", 16},
		{"content-length", 14},
		{"content-type", 12},
		{"cseq", 4},
		{"date", 4},
		{"error-info", 10},
		{"expires", 7},
		{"from", 4},
		{"in-reply-to", 11},
		{"maxforwards", 11},
		{"mime-version", 12},
		{"min-expires", 11},
		{"organization", 12},
		{"priority", 8},
		{"proxy-authenticate", 18},
		{"proxy-authorization", 19},
		{"proxy-require", 13},
		{"record-route", 12},
		{"reply-to", 8},
		{"require", 7},
		{"retry-after", 11},
		{"route", 5},
		{"server", 6},
		{"subject", 7},
		{"supported", 9},
		{"timestamp", 9},
		{"to", 2},
		{"unsupported", 11},
		{"user-agent", 10},
		{"via", 3},
		{"warning", 7},
		{"www-authenticate", 16},
};
static apg_uint uiACharStricmp(const apg_achar* acpPhrase, apg_uint uiPhraseLength, BNAMES* spNames){
	apg_uint uiRet = 0;
	apg_uint i;
	char cChar;
	if(uiPhraseLength == spNames->uiLength){
		uiRet = uiPhraseLength;
		for(i = 0; i < uiPhraseLength; i++){
			cChar = (char)acpPhrase[i];
			if(cChar >= (char)65 && cChar <= (char)90){cChar += 32;}
			if(cChar != spNames->cpName[i]){uiRet = 0;break;}
		}
	}
	return uiRet;
}
static apg_uint uiMsgHdrName(const apg_achar* acpPhrase, apg_uint uiMaxPhraseLength, apg_uint* uipName, apg_uint* uipIsUdt){
	apg_uint uiHdr = 0;
	apg_uint uiNameId = UDT_GRAMMAR5_U_EXTENSION_HEADER;
	apg_uint uiIsUdt = APG_TRUE;
	apg_uint uiHColon;
	apg_uint uiNameLen = 0;
	apg_uint uiLen;
	char cChar;
	while(APG_TRUE){
		// get the name
		for(; uiNameLen < uiMaxPhraseLength; uiNameLen++){
			if(acpPhrase[uiNameLen] == (apg_achar)32 ||
					acpPhrase[uiNameLen] == (apg_achar)9 ||
					acpPhrase[uiNameLen] == (apg_achar)':'){break;}
		}
		if(uiNameLen == 0){break;} // name length must be > 0

		// get position of header
		for(uiHColon = uiNameLen; uiHColon < uiMaxPhraseLength; uiHColon++){
			if(!(acpPhrase[uiHColon] == (apg_achar)32 || acpPhrase[uiHColon] == (apg_achar)9)){break;}
		}
		if(acpPhrase[uiHColon] != (apg_achar)':'){break;} // end of space must be colon
		uiHdr = uiHColon + 1;
		while(uiHdr < uiMaxPhraseLength){
			if(acpPhrase[uiHdr] == (apg_achar)32){uiHdr++;continue;}
			if(acpPhrase[uiHdr] == (apg_achar)9){uiHdr++;continue;}
			uiLen = uiLineContinue(&acpPhrase[uiHdr], uiMaxPhraseLength-uiHdr);
			if(uiLen){uiHdr += uiLen;continue;}
			break;
		}

		cChar = (char)acpPhrase[0];
		if(cChar >= (char)65 && cChar <= (char)90){cChar += 32;}
		if(uiNameLen == 1){
			// get the abreviated header name
			switch(cChar){
			case 'i': uiNameId = UDT_GRAMMAR5_U_CALLID; uiIsUdt = APG_TRUE; break;
			case 'm': uiNameId = RULE_GRAMMAR5_CONTACT; uiIsUdt = APG_FALSE; break;
			case 'e': uiNameId = RULE_GRAMMAR5_CONTENT_ENCODING; uiIsUdt = APG_FALSE; break;
			case 'l': uiNameId = RULE_GRAMMAR5_CONTENT_LENGTH; uiIsUdt = APG_FALSE; break;
			case 'c': uiNameId = RULE_GRAMMAR5_CONTENT_TYPE; uiIsUdt = APG_FALSE; break;
			case 'f': uiNameId = RULE_GRAMMAR5_FROM; uiIsUdt = APG_FALSE; break;
			case 's': uiNameId = RULE_GRAMMAR5_SUBJECT; uiIsUdt = APG_FALSE; break;
			case 'k': uiNameId = RULE_GRAMMAR5_SUPPORTED; uiIsUdt = APG_FALSE; break;
			case 't': uiNameId = RULE_GRAMMAR5_TO; uiIsUdt = APG_FALSE; break;
			case 'v': uiNameId = RULE_GRAMMAR5_VIA; uiIsUdt = APG_FALSE; break;
			}
		} else{
			// identify the full header name
			switch(cChar){
			case 'a':
				switch(uiNameLen){
				case 5:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Allow]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ALLOW;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 6:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Accept]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ACCEPT;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 10:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Alert_Info]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ALERT_INFO;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 13:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Authorization]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_AUTHORIZATION;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 15:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Accept_Encoding]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ACCEPT_ENCODING;
						uiIsUdt = APG_FALSE;
					}else if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Accept_Language]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ACCEPT_LANGUAGE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 19:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Authentication_Info]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_AUTHENTICATION_INFO;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 'c':
				switch(uiNameLen){
				case 4:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_CSeq]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CSEQ;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 7:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Call_ID]) == uiNameLen){
						uiNameId = UDT_GRAMMAR5_U_CALLID;
						uiIsUdt = APG_TRUE;
					}else if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Contact]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTACT;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 9:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Call_Info]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CALL_INFO;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 12:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Content_Type]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTENT_TYPE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 14:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Content_Length]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTENT_LENGTH;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 16:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Content_Encoding]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTENT_ENCODING;
						uiIsUdt = APG_FALSE;
					}else if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Content_Language]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTENT_LANGUAGE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 19:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Content_Disposition]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_CONTENT_DISPOSITION;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 'd':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Date]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_DATE;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'e':
				if(uiNameLen == 7){
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Expires]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_EXPIRES;
						uiIsUdt = APG_FALSE;
					}
				} else if(uiNameLen == 10){
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Error_Info]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ERROR_INFO;
						uiIsUdt = APG_FALSE;
					}
				}
				break;
			case 'f':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_From]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_FROM;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'i':
			if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_In_Reply_To]) == uiNameLen){
				uiNameId = RULE_GRAMMAR5_REPLY_TO;
				uiIsUdt = APG_FALSE;
			}
				break;
			case 'm':
				switch(uiNameLen){
				case 11:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Min_Expires]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_MIN_EXPIRES;
						uiIsUdt = APG_FALSE;
					}else if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Max_Forwards]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_MAX_FORWARDS;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 12:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_MIME_Version]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_MIME_VERSION;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 'o':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Organization]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_ORGANIZATION;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'p':
				switch(uiNameLen){
				case 8:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Priority]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_PRIORITY;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 13:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Proxy_Require]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_PROXY_REQUIRE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 18:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Proxy_Authenticate]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_PROXY_AUTHENTICATE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 19:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Proxy_Authorization]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_PROXY_AUTHORIZATION;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 'r':
				switch(uiNameLen){
				case 5:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Route]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ROUTE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 7:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Require]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_REQUIRE;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 8:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Reply_To]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_REPLY_TO;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 11:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Retry_After]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_ALLOW;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 12:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Record_Route]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_RECORD_ROUTE;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 's':
				switch(uiNameLen){
				case 6:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Server]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_SERVER;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 7:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Subject]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_SUBJECT;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 9:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Supported]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_SUPPORTED;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			case 't':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_To]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_TO;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'u':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Unsupported]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_UNSUPPORTED;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'v':
				if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Via]) == uiNameLen){
					uiNameId = RULE_GRAMMAR5_VIA;
					uiIsUdt = APG_FALSE;
				}
				break;
			case 'w':
				switch(uiNameLen){
				case 7:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_Warning]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_WARNING;
						uiIsUdt = APG_FALSE;
					}
					break;
				case 16:
					if(uiACharStricmp(acpPhrase, uiNameLen, &saHdrNames[MSG_HDR_WWW_Authenticate]) == uiNameLen){
						uiNameId = RULE_GRAMMAR5_WWW_AUTHENTICATE;
						uiIsUdt = APG_FALSE;
					}
					break;
				default:
					break;
				}
				break;
			default:
				uiNameId = UDT_GRAMMAR5_U_EXTENSION_HEADER;
				uiIsUdt = APG_TRUE;
				break;
			}
		}
		// success
		break;
	}
	*uipName = uiNameId;
	*uipIsUdt = uiIsUdt;
	return uiHdr;
}
apg_uint uiSIP_e_message_header(APG_CBDATA* spData){
	const apg_achar* acpPhrase;
	apg_uint uiMaxPhraseLength;
	apg_uint uiNameId;
	apg_uint uiIsUdt;
	apg_uint uiEnd;
	apg_uint uiOffset = spData->uiPhraseOffset;
	apg_uint uiSaveOffset = spData->uiPhraseOffset;
	apg_uint uiPhraseCount = 0;
	apg_uint uiMsgLen = 0;
	apg_uint uiFoundLineEnd;
	acpPhrase = spData->acpSrc + uiOffset;
	uiMaxPhraseLength = spData->uiSrcLen - uiOffset;
	while(APG_TRUE){
		uiFoundLineEnd = uiLineEnd(acpPhrase, uiMaxPhraseLength);
		if(uiFoundLineEnd){break;} // if line begins with line end, no more headers
		uiMsgLen = uiMsgHdrName(acpPhrase, uiMaxPhraseLength, &uiNameId, &uiIsUdt);
		if(uiMsgLen){
			uiOffset += uiMsgLen;
			acpPhrase = spData->acpSrc + uiOffset;
			uiMaxPhraseLength = spData->uiSrcLen - uiOffset;
			if(uiIsUdt){
				vExecuteUdt(spData, uiNameId, uiOffset);
			} else{
 				vExecuteRule(spData, uiNameId, uiOffset);
			}
			if(spData->uiPhraseLength == APG_UNDEFINED){break;} // didn't find a valid header value
			uiOffset += spData->uiPhraseLength;
			acpPhrase = spData->acpSrc + uiOffset;
			uiMaxPhraseLength = spData->uiSrcLen - uiOffset;
		} else{break;} // didn't find a valid header name (eg. "name : ")

		// get the line end
		uiEnd = uiLineEnd(acpPhrase, uiMaxPhraseLength);
		if(uiEnd == 0){break;} // header value not followed by CRLF
		uiOffset += uiEnd;
		acpPhrase = spData->acpSrc + uiOffset;
		uiMaxPhraseLength = spData->uiSrcLen - uiOffset;
		uiPhraseCount = uiOffset - uiSaveOffset; // found a valid message-header, increment the phrase length
	}
	spData->uiPhraseOffset = uiSaveOffset;
	spData->uiPhraseLength = uiPhraseCount;
	return 0;
}
/** \endcond */
