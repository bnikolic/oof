/**
   \file prior_sampler.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <boost/bind.hpp>

#include "prior_sampler.hxx"

#include "priors.hxx"
#include "metro_propose.hxx"
#include "bnmin_main.hxx"
#include "mcpoint.hxx"
#include "mcmonitor.hxx"
#include "markovchain.hxx"

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

  double likelihood(ModelDesc &md,
		    PriorNLikelihood &ml,
		    const std::vector<double> &x)
  {
    md.put(x);
    return ml.llprob();
  }

  double prior(ModelDesc &md,
	       PriorNLikelihood &ml,
	       const std::vector<double> &x)
  {
    md.put(x);
    return ml.pprob();
  }

  CSPAdaptive::CSPAdaptive(PriorNLikelihood &ml,
			   const std::vector<double> &initSigmas):
    CPriorSampler(ml),
    sigmas(initSigmas)
  {
    MarkovChain::fx_t flkl=boost::bind(likelihood, 
				       boost::ref(md),
				       boost::ref(ml), 
				       _1);

    MarkovChain::fx_t fprior=boost::bind(prior, 
					 boost::ref(md),
					 boost::ref(ml), 
					 _1);
    std::vector<double> ic(sigmas.size());
    md.get(ic);

    c.reset(new MarkovChain(ic,
			    flkl,
			    fprior,
			    constrPrior,
			    initSigmas.size()));
  }

  CSPAdaptive::~CSPAdaptive()
  {
  }

  double CSPAdaptive::advance(double L,
			      size_t maxprop)
  {
    std::vector<double> ic(c->n);
    md.get(ic);
    
    c->reset(ic);

    for(size_t i=0; i<maxprop; ++i)
    {
      normProp(*c,
	       sigmas);
    }
    md.put(c->gcx());

    // Note the convention is to return the negative value
    return -c->gcl();
  }
  

}


