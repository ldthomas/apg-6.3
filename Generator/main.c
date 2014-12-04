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
#include "SABNFGrammar.h"
#include "Grammar.h"
/** \file Generator/main.c \brief The main function that is the parser generator application, apg.*/

/** \cond NOSHOW */
// awful globals: used here so that they can be set dynamically but not necessary in vMainAlertHandler() call list
void* g_vpErrCtx = NULL;
void* g_vpWarnCtx = NULL;
/** \endcond */
static G_UINT uiValidateGrammar(void* vpCatCtx, void* vpErrCtx, void* vpWarnCtx);

// Linux OS exception handler
//#include <signal.h>
//static void vSignalHandler (int sig, siginfo_t *siginfo, void *context){
//	printf("\n");
//	printf("Signal Handler: signo: %d\n", siginfo->si_signo);
//	printf("Signal Handler: errno: %d\n", siginfo->si_errno);
//	printf("Signal Handler: code: %d\n", siginfo->si_code);
//	exit(EXIT_FAILURE);
//}
//typedef void (*PFN_OSEXCEPTION)(void);
//static void vOSExceptionHandler(){
//	int iTest;
//	struct sigaction act;
//	memset (&act, '\0', sizeof(act));
//	act.sa_sigaction = &vSignalHandler;
//	act.sa_flags = SA_SIGINFO;
//	for(iTest = 1; iTest < _NSIG; iTest++){
//		sigaction(iTest, &act, NULL);
//	}
//}

