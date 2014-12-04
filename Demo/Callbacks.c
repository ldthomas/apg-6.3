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
#include "CallbacksGrammar.h"
/** \file Demo/Callbacks.c \brief Demonstrates writing and calling callback functions.*/

//apg_uint uiFile(APG_CBDATA* spData);
apg_uint uiSemiComment(APG_CBDATA* spData);
apg_uint uiCppComment(APG_CBDATA* spData);
apg_uint uiCComment(APG_CBDATA* spData);
apg_uint uiHexNum(APG_CBDATA* spData);
apg_uint uiLineEnd(APG_CBDATA* spData);
apg_uint uiBlankLine(APG_CBDATA* spData);
apg_uint uiUDT_u_LineError(APG_CBDATA* spData);

// callback functions
/** User data passed to the Parser. Used to collect specialized parsing statistics.
@see uiParserSyntaxAnalysis()
@brief user data passed to the Parser
*/
typedef struct{
	FILE* spOut;/**< The ouput device to print output to.*/
	apg_uint uiSemiComments;/**< The number of semi comments*/
	apg_uint uiCppComments;/**< The number of C++ comments*/
	apg_uint uiCComments;/**< The number of C comments*/
	apg_uint uiHexNumOverrides;/**< The number of hexidecimal numbers rejected semantically*/
	apg_uint uiSemiCommentsRejected;/**< The number of semi comments rejected*/
	apg_uint uiLineNo;/**< The number of imput lines*/
	apg_uint uiBlankLines;/**< The number of blank lines*/
	apg_uint uiLineErrors;/**< The number of line errors*/
	apg_uint uiaErrorLineNos[100];/**< The line numbers of line errors*/
} PARSER_CALLBACK_DATA;

/** User data passed to the AST translator.
@see uiParserAstTranslate()
@brief user data passed to the AST translator
*/
typedef struct{
	FILE* spOut;/**< The ouput device to print output to.*/
	apg_uint uiAstDepth;/**< Used to keep track of the AST tree depth.*/
} AST_CALLBACK_DATA;

