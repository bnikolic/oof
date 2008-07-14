/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/bind.hpp>

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

void RecPars( const QuadModel & qm,
	      std::vector<double> &x)
{
  x.resize(1);
  x[0]=qm.a;
}

BOOST_AUTO_TEST_CASE( QuadMetro )
{
  using namespace Minim;

  const double params[]= { 1, 2, 3};

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=params[0]; 
  qm.b=params[1]; 
  qm.c=params[2];
  qm.eval(x, obs);
  
  QuadObs qo ( x,obs);

  std::vector<double> scratch(3);
  qo.residuals(scratch);
  qo.sigma=0.01;

  std::vector<double> sigmas(3,0.1);

  MetropolisMCMC metro(qo,sigmas);
  metro.f=boost::bind( RecPars, qm, _1);
  
  boost::shared_ptr< std::list<Minim::MCPoint>  >
    res( metro.sample(10000)) ;

  for (size_t i = 0 ; i < sigmas.size(); ++i)
  {
    BOOST_CHECK_CLOSE( res->back().p[i],
		       params[i],
		       1);
  }

  BOOST_CHECK_CLOSE( res->back().fval[0],
		     params[0],
		     1);



}

BOOST_AUTO_TEST_CASE( QuadMetro_Seq )
{
  using namespace Minim;

  const double params[]= { 1, 2, 3};

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=params[0]; 
  qm.b=params[1]; 
  qm.c=params[2];
  qm.eval(x, obs);
  
  QuadObs qo ( x,obs);

  std::vector<double> scratch(3);
  qo.residuals(scratch);
  qo.sigma=0.01;

  std::vector<double> sigmas(3,0.1);

  MetropolisMCMC metro(qo,sigmas,33, MetropolisMCMC::Sequence);
  metro.f=boost::bind( RecPars, qm, _1);
  
  boost::shared_ptr< std::list<Minim::MCPoint>  >
    res( metro.sample(30000)) ;

  for (size_t i = 0 ; i < sigmas.size(); ++i)
  {
    BOOST_CHECK_CLOSE( res->back().p[i],
		       params[i],
		       1);
  }

  BOOST_CHECK_CLOSE( res->back().fval[0],
		     params[0],
		     1);



}


