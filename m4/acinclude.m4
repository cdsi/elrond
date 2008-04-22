AC_DEFUN([XX_CHECK_GLIB], [
        AM_PATH_GLIB_2_0([2.16.0])

        if test "${GLIB_CFLAGS}" = "" || test "${GLIB_LIBS}" = ""; then
                AC_MSG_ERROR([unable to locate glib or incorrect version])
        fi
])

AC_DEFUN([GANDALF_WITH_SWIG], [
	gandalf_withval=yes

	AC_ARG_WITH([swig],
		AS_HELP_STRING([--with-swig=[SWIG_HOME]],
			[use specified swig to build language bindings]),
		[gandalf_withval=${withval}])

	if test ! "${gandalf_withval}" = "no"; then

		case "${gandalf_withval}" in
		yes)
			SWIG_HOME=${SWIG_HOME}
		;;
		/*)
			SWIG_HOME=${gandalf_withval}
		;;
		esac

		if test ! "${SWIG_HOME}" = "" &&
			test ! -d "${SWIG_HOME}"; then
				AC_MSG_WARN([unable to locate swig home: ${SWIG_HOME}])
				SWIG_HOME=/usr
		fi

		AC_MSG_NOTICE([with swig: ${SWIG_HOME}])
		AC_SUBST(SWIG_HOME)

		AC_ARG_VAR([SWIG], [please see: http://www.swig.org])
		PATH1=${SWIG_HOME}/bin:${PATH}
		AC_PATH_PROG([SWIG], [swig], [], [${PATH1}])
		test -z ${SWIG} && AC_MSG_ERROR([unable to locate swig])
		AC_SUBST(SWIG)

	fi
])

AC_DEFUN([GANDALF_WITH_JAVA], [
	gandalf_withval=yes

	AC_ARG_WITH([java],
		AS_HELP_STRING([--with-java[=JAVA_HOME]],
			[use specified java to build java bindings]),
		[gandalf_withval=${withval}])

	if test ! "${gandalf_withval}" = "no"; then

		case "${gandalf_withval}" in
		yes)
			JAVA_HOME=${JAVA_HOME}
		;;
		/*)
			JAVA_HOME=${gandalf_withval}
		;;
		esac

		if test "${JAVA_HOME}" = "" || test ! -d "${JAVA_HOME}"; then
			JAVA_HOME=/usr
		fi

		if test ! -d "${JAVA_HOME}"; then
			AC_MSG_ERROR([unable to locate java home: ${JAVA_HOME}])
		fi

		AC_MSG_NOTICE([with java: ${JAVA_HOME}])
		AC_SUBST([JAVA_HOME])

		AC_REQUIRE([AC_CANONICAL_HOST])[]dnl

		case "${host_os}" in
		*darwin*)
			JAVA_OS=darwin
		;;
		*linux*)
			JAVA_OS=linux
		;;
		*)
			AC_MSG_ERROR([${host_os} is an unsupported platform])
		;;
		esac

		INCLUDE1="${JAVA_HOME}/include"
		INCLUDE2="${JAVA_HOME}/include/${JAVA_OS}"

		if test ! -d "${INCLUDE1}" && test ! -d "${INCLUDE2}"; then
			AC_MSG_ERROR([unable to locate java includes: ${INCLUDE1} ${INCLUDE2}])
		fi

		JAVA_INCLUDES="-I${INCLUDE1} -I${INCLUDE2}"

		AC_MSG_NOTICE([java includes: ${JAVA_INCLUDES}])
		AC_SUBST(JAVA_INCLUDES)

	fi
])

AC_DEFUN([GANDALF_ENABLE_JAVA], [
	AC_REQUIRE([GANDALF_WITH_SWIG])[]dnl
	AC_REQUIRE([GANDALF_WITH_JAVA])[]dnl

	gandalf_enableval=yes

	AC_ARG_ENABLE([java],
		AS_HELP_STRING([--enable-java[=BINDINGS_HOME]],
			[enable Java language bindings]),
		[gandalf_enableval=${enableval}])

	ENABLE_JAVA=0

	if test ! "${gandalf_enableval}" = "no"; then

		case "${gandalf_enableval}" in
		yes)
			BINDINGS_HOME=${top_srcdir}
		;;
		/*)
			BINDINGS_HOME=${gandalf_enableval}
		;;
		esac

		O=${BINDINGS_HOME}/gandalf/backends
		P=gandalf.backends

		JAVA_FLAGS="-java -outdir $O -package $P"
		AC_SUBST(JAVA_FLAGS)

		ENABLE_JAVA=1

	fi

	AM_CONDITIONAL(ENABLE_JAVA, test ${ENABLE_JAVA} = 1)
])

AC_DEFUN([GANDALF_WITH_PYTHON], [
	gandalf_withval=yes

	AC_ARG_WITH([python],
		AS_HELP_STRING([--with-python[=PYTHON_HOME]],
			[use specified python to build python bindings]),
		[gandalf_withval=${withval}])

	if test ! "${gandalf_withval}" = "no"; then

		case "${gandalf_withval}" in
		yes)
			PYTHON_HOME=${PYTHON_HOME}
		;;
		/*)
			PYTHON_HOME=${gandalf_withval}
		;;
		esac

		if test "${PYTHON_HOME}" = "" || test ! -d "${PYTHON_HOME}"; then
			PYTHON_HOME=/usr
		fi

		if test ! -d "${PYTHON_HOME}"; then
			AC_MSG_ERROR([unable to locate python home: ${PYTHON_HOME}])
		fi

		AC_MSG_NOTICE([with python: ${PYTHON_HOME}])
		AC_SUBST(PYTHON_HOME)

		PYTHON_VERSIONS="2.5 2.4 2.3"

		for PYTHON_VERSION in ${PYTHON_VERSIONS}; do
			INCLUDE1="${PYTHON_HOME}/include/python${PYTHON_VERSION}"
			if test -d "${INCLUDE1}"; then
				break
			fi
		done

		if test ! -d "${INCLUDE1}"; then
			AC_MSG_ERROR([unable to locate python includes: ${PYTHON_HOME}/include/python: ${PYTHON_VERSIONS}])
		fi

		PYTHON_INCLUDES="-I${INCLUDE1}"

		AC_MSG_NOTICE([python includes: ${PYTHON_INCLUDES}])
		AC_SUBST(PYTHON_INCLUDES)

	fi

])

AC_DEFUN([GANDALF_ENABLE_PYTHON], [
	AC_REQUIRE([GANDALF_WITH_SWIG])[]dnl
	AC_REQUIRE([GANDALF_WITH_PYTHON])[]dnl

	gandalf_enableval=yes

	AC_ARG_ENABLE([python],
		AS_HELP_STRING([--enable-python[=BINDINGS_HOME]],
			[enable Python language bindings]),
		[gandalf_enableval=${enableval}])

	ENABLE_PYTHON=0

	if test ! "${gandalf_enableval}" = "no"; then

		case "${gandalf_enableval}" in
		yes)
			BINDINGS_HOME=${top_srcdir}
		;;
		/*)
			BINDINGS_HOME=${gandalf_enableval}
		;;
		esac

		O=${BINDINGS_HOME}/gandalf/backends

		PYTHON_FLAGS="-python -modern -outdir $O"
		AC_SUBST(PYTHON_FLAGS)

		ENABLE_PYTHON=1

	fi

	AM_CONDITIONAL(ENABLE_PYTHON, test ${ENABLE_PYTHON} = 1)
])

AC_DEFUN([GANDALF_CLOCKS], [
	SAVED_LIBS=${LIBS}
	AC_SEARCH_LIBS(clock_gettime, [rt posix4], [
		test "${ac_cv_search_clock_gettime}" = "none required" ||
			CLOCKS_LDFLAGS=${ac_cv_search_clock_gettime}
	])
	AC_CHECK_FUNCS([clock_gettime clock_settime])
	AC_SUBST(CLOCKS_LDFLAGS)
	LIBS=${SAVED_LIBS}
])

AC_DEFUN([GANDALF_ENABLE_A9225], [
	ENABLE_A9225=0

	AC_ARG_ENABLE([a9225],
		AS_HELP_STRING([--enable-a9225],
			[enable antenna hardware a9225 support]), [
		ENABLE_A9225=1
		])

	dnl TODO: is this a valid test?
	if test -e /dev/gpio_00_0; then
		ENABLE_A9225=1
	fi

	if test ${ENABLE_A9225} = 1; then
		AC_DEFINE([ENABLE_A9225], [], [Description])
		AC_MSG_NOTICE([enabled antenna hardware a9225 support])

		CFLAGS="${CFLAGS} -I/usr/src/linux/include"
	fi
])