/** A simple helper function to print blank spaces for indenting output.
@param spOut the output device to print on
@param uiIndent the number of spaces to indent
*/
void vIndent(FILE* spOut, apg_uint uiIndent){
	apg_uint i = 0;
	for(; i < uiIndent; i++){fprintf(spOut, " ");}
}
/** Syntax callback function for the File rule.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiFileParser(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = NULL;
	switch(spData->uiState){
	case PRE_PARSE:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		// pre-branch parse tree traversal (down)
		// initialize data
		FILE* spOut = spParserData->spOut;
		fprintf(spParserData->spOut, "\n");
		fprintf(spParserData->spOut, "uiFile: pre-parse processing\n");
		fprintf(spParserData->spOut, "uiFile: initialize the callback data\n");
		memset((void*)spParserData, 0, sizeof(PARSER_CALLBACK_DATA));
		spParserData->spOut = spOut;
		break;
	case MATCH:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		fprintf(spParserData->spOut, "\n");
		fprintf(spParserData->spOut, "uiFile: post-parse processing\n");
		fprintf(spParserData->spOut, "uiFile: display the collected data\n");
		fprintf(spParserData->spOut, "uiFile: state = %s\n", cpState2String(spData->uiState));
		fprintf(spParserData->spOut, "uiFile: %3lu = lines\n", (printf_uint)spParserData->uiLineNo);
		fprintf(spParserData->spOut, "uiFile: %3lu = blank lines\n", (printf_uint)spParserData->uiBlankLines);
		fprintf(spParserData->spOut, "uiFile: %3lu = hexidecimal numbers rejected semantically\n", (printf_uint)spParserData->uiHexNumOverrides);
		fprintf(spParserData->spOut, "uiFile: %3lu = SemiComments rejected\n", (printf_uint)spParserData->uiSemiCommentsRejected);
		fprintf(spParserData->spOut, "uiFile: %3lu = SemiComments\n", (printf_uint)spParserData->uiSemiComments);
		fprintf(spParserData->spOut, "uiFile: %3lu = CppComments\n", (printf_uint)spParserData->uiCppComments);
		fprintf(spParserData->spOut, "uiFile: %3lu = CComments\n", (printf_uint)spParserData->uiCComments);
		fprintf(spParserData->spOut, "uiFile: %3lu = errors\n", (printf_uint)spParserData->uiLineErrors);
		if(spParserData->uiLineErrors){
			apg_uint i;
			fprintf(spParserData->spOut, "uiFile:       errors at lines (one-based)\n");
			for(i = 0; i < spParserData->uiLineErrors; i++){
				fprintf(spParserData->spOut, "uiFile:       %lu\n", (printf_uint)spParserData->uiaErrorLineNos[i]);
			}
		}
		break;
	case EMPTY:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		fprintf(spParserData->spOut, "uiFile: error: state = EMPTY\n");
		break;
	case NOMATCH:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		fprintf(spParserData->spOut, "uiFile: error: state = NOMATCH\n");
		break;
	default:
		break;
	}
	return uiRet;
}
/** Semantic callback function for the File rule.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiFileAst(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	AST_CALLBACK_DATA* spAstData = NULL;
	switch(spData->uiState){
	case PRE_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		// pre-branch parse tree traversal (down)
		// initialize data
		FILE* spOut = spAstData->spOut;
		memset((void*)spAstData, 0, sizeof(AST_CALLBACK_DATA));
		spAstData->spOut = spOut;
		fprintf(spAstData->spOut, "\n");
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiFile: depth: %lu: PRE_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		spAstData->uiAstDepth++;
		break;
	case POST_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		spAstData->uiAstDepth--;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiFile: depth: %lu: POST_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		break;
	default:
		break;
	}
	return uiRet;
}
/** Syntax callback function for the SemiComment rule.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiSemiComment(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
	if(spData->uiState == PRE_PARSE){
		// pre-branch parse tree traversal (down)

	} else if(spData->uiState == MATCH){
		// post-branch parse tree traversal (up)
		// the grammar allows semi-comments, but here we are going to reject them semantically
		spData->uiPhraseLength = APG_UNDEFINED; // indicate that no phrase was matched
		uiRet = APG_TRUE; 						// override the normal syntax parsing of this rule
		spParserData->uiSemiCommentsRejected++;
	}
	return uiRet;
}
/** Syntax callback function for the CppComment rule.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiCppComment(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
	if(spData->uiState == PRE_PARSE){
		// pre-branch parse tree traversal (down)

	} else if(spData->uiState == MATCH){
		// post-branch parse tree traversal (up)
		spParserData->uiCppComments++;
	}
	return uiRet;
}
/** Syntax callback function for the CComment rule.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiCComment(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
	if(spData->uiState == PRE_PARSE){
		// pre-branch parse tree traversal (down)

	} else if(spData->uiState == MATCH){
		// post-branch parse tree traversal (up)
		spParserData->uiCComments++;
	}
	return uiRet;
}
/** Callback function for the Hexnum rule. Used for both syntax and semantic analysis.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiHexNum(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData;
	AST_CALLBACK_DATA* spAstData;
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	switch(spData->uiState){
	case PRE_PARSE:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		// pre-branch parse tree traversal (down)
		// make a quick decision about whether this is hexidecimal
		if(acpPhrase[1] != (apg_achar)'x'){
			// this is not hexidecimal - reject it semantically
			spData->uiPhraseLength = APG_UNDEFINED;	// indicates no phrase was matched
			uiRet = APG_TRUE; 						// override the normal parsing of this rule
			spParserData->uiHexNumOverrides++;
		}
		break;
	case MATCH:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		// post-branch parse tree traversal (up)
		spParserData->uiCComments++;
		break;
	case PRE_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiHexNum: depth: %lu: PRE_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		spAstData->uiAstDepth++;
		break;
	case POST_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		spAstData->uiAstDepth--;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiHexNum: depth: %lu: POST_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		break;
	default:
		break;
	}
	return uiRet;
}
/** Callback function for the Decnum rule. Used only for semantic analysis.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiDecNum(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	AST_CALLBACK_DATA* spAstData;
	switch(spData->uiState){
	case PRE_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiDecNum: depth: %lu: PRE_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		spAstData->uiAstDepth++;
		break;
	case POST_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		spAstData->uiAstDepth--;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiDecNum: depth: %lu: POST_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		break;
	default:
		break;
	}
	return uiRet;
}
/** Callback function for the LineEnd rule. Used only for syntax analysis.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiLineEnd(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
	if(spData->uiState == PRE_PARSE){
		// pre-branch parse tree traversal (down)

	} else if(spData->uiState == MATCH){
		// post-branch parse tree traversal (up)
		spParserData->uiLineNo++;
	}
	return uiRet;
}
/** Callback function for the BlankLine rule. Used only for syntax analysis.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiBlankLine(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
	if(spData->uiState == PRE_PARSE){
		// pre-branch parse tree traversal (down)

	} else if(spData->uiState == MATCH){
		// post-branch parse tree traversal (up)
		spParserData->uiBlankLines++;
	}
	return uiRet;
}
/** Callback function for the u_LineError UDT. Used for both syntax and semantic analysis.
@param spData the callback data passed to the function by the Parser
@return ignored by Parser
*/
apg_uint uiUDT_u_LineError(APG_CBDATA* spData){
	apg_uint uiRet = APG_FALSE;
	PARSER_CALLBACK_DATA* spParserData;
	AST_CALLBACK_DATA* spAstData;
	const apg_achar* acpPhrase = spData->acpSrc + spData->uiPhraseOffset;
	apg_uint uiPhraseLength = spData->uiSrcLen - spData->uiPhraseOffset;
	apg_uint uiErrorLength;
	apg_uint i;

	// when all else has failed,
	// suck up everything up to and including the next line end
	switch(spData->uiState){
	case PRE_PARSE:
		spParserData = (PARSER_CALLBACK_DATA*)spData->vpUserData;
		if(uiPhraseLength == 0){
			spData->uiPhraseLength = APG_UNDEFINED; // expect this when parser is discovering the EOS
		} else{
			uiErrorLength = 0;
			for(i = 0; i < uiPhraseLength; i++){
				if(acpPhrase[i] == (apg_achar)10){
					uiErrorLength = i + 1;
					break;
				}
				if(acpPhrase[i] == (apg_achar)13){
					if(i+1<uiPhraseLength && acpPhrase[i+1] == (apg_achar)10){
						uiErrorLength = i + 2;
						break;
					}
					uiErrorLength = i + 1;
					break;
				}
			}
			if(uiErrorLength == 0){spData->uiPhraseLength = i;}
			else{spData->uiPhraseLength = uiErrorLength;}

			// and report the error
			spParserData->uiLineNo++;
			spParserData->uiaErrorLineNos[spParserData->uiLineErrors] = spParserData->uiLineNo;
			spParserData->uiLineErrors++;
		}
		break;
	case PRE_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiUDT_u_LineError: depth: %lu: PRE_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		spAstData->uiAstDepth++;
		break;
	case POST_AST:
		spAstData = (AST_CALLBACK_DATA*)spData->vpUserData;
		spAstData->uiAstDepth--;
		vIndent(spAstData->spOut, spAstData->uiAstDepth);
		fprintf(spAstData->spOut, "uiUDT_u_LineError: depth: %lu: POST_AST translation\n", (printf_uint)spAstData->uiAstDepth);
		break;
	default:
		break;
	}
	return uiRet; // ignored by parser for UDTs
}

