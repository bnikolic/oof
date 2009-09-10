/**
   \file nestedgauss.hpp

   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   
   Nested sampling exploration of the simple gaussian model, for
   testing purposes
*/

#include "minimmodel.hxx"
#include "gaussmodel.hpp"
#include "nestedsampler.hxx"
#include "mcmonitor.hxx"
#include "priors.hxx"

struct desc {
  boost::shared_ptr<Minim::IndependentFlatPriors> obs;
  boost::shared_ptr<Minim::NestedS> s;
  boost::shared_ptr<Minim::SOutMCMon> mon;
};

desc mkDesc(double l_sigma,
	    bool monitor)
{
  using namespace Minim;
  GaussObs *gp = new GaussObs(3);
  gp->sigma=l_sigma;

  desc res;
  res.obs=boost::shared_ptr<IndependentFlatPriors>(new  IndependentFlatPriors(gp));

  res.obs->AddPrior("p0", -1.01,1.01);
  res.obs->AddPrior("p1", -1.01,1.01);
  res.obs->AddPrior("p2", -1.01,1.01);
  
  std::list<Minim::MCPoint> startset;

  startSetDirect(*res.obs,
		 20,
		 startset);

  std::vector<double> sigmas(3,0.1);

  res.s=boost::shared_ptr<NestedS>(new NestedS(*res.obs,
					       startset,
					       sigmas));

  if (monitor)
  {
    SOutMCMon *pp=new SOutMCMon();
    res.s->mon=pp;
    res.mon=boost::shared_ptr<SOutMCMon>(pp);
  }
  return res;
};

double getEvidence(double l_sigma,
		   size_t nsample,
		   bool monitor)
{

  using namespace Minim;
  GaussObs *gp = new GaussObs(3);
  gp->sigma=l_sigma;
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

  if (monitor)
  {
    s.mon=new SOutMCMon();
  }
  
  const double res=s.sample(nsample);

  delete s.mon;

  return res;
};



