
AC_INIT(src/interpolate.hxx)

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE(BNLIB, 1.0)

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

AC_CONFIG_SUBDIRS([pybind])	

AC_OUTPUT(Makefile 
          src/Makefile
	  cbind/Makefile
	  doc/Doxyfile
	  )
	  
