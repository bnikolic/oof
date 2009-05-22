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

double getEvidence(double l_sigma,
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
  
  const double res=s.sample(150);

  delete s.mon;

  return res;
};



