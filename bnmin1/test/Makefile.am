# Bojan Nikolic <bojan@bnikolic.co.uk>

bin_PROGRAMS= t_minim

t_minim_SOURCES = t_minim.cpp

LDADD=../src/libbnmin1.la ${BOOST_UNIT_TEST_FRAMEWORK_LIB}
INCLUDES=-I../src 
AM_CPPFLAGS= -DBOOST_TEST_DYN_LINK ${BOOST_CPPFLAGS}
AM_LDFLAGS=${BOOST_LDFLAGS}
