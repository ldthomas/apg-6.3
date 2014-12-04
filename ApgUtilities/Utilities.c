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
#include "ApgUtilities.h"
/** \file Utilities.c \brief A number of useful display functions.
*/
/** \cond NOSHOW */
typedef struct{
	APG_STAT* spStat;
	apg_uint uiIndex;
	char* cpName;
} APG_STATS_SORT;
/** \endcond */
static apg_uint uiIndent(apg_uint uiIndent, char* cpBuffer, apg_uint uiBufferLen);
static void vPrintOperatorLine(FILE* spOut, char* cpOp, APG_STAT* spNode);
static void vPrintOperatorList(FILE* spOut, APG_NAME_STAT* spNameStats, apg_uint uiCount, apg_uint uiType);
static void vDisplayOp(APG_PARSER_CTX*	spCtx, APG_OPCODE* spOp, apg_uint uiOpIndex);
static void vIndentPrint(FILE* spOut, apg_uint uiIndent);
static void vRootOpen(FILE* spOut, apg_uint uiLines, apg_uint uiNodes);
static void vRootClose(FILE* spOut);
static void vNodeOpen(FILE* spOut, apg_uint uiId, char* cpName);
static void vNodeClose(FILE* spOut, apg_uint uiId, char* cpName);
static void vPhraseText(FILE* spOut, const apg_achar* acpPhrase, apg_uint uiLength);
static void vPhrase(FILE* spOut, apg_uint uiOffset, apg_uint uiLength, const apg_achar* acpPhrase);
static void vPrintHeader(FILE* spOut);
static void vPrintLine(FILE* spOut, char* cpLine, apg_uint uiLine, apg_uint uiOffset, apg_uint uiLineLen);
static apg_uint uiAddNonAscii(char* cpAdd, char cChar);


///////////////////////////////////////////////////////////////////////////////
// DISPLAYS
///////////////////////////////////////////////////////////////////////////////
/** Displays a grammar (or any ASCII file of lines) with line and character number information.

Displays the grammar with 1-based line numbers and 0-based character offsets and lengths.
Non-ASCII characters are displayed in hex as \\xFF, for example.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param cpSrc pointer to the ASCII data to display
@param uiSrcLen the number of bytes to display
*/
void   vDisplayAscii(FILE* spOut, const char* cpSrc, apg_uint uiSrcLen){
	apg_uint uiBufLen = 5*uiSrcLen;
	char caBuffer[uiBufLen + 10];
	char* cpLine = &caBuffer[0];
	char* cpEllipsis = "...";
	char* cpEof = "<EOF>";
	apg_uint uiOffset = 0;
	apg_uint uiSkipAddingCharacters;
	apg_uint uiLineLen = 0;
	apg_uint uiLineNo = 1;
	apg_uint i;
	char cChar;

	if(spOut == NULL){spOut = stdout;}
	if(!(cpSrc && cpSrc[0])){
		fprintf(spOut, "vDisplaySourceLines: spSrc may not be NULL or empty\n");
		return;
	}

	vPrintHeader(spOut);
	uiSkipAddingCharacters = APG_FALSE;
	uiOffset = 0;
	uiLineLen = 0;
	uiLineNo = 1;
	cpLine = &caBuffer[0];
	for(i = 0; i < uiSrcLen; i++){
		cChar = cpSrc[i];
		if(cChar == 13){
			if(cpSrc[i+1] == 10){
				// CRLF line end
				uiLineLen += uiAddNonAscii(&cpLine[uiLineLen], cChar);
				uiLineLen += uiAddNonAscii(&cpLine[uiLineLen], cpSrc[i+1]);
				vPrintLine(spOut, cpLine, uiLineNo, uiOffset, i-uiOffset+2);
				uiOffset = i + 2;
				uiLineNo++;
				uiLineLen = 0;
				uiSkipAddingCharacters = APG_FALSE;
				i++; // increment for the extra line end character
			} else{
				// CR line end
				uiLineLen += uiAddNonAscii(&cpLine[uiLineLen], cChar);
				vPrintLine(spOut, cpLine, uiLineNo, uiOffset, i-uiOffset+1);
				uiOffset = i + 1;
				uiLineNo++;
				uiLineLen = 0;
				uiSkipAddingCharacters = APG_FALSE;
			}
		} else if(cChar == 10){
			// LF line end
			uiLineLen += uiAddNonAscii(&cpLine[uiLineLen], cChar);
			vPrintLine(spOut, cpLine, uiLineNo, uiOffset, i-uiOffset+1);
			uiOffset = i + 1;
			uiLineNo++;
			uiLineLen = 0;
			uiSkipAddingCharacters = APG_FALSE;
		} else{
			if(uiSkipAddingCharacters){
				// just increment the character count
				uiLineLen++;
			} else{
				if(cChar < 32 || cChar > 127){
						// non-ASCII
						uiLineLen += uiAddNonAscii(&cpLine[uiLineLen], cChar);
				} else{
					// non-special ASCII
					cpLine[uiLineLen] = cChar;
					uiLineLen++;
				}
			}
		}
		if(!uiSkipAddingCharacters && uiLineLen >= uiBufLen){
			// add ellipsis & quit adding characters to the buffer
			cpLine[uiLineLen] = 0;
			strcat(cpLine, cpEllipsis);
			uiLineLen += strlen(cpEllipsis);
			uiSkipAddingCharacters = APG_TRUE;
		}
	}
	if(uiLineLen > 0){
		// last line has no line end
		cpLine[uiLineLen] = 0;
		strcat(cpLine, cpEof);
		uiLineLen += strlen(cpEof);
		vPrintLine(spOut, cpLine, uiLineNo, uiOffset, uiLineLen);
	}
}

