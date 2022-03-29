
AC_INIT([WordleAgents], [0.1])
AM_INIT_AUTOMAKE

LT_PREREQ([2.2])
LT_INIT([dlopen])

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB

AC_CONFIG_SRCDIR([PickWords/Source/PickWords.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_HEADERS([stdio.h])
AC_SEARCH_LIBS([ltdl])

AC_CONFIG_FILES([Makefile
		 WordleAgent/Makefile
		 WordleAgent/Source/Makefile
                 PickWords/Makefile
                 PickWords/Source/Makefile
                 ])

AC_OUTPUT
echo \
"-------------------------------------------------

 ${PACKAGE_NAME} Version ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'
 Libraries: '${LIBS}'

 Package features:
    None (yet)

 Now type 'make @<:@<target>@:>@'
   where the optional <target> is:
     all                - build all binaries
     install            - install everything
     check              - run unit tests
     dist               - build distribution tarball
     distcheck          - build, run tests and generate distribution tar

--------------------------------------------------"
