AC_INIT(ASTROMAP, 
        1.1 , 
	"Bojan Nikolic" <bojan@bnikolic.co.uk> )  

AC_CONFIG_AUX_DIR(config)

AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE()

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX


AC_CHECK_HEADER( fftw.h,
		 [echo "found fftw version 2" ],
		 [AC_MSG_ERROR([Requires FFTW version 2] ) ] )

AC_LANG_PUSH(C++)

AC_CHECK_HEADERS( bndebug.hxx , 
		  [echo "found bnlib"],
		  [echo "Error: No bnlib" ]  
		  )

AC_CHECK_HEADERS( fitswrap.hxx , 
		  [echo "found bnfits"],
		  [echo "Error: No bnfits" ]  
		  )

AC_CHECK_HEADERS( minimmodel.hxx , 
		  [echo "Found minimisation library, will build fitting routines "]
		  )

AC_LANG_POP(C++)

AM_CONDITIONAL([HAVEBNMIN1], 
               [test x$ac_cv_header_minimmodel_hxx = xyes])

AC_CONFIG_SUBDIRS([plot])	


AC_OUTPUT(Makefile 
          src/Makefile
	  src/coordsys/Makefile	
	  src/dataser/Makefile	
	  src/wcs/Makefile
	  doc/Doxyfile)

