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
#include "nestedsampler.hxx"

namespace Minim
{
  
  CPriorSampler::CPriorSampler(PriorNLikelihood &ml,
			       ModelDesc &md):
    md(md),
    ml(ml),
    mon(NULL)
  {
  }

  CPriorSampler::~CPriorSampler()
  {
  }
  
  CSPMetro::CSPMetro(PriorNLikelihood &ml,
		     ModelDesc &md,
		     const std::vector<double> &sigmas,
		     unsigned seed):
    CPriorSampler(ml,md),
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
			   ModelDesc &md,
			   const std::vector<double> &initSigmas):
    CPriorSampler(ml,md),
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

    c.reset(new InitPntChain(ic,
			     flkl,
			     fprior,
			     constrPriorP));
  }

  CSPAdaptive::~CSPAdaptive()
  {
  }

  double CSPAdaptive::advance(double L,
			      size_t maxprop)
  {
    const size_t qrtr=maxprop/4;
    const double sf=0.95;    
    const double xf=1.0;

    for (size_t j=0; j<sigmas.size(); ++j)
	  sigmas[j]*=xf;

    std::vector<double> ic(c->n);
    md.get(ic);
    
    c->reset(ic);

    bool accepted=false;
    for(size_t i=0; i<maxprop; ++i)
    {
      bool a=normProp(*c,
		      sigmas);
      accepted=accepted or a;

      if (accepted==false and i>qrtr)
      {
	for (size_t j=0; j<sigmas.size(); ++j)
	  sigmas[j]*=sf;
      }
    }
    md.put(c->gcx());

    // Note the convention is to return the negative value
    return -c->gcl();
  }



  CSRMSSS::CSRMSSS(PriorNLikelihood &ml,
		   ModelDesc &md,
		   const std::set<MCPoint> &ss):
    CPriorSampler(ml,md),
    ss(ss)
  {
  }

  CSRMSSS::CSRMSSS(PriorNLikelihood &ml,
		   NestedS &s):
    CPriorSampler(ml,s),
    ss(s.g_ss())
  {
  }

  CSRMSSS::~CSRMSSS()
  {
  }

  void CSRMSSS::initChain(void)
  {
    MarkovChain::fx_t flkl=boost::bind(likelihood, 
				       boost::ref(md),
				       boost::ref(ml), 
				       _1);
    
    MarkovChain::fx_t fprior=boost::bind(prior, 
					 boost::ref(md),
					 boost::ref(ml), 
					 _1);
    std::vector<double> ic(ss.begin()->p.size());
    md.get(ic);

    c.reset(new ILklChain(ic,
			  flkl,
			  fprior,
			  constrPriorL));

    nprop=0;
  }

  double CSRMSSS::advance(double L,
			  size_t maxprop)
  {
    const double sf=0.1;

    if (not c) 
      initChain();

    const size_t n=c->n;


    std::vector<double> ic(n);
    md.get(ic);
    c->reset(ic,
	     L);

    std::vector<double> cv, eigvals, eigvects;
    omoment2(ss, cv);
    principalCV(cv, 
		eigvals, eigvects);

    for(size_t j=0; j<eigvals.size(); ++j)
      eigvals[j]= pow(eigvals[j],0.5)*sf;

    for(size_t i=0; i<maxprop; ++i)
    {
      std::vector<double> sigmas(n,0);
      sigmas[nprop%n]=eigvals[nprop%n];
      eigenProp(*c,
		//sigmas,
		eigvals,
		eigvects);
      ++nprop;
    }
    md.put(c->gcx());

    // Note the convention is to return the negative value
    return -c->gcl();
  }
  

}


