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

#ifndef MAIN_H_
#define MAIN_H_
#include "Apg.h"
#include "ApgUtilities.h"
#include "SIPGrammar.h"
#include "Grammar1.h"
#include "Grammar2.h"
#include "Grammar3.h"
#include "Grammar4.h"
#include "Grammar5.h"
#include <stdio.h>
#include <stdlib.h>

#define MASSERT(cond) if(!(cond)){vTerminalAlert(__LINE__, __FILE__);}
#define CR (apg_achar)13
#define LF (apg_achar)10
#define SEMI (apg_achar)59

typedef struct{
	char*	cpStr;
	apg_uint	uiLength;
} BSTR;
typedef struct{
	apg_achar*	acpMsg;
	apg_uint	uiLength;
} MSG;

typedef struct{
	void*		vpParser;
	apg_uint	uiRuleCount;
	apg_uint	uiUdtCount;
	APG_RULE*	spRules;
	APG_UDT*	spUdts;

}PARSER_INFO;
typedef struct{
	void*		vpMemCtx;
	void*       vpVecMsgChars;
	void*       vpVecMsgs;
	void*		vpTimer;
	void**		vppParsers;
	char*		cpMsgsTextFile;
	MSG*        spMsgs;
	apg_uint    uiMsgCount;
	apg_uint	uiTimeRepetitions;
	apg_uint	uiParserCount;
} INPUT;

typedef struct{
	apg_uint	uiaNodeStats[11];
}STATS_INFO;
typedef struct{
	double		dTime;
	apg_uint	uiMsgs;
	apg_uint	uiMsgChars;
}TIME_INFO;
typedef struct{
	TIME_INFO*	spTimeResults;
	STATS_INFO*	spStatsResults;
} OUTPUT;


apg_uint uiTortureTestTranslator(void* vpMemCtx, const char* cpInput, void* vpVecMsgsBinary);
apg_uint uiMessages(apg_achar* acpSrc, apg_uint uiLen, void* vpVecMsg);

// SIP UDT library
// Grammar1 - alphanum and its uses
apg_uint uiSIP_u_token(APG_CBDATA* spData);
apg_uint uiSIP_u_unreserved(APG_CBDATA* spData);
apg_uint uiSIP_u_one_or_more_unreserved(APG_CBDATA* spData);
apg_uint uiSIP_e_domainlabel(APG_CBDATA* spData);
apg_uint uiSIP_u_toplabel(APG_CBDATA* spData);
apg_uint uiSIP_u_scheme(APG_CBDATA* spData);
apg_uint uiSIP_u_callid(APG_CBDATA* spData);
apg_uint uiSIP_u_rfc1035domain(APG_CBDATA* spData);

// Grammar2 - white space and line ends
apg_uint uiSIP_u_LWS(APG_CBDATA* spData);
apg_uint uiSIP_e_SWS(APG_CBDATA* spData);
apg_uint uiSIP_u_HColon(APG_CBDATA* spData);
apg_uint uiSIP_u_Comma(APG_CBDATA* spData);
apg_uint uiSIP_u_LAQuot(APG_CBDATA* spData);
apg_uint uiSIP_u_RAQuot(APG_CBDATA* spData);
apg_uint uiSIP_u_LDQuot(APG_CBDATA* spData);
apg_uint uiSIP_u_RDQuot(APG_CBDATA* spData);
apg_uint uiSIP_u_Semi(APG_CBDATA* spData);
apg_uint uiSIP_u_Slash(APG_CBDATA* spData);
apg_uint uiSIP_u_Equal(APG_CBDATA* spData);
apg_uint uiSIP_u_Star(APG_CBDATA* spData);
apg_uint uiSIP_u_Colon(APG_CBDATA* spData);
apg_uint uiSIP_u_LParen(APG_CBDATA* spData);
apg_uint uiSIP_u_RParen(APG_CBDATA* spData);
apg_uint uiSIP_u_LHEX(APG_CBDATA* spData);
apg_uint uiSIP_u_nc_value(APG_CBDATA* spData);
apg_uint uiSIP_u_request_digest(APG_CBDATA* spData);

// Grammar3
apg_uint uiSIP_e_MessageBody(APG_CBDATA* spData);
apg_uint uiSIP_u_escaped(APG_CBDATA* spData);
apg_uint uiSIP_u_pname(APG_CBDATA* spData);
apg_uint uiSIP_u_pvalue(APG_CBDATA* spData);
apg_uint uiSIP_e_text_utf8trim(APG_CBDATA* spData);
apg_uint uiSIP_u_extension_header(APG_CBDATA* spData);
apg_uint uiSIP_u_OneOrMoreDigit(APG_CBDATA* spData);
apg_uint uiSIP_e_digit(APG_CBDATA* spData);
apg_uint uiSIP_u_CRLF(APG_CBDATA* spData);

// Grammar4
apg_uint uiSIP_u_IPv4address(APG_CBDATA* spData);
apg_uint uiSIP_u_user(APG_CBDATA* spData);
apg_uint uiSIP_u_quoted_string(APG_CBDATA* spData);

// Grammar5
apg_uint uiSIP_e_message_header(APG_CBDATA* spData);

// test UDT library functions
apg_uint uiTestHostname();
apg_uint uiTestUnresereved();
apg_uint uiTestToken();
apg_uint uiTestScheme();
apg_uint uiTestCallid();
apg_uint uiTestRFC1035Domain();
apg_uint uiTestLws();
apg_uint uiTestHColon();
apg_uint uiTestHLetter();
apg_uint uiTestLeftRightLetter();
apg_uint uiTestLEX();
apg_uint uiTestNcValue();
apg_uint uiTestRequestDigest();
apg_uint uiTestMessageBody();

#endif /* MAIN_H_ */