/** The main function of the parser generator application

@param argc the variable number of command line arguments
@param argv pointer to a list of pointers to the command line arguments.
The arguments and their meanings are given here or can be viewed by running "apg --help".
They are for the most part self-explanatory.
If in doubt about an option try it and what you get should be self-explanitory.
The only exception is, possibly, the attributes.
A separate, detailed discussion of these is given in the website documentation
<a href="http://ccri/apg/docs/doc63#attributes">here</a>
<pre>
APG(version 6.3)
Usage: apg options
options: one or more of the following:
</pre>
<pre>
help options
?                 - print this help screen
help              - print this help screen
/?                - print this help screen
/help             - print this help screen
-help             - print this help screen
--help            - print this help screen
</pre>
<pre>
version options
--version         - print version
-v                - print version
/v                - print version
</pre>
<pre>
name options
/in:pathname      - pathname of input SABNF grammar (required)
/out:path         - path for generated parser, including trailing delimiter (default = ./ or current working directory)
/log:pathname     - log output to pathname (default is console)
/C:name           - C-language parser project name (outputs files name.h & name.c)
/C++:name         - C++ language parser project name (outputs files name.h & name.cpp)
</pre>
<pre>
true/false options, all defaults are false
/dv               - verbose, implies all display options except /dopcodes & /dast
/dconfig          - display all of the configuration parameters
/dgrammar         - display input grammar file with one-based line numbers
/dwarnings        - display grammar syntax warnings
/dgrammar-metrics - display grammar metrics
/dattributes      - display attributes
/drules           - display rules and udts
/dast             - display AST records (caution: may generate many records)
/dtypes           - display the integer type sizes
/dopcodes         - display grammar opcodes in human-readable format (caution: may generate many opcodes)
</pre>
<pre>
options are case sensitive and must appear exactly as indicated above
paths, pathnames and names must be < 128 in length
default values of all true/false options are false
</pre>
*/
int main(int argc, char** argv){
	int iReturn = EXIT_FAILURE;
	void* vpMemCtx = NULL;
	void* vpParserCtx = NULL;
	void* vpCatCtx = NULL;
	void* vpErrCtx = NULL;
	void* vpWarnCtx = NULL;
	char* cpInputString = NULL;
	G_UINT uiTest;
	G_UINT uiTrace = APG_FALSE;
	G_UINT uiStats = APG_FALSE;
	G_UINT uiInputStringLen = 0;
	G_UINT uiInputStringBufLen = 0;
	apg_achar* acpInputString = NULL;
	CALLBACK_CTX sCallbackCtx;
	GRAMMAR_METRICS sMetrics;
	APG_CALLBACK saSemantic[RULE_COUNT_SABNFGRAMMAR];
	CM_CONFIG sConfig;

	printf("%u - sizeof(apg_uint)\n", sizeof(apg_uint));
	printf("%u - sizeof(apg_achar)\n", sizeof(apg_achar));
	printf("\n");

	while(APG_TRUE){
		///////////////////////////////////////////////////////////////////////////
		// SET UP
		///////////////////////////////////////////////////////////////////////////
		// memory and error reporting
		vpMemCtx = vpMemCtor();
		MSGASSERT(vpMemCtx, "memory component constructor failed");
		vpErrCtx = vpErrorsCtor(vpMemCtx, vMainAlertHandler);
		MSGASSERT(vpErrCtx, "error reporting constructor failed");
		g_vpErrCtx = vpErrCtx;
		vpWarnCtx = vpErrorsCtor(vpMemCtx, vMainAlertHandler);
		MSGASSERT(vpWarnCtx, "warning reporting component constructor failed");
		g_vpWarnCtx = vpWarnCtx;

		///////////////////////////////////////////////////////////////////////////
		// READ THE COMMAND LINE
		///////////////////////////////////////////////////////////////////////////
		// get the command line options
		uiTest = uiCommandLine(&sConfig, argc, argv);
		if(!uiTest){break;}
		if(sConfig.uiLog){
			// redirect of output to a log file requested on command line
			FILE* spRedirectOut;
			vLicenseNotice(stdout);
			printf("%s - output redirect file\n", sConfig.caLog);
			spRedirectOut = freopen(sConfig.caLog, "w", stdout);
			MSGASSERT(spRedirectOut, "failed to open output redirect file");
		}
		if(sConfig.uiVersion){
			vLicenseNotice(stdout);
			break;
		}
		if(sConfig.uiHelp){
			vDisplayHelp(argc, argv);
			break;
		}
		if(!sConfig.uiInput){
            printf("\n*** ");
			printf("input file name is required\n");
			vDisplayHelp(argc, argv);
			break;
		}
		vLicenseNotice(stdout);
		if(sConfig.uiDisplayConfig){
            printf("\n*** ");
            printf("configuration parameters\n");
            vDisplayConfig(&sConfig);
		}
		if(sConfig.uiDisplayTypes){
            printf("\n*** ");
            printf("integer type sizes\n");
            vDisplayTypeSizes(NULL);
		}

		///////////////////////////////////////////////////////////////////////////
		// PREPARE THE GRAMMAR FOR PARSING
		///////////////////////////////////////////////////////////////////////////
		// read the grammar
		uiInputStringLen = uiGetFileSize(&sConfig.caInput[0]);
		MSGASSERT(uiInputStringLen, "failed to get input file size - file probably does not exist");
		uiInputStringBufLen = (sizeof(apg_achar) * 2) * (uiInputStringLen + 10);
		cpInputString = (char*)vpMemAlloc(vpMemCtx, uiInputStringBufLen);
		MSGASSERT(cpInputString, "failed to allocate memory for input string");
		uiTest = uiGetFile(&sConfig.caInput[0], (void*)cpInputString);
		MSGASSERT(uiTest, "failed to read input string");
		if(!((cpInputString[uiInputStringLen - 1] == (char)10) || (cpInputString[uiInputStringLen - 1] == (char)13))){
			vErrorsReport(vpWarnCtx, "Grammar: Last line has no line ending. Line end CRLF added.");
			cpInputString[uiInputStringLen] = (char)13;
			uiInputStringLen++;
			cpInputString[uiInputStringLen] = (char)10;
			uiInputStringLen++;
		}
		cpInputString[uiInputStringLen] = 0;
		// catalog the lines for error reporting of line numbers
		vpCatCtx = vpCatalogCtor(vpMemCtx, vMainAlertHandler);
		MSGASSERT(vpCatCtx, "line number catalog constructor failed");
		uiTest = uiCatalogLines(vpCatCtx, cpInputString, uiInputStringLen);
		if(cpInputString && uiInputStringLen && sConfig.uiDisplayGrammar){
            printf("\n*** ");
			printf("annotated input string\n");
			vCatalogDisplay(vpCatCtx, stdout);
		}
		MSGASSERT(uiTest, "line number cataloging failed");
		// validate the grammar
		uiTest = uiValidateGrammar(vpCatCtx, vpErrCtx, vpWarnCtx);
		MSGASSERT(uiTest, "grammar validation failed");
		// convert input string to alphabet characters for the parser
		acpInputString = (apg_achar*)vpMemAlloc(vpMemCtx, uiInputStringLen + 10);
		MSGASSERT(acpInputString, "failed to allocate memory for alphabet character translation of input string");
		vCharToAChar(acpInputString, cpInputString, uiInputStringLen);

		///////////////////////////////////////////////////////////////////////////
		// PARSE THE GRAMMAR
		///////////////////////////////////////////////////////////////////////////
		// get the parser context
		vpParserCtx = vpParserCtor(vpParserInit_SABNFGrammar, vMainAlertHandler);
		MSGASSERT(vpParserCtx, "parser constructor failed");
		vSemanticInit(saSemantic);
		vParserAstInitCallbacks(vpParserCtx, saSemantic, NULL);		// define the AST for translation
		if(uiStats){uiParserStatsEnable(vpParserCtx, APG_TRUE);}	// enable statistics gathering
		if(uiTrace){uiParserTraceEnable(vpParserCtx, APG_TRUE);} // enable tracing
		vCallbackInit(vpMemCtx, &sCallbackCtx);					// provisions for the callback functions
		sCallbackCtx.pfnAlertHandler = vMainAlertHandler;
		sCallbackCtx.vpErrCtx = vpErrCtx;
		sCallbackCtx.vpWarnCtx = vpWarnCtx;
		sCallbackCtx.vpLineCatalogCtx = vpCatCtx;
		uiTest = uiParserSyntaxAnalysis(vpParserCtx, RULE_SABNFGRAMMAR_FILE, acpInputString, uiInputStringLen, &sCallbackCtx);
		MSGASSERT(uiTest, "parser syntax analysis failed");
		if(sConfig.uiDisplayState){
            printf("\n*** ");
			printf("generator state\n");
			vDisplayParserState(NULL, vpParserCtx);
		}
		if(sConfig.uiDisplayAst){
            printf("\n*** ");
			printf("AST\n");
			vDisplayAstRecords(NULL, vpParserCtx);
		}
		if(uiErrorsCount(vpErrCtx)){
		    break;
        }

		///////////////////////////////////////////////////////////////////////////
		// APG, THE PARSER GENERATOR: GENERATE A PARSER FROM THE INPUT GRAMMAR
		///////////////////////////////////////////////////////////////////////////
		uiParserAstTranslate(vpParserCtx, NULL, NULL, &sCallbackCtx);
		if(uiErrorsCount(vpErrCtx)){break;}
		if(sConfig.uiDisplayGrammarMetrics){
			// display of grammar metrics requested on command line
            printf("\n*** ");
			printf("grammar metrics\n");
			vGrammarMetrics(&sCallbackCtx, &sMetrics);
			vDisplayGrammarMetrics(&sMetrics);
		}
		if(sConfig.uiDisplayRules){
			// display of opcodes in human-readable format requested (may generate lots of output)
            printf("\n*** ");
			printf("rules\n");
			vGeneratorDisplayRules(&sCallbackCtx);
		}
		if(sConfig.uiDisplayOpcodes){
			// display of opcodes in human-readable format requested (may generate lots of output)
            printf("\n*** ");
			printf("opcodes (in human-readable format)n");
			vGeneratorDisplayOpcodes(&sCallbackCtx);
		}

		///////////////////////////////////////////////////////////////////////////
		// GRAMMAR ATTRIBUTES
		///////////////////////////////////////////////////////////////////////////
		// attributes
        ATTRS_CTX* vpAttrsCtx = (ATTRS_CTX*)vpAttrsCtor(&sCallbackCtx);
        MSGASSERT(vpAttrsCtx, "attributes component constructor failed");
        uiTest = uiAttributes(vpAttrsCtx);
        if(uiTest){
            if(sConfig.uiDisplayAttributes){
                printf("\n*** ");
                printf("rule reference types\n");
                vDisplayRuleDependencyTypes(vpAttrsCtx);
                printf("\n*** ");
                printf("grammar attributes\n");
                vDisplayAttrs(vpAttrsCtx);
            }
        } else{
            vErrorsReport(vpErrCtx, "Attributes error: unparsable attributes found - displaying attributes");
            printf("\n*** ");
            printf("rule reference types\n");
            vDisplayRuleDependencyTypes(vpAttrsCtx);
            printf("\n*** ");
            printf("grammar attributes\n");
            vDisplayAttrs(vpAttrsCtx);
            break;
        }

		///////////////////////////////////////////////////////////////////////////
		// OUTPUT THE GENERATED PARSER IN THE REQUESTED LANGUAGES
		///////////////////////////////////////////////////////////////////////////
		uiTrace = APG_FALSE;
		if(sConfig.uiC){
		    char caFileName[1024];
			char* cpPath = NULL;
			if(sConfig.uiOutput){cpPath = &sConfig.caOutput[0];}
            printf("\n*** ");
            printf("C parser generated\n");
			vGenerateCHeader(&sCallbackCtx, cpPath, &sConfig.caC[0], cpInputString, caFileName, 1024);
            printf("    %s\n", caFileName);
			vGenerateCSource(&sCallbackCtx, cpPath, &sConfig.caC[0], caFileName, 1024);
            printf("    %s\n", caFileName);
			uiTrace = APG_TRUE;
		}
		if(sConfig.uiCpp){
		    char caFileName[1024];
			char* cpPath = NULL;
			if(sConfig.uiOutput){cpPath = &sConfig.caOutput[0];}
            printf("\n*** ");
            printf("C++ parser generated\n");
			vGenerateCppHeader(&sCallbackCtx, cpPath, &sConfig.caCpp[0], cpInputString, caFileName, 1024);
            printf("    %s\n", caFileName);
			vGenerateCppSource(&sCallbackCtx, cpPath, &sConfig.caCpp[0], caFileName, 1024);
            printf("    %s\n", caFileName);
			uiTrace = APG_TRUE;
		}
		if(!uiTrace){printf("<no parser output requested>\n");}

		// success
		iReturn = EXIT_SUCCESS;
		break;
	}
	///////////////////////////////////////////////////////////////////////////
	// DIPSLAY ERRORS AND WARNINGS
	///////////////////////////////////////////////////////////////////////////
	if(sConfig.uiDisplayWarnings && vpWarnCtx && (G_UINT)uiErrorsCount(vpWarnCtx)){
        printf("\n*** ");
		printf("%lu warning(s) detected\n", (printf_uint)uiErrorsCount(vpWarnCtx));
		char* cpMsg = cpErrorsIterInit(vpWarnCtx);
		G_UINT uiError = 0;
		while(cpMsg){
			printf("%lu: %s\n", (G_UINT)uiError, cpMsg);
			uiError++;
			cpMsg = cpErrorsIterNext(vpWarnCtx);
		}
	}
	if(vpErrCtx && uiErrorsCount(vpErrCtx)){
        printf("\n*** ");
		printf("%lu error(s) detected\n", (printf_uint)uiErrorsCount(vpErrCtx));
		char* cpMsg = cpErrorsIterInit(vpErrCtx);
		G_UINT uiError = 0;
		while(cpMsg){
			printf("%lu: %s\n", (G_UINT)uiError, cpMsg);
			uiError++;
			cpMsg = cpErrorsIterNext(vpErrCtx);
		}
	}

	// success
	vMemDtor(vpMemCtx);
	return iReturn;
}

