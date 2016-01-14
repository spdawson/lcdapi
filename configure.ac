#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([lcdapi], [0.10], [spdawson@gmail.com])
AC_CONFIG_SRCDIR([lcdapi/api/LCDConnection.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([foreign])
LT_INIT
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
  then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN],
[test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])

# Checks for libraries.
AC_CHECK_LIB([pthread], [pthread_create])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

AX_CHECK_COMPILE_FLAG([-fdiagnostics-color=always],[CXXFLAGS="$CXXFLAGS -fdiagnostics-color=always"])

# Checks for library functions.
AC_CHECK_FUNCS([memset socket strtol])

AC_CONFIG_FILES([Makefile
                 docs/Makefile
                 example/Makefile])
AC_OUTPUT
