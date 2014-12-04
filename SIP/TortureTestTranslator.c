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
/** \file SIP/TortureTestTranslator.c \brief Translates the text version of the torture test SIP messages into their binary format.
*/
/** \cond NOSHOW */
typedef unsigned char uchar;
/** \endcond */

static apg_uint uiLongLines(void* vpMemCtx, BSTR* spMsg, void* vpTransCtx);
static apg_uint uiBinaryCharacters(void* vpMemctx, BSTR* spMsg, void* vpTransCtx);
static apg_uint uiRepeatingStrings(void* vpMemCtx, BSTR* spMsg, void* vpTransCtx);

static char* g_cpLineEnd = "\n";
// quick convert from hex digit to integer
// quick character validation
static uchar ucaHexToInt[256] =
{
  255,255,255,255,255,255,255,255,255,255,  // 0
  255,255,255,255,255,255,255,255,255,255,  // 10
  255,255,255,255,255,255,255,255,255,255,  // 20
  255,255,255,255,255,255,255,255,255,255,  // 30
  255,255,255,255,255,255,255,255,  0,  1,  // 40
    2,  3,  4,  5,  6,  7,  8,  9,255,255,  // 50
  255,255,255,255,255, 10, 11, 12, 13, 14,  // 60
   15,255,255,255,255,255,255,255,255,255,  // 70
  255,255,255,255,255,255,255,255,255,255,  // 80
  255,255,255,255,255,255,255, 10, 11, 12,  // 90
   13, 14, 15,255,255,255,255,255,255,255,  // 100
  255,255,255,255,255,255,255,255,255,255,  // 110
  255,255,255,255,255,255,255,255,255,255,  // 120
  255,255,255,255,255,255,255,255,255,255,  // 130
  255,255,255,255,255,255,255,255,255,255,  // 140
  255,255,255,255,255,255,255,255,255,255,  // 150
  255,255,255,255,255,255,255,255,255,255,  // 160
  255,255,255,255,255,255,255,255,255,255,  // 170
  255,255,255,255,255,255,255,255,255,255,  // 180
  255,255,255,255,255,255,255,255,255,255,  // 190
  255,255,255,255,255,255,255,255,255,255,  // 200
  255,255,255,255,255,255,255,255,255,255,  // 210
  255,255,255,255,255,255,255,255,255,255,  // 220
  255,255,255,255,255,255,255,255,255,255,  // 230
  255,255,255,255,255,255,255,255,255,255,  // 240
  255,255,255,255,255,255                   // 250
};

