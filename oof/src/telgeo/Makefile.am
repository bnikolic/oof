
lib_LTLIBRARIES = libtelgeo.la 

libtelgeo_la_SOURCES = telgeo.cxx telgeo.hxx \
			cassegrain.hxx cassegrain.cxx \
			tdzhelper.hxx \
			gbtgeo.cxx gbtgeo.hxx\
			telswitch.cxx telswitch.hxx \
			primefoc.cxx primefoc.hxx \
			paramgeo.cxx paramgeo.hxx

libtelgeo_la_CFLAGS = -Wall   ${BN_CFLAGS}
libtelgeo_la_CPPFLAGS = -Wall ${BN_CFLAGS}
libtelgeo_la_LIBADD = -lboost_regex
