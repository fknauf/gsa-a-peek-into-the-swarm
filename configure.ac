AC_INIT([apeekintotheswarm], [1.0.0], , [apeekintotheswarm])
AM_INIT_AUTOMAKE([foreign 1.11 -Wall -Werror subdir-objects])

AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT([/usr])

CXXFLAGS+=" -Wall -Wextra -pedantic -std=c++17 -fopenmp"
LDLIBS+="-lopenmp"

APITS_ARG_ENABLE_DEBUG(no)

AC_PROG_CXX

AM_SILENT_RULES([yes])

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
