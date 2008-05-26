
SUBDIRS = f77

lib_LTLIBRARIES = libbnmin1.la 

libbnmin1_la_SOURCES = minimmodel.hxx minimmodel.cxx \
			paramctr.hxx \
			minim.hxx minim.cxx \
			pda.hxx \
			lmmin.hxx lmmin.cxx \
			monitor.cxx monitor.hxx \
			minimio.cxx minimio.hxx \
			lmminutils.cxx lmminutils.hxx\
			bnmin_main.cxx bnmin_main.hxx \
			metropolis.cxx metropolis.hxx

libbnmin1_la_LIBADD = f77/libminpda.la -lgsl  -lgslcblas

libbnmin1_la_CFLAGS = -Wall
libbnmin1_la_CPPFLAGS = -Wall

include_HEADERS = lmmin.hxx minim.hxx minimmodel.hxx paramctr.hxx pda.hxx monitor.hxx \
			minimio.hxx lmminutils.hxx bnmin_main.hxx
