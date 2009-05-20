/**
   \file priors.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
*/

#include "priors.hxx"

#include "paramalgo.hxx"
#include <cmath>

namespace Minim {

  PriorNLikelihood::PriorNLikelihood(MLikelihood * mod):
    _mod(mod)
  {
  }

  PriorNLikelihood::~PriorNLikelihood()
  {
  }

  void  PriorNLikelihood::AddParams (std::vector< Minim::DParamCtr > &pars)
  {
    _mod->AddParams(pars);
  }

  IndependentPriors::IndependentPriors(MLikelihood * mod):
    PriorNLikelihood(mod)    
  {
    AddParams(_mpars);
  }

  IndependentPriors::~IndependentPriors(void)
  {
  }

  void IndependentPriors::AddPrior( const std::string & pname,
					double low,
					double high)
  {
    fprior_t pr;
    
    DParamCtr * par=findName(_mpars,pname);
    if (par == NULL)
      throw ParamError(pname+" not found");
    pr.p=par->p;
    pr.pmin=low;
    pr.pmax=high;
    priorlist.push_back(pr);
  }

  double IndependentFlatPriors::pprob(void) const
  {
    double lpriorprop = 0 ;
    for (priorlist_t::const_iterator i = pbegin();
	 i != pend();
	 ++i)
    {
      const double p = * (i->p);
      if (p < i->pmin or p > i->pmax)
	lpriorprop += lkl_h;
    }
    return lpriorprop;
  }

  IndependentFlatPriors::IndependentFlatPriors(MLikelihood * mod):
    IndependentPriors(mod)
  {
  }
  
  IndependentFlatPriors::~IndependentFlatPriors(void)
  {
  }

  LogFlatPriors::LogFlatPriors(MLikelihood * mod):
    IndependentPriors(mod)
  {
  }
  
  LogFlatPriors::~LogFlatPriors(void)
  {
  }

  double LogFlatPriors::pprob(void) const
  {
    double lpriorprop = 0 ;
    for (priorlist_t::const_iterator i = pbegin();
	 i != pend();
	 ++i)
    {
      const double p = * (i->p);
      if (p < i->pmin or p > i->pmax)
      {
	lpriorprop += lkl_h;
      }
      else
      {
	lpriorprop += std::log(p);
      }
    }
    return lpriorprop;
  }


}

