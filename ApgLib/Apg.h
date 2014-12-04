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
/** \mainpage APG - an ABNF Parser Generator

APG is organized into three separate directories plus an additional five directories
for the five examples of APG usage. The three APG directories are:
<ul>
<li>
<b>ApgLib</b> <br>This is the basic library. It has the API for the parser itself. It is designed
to <i>not</i> include any references to the C run-time libary I/O functions,
for reasons of economy.
Since the variable character width is a compile-time variable,
ApgLib is compiled separately with each application. No static library is built.
<br></li>
<li>

<b>ApgUtilities</b><br> As the name implies, is a library of utility functions.
These are not necessary for the parser itself, but provide a convenient set of
helper functions. These are mostly display functions, which need the C run-time I/O library,
but also has a few basic file handling functions and a timer component used in the timing tests.
<br></li>
<li>

<b>Generator</b> <br>This is APG, the parser generator. It reads an SABNF grammar and generates a parser in the
form of C or C++ source code.
</li>
</ul>
The five examples of APG usage are:

<ul>
<li>
<b>Demo</b> <br>This is a simple "Hello World" example of a parser. It demonstrates most of the basic
APG operations and gives examples of how to write and set up rule and UDT callback functions.
<br></li>
<li>

<b>CppDemo </b> <br> This gives a simple example of setting up a C++ parser.
<br></li>
<li>

<b>MEGACO</b>. <br>APG has proved a popular choice for parsing MEGACO messages
(<a href="http://www.ietf.org/rfc/rfc3525.txt?number=3525">RFC 3525</a>.)
This is an example of how to set up a C++ parser for this grammar.
<br></li>
<li>

<b>SIP</b> <br>This is an in-depth study of using UDTs to significantly speed up the parsing process
without altering the language of interest.
The SIP grammar (<a href="http://www.ietf.org/rfc/rfc3261.txt?number=3261">RFC 3261</a>) has been selected for this study because it is a
substantial (300+ rule names) and <a href="http://en.wikipedia.org/wiki/List_of_SIP_software">commercially significant</a> grammar.
<br></li>
<li>

<b>WideCharacters</b> <br>This is an example of using an alphabet character width greater than 8 bits.
This example parses UNICODE characters using their full 32-bit integer character codes (UTF-32).
</li>
</ul>

For more information about APG, Version 6.3 see <a href="doc6.3.html">doc6.3</a>.
*/

/** \file Apg.h \brief Required header file for all APG-generated parsers. Contains important configuration macros and declarations of the API functions for the entire library.

APG Version 6.3 is the first version to allow for alphabet character codes larger than 8 bits wide.
While variable, it is a "compile-time" variable and how it is controlled is dicussed here.

Alphabet character codes have the typedef apg_achar (the prefix apg_ or APG_ is often used here as a namespace.)
Its definition is controlled with the #define macro _APG_CFG_ACHAR. The corresponding values of _APG_CFG_ACHAR and apg_achar are given here:
<pre>
typedef unsigned char      apg_achar; // _APG_CFG_ACHAR = 1
typedef unsigned short int apg_achar; // _APG_CFG_ACHAR = 2
typedef unsigned int       apg_achar; // _APG_CFG_ACHAR = 4
typedef unsigned long int  apg_achar; // _APG_CFG_ACHAR = 8
typedef unsigned char      apg_achar; // (default) _APG_CFG_ACHAR undefined or defined as some value other than 1, 2, 4 or 8.
</pre>

Similarly, the size of the unsigned integer, apg_uint, ubiquitously used by APG, can be controlled here as well.
(Sizes less than 4 are risky and should be avoided. The full range is given here for completness.)
<pre>
typedef unsigned char      apg_uint; // _APG_CFG_UINT = 1
typedef unsigned short int apg_uint; // _APG_CFG_UINT = 2
typedef unsigned int       apg_uint; // _APG_CFG_UINT = 4
typedef unsigned long int  apg_uint; // _APG_CFG_UINT = 8
typedef unsigned int       apg_uint; // (default) _APG_CFG_UINT undefined or defined as some value other than 1, 2, 4 or 8.
</pre>

In this regard, also note that APG code rather fastidiously adheres to use of the following Hungarian notation
for variable and function names:
<pre>
prefix - type
c      - char
cp     - char*
ac     - apg_achar
acp    - apg_achar*
ui     - apg_uint
uip    - apg_uint*
v      - void
vp     - void*
s      - struct/union
sp     - pointer to struct/union
</pre>

A second important set of configuration #define macros are _APG_CFG_DEBUG, _APG_CFG_TRACE and _APG_CFG_STATS.

_APG_CFG_DEBUG is really a legacy macro whose usefullness is minor. In Version 6.3 it serves only as a shorthand
way to simultaneously define the other two, _APG_CFG_TRACE and _APG_CFG_STATS. (In previous versions it also
defined a debug assertion macro. This has been removed because of some complications it caused in multi-threaded
applications.)

_APG_CFG_TRACE must be defined in order to enable tracing. The reason for doing it this way is because tracing
seriously impacts the parser's performance and forces the inclusion of the IO library functions into the libary.
When this macro is not defined, the tracing code is not compiled or included in the library, resulting in not
only better preformance but a significanly smaller footprint.

For simialar reasons, _APG_CFG_STATS must be defined to enable the collection of parsing statistics.
Statistics collection can be vitally important when optimizing a parser, especially through the use of UDTs,
but usually serves no purpose in a release or production version.
*/

