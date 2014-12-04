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
#include "main.h"
/** \file Demo/main.c \brief Demonstrates the use of APG with three simple applications.*/
/** The main program. Runs three separate tests.

1. vDemoSetup(). Uses a simplified version of the SABNF grammer to demonstrate Parser basics. The test output is written to Setup.output.
2. vDemoCallbacks(). Uses a simplified version of the SABNF grammer to demonstrate the basics of writing and using callback functions. The test output is written to Callbacks.output.
3. vDemoUdts(). Uses a simple grammar which refers to all rules parsed by the Parser's UDT library. The test output is written to UdtLib.output.

The grammar files for these tests have been generated with the parser generator commands:
<pre>
apg /in:Callbacks.bnf /C:CallbacksGrammar /dwarnings /dtypes
apg /in:Setup.bnf /C:SetupGrammar /dwarnings /dtypes
apg /in:UdtLib.bnf /C:UdtLibGrammar /dwarnings /dtypes
</pre>
*/
int main() {
	apg_uint uiTestSetup = APG_TRUE;
	apg_uint uiTestUdts = APG_TRUE;
	apg_uint uiTestCallbacks = APG_TRUE;

	if(uiTestSetup){vDemoSetup();}
	if(uiTestUdts){vDemoUdts();}
	if(uiTestCallbacks){vDemoCallbacks();}

	return EXIT_SUCCESS;
}
