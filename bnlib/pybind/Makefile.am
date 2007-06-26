
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pybnlib.py pybnlib.cxx 
bin_SCRIPTS =  pybnlib.py

dist_bin_SCRIPTS =  bin/kolmogorovutils.py

lib_LTLIBRARIES = _pybnlib.la 

_pybnlib_la_LDFLAGS = -module
_pybnlib_la_LIBADD  = ../src/libbnlib.la
_pybnlib_la_SOURCES = pybnlib.cxx pybnlib.i
_pybnlib_la_CPPFLAGS = @PYTHON_INCLUDES@
