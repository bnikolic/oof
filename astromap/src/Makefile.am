
SUBDIRS = wcs coordsys dataser


lib_LTLIBRARIES = libastromap.la 

libastromap_la_SOURCES= astromap.cxx astromap.hxx \
			fft.cxx fft.hxx \
			mapops.hxx mapops.cxx \
			mapset.cxx mapset.hxx tmapset.hxx \
			pixextract.hxx pixextract.cxx \
			lcmaps.hxx lcmaps.cxx \
			astromapio.cxx astromapio.hxx \
			convolve.cxx convolve.hxx \
			mapregions.cxx mapregions.hxx \
			pixiterators.cxx pixiterators.hxx \
			pixalgo.cxx pixalgo.hxx \
			fresneltrans.cxx fresneltrans.hxx \
			mapstructure.cxx mapstructure.hxx


libastromap_la_CFLAGS = -Wall
libastromap_la_CPPFLAGS = -Wall

libastromap_la_LIBADD = -lfftw -lbnlib -lbnfits coordsys/libcoordsys.la \
			dataser/libdataser.la -lbnfits

include_HEADERS = 	astromap.hxx mapops.hxx \
			mapset.hxx tmapset.hxx	 \
			pixextract.hxx \
			lcmaps.hxx \
			fft.hxx \
			astromap_fwd.hxx \
			astromapio.hxx \
			convolve.hxx \
			mapregions.hxx \
			pixiterators.hxx \
			pixalgo.hxx \
			fresneltrans.hxx\
			mapstructure.hxx