// NOTE: error handling is done with the statement:
//       if(error){vTerminalAlert(__LINE__, __FILE__);}
//       prints line and file where error was detected and exits

/** Demonstrates writing and using rule and UDT callback functions. The test output is written to Callbacks.output.

- parsing
  - adding callback functions to selected rules
  - overriding the syntax semantically
    - pre-branch syntax error detections
    - post-branch semantically overriding the syntax
    - adding the required callback functions for the UDTs defined in the grammar
- Abstract Syntax Tree (AST) translation
  - translating rule AST nodes
  - translating UDT AST nodes
  - using the same callback function for both parsing and AST translation
  - using the different callback functions for parsing and AST translation
*/
void vDemoCallbacks(){
	apg_uint uiBufferSize = 256;
	char caInputString[uiBufferSize];
	apg_achar acaParserString[uiBufferSize];
	apg_uint uiStrLen;
	apg_uint uiTest;
	APG_CALLBACK saRuleTranslations[RULE_COUNT_CALLBACKSGRAMMAR];
	APG_CALLBACK saUdtTranslations[UDT_COUNT_CALLBACKSGRAMMAR];
	APG_CALLBACK saRuleCallbacks[RULE_COUNT_CALLBACKSGRAMMAR];
	APG_CALLBACK saUdtCallbacks[UDT_COUNT_CALLBACKSGRAMMAR];
	PARSER_CALLBACK_DATA sParserData;
	AST_CALLBACK_DATA sAstData;
	void* vpParser = NULL;
	char* cpInFile = "Callbacks.input";
	char* cpOutFile = "Callbacks.output";
	FILE* spOut = NULL;

	// redirects output
	spOut = fopen(cpOutFile, "w");
	if(spOut){
		printf("%s - output redirect file for vDemoCallbacks\n", cpOutFile);
	} else{
		printf("could not open output file \"%s\" - using stdout instead\n", cpOutFile);
		spOut = stdout;
	}

	fprintf(spOut, "*** LICENSE NOTICE ***\n");
	vLicenseNotice(spOut);

	fprintf(spOut, "\n*** DEMO CALLBACKS ***\n");
	fprintf(spOut, "    - parsing\n");
	fprintf(spOut, "      - adding callback functions to selected rules\n");
	fprintf(spOut, "      - overriding the syntax semantically\n");
	fprintf(spOut, "        - pre-branch syntax error detections\n");
	fprintf(spOut, "        - post-branch semantically overriding the syntax\n");
	fprintf(spOut, "      - adding the required callback functions for the UDTs defined in the grammar\n");
	fprintf(spOut, "    - Abstract Syntax Tree (AST) translation\n");
	fprintf(spOut, "      - translating rule AST nodes\n");
	fprintf(spOut, "      - translating UDT AST nodes\n");
	fprintf(spOut, "      - using the same callback function for both parsing and AST translation\n");
	fprintf(spOut, "      - using the different callback functions for parsing and AST translation\n");

	// construct the parser
	vpParser = vpParserCtor(vpParserInit_CallbacksGrammar, vTerminalAlert);
	if(!vpParser){vTerminalAlert(__LINE__, __FILE__);}

	// get the input string
	memset((void*)&caInputString[0], 0, uiBufferSize);
	uiStrLen = uiGetFileSize(cpInFile);
	if(!uiStrLen){vTerminalAlert(__LINE__, __FILE__);}
	if(uiStrLen > uiBufferSize){vTerminalAlert(__LINE__, __FILE__);}
	uiTest = uiGetFile(cpInFile, (void*)&caInputString[0]);
	if(uiTest != uiStrLen){vTerminalAlert(__LINE__, __FILE__);}
	caInputString[uiStrLen] = 0;

	fprintf(spOut, "\n*** THE INPUT STRING\n");
	vDisplayAscii(spOut, caInputString, uiStrLen);

	// convert the input string to alphabet characters
	vCharToAChar(&acaParserString[0], &caInputString[0], uiStrLen);

	// setup for syntax callbacks
	memset((void*)saRuleCallbacks, 0, sizeof(saRuleCallbacks));
	memset((void*)saUdtCallbacks, 0, sizeof(saUdtCallbacks));
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_FILE] = uiFileParser;					// parser rule callback is different from AST callback
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_BLANKLINE] = uiBlankLine;
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_LINEEND] = uiLineEnd;
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_HEXNUM] = uiHexNum;
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_CCOMMENT] = uiCComment;
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_CPPCOMMENT] = uiCppComment;
	saRuleCallbacks[RULE_CALLBACKSGRAMMAR_SEMICOMMENT] = uiSemiComment;
	saUdtCallbacks[UDT_CALLBACKSGRAMMAR_U_LINEERROR] = uiUDT_u_LineError;
	uiParserSyntaxInitCallbacks(vpParser, &saRuleCallbacks[0], &saUdtCallbacks[0]);// parser UDT callback is same AST callback

	// set up for AST callbacks
	memset((void*)saRuleTranslations, 0, sizeof(saRuleTranslations));
	memset((void*)saUdtTranslations, 0, sizeof(saUdtTranslations));
	// we are not interesed in translating these node
	saRuleTranslations[RULE_CALLBACKSGRAMMAR_FILE] = uiFileAst;					// AST rule callback is different from parser callback
	saRuleTranslations[RULE_CALLBACKSGRAMMAR_HEXNUM] = uiHexNum;				// AST rule callback is same as parser callback
	saRuleTranslations[RULE_CALLBACKSGRAMMAR_DECNUM] = uiDecNum;				// AST node not used during parsing
	saUdtTranslations[UDT_CALLBACKSGRAMMAR_U_LINEERROR] = uiUDT_u_LineError;	// AST UDT callback is same as parser callback
	vParserAstInitCallbacks(vpParser, &saRuleTranslations[0], &saUdtTranslations[0]);

	// parse the string
	sParserData.spOut = spOut;
	sAstData.spOut = spOut;
	uiTest = uiParserSyntaxAnalysis(vpParser, RULE_CALLBACKSGRAMMAR_FILE, &acaParserString[0], uiStrLen, &sParserData);
	if(!uiTest){vTerminalAlert(__LINE__, __FILE__);}

	// examine the parser state
	fprintf(spOut, "\n*** PARSER STATE\n");
	vDisplayParserState(spOut, vpParser);

	// display the ast
	// look at the parsed phrases (AST nodes)
	fprintf(spOut, "\n*** AST NODES DISPLAY\n");
	vDisplayAstRecords(spOut, vpParser);

	// translate the AST
	fprintf(spOut, "\n*** AST TRANSLATIONS\n");
	uiTest = uiParserAstTranslate(vpParser, NULL, NULL, &sAstData);
	if(uiTest != 0){vTerminalAlert(__LINE__, __FILE__);}


	fprintf(spOut, "\n*** DEMO CALLBACKS - test ended successfully ***\n");
	if(spOut != stdout){fclose(spOut);}
}
