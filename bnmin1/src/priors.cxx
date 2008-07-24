/**
   \file priors.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
*/

#include "priors.hxx"

#include "paramalgo.hxx"

namespace Minim {

  IndependentFlatPriors::IndependentFlatPriors(MLikelihood * mod):
    _mod(mod)
  {
    _mod->AddParams(_mpars);
  }

  IndependentFlatPriors::~IndependentFlatPriors(void)
  {
  }
  
  
  void IndependentFlatPriors::AddPrior( const std::string & pname,
					double low,
					double high)
  {
    fprior_t pr;
    
    DParamCtr * par=findName(_mpars,pname);
    if ( par == NULL)
      throw "Could not find parameter";
    pr.p=par->p;
    pr.pmin=low;
    pr.pmax=high;
    priorlist.push_back(pr);
  }


  double IndependentFlatPriors::lLikely(void) const
  {
    double lpriorprop = 0 ;
    for (priorlist_t::const_iterator i = priorlist.begin();
	 i != priorlist.end();
	 ++i)
    {
      const double p = * (i->p);
      if (p < i->pmin or p > i->pmax)
	lpriorprop += 1e9;
    }
    return lpriorprop + _mod->lLikely();
  }
  
  void  IndependentFlatPriors::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    _mod->AddParams(pars);
  }


}

