
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pybnfits.py pybnfits.cxx 
bin_SCRIPTS =   pybnfits.py bin/bnfitsutils.py

lib_LTLIBRARIES = _pybnfits.la 

_pybnfits_la_LDFLAGS = -module
_pybnfits_la_LIBADD  = ../src/libbnfits.la
_pybnfits_la_SOURCES = pybnfits.cxx pybnfits.i
_pybnfits_la_CPPFLAGS = @PYTHON_INCLUDES@
