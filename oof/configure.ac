
AC_INIT()

AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE(OOF, 1.0.1)

AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


AC_PROG_CC
AC_PROG_CXX

AC_CONFIG_SUBDIRS([pybind])	

AC_LANG_PUSH(C++)

AC_CHECK_HEADERS( astromap.hxx , 
		  [echo "found AstroMap"],
		  [echo "Error: No AstroMap!!!" ]  
		  )

AC_CHECK_HEADERS( minimmodel.hxx , 
		  [echo "found BNMinim "],
		  [echo "Error: No BNMinim  !!!" ]  
		  )

AC_LANG_POP(C++)

AC_OUTPUT(Makefile
	  src/Makefile
	  src/aperture/Makefile 
	  src/telgeo/Makefile
	  src/farfield/Makefile
	  doc/Doxyfile)




	
