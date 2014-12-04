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

static apg_achar* cpLookForStart(apg_achar* cpBeg, apg_achar* cpEnd);
static apg_achar* cpLookForEnd(apg_achar* cpBeg, apg_achar* cpEnd);

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Separate a file of semicolon-separated SIP messages
//              into a vector of BStrings.
//
// FUNCTION: apg_uint uiMessages
//
//      ARG: 1) char* cpFile
//              : pointer to the list of SIP messages
//
//      ARG: 2) apg_uint uiLen
//              : number of characters in the list of messages
//
//      ARG: 3) void* vpVecMsg
//              : pointer to a valid vector of binary strings context
//
//   RETURN: number of messages in the list.
//
//////////////////////////////////////////////////////////////////////////
apg_uint uiMessages(apg_achar* acpSrc, apg_uint uiLen, void* vpVecMsg)
{
  apg_uint uiReturn = 0;
  MSG* spMsg;
  apg_achar* cpStart;
  apg_achar* cpEnd;
  apg_achar* cpNext;
  apg_achar* cpEndFile;
  MASSERT(acpSrc);
  MASSERT(uiLen);
  MASSERT(vpVecMsg);

  vVecClear(vpVecMsg);
  cpNext = acpSrc;
  cpEndFile = cpNext + uiLen;

  // single-point-of-exit loop
  while(APG_TRUE)
  {
    cpStart = cpLookForStart(cpNext, cpEndFile);
    if(!cpStart){uiReturn = uiVecSize(vpVecMsg);break;}	// normal end of loop

    cpEnd = cpLookForEnd(cpStart, cpEndFile);
    if(!cpEnd){uiReturn = uiVecSize(vpVecMsg);break;}	// normal end of loop

    // push a message on the vector
    spMsg = (MSG*)vpVecPush(vpVecMsg, NULL);
    if(!spMsg){uiReturn = 0;break;}						// error, abnormal end of loop
    spMsg->acpMsg = cpStart;
    spMsg->uiLength = (apg_uint)(cpEnd - cpStart);
    cpNext = cpEnd;
  } // end of single-point-of-exit loop

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Search for the beginning of a message
//
// FUNCTION: static char* cpLookForStart
//
//      ARG: 1) char* cpBeg
//              : pointer to the text to begin searching
//
//      ARG: 2) char* cpEnd
//              : pointer to the end of the text to search
//
//   RETURN: on success, pointer to the beginning of the message
//           on failure, NULL
//
//////////////////////////////////////////////////////////////////////////
static apg_achar* cpLookForStart(apg_achar* cpBeg, apg_achar* cpEnd)
{
  apg_achar* cpReturn = NULL;
  apg_achar cPrev = LF;
  apg_achar* cpNext = cpBeg;

  for(; cpNext < cpEnd; ++cpNext)
  {
    if(cPrev == LF && *cpNext != SEMI)
    {
      // found begin of msg
      break;
    }

    cPrev = *cpNext;
  }

  if(cpNext < cpEnd)
  {
    // found a msg
    cpReturn = cpNext;
  }
  // else found end of text

  return cpReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Look for the end of a message.
//
// FUNCTION: static char* cpLookForEnd
//
//      ARG: 1) char* cpBeg
//              : pointer to a message
//
//      ARG: 2) char* cpEnd
//              : output, pointer to the end of the list of message
//
//   RETURN: on success, pointer to the end of the message
//           on failure, NULL
//
//////////////////////////////////////////////////////////////////////////
static apg_achar* cpLookForEnd(apg_achar* cpBeg, apg_achar* cpEnd)
{
  apg_achar* cpReturn = NULL;
  apg_achar cPrev = LF;
  apg_achar* cpNext = cpBeg;

  for(; cpNext < cpEnd; ++cpNext)
  {
    if(cPrev == LF && *cpNext == SEMI)
    {
      // found end of msg
      break;
    }

    cPrev = *cpNext;
  }

  if(cpBeg < cpNext)
  {
    // found a msg
    cpReturn = cpNext;
  }
  // else found end of text

  return cpReturn;
}
