
AC_INIT([WordleAgents], [0.1])
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB
AM_PROG_CC_C_O

AC_CONFIG_SRCDIR([PickWords/PickWords.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_HEADERS([stdio.h])

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
