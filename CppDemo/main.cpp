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
/** \file CppDemo/main.cpp \brief Simple example of setting up a C++ parser.

1. Instantiation of the parser.
2. Initilizing rule and UDT syntax and semantic callback functions.
3. Tracing the parser.
4. Statistics gathering and display.
5. Displaying the parser state.
6. Create, display and translate the AST.

The grammar file for this test has been generated with the parser generator command:
<pre>
apg /in:CppDemo.bnf /C++:CppDemo /dwarnings /dtypes
</pre>
*/
/** The main function. Takes no command line arguments. */
int main(){
	apg_uint uiTrace = APG_TRUE;
	apg_uint uiStats = APG_TRUE;
	apg_uint uiState = APG_TRUE;
	apg_uint uiAstNodesOnly = APG_TRUE;
	apg_uint uiAstCallbacks= APG_TRUE;
	apg_uint uiSuccess;
	const char* cpInput = "Hello World\n";
	apg_uint uiInputLen = strlen(cpInput);
	apg_achar acaInput[uiInputLen + 1];
	vCharToAChar(acaInput, cpInput, uiInputLen);
	CppDemo oCpp(vTerminalAlert);
	APG_CALLBACK saSyntaxRuleCallbacks[oCpp.RULEID_COUNT];
	APG_CALLBACK saSyntaxUdtCallbacks[oCpp.UDTID_COUNT];
	APG_CALLBACK saAstRuleCallbacks[oCpp.RULEID_COUNT];
	APG_CALLBACK saAstUdtCallbacks[oCpp.UDTID_COUNT];
	apg_uint saAstRuleNodes[oCpp.RULEID_COUNT];
	apg_uint saAstUdtNodes[oCpp.UDTID_COUNT];

	printf("CPPDEMO: BEGIN\n");

    printf("CppDemo Grammar Information:\n");
	vDisplayGrammarInfo(NULL, oCpp.m_vpParserInit);
    printf("\n");
    printf("\n");
	oCpp.vDefineSyntaxCallbacks(saSyntaxRuleCallbacks, saSyntaxUdtCallbacks);
	oCpp.uiSyntaxCallbacks(saSyntaxRuleCallbacks, saSyntaxUdtCallbacks);

	if(uiAstNodesOnly){
		oCpp.vDefineAstNodes(saAstRuleNodes, saAstUdtNodes);
		oCpp.vAstInitNodes(saAstRuleNodes, saAstUdtNodes);
	}
	if(uiAstCallbacks){
		vCharToAChar(acaInput, cpInput, uiInputLen);
		oCpp.vDefineAstCallbacks(saAstRuleCallbacks, saAstUdtCallbacks);
		oCpp.vAstInitCallbacks(saAstRuleCallbacks, saAstUdtCallbacks);
	}

	if(uiTrace){
		printf("PARSER: TRACE ENABLED\n");
		oCpp.uiTraceEnable();
//		oCpp.vTraceOp(APG_TRACE_TBS);
//		oCpp.vTraceRule(oCpp.RULEID_CRLF, APG_FALSE);
//		oCpp.vTraceUdt(oCpp.UDTID_U_WORLD, APG_FALSE);
//		oCpp.vTraceRange(3, 4);
	}

	if(uiStats){
		oCpp.uiStatsEnable();
	}

	printf("PARSER: SYNTAX ANALYSIS\n");
	uiSuccess = oCpp.uiSyntaxAnalysis(oCpp.RULEID_HELLOWORLD, acaInput, uiInputLen);
	if(uiSuccess){printf("oCpp.uiSyntaxAnalysis: success\n");}
	else{printf("oCpp.uiSyntaxAnalysis: failed\n");}

	if(uiState){
		printf("\nPARSER: STATE\n");
		FILE* spOut = stdout;
		APG_PARSER_STATE sState;
		oCpp.uiState(&sState);
		vDisplayState(spOut, &sState);
	}

	if(uiStats){
//		printf("\nPARSER: STATISTICS\n");
		FILE* spOut = stdout;
		apg_uint uiTest;
		apg_uint uiBufferSize = 10000;
		char caBuffer[uiBufferSize];
		APG_PARSER_STATS* spStats = (APG_PARSER_STATS*)&caBuffer[0];
		oCpp.uiStatsGet(NULL, &uiTest);
		if(uiTest <= uiBufferSize){
			oCpp.uiStatsGet(spStats, &uiTest);
			fprintf(spOut, "\nPARSER STATISTICS:\n");
			vDisplayOperatorStats(spOut, spStats);
			vDisplayRuleStats(spOut, spStats, "count");
		} else{
			fprintf(spOut, "\nNO PARSER STATISTICS: insufficient buffer size: needed: %u: have: %u\n",
					(apg_uint)uiTest, (apg_uint)uiBufferSize);
		}
	}

	if(uiAstNodesOnly){
		printf("\nAST: NODES - native record format\n");
		void* vpParserCtx = oCpp.vpGetParserCtx();
		vDisplayAstRecords(NULL, vpParserCtx);
		printf("\nAST: NODES - XML format\n");
		apg_uint uiTest = uiAstToXml(NULL, vpParserCtx);
		CPPASSERT(uiTest, "uiAstToXml() failed");
	}
	if(uiAstCallbacks){
		printf("\nAST: TRANSLATION\n");
		oCpp.uiAstTranslate(NULL, NULL);
	}

    printf("\nCPPDEMO: simple demo: end\n");
	printf("\nCPPDEMO: END\n");
	return EXIT_SUCCESS;
}
