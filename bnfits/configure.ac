AC_INIT()

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE(BNFITS, 1.0.1 )

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AC_CHECK_LIB( [cfitsio] , [ffopen] , 
	      [AC_DEFINE(HAVE_CFITSIO) ] , 
	      [echo "no cfitsio"] , 
	      [ -lm ])


AC_CONFIG_SUBDIRS([pybind])	 

AC_OUTPUT(Makefile 
          src/Makefile)

