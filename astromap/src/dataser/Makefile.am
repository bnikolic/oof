

lib_LTLIBRARIES = libdataser.la 

libdataser_la_SOURCES= dataseries.hxx dataseries.cxx datapoint.cxx	\
			datapoint.hxx dsfileops.cxx dsfileops.hxx	\
			 dstomap.hxx dstomap.cxx mapdseval.cxx		\
			mapdseval.hxx mapdsutils.cxx mapdsutils.hxx	\
			mapdseval_flat.hxx mapdseval_flat.cxx


libdataser_la_CFLAGS = -Wall   ${BN_CFLAGS}
libdataser_la_CPPFLAGS = -Wall ${BN_CFLAGS}

libdataser_la_LIBADD = 

include_HEADERS = dataseries.hxx datapoint.hxx dsfileops.hxx		\
	        	 dstomap.hxx mapdseval.hxx mapdsutils.hxx	\
	        	mapdseval_flat.hxx
