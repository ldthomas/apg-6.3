#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([apg], [6.3], [lowell@coasttocoastresearch.com])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign dist-zip])
AC_CONFIG_HEADERS([config.h])

CFLAGS=''
CXXFLAGS=''
CPPFLAGS=''
AM_CFLAGS=''
AM_CXXFLAGS=''
AM_CPPFLAGS=''

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([malloc.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