static G_UINT uiValidateGrammar(void* vpCatCtx, void* vpErrCtx, void* vpWarnCtx){
	G_UINT uiRet = APG_TRUE;
	CATALOG_CTX* spCtx = (CATALOG_CTX*)vpCatCtx;
	CATALOG_LINE* spLine = NULL;
	unsigned char* ucpChar;
	G_UINT uiChar;
	G_UINT uiHasNonABNFLineEnd = APG_FALSE;
	char caBuffer[2 * MAX_DISPLAY_LINE_LEN + 10];
	if(spCtx){
		spLine = spCatalogIterInit(vpCatCtx);
		while(spLine){
			if(spLine->uiLineEndLen == 1){uiHasNonABNFLineEnd = APG_TRUE;}
			uiChar = 0;
			for(ucpChar = (unsigned char*)spLine->cpBeg; ucpChar < (unsigned char*)spLine->cpEnd; ucpChar++, uiChar++){
				G_UINT uiError = APG_FALSE;
				if(*ucpChar < (unsigned char)9){uiError = APG_TRUE;}
				else if(*ucpChar > (unsigned char)10 && *ucpChar < (unsigned char)13){uiError = APG_TRUE;}
				else if(*ucpChar > (unsigned char)13 && *ucpChar < (unsigned char)32){uiError = APG_TRUE;}
				else if(*ucpChar > (unsigned char)127){uiError = APG_TRUE;}
				if(uiError){
					// report error
					G_UINT n = 0;
					uiRet = APG_FALSE;
					n += sprintf(&caBuffer[n],
							"Grammar: invalid character: line no: %lu: character no: %lu: character: %lu\n    ",
							(G_UINT)spLine->uiLineNo, (G_UINT)(spLine->uiBegChar + uiChar), (G_UINT)*ucpChar);
					vCatalogDisplayLine(spLine, &caBuffer[n], MAX_DISPLAY_LINE_LEN);
					vErrorsReport(vpErrCtx, &caBuffer[0]);
				}
			}
			spLine = spCatalogIterNext(vpCatCtx);
		}
	}
	if(uiHasNonABNFLineEnd){
		vErrorsReport(vpWarnCtx, "Grammar: has non-ABNF(non-CRLF) line endings");
	}
	return uiRet;
}

