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
#include "Generator.h"
#include "Grammar.h"
#include <ctype.h>

typedef struct{
	char* cpName;
	G_UINT uiIndex;
} SORT_NAMES;

static void vGeneratorLicenseNotice(FILE* spFile);
static void vWriteGrammarData(FILE* spFile, void* vpVecData);
static G_UINT uiGenerateGrammarData(CALLBACK_CTX* spCtx, void* vpVec);
static int iCompNames(const void* vpLhs, const void* vpRhs);
static void vPrintOriginalGrammar(FILE* spFile, char* cpGrammar);
static void vToUpper(char* cpString, char* cpToUpper, G_UINT uiLen);
static G_UINT uiMinIntSize(G_UINT uiSize);

void vGenerateCppHeader(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpGrammar, char* cpFileName, apg_uint uiFileNameLen){
	char caHeaderDefine[1024];
	char caBuffer[1024];
	char caBuffer2[1024];
	FILE* spFile = NULL;
	FILE* spOut = NULL;
	G_UINT i;
	char* cpHeaderFileName;
	G_RULE* spRules = (G_RULE*)vpVecFront(spCtx->vpVecRuleTable);
	G_UINT uiRuleCount = (G_UINT)uiVecSize(spCtx->vpVecRuleTable);
	G_UDT* spUdts = (G_UDT*)vpVecFront(spCtx->vpVecUdtTable);
	char* cpStringTable = (char*)vpVecFront(spCtx->vpVecCharTable);
	char* cpName;
	G_UINT uiUdtCount = (G_UINT)uiVecSize(spCtx->vpVecUdtTable);
	G_UINT uiCheckPoint = uiMemCheckPoint(spCtx->vpMemCtx);
	SORT_NAMES* spRuleSort;
	SORT_NAMES* spUdtSort = NULL;

	GASSERT(cpProjectName);
	GASSERT(strlen(cpProjectName));

	// open the header file
	cpHeaderFileName = cpFileName;
	if(cpPath && cpPath[0]){
		GASSERT((strlen(cpProjectName) + strlen(cpPath) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpPath);
		strcat(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".h");
	} else{
		GASSERT((strlen(cpProjectName) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".h");
	}
	spFile = fopen(cpHeaderFileName, "w");
	GASSERT(spFile);
	spOut = spFile;

	spRuleSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiRuleCount);
	GASSERT(spRuleSort);
	for(i = 0; i < uiRuleCount; i++){
		spRuleSort[i].cpName = cpStringTable + spRules[i].uiNameOffset;
		spRuleSort[i].uiIndex = i;
	}
	qsort(spRuleSort, uiRuleCount, sizeof(SORT_NAMES), iCompNames);
	if(uiUdtCount){
		spUdtSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiUdtCount);
		GASSERT(spUdtSort);
		for(i = 0; i < uiUdtCount; i++){
			spUdtSort[i].cpName = cpStringTable + spUdts[i].uiNameOffset;
			spUdtSort[i].uiIndex = i;
		}
		qsort(spUdtSort, uiUdtCount, sizeof(SORT_NAMES), iCompNames);
	}

	// license notice
	vGeneratorLicenseNotice(spFile);
	caHeaderDefine[0] = 0;
	strcpy(caHeaderDefine, cpProjectName);
	strcat(caHeaderDefine, "_H");
	vToUpper(caHeaderDefine, caBuffer, sizeof(caBuffer));
	strcpy(caHeaderDefine, caBuffer);
	fprintf(spFile, "#ifndef %s\n", caHeaderDefine);
	fprintf(spFile, "#define %s\n", caHeaderDefine);

///////////////////////////////////////////////////////////////////////////////////////
	fprintf(spOut, "using namespace std;\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "/*********************************************************\n");
	fprintf(spOut, " * NOTE: DO NOT MODIFY THE CONTENTS OF THIS FILE       ***\n");
	fprintf(spOut, " *       CHANGES WILL BE LOST ON REGENERATION          ***\n");
	fprintf(spOut, " ********************************************************/\n");
	fprintf(spOut, "class %s{\n", cpProjectName);
	fprintf(spOut, "	private:\n");
	fprintf(spOut, "	PFN_ALERT m_pfnAlertHandler;\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	public:\n");
	fprintf(spOut, "	static void* m_vpParserInit;\n");
	fprintf(spOut, "	enum{\n");

	// rule name ids
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		fprintf(spFile, "        RULEID_%s = %lu,", caBuffer2, (unsigned long int)spRuleSort[i].uiIndex);
		fprintf(spFile, " // %s\n", cpName);
	}
	fprintf(spFile, "        RULEID_COUNT = %lu\n", (unsigned long int)uiRuleCount);
	fprintf(spFile, "	} RULEIDS;\n");
	fprintf(spFile, "\n");

	// udt name ids
    fprintf(spOut, "	//UDT IDs\n");
    fprintf(spOut, "	enum{\n");
	if(uiUdtCount){
		vToUpper(cpProjectName, caBuffer, sizeof(caBuffer));
		for(i = 0; i < uiUdtCount; i++){
			cpName = spUdtSort[i].cpName;
			vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
			fprintf(spFile, "        UDTID_%s = %lu,", caBuffer2, (unsigned long int)spUdtSort[i].uiIndex);
			fprintf(spFile, " // %s\n", cpName);
		}
	}
    fprintf(spFile, "        UDTID_COUNT = %lu\n", (unsigned long int)uiUdtCount);
    fprintf(spFile, "	} UDTIDS;\n");

	fprintf(spOut, "\n");
	fprintf(spOut, "	// CLASS FUNCTIONS\n");
	fprintf(spOut, "	%s();\n", cpProjectName);
	fprintf(spOut, "	%s(PFN_ALERT pfnAlertHandler);\n", cpProjectName);
	fprintf(spOut, "	~%s();\n", cpProjectName);
	fprintf(spOut, "	void* vpGetParserCtx(){return m_vpParserCtx;}\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	// parser syntax analysis\n");
	fprintf(spOut, "	void 		vDefineSyntaxCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks);\n");
	fprintf(spOut, "	apg_uint	uiSyntaxCallbacks(APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks);\n");
	fprintf(spOut, "	apg_uint	uiSyntaxAnalysis(apg_uint uiStartRule, apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData = NULL);\n");
	fprintf(spOut, "	apg_uint	uiState(APG_PARSER_STATE* spState);\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	// parser semantic analysis\n");
	fprintf(spOut, "	void		vDefineAstNodes(apg_uint* uipRules, apg_uint* uipUdts);\n");
	fprintf(spOut, "	void		vDefineAstCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);\n");
	fprintf(spOut, "	void		vAstInitNodes(apg_uint* uipRules, apg_uint* uipUdts);\n");
	fprintf(spOut, "	void		vAstInitCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks);\n");
	fprintf(spOut, "	apg_uint	uiAstTranslate(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks, void* vpData = NULL);\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	// parser statistics\n");
	fprintf(spOut, "	apg_uint 	uiStatsEnable(apg_uint uiEnable = APG_TRUE);\n");
	fprintf(spOut, "	apg_uint	uiStatsGet(APG_PARSER_STATS* spStats, apg_uint* uipBufferSize);\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	// parser trace configuration\n");
	fprintf(spOut, "	apg_uint	uiTraceEnable(apg_uint uiEnable = APG_TRUE);\n");
	fprintf(spOut, "	void		vTraceOp(apg_uint uiOpId, apg_uint uiEnable = APG_TRUE);\n");
	fprintf(spOut, "	void		vTraceRule(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);\n");
	fprintf(spOut, "	void		vTraceUdt(apg_uint uiIndex, apg_uint uiEnable = APG_TRUE);\n");
	fprintf(spOut, "	void		vTraceRange(apg_uint uiBegin = 0, apg_uint uiCount = APG_INFINITE);\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	public:\n");
	fprintf(spOut, "	void* m_vpParserCtx;\n");
	fprintf(spOut, "	APG_PARSER_STATS* m_spStats;\n");
	fprintf(spOut, "	APG_PARSER_STATE m_sState;\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "	// SYNTAX CALL BACK FUNCTIONS\n");
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		fprintf(spFile, "   static apg_uint uiSyn_%s(APG_CBDATA* spData);\n", cpName);
	}
	if(uiUdtCount){
		for(i = 0; i < uiUdtCount; i++){
			cpName = spUdtSort[i].cpName;
			fprintf(spFile, "   static apg_uint uiSyn_%s(APG_CBDATA* spData);\n", cpName);
		}
	}
	fprintf(spFile, "\n");
	fprintf(spFile, "	// AST CALL BACK FUNCTIONS\n");
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		fprintf(spFile, "   static apg_uint uiAst_%s(APG_CBDATA* spData);\n", cpName);
	}
	if(uiUdtCount){
		for(i = 0; i < uiUdtCount; i++){
			cpName = spUdtSort[i].cpName;
			fprintf(spFile, "   static apg_uint uiAst_%s(APG_CBDATA* spData);\n", cpName);
		}
	}
	fprintf(spFile, "};");
