AC_INIT() 

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE(ASTROMAP, 0.01)

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AC_CHECK_LIB( [fftw] , [fftw2d_create_plan] )

AC_LANG_PUSH(C++)

AC_CHECK_HEADERS( bndebug.hxx , 
		  [echo "found bnlib"],
		  [echo "Error: No bnlib" ]  
		  )

AC_LANG_POP(C++)

AC_CONFIG_SUBDIRS([plot])	


AC_OUTPUT(Makefile 
          src/Makefile
	  src/coordsys/Makefile	
	  src/wcs/Makefile)

