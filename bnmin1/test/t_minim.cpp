/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>

#include "minimmodel.hxx"
#include "quadmodel.hpp"
#include "lmmin.hxx"
#include "monitor.hxx"
#include "minimio.hxx"
#include "metropolis.hxx"
#include "priors.hxx"


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


BOOST_AUTO_TEST_CASE( Params_ByName )
{
  using namespace Minim;

  QuadModel qm;
  ModelDesc md(qm);
  
  BOOST_CHECK( md["a"]->p == &qm.a);
  BOOST_CHECK( md["c"]->p == &qm.c);
}

BOOST_AUTO_TEST_CASE( QuadPrior )
{
  using namespace Minim;
  using namespace boost::assign;

  const double params[]= { 1, 2, 3};

  // Abcissa values at which the quardratic function is "observed"
  std::vector<double> x;
  x +=  -1, 0 , 1;

  // Corresponding "observation"
  std::vector<double> obs(3);

  QuadModel qm;
  qm.a=params[0]; 
  qm.b=params[1]; 
  qm.c=params[2];
  qm.eval(x, obs);
  
  std::auto_ptr<QuadObs> qo (new QuadObs( x,obs));

  std::vector<double> scratch(3);
  qo->residuals(scratch);
  qo->sigma=0.01;

  IndependentFlatPriors qifp( qo.release() );
  std::vector<double> sigmas(3,0.1);

  qifp.AddPrior("a", -10,10);
  qifp.AddPrior("b", -10,10);
  qifp.AddPrior("c", -10,2);

  MetropolisMCMC metro(qifp,sigmas);
  boost::shared_ptr< std::list<Minim::MCPoint>  >
    res( metro.sample(10000)) ;

  BOOST_CHECK_CLOSE( res->back().p[2],
		     2.0,
		     1);

}

