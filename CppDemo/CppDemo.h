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
#ifndef CPPDEMO_H
#define CPPDEMO_H
using namespace std;

/*********************************************************
 * NOTE: DO NOT MODIFY THE CONTENTS OF THIS FILE       ***
 *       CHANGES WILL BE LOST ON REGENERATION          ***
 ********************************************************/
class CppDemo{
	private:
	PFN_ALERT m_pfnAlertHandler;

	public:
	static void* m_vpParserInit;
	enum{
        RULEID_CRLF = 2, // CRLF
        RULEID_HELLO = 1, // Hello
        RULEID_HELLOWORLD = 0, // HelloWorld
        RULEID_COUNT = 3
	} RULEIDS;

	//UDT IDs
	enum{
        UDTID_U_WORLD = 0, // u_World
        UDTID_COUNT = 1
	} UDTIDS;

	// CLASS FUNCTIONS
	CppDemo();
	CppDemo(PFN_ALERT pfnAlertHandler);
	~CppDemo();
	void* vpGetParserCtx(){return m_vpParserCtx;}

	// parser syntax analysis
	void 		vDefineSyntaxCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks);
	apg_uint	uiSyntaxCallbacks(APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks);
	apg_uint	uiSyntaxAnalysis(apg_uint uiStartRule, apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData = NULL);
	apg_uint	uiState(APG_PARSER_STATE* spState);

	// parser semantic analysis
	void		vDefineAstNodes(apg_uint* uipRules, apg_uint* uipUdts);
	void		vDefineAstCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);
	void		vAstInitNodes(apg_uint* uipRules, apg_uint* uipUdts);
	void		vAstInitCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);
	apg_uint	uiAstTranslate(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks, void* vpData = NULL);

	// parser statistics
	apg_uint 	uiStatsEnable(apg_uint uiEnable = APG_TRUE);
	apg_uint	uiStatsGet(APG_PARSER_STATS* spStats, apg_uint* uipBufferSize);

	// parser trace configuration
	apg_uint	uiTraceEnable(apg_uint uiEnable = APG_TRUE);
	void		vTraceOp(apg_uint uiOpId, apg_uint uiEnable = APG_TRUE);
	void		vTraceRule(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);
	void		vTraceUdt(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);
	void		vTraceRange(apg_uint uiBegin = 0, apg_uint uiCount = APG_INFINITE);

	public:
	void* m_vpParserCtx;
	APG_PARSER_STATS* m_spStats;
	APG_PARSER_STATE m_sState;

	// SYNTAX CALL BACK FUNCTIONS
   static apg_uint uiSyn_CRLF(APG_CBDATA* spData);
   static apg_uint uiSyn_Hello(APG_CBDATA* spData);
   static apg_uint uiSyn_HelloWorld(APG_CBDATA* spData);
   static apg_uint uiSyn_u_World(APG_CBDATA* spData);

	// AST CALL BACK FUNCTIONS
   static apg_uint uiAst_CRLF(APG_CBDATA* spData);
   static apg_uint uiAst_Hello(APG_CBDATA* spData);
   static apg_uint uiAst_HelloWorld(APG_CBDATA* spData);
   static apg_uint uiAst_u_World(APG_CBDATA* spData);
};
#endif // CPPDEMO_H

//**** SABNF GRAMMAR ****
//;
//; Hello World C++ Demonstration Grammar
//;
//HelloWorld = Hello 1*%d32 u_World [CRLF]
//Hello = "Hello"
//CRLF = %d10
////**** SABNF GRAMMAR ***