///////////////////////////////////////////////////////////////////////////////////////

	// #endif
	fprintf(spFile, "\n#endif // %s\n", caHeaderDefine);
	fprintf(spFile, "\n");
	fprintf(spFile, "//**** SABNF GRAMMAR ****\n");
	vPrintOriginalGrammar(spFile, cpGrammar);
	fprintf(spFile, "//**** SABNF GRAMMAR ***\n");
	fprintf(spFile, "\n");

	vMemFreeToCheckPoint(spCtx->vpMemCtx, uiCheckPoint);
}

void vGenerateCppSource(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpFileName, apg_uint uiFileNameLen){
	char caBuffer[1024];
	char caBuffer2[1024];
	FILE* spFile;
	FILE* spOut;
	G_UINT i;
	void* vpVecData = NULL;
	char* cpHeaderFileName;
	char* cpName = NULL;
	G_UINT guiMaxInt;
	SORT_NAMES* spRuleSort;
	SORT_NAMES* spUdtSort = NULL;
	G_RULE* spRules = (G_RULE*)vpVecFront(spCtx->vpVecRuleTable);
	G_UINT uiRuleCount = (G_UINT)uiVecSize(spCtx->vpVecRuleTable);
	G_UDT* spUdts = (G_UDT*)vpVecFront(spCtx->vpVecUdtTable);
	char* cpStringTable = (char*)vpVecFront(spCtx->vpVecCharTable);
	G_UINT uiUdtCount = (G_UINT)uiVecSize(spCtx->vpVecUdtTable);
	G_UINT uiCheckPoint = uiMemCheckPoint(spCtx->vpMemCtx);

	GASSERT(cpProjectName);
	GASSERT(strlen(cpProjectName));

	// open the header file
	cpHeaderFileName = cpFileName;
	if(cpPath && cpPath[0]){
		GASSERT((strlen(cpProjectName) + strlen(cpPath) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpPath);
		strcat(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".cpp");
	} else{
		GASSERT((strlen(cpProjectName) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".cpp");
	}
	spFile = fopen(cpHeaderFileName, "w");
	GASSERT(spFile);
	spOut = spFile;

	spRuleSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiRuleCount);
	GASSERT(spRuleSort);
	for(i = 0; i < uiRuleCount; i++){
		spRuleSort[i].cpName = cpStringTable + spRules[i].uiNameOffset;
		spRuleSort[i].uiIndex = i;
	}
	qsort(spRuleSort, uiRuleCount, sizeof(SORT_NAMES), iCompNames);
	if(uiUdtCount){
		spUdtSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiUdtCount);
		GASSERT(spUdtSort);
		for(i = 0; i < uiUdtCount; i++){
			spUdtSort[i].cpName = cpStringTable + spUdts[i].uiNameOffset;
			spUdtSort[i].uiIndex = i;
		}
		qsort(spUdtSort, uiUdtCount, sizeof(SORT_NAMES), iCompNames);
	}

	// grammar data
	vpVecData = vpVecCtor(spCtx->vpMemCtx, sizeof(G_UINT), 5000);
	GASSERT(vpVecData);
	guiMaxInt = uiGenerateGrammarData(spCtx, vpVecData);
	GASSERT(guiMaxInt != APG_UNDEFINED);

	// license notice
	vGeneratorLicenseNotice(spFile);
	fprintf(spFile, "#include \"Apg.h\"\n");
	strcpy(caBuffer, cpProjectName);
	strcat(caBuffer, ".h");
	fprintf(spFile, "#include \"%s\"\n", caBuffer);
	fprintf(spOut, "\n");

	// general info
	fprintf(spFile, "\n");
	fprintf(spFile, "// NOTE 1: Generator's ApgLib version number = \"%s\"\n", cpApgVersion());
	fprintf(spFile, "\n");
	fprintf(spFile, "// NOTE 2: The Parser's alphabet character (apg_achar) must be large enough to accommodate the grammar's largest character.\n");
	fprintf(spFile, "//         Grammar's largest alphabet character = %lu\n", (unsigned long int)spCtx->uiACharMax);
	fprintf(spFile, "//         Parser's sizeof(apg_achar) must be  >= %lu\n", (unsigned long int)uiMinIntSize(spCtx->uiACharMax));
	fprintf(spFile, "//         Grammar's largest integer(*)         = %lu\n", (unsigned long int)spCtx->uiUintMax);
	fprintf(spFile, "//         Parser's sizeof(apg_uint) must be   >= %lu\n", (unsigned long int)uiMinIntSize(spCtx->uiUintMax));
	fprintf(spFile, "//\n");
	fprintf(spFile, "//    (*): sizeof(apg_uint) <= 2 should be used with caution and only for extemely small parsers.\n");
	fprintf(spFile, "//         The largest integer refers only to the grammar's data. Other Parser integer's may,\n");
	fprintf(spFile, "//         and likely will, have larger requirements. Parser may fail unpredictably.\n");
	fprintf(spFile, "\n");
	fprintf(spFile, "static unsigned long int ulData[%lu] = {\n", (unsigned long int)uiVecSize(vpVecData));
	vWriteGrammarData(spFile, vpVecData);
	fprintf(spFile, "\n");
	fprintf(spFile, "};\n");
	vVecDtor(vpVecData);

	// pass pointer to Parser
	fprintf(spFile, "\n");
	fprintf(spFile, "// Parser initialization data\n");
	fprintf(spFile, "void* %s::m_vpParserInit = (void*)&ulData[0];\n", cpProjectName);
	fprintf(spOut, "\n");
	fprintf(spOut, "// Constructors\n");
	fprintf(spOut, "%s::%s(){\n", cpProjectName, cpProjectName);
	fprintf(spOut, "	m_pfnAlertHandler = NULL;\n");
	fprintf(spOut, "	m_vpParserCtx = vpParserCtor(m_vpParserInit, m_pfnAlertHandler);\n");
	fprintf(spOut, "	if(!m_vpParserCtx){m_pfnAlertHandler(__LINE__, __FILE__);}\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "%s::%s(PFN_ALERT pfnAlertHandler){\n", cpProjectName, cpProjectName);
	fprintf(spOut, "	m_vpParserCtx = vpParserCtor(m_vpParserInit, m_pfnAlertHandler);\n");
	fprintf(spOut, "	if(!m_vpParserCtx){m_pfnAlertHandler(__LINE__, __FILE__);}\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "// Destructor\n");
	fprintf(spOut, "%s::~%s(){if(m_vpParserCtx){vParserDtor(m_vpParserCtx);}}\n", cpProjectName, cpProjectName);
	fprintf(spOut, "\n");
	fprintf(spOut, "// Parser API\n");
	fprintf(spOut, "apg_uint %s::uiSyntaxCallbacks(APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks){\n", cpProjectName);
	fprintf(spOut, "	return uiParserSyntaxInitCallbacks(m_vpParserCtx, spRuleCallbacks, spUdtCallbacks);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "apg_uint %s::uiSyntaxAnalysis(apg_uint uiStartRule, apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData){\n", cpProjectName);
	fprintf(spOut, "	return uiParserSyntaxAnalysis(m_vpParserCtx, uiStartRule, acpSrc, uiSrcLen, vpData);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "apg_uint %s::uiState(APG_PARSER_STATE* spState){\n", cpProjectName);
	fprintf(spOut, "	return uiParserState(m_vpParserCtx, spState);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "void %s::vAstInitNodes(apg_uint* uipRules, apg_uint* uipUdts){\n", cpProjectName);
	fprintf(spOut, "	vParserAstInitNodes(m_vpParserCtx, uipRules, uipUdts);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "void %s::vAstInitCallbacks(APG_CALLBACK* ppfnRuleCallbacks, APG_CALLBACK* ppfnUdtCallbacks){\n", cpProjectName);
	fprintf(spOut, "	vParserAstInitCallbacks(m_vpParserCtx, ppfnRuleCallbacks, ppfnUdtCallbacks);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "apg_uint %s::uiAstTranslate(APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, void* vpData){\n", cpProjectName);
	fprintf(spOut, "	return uiParserAstTranslate(m_vpParserCtx, pfnRuleCallbacks, pfnUdtCallbacks, vpData);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "apg_uint %s::uiStatsEnable(apg_uint uiEnable){\n", cpProjectName);
	fprintf(spOut, "	return uiParserStatsEnable(m_vpParserCtx, uiEnable);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "apg_uint %s::uiStatsGet(APG_PARSER_STATS* spStats, apg_uint* uipBufferSize){\n", cpProjectName);
	fprintf(spOut, "	return uiParserStatsGet(m_vpParserCtx, spStats, uipBufferSize);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");
	fprintf(spOut, "apg_uint %s::uiTraceEnable(apg_uint uiEnable){\n", cpProjectName);
	fprintf(spOut, "	return uiParserTraceEnable(m_vpParserCtx, uiEnable);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "void %s::vTraceOp(apg_uint uiOpId, apg_uint uiEnable){\n", cpProjectName);
	fprintf(spOut, "	vParserTraceOp(m_vpParserCtx, uiOpId, uiEnable);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "void %s::vTraceRule(apg_uint uiIndex, apg_uint uiEnable){\n", cpProjectName);
	fprintf(spOut, "	vParserTraceRule(m_vpParserCtx, uiIndex, uiEnable);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "void %s::vTraceUdt(apg_uint uiIndex, apg_uint uiEnable){\n", cpProjectName);
	fprintf(spOut, "	vParserTraceUdt(m_vpParserCtx, uiIndex, uiEnable);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "void %s::vTraceRange(apg_uint uiBegin, apg_uint uiCount){\n", cpProjectName);
	fprintf(spOut, "	vParserTraceRange(m_vpParserCtx, uiBegin, uiCount);\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");

	fprintf(spOut, "///////////////////////////////////////////////////////////////////////////////\n");
	fprintf(spOut, "// PARSER HELPERS\n");
	fprintf(spOut, "// The following commented functions are provided as helper code to initially\n");
	fprintf(spOut, "// set up a parser. Cut and paste any functions desired to a separate *.cpp file\n");
	fprintf(spOut, "// and modify as needed for a specific application.\n");
	fprintf(spOut, "// DO NOT MODIFY THIS FILE - any changes will be over written on regeneration.\n");
	fprintf(spOut, "///////////////////////////////////////////////////////////////////////////////\n");
	fprintf(spOut, "/*\n");
	fprintf(spOut, "// To initialize the syntax callback functions before parsing,\n");
	fprintf(spOut, "// uncomment all required callback functions.\n");
	fprintf(spOut, "// sppRuleCallbacks array length must be at least %s::RULEID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// sppUdtCallbacks array length must be at least %s::UDTID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// No bounds checking is done.\n");
	fprintf(spOut, "// Arguments may be NULL.\n");
	fprintf(spOut, "void %s::vDefineSyntaxCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks){\n", cpProjectName);
	fprintf(spOut, "    if(sppRuleCallbacks){\n");
	fprintf(spOut, "        memset((void*)sppRuleCallbacks, 0, sizeof(APG_CALLBACK) * %s::RULEID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spRuleSort[i].uiIndex == 0){
            fprintf(spFile, "        sppRuleCallbacks[%s::RULEID_%s] = %s::uiSyn_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		} else{
            fprintf(spFile, "//      sppRuleCallbacks[%s::RULEID_%s] = %s::uiSyn_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "    if(sppUdtCallbacks){\n");
	fprintf(spOut, "        memset((void*)sppUdtCallbacks, 0, sizeof(APG_CALLBACK) * %s::UDTID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiUdtCount; i++){
		cpName = spUdtSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spUdtSort[i].uiIndex == 0){
            fprintf(spFile, "        sppUdtCallbacks[%s::UDTID_%s] = %s::uiSyn_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		} else{
            fprintf(spFile, "//      sppUdtCallbacks[%s::UDTID_%s] = %s::uiSyn_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "}\n");

	fprintf(spOut, "// To initialize the AST callback functions before AST translation,\n");
	fprintf(spOut, "// uncomment any required callback functions.\n");
	fprintf(spOut, "// sppRuleCallbacks array length must be at least %s::RULEID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// sppUdtCallbacks array length must be at least %s::UDTID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// No bounds checking is done.\n");
	fprintf(spOut, "// Arguments may be NULL.\n");
	fprintf(spOut, "void %s::vDefineAstCallbacks(APG_CALLBACK* sppRuleCallbacks, APG_CALLBACK* sppUdtCallbacks){\n", cpProjectName);
	fprintf(spOut, "    if(sppRuleCallbacks){\n");
	fprintf(spOut, "    memset((void*)sppRuleCallbacks, 0, sizeof(APG_CALLBACK) * %s::RULEID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spRuleSort[i].uiIndex == 0){
            fprintf(spFile, "        sppRuleCallbacks[%s::RULEID_%s] = %s::uiAst_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		} else{
            fprintf(spFile, "//      sppRuleCallbacks[%s::RULEID_%s] = %s::uiAst_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "    if(sppUdtCallbacks){\n");
	fprintf(spOut, "        memset((void*)sppUdtCallbacks, 0, sizeof(APG_CALLBACK) * %s::UDTID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiUdtCount; i++){
		cpName = spUdtSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spUdtSort[i].uiIndex == 0){
            fprintf(spFile, "        sppUdtCallbacks[%s::UDTID_%s] = %s::uiAst_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		} else{
            fprintf(spFile, "//      sppUdtCallbacks[%s::UDTID_%s] = %s::uiAst_%s;\n",
                    cpProjectName, caBuffer2, cpProjectName, cpName);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "}\n");

	fprintf(spOut, "// To define which nodes to keep in the the AST,\n");
	fprintf(spOut, "// uncomment any required nodes.\n");
	fprintf(spOut, "// sppRuleCallbacks array length must be at least %s::RULEID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// sppUdtCallbacks array length must be at least %s::UDTID_COUNT.\n", cpProjectName);
	fprintf(spOut, "// No bounds checking is done.\n");
	fprintf(spOut, "void %s::vDefineAstNodes(apg_uint* uipRuleCallbacks, apg_uint* uipUdtCallbacks){\n", cpProjectName);
	fprintf(spOut, "    if(uipRuleCallbacks){\n");
	fprintf(spOut, "        memset((void*)uipRuleCallbacks, 0, sizeof(APG_CALLBACK) * %s::RULEID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiRuleCount; i++){
		cpName = spRuleSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spRuleSort[i].uiIndex == 0){
            fprintf(spFile, "        uipRuleCallbacks[%s::RULEID_%s] = APG_TRUE;\n",	cpProjectName, caBuffer2);
		} else{
            fprintf(spFile, "//      uipRuleCallbacks[%s::RULEID_%s] = APG_TRUE;\n",	cpProjectName, caBuffer2);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "    if(uipUdtCallbacks){\n");
	fprintf(spOut, "        memset((void*)uipUdtCallbacks, 0, sizeof(APG_CALLBACK) * %s::UDTID_COUNT);\n", cpProjectName);
	for(i = 0; i < uiUdtCount; i++){
		cpName = spUdtSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		if(spUdtSort[i].uiIndex == 0){
            fprintf(spFile, "        uipUdtCallbacks[%s::UDTID_%s] = APG_TRUE;\n", cpProjectName, caBuffer2);
		} else{
            fprintf(spFile, "//      uipUdtCallbacks[%s::UDTID_%s] = APG_TRUE;\n", cpProjectName, caBuffer2);
		}
	}
	fprintf(spOut, "    }\n");
	fprintf(spOut, "}\n");

	fprintf(spOut, "\n");
	fprintf(spOut, "// Copy and override for each required Rule syntax callback functions\n");
	for(i = 0; i < uiRuleCount; i++){
		if(spRuleSort[i].uiIndex == 0){
			cpName = spRuleSort[i].cpName;
			vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
			break;
		}
	}
	fprintf(spOut, "// template for Rule syntax callback functions\n");
	fprintf(spOut, "apg_uint %s::uiSyn_%s(APG_CBDATA* spData){\n", cpProjectName, cpName);
	fprintf(spOut, "    apg_uint uiRet = APG_FALSE;\n");
    fprintf(spOut, "//  uncomment to access the phrase to be parsed by this function\n");
    fprintf(spOut, "//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;\n");
    fprintf(spOut, "//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;\n");
	fprintf(spOut, "    switch(spData->uiState){\n");
	fprintf(spOut, "    case PRE_PARSE:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    case NOMATCH:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    case MATCH:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    case EMPTY:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    }\n");
	fprintf(spOut, "    return uiRet; // if APG_TRUE this function will override the normal parsing of this rule\n");
	fprintf(spOut, "}\n");

	if(uiUdtCount > 0){
		for(i = 0; i < uiUdtCount; i++){
			if(spUdtSort[i].uiIndex == 0){
				cpName = spUdtSort[i].cpName;
				vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
				break;
			}
		}
        fprintf(spOut, "\n");
        fprintf(spOut, "// template for UDT syntax callback functions\n");
        fprintf(spOut, "// Copy and override for each required UDT syntax callback functions\n");
		fprintf(spOut, "apg_uint %s::uiSyn_%s(APG_CBDATA* spData){\n", cpProjectName, cpName);
        fprintf(spOut, "//  uncomment to access the phrase to be parsed by this function\n");
		fprintf(spOut, "//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;\n");
		fprintf(spOut, "//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;\n");
		fprintf(spOut, "    if(spData->uiState == PRE_PARSE){\n");
		fprintf(spOut, "    }\n");
		fprintf(spOut, "    return APG_UNDEFINED; // ignored by parser for UDTs\n");
		fprintf(spOut, "}\n");
	}

	fprintf(spOut, "\n");
	for(i = 0; i < uiRuleCount; i++){
		if(spRuleSort[i].uiIndex == 0){
			cpName = spRuleSort[i].cpName;
			vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
			break;
		}
	}
	fprintf(spOut, "// template for Rule AST callback functions\n");
	fprintf(spOut, "apg_uint %s::uiAst_%s(APG_CBDATA* spData){\n", cpProjectName, cpName);
    fprintf(spOut, "//  uncomment to access the phrase to be parsed by this function\n");
    fprintf(spOut, "//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;\n");
    fprintf(spOut, "//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;\n");
	fprintf(spOut, "    switch(spData->uiState){\n");
	fprintf(spOut, "    case PRE_AST:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    case POST_AST:\n");
	fprintf(spOut, "        break;\n");
	fprintf(spOut, "    }\n");
	fprintf(spOut, "    return APG_UNDEFINED; // return value ignored by parser\n");
	fprintf(spOut, "}\n");
	fprintf(spOut, "\n");
	if(uiUdtCount > 0){
		for(i = 0; i < uiUdtCount; i++){
			if(spUdtSort[i].uiIndex == 0){
				cpName = spUdtSort[i].cpName;
				vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
				break;
			}
		}
        fprintf(spOut, "// template for UDT AST callback functions\n");
		fprintf(spOut, "apg_uint %s::uiAst_%s(APG_CBDATA* spData){\n", cpProjectName, cpName);
        fprintf(spOut, "//  uncomment to access the phrase to be parsed by this function\n");
		fprintf(spOut, "//  const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;\n");
		fprintf(spOut, "//  apg_uint uiMaxPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;\n");
		fprintf(spOut, "    switch(spData->uiState){\n");
		fprintf(spOut, "    case PRE_AST:\n");
		fprintf(spOut, "        break;\n");
		fprintf(spOut, "    case POST_AST:\n");
		fprintf(spOut, "        break;\n");
		fprintf(spOut, "    }\n");
		fprintf(spOut, "    return APG_UNDEFINED; // return value ignored by parser\n");
		fprintf(spOut, "}\n");
	}
	fprintf(spOut, "*/\n");

	vMemFreeToCheckPoint(spCtx->vpMemCtx, uiCheckPoint);
}

void vGenerateCHeader(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpGrammar, char* cpFileName, apg_uint uiFileNameLen){
	char caBuffer[1024];
	char caBuffer2[1024];
	FILE* spFile = NULL;
	G_UINT i;
	char* cpHeaderFileName;
	G_RULE* spRules = (G_RULE*)vpVecFront(spCtx->vpVecRuleTable);
	G_UINT uiRuleCount = (G_UINT)uiVecSize(spCtx->vpVecRuleTable);
	G_UDT* spUdts = (G_UDT*)vpVecFront(spCtx->vpVecUdtTable);
	char* cpStringTable = (char*)vpVecFront(spCtx->vpVecCharTable);
	char* cpName;
	G_UINT uiUdtCount = (G_UINT)uiVecSize(spCtx->vpVecUdtTable);
	G_UINT uiCheckPoint = uiMemCheckPoint(spCtx->vpMemCtx);
	SORT_NAMES* spSort = NULL;

	GASSERT(cpProjectName);
	GASSERT(strlen(cpProjectName));

	// open the header file
	cpHeaderFileName = cpFileName;
	if(cpPath && cpPath[0]){
		GASSERT((strlen(cpProjectName) + strlen(cpPath) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpPath);
		strcat(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".h");
	} else{
		GASSERT((strlen(cpProjectName) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".h");
	}
	spFile = fopen(cpHeaderFileName, "w");
	GASSERT(spFile);

	// license notice
	vGeneratorLicenseNotice(spFile);
	vToUpper(cpHeaderFileName, caBuffer, sizeof(caBuffer));
	fprintf(spFile, "#ifndef %s\n", caBuffer);
	fprintf(spFile, "#define %s\n", caBuffer);

	// rule name ids
	spSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiRuleCount);
	GASSERT(spSort);
	for(i = 0; i < uiRuleCount; i++){
		spSort[i].cpName = cpStringTable + spRules[i].uiNameOffset;
		spSort[i].uiIndex = i;
	}
	qsort(spSort, uiRuleCount, sizeof(SORT_NAMES), iCompNames);
	fprintf(spFile, "\n// rule ids\n");
	vToUpper(cpProjectName, caBuffer, sizeof(caBuffer));
	for(i = 0; i < uiRuleCount; i++){
		cpName = spSort[i].cpName;
		vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
		fprintf(spFile, "#define RULE_%s_%s %lu", caBuffer, caBuffer2, (unsigned long int)spSort[i].uiIndex);
		fprintf(spFile, " // %s\n", cpName);
	}
	fprintf(spFile, "#define RULE_COUNT_%s %lu\n", caBuffer, (unsigned long int)uiRuleCount);

	// udt name ids
	if(uiUdtCount){
	    // alphabetize the UDT names
	    if(spSort != NULL){vMemFree(spCtx->vpMemCtx, (void*)spSort);}
        spSort = (SORT_NAMES*)vpMemAlloc(spCtx->vpMemCtx, sizeof(SORT_NAMES) * uiUdtCount);
        GASSERT(spSort);
        for(i = 0; i < uiUdtCount; i++){
            spSort[i].cpName = cpStringTable + spUdts[i].uiNameOffset;
            spSort[i].uiIndex = i;
        }
        qsort(spSort, uiUdtCount, sizeof(SORT_NAMES), iCompNames);



		fprintf(spFile, "\n// UDT ids\n");
		vToUpper(cpProjectName, caBuffer, sizeof(caBuffer));
		for(i = 0; i < uiUdtCount; i++){
//			cpName = cpStringTable + spUdts[i].uiNameOffset;
            cpName = spSort[i].cpName;
			vToUpper(cpName, caBuffer2, sizeof(caBuffer2));
//			fprintf(spFile, "#define UDT_%s_%s %lu", caBuffer, caBuffer2, (unsigned long int)spUdts[i].uiUdtIndex);
			fprintf(spFile, "#define UDT_%s_%s %lu", caBuffer, caBuffer2, (unsigned long int)spSort[i].uiIndex);
			fprintf(spFile, " // %s\n", cpName);
		}
		fprintf(spFile, "#define UDT_COUNT_%s %lu\n", caBuffer, (unsigned long int)uiUdtCount);
	}

	// extern
	fprintf(spFile, "\n");
	fprintf(spFile, "// Parser initialization data\n");
	fprintf(spFile, "extern void* vpParserInit_%s;\n", cpProjectName);

	// #endif
	vToUpper(cpHeaderFileName, caBuffer, sizeof(caBuffer));
	fprintf(spFile, "\n#endif // %s\n", caBuffer);
	fprintf(spFile, "\n");
	fprintf(spFile, "//**** SABNF GRAMMAR ****\n");
	vPrintOriginalGrammar(spFile, cpGrammar);
	fprintf(spFile, "//**** SABNF GRAMMAR ***\n");
	fprintf(spFile, "\n");

	vMemFreeToCheckPoint(spCtx->vpMemCtx, uiCheckPoint);
}

void vGenerateCSource(CALLBACK_CTX* spCtx, char* cpPath, char* cpProjectName, char* cpFileName, apg_uint uiFileNameLen){
	char caBuffer[1024];
	FILE* spFile;
	void* vpVecData = NULL;
	char* cpHeaderFileName;
	G_UINT guiMaxInt;

	GASSERT(cpProjectName);
	GASSERT(strlen(cpProjectName));

	// open the header file
	cpHeaderFileName = cpFileName;
	if(cpPath && cpPath[0]){
		GASSERT((strlen(cpProjectName) + strlen(cpPath) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpPath);
		strcat(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".c");
	} else{
		GASSERT((strlen(cpProjectName) + 5) < uiFileNameLen);
		strcpy(cpHeaderFileName, cpProjectName);
		strcat(cpHeaderFileName, ".c");
	}
	spFile = fopen(cpHeaderFileName, "w");
	GASSERT(spFile);

	// grammar data
	vpVecData = vpVecCtor(spCtx->vpMemCtx, sizeof(G_UINT), 5000);
	GASSERT(vpVecData);
	guiMaxInt = uiGenerateGrammarData(spCtx, vpVecData);
	GASSERT(guiMaxInt != APG_UNDEFINED);

	// license notice
	vGeneratorLicenseNotice(spFile);
	fprintf(spFile, "#include \"Apg.h\"\n");
	strcpy(caBuffer, cpProjectName);
	strcat(caBuffer, ".h");
	fprintf(spFile, "#include \"%s\"\n", caBuffer);

	// general info
	fprintf(spFile, "\n");
	fprintf(spFile, "// NOTE 1: Generator's ApgLib version number = \"%s\"\n", cpApgVersion());
	fprintf(spFile, "\n");
	fprintf(spFile, "// NOTE 2: The Parser's alphabet character (apg_achar) must be large enough to accommodate the grammar's largest character.\n");
	fprintf(spFile, "//         Grammar's largest alphabet character = %lu\n", (unsigned long int)spCtx->uiACharMax);
	fprintf(spFile, "//         Parser's sizeof(apg_achar) must be  >= %lu\n", (unsigned long int)uiMinIntSize(spCtx->uiACharMax));
	fprintf(spFile, "//         Grammar's largest integer(*)         = %lu\n", (unsigned long int)spCtx->uiUintMax);
	fprintf(spFile, "//         Parser's sizeof(apg_uint) must be   >= %lu\n", (unsigned long int)uiMinIntSize(spCtx->uiUintMax));
	fprintf(spFile, "//\n");
	fprintf(spFile, "//    (*): sizeof(apg_uint) <= 2 should be used with caution and only for extemely small parsers.\n");
	fprintf(spFile, "//         The largest integer refers only to the grammar's data. Other Parser integer's may,\n");
	fprintf(spFile, "//         and likely will, have larger requirements. Parser may fail unpredictably.\n");
	fprintf(spFile, "\n");
	fprintf(spFile, "static unsigned long int ulData[%lu] = {\n", (unsigned long int)uiVecSize(vpVecData));
	vWriteGrammarData(spFile, vpVecData);
	fprintf(spFile, "\n");
	fprintf(spFile, "};\n");
	vVecDtor(vpVecData);

	// pass pointer to Parser
	fprintf(spFile, "\n");
	fprintf(spFile, "// Parser initialization data\n");
	fprintf(spFile, "void* vpParserInit_%s = (void*)&ulData[0];\n", cpProjectName);
}

void vGrammarMetrics(CALLBACK_CTX* spCtx, GRAMMAR_METRICS* spMetrics){
	G_OPCODE* spOp;
	G_OPCODE* spOpEnd;
	memset((void*)spMetrics, 0, sizeof(GRAMMAR_METRICS));
	spMetrics->uiACharMin = spCtx->uiACharMin;
	spMetrics->uiACharMax = spCtx->uiACharMax;
	spMetrics->uiRuleCount = uiVecSize(spCtx->vpVecRuleTable);
	spMetrics->uiUdtCount = uiVecSize(spCtx->vpVecUdtTable);
	spMetrics->uiOpcodeCount = uiVecSize(spCtx->vpVecOpcodeTable);
	spOp = (G_OPCODE*)vpVecFront(spCtx->vpVecOpcodeTable);
	spOpEnd = spOp + spMetrics->uiOpcodeCount;
	for(; spOp < spOpEnd; spOp++){
		switch(spOp->uiType){
		case G_TYPE_ALT:
			spMetrics->uiAlt++;
			spMetrics->uiAltChildren += spOp->sOpType.sAlt.uiChildCount;
			break;
		case G_TYPE_CAT:
			spMetrics->uiCat++;
			spMetrics->uiCatChildren += spOp->sOpType.sCat.uiChildCount;
			break;
		case G_TYPE_REP:
			spMetrics->uiRep++;
			break;
		case G_TYPE_RNM:
			spMetrics->uiRnm++;
			break;
		case G_TYPE_UDT:
			spMetrics->uiUdt++;
			break;
		case G_TYPE_AND:
			spMetrics->uiAnd++;
			break;
		case G_TYPE_NOT:
			spMetrics->uiNot++;
			break;
		case G_TYPE_TRG:
			spMetrics->uiTrg++;
			break;
		case G_TYPE_TBS:
			spMetrics->uiTbs++;
			break;
		case G_TYPE_TLS:
			spMetrics->uiTls++;
			break;
		default:
			GASSERT(APG_FALSE);
			break;
		}
	}
}
void vDisplayGrammarMetrics(GRAMMAR_METRICS* spMetrics){
	char* cpFmt = "%6lu = %s\n";
	printf(cpFmt, (unsigned long int)spMetrics->uiACharMin, "min alphabet character code");
	printf(cpFmt, (unsigned long int)spMetrics->uiACharMax, "max alphabet character code");
	printf(cpFmt, (unsigned long int)spMetrics->uiRuleCount, "rules");
	printf(cpFmt, (unsigned long int)spMetrics->uiUdtCount, "UDTs");
	printf(cpFmt, (unsigned long int)spMetrics->uiOpcodeCount, "total opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiRnm, "RNM opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiUdt, "UDT opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiAlt, "ALT opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiAltChildren, "ALT alternates");
	printf(cpFmt, (unsigned long int)spMetrics->uiCat, "CAT opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiCatChildren, "CAT concatenated elements");
	printf(cpFmt, (unsigned long int)spMetrics->uiRep, "REP opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiAnd, "AND opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiNot, "NOT opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiTrg, "TRG opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiTbs, "TBS opcodes");
	printf(cpFmt, (unsigned long int)spMetrics->uiTls, "TLS opcodes");

}

///////////////////////////////////////////////////////////////////////////////
// STATIC HELPERS
///////////////////////////////////////////////////////////////////////////////
static int iCompNames(const void* vpLhs, const void* vpRhs){
	SORT_NAMES* spLhs = (SORT_NAMES*)vpLhs;
	SORT_NAMES* spRhs = (SORT_NAMES*)vpRhs;
	return apg_stricmp(spLhs->cpName, spRhs->cpName);
}
static void vPrintOriginalGrammar(FILE* spFile, char* cpGrammar){
	G_UINT i, uiLen = strlen(cpGrammar);
	fprintf(spFile, "//");
	for(i = 0; i < uiLen; i++){
		fprintf(spFile, "%c", cpGrammar[i]);
		if(cpGrammar[i] == (char)13){
			if(i+1<uiLen && cpGrammar[i+1]==(char)10){i++;}
			fprintf(spFile, "//");
		} else if(cpGrammar[i] == (char)10){fprintf(spFile, "//");}
	}
}

static void vToUpper(char* cpString, char* cpToUpper, G_UINT uiLen){
	GASSERT(cpString);
	GASSERT(cpToUpper);
	GASSERT(uiLen);
	uiLen++;
	uiLen = min(uiLen, (G_UINT)(strlen(cpString)+1));
	char* cpEnd = cpString + uiLen - 1;
	for(; cpString < cpEnd; cpString++, cpToUpper++){
		if(!isalnum(*cpString)){*cpToUpper = '_';}
		else{*cpToUpper = toupper(*cpString);}
	}
	*cpToUpper = 0;
}

static G_UINT uiMinIntSize(G_UINT uiSize){
	G_UINT uiRet = 0;
	G_UINT uiTest;
	while(APG_TRUE){
		uiTest = (unsigned char)-1;
		if(uiTest >= uiSize){uiRet = sizeof(unsigned char); break;}
		uiTest = (unsigned short int)-1;
		if(uiTest >= uiSize){uiRet = sizeof(unsigned short int); break;}
		uiTest = (unsigned int)-1;
		if(uiTest >= uiSize){uiRet = sizeof(unsigned int); break;}
		uiTest = (unsigned long int)-1;
		if(uiTest >= uiSize){uiRet = sizeof(unsigned long int); break;}
		break;
	}
	return uiRet;
}

static G_UINT uiGenerateGrammarData(CALLBACK_CTX* spCtx, void* vpVec){
	G_UINT guiRet = (G_UINT)APG_UNDEFINED;
	G_HDR sHdr;
	G_HDR* spHdr;
//	Gupdate_HDR sHdr;
//	Gupdate_HDR* spHdr;
	G_RULE* spRule;
	G_RULE* spVecRule;
	G_UDT* spUdt;
	G_UDT* spVecUdt;
	G_OPCODE* spOpcode;
	G_OPCODE* spVecOpcode;
	G_UINT i;
	G_UINT guiTest;
	G_UINT* guipData;
	G_UINT uiMaxIntSize;
	void* vpTest;
	char* cpChars;
	char* cpVersion = cpApgVersion();

	memset((void*)&sHdr, 0, sizeof(G_HDR));

	// allocate space for the header
	// NOTE: the byte size of all structures must be an integral number of G_UINT integers
	GASSERT((sizeof(G_HDR)/sizeof(G_UINT)) * sizeof(G_UINT) == sizeof(G_HDR));
	vVecClear(vpVec);
	vpTest = vpVecPushn(vpVec, (void*)&sHdr, (sizeof(G_HDR)/sizeof(G_UINT)));
	GASSERT(vpTest);
	memset(vpTest, 0, sizeof(*spHdr));

	// push the version
	sHdr.uiVersionOffset = uiVecSize(vpVec);
	sHdr.uiVersionLen = strlen(cpVersion) + 1;
	for(i = 0; i < sHdr.uiVersionLen; i++){
		guiTest = (G_UINT)cpVersion[i];
		vpTest = vpVecPush(vpVec, (void*)&guiTest);
		GASSERT(vpTest);
	}

	// push the ALT/CAT child index list
	sHdr.uiChildListOffset = uiVecSize(vpVec);
	sHdr.uiChildListLen = uiVecSize(spCtx->vpVecChildList);
	guipData = (G_UINT*)vpVecFront(spCtx->vpVecChildList);
	GASSERT(guipData);
	for(i = 0; i < sHdr.uiChildListLen; i++){
		guiTest = (G_UINT)guipData[i];
		vpTest = vpVecPush(vpVec, (void*)&guiTest);
		GASSERT(vpTest);
	}

	// push the rule table
	sHdr.uiRulesOffset = uiVecSize(vpVec);
	sHdr.uiRulesLen = uiVecSize(spCtx->vpVecRuleTable);
	spRule = (G_RULE*)vpVecFront(spCtx->vpVecRuleTable);
	GASSERT(spRule);
	GASSERT((sizeof(G_RULE)/sizeof(G_UINT)) * sizeof(G_UINT) == sizeof(G_RULE));
	spVecRule = (G_RULE*)vpVecPushn(vpVec, NULL, (sizeof(G_RULE)/sizeof(G_UINT)) * sHdr.uiRulesLen);
	GASSERT(spVecRule);
	for(i = 0; i < sHdr.uiRulesLen; i++){
		spVecRule[i] = spRule[i];
		spVecRule[i] = spRule[i];
	}

	// push the UDT table
	if(uiVecSize(spCtx->vpVecUdtTable)){
		sHdr.uiUdtsOffset = uiVecSize(vpVec);
		sHdr.uiUdtsLen = uiVecSize(spCtx->vpVecUdtTable);
		spUdt = (G_UDT*)vpVecFront(spCtx->vpVecUdtTable);
		GASSERT(spUdt);
		GASSERT((sizeof(G_UDT)/sizeof(G_UINT)) * sizeof(G_UINT) == sizeof(G_UDT));
		spVecUdt = (G_UDT*)vpVecPushn(vpVec, NULL, (sizeof(G_UDT)/sizeof(G_UINT)) * sHdr.uiUdtsLen);
		GASSERT(spVecUdt);
		for(i = 0; i < sHdr.uiUdtsLen; i++){
			spVecUdt[i] = spUdt[i];
		}
	}

	// push the opcode table
	GASSERT((sizeof(G_OPCODE)/sizeof(G_UINT)) * sizeof(G_UINT) == sizeof(G_OPCODE));
	sHdr.uiOpcodesOffset = uiVecSize(vpVec);
	sHdr.uiOpcodesLen = uiVecSize(spCtx->vpVecOpcodeTable);
	spVecOpcode = (G_OPCODE*)vpVecPushn(vpVec, NULL, sHdr.uiOpcodesLen * (sizeof(G_OPCODE)/sizeof(G_UINT)));
	GASSERT(spVecOpcode);
	spOpcode = (G_OPCODE*)vpVecFront(spCtx->vpVecOpcodeTable);
	GASSERT(spOpcode);
	for(i = 0; i < sHdr.uiOpcodesLen; i++){
		spVecOpcode[i] = spOpcode[i];
	}

	// push the character table
	sHdr.uiCharTableOffset = uiVecSize(vpVec);
	sHdr.uiCharTableLen = uiVecSize(spCtx->vpVecCharTable);
	cpChars = (char*)vpVecFront(spCtx->vpVecCharTable);
	GASSERT(cpChars);
	for(i = 0; i < sHdr.uiCharTableLen; i++){
		guiTest = (G_UINT)cpChars[i];
		vpTest = vpVecPush(vpVec, (void*)&guiTest);
		GASSERT(vpTest);
	}

	// compute the max int
	uiMaxIntSize = 0;
	i = 0;
	guipData = (G_UINT*)vpVecAt(vpVec, i);
	while(guipData){
        guiTest = *guipData;
		if(guiTest > uiMaxIntSize && guiTest < (G_UINT)APG_UNDEFINED){
		    uiMaxIntSize = guiTest;
        }
        i++;
        guipData = (G_UINT*)vpVecAt(vpVec, i);
	}
	sHdr.uiUintMax = uiMaxIntSize;
	spCtx->uiUintMax = uiMaxIntSize;

	// push the alphabet character table
	sHdr.uiACharTableOffset = uiVecSize(vpVec);
	sHdr.uiACharTableLen = uiVecSize(spCtx->vpVecACharTable);
	guipData = (G_UINT*)vpVecFront(spCtx->vpVecACharTable);
	GASSERT(guipData);
	for(i = 0; i < sHdr.uiACharTableLen; i++){
		guiTest = (G_UINT)guipData[i];
		vpTest = vpVecPush(vpVec, (void*)&guiTest);
		GASSERT(vpTest);
	}

	// complete the header
	sHdr.uiSizeInBytes = (G_UINT)(uiVecSize(vpVec) * sizeof(G_UINT));
	sHdr.uiACharMin = (G_UINT)spCtx->uiACharMin;
	sHdr.uiACharMax = (G_UINT)spCtx->uiACharMax;
	sHdr.uiMinSizeofACharMax = uiMinIntSize(sHdr.uiACharMax);
	sHdr.uiMinSizeofUintMax = uiMinIntSize(sHdr.uiUintMax);

    // finally, complete the header in the data Vector
	spHdr = (G_HDR*)vpVecFront(vpVec);
	GASSERT(spHdr);
	*spHdr = sHdr;
	guiRet = spHdr->uiSizeInBytes;
	return guiRet;
}

static void vWriteGrammarData(FILE* spFile, void* vpVecData){
	G_UINT uiMaxLineLen = 80;
	G_UINT uiLineLen;
	G_UINT uiCount, i;
	G_UINT* uipWords;

	GASSERT(vpVecData);
	uipWords = (G_UINT*)vpVecFront(vpVecData);
	GASSERT(uipWords);
	uiCount = uiVecSize(vpVecData);
	GASSERT(uiCount > 0);
	uiLineLen = 0;
	fprintf(spFile, "    ");
	for(i = 0; i < uiCount-1; i++){
		uiLineLen += fprintf(spFile, "%d, ", (int)uipWords[i]);
		if(uiLineLen >= uiMaxLineLen){
			fprintf(spFile, "\n");
			uiLineLen = 0;
			fprintf(spFile, "    ");
		}
	}
		uiLineLen += fprintf(spFile, "%d", (int)uipWords[i]);
}

static void vGeneratorLicenseNotice(FILE* spFile){
	if(!spFile){spFile = stdout;}
	fprintf(spFile, "/*******************************************************************************\n");
	vLicenseNotice(spFile);
	fprintf(spFile, "*******************************************************************************/\n");
}
