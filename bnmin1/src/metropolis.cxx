/**
   \file metropolis.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <list>

#include "metropolis.hxx"


namespace Minim {

  MetropolisMCMC::MetropolisMCMC(MLikelihood & ml,
				 const std::vector<double> & sigmas,
				 unsigned seed
				 ):
    ModelDesc(ml),
    ml(ml),
    sigmas(sigmas),
    generator(seed),
    norm(generator, norm_dist)
  {
    if (sigmas.size() != NParam() )
      throw Error("Number of sigmas not consistent with number of pars set to fit");
  }

  std::list<std::vector<double> > *
  MetropolisMCMC::sample(size_t npropose)
  {
    for(size_t sn =0 ; sn < npropose; ++sn)
    {

    }
  }

  


}

