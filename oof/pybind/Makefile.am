
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pyoof.py pyoof.cxx 
nodist_bin_SCRIPTS = pyoof.py 

lib_LTLIBRARIES = _pyoof.la 

_pyoof_la_LDFLAGS = -module
_pyoof_la_LIBADD  = ../src/liboof.la
_pyoof_la_SOURCES =  pyoof.i
nodist__pyoof_la_SOURCES = pyoof.cxx 
_pyoof_la_CPPFLAGS = @PYTHON_INCLUDES@