/** Displays a Parser's opcodes in a human-readable format.
@param vpCtx context handle of the Parser, previously returned from vpParserCtor().
@see vpParserCtor()
*/
void vDisplayOpcodes(void* vpCtx){
	APG_PARSER_CTX*	spCtx = (APG_PARSER_CTX*)vpCtx;
	apg_uint i, j, uiOpIndex;
	APG_RULE* spRule;
	APG_OPCODE* spOp;

	printf("vDisplayOpcodes:\n");
	uiOpIndex = 0;
	for(i = 0; i < spCtx->uiRuleCount; i++){
		spRule = &spCtx->spRules[i];
		printf("RNM(%s) index: %lu: opcodes: %lu\n",
				spRule->cpRuleName, (printf_uint)i, (printf_uint)spRule->uiOpcodeCount);
		spOp = spRule->spOp;
		for(j = 0; j < spCtx->spRules[i].uiOpcodeCount; j++, spOp++){
			vDisplayOp(spCtx, spOp, uiOpIndex);
			uiOpIndex++;
		}
		printf("\n");
	}
}

/** Displays the Abstract Syntax Tree (AST) records.

There is one record for each rule/UDT node visit.
That means two records for each node: one for the PRE_AST or downward direction visit
and one for the POST_AST or upward direction visit.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param vpParserCtx context handle of the Parser, previously returned from vpParserCtor().
@see vpParserCtor()
*/
void vDisplayAstRecords(FILE* spOut, void*	vpParserCtx){
	APG_PARSER_CTX* spParserCtx = (APG_PARSER_CTX*)vpParserCtx;
	if(spParserCtx->vpAstCtx){
		apg_uint uiCharLen;
		apg_uint uiBufLen = 128;
		char cpBuffer[uiBufLen];

		char caPrtBuf[APG_DISPLAY_MAX_LINE + sizeof(PRINTBUF) + 1];
		void* vpPrtBuf = NULL;
		char caScratchBuf[3*APG_DISPLAY_MAX_LINE + 1];

		char* cpState;
		APG_AST_CTX* spCtx = (APG_AST_CTX*)spParserCtx->vpAstCtx;
		APG_AST_RECORD* spRecord = spCtx->spRecords;
		APG_AST_RECORD* spRecordEnd = spCtx->spRecords + spCtx->uiRecordCount;
		const apg_achar* acpPhrase;
		apg_uint uiPhraseLen;
		apg_uint uiTreeDepth = 0;

		if(spOut == NULL){spOut = stdout;}
		fprintf(spOut, "    a: this  record number\n");
		fprintf(spOut, "    b: other record number\n");
		fprintf(spOut, "    c: tree depth\n");
		fprintf(spOut, "    d: state: ~=open, M=MATCH, E=EMPTY\n");
		fprintf(spOut, "    e: indented operator\n");
		fprintf(spOut, "    f: phrase offset\n");
		fprintf(spOut, "    g: phrase length\n");
		fprintf(spOut, "    h: phrase (... = truncated)\n");
		fprintf(spOut, "%5s:%5s:%3s:%s:%2s:%s:%3s:%3s\n", "a", "b", "c", "d", "e", "f", "g", "h");
		fprintf(spOut, "%5s:%5s:%3s:%s:%s:%s:%3s:%3s\n", "-----", "-----", "---", "-", "--", "-", "---", "---");
		for(; spRecord < spRecordEnd; spRecord++){
			vpPrtBuf = vpStrBufInit(&caPrtBuf[0], sizeof(caPrtBuf));
			if(spRecord->uiState == PRE_AST){
				cpState = "~";
				sprintf(&caScratchBuf[0], "%5lu:%5lu:%3lu:%s:",
						(printf_uint)spRecord->uiThisRecord, (printf_uint)spRecord->uiThatRecord, (printf_uint)uiTreeDepth, cpState);
				uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
				acpPhrase = spParserCtx->acpInputString + spRecord->uiPhraseOffset;
				uiPhraseLen = spRecord->uiPhraseLength;
				uiIndent(uiTreeDepth, cpBuffer, uiBufLen);
				if(spRecord->uiId >= spParserCtx->uiRuleCount){
					APG_UDT* spUdt = spParserCtx->spUdts + spRecord->uiId - spParserCtx->uiRuleCount;
					sprintf(&caScratchBuf[0], "%s%s:%lu:%lu:", cpBuffer, spUdt->cpUdtName,
							(printf_uint)spRecord->uiPhraseOffset, (printf_uint)spRecord->uiPhraseLength);
					uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
					uiCharLen = uiACharToString(cpBuffer, uiBufLen, acpPhrase, uiPhraseLen);
					uiStrBufCat(vpPrtBuf, cpBuffer);
				} else{
					APG_RULE* spRule= spParserCtx->spRules + spRecord->uiId;
					sprintf(&caScratchBuf[0], "%s%s:%lu:%lu:", cpBuffer, spRule->cpRuleName,
							(printf_uint)spRecord->uiPhraseOffset, (printf_uint)spRecord->uiPhraseLength);
					uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
					uiACharToString(cpBuffer, uiBufLen, acpPhrase, uiPhraseLen);
					uiStrBufCat(vpPrtBuf, cpBuffer);
				}
				fprintf(spOut, "%s", cpStrBufString(vpPrtBuf));
				if(uiStrBufIsTruncated(vpPrtBuf)){fprintf(spOut, "...");}
				fprintf(spOut, "\n");
				uiTreeDepth++;
			} else if(spRecord->uiState == POST_AST){
				cpState = (spRecord->uiPhraseLength) ? "M": "E";
				sprintf(&caScratchBuf[0], "%5lu:%5lu:%3lu:%s:",
						(printf_uint)spRecord->uiThisRecord, (printf_uint)spRecord->uiThatRecord, (printf_uint)uiTreeDepth, cpState);
				uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
				acpPhrase = spParserCtx->acpInputString + spRecord->uiPhraseOffset;
				uiPhraseLen = spRecord->uiPhraseLength;
				uiTreeDepth--;
				uiIndent(uiTreeDepth, cpBuffer, uiBufLen);
				if(spRecord->uiId >= spParserCtx->uiRuleCount){
					APG_UDT* spUdt = spParserCtx->spUdts + spRecord->uiId - spParserCtx->uiRuleCount;
					sprintf(&caScratchBuf[0], "%s%s:%lu:%lu:", cpBuffer, spUdt->cpUdtName,
							(printf_uint)spRecord->uiPhraseOffset, (printf_uint)spRecord->uiPhraseLength);
					uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
					uiACharToString(cpBuffer, uiBufLen, acpPhrase, uiPhraseLen);
					uiStrBufCat(vpPrtBuf, cpBuffer);
				} else{
					APG_RULE* spRule= spParserCtx->spRules + spRecord->uiId;
					sprintf(&caScratchBuf[0], "%s%s:%lu:%lu:", cpBuffer, spRule->cpRuleName,
							(printf_uint)spRecord->uiPhraseOffset, (printf_uint)spRecord->uiPhraseLength);
					uiStrBufCat(vpPrtBuf, &caScratchBuf[0]);
					uiACharToString(cpBuffer, uiBufLen, acpPhrase, uiPhraseLen);
					uiStrBufCat(vpPrtBuf, cpBuffer);
				}
				fprintf(spOut, "%s", cpStrBufString(vpPrtBuf));
				if(uiStrBufIsTruncated(vpPrtBuf)){fprintf(spOut, "...");}
				fprintf(spOut, "\n");
			}
		}
	}
}

