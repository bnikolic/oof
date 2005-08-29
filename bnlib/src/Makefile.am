 
lib_LTLIBRARIES = libbnlib.la 

libbnlib_la_SOURCES= interpolate.hxx interpolate.cxx \
			unaryfn.hxx \
	     		interpolategsl.hxx interpolategsl.cxx \
			integrate.cxx integrate.hxx \
			phyconstants.hxx phyconstants.cxx \
			phyfunc.hxx phyfunc.cxx\
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
			interpolatelog.cxx interpolatelog.hxx

libbnlib_la_CFLAGS = -Wall
libbnlib_la_CPPFLAGS = -Wall

libbnlib_la_LIBADD = -lgsl -lgslcblas

include_HEADERS = 	unaryfn.hxx \
			interpolate.hxx \
			interpolate_forwd.hxx \
			interpolategsl.hxx \
			integrate.hxx\
			phyconstants.hxx\
			phyfunc.hxx \
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
			interpolatelog.hxx
