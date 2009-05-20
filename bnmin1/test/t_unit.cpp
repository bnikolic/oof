/// Bojan Nikolic <bojan@bnikolic.co.uk>

#define BOOST_AUTO_TEST_MAIN

#include <limits>
#include <set>

#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/bind.hpp>
#include <boost/assign/list_of.hpp>

#include "metro_propose.hxx"
#include "priors.hxx"
#include "../src/pda.hxx"
#include "gradientminim.hxx"
#include "quadmodel.hpp"

#include "twoerrline_ml.hxx"

#include "mcpoint.hxx"
#include "nestedsampler.hxx"
#include "prior_sampler.hxx"

#include "mcmonitor.hxx"



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

BOOST_AUTO_TEST_CASE(FlatPrior_NoParam)
{
  std::vector<double> dummy;
  Minim::IndependentFlatPriors pr(new QuadObs(dummy,dummy));

  BOOST_CHECK_EQUAL(pr.llprob(), pr.lLikely());

  pr.AddPrior("c", 0,1);

  Minim::ModelDesc md(pr);
  md["c"]->setp(0.5);
  
  BOOST_CHECK_EQUAL(pr.pprob(), 0);

  md["c"]->setp(2);
  
  BOOST_CHECK(pr.pprob()> 1e5);
  

  BOOST_CHECK_THROW(pr.AddPrior("d", 0,1),
		    Minim::ParamError);
  
}



BOOST_AUTO_TEST_CASE(PDA_D1MACH)
{
  
  int i=3;
  double x = pda_d1mach__(&i);
  // Curiously this is a factor of two smaller than expected...
  BOOST_CHECK_EQUAL(x*2,
		    std::numeric_limits<double>::epsilon());
		    
}


BOOST_AUTO_TEST_CASE(BFGS2Minim_constructs)
{
  std::vector<double> x(5,1.0);
  std::vector<double> obs(5,2.0);
  
  QuadGrad qg(x,obs);
  Minim::BFGS2Minim m(qg);

}

BOOST_AUTO_TEST_CASE(LineTwoErrML_basics)
{

  std::vector<double> x(5,1.0);
  std::vector<double> obs(5,2.0);
  
  Minim::LineTwoErrML lml(x, obs,
			  0.1, 0.1);

  lml.a=0; lml.b=2;
  BOOST_CHECK_EQUAL(lml.lLikely(),0);
  
}

BOOST_AUTO_TEST_CASE(MCPoint_Less)
{
  Minim::MCPoint a,b;
  a.ll=10; b.ll=20;
  
  BOOST_CHECK( a<b);
  a.ll=30;
  BOOST_CHECK( b<a);

  std::set<Minim::MCPoint> ps;
  ps.insert(a);
  ps.insert(b);
  
  BOOST_CHECK_EQUAL(ps.begin()->ll,
		    20);
}

BOOST_AUTO_TEST_CASE(llPoint_Wrks)
{
  std::vector<double> dummy;
  Minim::IndependentFlatPriors pr(new QuadObs(dummy,
					      dummy));
  pr.AddPrior("c", 0,1);


  Minim::MCPoint p1; 
  p1.p=boost::assign::list_of(0.5)(0.5)(0.5);

  Minim::MCPoint p2; 
  p2.p=boost::assign::list_of(0.5)(0.5)(0.5);

  std::list<Minim::MCPoint> lp;
  lp.push_back(p1); 
  lp.push_back(p2);

  std::set<Minim::MCPoint> res;
  
  llPoint(pr, lp, res);

  BOOST_CHECK_EQUAL(res.begin()->ll,0);
  
}

BOOST_AUTO_TEST_CASE(prior_sampler_constr)
{
  std::vector<double> dummy;
  Minim::IndependentFlatPriors pr(new QuadObs(dummy,
					      dummy));
  std::vector<double> sigs(3, 0.1);
  Minim::CPriorSampler a(pr, sigs);
		
}

BOOST_AUTO_TEST_CASE(SOutMCMon_tprint)
{
  Minim::SOutMCMon t;
  Minim::MCPoint p;
  p.p.push_back(10);
  t.accept(p);
}
