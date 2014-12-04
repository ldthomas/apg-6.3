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
#include "CppDemo.h"


// NOTE 1: Generator's ApgLib version number = "6.3"

// NOTE 2: The Parser's alphabet character (apg_achar) must be large enough to accommodate the grammar's largest character.
//         Grammar's largest alphabet character = 111
//         Parser's sizeof(apg_achar) must be  >= 1
//         Grammar's largest integer(*)         = 117
//         Parser's sizeof(apg_uint) must be   >= 1
//
//    (*): sizeof(apg_uint) <= 2 should be used with caution and only for extemely small parsers.
//         The largest integer refers only to the grammar's data. Other Parser integer's may,
//         and likely will, have larger requirements. Parser may fail unpredictably.

static unsigned long int ulData[163] = {
    1, 1, 1304, 10, 111, 117, 20, 4, 122, 34, 156, 7, 24, 4, 28, 3, 52, 1, 59, 9, 54, 
    46, 51, 0, 1, 2, 4, 5, 3, 44, 10, 4, 10, 0, 0, 7, 4, 85, 5, 23, 5, 1, 7, 1, 5, 101, 
    4, 29, 4, 2, 8, 1, 0, 0, 0, 15, 7, 0, 0, 41, 3, 57, 27, 0, 4, 0, 10, 3, 57, 5, -1, 
    1, 0, 30, 3, 63, 6, 3, 1, -1, 80, 3, 65, 4, 0, 1, 0, 20, 3, 70, 7, 0, 0, 0, 30, 
    3, 78, 6, 6, 0, 1, 10, 3, 79, 4, -1, 2, 0, 70, 4, 93, 7, 1, 5, 0, 80, 5, 108, 4, 
    6, 1, 0, 54, 46, 51, 0, 72, 101, 108, 108, 111, 87, 111, 114, 108, 100, 0, 117, 
    95, 87, 111, 114, 108, 100, 0, 72, 101, 108, 108, 111, 0, 67, 82, 76, 70, 0, 32, 
    72, 101, 108, 108, 111, 10
};

// Parser initialization data
void* CppDemo::m_vpParserInit = (void*)&ulData[0];

// Constructors
CppDemo::CppDemo(){
	m_pfnAlertHandler = NULL;
	m_vpParserCtx = vpParserCtor(m_vpParserInit, m_pfnAlertHandler);
	if(!m_vpParserCtx){m_pfnAlertHandler(__LINE__, __FILE__);}
}
CppDemo::CppDemo(PFN_ALERT pfnAlertHandler){
	m_vpParserCtx = vpParserCtor(m_vpParserInit, m_pfnAlertHandler);
	if(!m_vpParserCtx){m_pfnAlertHandler(__LINE__, __FILE__);}
}

// Destructor
CppDemo::~CppDemo(){if(m_vpParserCtx){vParserDtor(m_vpParserCtx);}}

// Parser API
apg_uint CppDemo::uiSyntaxCallbacks(APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks){
	return uiParserSyntaxInitCallbacks(m_vpParserCtx, spRuleCallbacks, spUdtCallbacks);
}
apg_uint CppDemo::uiSyntaxAnalysis(apg_uint uiStartRule, apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData){
	return uiParserSyntaxAnalysis(m_vpParserCtx, uiStartRule, acpSrc, uiSrcLen, vpData);
}
apg_uint CppDemo::uiState(APG_PARSER_STATE* spState){
	return uiParserState(m_vpParserCtx, spState);
}

void CppDemo::vAstInitNodes(apg_uint* uipRules, apg_uint* uipUdts){
	vParserAstInitNodes(m_vpParserCtx, uipRules, uipUdts);
}
void CppDemo::vAstInitCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks){
	vParserAstInitCallbacks(m_vpParserCtx, ppfnRuleCallbacks, ppfnUdtCallbacks);
}
apg_uint CppDemo::uiAstTranslate(APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, void* vpData){
	return uiParserAstTranslate(m_vpParserCtx, pfnRuleCallbacks, pfnUdtCallbacks, vpData);
}

apg_uint CppDemo::uiStatsEnable(apg_uint uiEnable){
	return uiParserStatsEnable(m_vpParserCtx, uiEnable);
}
apg_uint CppDemo::uiStatsGet(APG_PARSER_STATS* spStats, apg_uint* uipBufferSize){
	return uiParserStatsGet(m_vpParserCtx, spStats, uipBufferSize);
}

apg_uint CppDemo::uiTraceEnable(apg_uint uiEnable){
	return uiParserTraceEnable(m_vpParserCtx, uiEnable);
}
void CppDemo::vTraceOp(apg_uint uiOpId, apg_uint uiEnable){
	vParserTraceOp(m_vpParserCtx, uiOpId, uiEnable);
}
void CppDemo::vTraceRule(apg_uint uiIndex, apg_uint uiEnable){
	vParserTraceRule(m_vpParserCtx, uiIndex, uiEnable);
}
void CppDemo::vTraceUdt(apg_uint uiIndex, apg_uint uiEnable){
	vParserTraceUdt(m_vpParserCtx, uiIndex, uiEnable);
}
void CppDemo::vTraceRange(apg_uint uiBegin, apg_uint uiCount){
	vParserTraceRange(m_vpParserCtx, uiBegin, uiCount);
}

