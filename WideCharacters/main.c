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

static apg_uint uiCherokeeGen(apg_achar* acpPutItHere);
static apg_uint uiGreekGen(apg_achar* acpPutItHere);
static apg_uint uiCyrillicGen(apg_achar* acpPutItHere);

/** \file WideCharacters/main.c \brief Demonstrates parsing with an alphabet character code width of 32-bits.

The grammar for this parser includes alphabet character codes from the Greek, Cyrillic and Cherokee UNICODE code charts.
See:
- <a href="http://unicode.org/versions/latest/">UNICODE</a>
- <a href="http://unicode.org/charts/">UNICODE code charts</a>.

The input string is in UTF-32, 32-bit character codes. The input is translated to an HTML page of characters.
To view the translation a web browser which supports the Greek, Cyrillic and Cherokee code charts is required.

The grammar files for these tests have been generated with the parser generator commands:
<pre>
apg /in:WideCharacters.bnf /C:WideGrammar /dwarnings /dtypes
</pre>
*/
int main() {
	char* cpOutput = "WideCharacters.html";
	apg_uint uiTrace = APG_FALSE;
	apg_uint uiStats = APG_FALSE;
	void* vpMemCtx;
	apg_uint uiTest;
	apg_uint uiInputLen;
	apg_uint uiInputSize = 4096;
	apg_achar acaInput[uiInputSize];
	APG_CALLBACK saSemantic[RULE_COUNT_WIDEGRAMMAR];
	CALLBACK_CTX sCallbackCtx;
	void* vpParserCtx;

	printf("TYPE SIZES\n");
	vDisplayTypeSizes(NULL);
	printf("\n");
	vpMemCtx = vpMemCtor();
	MASSERT(vpMemCtx, "memory constructor failed");

	// get input
	uiInputLen = 0;
	uiInputLen += uiCherokeeGen(&acaInput[uiInputLen]);
	MASSERT((uiInputLen <= uiInputSize), "buffer overrun: input size larger than allocated buffer");
	uiInputLen += uiGreekGen(&acaInput[uiInputLen]);
	MASSERT((uiInputLen <= uiInputSize), "buffer overrun: input size larger than allocated buffer");
	uiInputLen += uiCyrillicGen(&acaInput[uiInputLen]);
	MASSERT((uiInputLen <= uiInputSize), "buffer overrun: input size larger than allocated buffer");

	// set up parser
	vpParserCtx = vpParserCtor(vpParserInit_WideGrammar, vTerminalAlert);
	MASSERT(vpParserCtx, "parser construction failed");
	vSemanticInit(saSemantic);
	vParserAstInitCallbacks(vpParserCtx, saSemantic, NULL);		// define the AST for translation
	if(uiStats){uiParserStatsEnable(vpParserCtx, APG_TRUE);}	// enable statistics gathering
	if(uiTrace){uiParserTraceEnable(vpParserCtx, APG_TRUE);} // enable tracing

	// parse the examples
	uiTest = uiParserSyntaxAnalysis(vpParserCtx, 0, acaInput, uiInputLen, NULL);
	if(uiTest){
		printf("WideCharacters example completed successfully.\n");
		printf("To see the results, view the file \"./%s\" in your favorite Web Browser.\n", cpOutput);
		printf("\n");
	}
	vDisplayParserState(NULL, vpParserCtx);
	MASSERT(uiTest, "parser failed");

	// translate into HTML file
	sCallbackCtx.cpFileName = cpOutput;
	sCallbackCtx.spFile = NULL;
	uiParserAstTranslate(vpParserCtx, NULL, NULL, (void*)&sCallbackCtx);

	printf("main: normal exit: EXIT_SUCCESS\n");
	return EXIT_SUCCESS;
}

static apg_uint uiPrefix(char* cpPrefix, apg_achar* acpPutItHere){
	apg_uint uiLen = strlen(cpPrefix);
	apg_uint i;
	for(i = 0; i < uiLen; i++){acpPutItHere[i] = (apg_achar)cpPrefix[i];}
	return uiLen;
}
static apg_uint uiCherokeeGen(apg_achar* acpPutItHere){
	apg_uint uiRet = 0;
	apg_uint i;
	apg_uint uiBeg, uiEnd;
	char* cpName = "Cherokee";

	// example 1
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13a0;
	uiEnd = 0x13af;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 2
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13b0;
	uiEnd = 0x13bf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 3
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13c0;
	uiEnd = 0x13cf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 4
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13d0;
	uiEnd = 0x13df;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 5
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13e0;
	uiEnd = 0x13ef;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 6
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x13f0;
	uiEnd = 0x13f4;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	return uiRet;
}
static apg_uint uiGreekGen(apg_achar* acpPutItHere){
	apg_uint uiRet = 0;
	apg_uint i;
	apg_uint uiBeg, uiEnd;
	char* cpName = "Greek";

	// example 1
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x390;
	uiEnd = 0x39f;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 2
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x3a0;
	uiEnd = 0x3af;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 3
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x3b0;
	uiEnd = 0x3bf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 4
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x3c0;
	uiEnd = 0x3cf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 5
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x3d0;
	uiEnd = 0x3df;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 6
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x3e0;
	uiEnd = 0x3ef;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	return uiRet;
}
static apg_uint uiCyrillicGen(apg_achar* acpPutItHere){
	apg_uint uiRet = 0;
	apg_uint i;
	apg_uint uiBeg, uiEnd;
	char* cpName = "Cyrillic";

	// example 1
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x400;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 2
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x410;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 3
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x420;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 4
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x430;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 5
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x440;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	// example 6
	uiRet += uiPrefix(cpName, &acpPutItHere[uiRet]);
	uiBeg = 0x450;
	uiEnd = uiBeg + 0xf;
	for(i = uiBeg; i <= uiEnd; i++){acpPutItHere[uiRet++] = i;}
	acpPutItHere[uiRet++] = (apg_achar)10;

	return uiRet;
}
