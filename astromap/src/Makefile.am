
SUBDIRS = wcs coordsys


lib_LTLIBRARIES = libastromap.la 

libastromap_la_SOURCES= astromap.cxx astromap.hxx \
			fft.cxx fft.hxx \
			mapops.hxx mapops.cxx \
			mapset.cxx mapset.hxx tmapset.hxx

libastromap_la_CFLAGS = -Wall
libastromap_la_CPPFLAGS = -Wall

libastromap_la_LIBADD = -lfftw -lbnlib coordsys/libcoordsys.la

include_HEADERS = 	astromap.hxx mapops.hxx \
			mapset.hxx tmapset.hxx	


