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
#include "ApgUtilities.h"
#include "MEGACO.h"
#include <iostream>

/** An assertion macro which calls the vTerminalAlertMsg() alert handler on errors.
@see vTerminalAlertMsg()
*/
#define MASSERT(cond, msg) if(!(cond)){vTerminalAlertMsg(__LINE__, __FILE__, (msg));}

using namespace std;

/** \file MEGACO/main.cpp \brief Sets up and runs a parser for the MEGACO grammar.

The grammar file for this test has been generated with the parser generator command:
<pre>
apg /in:MEGACO.bnf /C++:MEGACO /dwarnings /dtypes
</pre>
*/
/** The main function. Takes no command line arguments. */
int main()
{
    apg_uint uiTrace = APG_FALSE;
	apg_uint uiStats = APG_TRUE;
	apg_uint uiState = APG_TRUE;
	apg_uint uiSuccess;
	const char* cpFileName = "MEGACO.input";
	char* cpInput = NULL;
	apg_achar* acpInput = NULL;
	apg_uint uiInputLen = 0;

	printf("\nMEGACO: BEGIN\n");
	void* vpMemCtx = vpMemCtor();
    MASSERT(vpMemCtx, "unable to get memory component");

	MEGACO oMegaco(vTerminalAlert);
	APG_CALLBACK saSyntaxRuleCallbacks[oMegaco.RULEID_COUNT];
	APG_CALLBACK saAstRuleCallbacks[oMegaco.RULEID_COUNT];

	oMegaco.vDefineSyntaxCallbacks(saSyntaxRuleCallbacks, NULL);
	oMegaco.uiSyntaxCallbacks(saSyntaxRuleCallbacks, NULL);

    oMegaco.vDefineAstCallbacks(saAstRuleCallbacks, NULL);
    oMegaco.vAstInitCallbacks(saAstRuleCallbacks, NULL);

    uiInputLen = uiGetFileSize(cpFileName);
    MASSERT(uiInputLen, "unable to open input string file");
    cpInput = (char*)vpMemAlloc(vpMemCtx, uiInputLen + 10);
    MASSERT(cpInput, "unable to allocate memory for string file");
    acpInput = (apg_achar*)vpMemAlloc(vpMemCtx, (uiInputLen + 10) * sizeof(apg_achar));
    MASSERT(acpInput, "unable to allocate memory for apg_achar input string");
    uiInputLen = uiGetFile(cpFileName, (void*)cpInput);
    MASSERT(uiInputLen, "unable to open input string file");
    cpInput[uiInputLen] = 0;
	vCharToAChar(acpInput, cpInput, uiInputLen);

	if(uiTrace){
		printf("MEGACO: TRACE ENABLED\n");
		oMegaco.uiTraceEnable();
	}

	if(uiStats){
		oMegaco.uiStatsEnable();
	}

	printf("MEGACO: SYNTAX ANALYSIS\n");
	uiSuccess = oMegaco.uiSyntaxAnalysis(oMegaco.RULEID_MEGACOMESSAGE, acpInput, uiInputLen);
	if(uiState){
		printf("\nMEGACO: STATE\n");
		FILE* spOut = stdout;
		APG_PARSER_STATE sState;
		oMegaco.uiState(&sState);
		vDisplayState(spOut, &sState);
	}
    MASSERT(uiSuccess, "oMegaco.uiSyntaxAnalysis: failed\n");
	printf("oMegaco.uiSyntaxAnalysis: success\n");

	if(uiStats){
//		printf("\nPARSER: STATISTICS\n");
		FILE* spOut = stdout;
		apg_uint uiTest;
		apg_uint uiBufferSize = 50000;
		char caBuffer[uiBufferSize];
		APG_PARSER_STATS* spStats = (APG_PARSER_STATS*)&caBuffer[0];
		oMegaco.uiStatsGet(NULL, &uiTest);
		if(uiTest <= uiBufferSize){
			oMegaco.uiStatsGet(spStats, &uiTest);
			fprintf(spOut, "\nMEGACO STATISTICS:\n");
			vDisplayOperatorStats(spOut, spStats);
			vDisplayRuleStats(spOut, spStats, "count");
		} else{
			fprintf(spOut, "\nNO nMEGACO STATISTICS: insufficient buffer size: needed: %u: have: %u\n",
					(apg_uint)uiTest, (apg_uint)uiBufferSize);
		}
	}

	printf("MEGACO: TRANSLATE AST\n");
    oMegaco.uiAstTranslate(NULL, NULL);
    printf("\nMEGACO: AST TRANSLATION: native APG format\n");
    vDisplayAstRecords(NULL, oMegaco.vpGetParserCtx());
    printf("\nMEGACO: AST TRANSLATION: XML format\n");
    uiAstToXml(NULL, oMegaco.vpGetParserCtx());

	printf("\nMEGACO: END SUCCESS\n");
	return EXIT_SUCCESS;
}
