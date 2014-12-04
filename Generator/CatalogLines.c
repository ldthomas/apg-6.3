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
#include "Generator.h"

#define CASSERT(cond) if(!(cond)){spCtx->pfnAlertHandler(__LINE__, __FILE__);}

void* vpCatalogCtor(void* vpMemCtx, void* vpAlertHandler){
	void* vpRet = NULL;
	void* vpVec = NULL;
	CATALOG_CTX* spCtx = NULL;
	while(APG_TRUE){
		if(!vpMemCtx){break;}
		vpVec = vpVecCtor(vpMemCtx, sizeof(CATALOG_LINE), 500);
		if(!vpVec){break;}
		spCtx = (CATALOG_CTX*)vpMemAlloc(vpMemCtx, sizeof(CATALOG_CTX));
		if(!spCtx){break;}
		memset((void*)spCtx, 0, sizeof(CATALOG_CTX));
		spCtx->vpMemCtx = vpMemCtx;
		spCtx->vpVecLines = vpVec;
		spCtx->uiIterNext = 0;
		if(vpAlertHandler){spCtx->pfnAlertHandler = (PFN_ALERT)vpAlertHandler;}
		else{spCtx->pfnAlertHandler = vTerminalAlert;}

		// success
		vpRet = (void*)spCtx;
		break;
	}
	return vpRet;
}

void vCatalogDtor(void* vpCtx){
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	void* vpMemCtx;
	if(spCtx){
		vpMemCtx = spCtx->vpMemCtx;
		vVecDtor(spCtx->vpVecLines);
		memset((void*)spCtx, 0, sizeof(CATALOG_CTX));
		vMemFree(vpMemCtx, vpCtx);
	}
}

CATALOG_LINE* spCatalogIterInit(void* vpCtx){
	CATALOG_LINE* spRet = NULL;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	if(spCtx){
		spCtx->uiIterNext = 0;
		spRet = (CATALOG_LINE*)vpVecFront(spCtx->vpVecLines);
		if(spRet){spCtx->uiIterNext = 1;}
	}
	return spRet;
}

CATALOG_LINE* spCatalogIterNext(void* vpCtx){
	CATALOG_LINE* spRet = NULL;
	void* vpLine;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	if(spCtx){
		vpLine = vpVecAt(spCtx->vpVecLines, spCtx->uiIterNext);
		if(vpLine){
			spCtx->uiIterNext++;
			spRet = (CATALOG_LINE*)vpLine;
		}
	}
	return spRet;
}