/** Displays size, in bytes, for each of the four basic C unsigned types (char, short, int, long) as well as for apg_uint and apg_achar.

Useful to check the type sizes for a specific OS and to verify the APG type sizes for apg_uint and apg_achar.
@param spOut the FILE to write the display to. If NULL, uses stdout.
*/
void vDisplayTypeSizes(FILE* spOut){
	if(spOut == NULL){spOut = stdout;}
	fprintf(spOut, "     unsigned char: %lu\n", (printf_uint)sizeof(unsigned char));
	fprintf(spOut, "unsigned short int: %lu\n", (printf_uint)sizeof(unsigned short));
	fprintf(spOut, "      unsigned int: %lu\n", (printf_uint)sizeof(unsigned int));
	fprintf(spOut, " unsigned long int: %lu\n", (printf_uint)sizeof(unsigned long int));
	fprintf(spOut, "         apg_achar: %lu\n", (printf_uint)sizeof(apg_achar));
	fprintf(spOut, "          apg_uint: %lu\n", (printf_uint)sizeof(apg_uint));
}

static char* g_cpDisplayStatsHdrFmt = "%5s %9s %9s %9s %9s";
/** Displays statistics for all node types.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param spStats pointer to the statistics data return from uiParserStatsGet().
@see uiParserStatsEnable()
@see uiParserStatsGet()
*/
void vDisplayOperatorStats(FILE* spOut, APG_PARSER_STATS* spStats){
	if(spOut == NULL){spOut = stdout;}
	if(!spStats){fprintf(spOut, "<no statistics>\n");}
	else{
		fprintf(spOut, g_cpDisplayStatsHdrFmt, "", "NOMATCH", "EMPTY", "MATCH", "TOTAL");
	    fprintf(spOut, "%s", " : OPERATOR STATISTICS");
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "RNM", &spStats->sRnm);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "UDT", &spStats->sUdt);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "ALT", &spStats->sAlt);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "CAT", &spStats->sCat);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "REP", &spStats->sRep);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "AND", &spStats->sAnd);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "NOT", &spStats->sNot);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "TRG", &spStats->sTrg);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "TBS", &spStats->sTbs);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "TLS", &spStats->sTls);
		fprintf(spOut, "\n");
		vPrintOperatorLine(spOut, "TOTAL", &spStats->sTotal);
		fprintf(spOut, "\n");
	}
}
/** Displays statistics for the rule and UDT nodes.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param spStats pointer to the statistics data return from uiParserStatsGet().
@param cpType indicates the type of rule/UDT listing

- cpType = "alpha" - list the rule/UDT nodes alphabetically (rule/UDT nodes with 0 hits are omitted)
- cpType = "count" - list the rule/UDT nodes descending numerically on hit count (rule/UDT nodes with 0 hits are omitted)
- cpType = NULL or other, list the rule/UDT nodes by grammar index
@see uiParserStatsEnable()
@see uiParserStatsGet()
*/
void vDisplayRuleStats(FILE* spOut, APG_PARSER_STATS* spStats, const char* cpType){
	apg_uint uiType = 0; // 0=default, 1=alpha, 2=count
	if(spOut == NULL){spOut = stdout;}
	if(!spStats){fprintf(spOut, "<no statistics>\n");}
	else{
		if(cpType && (*cpType == 'a' || *cpType == 'A')){uiType = 1;}
		if(cpType && (*cpType == 'c' || *cpType == 'C')){uiType = 2;}
	    fprintf(spOut, "\n");
	    fprintf(spOut, g_cpDisplayStatsHdrFmt, "", "NOMATCH", "EMPTY", "MATCH", "TOTAL");
	    fprintf(spOut, "%s", " : RULE/UDT STATISTICS");
	    switch(uiType){
	    case 1: // cpType = "alpha", list rules/UDTs alphabetically
		    fprintf(spOut, "%s", " (alphabetically sorted on rule/UDT names)");
		    fprintf(spOut, "\n");
		    vPrintOperatorList(spOut, spStats->spNameStatsAlpha, spStats->uiNameCount, 1);
	    	break;
	    case 2: // cpType = "alpha", list rules/UDTs descending on count
		    fprintf(spOut, "%s", " (numerically sorted on total node visits)");
		    fprintf(spOut, "\n");
		    vPrintOperatorList(spOut, spStats->spNameStatsCount, spStats->uiNameCount, 2);
	    	break;
	    default: // default = list by grammar index
		    fprintf(spOut, "%s", " (not sorted, listed by grammar index, rules followed by UDTs)");
		    fprintf(spOut, "\n");
		    vPrintOperatorList(spOut, spStats->spNameStats, spStats->uiNameCount, 0);
	    	break;
	    }
	}
}

