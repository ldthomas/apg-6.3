APGLIB_SRC=\
  ApgLib/Ast.c \
  ApgLib/Memory.c \
  ApgLib/Operators.c \
  ApgLib/Parser.c \
  ApgLib/Stats.c \
  ApgLib/Tools.c \
  ApgLib/Trace.c \
  ApgLib/UdtLib.c \
  ApgLib/Vector.c \
  ApgLib/Apg.h \
  ApgLib/Grammar.h \
  ApgLib/Private.h \
  ApgUtilities/ApgUtilities.h \
  ApgUtilities/Files.c \
  ApgUtilities/timer.c \
  ApgUtilities/Utilities.c

GENERATOR_SRC=\
  Generator/Attributes.c \
  Generator/AttributesDependencies.c \
  Generator/AttributesNonRecursive.c \
  Generator/AttributesRecursive.c \
  Generator/Callbacks.c \
  Generator/Callbacks.h \
  Generator/CatalogLines.c \
  Generator/CommandLine.c \
  Generator/CommandLine.h \
  Generator/Errors.c \
  Generator/Generator.c \
  Generator/Generator.h \
  Generator/main.c \
  Generator/SABNFGrammar.c \
  Generator/SABNFGrammar.h
  
CPPDEMO_SRC = \
  CppDemo/CppDemo.cpp \
  CppDemo/CppDemo.h \
  CppDemo/CppDemoCallbacks.cpp \
  CppDemo/main.cpp \
  CppDemo/main.h

DEMO_SRC = \
  Demo/main.c \
  Demo/main.h \
  Demo/Setup.c \
  Demo/SetupGrammar.c \
  Demo/SetupGrammar.h \
  Demo/Callbacks.c \
  Demo/CallbacksGrammar.c \
  Demo/CallbacksGrammar.h \
  Demo/UdtLibDemo.c \
  Demo/UdtLibGrammar.c \
  Demo/UdtLibGrammar.h

MEGACO_SRC = \
  MEGACO/Callbacks.cpp \
  MEGACO/main.cpp \
  MEGACO/MEGACO.cpp \
  MEGACO/MEGACO.h

SIP_SRC = \
  SIP/Grammar1.c \
  SIP/Grammar1.h \
  SIP/Grammar2.c \
  SIP/Grammar2.h \
  SIP/Grammar3.c \
  SIP/Grammar3.h \
  SIP/Grammar4.c \
  SIP/Grammar4.h \
  SIP/Grammar5.c \
  SIP/Grammar5.h \
  SIP/main.c \
  SIP/main.h \
  SIP/Messages.c \
  SIP/SIPGrammar.c \
  SIP/SIPGrammar.h \
  SIP/SIPUdtLib.c \
  SIP/TestUdts.c \
  SIP/TortureTestTranslator.c


WIDE_SRC = \
  WideCharacters/Callbacks.c \
  WideCharacters/main.c \
  WideCharacters/main.h \
  WideCharacters/WideGrammar.c \
  WideCharacters/WideGrammar.h
  
APGINCLUDES			= -I$(srcdir)/ApgLib -I$(srcdir)/ApgUtilities
OPTFLAGS    		= -O3
DBGFLAGS    		=  -g -O2 -D_APG_CFG_DEBUG
WIDEFLAGS   		= -D_APG_CFG_ACHAR=4 -D_APG_CFG_UINT=8

bin_PROGRAMS    	= apg
noinst_PROGRAMS 	= apg_dbg\
                  		cppdemo cppdemo_dbg\
                  		demo demo_dbg\
                  		megaco megaco_dbg\
                  		sip sip_dbg\
                  		wide wide_dbg

apg_CFLAGS      	= $(OPTFLAGS) $(APGINCLUDES)
apg_dbg_CFLAGS  	= $(DBGFLAGS) $(APGINCLUDES)
apg_SOURCES     	= $(APGLIB_SRC) $(GENERATOR_SRC)
apg_dbg_SOURCES 	= $(apg_SOURCES)

cppdemo_CPPFLAGS    = $(OPTFLAGS) $(APGINCLUDES)
cppdemo_dbg_CPPFLAGS= $(DBGFLAGS) $(APGINCLUDES)
cppdemo_SOURCES     = $(APGLIB_SRC) $(CPPDEMO_SRC)
cppdemo_dbg_SOURCES = $(cppdemo_SOURCES)

demo_CFLAGS      	= $(OPTFLAGS) $(APGINCLUDES)
demo_dbg_CFLAGS  	= $(DBGFLAGS) $(APGINCLUDES)
demo_SOURCES     	= $(APGLIB_SRC) $(DEMO_SRC)
demo_dbg_SOURCES 	= $(demo_SOURCES)

megaco_CPPFLAGS     = $(OPTFLAGS) $(APGINCLUDES)
megaco_dbg_CPPFLAGS = $(DBGFLAGS) $(APGINCLUDES)
megaco_SOURCES      = $(APGLIB_SRC) $(MEGACO_SRC)
megaco_dbg_SOURCES  = $(megaco_SOURCES)

sip_CFLAGS      	= $(OPTFLAGS) $(APGINCLUDES)
sip_dbg_CFLAGS  	= $(DBGFLAGS) $(APGINCLUDES)
sip_SOURCES     	= $(APGLIB_SRC) $(SIP_SRC)
sip_dbg_SOURCES 	= $(sip_SOURCES)

wide_CFLAGS      	= $(OPTFLAGS) $(WIDEFLAGS) $(APGINCLUDES)
wide_dbg_CFLAGS  	= $(DBGFLAGS) $(WIDEFLAGS) $(APGINCLUDES)
wide_SOURCES     	= $(APGLIB_SRC) $(WIDE_SRC)
wide_dbg_SOURCES 	= $(wide_SOURCES)

EXTRA_DIST = \
 $(APGLIB_SRC) \
 Generator/AbnfForSabnf.bnf\
 Generator/runtests\
 Generator/generateGrammars\
 CppDemo/runtests\
 CppDemo/generateGrammars\
 CppDemo/CppDemo.bnf\
 Demo/runtests\
 Demo/generateGrammars\
 Demo/Callbacks.input \
 Demo/Callbacks.bnf \
 Demo/Setup.input \
 Demo/Setup.bnf \
 Demo/UdtLib.bnf\
 MEGACO/runtests\
 MEGACO/generateGrammars\
 MEGACO/MEGACO.input \
 MEGACO/MEGACO.bnf\
 SIP/runtests\
 SIP/generateGrammars\
 SIP/TortureTests.txt \
 SIP/Grammar1.bnf \
 SIP/Grammar2.bnf \
 SIP/Grammar3.bnf \
 SIP/Grammar4.bnf \
 SIP/Grammar5.bnf \
 SIP/SIP.input \
 SIP/SIP.bnf\
 WideCharacters/runtests\
 WideCharacters/generateGrammars\
 Doxyfile \
 DoxyHeader.html \
 DoxyFooter.html \
 LICENSE \
 README.md


