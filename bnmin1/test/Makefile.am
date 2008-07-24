# Bojan Nikolic <bojan@bnikolic.co.uk>

bin_PROGRAMS= t_minim t_unit t_utils

t_minim_SOURCES = t_minim.cpp quadmodel.hpp
t_unit_SOURCES = t_unit.cpp
t_utils_SOURCES = t_utils.cpp

LDADD=../src/libbnmin1.la ${BOOST_UNIT_TEST_FRAMEWORK_LIB}
INCLUDES=-I../src 
AM_CPPFLAGS= -DBOOST_TEST_DYN_LINK ${BOOST_CPPFLAGS}
AM_LDFLAGS=${BOOST_LDFLAGS}
