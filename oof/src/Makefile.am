
SUBDIRS = telgeo aperture farfield 

lib_LTLIBRARIES = liboof.la 

liboof_la_SOURCES = obsphasescreen.cxx obsphasescreen.hxx \
			obsdefocus.cxx obsdefocus.hxx \
			obscompare.cxx obscompare.hxx \
			maptoresidual.cxx maptoresidual.hxx\
			maptoresidual_ds.cxx maptoresidual_ds.hxx \
			obsfilefns.cxx obsfilefns.hxx \
			oof_main.cxx oof_main.hxx \
			oof_err.cxx oof_err.hxx

liboof_la_CFLAGS = -Wall   ${BN_CFLAGS}
liboof_la_CPPFLAGS = -Wall ${BN_CFLAGS}

liboof_la_LIBADD = ${BN_LIBS} telgeo/libtelgeo.la aperture/liboofaperture.la \
			farfield/libooffarfield.la

