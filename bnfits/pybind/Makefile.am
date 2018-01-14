
include $(top_srcdir)/config/swig.am
EXTRA_DIST = config/swig.am


BUILT_SOURCES = pybnfits.py pybnfits.cxx 
dist_bin_SCRIPTS =   pybnfits.py bin/bnfitsutils.py bin/iofits4.py

lib_LTLIBRARIES = _pybnfits.la 

_pybnfits_la_LDFLAGS = -module
_pybnfits_la_LIBADD  = ../src/libbnfits.la
_pybnfits_la_SOURCES = pybnfits.i
nodist__pybnfits_la_SOURCES = pybnfits.cxx
_pybnfits_la_CPPFLAGS = @PYTHON_INCLUDES@
