
AC_COPYRIGHT(Bojan Nikolic)
AC_REVISION($Id: configure.ac,v 1.4 2005/08/25 17:03:29 bnikolic Exp $)

AC_INIT()

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE(ASTROMAPPLOT, 0.01)

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AX_BOOST_BASE([1.34.0])

AC_CHECK_HEADERS( cpgplot.h , 
		  [echo "Found pgplot"],
		  [AC_MSG_ERROR("Error: No pgplot!!!!" ) ]    )

AM_PATH_PYTHON(2.3)

AC_PATH_X()
AC_PATH_XTRA()

AM_CHECK_PYTHON_HEADERS()

PKG_CHECK_MODULES([BN], [bnlib >= 1.1 bnfits >= 1.2 bnmin1 >= 1.2])

AC_PATH_PROGS([SWIG],[swig])
AC_SUBST(SWIGFLAGS)


AC_OUTPUT(Makefile
	  colmaps/Makefile
	  py/Makefile)
