include $(top_srcdir)/share/Makefile.decl

lib_LTLIBRARIES = libxul.la
libxul_la_SOURCES = xul.c xerror.c xprefs.c xtime.c xtrace.c xverbose.c
libxul_la_CFLAGS = $(GLIB_CFLAGS)
libxul_la_LIBADD = $(GLIB_LIBS)

bin_PROGRAMS = xultool
xultool_CFLAGS = $(GLIB_CFLAGS)
xultool_LDADD = $(GLIB_LIBS) libxul.la