/** Displays the Parser's state directly from the Parser.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param vpParserCtx context handle of the Parser, previously returned from vpParserCtor().
@see vpParserCtor()
*/
void vDisplayParserState(FILE* spOut, void* vpParserCtx){
	APG_PARSER_CTX* spParserCtx = (APG_PARSER_CTX*)vpParserCtx;
	if(spOut == NULL){spOut = stdout;}
	if(spParserCtx && (void*)spParserCtx == spParserCtx->vpValidate){
		fprintf(spOut, "%5s = success\n", cpBoolean2String(spParserCtx->sState.uiSuccess));
		fprintf(spOut, "%5s = state\n", cpState2String(spParserCtx->sState.uiState));
		fprintf(spOut, "%5lu = phrase length\n", (printf_uint)spParserCtx->sState.uiPhraseLength);
		fprintf(spOut, "%5lu = string length\n", (printf_uint)spParserCtx->sState.uiStringLength);
	} else{
		fprintf(spOut, "vDisplayParserState: invalid input\n");
	}
}

/** Displays the Parser state.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param spState state data, previously returned from uiParserState().
@see uiParserState()
*/
void vDisplayState(FILE* spOut, APG_PARSER_STATE* spState){
	if(spState){
		fprintf(spOut, "%5s = success\n", cpBoolean2String(spState->uiSuccess));
		fprintf(spOut, "%5s = state\n", cpState2String(spState->uiState));
		fprintf(spOut, "%5lu = phrase length\n", (printf_uint)spState->uiPhraseLength);
		fprintf(spOut, "%5lu = string length\n", (printf_uint)spState->uiStringLength);
	} else{
		fprintf(spOut, "vDisplayParserState: invalid input\n");
	}
}