G_UINT uiCatalogLines(void* vpCtx, char* cpSrc, G_UINT uiSrcLen){
	G_UINT uiRet = 0;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	  G_UINT uiCharBeg = 0;
	  G_UINT uiCharEnd = 0;
	  G_UINT uiLine = 0;
	  CATALOG_LINE* spLine;
	  char* cpLine = cpSrc;
	  char* cpBeg = cpSrc;
	  char* cpEnd = cpBeg + uiSrcLen;
	  if(vpCtx && cpSrc && uiSrcLen){
		  vVecClear(spCtx->vpVecLines);
		  spCtx->cpSrc = cpSrc;
		  spCtx->uiSrcLen = uiSrcLen;
		  spCtx->uiIterNext = 0;
		  for(; cpBeg < cpEnd; ++cpBeg, ++uiCharEnd)
		  {
		    if(*cpBeg == 13)
		    {
		      if(cpBeg[1] == 10)
		      {
		        // line ends with CRLF
		        spLine = vpVecPush(spCtx->vpVecLines, NULL);
		        CASSERT(spLine);
		        spLine->uiBegChar = uiCharBeg;
		        spLine->uiEndChar = uiCharBeg + uiCharEnd;
		        spLine->cpBeg = cpSrc + spLine->uiBegChar;
		        spLine->cpEnd = cpSrc + spLine->uiEndChar;
		        spLine->cpLine = cpLine;
		        spLine->uiLineLen = uiCharEnd + 2;
		        spLine->uiLineEndLen = 2;
		        spLine->uiLineNo = uiLine;
		        uiLine++;
		        uiCharBeg += uiCharEnd + 2;
		        uiCharEnd = -1;
		        cpBeg += 1;
		        cpLine = cpBeg + 1;
		        continue;
		      }
		      else
		      {
		        // line ends with CR only
		        spLine = vpVecPush(spCtx->vpVecLines, NULL);
		        CASSERT(spLine);
		        spLine->uiBegChar = uiCharBeg;
		        spLine->uiEndChar = uiCharBeg + uiCharEnd;
		        spLine->cpBeg = cpSrc + spLine->uiBegChar;
		        spLine->cpEnd = cpSrc + spLine->uiEndChar;
		        spLine->cpLine = cpLine;
		        spLine->uiLineLen = uiCharEnd + 1;
		        spLine->uiLineEndLen = 1;
		        spLine->uiLineNo = uiLine;
		        uiLine++;
		        uiCharBeg += uiCharEnd + 1;
		        uiCharEnd = -1;
		        cpLine = cpBeg + 1;
		        continue;
		      }
		    }

		    if(*cpBeg == 10)
		    {

		      // line ends with LR only
		        spLine = vpVecPush(spCtx->vpVecLines, NULL);
		        CASSERT(spLine);
		        spLine->uiBegChar = uiCharBeg;
		        spLine->uiEndChar = uiCharBeg + uiCharEnd;
		        spLine->cpBeg = cpSrc + spLine->uiBegChar;
		        spLine->cpEnd = cpSrc + spLine->uiEndChar;
		        spLine->cpLine = cpLine;
		        spLine->uiLineLen = uiCharEnd + 1;
		        spLine->uiLineEndLen = 1;
		        spLine->uiLineNo = uiLine;
		      uiLine++;
		      uiCharBeg += uiCharEnd + 1;
		      uiCharEnd = -1;
		      cpLine = cpBeg + 1;
		      continue;
		    }
		  }
		if(uiCharEnd > 0)
		{
		  // print the last line in case it has no line ender
			spLine = vpVecPush(spCtx->vpVecLines, NULL);
			CASSERT(spLine);
	        spLine->uiBegChar = uiCharBeg;
	        spLine->uiEndChar = uiCharBeg + uiCharEnd;
	        spLine->cpBeg = cpSrc + spLine->uiBegChar;
	        spLine->cpEnd = cpSrc + spLine->uiEndChar;
			spLine->cpLine = cpLine;
			spLine->uiLineLen = uiCharEnd;
	        spLine->uiLineEndLen = 0;
			spLine->uiLineNo = uiLine;
		}
		uiRet = uiVecSize(spCtx->vpVecLines);
	  }
	  return uiRet;
}

CATALOG_LINE* spCatalogGetLine(void* vpCtx, G_UINT uiLineNo){
	CATALOG_LINE* spRet = NULL;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	if(spCtx){
		CATALOG_LINE* spLine = (CATALOG_LINE*)vpVecAt(spCtx->vpVecLines, uiLineNo);
		if(spLine){spRet = spLine;}
	}
	return spRet;
}

G_UINT uiCatalogLineCount(void* vpCtx){
	G_UINT uiRet = 0;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	if(vpCtx){
	  uiRet = uiVecSize(spCtx->vpVecLines);
	}
	return uiRet;
}

G_UINT uiCatalogFindLine(void* vpCtx, G_UINT uiOffset){
	G_UINT uiRet = APG_UNDEFINED;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	if(vpCtx){
		CATALOG_LINE* spLine = (CATALOG_LINE*)vpVecFront(spCtx->vpVecLines);
		G_UINT uiCount = uiVecSize(spCtx->vpVecLines);
		G_UINT i = 0;
		for(; i < uiCount; i++, spLine++){
			if(uiOffset >= spLine->uiBegChar && uiOffset <= spLine->uiEndChar){
				uiRet = i;
				break;
			}
		}
	}
	return uiRet;
}

