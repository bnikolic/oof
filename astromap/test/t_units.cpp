/**
   \file t_units.cpp
   
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   
   Unit tests for AstroMap
*/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <boost/scoped_ptr.hpp>

#include "astromap.hxx"
#include "astromap_err.hxx"
#include "dataser/mapdseval.hxx"

using namespace AstroMap;

BOOST_AUTO_TEST_CASE(t_MkBiLinearCoeffs_runs)
{
  Map m(10,10);
  boost::scoped_ptr<MapPixLC> lc ( MkBiLinearCoeffs(1,1,m));
}

BOOST_AUTO_TEST_CASE(t_MkBiLinearCoeffs_correct_mid)
{
  Map m(10,10);
  boost::scoped_ptr<MapPixLC> lc ( MkBiLinearCoeffs(4.5,4.5,m));

  for (size_t i =0 ; i < 4 ; ++i)
  {
    BOOST_CHECK_EQUAL(lc->coeff[i], 0.25);
  }

  BOOST_CHECK_EQUAL(lc->index[0], 55);
}


BOOST_AUTO_TEST_CASE(t_MkBiLinearCoeffs_edge)
{
  Map m(10,10);

  {
    boost::scoped_ptr<MapPixLC> lc ( MkBiLinearCoeffs(0,0,m));
    for (size_t i =0 ; i < 4 ; ++i)
    {
      BOOST_CHECK(lc->index[i] >= 0);
    }
  }

  {
    BOOST_CHECK_THROW( boost::scoped_ptr<MapPixLC> lc ( MkBiLinearCoeffs(9,9,m)),
		       IndexingError);
  }

}

BOOST_AUTO_TEST_CASE(IndexingError_constructs)
{
  IndexingError e( 1,1, "test");
  BOOST_CHECK_EQUAL( std::string(e.what()),
		     "test at pixel (1,1) ");
}
