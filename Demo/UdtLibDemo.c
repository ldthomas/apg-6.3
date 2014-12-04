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
#include "UdtLibGrammar.h"
/** \file Demo/UdtLibDemo.c \brief Demonstrates how to use the UDT library that comes with APG.*/

// NOTE: error handling is done with the statement:
//       if(error){vTerminalAlert(__LINE__, __FILE__);}
//       prints line and file where error was detected and exits

/** Demonstrates the use of the Parser's UDT library. The test output is written to UdtLib.output.

- tests all functions in the UDT library
- demonstrates how they are implemented in an application
*/
void vDemoUdts(){
	apg_uint uiTrace = APG_FALSE;
	apg_uint uiStats = APG_FALSE;
	apg_uint uiBufferSize = 1024;
	char caInputString[uiBufferSize];
	apg_achar acaParserString[uiBufferSize];
	apg_uint uiStrLen;
	apg_uint uiTest;
	apg_uint i = 0;
	APG_PARSER_STATE sState;
	apg_uint uiaRuleAstNodes[RULE_COUNT_UDTLIBGRAMMAR];
	apg_uint uiaUdtAstNodes[UDT_COUNT_UDTLIBGRAMMAR];
	APG_CALLBACK saUdtSyntaxCallbacks[UDT_COUNT_UDTLIBGRAMMAR];
	void* vpParser = NULL;
	char* cpOutFile = "UdtLib.output";
	FILE* spOut = NULL;
	apg_uint uiStatsBufferSize = 10000;
	char caStatsBuffer[uiStatsBufferSize];
	APG_PARSER_STATS* spStats = (APG_PARSER_STATS*)&caStatsBuffer[0];

	// redirects output
	printf("%s - output redirect file for Demonstration UdtLib\n", cpOutFile);
	spOut = fopen(cpOutFile, "w");
	if(!spOut){vTerminalAlert(__LINE__, __FILE__);}

	fprintf(spOut, "*** LICENSE NOTICE ***\n");
	vLicenseNotice(spOut);

	fprintf(spOut, "\n*** DEMO UDTLIB ***\n");
	fprintf(spOut, "    Tests all functions in the UDT library &\n");
	fprintf(spOut, "    demonstrates how they are implemented in an application.\n");

	// display the integer sizes
	fprintf(spOut, "\n*** TYPE SIZES ***\n");
	vDisplayTypeSizes(spOut);

	// display the grammar information
	fprintf(spOut, "\n*** GRAMMAR INFORMATION ***\n");
	vDisplayGrammarInfo(spOut, vpParserInit_UdtLibGrammar);

	// construct the parser
	vpParser = vpParserCtor(vpParserInit_UdtLibGrammar, vTerminalAlert);
	if(!vpParser){vTerminalAlert(__LINE__, __FILE__);}

	// set up for parsing statistics
	uiStats = uiParserStatsEnable(vpParser, APG_TRUE);

	// set up for UDT syntax callbacks
	// NOTE: tests all UdtLib functions
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_E_OWSP] = (APG_CALLBACK)uiUdtLib_e_owsp;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_WSP] = (APG_CALLBACK)uiUdtLib_u_wsp;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_LINEEND] = (APG_CALLBACK)uiUdtLib_u_lineend;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_E_ANY] = (APG_CALLBACK)uiUdtLib_e_any;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_ALPHANUM] = (APG_CALLBACK)uiUdtLib_u_alphanum;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_ALPHANUM_HYPHEN] = (APG_CALLBACK)uiUdtLib_u_alphanum_hyphen;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_ALPHANUM_UNDER] = (APG_CALLBACK)uiUdtLib_u_alphanum_under;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_DECIMAL] = (APG_CALLBACK)uiUdtLib_u_decnum;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_HEXIDECIMAL] = (APG_CALLBACK)uiUdtLib_u_hexnum;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_QUOTEDSTRING] = (APG_CALLBACK)uiUdtLib_u_quotedstring;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_SINGLEQUOTEDSTRING] = (APG_CALLBACK)uiUdtLib_u_singlequotedstring;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_DOUBLEQUOTEDSTRING] = (APG_CALLBACK)uiUdtLib_u_doublequotedstring;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_CCOMMENT] = (APG_CALLBACK)uiUdtLib_u_c_comment;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_CPPCOMMENT] = (APG_CALLBACK)uiUdtLib_u_cpp_comment;
	saUdtSyntaxCallbacks[UDT_UDTLIBGRAMMAR_U_SEMICOMMENT] = (APG_CALLBACK)uiUdtLib_u_semi_comment;
	uiParserSyntaxInitCallbacks(vpParser, NULL, &saUdtSyntaxCallbacks[0]);


	// set up for AST generation & rule & UDT semantic callbacks
	for(; i < RULE_COUNT_UDTLIBGRAMMAR; i++){
		uiaRuleAstNodes[i] = APG_FALSE;
	}
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_FILE] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_BLANKLINE] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_LINE] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_LINEALPHA] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_LINEHYPHEN] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_LINEUNDER] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_LINEERROR] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_NUMBER] = APG_TRUE;
	uiaRuleAstNodes[RULE_UDTLIBGRAMMAR_COMMENT] = APG_TRUE;
	for(; i < UDT_COUNT_UDTLIBGRAMMAR; i++){
		uiaUdtAstNodes[i] = (saUdtSyntaxCallbacks[i]) ? APG_TRUE: APG_FALSE;
	}
	vParserAstInitNodes(vpParser, &uiaRuleAstNodes[0], &uiaUdtAstNodes[0]);


	// get the input string
	memset((void*)&caInputString[0], 0, uiBufferSize);

	// LF line ending
	strcat(caInputString, "\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// CRLF line ending
	strcat(caInputString, "  \r\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// CR line ending
	strcat(caInputString, "    \r");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// semicolon style comment
	strcat(caInputString, "; semi comment using CR line end\r");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// C++ style comment
	strcat(caInputString, "// C++ comment using CRLF line end\r\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// C style comment
	strcat(caInputString, "/* C comment using LF line end */\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// C style comment spanning multiple lines
	strcat(caInputString, "/* multi-line C comment \n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "continuing multi-line C comment \n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "  end of multi-line C comment */\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// named line
	strcat(caInputString, "\n// alphanum named line\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "john = \'John Doe\'\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "mary-jane = \"Mary Jane\"\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "jimmy_bob = \"Jimmy Bob\"\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	// numbered line
	strcat(caInputString, "\n// test decimal numbers\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "number = 123456789\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "hexi-decimal = 0x1234ABCD\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	strcat(caInputString, "multiple_numbers = 123 0xabCD 567 0x1a2A3b4cdEF \n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	strcat(caInputString, "\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}

	strcat(caInputString, "; end of test\n");
	if(strlen(caInputString) >= uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	uiStrLen = strlen(caInputString);

	// display the input string
	vDisplayAscii(spOut, caInputString, uiStrLen);

	// convert the input string to alphabet characters
	vCharToAChar(&acaParserString[0], &caInputString[0], uiStrLen);

	if(uiTrace){
		// set up for tracing the parse tree
		uiParserTraceEnable(vpParser, APG_TRUE);
	}

	// set up for parsing statistics
	uiStats = uiParserStatsEnable(vpParser, APG_TRUE);

	// parse the string
	uiTest = uiParserSyntaxAnalysis(vpParser, RULE_UDTLIBGRAMMAR_FILE, &acaParserString[0], uiStrLen, NULL);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}
	uiParserState(vpParser, &sState);

	// examine the parser state
	fprintf(spOut, "\n*** PARSER STATE ***\n");
	vDisplayParserState(spOut, vpParser);

	// look at the parsing statistics
	if(uiStats){
	uiParserStatsGet(vpParser, NULL, &uiTest);
        if(uiTest <= uiStatsBufferSize){
            uiParserStatsGet(vpParser, spStats, &uiTest);
            fprintf(spOut, "\n*** PARSER STATISTICS ***\n");
            vDisplayOperatorStats(spOut, spStats);
            vDisplayRuleStats(spOut, spStats, "count");
        } else{
            fprintf(spOut, "\n*** NO PARSER STATISTICS: insufficient buffer size: needed: %lu: have: %lu\n",
                    (printf_uint)uiTest, (printf_uint)uiStatsBufferSize);
        }
	}

	// look at the parsed phrases (AST nodes)
	fprintf(spOut, "\n*** AST NODES AND PHRASES ***\n");
	vDisplayAstRecords(spOut, vpParser);

	fprintf(spOut, "\n*** DEMO UDTLIB - test ended successfully ***\n");
	fclose(spOut);
}
