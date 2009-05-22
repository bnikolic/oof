/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>

#include "minimmodel.hxx"
#include "quadmodel.hpp"
#include "gaussmodel.hpp"
#include "lmmin.hxx"
#include "monitor.hxx"
#include "minimio.hxx"
#include "metropolis.hxx"
#include "priors.hxx"
#include "gradientminim.hxx"
#include "robustline.hxx"
#include "twoerrline_ml.hxx"
#include "nestedsampler.hxx"
#include "mcmonitor.hxx"


BOOST_AUTO_TEST_CASE( Initialisation )
{
  using namespace Minim;
  Model m;
}

QuadObs * mkStdObs(void)
{
  using namespace Minim;

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=1; qm.b=2; qm.c=3;
  qm.eval(x, obs);
  
  return new QuadObs( x,obs);

}

BOOST_AUTO_TEST_CASE( QuadT1 )
{
  using namespace Minim;

  boost::scoped_ptr<QuadObs> qo(mkStdObs());

  std::vector<double> scratch(3);
  qo->residuals(scratch);

  LMMin minimiser(*qo);
  minimiser.ftol=minimiser.xtol=minimiser.gtol=1e-5;
  ChiSqMonitor mon;
  minimiser.AddMon(&mon);
  minimiser.solve();

  PrettyPrint(minimiser);

  BOOST_CHECK_EQUAL( qo->qm.a,
		     1);

  BOOST_CHECK_EQUAL( qo->qm.b,
		     2);

  BOOST_CHECK_EQUAL( qo->qm.c,
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

BOOST_AUTO_TEST_CASE(GaussObs_Metro)
{
  using namespace Minim;
  
  GaussObs go(3);
  go.p[0]=10; 
  go.p[1]=0;
  go.p[2]=0;
  std::vector<double> sigmas(3,0.1);
  
  MetropolisMCMC metro(go,sigmas);  

  boost::shared_ptr< std::list<Minim::MCPoint>  >
    res( metro.sample(10000)) ;

  for (size_t i = 0; i < sigmas.size(); ++i)
  {
    BOOST_CHECK(fabs(res->back().p[i]) < 3);
  }  
  


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


BOOST_AUTO_TEST_CASE(BFGS2Minim_QuadRes)
{
  using namespace Minim;

  std::vector<double> x(3);
  x[0]=-1; x[1]=0; x[2]=1;
  
  std::vector<double> obs(3);
  QuadModel qm;
  qm.a=1; qm.b=2; qm.c=3;
  qm.eval(x, obs);

  BOOST_CHECK(obs[2] != 0);  

  std::vector<double> g(3);
  qm.grad(0, g);
  BOOST_CHECK_EQUAL(g[0], 1);
  BOOST_CHECK(g[1] == 0);

  
  QuadGrad qg(x,obs);
  BFGS2Minim m(qg);

  BOOST_CHECK(qg.lLikely() > 0);
  std::vector<double> scratch;
  qg.lGrd(scratch);


  BOOST_CHECK(scratch.size() == 3);  
  BOOST_CHECK(scratch[2] != 0);  
  BOOST_CHECK(scratch[0] != 0);  
  BOOST_CHECK(scratch[1] != 0);  

  m.solve();

  BOOST_CHECK_CLOSE(qg.qm.a,
		    1.0,
		    1e-3);

  BOOST_CHECK_CLOSE(qg.qm.b,
		    2.0,
		    1e-3);

  BOOST_CHECK_CLOSE(qg.qm.c,
		    3.0,
		    1e-3);

}


BOOST_AUTO_TEST_CASE(t_RobustLineObsMod)
{
  
  std::vector<double> xvals = boost::assign::list_of(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);  
  std::vector<double> yvals = boost::assign::list_of(1)(2)(3)(4)(5)(6)(7)(80)(9)(10);  

  Minim::RobustLineObsMod rom(xvals, yvals);
  rom.a=0;
  rom.b=0;

  BOOST_CHECK_CLOSE(rom.lLikely(),
		    127.0,
		    1e-10);  

  std::vector<double> grad;
  rom.lGrd(grad);
  BOOST_CHECK_CLOSE(grad[1],
		    -10.0,
		    1e-10);  

  BOOST_CHECK_CLOSE(grad[0],
		    -55.0,
		    1e-10);  
  

  for(size_t i=0; i<1; ++i)
  {
    rom.a=0;
    rom.b=0;  
    Minim::BFGS2Minim m(rom);
    m.solve();
  }


  BOOST_CHECK_CLOSE(rom.a,
		    1.0,
		    5);  

  BOOST_CHECK_CLOSE(rom.b,
		    0.17,
		    5);  

  BOOST_CHECK_CLOSE(rom.lLikely(),
		    72.0,
		    1);  
  

}

BOOST_AUTO_TEST_CASE(t_LineTwoErrML)
{

  /**
  std::vector<double> x(10), obs(10);
  for (size_t i=0; i <x.size(); ++i)
  {
    x[i]=i;
    obs[i]=i;
  }
  */
  std::vector<double> x=boost::assign::list_of(1)(2);
  std::vector<double> obs=boost::assign::list_of(1)(2);

  Minim::LineTwoErrML lml(x, obs,
			  1.0, 1.0);
  lml.a=1.0;
  lml.b=1.0;

  Minim::BFGS2Minim m(lml);
  m.solve();
  
  BOOST_CHECK_CLOSE(lml.a, 1.0, 1e-2);  
  BOOST_CHECK_CLOSE(1+lml.b, 1.0, 1e-2);  
  
}

BOOST_AUTO_TEST_CASE(t_LineTwoErr_LavMarq)
{
  std::vector<double> x=boost::assign::list_of(1)(2);
  std::vector<double> obs=boost::assign::list_of(1)(2);

  Minim::LineTwoErr_LavMarq lml(x, obs,
				1.0, 1.0);
  Minim::LMMin m(lml);
  m.ftol=m.xtol=m.gtol=1e-5;
  Minim::ChiSqMonitor mon;
  m.AddMon(&mon);
  m.solve();

  const double ra=m.getbyname("a")->getp();
  BOOST_CHECK_CLOSE(ra, 1.0, 1e-2);  
  BOOST_CHECK_CLOSE(1+m.getbyname("b")->getp(), 1.0, 1e-2);  
  
}



BOOST_AUTO_TEST_CASE(t_NestedSampling_Gauss)
{  
  using namespace Minim;
  GaussObs *gp = new GaussObs(3);
  gp->sigma=1.0;
  IndependentFlatPriors obs(gp);


  obs.AddPrior("p0", -1.01,1.01);
  obs.AddPrior("p1", -1.01,1.01);
  obs.AddPrior("p2", -1.01,1.01);
  
  std::list<Minim::MCPoint> startset;

  startSetDirect(obs,
		 20,
		 startset);

  std::vector<double> sigmas(3,0.1);

  NestedS s(obs,
	    startset,
	    sigmas);
  
  s.mon=new SOutMCMon();
  
  const double res=s.sample(150);

  BOOST_CHECK_CLOSE(res, 
		    // Note pre-factor 8 cancels with 1/2 inside power
		    pow(erf(gp->sigma/sqrt(2)),3) ,
		    40);
  delete s.mon;

	  
}

BOOST_AUTO_TEST_CASE(t_NestedSampling)
{  
  using namespace Minim;
  IndependentFlatPriors obs(mkStdObs());
  
  std::list<Minim::MCPoint> startset;
  Minim::MCPoint p; 

  p.p=boost::assign::list_of(0)(0)(0);
  startset.push_back(p);

  p.p=boost::assign::list_of(2)(0)(0);
  startset.push_back(p);

  p.p=boost::assign::list_of(0)(1)(5);
  startset.push_back(p);

  p.p=boost::assign::list_of(3)(1)(10);
  startset.push_back(p);

  p.p=boost::assign::list_of(-3)(2)(10);
  startset.push_back(p);
  
  std::vector<double> sigmas(3,0.1);

  NestedS s(obs,
	    startset,
	    sigmas);
  
  const double res=s.sample(30);

  //BOOST_CHECK_CLOSE(res,0.0, 10);
	  
}

