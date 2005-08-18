
SUBDIRS = telgeo aperture farfield 

lib_LTLIBRARIES = liboof.la 

liboof_la_SOURCES = obsphasescreen.cxx obsphasescreen.hxx \
			obsdefocus.cxx obsdefocus.hxx \
			obscompare.cxx obscompare.hxx \
			maptoresidual.cxx maptoresidual.hxx\
			maptoresidual_ds.cxx maptoresidual_ds.hxx \
			obsfilefns.cxx obsfilefns.hxx

liboof_la_CFLAGS = -Wall
liboof_la_CPPFLAGS = -Wall 

liboof_la_LIBADD = -lastromap -lbnmin1 telgeo/libtelgeo.la aperture/liboofaperture.la \
			farfield/libooffarfield.la