/** Displays information about a grammar.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param vpHdr pointer to the grammar-generated data.

- For a C-language parser this will be vpParserInit_ProjectName
- For a C++ parser this will be the class data member m_vpParserInit.
*/
void vDisplayGrammarInfo(FILE* spOut, void* vpHdr){
	G_HDR* spHdr = (G_HDR*)vpHdr;
	char caVersion[64];
	apg_uint i;
	unsigned long int* uipOffset;
	char* cpFmtVersion = "%15s = %s\n";
	char* cpFmtData = "%15lu = %s\n";
	if(spOut == NULL){spOut = stdout;}
	if(spHdr){
		uipOffset =(unsigned long int*)spHdr +  spHdr->uiVersionOffset;
		for(i = 0; i < spHdr->uiVersionLen; i++){
			caVersion[i] = (char)uipOffset[i];
		}
		caVersion[i] = 0;
		fprintf(spOut, cpFmtVersion, &caVersion[0], "Version");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiSizeInBytes, "Grammar size in bytes");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiACharMin, "Grammar alphabet character min");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiACharMax, "Grammar alphabet character max");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiUintMax, "Grammar integer max");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiMinSizeofACharMax, "min sizeof(apg_achar)");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiMinSizeofUintMax, "min sizeof(apg_uint)");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiRulesLen, "Number of rules");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiUdtsLen, "Number of UDTs");
		fprintf(spOut, cpFmtData, (printf_uint)spHdr->uiOpcodesLen, "Number of opcodes");
	}
}

///////////////////////////////////////////////////////////////////////////////
// OTHER HELPERS
///////////////////////////////////////////////////////////////////////////////
/** Displays the APG license notice.
@param spFile the FILE to write the display to. If NULL, uses stdout.
*/
void vLicenseNotice(FILE* spFile)
{
  if(!spFile){spFile = stdout;}
  fprintf(spFile, "  APG Version %s\n", cpApgVersion());
//  fprintf(spFile, "  %s\n", cpApgDescription());
  fprintf(spFile, "  %s\n", cpApgCopyright());
  fprintf(spFile, "\n");
  fprintf(spFile, "  author:  %s\n", cpApgAuthor());
  fprintf(spFile, "  email:   %s\n", cpApgEmail());
  fprintf(spFile, "  website: %s\n", cpApgWebsite());
  fprintf(spFile, "\n");
  fprintf(spFile, "%s", cpApgGPLNotice());
}

/** Displays the Abstract Syntax Tree (AST) in XML format to the specified file.

The AST has one node for each rule/UDT name.
For example the rule named "Hello" with grammar index "1" would have the structure:
<pre>
\<node name="Hello" id="1"\>
 \<phrase offset="0" length="5"\>Hello\</phrase\>
\</node\>\<!-- name="Hello" id="1" --\>
</pre>
That is an open \<node\> tag, defining the AST node, a \<phrase\> tag defining the matched phrase
and a close \</node\> tag. \<node\> tags will be nested for recursion.

The \<phrase\> tag has attributes "offset=" giving the offset into the input string to the
first character of the phrase, "length=" giving the phrase length and the tag text is the matched phrase.

There will always be a \<root\> tag to act as the mandatory parent of all \<node\> tags.
The \<root\> tag will have attributes "lines=", giving the total number of lines in the AST
and "nodes=" giving the number of nodes in the AST.
@param spOut the FILE to write the display to. If NULL, uses stdout.
@param vpParserCtx context handle of the Parser, previously returned from vpParserCtor().
@see vpParserCtor()
@return true if successful, false otherwise
*/
apg_uint uiAstToXml(FILE* spOut, void* vpParserCtx){
	apg_uint uiRet = APG_TRUE;
	char* cpError = NULL;
	char* cpName = NULL;
	APG_PARSER_CTX* spParserCtx = (APG_PARSER_CTX*)vpParserCtx;
	APG_AST_CTX* spAstCtx;
	APG_AST_RECORD* spRecord;
	APG_AST_RECORD* spRecordEnd;
	apg_uint uiTreeDepth;
	APG_RULE* spRules;
	APG_UDT* spUdts;
	const apg_achar* acpInputString;
	char* cpDeclaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

	while(APG_TRUE){
		if(spOut == NULL){spOut = stdout;}
		if(!(spParserCtx && spParserCtx->vpValidate == vpParserCtx)){
			cpError = "input error; NULL or invalid parser context";
			break;
		}
		spRules = spParserCtx->spRules;
		spUdts = spParserCtx->spUdts;
		acpInputString = spParserCtx->acpInputString;
		spAstCtx = (APG_AST_CTX*)spParserCtx->vpAstCtx;
		if(!spAstCtx){
			cpError = "no AST; must call vParserSemanticInit() prior to parsing";
			break;
		}
		if(!spAstCtx->uiRecordCount){
			cpError = "no AST records have been generated";
			break;
		}
		spRecord = spAstCtx->spRecords;
		spRecordEnd = spAstCtx->spRecords + spAstCtx->uiRecordCount;

		// print the open ROOT record
		fprintf(spOut, "%s\n", cpDeclaration);
		uiTreeDepth = 0;
		vRootOpen(spOut, (3 * (spAstCtx->uiRecordCount/2 + 1) + 1), spAstCtx->uiRecordCount/2);
		uiTreeDepth++;
		vIndentPrint(spOut, uiTreeDepth);
		vPhrase(spOut, 0, spParserCtx->uiInputStringLen, acpInputString);
		for(; spRecord < spRecordEnd; spRecord++){
			if(spRecord->uiId < spAstCtx->uiRuleCount){cpName = spRules[spRecord->uiId].cpRuleName;}
			else if(spRecord->uiId < spAstCtx->uiNodeCount){cpName = spUdts[spRecord->uiId - spAstCtx->uiRuleCount].cpUdtName;}
			if(spRecord->uiState == PRE_AST){
				vIndentPrint(spOut, uiTreeDepth);
				vNodeOpen(spOut, spRecord->uiId, cpName);
				uiTreeDepth++;
				vIndentPrint(spOut, uiTreeDepth);
				vPhrase(spOut, spRecord->uiPhraseOffset, spRecord->uiPhraseLength, (acpInputString + spRecord->uiPhraseOffset));
			} else if(spRecord->uiState == POST_AST){
				uiTreeDepth--;
				vIndentPrint(spOut, uiTreeDepth);
				vNodeClose(spOut, spRecord->uiId, cpName);
			}
		}

		uiTreeDepth--;
		vRootClose(spOut);

		break;
	}
	if(cpError){
		fprintf(spOut, "\n!!! AST to XML conversion error: %s !!!\n", cpError);
		uiRet = APG_FALSE;
	}
	return uiRet;
}

