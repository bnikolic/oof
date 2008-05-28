/**
   \file metropolis.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <list>

#include "metropolis.hxx"


namespace Minim {

  MetropolisMCMC::MetropolisMCMC(MLikelihood & ml,
				 const std::vector<double> & sigmas
				 ):
    ModelDesc(ml),
    ml(ml),
    sigmas(sigmas)
  {
  }

  std::list<std::vector<double> > *
  MetropolisMCMC::sample(size_t npropose)
  {
    if (sigmas.size() != NParam() )
      throw Error("Number of sigmas not consistent with number of pars set to fit");

  }

  


}

