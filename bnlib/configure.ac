
AC_INIT(BNLIB,
	1.3.3,
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

AM_PATH_GSL(1.5,
	[AC_DEFINE([BN_HAVE_GSL], [1] ,  [Define if GSLv1.5 exists.])],
	AC_MSG_WARN(Tested version of GSL not found, but you might be OK anyway) )

AC_ARG_ENABLE(pybinding,
	      [AS_HELP_STRING([--disable-pybinding],
                              [Do not configure and build the python bindings])],
              [dopybind=$enableval],
	      [dopybind=--enable-pybinding])

AM_CONDITIONAL([PYBIND_OPT], 
	       [test "x$dopybind" != xno])

AS_IF([test "x$dopybind" != xno],
      AC_CONFIG_SUBDIRS([pybind]))

AX_BOOST_BASE([1.34.0])
AX_BOOST_PROGRAM_OPTIONS()

AC_OUTPUT(Makefile 
          src/Makefile
	  src/kolmog/Makefile
	  cbind/Makefile
	  test/Makefile
	  doc/Doxyfile
	  doc/Kolmog.doxy
	  bnlib.pc
	  )
	  
