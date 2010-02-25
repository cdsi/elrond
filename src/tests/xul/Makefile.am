include $(top_srcdir)/share/Makefile.decl

TEST_PROGS += xultest
xultest_CFLAGS = $(GLIB_CFLAGS) $(XUL_CFLAGS)
xultest_LDADD = $(GLIB_LIBS) $(XUL_LIBS)
xultest_SOURCES = xultest.c xprefs.c xtime.c

bin_PROGRAMS = $(TEST_PROGS)
