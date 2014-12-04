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
#ifndef COMMANDLINE_H_INCLUDED
#define COMMANDLINE_H_INCLUDED

// configuration
#define CM_NAME_MAX 128
typedef struct
{
	// name parameters
	apg_uint uiInput;
	apg_uint uiOutput;
	apg_uint uiLog;
	char caInput[CM_NAME_MAX];
	char caOutput[CM_NAME_MAX];
	char caLog[CM_NAME_MAX];

	// language options
	apg_uint uiC;
	apg_uint uiCpp;
	char caC[CM_NAME_MAX];
	char caCpp[CM_NAME_MAX];

	// true/false parameters
	apg_uint uiVersion;
	apg_uint uiDisplayVerbose;
	apg_uint uiDisplayConfig;
	apg_uint uiDisplayState;
	apg_uint uiDisplayGrammar;
	apg_uint uiDisplayWarnings;
	apg_uint uiDisplayGrammarMetrics;
	apg_uint uiDisplayAttributes;
	apg_uint uiDisplayOpcodes;
	apg_uint uiDisplayRules;
	apg_uint uiDisplayAst;
	apg_uint uiDisplayTypes;

	// display help screen
	apg_uint uiHelp;
} CM_CONFIG;

apg_uint uiCommandLine(CM_CONFIG* spConfig, int argc, char** argv);
void vDisplayConfig(CM_CONFIG* spConfig);
void vDisplayHelp(int argc, char** argv);


#endif // COMMANDLINE_H_INCLUDED
