
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pybnmin1.py pybnmin1.cxx 
bin_SCRIPTS = pybnmin1.py  bin/bnmin1io.py

lib_LTLIBRARIES = _pybnmin1.la 

_pybnmin1_la_LDFLAGS = -module
_pybnmin1_la_LIBADD  = ../src/libbnmin1.la
_pybnmin1_la_SOURCES = pybnmin1.cxx pybnmin1.i
_pybnmin1_la_CPPFLAGS = @PYTHON_INCLUDES@
