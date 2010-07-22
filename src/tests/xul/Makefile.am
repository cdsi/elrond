include $(top_srcdir)/share/Makefile.include

TEST_PROGS += xultest
xultest_CFLAGS = $(GLIB_CFLAGS) $(XUL_CFLAGS)
xultest_LDADD = $(GLIB_LIBS) $(XUL_LIBS)
xultest_SOURCES = xultest.c xbuffer.c xprefs.c xshm.c xtime.c

bin_PROGRAMS = $(TEST_PROGS)

indent-local:
	@indent *.[ch]

coverage-local-clear:
	@lcov --directory $(top_srcdir) --zerocounters

coverage-local: coverage-local-clear test
	@lcov --directory $(top_srcdir) --output-file lcov.info --capture

coverage-report-local: coverage-local
	@genhtml --output-directory coverage lcov.info

.PHONY: indent-local coverage-local-clean coverage-local coveage-report-local
