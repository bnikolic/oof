AC_INIT(BNMIN1, 
	1.12,
	bojan@bnikolic.co.uk)

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE()

AC_CONFIG_HEADERS(config.h)

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX
AC_PROG_F77

AM_CONDITIONAL([GFORTRAN], [test "$ac_ct_F77" = "gfortran"])

AM_PATH_GSL(1.9,
	[],
	AC_MSG_ERROR(Could not find the required version of GSL))

AC_LANG_PUSH(C++)

AC_ARG_ENABLE(buildtests,
	      [AS_HELP_STRING([--disable-buildtests],
                              [Do not configure and build the tests])],
              [dobuildtests=$enableval],
	      [dobuildtests=--enable-buildtests])

AM_CONDITIONAL([BUILDTESTS_OPT], 
	       [test "x$dobuildtests" != xno])

AX_BOOST_BASE([1.34.0])

if test "$dobuildtests" != "no" ; then
   AX_BOOST_UNIT_TEST_FRAMEWORK()
   AX_BOOST_PROGRAM_OPTIONS()
fi

AC_LANG_POP(C++)

AC_ARG_ENABLE(pybind,
	      [AS_HELP_STRING([--disable-pybind],
                              [Do not configure and build the python bindings])],
              [dopybind=$enableval],
	      [dopybind=--enable-pybinding])

AM_CONDITIONAL([PYBIND_OPT], 
	       [test "x$dopybind" != xno])

AC_ARG_ENABLE(pda,
	      [AS_HELP_STRING([--disable-pda],
                              [Do not compile, link or use the PDA algorithms])],
              [dopda=$enableval],
	      [dopda=--enable-pda])

AM_CONDITIONAL([PDA_OPT], 
	       [test "x$dopda" != xno])

if test "$dopda" = "no" ; then
   AC_DEFINE([BNMIN1_NO_PDA],[1],
             [Defined if we can not use the PDA algorithms])
fi


AS_IF([test "x$dopybind" != xno],
      AC_CONFIG_SUBDIRS([pybind]))

AC_OUTPUT(Makefile 
          src/Makefile
	  src/f77/Makefile
	  test/Makefile
	  doc/Doxyfile
	  bnmin1.pc)
