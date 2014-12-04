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
/** \file WideCharacters/Callbacks.c \brief All of the user-written rule callback functions.
*/

static apg_uint examples(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == PRE_AST){
		  spCallbackCtx->spFile = fopen(spCallbackCtx->cpFileName, "w");
		  MASSERT(spCallbackCtx->spFile, "examples: can't open output file name");
		  spCallbackCtx->uiExampleNo = 0;
		  fprintf(spCallbackCtx->spFile, "<body>");
		  fprintf(spCallbackCtx->spFile, "<h1>APG Version 6.3</h1>");
		  fprintf(spCallbackCtx->spFile, "Copyright &copy; 2005 - 2012 Lowell D. Thomas<br>");
		  fprintf(spCallbackCtx->spFile, "lowell@coasttocoastresearch.com");
		  fprintf(spCallbackCtx->spFile, "<h2>Wide Characters Example</h2>");
		  fprintf(spCallbackCtx->spFile, "<p>To view this example correctly, your browser should ");
		  fprintf(spCallbackCtx->spFile, "support the UNICODE code charts for Cherokee, Greek and Cyrillic.</br>");
		  fprintf(spCallbackCtx->spFile, "See <a href=\"http://unicode.org/versions/latest/\">http://unicode.org/versions/latest/</a> and");
		  fprintf(spCallbackCtx->spFile, "See <a href=\"http://unicode.org/charts/\">http://unicode.org/charts/</a>.</p>");
	  } else{
		  fprintf(spCallbackCtx->spFile, "</body>\n");
		  spCallbackCtx->spFile = fopen(spCallbackCtx->cpFileName, "w");
		  spCallbackCtx->spFile = NULL;
	  }
	  return APG_UNDEFINED;
}

static apg_uint end(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  spCallbackCtx->uiExampleNo++;
	  }
	  return APG_UNDEFINED;
}

static apg_uint er_ex(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == PRE_AST){
		  fprintf(spCallbackCtx->spFile, "error: unknown language: ");
	  } else{
		  fprintf(spCallbackCtx->spFile, "</br>\n");
		  fprintf(spCallbackCtx->spFile, "\n");
	  }
	  return APG_UNDEFINED;
}

static apg_uint er_char(APG_CBDATA* spData){
	  const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  apg_achar acChar = acpString[0];
		  if(acChar >= (apg_achar)32 && acChar <= (apg_achar)126){
			  fprintf(spCallbackCtx->spFile, "%c", (char)acChar);
		  }
		  fprintf(spCallbackCtx->spFile, "&#x%x;", acChar);
	  }
	  return APG_UNDEFINED;
}

static apg_uint cher_ex(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == PRE_AST){
		  fprintf(spCallbackCtx->spFile, "Cherokee: ");
	  } else{
		  fprintf(spCallbackCtx->spFile, "</br>\n");
		  fprintf(spCallbackCtx->spFile, "\n");
	  }
	  return APG_UNDEFINED;
}

static apg_uint cher_char(APG_CBDATA* spData){
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  fprintf(spCallbackCtx->spFile, "&#x%x;", acpString[0]);
	  }
	  return APG_UNDEFINED;
}

static apg_uint cyr_ex(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == PRE_AST){
		  fprintf(spCallbackCtx->spFile, "Cyrillic: ");
	  } else{
		  fprintf(spCallbackCtx->spFile, "</br>\n");
		  fprintf(spCallbackCtx->spFile, "\n");
	  }
	  return APG_UNDEFINED;
}

static apg_uint cyr_char(APG_CBDATA* spData){
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  fprintf(spCallbackCtx->spFile, "&#x%x;", acpString[0]);
	  }
	  return APG_UNDEFINED;
}

static apg_uint gr_ex(APG_CBDATA* spData){
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == PRE_AST){
		  fprintf(spCallbackCtx->spFile, "Greek: ");
	  } else{
		  fprintf(spCallbackCtx->spFile, "</br>\n");
		  fprintf(spCallbackCtx->spFile, "\n");
	  }
	  return APG_UNDEFINED;
}

static apg_uint gr_char(APG_CBDATA* spData){
	const apg_achar* acpString = spData->acpSrc + spData->uiPhraseOffset;
	  CALLBACK_CTX* spCallbackCtx = (CALLBACK_CTX*)spData->vpUserData;
	  if(spData->uiState == POST_AST){
		  fprintf(spCallbackCtx->spFile, "&#x%x;", acpString[0]);
	  }
	  return APG_UNDEFINED;
}

/** \cond NOSHOW */
void vSemanticInit(APG_CALLBACK* spSemantic){
	APG_CALLBACK* spBeg = spSemantic;
	APG_CALLBACK* spEnd = spSemantic + RULE_COUNT_WIDEGRAMMAR;
	for(; spBeg < spEnd; spBeg++){*spBeg = NULL;}
	spSemantic[RULE_WIDEGRAMMAR_UTF32_EXAMPLES] = examples;
	spSemantic[RULE_WIDEGRAMMAR_CHEROKEE_CHAR] = cher_char;
	spSemantic[RULE_WIDEGRAMMAR_CHEROKEE_EXAMPLE] = cher_ex;
	spSemantic[RULE_WIDEGRAMMAR_CYRILLIC_CHAR] = cyr_char;
	spSemantic[RULE_WIDEGRAMMAR_CYRILLIC_EXAMPLE] = cyr_ex;
	spSemantic[RULE_WIDEGRAMMAR_END] = end;
	spSemantic[RULE_WIDEGRAMMAR_ERROR_EXAMPLE] = er_ex;
	spSemantic[RULE_WIDEGRAMMAR_ERROR_CHAR] = er_char;
	spSemantic[RULE_WIDEGRAMMAR_GREEK_CHAR] = gr_char;
	spSemantic[RULE_WIDEGRAMMAR_GREEK_EXAMPLE] = gr_ex;
}
/** \endcond */
