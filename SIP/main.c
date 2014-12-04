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
/** \file SIP/main.c \brief The driver for the SIP tests.

This is an in-depth study of using UDTs to significantly speed up the parsing process
without altering the language of interest.


- Why SIP? The SIP (<a href="http://www.ietf.org/rfc/rfc3261.txt?number=3261">RFC 3261</a>) grammar has been selected for this study because it is a
substantial (300+ rule names) and <a href="http://en.wikipedia.org/wiki/List_of_SIP_software">commercially significant</a> grammar.

- What messages have been used for the study? Conveniently, there exists a published set of SIP messages especially designed to stretch the parser.
These have been published as <a href="http://datatracker.ietf.org/doc/rfc4475/">RFC 4475</a>.
The published messages have a mark-up method of indicating such things as
long lines,
long, repeating strings and
non-printing characters.
The marked up text for the 13 published valid SIP messages are in the file TortureTests.txt.
The function uiTortureTestTranslator() reads this file and translates all of the mark up into binary, 8-bit character codes ready for parsing.

- How was the study done? The improvements were done in stages.
At each stage the rule name statistics were used to see which rules were getting parsed most often.
Those rules were then converted to UDTs and optimized by handwriting the parsing of those particular phrases.
The optimizations were done in six stages, including the baseline stage with no UDTs.

- What to look for in the results?
The test runs each of the six stage parsers for statistics and prints the statistics for each stage
along with a comparision of statistics of each stage with the baseline.
It then runs timing tests for each of the six stage parsers. Again, the timing results of each test
along with comparisons of each stage with the baseline are given.

The timing results will vary, of course, between computers and even between different runs on the same computer.
But in my tests, I was able to see a 10-fold increase in parsing speed in the debug version of the code.
In the optimized, release version this was somewhat less.

Be patient. The timing tests can take up to several minutes to complete.

To regenerate the grammars for the six stages:
<pre>
apg /in:Grammar1.bnf /C:Grammar1 /dwarnings /dtypes
apg /in:Grammar2.bnf /C:Grammar2 /dwarnings /dtypes
apg /in:Grammar3.bnf /C:Grammar3 /dwarnings /dtypes
apg /in:Grammar4.bnf /C:Grammar4 /dwarnings /dtypes
apg /in:Grammar5.bnf /C:Grammar5 /dwarnings /dtypes
apg /in:SIP.bnf /C:SIPGrammar /dwarnings /dtypes
</pre>
*/
static apg_uint uiGetMsgs(INPUT* spInput);
static apg_uint uiGetStats(INPUT* spInput, OUTPUT* spOuput, apg_uint uiLevel);
static apg_uint uiGetTimes(INPUT* spInput, OUTPUT* spOutput, apg_uint uiParserLevel);
static void* vpGetParser(void* vpMemCtx, apg_uint uiLevel);
static void vDisplayResults(apg_uint uiParserCount, OUTPUT* spOutput);

int main() {
	char* cpMgsText = "TortureTests.txt";
	FILE* spOut = stdout;
	INPUT sInput;
	OUTPUT sOutput;
	apg_uint i, uiTest;
	apg_uint uiParserCount = 6;
	void*	vpaParserCtx[uiParserCount];
	TIME_INFO saTimeInfo[uiParserCount];
	STATS_INFO saStatsInfo[uiParserCount];

	fprintf(spOut, "*** main: SIP testing: begin\n");

	// input set up
	sInput.vpMemCtx = vpMemCtor();
	MASSERT(sInput.vpMemCtx);
	sInput.vpVecMsgChars = vpVecCtor(sInput.vpMemCtx, sizeof(apg_achar), 1000);
	MASSERT(sInput.vpVecMsgChars);
	sInput.vpVecMsgs = vpVecCtor(sInput.vpMemCtx, sizeof(MSG), 100);
	MASSERT(sInput.vpVecMsgs);
	sInput.vpTimer = vpTimerCtor(sInput.vpMemCtx);
	MASSERT(sInput.vpTimer);
	sInput.uiParserCount = uiParserCount;
	sInput.uiTimeRepetitions = 1000;
	sInput.vppParsers = &vpaParserCtx[0];
	sInput.cpMsgsTextFile = cpMgsText;

	// output setup
	sOutput.spStatsResults = &saStatsInfo[0];
	sOutput.spTimeResults = &saTimeInfo[0];

	// get the torture test messages
	uiTest = uiGetMsgs(&sInput);
    MASSERT(uiTest);

	// get the parsers
	for(i = 0; i < sInput.uiParserCount; i++){
		sInput.vppParsers[i] = vpGetParser(sInput.vpMemCtx, i);
		MASSERT(sInput.vppParsers[i]);
	}

	uiTest = uiParserStatsEnable(sInput.vppParsers[0], APG_FALSE);
	if(uiTest){
		// get the statistics for each parser
		for(i = 0; i < sInput.uiParserCount; i++){
			uiTest = uiGetStats(&sInput, &sOutput, i);
			MASSERT(uiTest);

		}
	}else{
		sOutput.spStatsResults = NULL;
	}

	// get the times for each parser
	fprintf(spOut, "\n*** Time tests running - this may take a few moments ...\n");
	for(i = 0; i < sInput.uiParserCount; i++){
		uiTest = uiGetTimes(&sInput, &sOutput, i);
		MASSERT(uiTest);
	}

	// display comparison results
	vDisplayResults(uiParserCount, &sOutput);

	vMemDtor(sInput.vpMemCtx);
	fprintf(spOut, "\n");
	fprintf(spOut, "*** main: SIP testing: end: EXIT_SUCCESS\n");
	return EXIT_SUCCESS;
}