#ifndef APG_H_6_3
#define APG_H_6_3
//static int testing = 0; /**! member comment */

#include <stdlib.h>
#include <string.h>

// Begin C-language linkage specification
#if defined(__cplusplus)
extern "C"
{
#endif

//////////////////////////////////////////////////////////////////////////
// BASIC INTEGER TYPES
//////////////////////////////////////////////////////////////////////////
// APG integer apg_uint, default = unsigned int
/** apg_uint defines the APG integer. It may be 1, 2, 4 or 8 bytes long. (1 and 2 not recommended)*/
#if defined _APG_CFG_UINT && _APG_CFG_UINT == 1
    typedef unsigned char apg_uint;
#elif defined _APG_CFG_UINT && _APG_CFG_UINT == 2
    typedef unsigned short int apg_uint;
#elif defined _APG_CFG_UINT && _APG_CFG_UINT == 4
    typedef unsigned int apg_uint;
#elif defined _APG_CFG_UINT && _APG_CFG_UINT == 8
    typedef unsigned long int apg_uint;
#else
    typedef unsigned int apg_uint;
#endif

// APG alphabet character apg_achar, default = unsigned char
/** apg_achar defines the APG alphabet character code. It may be 1, 2, 4 or 8 bytes long. */
#if defined _APG_CFG_ACHAR && _APG_CFG_ACHAR == 1
	typedef unsigned char apg_achar;
#elif defined _APG_CFG_ACHAR && _APG_CFG_ACHAR == 2
	typedef unsigned short int apg_achar;
#elif defined _APG_CFG_ACHAR && _APG_CFG_ACHAR == 4
	typedef unsigned int apg_achar;
#elif defined _APG_CFG_ACHAR && _APG_CFG_ACHAR == 8
	typedef unsigned long int apg_achar;
#else
	typedef unsigned char apg_achar;
#endif

/** An APG-specific true value */
#define APG_TRUE       1	// apg_uint true value

/** An APG-specific false value */
#define APG_FALSE      0	// apg_uint false value
/** Often used to indicate an undefined value for an apg_uint integer.

While practically insignificant, note that in this regard the useful maximum value for apg_uint integers is reduced by one.*/
#define APG_UNDEFINED -1    // often used to represent an undefined integer

/** Often used to indicate an infinite value for an apg_uint integer.

While practically insignificant, note that in this regard the useful maximum value for apg_uint integers is reduced by one.*/
#define APG_INFINITE  -1    // often used to represent an infinite integer

// NOTE: on Hungarian notation
// prefix - type
// c      - char
// cp     - char*
// ac     - apg_achar
// acp    - apg_achar*
// ui     - apg_uint
// uip    - apg_uint*
// v      - void
// vp     - void*
// s      - struct/union
// sp     - pointer to struct/union

//////////////////////////////////////////////////////////////////////////
// CONFIGURATION CONTROL
// Control of debugging, statistics and tracing information is designed
// through macros so that when not needed, they generate no code.
//
// Debug information
// _APG_CFG_DEBUG - if defined:
//                  - automatically defines _APG_CFG_STATS
//                  - automatically defines _APG_CFG_TRACE
//
//////////////////////////////////////////////////////////////////////////

// these macros generate no code unless otherwise defined
/** \cond NODOC */
#if defined(_APG_CFG_DEBUG)
  // debug implies defines tracing & statistics gathering
  #undef  _APG_CFG_TRACE
  #define _APG_CFG_TRACE

  #undef  _APG_CFG_STATS
  #define _APG_CFG_STATS
#endif

#if defined(_APG_CFG_TRACE)
  // tracing macros (requires run-time set up in addition to _APG_CFG_TRACE)
  #define APG_TRACE_ADMIN(ctx, a, i, e, c) vTraceAdmin((ctx), (a), (i), (e), (c));
  #define APG_TRACE(ctx, op, a, i, off, pl) if((ctx)->vpTraceCtx){vTrace((ctx), (op), (a), (i), (off), (pl));}
#else
  #define APG_TRACE_ADMIN(ctx, a, i, e, c)
  #define APG_TRACE(ctx, op, a, i, off, pl)
#endif

#if defined(_APG_CFG_STATS)
	#define APG_STATS_ADMIN(ctx, a, s, r, cfg) vStatsAdmin((ctx), (a), (s), (r), (cfg))
	#define APG_STATS(ctx, a, s, o, r) vStats((ctx), (a), (s), (o), (r))
#else
	#define APG_STATS_ADMIN(ctx, a, s, r, cfg)
	#define  APG_STATS(ctx, a, s, o, r)
#endif
/** \endcond */

// Configurable default values
#undef APG_VEC_ELEMENT
#undef APG_VEC_ALLOC
/** The default vector element size (bytes.)
@see vpVecCtor()
*/
#define APG_VEC_ELEMENT   ((apg_uint)1)     // default vector element size (bytes)
/** The default initial number of vector elements allocated.
@see vpVecCtor()
*/
#define APG_VEC_ALLOC     ((apg_uint)100)   // default initial number of vector elements allocated
/** The max line length in trace and AST record output. */
#define	APG_DISPLAY_MAX_LINE	128

//////////////////////////////////////////////////////////////////////////
// ALERT HANDLING
//////////////////////////////////////////////////////////////////////////
/** Defines the function type for handling alerts with line number and file name.
@param uiLine the line number where the alert was generated.
@param cpFile name of the file where the alert was generated.
@see vTerminalAlert()*/
typedef void (*PFN_ALERT)(unsigned int uiLine, const char* cpFile);
/** Defines the function type for handling alerts with line number, file name and a dexcriptive message.
@param uiLine the line number where the alert was generated.
@param cpFile name of the file where the alert was generated.
@param cpMsg a descriptive message for the alert that was generated.
@see vTerminalAlertMsg()*/
typedef void (*PFN_ALERT_MSG)(unsigned int uiLine, const char* cpFile, const char* cpMsg);
/** The default alert handler. (Simply exits the program.)
@param uiLine the line number where the alert was generated.
@param cpFile name of the file where the alert was generated.
*/
void vDefaultAlertHandler(unsigned int uiLine, const char* cpFile);

//////////////////////////////////////////////////////////////////////////
// TOOLS
//////////////////////////////////////////////////////////////////////////
// non-ANSI minimum/maximum macros
#undef min
#undef max
/** minimum macro - defined here because it is non-ANSI. */
#define min(a,b) (((a) < (b)) ? (a) : (b))
/** maximum macro - defined here because it is non-ANSI. */
#define max(a,b) (((a) > (b)) ? (a) : (b))

// stricmp is non-ANSI - not all CRTs support it
/** Case-insensitive: compares two strings.
The two strings are compared, character for character.
NOTE: stricmp() is non-ANSI and therefore, not used
@param cpLhs pointer to the left of the two strings to compare
@param cpRhs pointer to the right of the two strings to compare
@return 0 if the two strings are case-insensitively equal<br>
-1 if the left string is less than the right string<br>
+1 if the left string is greater than the right string
*/
int apg_stricmp(const char* cpLhs, const char* cpRhs);
/** Convert an ASCII, 8-bit character string to an apg_achar character string.
@param acpAChars pointer the destination or apg_achar character string
@param cpChars pointer to the 8-bit character string to convert
@param uiLen the number of characters to convert
*/
void vCharToAChar(apg_achar* acpAChars, const char* cpChars, apg_uint uiLen);
/** Calculate the size of the string translated by uiACharToString()
@param acpAChars pointer the apg_achar character string
@param uiALen the number of apg_achar characters
@see uiACharToString()
@return the calculated size
*/
apg_uint uiACharToStringSize(const apg_achar* acpAChars, apg_uint uiALen);
/** Converts a string of apg_achar characters to a null-terminated printable ASCII string.
Non-printing characters are of the form: <xFF>.
Brackets are used to distinguish the hex format from adjacent printing characters of "x" and "F", for example.
The worst case scenario is that all translated characters will be of the form <xFF>, where sizeof(apg_achar) is 1 for example.
To be safe, the cpChars buffer size, uiCLen, should be at least:
uiALen * ((sizeof(apg_achar) * 2) + 3)
plus 1 for terminating null. To get the exact size in advance, see uiACharToStringSize().
@param cpChars pointer to the buffer to receive the printable, 8-bit character string
@param uiCLen length of the cpChars buffer
@param acpAChars pointer the apg_achar character string
@param uiALen the number of apg_achar characters
@see uiACharToStringSize()
@return the number of apg_achar characters translates. If < uiAlen, the translation was truncated due to insufficient buffer length, uiCLen
*/
apg_uint uiACharToString(char* cpChars, apg_uint uiCLen, const apg_achar* acpAChars, apg_uint uiALen);

/** \cond */
// APG INFORMATION
char* cpApgVersion();
char* cpApgAuthor();
char* cpApgDescription();
char* cpApgCopyright();
char* cpApgEmail();
char* cpApgWebsite();
char* cpApgGPLNotice();
/** \endcond */

//////////////////////////////////////////////////////////////////////////
// MEMORY MANAGEMENT COMPONENT
// A container for all parser & parser-related memory allocations.
// Intended for initial set ups, not for dynamic allocation during parsing.
//////////////////////////////////////////////////////////////////////////
/** For generated by the Memory component. Available to the user for display of memory statistics.
@see uiMemStats()
@brief generated by the Memory component, available to the user for display of memory statistics
*/
typedef struct{
  apg_uint uiAllocations;   /**< the number of memory allocations */
  apg_uint uiReAllocations; /**< the number of re-allocations*/
  apg_uint uiFrees; /**< the number of memory allocations freed*/
  apg_uint uiCells; /**< the current number of memory cells (allocations)*/
  apg_uint uiMaxCells; /**< the maximum number of memory cells allocated*/
  apg_uint uiHeapBytes; /**< the current number of heap bytes allocated*/
  apg_uint uiMaxHeapBytes; /**< the maximum number of heap bytes allocated*/
} APG_MEM_STATS;

/** the type required of any user-supplied memory allocator. The default allocator is malloc(). */
typedef void* (*PFN_ALLOCATOR)(size_t);
/** the type required of any user-supplied memory de-allocator. The default de-allocator is free(). */
typedef void  (*PFN_DEALLOCATOR)(void*);
void*		vpMemCtorA(PFN_ALLOCATOR pfnAllocator, PFN_DEALLOCATOR pfnDeAllocator);
void*		vpMemCtor();
void		vMemDtor(void* vpCtx);
apg_uint	uiMemValidate(void* vpCtx);
void*		vpMemAlloc(void* vpCtx, apg_uint uiBytes);
void*		vpMemRealloc(void* vpCtx, void* vpData, apg_uint uiBytes);
void		vMemFree(void* vpCtx, void* vpData);
apg_uint	uiMemCheckPoint(void* vpCtx);
void		vMemFreeToCheckPoint(void* vpCtx, apg_uint uiChk);
void		vMemClear(void* vpCtx);

//////////////////////////////////////////////////////////////////////////
// VECTOR
// a dynamic buffer for an arbitrary number of fixed-size elements
// Intended for initial set ups, not for dynamic allocation during parsing.
//////////////////////////////////////////////////////////////////////////
void* vpVecCtor(void* vpMemCtx, apg_uint uiElementSize, apg_uint uiInitialAlloc);
void  vVecDtor(void* vpCtx);
void* vpVecPush(void* vpVec, void* vpElement);
void* vpVecPushn(void* vpCtx, void* vpElement, apg_uint uiCount);
void* vpVecPop(void* vpCtx);
void* vpVecPopn(void* vpCtx, apg_uint uiCount);
void* vpVecPopTo(void* vpCtx, apg_uint uiIndex);
void* vpVecFront(void* vpCtx);
void* vpVecBack(void* vpCtx);
void* vpVecAt(void* vpCtx, apg_uint uiIndex);
apg_uint  uiVecBytes(void* vpCtx);
apg_uint  uiVecSize(void* vpCtx);
apg_uint  uiVecElementSize(void* vpCtx);
apg_uint  uiVecReallocations(void* vpCtx);
apg_uint	uiVecValidate(void* vpCtx);
void  vVecClear(void* vpCtx);

//////////////////////////////////////////////////////////////////////////
// PARSER
//////////////////////////////////////////////////////////////////////////
// structure passed to all syntax and semantic call back functions
/*

// !!!! DEBUG
Therefore, some variables are defined in a hierarchy of useage:
<pre>
Syntax Analysis - uiParserSyntaxAnalysis()
  rule callback functions
  UDT callback functions
Semantic Analysis - uiParserAstTranslate()
  rule callback functions
  UDT callback functions
</pre>


	Syntax Analysis, both rule and UDT callback functions.
	<pre>
	May be one of:
	PRE_PARSE - indicates the downward traversal state. No phrase has yet been matched.
	MATCH - a non-empty phrase has been matched
	EMPTY - an empty phrase has been matched
	NOMATCH - no phrase has been matched.
    </pre>
    Note on UDT

	From uiParserSyntaxAnalysis() may be any of PRE_PARSE, MATCH, EMPTY or NOMATCH.<br>
	From uiParserAstTranslate() may be  PRE_AST or POST_AST.

	//   SYNTAX ANALYSIS: output - set uiPhraseLength to the matched phrase length or APG_UNDEFINED if no match found
	// SEMANTIC ANALYSIS: uiPhraseLength for user's use only, ignored by parser on return

	// NOT USED BY PARSER - optional user-defined data, may be NULL
*/
/** The data structure passed to all syntax and AST callback functions, both rule and UDT.

It has been convenient to use a single data structure and function prototype for all callback functions,
whether rule or UDT callback, whether syntax or semantic analysis. However,
the variables in the callback data structure have slightly different meanings in each case.
See APG_CALLBACK for the details about the different types of usage.

@see APG_CALLBACK
@brief The data structure passed to all syntax and AST callback functions, both rule and UDT
*/
typedef struct{
	void*			    vpCtx;			/**< the parser's context handle. For system use only.*/
	const apg_achar*	acpSrc;			/**< pointer to the input string (user must not be modify this string)*/
	apg_uint		    uiSrcLen;		/**< the input string length*/
	apg_uint		    uiPhraseOffset;	/**< offset to the first character of the phrase matched or to be matched*/
	apg_uint		    uiState;		/**< the state of the parser. Varies with usage. @see APG_CALLBACK.	*/
	apg_uint            uiPhraseLength;/**< the phrase length. Varies with usage. @see APG_CALLBACK.*/
	void*		        vpUserData;/**< user-defined data passed to uiParserSyntaxAnalysis() or uiParserAstTranslate(). Ignored by Parser.*/
} APG_CBDATA;

/** Prototype of all user-written callback functions. It is the same for
rule and UDT callback functions
and for syntax and semantic analysis.

The interpretation of some
data structure variables are somewhat different in each of the different cases.
While this has been done for program development convenience, it can be confusing to the user in practice.
Therefore, each of the four cases is descibed separately.
Also, see Callbacks.c in the Demo example for explict examples how to write the callback functions in each case
and initialize the Parser so that it will call them.

Only the uiState, uiPhraseLength and return values differ. For all other data variables refer to APG_CBDATA.

1. Rule Syntax Callback eg.<br>
apg_uint MySyntaxRuleCallback(APG_CBDATA spData);<br>
@see Callbacks.c in the Demo example for examples of usage.
@see uiParserSyntaxInitCallbacks()
@see uiParserSyntaxAnalysis()
@param uiState one of PRE_PARSE, EMPTY, MATCH, NOMATCH indicating the parser state prior to phrase matching or the state following phrase matching
@param uiPhraseLength input: (from Parser) the length of the matched phrase, if any <br>
output: (if overriding the Parser, ie. returning true) >= 0 for matched phrase,
APG_UNDEFINED for no matched phrase
@return true if this result is to override the Parser's result, false to continue with the normal parsing

2. Rule Semantic Callback eg.<br>
apg_uint MySemanticRuleCallback(APG_CBDATA spData);<br>
@see Callbacks.c in the Demo example for examples of usage.
@see vParserAstInitCallbacks()
@see uiParserAstTranslate()
@param uiState one of PRE_AST, POST_AST indicating before the AST node traversal (downward direction node visit) or after AST node traversal (upward directionnode visit).
@param uiPhraseLength the length of the matched phrase. Note that a phrase has always been matched for this node or it wouldn't be in the AST.
@return ignored by Parser

3. UDT Syntax Callback eg.<br>
apg_uint MySyntaxUdtCallback(APG_CBDATA spData);<br>
@see Callbacks.c in the Demo example for examples of usage.
@see uiParserSyntaxInitCallbacks()
@see uiParserSyntaxAnalysis()
@param uiState PRE_PARSE only. UDTs are terminals and are only traversed once from the downward direction.
@param uiPhraseLength user must set this to 0 if an empty phrase is matched, > 0 if a non-empty phrase is matched or APG_UNDEFINED if no phrase is matched.
Note that only UDTs whose names begin with "e_" may return 0. If a "u-" named UDT returns 0 the Parser will fail.
@return ignored by Parser

4. UDT Semantic Callback eg.<br>
apg_uint MySemanticUdtCallback(APG_CBDATA spData);<br>
@see Callbacks.c in the Demo example for examples of usage.
@see vParserAstInitCallbacks()
@see uiParserAstTranslate()
@param uiState one of PRE_AST or POST_AST indicating a pre-branch (downward direction) traversal or a post-branch (upward direction) traversal of the node.
@param uiPhraseLength the length of the matched phrase. Note that a phrase has always been matched for this node or it wouldn't be in the AST.
@return ignored by Parser
*/
typedef apg_uint (*APG_CALLBACK)(APG_CBDATA* spData);

void vExecuteRule(APG_CBDATA* spData, apg_uint uiId, apg_uint uiOffset);
void vExecuteUdt(APG_CBDATA* spData, apg_uint uiId, apg_uint uiOffset);

// call back function states
/** The uiState value passed to callback functions by uiParserSyntaxAnalysis() to indicate the pre-parse or downward traversal of a syntax tree node.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserSyntaxAnalysis()
*/
#define PRE_PARSE	((apg_uint)0) // pre-branch state
/** The uiState value passed to callback functions by uiParserSyntaxAnalysis() to indicate the post-parse or upward traversal of a syntax tree node when no phrase has been matched.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserSyntaxAnalysis()
*/
#define NOMATCH		((apg_uint)1) // post-branch, string was not matched by grammar syntax
/** The uiState value passed to callback functions by uiParserSyntaxAnalysis() to indicate the post-parse or upward traversal of a syntax tree node when an empty phrase has been matched.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserSyntaxAnalysis()
*/
#define EMPTY		((apg_uint)2) // post-branch, syntax was matched by an empty string
/** The uiState value passed to callback functions by uiParserSyntaxAnalysis() to indicate the post-parse or upward traversal of a syntax tree node when a non-empty phrase has been matched.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserSyntaxAnalysis()
*/
#define MATCH		((apg_uint)3) // post-branch, syntax was matched with a string of one or more characters
/** The uiState value passed to callback functions by uiParserAstTranslate() to indicate the downward traversal of an AST node.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserAstTranslate()
*/
#define PRE_AST		((apg_uint)4) // post-branch state (semantic analysis only)
/** The uiState value passed to callback functions by uiParserAstTranslate() to indicate the upward traversal of an AST node.
@see APG_CBDATA
@see APG_CALLBACK
@see uiParserAstTranslate()
*/
#define POST_AST	((apg_uint)5) // post-branch state (semantic analysis only)

// parser final state
/** the state of the parser after parsing an input string.
@brief the state of the parser after parsing an input string. */
typedef struct{
	apg_uint uiSuccess; /**< true if the input string was matched in its entirety. false otherwise. */
	apg_uint uiState; /**< one of EMPTY, MATCH or NOMATCH. Note that it is possible for the parser to match a phrase without matching the entire input string.*/
	apg_uint uiPhraseLength; /**< length of the matched phrase*/
	apg_uint uiStringLength; /**< length of the input string*/
} APG_PARSER_STATE;

// parser statistics
/** node statistics
@brief the parsers total node hit statistics
 */
typedef struct{
	apg_uint uiTotal;/**< total number of node hits*/
	apg_uint uiMatch;/**< number of matched phrase node hits*/
	apg_uint uiEmpty;/**< number of empty matched phrase node hits*/
	apg_uint uiNoMatch;/**< number of node hits for which no phrase was matched*/
} APG_STAT;

/** named rule or UDT node stats
@brief named rule or UDT node statistics
*/
typedef struct{
	apg_uint uiIndex;/**< rule/UDT index*/
	char* cpName;/**< rule/UDT name*/
	APG_STAT sStat;/**< node stats for this named node*/
} APG_NAME_STAT;

/** full set of statistics gathered during parsing, uiParserSyntaxAnalysis()
 @brief full set of statistics gathered during parsing, uiParserSyntaxAnalysis()
 */
typedef struct{
	apg_uint		uiSize; /**< total size in bytes of this structure*/
	apg_uint		uiNameCount; /**< total number of named nodes*/
	apg_uint		uiRuleCount; /**< number of rule names*/
	apg_uint		uiUdtCount; /**< number of UDT names*/
	APG_NAME_STAT*	spNameStats; /**< pointer to named node stats*/
	APG_NAME_STAT*	spNameStatsAlpha; /**< pointer to named node stats with names in alphabetical order*/
	APG_NAME_STAT*	spNameStatsCount; /**< pointer to named node stats ordered descending numerically on number of node hits*/
	char*			cpNames; /**< pointer to the list of names*/
	APG_STAT		sRnm; /**<  node stats for RNM nodes*/
	APG_STAT		sUdt; /**<  node stats for UDT nodes*/
	APG_STAT		sRep; /**<  node stats for REP nodes*/
	APG_STAT		sAlt; /**<  node stats for ALT nodes*/
	APG_STAT		sCat; /**<  node stats for CAT nodes*/
	APG_STAT		sAnd; /**<  node stats for AND nodes*/
	APG_STAT		sNot; /**<  node stats for NOT nodes*/
	APG_STAT		sTrg; /**<  node stats for TRG nodes*/
	APG_STAT		sTbs; /**<  node stats for TBS nodes*/
	APG_STAT		sTls; /**<  node stats forTLS nodes*/
	APG_STAT		sTotal; /**<  node stats for the total of all of the above nodes*/
} APG_PARSER_STATS;

// parser constructor/desctructor
void*		vpParserCtor(void* vpParserInit, PFN_ALERT pfnAlertHandler);
void		vParserDtor(void* vpCtx);

// parser syntax analysis
apg_uint	uiParserSyntaxInitCallbacks(void* vpCtx, APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks);
apg_uint	uiParserSyntaxAnalysis(void* vpCtx, apg_uint uiStartRule, const apg_achar* acpSrc, apg_uint uiSrcLen, void* vpData);
apg_uint	uiParserState(void* vpCtx, APG_PARSER_STATE* spState);

// parser semantic analysis
void		vParserAstInitNodes(void* vpCtx, apg_uint* uipRules, apg_uint* uipUdts);
void		vParserAstInitCallbacks(void* vpCtx, APG_CALLBACK* spRuleCallbacks, APG_CALLBACK* spUdtCallbacks);
apg_uint	uiParserAstTranslate(void* vpCtx, APG_CALLBACK* pfnRuleCallbacks, APG_CALLBACK* pfnUdtCallbacks, void* vpData);

// parser statistics
apg_uint 	uiParserStatsEnable(void* vpCtx, apg_uint uiEnable);
apg_uint	uiParserStatsGet(void* vpCtx, APG_PARSER_STATS* spStats, apg_uint* uipBufferSize);

// parser trace configuration
apg_uint	uiParserTraceEnable(void* vpCtx, apg_uint uiEnable);
void		vParserTraceOp(void* vpCtx, apg_uint uiOpId, apg_uint uiEnable);
void		vParserTraceRule(void* vpCtx, apg_uint uiIndex, apg_uint uiEnable);
void		vParserTraceUdt(void* vpCtx, apg_uint uiIndex, apg_uint uiEnable);
void		vParserTraceRange(void* vpCtx, apg_uint uiBegin, apg_uint uiCount);

// TRACE OPERATOR IDS
/** \cond NODOC */
/** uiOpId in vParserTraceOp(). Trace all operator nodes.*/
#define APG_TRACE_ALL			1
/** uiOpId in vParserTraceOp(). Trace the TRG operator nodes.*/
#define APG_TRACE_TRG           2
/** uiOpId in vParserTraceOp(). Trace the TBS operator nodes.*/
#define APG_TRACE_TBS           3
/** uiOpId in vParserTraceOp(). Trace the TLS operator nodes.*/
#define APG_TRACE_TLS           4
/** uiOpId in vParserTraceOp(). Trace the AND operator nodes.*/
#define APG_TRACE_AND           5
/** uiOpId in vParserTraceOp(). Trace the NOT operator nodes.*/
#define APG_TRACE_NOT           6
/** uiOpId in vParserTraceOp(). Trace the CAT operator nodes.*/
#define APG_TRACE_CAT           7
/** uiOpId in vParserTraceOp(). Trace the ALT operator nodes.*/
#define APG_TRACE_ALT           8
/** uiOpId in vParserTraceOp(). Trace the REP operator nodes.*/
#define APG_TRACE_REP           9
/** uiOpId in vParserTraceOp(). Trace the RNM operator nodes.*/
#define APG_TRACE_RNM           10
/** uiOpId in vParserTraceOp(). Trace the UDT operator nodes.*/
#define APG_TRACE_UDT           11
/** uiOpId in vParserTraceOp(). If enabled, the trace records are counted but not printed.

Can be useful when the number of records is too large to print for getting an idea of what range of records to print.*/
#define APG_TRACE_COUNT		    12
/** \endcond */

// the UDT callback function library
apg_uint uiUdtLib_e_owsp(APG_CBDATA* spData);
apg_uint uiUdtLib_u_wsp(APG_CBDATA* spData);
apg_uint uiUdtLib_u_lineend(APG_CBDATA* spData);
apg_uint uiUdtLib_e_any(APG_CBDATA* spData);
apg_uint uiUdtLib_u_semi_comment(APG_CBDATA* spData);
apg_uint uiUdtLib_u_cpp_comment(APG_CBDATA* spData);
apg_uint uiUdtLib_u_c_comment(APG_CBDATA* spData);
apg_uint uiUdtLib_u_alphanum(APG_CBDATA* spData);
apg_uint uiUdtLib_u_alphanum_hyphen(APG_CBDATA* spData);
apg_uint uiUdtLib_u_alphanum_under(APG_CBDATA* spData);
apg_uint uiUdtLib_u_decnum(APG_CBDATA* spData);
apg_uint uiUdtLib_u_hexnum(APG_CBDATA* spData);
apg_uint uiUdtLib_u_quotedstring(APG_CBDATA* spData);
apg_uint uiUdtLib_u_singlequotedstring(APG_CBDATA* spData);
apg_uint uiUdtLib_u_doublequotedstring(APG_CBDATA* spData);

// End C-language linkage specification
#if defined(__cplusplus)
}
#endif

#endif // APG_H_6_3
