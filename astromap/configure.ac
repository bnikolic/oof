AC_INIT(ASTROMAP, 
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

PKG_CHECK_MODULES([BN], [bnlib >= 1.1 bnfits >= 1.2])


AC_CHECK_HEADER( fftw.h,
		 [echo "found fftw version 2" ],
		 [AC_MSG_ERROR([Requires FFTW version 2] ) ] )

AC_LANG_PUSH(C++)

AC_CHECK_HEADERS( minimmodel.hxx , 
		  [echo "Found minimisation library, will build fitting routines "]
		  )

AC_LANG_POP(C++)

AM_CONDITIONAL([HAVEBNMIN1], 
               [test x$ac_cv_header_minimmodel_hxx = xyes])

AX_BOOST(1.34.0,
	[echo "GOOD: You have BOOST ... we will be using that!" ],		     
	AC_MSG_ERROR(["ERROR: No BOOST  ... ; you can find it at  http://www.boost.org/ "])  )


AC_CONFIG_SUBDIRS([plot])	


AC_OUTPUT(Makefile 
          src/Makefile
	  src/coordsys/Makefile	
	  src/dataser/Makefile	
	  src/wcs/Makefile
	  doc/Doxyfile
	  astromap.pc
	  test/Makefile)