static apg_uint uiGetStats(INPUT* spInput, OUTPUT* spOutput, apg_uint uiParserLevel){
	apg_uint uiRet = 0;
	apg_uint i, uiTest;
	FILE* spOut = stdout;
	void* vpParser = spInput->vppParsers[uiParserLevel];
	apg_uint uiStatsBufferSize = 100000;
	char caStatsBuffer[uiStatsBufferSize];
	APG_PARSER_STATS* spStats = (APG_PARSER_STATS*)&caStatsBuffer[0];
	STATS_INFO* spStatsInfo = &spOutput->spStatsResults[uiParserLevel];

	uiTest = uiParserStatsEnable(vpParser, APG_TRUE);
	if(!uiTest){
		fprintf(spOut, "*** PARSER STATISTICS: statistics not available\n");
		return APG_TRUE;
	}

	// parse the messages
	fprintf(spOut, "\n");
	fprintf(spOut, "*** PARSER STATISTICS: parser level: %u\n", (apg_uint)uiParserLevel);
	for(i = 0; i < spInput->uiMsgCount; i++){
		uiTest = uiParserSyntaxAnalysis(vpParser, 0,
				spInput->spMsgs[i].acpMsg, spInput->spMsgs[i].uiLength, NULL);
		if(!uiTest){fprintf(spOut, "\n    - SIP MESSAGE = %u: PARSER FAILED: parser level: %u\n",
				(apg_uint)i, (apg_uint)uiParserLevel);}
		else{uiRet++;}
	}

	// look at the parsing statistics
	fprintf(spOut, "*** PARSER STATISTICS: message count: %u\n", (apg_uint)spInput->uiMsgCount);
	uiParserStatsGet(vpParser, NULL, &uiTest);
	fprintf(spOut, "*** PARSER STATISTICS: buffer size: needed: %u: have: %u\n",
			(apg_uint)uiTest, (apg_uint)uiStatsBufferSize);
	if(uiTest <= uiStatsBufferSize){
		uiParserStatsGet(vpParser, spStats, &uiTest);
		fprintf(spOut, "*** PARSER STATISTICS:\n");
		vDisplayOperatorStats(spOut, spStats);
		vDisplayRuleStats(spOut, spStats, "count");
		spStatsInfo->uiaNodeStats[0] = spStats->sRnm.uiTotal;
		spStatsInfo->uiaNodeStats[1] = spStats->sUdt.uiTotal;
		spStatsInfo->uiaNodeStats[2] = spStats->sRep.uiTotal;
		spStatsInfo->uiaNodeStats[3] = spStats->sAlt.uiTotal;
		spStatsInfo->uiaNodeStats[4] = spStats->sCat.uiTotal;
		spStatsInfo->uiaNodeStats[5] = spStats->sAnd.uiTotal;
		spStatsInfo->uiaNodeStats[6] = spStats->sNot.uiTotal;
		spStatsInfo->uiaNodeStats[7] = spStats->sTrg.uiTotal;
		spStatsInfo->uiaNodeStats[8] = spStats->sTbs.uiTotal;
		spStatsInfo->uiaNodeStats[9] = spStats->sTls.uiTotal;
		spStatsInfo->uiaNodeStats[10] = spStats->sTotal.uiTotal;
	} else{
		fprintf(spOut, "*** PARSER STATISTICS: insufficient buffer size: needed: %u: have: %u\n",
				(apg_uint)uiTest, (apg_uint)uiStatsBufferSize);
		spStatsInfo->uiaNodeStats[0] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[1] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[2] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[3] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[4] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[5] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[6] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[7] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[8] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[9] = APG_UNDEFINED;
		spStatsInfo->uiaNodeStats[10] = APG_UNDEFINED;
	}

	return uiRet;
}
static apg_uint uiGetTimes(INPUT* spInput, OUTPUT* spOutput, apg_uint uiParserLevel){
	apg_uint uiRepsMax = 1000;
	apg_uint uiReps = 0;
	apg_uint uiMsgs;
	apg_uint uiMsgChars;
	apg_uint i, j, uiTest;
    double dDuration = 0.0;
	FILE* spOut = stdout;

	// parse the messages
	if(spInput->uiTimeRepetitions > uiRepsMax){
		fprintf(spOut, "*** uiGetTimes: uiReps = %u: reduced to uiRepsMax = %u\n",
				(apg_uint)spInput->uiTimeRepetitions, (apg_uint)uiRepsMax);
		spInput->uiTimeRepetitions = uiRepsMax;
	}
	uiReps = 0;
	uiMsgs = 0;
	uiMsgChars = 0;
	uiTimerStart(spInput->vpTimer);
	for(j = 0; j < spInput->uiTimeRepetitions; j++){
		for(i = 0; i < spInput->uiMsgCount; i++){
			uiTest = uiParserSyntaxAnalysis(spInput->vppParsers[uiParserLevel],
					RULE_SIPGRAMMAR_SIP_MESSAGE, spInput->spMsgs[i].acpMsg, spInput->spMsgs[i].uiLength, NULL);
			if(!uiTest){
				fprintf(spOut, "\n    - SIP MESSAGE = %u: PARSER FAILED\n", (apg_uint)i);
			}
			else{
				uiMsgs++;
				uiMsgChars += spInput->spMsgs[i].uiLength;
			}
		}
	}
	uiTimerStop(spInput->vpTimer);

	// look at the parsing statistics
	dDuration = dTimerDuration(spInput->vpTimer, APG_TIMER_MILLISEC);
	spOutput->spTimeResults[uiParserLevel].dTime = dDuration;
	spOutput->spTimeResults[uiParserLevel].uiMsgs = uiMsgs;
	spOutput->spTimeResults[uiParserLevel].uiMsgChars = uiMsgChars;
	fprintf(spOut, "\n");
	fprintf(spOut, "*** uiGetTimes:         time(msec): %1.4G\n", dDuration);
	fprintf(spOut, "    uiGetTimes:           messages: %u:\n", (apg_uint)uiMsgs);
	fprintf(spOut, "    uiGetTimes: message characters: %u:\n", (apg_uint)uiMsgChars);
	fprintf(spOut, "    uiGetTimes:     time(msec)/msg: %1.4G\n", dDuration/(double)uiMsgs);
	fprintf(spOut, "    uiGetTimes:    time(msec)/char: %1.4G\n", dDuration/(double)uiMsgChars);

	return uiMsgs;
}
static void* vpGetParser(void* vpMemCtx, apg_uint uiLevel){
	void* vpRet = NULL;
	void* vpParser = NULL;
	APG_CALLBACK saGrammar1UdtLib[UDT_COUNT_GRAMMAR1];
	APG_CALLBACK saGrammar2UdtLib[UDT_COUNT_GRAMMAR2];
	APG_CALLBACK saGrammar3UdtLib[UDT_COUNT_GRAMMAR3];
	APG_CALLBACK saGrammar4UdtLib[UDT_COUNT_GRAMMAR4];
	APG_CALLBACK saGrammar5UdtLib[UDT_COUNT_GRAMMAR5];
	memset((void*)saGrammar1UdtLib, 0, sizeof(APG_CALLBACK) * UDT_COUNT_GRAMMAR1);
	memset((void*)saGrammar2UdtLib, 0, sizeof(APG_CALLBACK) * UDT_COUNT_GRAMMAR2);
	memset((void*)saGrammar3UdtLib, 0, sizeof(APG_CALLBACK) * UDT_COUNT_GRAMMAR3);
	memset((void*)saGrammar4UdtLib, 0, sizeof(APG_CALLBACK) * UDT_COUNT_GRAMMAR4);
	memset((void*)saGrammar5UdtLib, 0, sizeof(APG_CALLBACK) * UDT_COUNT_GRAMMAR5);

	switch(uiLevel){
	case 0:
		vpParser = vpParserCtor(vpParserInit_SIPGrammar, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		break;
	case 1:
		vpParser = vpParserCtor(vpParserInit_Grammar1, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		saGrammar1UdtLib[UDT_GRAMMAR1_U_TOKEN] = (APG_CALLBACK)uiSIP_u_token;
		saGrammar1UdtLib[UDT_GRAMMAR1_U_UNRESERVED] = (APG_CALLBACK)uiSIP_u_unreserved;
		saGrammar1UdtLib[UDT_GRAMMAR1_E_DOMAINLABEL] = (APG_CALLBACK)uiSIP_e_domainlabel;
		saGrammar1UdtLib[UDT_GRAMMAR1_U_TOPLABEL] = (APG_CALLBACK)uiSIP_u_toplabel;
		saGrammar1UdtLib[UDT_GRAMMAR1_U_SCHEME] = (APG_CALLBACK)uiSIP_u_scheme;
		saGrammar1UdtLib[UDT_GRAMMAR1_U_CALLID] = (APG_CALLBACK)uiSIP_u_callid;
		saGrammar1UdtLib[UDT_GRAMMAR1_U_RFC1035DOMAIN] = (APG_CALLBACK)uiSIP_u_rfc1035domain;
		uiParserSyntaxInitCallbacks(vpParser, NULL, &saGrammar1UdtLib[0]);
		break;
	case 2:
		vpParser = vpParserCtor(vpParserInit_Grammar2, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		// Grammar1
		saGrammar2UdtLib[UDT_GRAMMAR2_U_TOKEN] = (APG_CALLBACK)uiSIP_u_token;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_UNRESERVED] = (APG_CALLBACK)uiSIP_u_unreserved;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_ONE_OR_MORE_UNRESERVED] = (APG_CALLBACK)uiSIP_u_one_or_more_unreserved;
		saGrammar2UdtLib[UDT_GRAMMAR2_E_DOMAINLABEL] = (APG_CALLBACK)uiSIP_e_domainlabel;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_TOPLABEL] = (APG_CALLBACK)uiSIP_u_toplabel;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_SCHEME] = (APG_CALLBACK)uiSIP_u_scheme;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_CALLID] = (APG_CALLBACK)uiSIP_u_callid;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_RFC1035DOMAIN] = (APG_CALLBACK)uiSIP_u_rfc1035domain;
		// Grammar2
		saGrammar2UdtLib[UDT_GRAMMAR2_U_HCOLON] = (APG_CALLBACK)uiSIP_u_HColon;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_COMMA] = (APG_CALLBACK)uiSIP_u_Comma;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_SEMI] = (APG_CALLBACK)uiSIP_u_Semi;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_SLASH] = (APG_CALLBACK)uiSIP_u_Slash;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_EQUAL] = (APG_CALLBACK)uiSIP_u_Equal;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_LAQUOT] = (APG_CALLBACK)uiSIP_u_LAQuot;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_RAQUOT] = (APG_CALLBACK)uiSIP_u_RAQuot;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_LDQUOT] = (APG_CALLBACK)uiSIP_u_LDQuot;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_RDQUOT] = (APG_CALLBACK)uiSIP_u_RDQuot;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_LHEX] = (APG_CALLBACK)uiSIP_u_LHEX;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_STAR] = (APG_CALLBACK)uiSIP_u_Star;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_COLON] = (APG_CALLBACK)uiSIP_u_Colon;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_LPAREN] = (APG_CALLBACK)uiSIP_u_LParen;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_RPAREN] = (APG_CALLBACK)uiSIP_u_RParen;
		saGrammar2UdtLib[UDT_GRAMMAR2_E_SWS] = (APG_CALLBACK)uiSIP_e_SWS;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_LWS] = (APG_CALLBACK)uiSIP_u_LWS;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_NC_VALUE] = (APG_CALLBACK)uiSIP_u_nc_value;
		saGrammar2UdtLib[UDT_GRAMMAR2_U_REQUEST_DIGEST] = (APG_CALLBACK)uiSIP_u_request_digest;
		uiParserSyntaxInitCallbacks(vpParser, NULL, &saGrammar2UdtLib[0]);
		break;
	case 3:
		vpParser = vpParserCtor(vpParserInit_Grammar3, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		// Grammar1
		saGrammar3UdtLib[UDT_GRAMMAR3_U_TOKEN] = (APG_CALLBACK)uiSIP_u_token;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_UNRESERVED] = (APG_CALLBACK)uiSIP_u_unreserved;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_ONE_OR_MORE_UNRESERVED] = (APG_CALLBACK)uiSIP_u_one_or_more_unreserved;
		saGrammar3UdtLib[UDT_GRAMMAR3_E_DOMAINLABEL] = (APG_CALLBACK)uiSIP_e_domainlabel;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_TOPLABEL] = (APG_CALLBACK)uiSIP_u_toplabel;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_SCHEME] = (APG_CALLBACK)uiSIP_u_scheme;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_CALLID] = (APG_CALLBACK)uiSIP_u_callid;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_RFC1035DOMAIN] = (APG_CALLBACK)uiSIP_u_rfc1035domain;
		// Grammar2
		saGrammar3UdtLib[UDT_GRAMMAR3_U_HCOLON] = (APG_CALLBACK)uiSIP_u_HColon;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_COMMA] = (APG_CALLBACK)uiSIP_u_Comma;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_SEMI] = (APG_CALLBACK)uiSIP_u_Semi;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_SLASH] = (APG_CALLBACK)uiSIP_u_Slash;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_EQUAL] = (APG_CALLBACK)uiSIP_u_Equal;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_LAQUOT] = (APG_CALLBACK)uiSIP_u_LAQuot;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_RAQUOT] = (APG_CALLBACK)uiSIP_u_RAQuot;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_LDQUOT] = (APG_CALLBACK)uiSIP_u_LDQuot;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_RDQUOT] = (APG_CALLBACK)uiSIP_u_RDQuot;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_LHEX] = (APG_CALLBACK)uiSIP_u_LHEX;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_STAR] = (APG_CALLBACK)uiSIP_u_Star;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_COLON] = (APG_CALLBACK)uiSIP_u_Colon;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_LPAREN] = (APG_CALLBACK)uiSIP_u_LParen;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_RPAREN] = (APG_CALLBACK)uiSIP_u_RParen;
		saGrammar3UdtLib[UDT_GRAMMAR3_E_SWS] = (APG_CALLBACK)uiSIP_e_SWS;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_LWS] = (APG_CALLBACK)uiSIP_u_LWS;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_NC_VALUE] = (APG_CALLBACK)uiSIP_u_nc_value;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_REQUEST_DIGEST] = (APG_CALLBACK)uiSIP_u_request_digest;
		// Grammar3
		saGrammar3UdtLib[UDT_GRAMMAR3_E_MESSAGE_BODY] = (APG_CALLBACK)uiSIP_e_MessageBody;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_ESCAPED] = (APG_CALLBACK)uiSIP_u_escaped;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_PNANE] = (APG_CALLBACK)uiSIP_u_pname;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_PVALUE] = (APG_CALLBACK)uiSIP_u_pvalue;
		saGrammar3UdtLib[UDT_GRAMMAR3_E_TEXT_UTF8_TRIM] = (APG_CALLBACK)uiSIP_e_text_utf8trim;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_EXTENSION_HEADER] = (APG_CALLBACK)uiSIP_u_extension_header;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_ONEORMOREDIGIT] = (APG_CALLBACK)uiSIP_u_OneOrMoreDigit;
		saGrammar3UdtLib[UDT_GRAMMAR3_E_DIGIT] = (APG_CALLBACK)uiSIP_e_digit;
		saGrammar3UdtLib[UDT_GRAMMAR3_U_CRLF] = (APG_CALLBACK)uiSIP_u_CRLF;
		uiParserSyntaxInitCallbacks(vpParser, NULL, &saGrammar3UdtLib[0]);
		break;
	case 4:
		vpParser = vpParserCtor(vpParserInit_Grammar4, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		// Grammar1
		saGrammar4UdtLib[UDT_GRAMMAR4_U_TOKEN] = (APG_CALLBACK)uiSIP_u_token;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_UNRESERVED] = (APG_CALLBACK)uiSIP_u_unreserved;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_ONE_OR_MORE_UNRESERVED] = (APG_CALLBACK)uiSIP_u_one_or_more_unreserved;
		saGrammar4UdtLib[UDT_GRAMMAR4_E_DOMAINLABEL] = (APG_CALLBACK)uiSIP_e_domainlabel;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_TOPLABEL] = (APG_CALLBACK)uiSIP_u_toplabel;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_SCHEME] = (APG_CALLBACK)uiSIP_u_scheme;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_CALLID] = (APG_CALLBACK)uiSIP_u_callid;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_RFC1035DOMAIN] = (APG_CALLBACK)uiSIP_u_rfc1035domain;
		// Grammar2
		saGrammar4UdtLib[UDT_GRAMMAR4_U_HCOLON] = (APG_CALLBACK)uiSIP_u_HColon;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_COMMA] = (APG_CALLBACK)uiSIP_u_Comma;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_SEMI] = (APG_CALLBACK)uiSIP_u_Semi;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_SLASH] = (APG_CALLBACK)uiSIP_u_Slash;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_EQUAL] = (APG_CALLBACK)uiSIP_u_Equal;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_LAQUOT] = (APG_CALLBACK)uiSIP_u_LAQuot;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_RAQUOT] = (APG_CALLBACK)uiSIP_u_RAQuot;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_LDQUOT] = (APG_CALLBACK)uiSIP_u_LDQuot;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_RDQUOT] = (APG_CALLBACK)uiSIP_u_RDQuot;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_LHEX] = (APG_CALLBACK)uiSIP_u_LHEX;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_STAR] = (APG_CALLBACK)uiSIP_u_Star;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_COLON] = (APG_CALLBACK)uiSIP_u_Colon;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_LPAREN] = (APG_CALLBACK)uiSIP_u_LParen;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_RPAREN] = (APG_CALLBACK)uiSIP_u_RParen;