static G_UINT uiAddLF(char* cpAdd){
	cpAdd[0] = '<';
	cpAdd[1] = 'L';
	cpAdd[2] = 'F';
	cpAdd[3] = '>';
	return 4;
}
static G_UINT uiAddCR(char* cpAdd){
	cpAdd[0] = '<';
	cpAdd[1] = 'C';
	cpAdd[2] = 'R';
	cpAdd[3] = '>';
	return 4;
}
static G_UINT uiAddTab(char* cpAdd){
	cpAdd[0] = '<';
	cpAdd[1] = 'T';
	cpAdd[2] = 'A';
	cpAdd[3] = 'B';
	cpAdd[4] = '>';
	return 5;
}
#define ELIPSIS_LEN 5
static G_UINT uiAddElipsis(char* cpAdd){
	cpAdd[0] = '<';
	cpAdd[1] = '.';
	cpAdd[2] = '.';
	cpAdd[3] = '.';
	cpAdd[4] = '>';
	return ELIPSIS_LEN;
}
static G_UINT uiAddNull(char* cpAdd){
	cpAdd[0] = '<';
	cpAdd[1] = 'n';
	cpAdd[2] = 'u';
	cpAdd[3] = 'l';
	cpAdd[4] = 'l';
	cpAdd[5] = '>';
	return 6;
}
static char g_caTrans[17] = {'0','1', '2','3','4','5','6','7','8','9','A','B','C','D','E','F','X'};
static G_UINT uiAddDigit(char* cpAdd, apg_achar tChar, G_UINT uiSize, G_UINT uiShift, G_UINT* uipLeadingNonZero){
    G_UINT uiRet = 0;

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
static G_UINT uiAddHex(char* cpAdd, apg_achar tChar, G_UINT uiSize){
	G_UINT uiRet = 0;
	G_UINT uiError = APG_FALSE;
	G_UINT uiLeadingNonZero = APG_FALSE;
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
void vCatalogDisplayLine(CATALOG_LINE* spLine, char* cpBuffer, G_UINT uiBufLen){
	G_UINT i;
	G_UINT uiSize = sizeof(G_UINT);
	unsigned char ucChar;
	char* cpNextChar;
	char* cpBufferEnd;
	if(cpBuffer && (uiBufLen > (ELIPSIS_LEN + 1))){
		cpBufferEnd = cpBuffer + uiBufLen - ELIPSIS_LEN - 1;
		cpNextChar = cpBuffer;
		for(i = 0; i < spLine->uiLineLen; i++){
			if(cpNextChar >= cpBufferEnd){
				cpNextChar += uiAddElipsis(cpNextChar);
				break;
			}
			ucChar = (unsigned char)spLine->cpBeg[i];
			if(ucChar == CR){cpNextChar += uiAddCR(cpNextChar);}
			else if(ucChar == TAB){cpNextChar += uiAddTab(cpNextChar);}
			else if(ucChar == LF){cpNextChar += uiAddLF(cpNextChar);}
			else if(ucChar < SP || ucChar > ASCII_END){cpNextChar += uiAddHex(cpNextChar, ucChar, uiSize);}
			else{*cpNextChar++ = (char)ucChar;}
		}
		if(((cpNextChar < cpBufferEnd)) && spLine->uiLineEndLen == 0){cpNextChar += uiAddNull(cpNextChar);}
		*cpNextChar = 0;
	}
}

void vCatalogDisplay(void* vpCtx, FILE* spOut){
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCtx;
	char caBuffer[2 * MAX_DISPLAY_LINE_LEN + 10];
	G_UINT j, uiLines;
	G_UINT uiRuleNo;
	CATALOG_LINE* spLine = NULL;
	if(spCtx){
		if(spOut == NULL){spOut = stdout;}
		uiLines = uiVecSize(spCtx->vpVecLines);
		spLine = (CATALOG_LINE*)vpVecFront(spCtx->vpVecLines);
		fprintf(spOut, "  r : rule definition number (zero-based)\n");
		fprintf(spOut, "  l : line number (zero-based)\n");
		fprintf(spOut, "  b : beginning character number (zero-based)\n");
		fprintf(spOut, "  e : ending character number\n");
		fprintf(spOut, "  n : number of characters\n");
		fprintf(spOut, "[%3s, %3s, %3s, %3s, %3s] %s\n", "r", "l", "b", "e", "n", "line");
		fprintf(spOut, "[%3s, %3s, %3s, %3s, %3s] %s\n", "---", "---", "---", "---", "---", "----");
		uiRuleNo = 0;
		for(j = 0; j < uiLines; j++, spLine++){
			vCatalogDisplayLine(spLine, &caBuffer[0], MAX_DISPLAY_LINE_LEN);
			if(((caBuffer[0] >= (char)65) && (caBuffer[0] <= (char)90)) ||
					((caBuffer[0] >= (char)97) && (caBuffer[0] <= (char)122))){
				fprintf(spOut, "[%3lu, %3lu, %3lu, %3lu, %3lu] %s\n",
						(G_UINT)uiRuleNo, (G_UINT)spLine->uiLineNo, (G_UINT)spLine->uiBegChar,
						(G_UINT)spLine->uiEndChar, (G_UINT)spLine->uiLineLen, &caBuffer[0]);
				uiRuleNo++;
			} else{
				fprintf(spOut, "[%3s, %3lu, %3lu, %3lu, %3lu] %s\n",
						"-", (G_UINT)spLine->uiLineNo, (G_UINT)spLine->uiBegChar,
						(G_UINT)spLine->uiEndChar, (G_UINT)spLine->uiLineLen, &caBuffer[0]);
			}
		}
	}
}
