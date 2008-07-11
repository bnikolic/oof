# Bojan Nikolic <bojan@bnikolic.co.uk>
#

bin_PROGRAMS= t_units

t_units_SOURCES = t_units.cpp

LDADD=../src/libastromap.la  ${BOOST_UNIT_TEST_FRAMEWORK_LIB} 
INCLUDES=-I../src  ${BN_CFLAGS}
AM_CPPFLAGS= -DBOOST_TEST_DYN_LINK ${BOOST_CPPFLAGS}
AM_LDFLAGS= ${BOOST_LDFLAGS}