///////////////////////////////////////////////////////////////////////////////
// PARSER HELPERS
// The following commented functions are provided as helper code to initially
// set up a parser. Cut and paste any functions desired to a separate *.cpp file
// and modify as needed for a specific application.
// DO NOT MODIFY THIS FILE - any changes will be over written on regeneration.
///////////////////////////////////////////////////////////////////////////////
/*
// To initialize the syntax callback functions before parsing,
// uncomment all required callback functions.
// sppRuleCallbacks array length must be at least CppDemo::RULEID_COUNT.
// sppUdtCallbacks array length must be at least CppDemo::UDTID_COUNT.
// No bounds checking is done.
// Arguments may be NULL.
void CppDemo::vDefineSyntaxCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks){
    if(sppRuleCallbacks){
        memset((void*)sppRuleCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::RULEID_COUNT);
//      sppRuleCallbacks[CppDemo::RULEID_CRLF] = CppDemo::uiSyn_CRLF;
//      sppRuleCallbacks[CppDemo::RULEID_HELLO] = CppDemo::uiSyn_Hello;
        sppRuleCallbacks[CppDemo::RULEID_HELLOWORLD] = CppDemo::uiSyn_HelloWorld;
    }
    if(sppUdtCallbacks){
        memset((void*)sppUdtCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::UDTID_COUNT);
        sppUdtCallbacks[CppDemo::UDTID_U_WORLD] = CppDemo::uiSyn_u_World;
    }
}
// To initialize the AST callback functions before AST translation,
// uncomment any required callback functions.
// sppRuleCallbacks array length must be at least CppDemo::RULEID_COUNT.
// sppUdtCallbacks array length must be at least CppDemo::UDTID_COUNT.
// No bounds checking is done.
// Arguments may be NULL.
void CppDemo::vDefineAstCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks){
    if(sppRuleCallbacks){
    memset((void*)sppRuleCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::RULEID_COUNT);
//      sppRuleCallbacks[CppDemo::RULEID_CRLF] = CppDemo::uiAst_CRLF;
//      sppRuleCallbacks[CppDemo::RULEID_HELLO] = CppDemo::uiAst_Hello;
        sppRuleCallbacks[CppDemo::RULEID_HELLOWORLD] = CppDemo::uiAst_HelloWorld;
    }
    if(sppUdtCallbacks){
        memset((void*)sppUdtCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::UDTID_COUNT);
        sppUdtCallbacks[CppDemo::UDTID_U_WORLD] = CppDemo::uiAst_u_World;
    }
}
// To define which nodes to keep in the the AST,
// uncomment any required nodes.
// sppRuleCallbacks array length must be at least CppDemo::RULEID_COUNT.
// sppUdtCallbacks array length must be at least CppDemo::UDTID_COUNT.
// No bounds checking is done.
void CppDemo::vDefineAstNodes(apg_uint* uipRuleCallbacks, apg_uint* uipUdtCallbacks){
    if(uipRuleCallbacks){
        memset((void*)uipRuleCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::RULEID_COUNT);
//      uipRuleCallbacks[CppDemo::RULEID_CRLF] = APG_TRUE;
//      uipRuleCallbacks[CppDemo::RULEID_HELLO] = APG_TRUE;
        uipRuleCallbacks[CppDemo::RULEID_HELLOWORLD] = APG_TRUE;
    }
    if(uipUdtCallbacks){
        memset((void*)uipUdtCallbacks, 0, sizeof(APG_CALLBACK) * CppDemo::UDTID_COUNT);
        uipUdtCallbacks[CppDemo::UDTID_U_WORLD] = APG_TRUE;
    }
}

// Copy and override for each required Rule syntax callback functions
// template for Rule syntax callback functions
apg_uint CppDemo::uiSyn_HelloWorld(APG_CBDATA* spData){
    apg_uint uiRet = APG_FALSE;
//  uncomment to access the phrase to be parsed by this function
//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
    switch(spData->uiState){
    case PRE_PARSE:
        break;
    case NOMATCH:
        break;
    case MATCH:
        break;
    case EMPTY:
        break;
    }
    return uiRet; // if APG_TRUE this function will override the normal parsing of this rule
}

// template for UDT syntax callback functions
// Copy and override for each required UDT syntax callback functions
apg_uint CppDemo::uiSyn_u_World(APG_CBDATA* spData){
//  uncomment to access the phrase to be parsed by this function
//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
    if(spData->uiState == PRE_PARSE){
    }
    return APG_UNDEFINED; // ignored by parser for UDTs
}

// template for Rule AST callback functions
apg_uint CppDemo::uiAst_HelloWorld(APG_CBDATA* spData){
//  uncomment to access the phrase to be parsed by this function
//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
    switch(spData->uiState){
    case PRE_AST:
        break;
    case POST_AST:
        break;
    }
    return APG_UNDEFINED; // return value ignored by parser
}

// template for UDT AST callback functions
apg_uint CppDemo::uiAst_u_World(APG_CBDATA* spData){
//  uncomment to access the phrase to be parsed by this function
//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
    switch(spData->uiState){
    case PRE_AST:
        break;
    case POST_AST:
        break;
    }
    return APG_UNDEFINED; // return value ignored by parser
}
*/
