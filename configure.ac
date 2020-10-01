

AC_INIT(pkmt, 0.3.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX
AC_PROG_LIBTOOL






PKG_CHECK_MODULES(OCTETOS_CORE,octetos-core)

PKG_CHECK_MODULES(LIBCONFIG,libconfig++)

PKG_CHECK_MODULES(BDT,bdt)

PKG_CHECK_MODULES(CUNIT,cunit)

AC_DEFINE_UNQUOTED([PATHDIR], ["$ac_abs_confdir"],[Define to the read-only architecture-independent data directory.])


AC_OUTPUT([
Makefile
src/Makefile
tests/Makefile
])
