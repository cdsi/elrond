include $(top_srcdir)/share/Makefile.include

lib_LTLIBRARIES = libflusher.la libflusher32.la

libflusher_la_CFLAGS = $(EXTRA_CFLAGS) $(COVERAGE_CFLAGS)
libflusher_la_LIBADD = $(COVERAGE_LIBS)
libflusher_la_SOURCES = flusher.c

libflusher32_la_CFLAGS = $(EXTRA_CFLAGS) $(COVERAGE_CFLAGS) -m32 -DXX_TARGET=32
libflusher32_la_LIBADD = $(COVERAGE_LIBS)
libflusher32_la_SOURCES = flusher.c

bin_PROGRAMS = launcher launcher32

launcher_CFLAGS = $(EXTRA_CFLAGS) $(COVERAGE_CFLAGS)
launcher_LDADD = $(COVERAGE_LIBS)
launcher_SOURCES = launcher.c

launcher32_CFLAGS = $(EXTRA_CFLAGS) $(COVERAGE_CFLAGS) -m32 -DXX_TARGET=32
launcher32_LDADD = $(COVERAGE_LIBS)
launcher32_SOURCES = launcher.c

indent-local:
	@indent *.[ch]

quick-install-local: $(lib_LTLIBRARIES) $(bin_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) install
	@touch quick-install-local

.PHONY: indent-local
