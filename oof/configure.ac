AC_INIT(OOF,
	1.4b4,
	bojan@bnikolic.co.uk)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE()

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AC_CONFIG_SUBDIRS([pybind])	

AC_LANG_PUSH(C++)

PKG_CHECK_MODULES([BN], [bnlib >= 1.2 bnmin1 >= 1.2 astromap >= 1.2 bnfits >= 1.2])

AC_LANG_POP(C++)

AX_BOOST_BASE([1.34.0])
AX_BOOST_UNIT_TEST_FRAMEWORK()


AC_OUTPUT(Makefile
	  src/Makefile
	  src/aperture/Makefile 
	  src/telgeo/Makefile
	  src/farfield/Makefile
	  doc/Doxyfile
	  test/Makefile)




	
