/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>

#include "metro_propose.hxx"

BOOST_AUTO_TEST_CASE( MetroPropose_raccept )
{
  
  std::vector<double> sigmas(0);
  //  sigmas= boost::assign::list_of(1)(1)(1)(1);
  Minim::MetroPropose mp(sigmas, 1);

  for (size_t i =0 ; i < 100 ; ++i)
  {
    BOOST_CHECK ( mp.raccept() >=0 );
    BOOST_CHECK ( mp.raccept() <=1 );
  }
}

BOOST_AUTO_TEST_CASE( MetroProposeSeq_displace )
{
  
  std::vector<double> sigmas(4,1.0);
  {
    Minim::MetroPropose mp(sigmas, 1);
    std::vector<double> x(4,0);
    mp.displace(x); mp.displace(x); 
    BOOST_CHECK ( x[2] !=0);
    BOOST_CHECK ( x[3]!=0);
  }


  {
    Minim::MetroProposeSeq mps(sigmas, 1);
    std::vector<double> x(4,0);
    mps.displace(x); mps.displace(x); 
    BOOST_CHECK_EQUAL ( x[2],0);
    BOOST_CHECK_EQUAL ( x[3],0);
  }

}



