include $(top_srcdir)/share/Makefile.include

TEST_PROGS += xultest
xultest_CFLAGS = $(EXTRA_CFLAGS) $(GLIB_CFLAGS) $(XUL_CFLAGS)
xultest_LDADD = $(GLIB_LIBS) $(XUL_LIBS)
xultest_SOURCES = xultest.c xbuffer.c xprefs.c xshm.c xtime.c

bin_PROGRAMS = $(TEST_PROGS)

indent-local:
	@indent *.[ch]

quick-install-local: $(lib_LTLIBRARIES) $(bin_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) install
	@touch quick-install-local

coverage-clean-local:
	@lcov --directory $(top_srcdir) --zerocounters

coverage-local: coverage-clean-local test
	@lcov --directory $(top_srcdir) --output-file lcov.info --capture

coverage-report-local: coverage-local
	@genhtml --output-directory coverage lcov.info

.PHONY: indent-local coverage-clean-local coverage-local coveage-report-local
