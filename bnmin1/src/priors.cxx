/**
   \file priors.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
*/

#include "priors.hxx"

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

  }


}

