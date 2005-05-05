 
lib_LTLIBRARIES = libbnlib.la 

libbnlib_la_SOURCES= interpolate.hxx interpolate.cxx \
			unaryfn.hxx \
	     		interpolategsl.hxx interpolategsl.cxx 

libbnlib_la_LIBADD = -lgsl -lgslcblas

include_HEADERS = 	unaryfn.hxx \
			interpolate.hxx \
			interpolate_forwd.hxx \
			interpolategsl.hxx