//		saGrammar4UdtLib[UDT_GRAMMAR4_E_SWS] = (APG_CALLBACK)uiSIP_e_SWS;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_LWS] = (APG_CALLBACK)uiSIP_u_LWS;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_NC_VALUE] = (APG_CALLBACK)uiSIP_u_nc_value;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_REQUEST_DIGEST] = (APG_CALLBACK)uiSIP_u_request_digest;
		// Grammar3
		saGrammar4UdtLib[UDT_GRAMMAR4_E_MESSAGE_BODY] = (APG_CALLBACK)uiSIP_e_MessageBody;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_ESCAPED] = (APG_CALLBACK)uiSIP_u_escaped;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_PNANE] = (APG_CALLBACK)uiSIP_u_pname;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_PVALUE] = (APG_CALLBACK)uiSIP_u_pvalue;
		saGrammar4UdtLib[UDT_GRAMMAR4_E_TEXT_UTF8_TRIM] = (APG_CALLBACK)uiSIP_e_text_utf8trim;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_EXTENSION_HEADER] = (APG_CALLBACK)uiSIP_u_extension_header;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_ONEORMOREDIGIT] = (APG_CALLBACK)uiSIP_u_OneOrMoreDigit;
		saGrammar4UdtLib[UDT_GRAMMAR4_E_DIGIT] = (APG_CALLBACK)uiSIP_e_digit;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_CRLF] = (APG_CALLBACK)uiSIP_u_CRLF;
		// Grammar4
		saGrammar4UdtLib[UDT_GRAMMAR4_U_USER] = (APG_CALLBACK)uiSIP_u_user;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_IPV4ADDRESS] = (APG_CALLBACK)uiSIP_u_IPv4address;
		saGrammar4UdtLib[UDT_GRAMMAR4_U_QUOTED_STRING] = (APG_CALLBACK)uiSIP_u_quoted_string;
		uiParserSyntaxInitCallbacks(vpParser, NULL, &saGrammar4UdtLib[0]);
		break;
	case 5:
		vpParser = vpParserCtor(vpParserInit_Grammar5, vTerminalAlert);
		if(vpParser){vpRet = vpParser;}
		// Grammar1
		saGrammar5UdtLib[UDT_GRAMMAR5_U_TOKEN] = (APG_CALLBACK)uiSIP_u_token;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_UNRESERVED] = (APG_CALLBACK)uiSIP_u_unreserved;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_ONE_OR_MORE_UNRESERVED] = (APG_CALLBACK)uiSIP_u_one_or_more_unreserved;
		saGrammar5UdtLib[UDT_GRAMMAR5_E_DOMAINLABEL] = (APG_CALLBACK)uiSIP_e_domainlabel;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_TOPLABEL] = (APG_CALLBACK)uiSIP_u_toplabel;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_SCHEME] = (APG_CALLBACK)uiSIP_u_scheme;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_CALLID] = (APG_CALLBACK)uiSIP_u_callid;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_RFC1035DOMAIN] = (APG_CALLBACK)uiSIP_u_rfc1035domain;
		// Grammar2
