include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am

SUBDIRS = colmaps py

lib_LTLIBRARIES = libastromapplot.la  _pyplot.la

BUILT_SOURCES = pyplot.py pyplot.cxx
nodist_bin_SCRIPTS =   pyplot.py 


libastromapplot_la_SOURCES=   plot.hxx plot.cxx \
				phelpers.hxx phelpers.cxx

libastromapplot_la_CPPFLAGS = -Wall -DCMAPDATADIR="$(datadir)" ${BN_CFLAGS} ${BOOST_CPPFLAGS}

#libastromapplot_la_LIBADD = ~/s/lib/libcpgplot.so

_pyplot_la_LDFLAGS = -module @X_LIBS@ -fopenmp
_pyplot_la_LIBADD  = ../src/libastromap.la \
			libastromapplot.la \
			-lpgplot -lcpgplot  -lX11 -lpng


_pyplot_la_SOURCES =  pyplot.i
nodist__pyplot_la_SOURCES = pyplot.cxx
_pyplot_la_CPPFLAGS = @PYTHON_INCLUDES@ ${BN_CFLAGS} ${BOOST_CPPFLAGS}





