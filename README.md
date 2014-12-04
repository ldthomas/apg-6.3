##APG - An ABNF Parser Generator

**Version:** 6.3

**Description:**  

<ul><li><b>APG</b> is an acronym for "ABNF Parser Generator"
</li>
<li>generates parsers in C or C++
</li>
<li>generates language parsers and translators from a superset of the Augmented Backus-Naur Form (ABNF <a href="https://tools.ietf.org/html/rfc5234">RFC5234</a>) grammar syntax
</li>
<li>accepts valid ABNF grammars
</li>
<li>accepts <code>AND</code> & <code>NOT</code> syntactic predicate operators for conditional parsing based on specified, look-ahead phrases
</li>
<li>accepts User-Defined Terminals (UDTs) which allow user-written, non-Context-Free phrase recognition operators
</li>
<li>runs on both 32- and 64-bit operating systems
</li>
<li>input language strings may be represented with 8-, 16-, 32- or 64-bit character codes
</li>
<li>user-written callback functions provide complete monitoring and flow control of the parser</li>
<li>optional generation of an Abstract Syntax Tree (AST)</li>
<li>translation of the AST with user-written callback functions</li>
<li>extensive tracing facilities</li>
<li>statistics gathering for a full picture of parse tree node coverage</li>
<li>extensive attribute generation for an overview of the grammar's characteristics</li>
</ul>
For more details see the documentation or visit the <a href="http://www.coasttocoastresearch.com">APG website</a>.

|directories/files:|description|
|:--------|:----------|  
|  ApgLib/                   |- the APG runtime library, required by the generator and all generated parsers
|  ApgUtilities/                   |- optional but useful utilities, especially for formatted display of APG's data structures
|  Generator/                |- the main() function here is the parser generator
|  CppDemo/                 |- example of how to set up and run a C++ parser
|  Demo/             |- a simple example which demonstrates most of the APG features including UDTs
|  MEGACO/         |- a C++ parser for the Media Gateway Control protocol ([RFC3525](http://www.ietf.org/rfc/rfc3525.txt?number=3525))
|  SIP/          |- an extensive timing test demonstrating the power of UDTs for the Session Initiation Protocol ([RFC3261](https://www.ietf.org/rfc/rfc3261.txt))
|  WideCharacters/        |- demonstrates parsing 32-bit character coded input strings
|  LICENSE                     |- Version 2 of the GNU General Public License|
|  README.md                   |- this file|
|  Doxyfile                   |- documentation generation (Doxygen) configuration file|
|  DoxyHeader.html                   |- documentation header file|
|  DoxyFooter.html             |- documentation footer file|
|  other                   |- automake files|

Each of the directories Generator, CppDemo, Demo, MEGACO, SIP and WideCharacters has two bash scripts: `tuntests` and `generateGrammars`.
`runtests` will run one or more tests on the optimized and debug builds.
`generateGrammars` will re-generate all of the parser files from the included grammar (.bnf) files. 

**Linux Installation:**  

The automake installation uses the "subdir-objects" option. This option has changed with automake >=1.14. It is recommended with version 1.14 and will be mandatory in automake 2.0. Consequently, APG and the examples are now built with a single Makefile.am file and recursion into subdirectories has been eliminated. This has the feature of putting all of the object files in the same directories where the respective the source files reside. A couple of tricks will be demonstrated here to get rid of the clutter if you find this annoying.

<u>a) the basic build:</u>
```
clone or unzip apg-6.3
cd (repo directory)
./configure
make
sudo make install
```
This will make all targets (see b) below) and install the optimized version of apg in:
`/usr/local/bin/apg`
apg is the parser generator. For usage, execute "apg --help".
 
To change the install location use, for example:
`./configure --prefix=/mydir` installs to `/mydir/bin/apg`

Note that apg may conflict with a program name already installed (Automated Password Generator, for example.) To change the name of the installed program use, for example:
`./configure --program-prefix=my` installs `/usr/local/bin/myapg`
or
`./configure --program-suffix=en` installs `/usr/local/bin/apgen`
 
<u>b) the build targets:</u>
 
|optimized target       |debug target  |description|
|:----------------|:-------------|:----------|
|   apg           |    apg_dbg   | APG - the ABNF Parser Generator|
|   cppdemo        | cppdemo_dbg | basic demonstration of building and using a C++ parser|
|   demo          |   demo_dbg        | basic demonstration of most of the APG features|
|   megaco        | megaco_dbg      | sample C++, MEGAGO parser|
|   sip           |    sip_dbg         | extensive timing tests for variously optimized SIP parsers|
|   wide          |   wide_dbg        | example of using 32-bit wide grammar alphabet characters|

Note that individual programs can be built by specifying the target names. e.g.
`make apg            ; build only the optimized version of apg`
`make sip sip_dbg    ; build both the optimized and debug versions of the SIP example`
 
<u>c) (recommended) put all object files and executables in a separate directory:</u>
```
clone or unzip apg-6.3
cd (repo directory)
mkdir build
cd build
../configure
make
sudo make install
```
When using this configuration it will be necessary to supply the build directory as a parameter to the test scripts, `runtests` and `generateGrammars`, that exist in each target directory. For example, with the build above, to test the generator (apg)
```
cd ../Generator
./runtests ../build
./generateGrammars ../build
```
<u>d) clean up:</u>
`make mostlyclean      ; remove all object files but not the executable programs`
`make maintainer-clean ; remove everything make created`

**Documentation:**  
Install [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html). From the repo directory run
`doxygen`
Open `./documentation/index.html` in any web browser. Or visit the [APG website](http://www.coasttocoastresearch.com).

**Copyright:**  
  *Copyright &copy; 2005 - 2012 Lowell D. Thomas, all rights reserved*  

**License:**  
  APG Version 6.3 is released under Version 2.0 or higher of the
  <a href="https://www.gnu.org/licenses/licenses.html">GNU General Public License</a>.