/** An alert handler which prints the location where the alert was generated and exits the application.

Note: this is the normal way that APG reports terminal errors.
It is assumed that the user is a sufficiently able programmer to look at the code location
and see what the problem is.
@param uiLine the line number where the alert was generated
@param cpFile the name of the file where the alert was generated.
*/
void vTerminalAlert(unsigned int uiLine, const char* cpFile){
	if(!cpFile){cpFile = "<none>";}
	printf("vTerminalAlert: file: %s: line: %u\n", cpFile, uiLine);
	printf("vTerminalAlert: exit(EXIT_FAILURE);\n");
	exit(EXIT_FAILURE);
}

/** An alert handler which prints the location where the alert was generated, a user-defined message and exits the application.
@param uiLine the line number where the alert was generated
@param cpFile the name of the file where the alert was generated.
@param cpMsg the message that was generated by the function that issued the alert, presumably giving some indication of what the problem was.
*/
void vTerminalAlertMsg(unsigned int uiLine, const char* cpFile, const char* cpMsg){
	if(!cpFile){cpFile = "<none>";}
	if(!cpMsg){cpMsg = "<none>";}
	printf("vTerminalAlertMsg: file: %s: line: %u: %s\n", cpFile, uiLine, cpMsg);
	printf("vTerminalAlertMsg: exit(EXIT_FAILURE);\n");
	exit(EXIT_FAILURE);
}

/** Translates the Parser state into a readable ASCII string.
@param uiState the Parse state.
@return pointer to the string:
<pre>
"PRE_PARSE"
"EMPTY"
"MATCH"
"NOMATCH"
"PRE_AST"
"POST_AST"
"UNKNOWN" - if uiState is not a valid state value.
</pre>
*/
const char* cpState2String(apg_uint uiState){
	char* cpRet = "UNKNOWN";
	if(uiState == MATCH){cpRet = "MATCH";}
	else if(uiState == NOMATCH){cpRet = "NOMATCH";}
	else if(uiState == EMPTY){cpRet = "EMPTY";}
	else if(uiState == PRE_PARSE){cpRet = "PRE_PARSE";}
	else if(uiState == PRE_AST){cpRet = "PRE_AST";}
	else if(uiState == POST_AST){cpRet = "POST_AST";}
	return cpRet;
}

/** Translate a true/false value into a readable ASCII string.
@param uiBool the true/false value: 1 (eg. APG_TRUE) is interpreted as true, all other values as false.
@return pointer to the string "TRUE" for true, "FALSE" for false.
*/
const char* cpBoolean2String(apg_uint uiBool){
	return uiBool ? "TRUE" : "FALSE";
}

///////////////////////////////////////////////////////////////////////////////
// STATIC HELPER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
static apg_uint uiIndent(apg_uint uiIndent, char* cpBuffer, apg_uint uiBufferLen){
	apg_uint i, uiLen = 0;
	if(cpBuffer && uiBufferLen){
		uiLen = min(uiIndent, uiBufferLen);
		cpBuffer[0] = 0;
		for(i = 0; i < uiLen; i++){
			strcat(cpBuffer, " ");
		}
	}
	return uiLen;
}

