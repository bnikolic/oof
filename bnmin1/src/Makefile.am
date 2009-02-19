
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
			metropolis.cxx metropolis.hxx\
			metro_propose.cxx metro_propose.hxx\
			priors.cxx priors.hxx\
			paramalgo.cxx paramalgo.hxx \
			gradientmodel.cxx gradientmodel.hxx\
			gradientminim.cxx gradientminim.hxx \
			robustline.cxx robustline.hxx

libbnmin1_la_LIBADD = f77/libminpda.la  $(GSL_LIBS)

libbnmin1_la_CFLAGS = -Wall $(GSL_CFLAGS)
libbnmin1_la_CPPFLAGS = -Wall $(GSL_CFLAGS)

include_HEADERS = lmmin.hxx minim.hxx minimmodel.hxx paramctr.hxx pda.hxx monitor.hxx \
			minimio.hxx lmminutils.hxx bnmin_main.hxx priors.hxx metropolis.hxx \
			gradientmodel.hxx gradientminim.hxx robustline.hxx