//		saGrammar5UdtLib[UDT_GRAMMAR5_U_HCOLON] = (APG_CALLBACK)uiSIP_u_HColon;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_COMMA] = (APG_CALLBACK)uiSIP_u_Comma;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_SEMI] = (APG_CALLBACK)uiSIP_u_Semi;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_SLASH] = (APG_CALLBACK)uiSIP_u_Slash;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_EQUAL] = (APG_CALLBACK)uiSIP_u_Equal;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_LAQUOT] = (APG_CALLBACK)uiSIP_u_LAQuot;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_RAQUOT] = (APG_CALLBACK)uiSIP_u_RAQuot;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_LDQUOT] = (APG_CALLBACK)uiSIP_u_LDQuot;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_RDQUOT] = (APG_CALLBACK)uiSIP_u_RDQuot;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_LHEX] = (APG_CALLBACK)uiSIP_u_LHEX;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_STAR] = (APG_CALLBACK)uiSIP_u_Star;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_COLON] = (APG_CALLBACK)uiSIP_u_Colon;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_LPAREN] = (APG_CALLBACK)uiSIP_u_LParen;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_RPAREN] = (APG_CALLBACK)uiSIP_u_RParen;
//		saGrammar5UdtLib[UDT_GRAMMAR5_E_SWS] = (APG_CALLBACK)uiSIP_e_SWS;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_LWS] = (APG_CALLBACK)uiSIP_u_LWS;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_NC_VALUE] = (APG_CALLBACK)uiSIP_u_nc_value;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_REQUEST_DIGEST] = (APG_CALLBACK)uiSIP_u_request_digest;
		// Grammar3
		saGrammar5UdtLib[UDT_GRAMMAR5_E_MESSAGE_BODY] = (APG_CALLBACK)uiSIP_e_MessageBody;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_ESCAPED] = (APG_CALLBACK)uiSIP_u_escaped;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_PNANE] = (APG_CALLBACK)uiSIP_u_pname;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_PVALUE] = (APG_CALLBACK)uiSIP_u_pvalue;
		saGrammar5UdtLib[UDT_GRAMMAR5_E_TEXT_UTF8_TRIM] = (APG_CALLBACK)uiSIP_e_text_utf8trim;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_EXTENSION_HEADER] = (APG_CALLBACK)uiSIP_u_extension_header;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_ONEORMOREDIGIT] = (APG_CALLBACK)uiSIP_u_OneOrMoreDigit;
		saGrammar5UdtLib[UDT_GRAMMAR5_E_DIGIT] = (APG_CALLBACK)uiSIP_e_digit;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_CRLF] = (APG_CALLBACK)uiSIP_u_CRLF;
		// Grammar4
		saGrammar5UdtLib[UDT_GRAMMAR5_U_USER] = (APG_CALLBACK)uiSIP_u_user;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_IPV4ADDRESS] = (APG_CALLBACK)uiSIP_u_IPv4address;
		saGrammar5UdtLib[UDT_GRAMMAR5_U_QUOTED_STRING] = (APG_CALLBACK)uiSIP_u_quoted_string;
		// Grammar5
		saGrammar5UdtLib[UDT_GRAMMAR5_E_MESSAGE_HEADER] = (APG_CALLBACK)uiSIP_e_message_header;
		uiParserSyntaxInitCallbacks(vpParser, NULL, &saGrammar5UdtLib[0]);
		break;
	default:
		break;
	}

	return vpRet;
}