static void vPrintOperatorList(FILE* spOut, APG_NAME_STAT* spNameStats, apg_uint uiCount, apg_uint uiType){
	apg_uint uiIndex;
	APG_STAT* spStat;
    for(uiIndex = 0; uiIndex < uiCount; uiIndex++){
    	spStat = &spNameStats[uiIndex].sStat;
    	if(uiType == 0){
		    vPrintOperatorLine(spOut, "", spStat);
		    fprintf(spOut, " : %s", spNameStats[uiIndex].cpName);
		    fprintf(spOut, "\n");
    	} else{
			if(spStat->uiTotal > 0){
				vPrintOperatorLine(spOut, "", spStat);
				fprintf(spOut, " : %s", spNameStats[uiIndex].cpName);
				fprintf(spOut, "\n");
			}
    	}
    }
}
static void vPrintOperatorLine(FILE* spOut, char* cpOp, APG_STAT* spNode)
{
  if(cpOp){
	  fprintf(spOut, "%5s %9lu %9lu %9lu %9lu",
	    cpOp,
	    (printf_uint)spNode->uiNoMatch,
	    (printf_uint)spNode->uiEmpty,
	    (printf_uint)spNode->uiMatch,
	    (printf_uint)spNode->uiTotal);
  } else{
	  fprintf(spOut, "vPrintOperatorLine: cpOp may not be NULL: line: %u: file: %s\n", __LINE__, __FILE__);
  }
}

//static int iCompCount(const void* vpLeft, const void* vpRight)
//{
//  APG_STATS_SORT* spLeft;
//  APG_STATS_SORT* spRight;
//
//  // sort descending
//  spLeft = (APG_STATS_SORT*)vpLeft;
//  spRight = (APG_STATS_SORT*)vpRight;
//  if(spLeft->spStat->uiTotal < spRight->spStat->uiTotal){return +1;}
//  if(spLeft->spStat->uiTotal > spRight->spStat->uiTotal){return -1;}
//  return 0;
//}
//
//static int iCompAlpha(const void* vpLeft, const void* vpRight)
//{
//	  APG_STATS_SORT* spLeft = (APG_STATS_SORT*)vpLeft;
//	  APG_STATS_SORT* spRight = (APG_STATS_SORT*)vpRight;
//
//	// sort descending
////	return apg_stricmp(spLeft->cpName, spRight->cpName);
//	return strcmp(spLeft->cpName, spRight->cpName);
//}

static void vDisplayOp(APG_PARSER_CTX*	spCtx, APG_OPCODE* spOp, apg_uint uiOpIndex){
	apg_uint i;
	printf("  %lu: ", (printf_uint)uiOpIndex);
	if(spOp->pfnOp == uiRNM){
		APG_RULE* spRule = spOp->sUnion.sRnm.spRule;
		printf("RNM(%s): index: %lu: opcodes: %lu\n",
				spRule->cpRuleName, (printf_uint)spRule->uiRuleIndex, (printf_uint)spRule->uiOpcodeCount);
	} else if(spOp->pfnOp == uiUDT){
		APG_UDT* spUdt = spOp->sUnion.sUdt.spUdt;
		printf("UDT(%s): index: %lu\n", spUdt->cpUdtName, (printf_uint)spUdt->uiUdtIndex);
	} else if(spOp->pfnOp == uiREP){
		if(spOp->sUnion.sRep.uiMax == APG_UNDEFINED){
			printf("REP: min: %lu: max: inf\n", (printf_uint)spOp->sUnion.sRep.uiMin);
		} else{
			printf("REP: min: %lu: max: %lu\n", (printf_uint)spOp->sUnion.sRep.uiMin, (printf_uint)spOp->sUnion.sRep.uiMax);
		}
	} else if(spOp->pfnOp == uiALT){
		printf("ALT: count: %lu: ", (printf_uint)spOp->sUnion.sAlt.uiChildCount);
		for(i = 0; i < spOp->sUnion.sAlt.uiChildCount; i++){
			printf("%lu: ", (printf_uint)spOp->sUnion.sAlt.uipChildList[i]);
		}
		printf("\n");
	} else if(spOp->pfnOp == uiCAT){
		printf("CAT: count: %lu: ", (printf_uint)spOp->sUnion.sCat.uiChildCount);
		for(i = 0; i < spOp->sUnion.sCat.uiChildCount; i++){
			printf("%lu: ", (printf_uint)spOp->sUnion.sCat.uipChildList[i]);
		}
		printf("\n");
	} else if(spOp->pfnOp == uiAND){
		printf("AND\n");
	} else if(spOp->pfnOp == uiNOT){
		printf("NOT\n");
	} else if(spOp->pfnOp == uiTRG){
		printf("TRG: min: %lu: max: %lu\n",
				(printf_uint)spOp->sUnion.sTrg.acMin, (printf_uint)spOp->sUnion.sTrg.acMax);
	} else if(spOp->pfnOp == uiTBS){
		printf("TBS: len: %lu: ", (printf_uint)spOp->sUnion.sTbs.uiStrLen);
		for(i = 0; i < spOp->sUnion.sTbs.uiStrLen; i++){
			printf("0x%lX: ", (printf_uint)spOp->sUnion.sTbs.acpStrTbl[i]);
		}
	} else if(spOp->pfnOp == uiTLS){
		printf("TBS: len: %lu: ", (printf_uint)spOp->sUnion.sTls.uiStrLen);
		for(i = 0; i < spOp->sUnion.sTls.uiStrLen; i++){
			printf("0x%lX: ", (printf_uint)spOp->sUnion.sTls.acpStrTbl[i]);
		}
		printf("\n");
	} else{printf("vDisplayOp: unknown operator type\n");}
}

