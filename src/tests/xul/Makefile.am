include $(top_srcdir)/share/Makefile.decl

TEST_PROGS += xultest
xultest_CFLAGS = $(GLIB_CFLAGS) $(XUL_CFLAGS)
xultest_LDADD = $(GLIB_LIBS) $(XUL_LIBS)
xultest_SOURCES = xultest.c xprefs.c xtime.c

bin_PROGRAMS = $(TEST_PROGS)

coverage-local-clear:
	@lcov --directory $(top_srcdir) --zerocounters

coverage-local: coverage-local-clear test
	@lcov --directory $(top_srcdir) --output-file lcov.info --capture

coverage-report-local: coverage-local
	@genhtml --output-directory coverage lcov.info

.PHONY: coverage-local-clean coverage-local coveage-report-local
