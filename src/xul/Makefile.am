include $(top_srcdir)/share/Makefile.decl

lib_LTLIBRARIES = libxul.la
libxul_la_CFLAGS = $(GLIB_CFLAGS) $(GMODULE_CFLAGS) $(COVERAGE_CFLAGS)
libxul_la_LIBADD = $(GLIB_LIBS) $(GMODULE_LIBS) $(COVERAGE_LIBS)
libxul_la_SOURCES = xul.c xbuffer.c xerror.c xprefs.c xshm.c xtime.c xtrace.c xverbose.c

bin_PROGRAMS = xultool
xultool_CFLAGS = $(GLIB_CFLAGS) $(GMODULE_CFLAGS) $(XUL_CFLAGS)
xultool_LDADD = $(GLIB_LIBS) $(GMODULE_LIBS) $(XUL_LIBS) libxul.la

BUILT_SOURCES =
SUFFIXES = .i

if ENABLE_PYTHON

lib_LTLIBRARIES += libpyxul.la
libpyxul_la_CFLAGS = $(GLIB_CFLAGS) $(GMODULE_CFLAGS) $(XUL_CFLAGS) $(PYTHON_INCLUDES)
libpyxul_la_LIBADD = $(GLIB_LIBS) $(GMODULE_LIBS) $(XUL_LIBS)  $(PYTHON_LIBS) libxul.la
libpyxul_la_SOURCES = python.c

BUILT_SOURCES += python.c

python.c: wrapper.i _xul.h
	@$(SWIG) $(SWIGFLAGS) $(INCLUDES) $(PYTHON_FLAGS) $(PYTHON_INCLUDES) -o $@ wrapper.i

endif

CLEANFILES = $(BUILT_SOURCES)

check-local:
	@test ! -d .libs || (cd .libs ; test ! -f libpyxul.so || ln -fs libpyxul.so _xul.so)

indent-local:
	@indent *.[ch]

install-exec-hook:
	@test ! -d $(DESTDIR)$(libdir) || (cd $(DESTDIR)$(libdir) ; \
		test ! -f libpyxul.so || ln -fs libpyxul.so _xul.so)

uninstall-hook:
	@rm -f $(DESTDIR)$(libdir)/_xul.so

.PHONY: check-local indent-local
