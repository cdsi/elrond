lib_LTLIBRARIES = libxul.la
libxul_la_SOURCES = xul.c
libxul_la_CFLAGS = $(GLIB_CFLAGS)
libxul_la_LIBADD = $(GLIB_LIBS)

bin_PROGRAMS = xultool
xultool_CFLAGS = $(GLIB_CFLAGS)
xultool_LDADD = $(GLIB_LIBS) libxul.la