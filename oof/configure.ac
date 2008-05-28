
AC_INIT(OOF,
	1.2,
	"Bojan Nikolic" <bojan@bnikolic.co.uk> )

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

AC_CHECK_HEADERS( astromap.hxx , 
		  [echo "found AstroMap"],
		  AC_MSG_ERROR(["Error: No AstroMap!!!" ] )
		  )

PKG_CHECK_MODULES([BN], [bnmin1 >= 1.2])

AC_LANG_POP(C++)

AC_OUTPUT(Makefile
	  src/Makefile
	  src/aperture/Makefile 
	  src/telgeo/Makefile
	  src/farfield/Makefile
	  doc/Doxyfile)




	
