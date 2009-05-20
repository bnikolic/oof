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
  
  CPriorSampler::CPriorSampler(PriorNLikelihood &ml,
			       const std::vector<double> &sigmas,
			       unsigned seed):
    prop(new MetroPropose(sigmas, seed)),
    md(ml),
    ml(ml),
    mon(NULL)
  {
  }

  CPriorSampler::~CPriorSampler()
  {
  }

  double CPriorSampler::advance(double L,
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
    
    if (not (cllikel > L))
      throw BaseErr("Could not obtain a better point");
    return cllikel;
    
  }

}


