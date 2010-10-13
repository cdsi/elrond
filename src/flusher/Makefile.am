include $(top_srcdir)/share/Makefile.include

lib_LTLIBRARIES = libflusher.la
libflusher_la_CFLAGS = $(COVERAGE_CFLAGS)
libflusher_la_LIBADD = $(COVERAGE_LIBS)
libflusher_la_SOURCES = flusher.c

indent-local:
	@indent *.[ch]

quick-install-local: $(lib_LTLIBRARIES) $(bin_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) install
	@touch quick-install-local

.PHONY: indent-local
