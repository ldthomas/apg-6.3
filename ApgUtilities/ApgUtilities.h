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

#ifndef _ApgUtilities_h_16_6_2006_16_21_
#define _ApgUtilities_h_16_6_2006_16_21_
/** \file ApgUtilities.h \brief Declarations of all APG utility functions.

APG utilites are in three main categories. There are a few file helpers
for commonly used file functions, a "timer component" used in the timing studies in the examples
and display utilities for displaying the parsing results.

*/
#include "Apg.h"
#include "Private.h"
#include "Grammar.h"
#include <stdio.h>
#include <time.h>

// Begin C-language linkage specification
#if defined(__cplusplus)
extern "C"
{
#endif

// used exclusively to maintain conformance in printf %lu integer formats
/** printf_uint is used uniformly in all printf() statemenst to convert integer data
to unsigned ints. This way the \%lu format can be used regardless of the
current size of apg_uint.
*/
typedef unsigned long int printf_uint;

//////////////////////////////////////////////////////////////////////////
// FILE HELPERS
//////////////////////////////////////////////////////////////////////////
apg_uint uiGetFileSize(const char* cpFileName);
apg_uint uiGetFile(const char* cpFileName, void* vpBuffer);
apg_uint uiWriteFile(const char* cpFileName, void* vpData, apg_uint uiDataLen);
//apg_uint uiRenameFile(const char* cpFileName);
/** \cond NOSHOW */
void     vJavaScriptApgBytes(FILE* in, FILE* out);
/** \endcond */

//////////////////////////////////////////////////////////////////////////
// ALERTS
//////////////////////////////////////////////////////////////////////////
// alert handler that prints the alert state and terminates
void vTerminalAlert(unsigned int uiLine, const char* cpFile);
void vTerminalAlertMsg(unsigned int uiLine, const char* cpFile, const char* cpMsg);

//////////////////////////////////////////////////////////////////////////
// TIMER
//////////////////////////////////////////////////////////////////////////
/** \cond NODISPLAY */
#define APG_TIMER_SEC 1.0
#define APG_TIMER_MILLISEC 1000.0
#define APG_TIMER_MICROSEC 1000000.0
/** \endcond */
void* vpTimerCtor(void* vpMemCtx);
void vTimerDtor(void* vpCtx);
apg_uint uiTimerStart(void* vpCtx);
apg_uint uiTimerStop(void* vpCtx);

// uiConversion = desired units / second
// or desired unit = seconds * uiConversion
double dTimerStartTime(void* vpCtx, double dConversion);
double dTimerStopTime(void* vpCtx, double dConversion);
double dTimerDuration(void* vpCtx, double dConversion);
apg_uint uiTimerRates(void* vpCtx, double* dpRates, apg_uint uiLen, double dConversion);

//////////////////////////////////////////////////////////////////////////
// STATS
//////////////////////////////////////////////////////////////////////////
void vDisplayMemStats(void* vpCtx);
void vDisplayOperatorStats(FILE* spOut, APG_PARSER_STATS* spStats);
void vDisplayRuleStats(FILE* spOut, APG_PARSER_STATS* spStats, const char* cpType);

//////////////////////////////////////////////////////////////////////////
// STATES & STATS
//////////////////////////////////////////////////////////////////////////
void vDisplayParserState(FILE* spOut, void* vpParserCtx);
void vDisplayState(FILE* spOut, APG_PARSER_STATE* spState);
apg_uint uiAstToXml(FILE* spOut, void* vpParserCtx);

//////////////////////////////////////////////////////////////////////////
// MISC
//////////////////////////////////////////////////////////////////////////
void vDisplayOpcodes(void* vpCtx);
void vDisplayAstRecords(FILE* spOut, void* vpParserCtx);
void vDisplayRules(void* vpParserCtx);
void vDisplayUdts(void* vpParserCtx);
const char* cpState2String(apg_uint uiState);
const char* cpBoolean2String(apg_uint uiBool);


// print file with one-based line numbers
void vDisplayAscii(FILE* spOut, const char* cpSrc, apg_uint uiSrcLen);
// prints the list of error locations in the error queue
void vLicenseNotice(FILE* spFile);
// print type sizes
void vDisplayTypeSizes(FILE* spOut);
void vDisplayGrammarInfo(FILE* spOut, void* vpHdr);

// NOTE: can't access APG_PARSER_CTX from here, but don't lose this code
//       it may come in handy another day
// prints a human-readable list of the parser's opcodes
//void vPrintOpcodes(APG_PARSER_CTX* spCtx);
// prints a human-readable display of the rule list
//void vPrintRuleList(APG_PARSER_CTX* spCtx);
// prints an ASCII string as string of 2-digit hexidecimal
//void vHexString(char* cpBuffer, apg_uint uiBufLen, char* cpString, apg_uint uiLen);

// End C-language linkage specification
#if defined(__cplusplus)
}
#endif

#endif // _ApgUtilities_h_16_6_2006_16_21_
