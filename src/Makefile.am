

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = pkmt

dist_bin_SCRIPTS = pkmt-prephost-build

pkmt_SOURCES = \
	main.cc \
	commands.cc

pkmt_LDFLAGS = 

pkmt_LDADD = $(BDT_LIBS)
pkmt_CPPFLAGS = $(BDT_CFLAGS)

