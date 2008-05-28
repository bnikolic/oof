/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>

#include "minimmodel.hxx"
#include "quadmodel.hpp"
#include "lmmin.hxx"
#include "monitor.hxx"
#include "minimio.hxx"
#include "metropolis.hxx"


BOOST_AUTO_TEST_CASE( Initialisation )
{
  using namespace Minim;
  Model m;
}

BOOST_AUTO_TEST_CASE( QuadT1 )
{
  using namespace Minim;

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=1; qm.b=2; qm.c=3;
  qm.eval(x, obs);
  
  QuadObs qo ( x,obs);

  std::vector<double> scratch(3);
  qo.residuals(scratch);

  LMMin minimiser(qo);
  ChiSqMonitor mon;
  minimiser.AddMon(&mon);
  minimiser.solve();

  PrettyPrint(minimiser);

  BOOST_CHECK_EQUAL( qo.qm.a,
		     1);

  BOOST_CHECK_EQUAL( qo.qm.b,
		     2);

  BOOST_CHECK_EQUAL( qo.qm.c,
		     3);

}

BOOST_AUTO_TEST_CASE( QuadMetro )
{
  using namespace Minim;

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=1; qm.b=2; qm.c=3;
  qm.eval(x, obs);
  
  QuadObs qo ( x,obs);

  std::vector<double> scratch(3);
  qo.residuals(scratch);

  std::vector<double> sigmas(3,0.1);

  MetropolisMCMC metro(qo,sigmas);
  metro.sample(1000);



}