/** \cond NOSHOW */
void vMainAlertHandler(unsigned int uiLine, const char* cpFile){
	printf("\n");
	printf("ERROR: an unrecoverable error was encountered at the following file and line number:\n");
	printf(" line: %lu\n", (G_UINT)uiLine);
	printf(" file: %s\n", cpFile);
	printf("\n");
	if(g_vpErrCtx && uiErrorsCount(g_vpErrCtx)){
		char* cpMsg = cpErrorsIterInit(g_vpErrCtx);
		G_UINT uiError = 0;
		if(cpMsg){
			printf("\n*** %lu error(s) reported to the error log ***\n", (G_UINT)uiErrorsCount(g_vpErrCtx));
			while(cpMsg){
				printf("%lu: %s\n", (G_UINT)uiError, cpMsg);
				uiError++;
				cpMsg = cpErrorsIterNext(g_vpErrCtx);
			}
		}
	}
	if(g_vpWarnCtx && uiErrorsCount(g_vpWarnCtx)){
		char* cpMsg = cpErrorsIterInit(g_vpWarnCtx);
		G_UINT uiError = 0;
		if(cpMsg){
			printf("\n*** %lu warning(s) reported to the warning log ***\n", (G_UINT)uiErrorsCount(g_vpWarnCtx));
			while(cpMsg){
				printf("%lu: %s\n", (G_UINT)uiError, cpMsg);
				uiError++;
				cpMsg = cpErrorsIterNext(g_vpWarnCtx);
			}
		}
	}
	printf("\n");
	printf("*** exit(EXIT_FAILURE) called ***\n");
	exit(EXIT_FAILURE);
}

void vMsgAssert(char* cpMsg, unsigned int uiLine, char* cpFile){
	char caAssertBuffer[4096];
	char* cpAssertBuffer = &caAssertBuffer[0];
	G_UINT uiLen;
	char* cpNoMsg = "<no message>";
	if(!cpMsg){cpMsg = cpNoMsg;}
	uiLen = strlen(cpMsg);
	if(!uiLen){cpMsg = cpNoMsg;}
	sprintf(cpAssertBuffer, "line: %lu: file: %s: msg: %s", (G_UINT)uiLine, cpFile, cpMsg);
	vErrorsReport(g_vpErrCtx, cpAssertBuffer);
	vMainAlertHandler(uiLine, cpFile);
}
/** \endcond */
