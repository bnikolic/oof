/// Bojan Nikolic <bojan@bnikolic.co.uk>
/// 
/// Tests of the sets routines

#define BOOST_AUTO_TEST_MAIN

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <iostream>

#include "../config.h"

#include "sets/ellipsoids.hxx"

namespace ublas = boost::numeric::ublas;

BOOST_AUTO_TEST_CASE(InvertIdentity)
{
  ublas::identity_matrix<double> id(5);
  ublas::matrix<double> res(5,5);
  Minim::InvertLP(id, res);
  std::cout<<res;
}


