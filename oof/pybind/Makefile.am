
include $(top_srcdir)/swig.am
EXTRA_DIST = swig.am

CLEANFILES = pyoof.py pyoof.cxx 

BUILT_SOURCES = pyoof.py pyoof.cxx 
nodist_bin_SCRIPTS = pyoof.py 

lib_LTLIBRARIES = _pyoof.la 

_pyoof_la_LDFLAGS = -module
_pyoof_la_LIBADD  = ../src/liboof.la ../src/aperture/liboofaperture.la ../src/farfield/libooffarfield.la ../src/telgeo/libtelgeo.la
_pyoof_la_SOURCES =  pyoof.i
nodist__pyoof_la_SOURCES = pyoof.cxx 
_pyoof_la_CPPFLAGS = @PYTHON_INCLUDES@ ${BN_CFLAGS} ${BOOST_CPPFLAGS}
