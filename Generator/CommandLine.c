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
/******************************************************************************
   purpose: Reads and interprets the command line parameters

*********************************************************************/
#include "Generator.h"
#include <malloc.h>

static char* s_cpHelp1 = "?";
static char* s_cpHelp2 = "/?";
static char* s_cpHelp3 = "help";
static char* s_cpHelp4 = "/help";
static char* s_cpHelp5 = "-help";
static char* s_cpHelp6 = "--help";
static char* s_cpVersion1 = "/v";
static char* s_cpVersion2 = "-v";
static char* s_cpVersion3 = "--version";
static char* s_cpIn = "/in:";
static char* s_cpOut = "/out:";
static char* s_cpLog = "/log:";
static char* s_cpC = "/C:";
static char* s_cpCpp = "/C++:";
static char* s_cpVerbose = "/dv";
static char* s_cpConfig = "/dconfig";
static char* s_cpState = "/dstate";
static char* s_cpGrammar = "/dgrammar";
static char* s_cpWarnings = "/dwarnings";
static char* s_cpGrammarMetrics = "/dgrammar-metrics";
static char* s_cpOpcodes = "/dopcodes";
static char* s_cpAttributes = "/dattributes";
static char* s_cpRules = "/drules";
static char* s_cpAst = "/dast";
static char* s_cpTypes = "/dtypes";

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Examines a command line option to see if it 1) matches
//              the specified option and 2) if it is followed by a file name.
//
// FUNCTION: static uiIsFileName
//
//      ARG: 1) char* cpArg
//              : the command line option to test
//
//      ARG: 2) char* cpOption
//              : the option to look for
//
//      ARG: 3) apg_uint* uipError
//              : returns true on success
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiIsFileName(char* cpArg, char* cpOption, apg_uint* uipError)
{
  apg_uint uiReturn = APG_TRUE;
  apg_uint uiLen = strlen(cpOption);

  // single-point-of-exit loop
  while(APG_TRUE)
  {
    if(0 != memcmp((void*)cpArg, cpOption, uiLen))
    {
      // input option not found
      uiReturn = APG_FALSE;
      break;
    }

    if(0 == cpArg[uiLen])
    {
      // format error
      printf("option error - \"%s\" file name is missing\n", cpArg);
      *uipError = APG_TRUE;
      break;
    }

    // found good file name
    break;
  } // end of single-point-of-exit loop

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Checks a command line option to see if it is one of the
//              help option forms.
//
// FUNCTION: static uiIsHelp
//
//      ARG: 1) char* cpArg
//              : pointer to the command line option
//
//      ARG: 2) CM_CONFIG* spConfig
//              : pointer to the command line configuration struct
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiIsHelp(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = APG_TRUE;

  // single-point-of-exit loop
  while(APG_TRUE)
  {
    if(0 == memcmp((void*)cpArg, s_cpHelp1, strlen(s_cpHelp1)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpHelp2, strlen(s_cpHelp2)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpHelp3, strlen(s_cpHelp3)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpHelp4, strlen(s_cpHelp4)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpHelp5, strlen(s_cpHelp5)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpHelp6, strlen(s_cpHelp6)))
    {
      spConfig->uiHelp = APG_TRUE;
      break;
    }

    uiReturn = APG_FALSE;
    break;
  } // end of single-point-of-exit loop

  return uiReturn;
}

static apg_uint uiIsVersion(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = APG_TRUE;

  // single-point-of-exit loop
  while(APG_TRUE)
  {
    if(0 == memcmp((void*)cpArg, s_cpVersion1, strlen(s_cpVersion1)))
    {
      spConfig->uiVersion = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpVersion2, strlen(s_cpVersion2)))
    {
      spConfig->uiVersion = APG_TRUE;
      break;
    }

    if(0 == memcmp((void*)cpArg, s_cpVersion3, strlen(s_cpVersion3)))
    {
      spConfig->uiVersion = APG_TRUE;
      break;
    }

    uiReturn = APG_FALSE;
    break;
  } // end of single-point-of-exit loop

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Checks a command line option for the /in option and
//              extracts the file name.
//
// FUNCTION: static uiIsIn
//
//      ARG: 1) char* cpArg
//              : pointer to the command line option
//
//      ARG: 2) CM_CONFIG* spConfig
//              : pointer to the command line configuration struct
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiGetName(char* cpDst, char* cpSrc){
	apg_uint uiRet = APG_FALSE;
	apg_uint uiSrcLen;
	while(APG_TRUE){
		if(cpSrc == NULL){break;}
		if(cpDst == NULL){break;}
		uiSrcLen = strlen(cpSrc);
		if(uiSrcLen == 0){break;}
		if(uiSrcLen >= CM_NAME_MAX){break;}
		if(cpSrc[0] == '"'){
			if(cpSrc[uiSrcLen - 1] != '"'){break;}
			cpSrc[uiSrcLen - 1] = 0;
			cpSrc++;
			uiSrcLen -= 2;
		}
		strcpy(cpDst, cpSrc);
		uiRet = APG_TRUE;
		break;
	}
	return uiRet;
}
static apg_uint uiIsIn(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = uiIsFileName(cpArg, s_cpIn, &spConfig->uiHelp);
  apg_uint uiLen = strlen(s_cpIn);

  if(uiReturn)
  {
    uiReturn = uiGetName(spConfig->caInput, &cpArg[uiLen]);
    spConfig->uiInput = uiReturn;
  }

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Checks a command line option for the /out option and
//              extracts the file name.
//
// FUNCTION: static uiIsOut
//
//      ARG: 1) char* cpArg
//              : pointer to the command line option
//
//      ARG: 2) CM_CONFIG* spConfig
//              : pointer to the command line configuration struct
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiIsOut(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = uiIsFileName(cpArg, s_cpOut, &spConfig->uiHelp);
  apg_uint uiLen = strlen(s_cpOut);

  if(uiReturn)
  {
    uiReturn = uiGetName(spConfig->caOutput, &cpArg[uiLen]);
    spConfig->uiOutput = uiReturn;
  }

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Checks a command line option for the /log option and
//              extracts the file name.
//
// FUNCTION: static uiIsLog
//
//      ARG: 1) char* cpArg
//              : pointer to the command line option
//
//      ARG: 2) CM_CONFIG* spConfig
//              : pointer to the command line configuration struct
//
//   RETURN: true on success
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiIsLog(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = uiIsFileName(cpArg, s_cpLog, &spConfig->uiHelp);
  apg_uint uiLen = strlen(s_cpLog);

  if(uiReturn)
  {
    uiReturn = uiGetName(spConfig->caLog, &cpArg[uiLen]);
    spConfig->uiLog = uiReturn;
  }

  return uiReturn;
}

static apg_uint uiIsC(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = uiIsFileName(cpArg, s_cpC, &spConfig->uiHelp);
  apg_uint uiLen = strlen(s_cpC);

  if(uiReturn)
  {
    uiReturn = uiGetName(spConfig->caC, &cpArg[uiLen]);
    spConfig->uiC = uiReturn;
  }

  return uiReturn;
}

static apg_uint uiIsCpp(char* cpArg, CM_CONFIG* spConfig)
{
  apg_uint uiReturn = uiIsFileName(cpArg, s_cpCpp, &spConfig->uiHelp);
  apg_uint uiLen = strlen(s_cpCpp);

  if(uiReturn)
  {
    uiReturn = uiGetName(spConfig->caCpp, &cpArg[uiLen]);
    spConfig->uiCpp = uiReturn;
  }

  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: Checks for a specific option and returns its true/false value
//
// FUNCTION: static uiIsOption
//
//      ARG: 1) char* cpArg
//              : pointer to the command line option
//
//      ARG: 2) char* cpOption
//              : pointer to the option to look for
//
//      ARG: 3) apg_uint* uipOption
//              : on return, true if the option was found, false otherwise
//
//   RETURN:
//
//////////////////////////////////////////////////////////////////////////
static apg_uint uiIsOption(char* cpArg, char* cpOption, apg_uint* uipOption)
{
  apg_uint uiReturn = APG_FALSE;
  apg_uint uiLen = strlen(cpOption);
  if(0 == memcmp((void*)cpArg, cpOption, uiLen))
  {
    if(cpArg[uiLen] == 0)
    {
      *uipOption = APG_TRUE;
      uiReturn = APG_TRUE;
    }
  }
  return uiReturn;
}

//////////////////////////////////////////////////////////////////////////
// DESCRIPTION: parse the command line
//
// FUNCTION: apg_uint uiCommandLine
//
//      ARG: 1) CM_CONFIG* spConfig
//              : pointer to the command line configuration struct
//
//      ARG: 2) int argc
//              : the number of command line arguments
//
//      ARG: 3) char** argv
//              : pointer to a list of pointers to the command line arguments
//
//   RETURN: true on success
//           prints a help screen to the console on error or detection
//           of a help option
//
//////////////////////////////////////////////////////////////////////////
char* cpBool(apg_uint uiBool){
	return uiBool ? "true": "false";
}
void vDisplayConfig(CM_CONFIG* spConfig){
	printf("%20s %s\n", "help", cpBool(spConfig->uiHelp));
	printf("%20s %s\n", s_cpVerbose, cpBool(spConfig->uiDisplayVerbose));
	printf("%20s %s\n", s_cpConfig, cpBool(spConfig->uiDisplayConfig));
	printf("%20s %s\n", s_cpGrammar, cpBool(spConfig->uiDisplayGrammar));
	printf("%20s %s\n", s_cpState, cpBool(spConfig->uiDisplayState));
	printf("%20s %s\n", s_cpWarnings, cpBool(spConfig->uiDisplayWarnings));
	printf("%20s %s\n", s_cpRules, cpBool(spConfig->uiDisplayRules));
	printf("%20s %s\n", s_cpAst, cpBool(spConfig->uiDisplayAst));
	printf("%20s %s\n", s_cpGrammarMetrics, cpBool(spConfig->uiDisplayGrammarMetrics));
	printf("%20s %s\n", s_cpAttributes, cpBool(spConfig->uiDisplayAttributes));
	printf("%20s %s\n", s_cpOpcodes, cpBool(spConfig->uiDisplayOpcodes));
	printf("%20s \"%s\"\n", s_cpIn, spConfig->caInput);
	printf("%20s \"%s\"\n", s_cpOut,  spConfig->caOutput);
	printf("%20s \"%s\"\n", s_cpLog, spConfig->caLog);
	printf("%20s \"%s\"\n", s_cpC, spConfig->caC);
	printf("%20s \"%s\"\n", s_cpCpp, spConfig->caCpp);
}
apg_uint uiCommandLine(CM_CONFIG* spConfig, int argc, char** argv)
{
  int i;
  char* cpArg;
  apg_uint uiReturn = APG_TRUE;

  // set defaults - start rule = 0, all display is off
  memset((void*)spConfig, 0, sizeof(*spConfig));

  for(i = 1; i < argc; ++i)
  {
    cpArg = argv[i];

    // help
    if(uiIsHelp(cpArg, spConfig)){continue;}
    if(uiIsVersion(cpArg, spConfig)){continue;}
    if(uiIsIn(cpArg, spConfig)){continue;}
    if(uiIsOut(cpArg, spConfig)){continue;}
    if(uiIsLog(cpArg, spConfig)){continue;}
    if(uiIsC(cpArg, spConfig)){continue;}
    if(uiIsCpp(cpArg, spConfig)){continue;}
    if(uiIsOption(cpArg, s_cpVerbose, &spConfig->uiDisplayVerbose)){continue;}
    if(uiIsOption(cpArg, s_cpConfig, &spConfig->uiDisplayConfig)){continue;}
    if(uiIsOption(cpArg, s_cpState, &spConfig->uiDisplayState)){continue;}
    if(uiIsOption(cpArg, s_cpGrammar, &spConfig->uiDisplayGrammar)){continue;}
    if(uiIsOption(cpArg, s_cpWarnings, &spConfig->uiDisplayWarnings)){continue;}
    if(uiIsOption(cpArg, s_cpGrammarMetrics, &spConfig->uiDisplayGrammarMetrics)){continue;}
    if(uiIsOption(cpArg, s_cpAttributes, &spConfig->uiDisplayAttributes)){continue;}
    if(uiIsOption(cpArg, s_cpOpcodes, &spConfig->uiDisplayOpcodes)){continue;}
    if(uiIsOption(cpArg, s_cpRules, &spConfig->uiDisplayRules)){continue;}
    if(uiIsOption(cpArg, s_cpAst, &spConfig->uiDisplayAst)){continue;}
    if(uiIsOption(cpArg, s_cpTypes, &spConfig->uiDisplayTypes)){continue;}

    // unknown option
    printf("option %d unrecognized: \"%s\"\n", i, cpArg);
    spConfig->uiHelp = APG_TRUE;
  }

  if(spConfig->uiDisplayVerbose)
  {
		// implies all other display options
		spConfig->uiDisplayConfig = APG_TRUE;
		spConfig->uiDisplayState = APG_TRUE;
		spConfig->uiDisplayGrammar = APG_TRUE;
		spConfig->uiDisplayWarnings = APG_TRUE;
		spConfig->uiDisplayGrammarMetrics = APG_TRUE;
		spConfig->uiDisplayAttributes = APG_TRUE;
		spConfig->uiDisplayRules = APG_TRUE;
		spConfig->uiDisplayTypes = APG_TRUE;
  }

  return uiReturn;
}

void vDisplayHelp(int argc, char** argv){
	int i;
    printf("\n");
    printf("COMMAND LINE OPTIONS FOUND\n");
    for(i = 0; i < argc; ++i)
    {
      printf("%s \n", argv[i]);
    }
    printf("\n");

    // display the help screen
    printf("APG(version %s)\n", cpApgVersion());
    printf("Usage: apg options\n");
    printf("options: one or more of the following:\n");
    printf("\n");
    printf("help options\n");
    printf("?                 - print this help screen\n");
    printf("help              - print this help screen\n");
    printf("/?                - print this help screen\n");
    printf("/help             - print this help screen\n");
    printf("-help             - print this help screen\n");
    printf("--help            - print this help screen\n");
    printf("\n");
    printf("version options\n");
    printf("--version         - print version\n");
    printf("-v                - print version\n");
    printf("/v                - print version\n");
    printf("\n");
    printf("name options\n");
    printf("/in:pathname      - pathname of input SABNF grammar (required)\n");
    printf("/out:path         - path for generated parser, including trailing delimiter (default = ./ or current working directory)\n");
    printf("/log:pathname     - log output to pathname (default is console)\n");
    printf("/C:name           - C-language parser project name (outputs files name.h & name.c)\n");
    printf("/C++:name         - C++ language parser project name (outputs files name.h & name.cpp)\n");
    printf("\n");
    printf("true/false options, all defaults are false\n");
    printf("/dv               - verbose, implies all display options except /dopcodes & /dast\n");
    printf("/dconfig          - display all of the configuration parameters\n");
    printf("/dgrammar         - display input grammar file with one-based line numbers\n");
    printf("/dwarnings        - display grammar syntax warnings\n");
    printf("/dgrammar-metrics - display grammar metrics\n");
    printf("/dattributes      - display attributes\n");
    printf("/drules           - display rules and udts\n");
    printf("/dast             - display AST records (caution: may generate many records)\n");
    printf("/dtypes           - display the integer type sizes\n");
    printf("/dopcodes         - display grammar opcodes in human-readable format (caution: may generate many opcodes)\n");

    printf("\n");
    printf("options are case sensitive and must appear exactly as indicated above\n");
    printf("paths, pathnames and names must be < 128 in length\n");
    printf("default values of all true/false options are false\n");
}