/** Translates the text versions of the torture test messages to parsable binary format

Translates the "long lines", "non-printable characters"
and "long repeating strings" from the torture test SIP
messages given in <a href="http://datatracker.ietf.org/doc/rfc4475/">RFC 4475</a>.

Input file is printable ASCII characters only. Output
is a binary file containing non-printable characters,
very long lines, and lines containing very long
strings of repeating characters.
Both input and output files contain multiple SIP
messages, separated by one or more lines beginning
with a semicolon - that is a "CRLF;" character sequence.
Note that no valid SIP message line begins with "CRLF;"
@param vpMemCtx memory component context handle previously returned from vpMemCtor()
@param cpInput pointer to the ASCII text version of the messages
@param vpVecMsgsBinary vector component context handle previously returned from vpVecCtor()
@see vpMemCtor()
@see vpVecCtor()
@return true on success, false otherwise
*/
apg_uint uiTortureTestTranslator(void* vpMemCtx, const char* cpInput, void* vpVecMsgsBinary){
  apg_uint	uiReturn = 0;
  BSTR		sSrc;
  apg_achar*	acpOutput;
  BSTR		sTemp;
  apg_uint	uiTest;
  void*		vpMsgsInCtx = NULL;
  void*		vpMsgsOutCtx = NULL;
  void*		vpTransOneCtx = NULL;
  void*		vpTransTwoCtx = NULL;
  apg_uint	uiBytes;
  apg_uint	uiCheckPoint;

  // validate input
  MASSERT(vpVecMsgsBinary);
  MASSERT(uiVecValidate(vpVecMsgsBinary));
  MASSERT(cpInput);
  MASSERT(cpInput[0] != 0);
  uiTest = uiMemValidate(vpMemCtx);
  MASSERT(uiTest);
  uiCheckPoint = uiMemCheckPoint(vpMemCtx);

  // get the list of messages
  sSrc.uiLength = uiGetFileSize(cpInput);
  MASSERT(sSrc.uiLength);
  sSrc.cpStr = (char*)vpMemAlloc(vpMemCtx, sSrc.uiLength + 10);
  MASSERT(sSrc.cpStr);
  sSrc.uiLength = uiGetFile(cpInput, (void*)sSrc.cpStr);
  MASSERT(sSrc.uiLength);
  sSrc.cpStr[sSrc.uiLength] = 0;

  // get a vector contexts
  vpMsgsInCtx = vpVecCtor(vpMemCtx, sizeof(BSTR), 0);
  MASSERT(vpMsgsInCtx);
  vpMsgsOutCtx = vpVecCtor(vpMemCtx, sizeof(BSTR), 0);
  MASSERT(vpMsgsOutCtx);
  vpTransOneCtx = vpVecCtor(vpMemCtx, sizeof(uchar), 0);
  MASSERT(vpTransOneCtx);
  vpTransTwoCtx = vpVecCtor(vpMemCtx, sizeof(uchar), 0);
  MASSERT(vpTransTwoCtx);

  // translate the long lines
  uiBytes = uiLongLines(vpMemCtx, &sSrc, vpTransOneCtx);
  MASSERT(uiBytes);

  // translate the long repeating strings
  sTemp.cpStr = (char*)vpVecFront(vpTransOneCtx);
  MASSERT(sTemp.cpStr);
  sTemp.uiLength = uiVecSize(vpTransOneCtx);
  uiBytes = uiRepeatingStrings(vpMemCtx, &sTemp, vpTransTwoCtx);
  MASSERT(uiBytes);

  // translate the non-printing characters
  sTemp.cpStr = (char*)vpVecFront(vpTransTwoCtx);
  MASSERT(sTemp.cpStr);
  sTemp.uiLength = uiVecSize(vpTransTwoCtx);
  vVecClear(vpTransOneCtx);
  uiBytes = uiBinaryCharacters(vpMemCtx, &sTemp, vpTransOneCtx);
  MASSERT(uiBytes);

  // convert the output string to alphabet characters (apg_achar)
  sTemp.cpStr = vpVecFront(vpTransOneCtx);
  sTemp.uiLength = uiVecSize(vpTransOneCtx);
  vVecClear(vpVecMsgsBinary);
  acpOutput = (apg_achar*)vpVecPushn(vpVecMsgsBinary, NULL, sTemp.uiLength);
  MASSERT(acpOutput);
  vCharToAChar(acpOutput, sTemp.cpStr, sTemp.uiLength);

  // success
  vMemFreeToCheckPoint(vpMemCtx, uiCheckPoint);
  uiReturn = APG_TRUE;
  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Search for tagged long lines and replace them as directed.
//
// FUNCTION: static apg_uint uiLongLines
//
//      ARG: 1) BSTR* spMsg
//              : binary string defining a SIP message
//
//      ARG: 2) void* vpTransCtx
//              : vector component context for the output file
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiLongLines(void* vpMemCtx, BSTR* spMsg, void* vpTransCtx)
{
  apg_uint uiReturn = APG_FALSE;
  apg_uint uiPrefixLen;
  char* cpPrefixEnd;
  char* cpPhrasePrev;
  char* cpPhraseNext;
  char* cpPhraseEnd;
  char* cpLineBeg;
  char* cpLineEnd;
  void* vpTest;
  char  cSave;
  static char* cpStartTag = "<allOneLine>\n";
  static char* cpEndTag = "</allOneLine>\n";
  apg_uint uiStartTagLen = strlen(cpStartTag);
  apg_uint uiEndTagLen = strlen(cpEndTag);

  // single-point-of-exit loop
  cpPhrasePrev = (char*)spMsg->cpStr;
  cpPrefixEnd = cpPhrasePrev + spMsg->uiLength;
  while(APG_TRUE)
  {
    // find the next long line
    cpPhraseNext = strstr(cpPhrasePrev, cpStartTag);
    if(!cpPhraseNext){break;}
    cpPhraseEnd = strstr(cpPhraseNext, cpEndTag);
    MASSERT(cpPhraseEnd);

    // output the prefix, if any
    uiPrefixLen = (apg_uint)(cpPhraseNext - cpPhrasePrev);
    if(uiPrefixLen)
    {
      vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
      MASSERT(vpTest);
    }

    // remove the extra CRLFs
    cSave = *cpPhraseEnd;
    *cpPhraseEnd = 0;
    cpPhraseNext += uiStartTagLen;
    cpLineBeg = cpPhraseNext;
    while(APG_TRUE)
    {
      cpLineEnd = strstr(cpLineBeg, g_cpLineEnd);
      if(!cpLineEnd){break;}
      uiPrefixLen = (apg_uint)(cpLineEnd - cpLineBeg);
      if(uiPrefixLen)
      {
        vpTest = vpVecPushn(vpTransCtx, (void*)cpLineBeg, uiPrefixLen);
        MASSERT(vpTest);
      }

      cpLineBeg = cpLineEnd + strlen(g_cpLineEnd);
    } // end of single-point-of-exit loop
    *cpPhraseEnd = cSave;

    // output a line end
    vpTest = vpVecPushn(vpTransCtx, (void*)g_cpLineEnd, strlen(g_cpLineEnd));
    MASSERT(vpTest);

    // set up for next phrase
    cpPhrasePrev = cpPhraseEnd + uiEndTagLen;
  } // end of single-point-of-exit loop

  // output the tail
  uiPrefixLen = (apg_uint)(cpPrefixEnd - cpPhrasePrev);
  if(uiPrefixLen)
  {
    vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
    MASSERT(vpTest);
  }

  // success
  uiReturn = APG_TRUE;
  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Search for tagged repeating strings and replace as directed.
//
// FUNCTION: static apg_uint uiRepeatingStrings
//
//      ARG: 1) BSTR* spMsg
//              : binary string defining a SIP message
//
//      ARG: 2) void* vpTransCtx
//              : vector component context for the output file
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiRepeatingStrings(void* vpMemCtx, BSTR* spMsg, void* vpTransCtx)
{
  apg_uint uiReturn = APG_FALSE;
  apg_uint uiPrefixLen;
  char* cpPrefixEnd;
  char* cpPhrasePrev;
  char* cpPhraseNext;
  char* cpPhraseEnd;
  void* vpTest;
  char  cSave;
  apg_uint uiCount;
  apg_uint uiIndex;
  char* cpRepeat;
  static char* cpStartTag = "<repeat count=";
  static char* cpEndTag = "</repeat>";
  apg_uint uiStartTagLen = strlen(cpStartTag);
  apg_uint uiEndTagLen = strlen(cpEndTag);

  // single-point-of-exit loop
  cpPhrasePrev = (char*)spMsg->cpStr;
  cpPrefixEnd = cpPhrasePrev + spMsg->uiLength;
  while(APG_TRUE)
  {
    // find the next long line
    cpPhraseNext = strstr(cpPhrasePrev, cpStartTag);
    if(!cpPhraseNext){break;}
    cpPhraseEnd = strstr(cpPhraseNext, cpEndTag);
    MASSERT(cpPhraseEnd);

    // output the prefix, if any
    uiPrefixLen = (apg_uint)(cpPhraseNext - cpPhrasePrev);
    if(uiPrefixLen)
    {
      vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
      MASSERT(vpTest);
    }

    // find the count
    cpRepeat = strstr(cpPhraseNext, ">");
    MASSERT(cpRepeat);
    cSave = *cpRepeat;
    *cpRepeat = 0;
    uiCount = (apg_uint)atol(cpPhraseNext + uiStartTagLen);
    *cpRepeat = cSave;

    // find the repeat string
    ++cpRepeat;

    // write the repeated string
    cSave = *cpPhraseEnd;
    *cpPhraseEnd = 0;
    uiPrefixLen = (apg_uint)strlen(cpRepeat);
    for(uiIndex = 0; uiIndex < uiCount; ++uiIndex)
    {
      vpTest = vpVecPushn(vpTransCtx, (void*)cpRepeat, uiPrefixLen);
      MASSERT(vpTest);
    }
    *cpPhraseEnd = cSave;

    // set up for next phrase
    cpPhrasePrev = cpPhraseEnd + uiEndTagLen;
  } // end of single-point-of-exit loop

  // output the tail
  uiPrefixLen = (apg_uint)(cpPrefixEnd - cpPhrasePrev);
  if(uiPrefixLen)
  {
    vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
    MASSERT(vpTest);
  }

  // success
  uiReturn = APG_TRUE;
  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Search for tagged binary characters and replace as directed.
//
// FUNCTION: static apg_uint uiBinaryCharacters
//
//      ARG: 1) BSTR* spMsg
//              : binary string defining a SIP message
//
//      ARG: 2) void* vpTransCtx
//              : vector component context for the output file
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiBinaryCharacters(void* vpMemCtx, BSTR* spMsg, void* vpTransCtx)
{
  apg_uint uiReturn = APG_FALSE;
  apg_uint uiPrefixLen;
  char* cpPrefixEnd;
  char* cpPhrasePrev;
  char* cpPhraseNext;
  char* cpPhraseEnd;
  void* vpTest;
  static char* cpStartTag = "<hex>";
  static char* cpEndTag = "</hex>";
  apg_uint uiStartTagLen = strlen(cpStartTag);
  apg_uint uiEndTagLen = strlen(cpEndTag);

  // single-point-of-exit loop
  cpPhrasePrev = (char*)spMsg->cpStr;
  cpPrefixEnd = cpPhrasePrev + spMsg->uiLength;
  while(APG_TRUE)
  {
    // find the next binary phrase
    cpPhraseNext = strstr(cpPhrasePrev, cpStartTag);
    if(!cpPhraseNext){break;}
    cpPhraseEnd = strstr(cpPhraseNext, cpEndTag);
    MASSERT(cpPhraseEnd);

    // output the prefix, if any
    uiPrefixLen = (apg_uint)(cpPhraseNext - cpPhrasePrev);
    if(uiPrefixLen)
    {
      vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
      MASSERT(vpTest);
    }

    // translate all hex characters
    cpPhraseNext += uiStartTagLen;
    while(APG_TRUE)
    {
      uchar ucBinary;
      uchar ucDigit1;
      uchar ucDigit2;

      if(cpPhraseNext == cpPhraseEnd){break;}
      if(*cpPhraseNext == CR || *cpPhraseNext == LF)
      {
        // skip line enders
        ++cpPhraseNext;
        continue;
      }

      // convert digit one
      ucDigit1 = ucaHexToInt[(uchar)*cpPhraseNext];
      MASSERT(ucDigit1 != 255);

      // convert digit two
      ++cpPhraseNext;
      MASSERT(cpPhraseNext < cpPhraseEnd);
      ucDigit2 = ucaHexToInt[(uchar)*cpPhraseNext];
      MASSERT(ucDigit2 != 255);

      // write the binary value
      ucBinary = (ucDigit1 << 4) + ucDigit2;
      vpTest = vpVecPush(vpTransCtx, (void*)&ucBinary);
      MASSERT(vpTest);

      ++cpPhraseNext;
    } // end of single-point-of-exit loop

    // set up for next phrase
    cpPhrasePrev = cpPhraseEnd + uiEndTagLen;
  } // end of single-point-of-exit loop

  // output the tail
  uiPrefixLen = (apg_uint)(cpPrefixEnd - cpPhrasePrev);
  if(uiPrefixLen)
  {
    vpTest = vpVecPushn(vpTransCtx, (void*)cpPhrasePrev, uiPrefixLen);
    MASSERT(vpTest);
  }

  // success
  uiReturn = APG_TRUE;
  return uiReturn;
}