//static unsigned long int uiMinIntSize(unsigned long int uiSize){
//	unsigned long int uiRet = 0;
//	unsigned long int uiTest;
//	while(APG_TRUE){
//		uiTest = (unsigned char)-1;
//		if(uiTest >= uiSize){uiRet = sizeof(unsigned char); break;}
//		uiTest = (unsigned short int)-1;
//		if(uiTest >= uiSize){uiRet = sizeof(unsigned short int); break;}
//		uiTest = (unsigned int)-1;
//		if(uiTest >= uiSize){uiRet = sizeof(unsigned int); break;}
//		uiTest = (printf_uint)-1;
//		if(uiTest >= uiSize){uiRet = sizeof(printf_uint); break;}
//		break;
//	}
//	return uiRet;
//}

static char* g_cpBeg1 = "<";
static char* g_cpBeg2 = "</";
static char* g_cpEnd1 = ">";
static char* g_cpRootName = "root";
static void vIndentPrint(FILE* spOut, apg_uint uiIndent){
	while(uiIndent--){fprintf(spOut, " ");}
}
static void vRootOpen(FILE* spOut, apg_uint uiLines, apg_uint uiNodes){
	fprintf(spOut, "%s%s lines=\"%lu\" nodes=\"%lu\"%s\n",
			g_cpBeg1, g_cpRootName, (printf_uint)uiLines, (printf_uint)uiNodes, g_cpEnd1);
}
static void vRootClose(FILE* spOut){
	fprintf(spOut, "%s%s%s\n", g_cpBeg2, g_cpRootName, g_cpEnd1);
}
static void vNodeOpen(FILE* spOut, apg_uint uiId, char* cpName){
	fprintf(spOut, "%snode name=\"%s\" id=\"%lu\"%s\n",
			g_cpBeg1, cpName, (printf_uint)uiId, g_cpEnd1);
}
static void vNodeClose(FILE* spOut, apg_uint uiId, char* cpName){
	fprintf(spOut, "%snode%s<!-- name=\"%s\" id=\"%lu\" -->\n", g_cpBeg2, g_cpEnd1, cpName, (printf_uint)uiId);
}
static void vPhraseText(FILE* spOut, const apg_achar* acpPhrase, apg_uint uiLength){
	apg_uint i = 0;
	for(; i < uiLength; i++){
		apg_achar c = acpPhrase[i];
		if(c < (apg_achar)32 || c > (apg_achar)126){
			fprintf(spOut, "&#x%02lX;", (printf_uint)c);
		}
		else{
			switch(c){
			case '&':
				fprintf(spOut, "&amp;");
				break;
			case '<':
				fprintf(spOut, "&lt;");
				break;
			case '>':
				fprintf(spOut, "&gt;");
				break;
			case '"':
				fprintf(spOut, "&quot;");
				break;
			case '\'':
				fprintf(spOut, "&apos;");
				break;
			default:
				fprintf(spOut, "%c", (char)c);
				break;
			}
		}
	}
}
static void vPhrase(FILE* spOut, apg_uint uiOffset, apg_uint uiLength, const apg_achar* acpPhrase){
	fprintf(spOut, "%sphrase offset=\"%lu\" length=\"%lu\"%s",
			g_cpBeg1, (printf_uint)uiOffset, (printf_uint)uiLength, g_cpEnd1);
	vPhraseText(spOut, acpPhrase, uiLength);
	fprintf(spOut, "%sphrase%s\n", g_cpBeg2, g_cpEnd1);
}
static void vPrintHeader(FILE* spOut){
	fprintf(spOut, "%6s, %6s, %6s\n", "lineno", "offset", "length");
}
static void vPrintLine(FILE* spOut, char* cpLine, apg_uint uiLine, apg_uint uiOffset, apg_uint uiLineLen){
    fprintf(spOut, "%06lu, %06lu, %06lu: %s\n", (printf_uint)uiLine, (printf_uint)uiOffset, (printf_uint)uiLineLen, cpLine);

}
static char g_caTrans[17] = {'0','1', '2','3','4','5','6','7','8','9','A','B','C','D','E','F','X'};
static apg_uint uiAddNonAscii(char* cpAdd, char cChar){
	apg_uint uiRet = 0;
	char cHex;
	cpAdd[uiRet++] = '\\';
	cpAdd[uiRet++] = 'x';
	cHex = (cChar & 0xF0) >> 4;
	cpAdd[uiRet++] = g_caTrans[(unsigned int)cHex];
	cHex = cChar & 0x0F;
	cpAdd[uiRet++] = g_caTrans[(unsigned int)cHex];
	cpAdd[uiRet] = 0;
	return uiRet;
}
