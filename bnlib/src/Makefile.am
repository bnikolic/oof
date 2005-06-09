 
lib_LTLIBRARIES = libbnlib.la 

libbnlib_la_SOURCES= interpolate.hxx interpolate.cxx \
			unaryfn.hxx \
	     		interpolategsl.hxx interpolategsl.cxx \
			integrate.cxx integrate.hxx \
			phyconstants.hxx phyconstants.cxx \
			phyfunc.hxx phyfunc.cxx\
			linraster.hxx linraster.cxx \
			onedmin.hxx onedmin.cxx \
			bndebug.hxx

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
			bndebug.hxx
