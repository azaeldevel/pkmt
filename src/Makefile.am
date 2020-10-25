AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

 

bin_PROGRAMS = pkmt


lib_LTLIBRARIES = libpkmt.la


pkmt_SOURCES = \
	main.cc \
	commands.cc \
	shell.cc \
	header.cc

pkmt_LDFLAGS = 

pkmt_LDADD = $(BDT_LIBS) $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(LIBCURL_LIBS) libpkmt.la
pkmt_CPPFLAGS = $(BDT_CFLAGS) $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS)  $(LIBCURL_CFLAGS)

libpkmt_la_SOURCES = data.cc data-collections.cc data-repository.cc data-package.cc header.cc shell.cc
libpkmt_la_LIBADD = $(BDT_LIBS) $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(LIBCURL_LIBS)
libpkmt_la_CPPFLAGS = $(BDT_CFLAGS) $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS)  $(LIBCURL_CFLAGS)
libpkmt_la_LDFLAGS = -static


pkmtdir = $(datadir)/pkmt
pkmt_DATA =

pkmt_includedir = $(includedir)/pkmt
pkmt_include_HEADERS = header.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pkmt.pc

EXTRA_DIST = pkmt.pc.in