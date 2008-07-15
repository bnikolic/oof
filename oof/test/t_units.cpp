/**
   \file t_units.cpp
   
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   
   Unit tests for OOF
*/

#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <boost/scoped_ptr.hpp>

#include "oof_err.hxx"


#include "aperture/aperturemod.hxx"
#include "aperture/multi_apmod.hxx"
#include "aperture/gaussampmod.hxx"
#include "aperture/zernmodel.hxx"
#include "telgeo/telswitch.hxx"
#include "telgeo/telgeo.hxx"
#include "astromap.hxx"


using namespace OOF;

BOOST_AUTO_TEST_CASE(t_empty)
{

}

BOOST_AUTO_TEST_CASE(t_NObsError_runs)
{
  NObsError(1,2,"test");
}

BOOST_AUTO_TEST_CASE(t_ApertureMod_nmod)
{
  AstroMap::Map m1(128,128);

  boost::scoped_ptr<TelGeometry> tel(MkALMA());
  
  ApertureMod am( new RZernModel(1,m1,tel.get()),
		  new GaussAmpMod(tel.get(),m1),
		  1.0,
		  m1);
  
  BOOST_CHECK_EQUAL( am.getphase(),
		     am.getPhase(3));

  BOOST_CHECK_EQUAL( am.getamp(),
		     am.getAmp(3));
  

}

BOOST_AUTO_TEST_CASE(t_MultiAmp_ApModel_basic)
{
  AstroMap::Map m1(128,128);

  boost::scoped_ptr<TelGeometry> tel(MkALMA());
  
  MultiAmp_ApModel am( new RZernModel(1,m1,tel.get()),
		       new GaussAmpMod(tel.get(),m1),
		       1.0,
		       m1,
		       3);

  BOOST_CHECK_EQUAL(am.getAR(1), 1.0);

  am.getAmp(0);am.getAmp(1);am.getAmp(2);
  BOOST_CHECK_THROW(am.getAmp(3),
		    NObsError);
}
