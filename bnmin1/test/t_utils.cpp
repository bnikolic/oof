/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include "paramalgo.hxx"

BOOST_AUTO_TEST_CASE( findName_NULL )
{
  using namespace Minim;
  
  std::vector<DParamCtr> pv1;
  BOOST_CHECK( findName(pv1, "x")== NULL);

  double x;
  pv1.push_back( DParamCtr(&x, "xx", true, ""));
  BOOST_CHECK( findName(pv1, "x")== NULL);
  
}
