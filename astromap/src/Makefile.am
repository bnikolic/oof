
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
			mapstructure.cxx mapstructure.hxx \
			fitting_basic.cxx fitting_basic.hxx\
			astromap_err.cxx astromap_err.hxx corrgaussnoise.cxx corrgaussnoise.hxx


libastromap_la_CFLAGS = -Wall   ${BN_CFLAGS} ${OPENMP_CFLAGS}
libastromap_la_CXXFLAGS = -Wall   ${BN_CFLAGS} ${OPENMP_CXXFLAGS}
libastromap_la_CPPFLAGS = -Wall ${BN_CFLAGS} ${BOOST_CPPFLAGS}

libastromap_la_LIBADD = -lfftw3_threads -lfftw3 ${BN_LIBS} \
			coordsys/libcoordsys.la \
			dataser/libdataser.la 

libastromap_la_LDFLAGS = ${OPENMP_CXXFLAGS} -Wl,--no-allow-shlib-undefined

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
			mapstructure.hxx\
			fitting_basic.hxx\
			astromap_err.hxx\
			corrgaussnoise.hxx