// get the torture test messages
static apg_uint uiGetMsgs(INPUT* spInput){
	apg_achar* acpMsgSrc;
	apg_uint uiMsgLength;
	apg_uint uiTest;

	// translate to binary messages
    uiTest = uiTortureTestTranslator(spInput->vpMemCtx, spInput->cpMsgsTextFile, spInput->vpVecMsgChars);
    MASSERT(uiTest);
    acpMsgSrc = (apg_achar*)vpVecFront(spInput->vpVecMsgChars);
    MASSERT(acpMsgSrc);
    uiMsgLength = uiVecSize(spInput->vpVecMsgChars);
    MASSERT(uiMsgLength);

    // separate the messages into BSTRs
    spInput->uiMsgCount = uiMessages(acpMsgSrc, uiMsgLength, spInput->vpVecMsgs);
    MASSERT(spInput->uiMsgCount);
    spInput->spMsgs = (MSG*)vpVecFront(spInput->vpVecMsgs);
    MASSERT(spInput->spMsgs);

	return APG_TRUE;
}

static void vDisplayResults(apg_uint uiParserCount, OUTPUT* spOutput){
	apg_uint i, uiNodeType, uiCount, uiBaseCount, uiPreviousCount;
	double dTime, dBaseTime, dPreviousTime, dBaseFactor, dPreviousFactor;
	char* cpNodeName;

	uiBaseCount = 0;
	dBaseTime = 0.0;
	if(spOutput->spStatsResults){
		// node stats
		printf("\n");
		printf("*** NODE COUNT COMPARISONS:\n");
		for(uiNodeType = 0; uiNodeType <= 10; uiNodeType++){
			switch(uiNodeType){
			case 0: cpNodeName = "RNM"; break;
			case 1: cpNodeName = "UDT"; break;
			case 2: cpNodeName = "REP"; break;
			case 3: cpNodeName = "ALT"; break;
			case 4: cpNodeName = "CAT"; break;
			case 5: cpNodeName = "AND"; break;
			case 6: cpNodeName = "NOT"; break;
			case 7: cpNodeName = "TRG"; break;
			case 8: cpNodeName = "TBS"; break;
			case 9: cpNodeName = "TLS"; break;
			case 10: cpNodeName = "TOTAL"; break;
			}
			printf("%10s %10s %10s %10s\n", cpNodeName, "total", "base", "previous");
			printf("%10s %10s %10s %10s\n", "test#", "count", "factor", "factor");
			uiPreviousCount = 0;
			for(i = 0; i < uiParserCount; i++){
				uiCount = spOutput->spStatsResults[i].uiaNodeStats[uiNodeType];
				if(uiCount == 0){printf("%10u %10u %10s %10s\n", i, uiCount, "--", "--");continue;}
				if(i == 0){
					uiBaseCount = spOutput->spStatsResults[i].uiaNodeStats[uiNodeType];
					printf("%10u %10u %10s %10s\n", i, uiCount, "--", "--");
				}else{
					dBaseFactor = (uiCount == 0) ? 0.0 : ((double)uiBaseCount/(double)uiCount);
					dPreviousFactor = (uiCount == 0) ? 0.0 : ((double)uiPreviousCount/(double)uiCount);
					printf("%10u %10u      %1.4G      %1.4G\n", i, uiCount, dBaseFactor, dPreviousFactor);
				}
				uiPreviousCount = uiCount;
			}
			printf("\n");
		}
	}

	// time stats
	printf("\n");
	printf("*** TIME COMPARISONS:\n");
	printf("%10s %10s %10s %10s\n", "", "total", "base", "previous");
	printf("%10s %10s %10s %10s\n", "test#", "time(msec)", "factor", "factor");
	dPreviousTime = 0.0;
	for(i = 0; i < uiParserCount; i++){
		dTime = spOutput->spTimeResults[i].dTime;
		if(i == 0){
			dBaseTime = spOutput->spTimeResults[i].dTime;
			printf("%10u       %1.4G %10s %10s \n", i, dTime, "--", "--");
		}else{
			dBaseFactor = (dTime == 0) ? 0.0 : dBaseTime/dTime;
			dPreviousFactor = (dTime == 0) ? 0.0 : dPreviousTime/dTime;
			printf("%10u       %1.4G      %1.4G      %1.4G \n", i, dTime, dBaseFactor, dPreviousFactor);
		}
		dPreviousTime = dTime;
	}
}
