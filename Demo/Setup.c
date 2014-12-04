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
#include "SetupGrammar.h"
/** \file Demo/Setup.c \brief Demonstrates the basics of setting up and running a parser.*/

// NOTE: error handling is done with the statement:
//       if(error){vTerminalAlert(__LINE__, __FILE__);}
//       prints line and file where error was detected and exits
/** Demonstrates the fundamentals of building a Parser. The test output is written to Setup.output.

- construction of the parser
- handling the input string
- examination of the parser state
- collecting and viewing parsing statistics
- setup and display of the AST
*/
void vDemoSetup(){
	apg_uint uiBufferSize = 1028;
	char caInputString[uiBufferSize];
	apg_achar acaParserString[uiBufferSize];
	apg_uint uiStrLen;
	apg_uint uiTest;
	apg_uint i = 0;
	APG_PARSER_STATE sState;
	apg_uint uiStatsBufferSize = 10000;
	char caStatsBuffer[uiStatsBufferSize];
	APG_PARSER_STATS* spStats = (APG_PARSER_STATS*)&caStatsBuffer[0];
	apg_uint uiaRuleNodes[RULE_COUNT_SETUPGRAMMAR];
	void* vpParser = NULL;
	char* cpInFile = "Setup.input";
	char* cpOutFile = "Setup.output";
	FILE* spOut = NULL;

	// redirects output
	printf("%s - output redirect file for Demonstration Setup\n", cpOutFile);
	spOut = fopen(cpOutFile, "w");
	if(!spOut){vTerminalAlert(__LINE__, __FILE__);}

	fprintf(spOut, "*** LICENSE NOTICE ***\n");
	vLicenseNotice(spOut);
	fprintf(spOut, "\n*** DEMO SETUP ***\n");
	fprintf(spOut, "    Demonstrates the fundamentals of building a parser.\n");
	fprintf(spOut, "      - contruction of the parser\n");
	fprintf(spOut, "      - handling the input string\n");
	fprintf(spOut, "      - examination of the parser state\n");
	fprintf(spOut, "      - collecting and viewing parsing statistics\n");
	fprintf(spOut, "      - setup and display of the AST\n");

	// display the integer sizes
	fprintf(spOut, "\n*** TYPE SIZES ***\n");
	vDisplayTypeSizes(spOut);

	// display the grammar information
	fprintf(spOut, "\n*** GRAMMAR INFORMATION ***\n");
	vDisplayGrammarInfo(spOut, vpParserInit_SetupGrammar);

	// get the input string
	memset((void*)&caInputString[0], 0, uiBufferSize);
	uiStrLen = uiGetFileSize(cpInFile);
	if(!uiStrLen){vTerminalAlert(__LINE__, __FILE__);}
	if(uiStrLen > uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	uiTest = uiGetFile(cpInFile, (void*)&caInputString[0]);
	if(uiTest != uiStrLen){vTerminalAlert(__LINE__, __FILE__);}

	// display the input string
	fprintf(spOut, "\n*** INPUT STRING WITH LINE NUMBERS AND CHARACTER OFFSETS ***\n");
	vDisplayAscii(spOut, &caInputString[0], uiStrLen);

	// convert the input string to alphabet characters
	vCharToAChar(&acaParserString[0], &caInputString[0], uiStrLen);

	// construct the parser
	vpParser = vpParserCtor(vpParserInit_SetupGrammar, vTerminalAlert);
	if(!vpParser){vTerminalAlert(__LINE__, __FILE__);}

	// parse the string
	uiTest = uiParserSyntaxAnalysis(vpParser, RULE_SETUPGRAMMAR_FILE, &acaParserString[0], uiStrLen, NULL);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}
	uiParserState(vpParser, &sState);

	// examine the parser state
	fprintf(spOut, "\n*** PARSER STATE ***\n");
	vDisplayParserState(spOut, vpParser);

	// set up for parsing statistics
	uiParserStatsEnable(vpParser, APG_TRUE);

	// parse again
	uiTest = uiParserSyntaxAnalysis(vpParser, RULE_SETUPGRAMMAR_FILE, &acaParserString[0], uiStrLen, NULL);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}

	// look at the parsing statistics
	uiParserStatsGet(vpParser, NULL, &uiTest);
	if(uiTest <= uiStatsBufferSize){
		uiParserStatsGet(vpParser, spStats, &uiTest);
		fprintf(spOut, "\n*** PARSER STATISTICS ***\n");
		vDisplayOperatorStats(spOut, spStats);
		vDisplayRuleStats(spOut, spStats, NULL);
		vDisplayRuleStats(spOut, spStats, "alpha");
		vDisplayRuleStats(spOut, spStats, "count");
	} else{
		fprintf(spOut, "\n*** NO PARSER STATISTICS: insufficient buffer size: needed: %lu: have: %lu\n",
				(printf_uint)uiTest, (printf_uint)uiStatsBufferSize);
	}

	// set up for AST generation
	for(; i < RULE_COUNT_SETUPGRAMMAR; i++){
		uiaRuleNodes[i] = APG_FALSE; // defaults to no AST nodes
	}
	// define AST nodes without defining syntax callback functions
	uiaRuleNodes[RULE_SETUPGRAMMAR_FILE] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_BLANKLINE] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_LINE] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_LINENAME] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_LINEERROR] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_ELEMENT] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_ALTERNATION] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_CONCATENATION] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_HEXNUM] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_DECNUM] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_CCOMMENT] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_CPPCOMMENT] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_SEMICOMMENT] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_SINGLEQUOTEDSTRING] = APG_TRUE;
	uiaRuleNodes[RULE_SETUPGRAMMAR_DOUBLEQUOTEDSTRING] = APG_TRUE;
	vParserAstInitNodes(vpParser, &uiaRuleNodes[0], NULL);

	// parse again
	uiTest = uiParserSyntaxAnalysis(vpParser, RULE_SETUPGRAMMAR_FILE, &acaParserString[0], uiStrLen, NULL);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}

	// look at the parsed phrases (AST nodes)
	fprintf(spOut, "\n*** AST NODES AND PHRASES ***\n");
	vDisplayAstRecords(spOut, vpParser);
	fprintf(spOut, "\n*** AST TO XML ***\n");
	uiTest = uiAstToXml(spOut, vpParser);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}

	// reset the standard output
	fprintf(spOut, "\n*** DEMO SETUP - test ended successfully ***\n");
	fclose(spOut);
}
