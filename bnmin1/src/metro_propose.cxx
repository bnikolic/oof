/**
   \file metro_propose.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "metro_propose.hxx"

namespace Minim {

  MetroPropose::MetroPropose(const std::vector<double> & sigmas,
			     unsigned seed):
    sigmas(sigmas),
    generator(seed),
    uni_dist(0,1),
    norm(generator, norm_dist),
    uni(generator, uni_dist)
  {
  }

  MetroPropose::~MetroPropose()
  {
  }

  void MetroPropose::displace( std::vector<double> &x)
  {
    for (size_t i =0 ; i < sigmas.size() ; ++i)
      x[i] += sigmas[i]* norm();
  }
    

}

