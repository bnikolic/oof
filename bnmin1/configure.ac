AC_INIT(BNMIN1, 
	1.5,
	"Bojan Nikolic"   <bojan@bnikolic.co.uk>)

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

AX_BOOST_BASE([1.34.0])
AX_BOOST_UNIT_TEST_FRAMEWORK()

AC_LANG_POP(C++)

AC_CONFIG_SUBDIRS([pybind])	


AC_OUTPUT(Makefile 
          src/Makefile
	  src/f77/Makefile
	  test/Makefile
	  doc/Doxyfile
	  bnmin1.pc)
