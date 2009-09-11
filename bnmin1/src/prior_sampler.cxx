/**
   \file prior_sampler.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "prior_sampler.hxx"

#include "priors.hxx"
#include "metro_propose.hxx"
#include "bnmin_main.hxx"
#include "mcpoint.hxx"
#include "mcmonitor.hxx"

namespace Minim
{
  
  CPriorSampler::CPriorSampler(PriorNLikelihood &ml):
    md(ml),
    ml(ml),
    mon(NULL)
  {
  }

  CPriorSampler::~CPriorSampler()
  {
  }
  
  CSPMetro::CSPMetro(PriorNLikelihood &ml,
		     const std::vector<double> &sigmas,
		     unsigned seed):
    CPriorSampler(ml),
    prop(new MetroPropose(sigmas, seed))
  {

  }

  CSPMetro::~CSPMetro()
  {

  }

  double CSPMetro::advance(double L,
			   size_t maxprop)
  {
    const size_t npars=prop->nPars();

    std::vector<double> cpoint(npars);
    md.get(cpoint);
    
    std::vector<double> propose(npars);

    // Current log prior value
    double clprior = -ml.pprob();

    double cllikel = -ml.llprob();

    for(size_t sn=0 ; sn<maxprop; ++sn)
    {
      propose=cpoint;
      prop->displace(propose);      
      md.put(propose);

      const double propllikel= -ml.llprob();
      
      if (mon)
      {
	MCPoint p(propose);
	p.ll=propllikel;
	mon->propose(p);
      }

      if (propllikel > L)
      {
	const double proplprior  = - ml.pprob();
	
	double    ldiff =  proplprior - clprior;

	if (ldiff > 0 or 
	    prop->raccept() < exp(ldiff) )
	{
	  cpoint=propose;
	  clprior=proplprior;      
	  cllikel=propllikel;

	  if (mon)
	  {
	    MCPoint p(cpoint);
	    p.ll=cllikel;
	    mon->accept(p);
	  }

	}
      }
    }
    // Store current point in the model
    md.put(cpoint);

    return cllikel;
    
  }


  CSPAdaptive::CSPAdaptive(PriorNLikelihood &ml,
			   const std::vector<double> &initSigmas,
			   unsigned seed):
    CPriorSampler(ml),
    prop(new MetroPropose(initSigmas, 
			  seed))    
  {
  }

  CSPAdaptive::~CSPAdaptive()
  {
  }

  double CSPAdaptive::advance(double L,
			      size_t maxprop)
  {

  }
  

}


