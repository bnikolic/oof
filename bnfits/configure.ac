AC_INIT(BNFITS,
	1.1,
	"Bojan Nikolic"   <bojan@bnikolic.co.uk>)


AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE()

AC_CONFIG_HEADERS(config.h)

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AC_CHECK_LIB( [cfitsio] , [ffopen] , 
	      [AC_DEFINE(HAVE_CFITSIO, [] , [Defined if found cfitsio library]) ] , 
	      [echo "no cfitsio"] , 
	      [ -lm ])


AC_CONFIG_SUBDIRS([pybind])	 

AC_OUTPUT(Makefile 
          src/Makefile)

