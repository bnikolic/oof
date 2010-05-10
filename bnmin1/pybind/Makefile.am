
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pybnmin1.py pybnmin1.cxx 
dist_bin_SCRIPTS = pybnmin1.py bin/bnmin1io.py bin/bnmin1utils.py	\
	           bin/bnmin1nested.py bin/bnmin1tables.py

lib_LTLIBRARIES = _pybnmin1.la 

_pybnmin1_la_LDFLAGS = -module
_pybnmin1_la_LIBADD  = ../src/libbnmin1.la
_pybnmin1_la_SOURCES = pybnmin1.i
nodist__pybnmin1_la_SOURCES = pybnmin1.cxx 
_pybnmin1_la_CPPFLAGS = @PYTHON_CPPFLAGS@  ${BOOST_CPPFLAGS}
