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

#include "Apg.h"
#include "Private.h"
/** \file ApgLib/Tools.c \brief A small chest of helpful tools.

*/

// default alert(error) handler
void vDefaultAlertHandler(unsigned int uiLine, const char* cpFile){
	exit(EXIT_FAILURE);
}

/** Case-insensitive: compares two strings.
The two strings are compared, character for character.
NOTE: stricmp() is non-ANSI and therefore, not used
@param cpLhs pointer to the left of the two strings to compare
@param cpRhs pointer to the right of the two strings to compare
@return 0 if the two strings are case-insensitively equal<br>
-1 if the left string is less than the right string<br>
+1 if the left string is greater than the right string
*/
int apg_stricmp(const char* cpLhs, const char* cpRhs)
{
  apg_uint uiLhsEmpty = APG_FALSE;
  apg_uint uiRhsEmpty = APG_FALSE;

  // handle any empty strings
  if(cpLhs == NULL || *cpLhs == 0){uiLhsEmpty = APG_TRUE;}
  if(cpRhs == NULL || *cpRhs == 0){uiRhsEmpty = APG_TRUE;}
  if(uiLhsEmpty && uiRhsEmpty){return 0;}
  if(uiLhsEmpty){return -1;}
  if(uiRhsEmpty){return 1;}

  // compare the strings
  while(APG_TRUE)
  {
    char cLhs = *cpLhs;
    char cRhs = *cpRhs;
    if(cLhs >= 65 && cLhs <= 90){cLhs += 32;}
    if(cRhs >= 65 && cRhs <= 90){cRhs += 32;}
    if(cLhs < cRhs){return -1;}
    if(cLhs > cRhs){return 1;}
    if(cLhs == 0){return 0;}
    cpLhs++;
    cpRhs++;
  }
  return 0; // never reached - just to keep the parser from complaining about no return function
}

/** Convert an ASCII, 8-bit character string to an apg_achar character string.
@param acpAChars pointer to the apg_achar character string
@param cpChars pointer to the 8-bit character string to convert
@param uiLen the number of characters to convert
*/
void vCharToAChar(apg_achar* acpAChars, const char* cpChars, apg_uint uiLen){
	if(acpAChars && cpChars && uiLen){
		apg_achar* acpACharsEnd = acpAChars + uiLen;
		for(; acpAChars < acpACharsEnd; acpAChars++, cpChars++)
			*acpAChars = (apg_achar)*cpChars;
	}
}

static char g_caTrans[17] = {'0','1', '2','3','4','5','6','7','8','9','A','B','C','D','E','F','X'};
static apg_uint uiAddDigit(char* cpAdd, apg_achar tChar, apg_uint uiSize, apg_uint uiShift, apg_uint* uipLeadingNonZero){
    apg_uint uiRet = 0;

    // NOTE: this weird masking of bits is to avoid compiler warning about integer constants being to big on 32-bit machines.
    unsigned long int uiMaskGen = 0xF;
    unsigned long int uiSizeof = uiSize * 8;
    unsigned long int uiShiftBits = uiSizeof - uiShift;
    unsigned long int uiMask = uiMaskGen << uiShiftBits;
    char cHex = (tChar & uiMask) >> uiShiftBits;
    if(*uipLeadingNonZero){
        cpAdd[0] = g_caTrans[(unsigned int)cHex];
        uiRet = 1;
    } else if(cHex > 0){
        cpAdd[0] = g_caTrans[(unsigned int)cHex];
        *uipLeadingNonZero = APG_TRUE;
        uiRet = 1;
    }
    return uiRet;
}
static apg_uint uiAddHex(char* cpAdd, apg_achar tChar, apg_uint uiSize){
	apg_uint uiRet = 0;
	apg_uint uiError = APG_FALSE;
	apg_uint uiLeadingNonZero = APG_FALSE;
	cpAdd[uiRet++] = '\\';
	cpAdd[uiRet++] = 'x';
	switch(uiSize){
	case 1:
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 4, &uiLeadingNonZero);
		break;
	case 2:
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 4, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 8, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 12, &uiLeadingNonZero);
		break;
	case 4:
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 4, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 8, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 12, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 16, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 20, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 24, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 28, &uiLeadingNonZero);
		break;
	case 8:
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 4, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 8, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 12, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 16, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 20, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 24, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 28, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 32, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 36, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 40, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 44, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 48, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 52, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 56, &uiLeadingNonZero);
        uiRet += uiAddDigit(&cpAdd[uiRet], tChar, uiSize, 60, &uiLeadingNonZero);
		break;
	default:
		uiError = APG_TRUE;
		break;
	}
	if(!uiError){
		char cHex = tChar & 0x0F;
		cpAdd[uiRet++] = g_caTrans[(unsigned int)cHex];
	}
	return uiRet;
}

