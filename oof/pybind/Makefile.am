
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pyoof.py pyoof.cxx 
bin_SCRIPTS = pyoof.py 

lib_LTLIBRARIES = _pyoof.la 

_pyoof_la_LDFLAGS = -module
_pyoof_la_LIBADD  = ../src/liboof.la
_pyoof_la_SOURCES = pyoof.cxx pyoof.i
_pyoof_la_CPPFLAGS = @PYTHON_INCLUDES@
