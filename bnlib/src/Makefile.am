SUBDIRS = kolmog

lib_LTLIBRARIES = libbnlib.la 

libbnlib_la_SOURCES= interpolate.hxx interpolate.cxx \
			unaryfn.hxx \
	     		interpolategsl.hxx interpolategsl.cxx \
			integrate.cxx integrate.hxx \
			phyconstants.hxx phyconstants.cxx \
			phyfunc.hxx phyfunc.cxx\
			phycosmo.cxx phycosmo.hxx \
			linraster.hxx linraster.cxx \
			onedmin.hxx onedmin.cxx \
			onedroot.cxx onedroot.hxx	 \
			oneddiff.cxx oneddiff.hxx \
			bndebug.hxx \
			bnrandom.hxx bnrandom.cxx \
			binaryfn.hxx \
			zernikepoly.hxx zernikepoly.cxx \
			gaussian.cxx gaussian.hxx \
			gsl_utils.cxx gsl_utils.hxx \
			interpolatelog.cxx interpolatelog.hxx \
			tophat.cxx tophat.hxx \
			integrateutils.cxx integrateutils.hxx\
			unaryfnutils.cxx unaryfnutils.hxx\
			quadratic_bfn.cxx quadratic_bfn.hxx \
			bnlib_main.cxx bnlib_main.hxx


libbnlib_la_CFLAGS = -Wall $(GSL_CFLAGS)
libbnlib_la_CPPFLAGS = -Wall $(GSL_CFLAGS)

libbnlib_la_LIBADD = $(GSL_LIBS) kolmog/libbnlibkolmog.la 

include_HEADERS = 	unaryfn.hxx \
			interpolate.hxx \
			interpolate_forwd.hxx \
			interpolategsl.hxx \
			integrate.hxx\
			phyconstants.hxx\
			phyfunc.hxx \
			phycosmo.hxx \
			linraster.hxx \
			onedmin.hxx \
			oneddiff.hxx \
			onedroot.hxx \
			bndebug.hxx \
			bnrandom.hxx \
			binaryfn.hxx	\
			zernikepoly.hxx \
			gaussian.hxx \
			gsl_utils.hxx \
			interpolatelog.hxx\
			tophat.hxx\
			integrateutils.hxx\
			unaryfnutils.hxx \
			quadratic_bfn.hxx\
			bnlib_main.hxx