/** Calculate the size of the string translated by uiACharToString()
@param acpAChars pointer the apg_achar character string
@param uiALen the number of apg_achar characters
@see uiACharToString()
@return the calculated size
*/
apg_uint uiACharToStringSize(const apg_achar* acpAChars, apg_uint uiALen){
	char caCharBuf[20];
	apg_uint i;
	apg_achar acChar;
	apg_uint uiStrLen;
	apg_uint uiSize = sizeof(apg_achar);
	uiStrLen = 0;
	for(i = 0; i < uiALen; i++){
		acChar = acpAChars[i];
		if(acChar < (apg_achar)20 || acChar > (apg_achar)127){
			uiStrLen += uiAddHex(&caCharBuf[0], acChar, uiSize);
		} else{
			uiStrLen++;
		}
	}
	return uiStrLen + 1;
}

/** Converts a string of alphabet characters to a null-terminated printable ASCII string.
Non-printing characters are of the form: <xFF>.
Brackets are used to distinguish the hex format from adjacent printing characters of "x" and "F", for example.
The worst case scenario is that all translated characters will be of the form <xFF>, where sizeof(apg_achar) is 1 for example.
To be safe, the cpChars buffer size, uiCLen, should be at least:
uiALen * ((sizeof(apg_achar) * 2) + 3)
plus 1 for terminating null. To get the exact size in advance, see uiACharToStringSize().
@param cpChars pointer to the buffer to receive the printable, 8-bit character string
@param uiCLen length of the cpChars buffer
@param acpAChars pointer the apg_achar character string
@param uiALen the number of apg_achar characters
@see uiACharToStringSize()
@return the number of apg_achar characters translated. If < uiAlen, the translation was truncated due to insufficient buffer length, uiCLen
*/
apg_uint uiACharToString(char* cpChars, apg_uint uiCLen, const apg_achar* acpAChars, apg_uint uiALen){
	char caCharBuf[20];
	apg_uint i = 0;
	apg_achar acChar;
	char* cpNextChar;
	const apg_achar* cpBufferEnd;
	apg_uint uiCharLen, uiStrLen;
	apg_uint uiCLenMax;
	apg_uint uiSize = sizeof(apg_achar);
	cpNextChar = cpChars;
	if(acpAChars && uiALen && cpChars && uiCLen){
		cpBufferEnd = acpAChars + uiALen;
		uiCLenMax = uiCLen - 1;
		uiStrLen = 0;
		for(i = 0; i < uiALen && uiStrLen < uiCLenMax; i++){
			acChar = acpAChars[i];
			if(acChar < (apg_achar)20 || acChar > (apg_achar)127){
				uiCharLen = uiAddHex(&caCharBuf[0], acChar, uiSize);
				if(uiStrLen + uiCharLen > uiCLenMax){break;}
			} else{
				uiCharLen = 1;
				caCharBuf[0] = (char)acChar;
			}
			memcpy((void*)cpNextChar, (void*)&caCharBuf[0], uiCharLen * sizeof(char));
			uiStrLen += uiCharLen;
			cpNextChar += uiCharLen;
		}
	}
	*cpNextChar = 0;
	return i;
}

