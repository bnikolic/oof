AC_PREREQ(2.59)

AC_COPYRIGHT(Bojan Nikolic)
AC_REVISION($Id$)

AC_INIT([pybnlib] , [0.01])

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE()

AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AM_PATH_GSL(1.5,
	[AC_DEFINE([BN_HAVE_GSL], [1] ,  [Define if GSLv1.5 exists.])],
	AC_MSG_WARN(Tested version of GSL not found, but you might be OK anyway) )

AM_PATH_PYTHON(2.4)

AM_CHECK_PYTHON_HEADERS()

AC_PROG_SWIG(1.3.31)

AC_OUTPUT(Makefile)


