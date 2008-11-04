AC_INIT(BNMIN1, 
	1.4,
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

AM_PATH_GSL(1.6)

AC_LANG_PUSH(C++)

AX_BOOST(1.34.0,
	[echo "GOOD: You have BOOST ... we will be using that!" ],		     
	AC_MSG_ERROR(["ERROR: No BOOST  ... ; you can find it at  http://www.boost.org/ "])  )

AC_LANG_POP(C++)

AC_CONFIG_SUBDIRS([pybind])	


AC_OUTPUT(Makefile 
          src/Makefile
	  src/f77/Makefile
	  test/Makefile
	  doc/Doxyfile
	  bnmin1.pc)