/** \cond NOSHOW */
void* vpStrBufInit(void* vpBuf, apg_uint uiBufLen){
	void* vpRet = NULL;
	PRINTBUF* spBuf = NULL;
	apg_uint uiOverhead = (apg_uint)sizeof(PRINTBUF) + 1;
	if(vpBuf && uiBufLen > uiOverhead){
		memset(vpBuf, 0, (sizeof(char) * uiBufLen));
		spBuf = (PRINTBUF*)vpBuf;
		spBuf->cpBuffer = (char*)vpBuf + sizeof(PRINTBUF);
		spBuf->uiBufLen = uiBufLen - uiOverhead;
		spBuf->uiBufCount = 0;
		spBuf->uiBufIsTruncated = APG_FALSE;
		spBuf->vpValidate = vpBuf;
		vpRet = vpBuf;
	}
	return vpRet;
}
apg_uint uiStrBufCat(void* vpBuf, char* cpString){
	PRINTBUF* spBuf = (PRINTBUF*)vpBuf;
	apg_uint uiRet = 0;
	apg_uint uiStrLen;
	apg_uint i;
	if(spBuf && (spBuf->vpValidate == vpBuf) && cpString && cpString[0]){
		uiStrLen = strlen(cpString);
		for(i = 0; (i < uiStrLen) && (spBuf->uiBufCount < spBuf->uiBufLen); i++){
			spBuf->cpBuffer[spBuf->uiBufCount] = cpString[i];
			spBuf->uiBufCount++;
			uiRet++;
		}
		spBuf->cpBuffer[spBuf->uiBufCount] = 0;
		spBuf->uiBufIsTruncated = (apg_uint)(uiRet < uiStrLen);
	}
	return uiRet;
}
char* cpStrBufString(void* vpBuf){
	PRINTBUF* spBuf = (PRINTBUF*)vpBuf;
	char* cpRet = NULL;
	if(spBuf && (spBuf->vpValidate == vpBuf)){
		cpRet = spBuf->cpBuffer;
	}
	return cpRet;
}
apg_uint uiStrBufCount(void* vpBuf){
	PRINTBUF* spBuf = (PRINTBUF*)vpBuf;
	apg_uint uiRet = 0;
	if(spBuf && (spBuf->vpValidate == vpBuf)){
		uiRet = spBuf->uiBufCount;
	}
	return uiRet;
}
apg_uint uiStrBufSize(void* vpBuf){
	PRINTBUF* spBuf = (PRINTBUF*)vpBuf;
	apg_uint uiRet = 0;
	if(spBuf && (spBuf->vpValidate == vpBuf)){
		uiRet = spBuf->uiBufLen;
	}
	return uiRet;
}
apg_uint uiStrBufIsTruncated(void* vpBuf){
	PRINTBUF* spBuf = (PRINTBUF*)vpBuf;
	apg_uint uiRet = APG_FALSE;
	if(spBuf && (spBuf->vpValidate == vpBuf)){
		uiRet = spBuf->uiBufIsTruncated;
	}
	return uiRet;
}

char* cpApgVersion(){return "6.3";}
char* cpApgAuthor(){return "Lowell D. Thomas";}
char* cpApgDescription(){return "APG - an ABNF Parser Generator";}
char* cpApgCopyright(){return "Copyright (C) 2005 - 2012 Lowell D. Thomas, all rights reserved";}
char* cpApgEmail(){return "lowell@coasttocoastresearch.com";}
char* cpApgWebsite(){return "http://www.coasttocoastresearch.com";}
char* cpApgGPLNotice(){
	static char* apg_cpApgGPLNotice =
			"  This program is free software: you can redistribute it and/or modify\n"
			"  it under the terms of the GNU General Public License as published by\n"
			"  the Free Software Foundation, either version 2 of the License, or\n"
			"  (at your option) any later version.\n"
			"\n"
			"  This program is distributed in the hope that it will be useful,\n"
			"  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
			"  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
			"  GNU General Public License for more details.\n"
			"\n"
			"  You should have received a copy of the GNU General Public License\n"
			"  along with this program.  If not, see\n"
			"  <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>\n"
			"  or write to the Free Software Foundation, Inc.,\n"
			"  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.\n";

	return apg_cpApgGPLNotice;
}
/** \endcond */
