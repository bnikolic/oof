/**
   \file prior_sampler.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Sampler of the prior distribution 
*/

#ifndef _BNMIN1_PRIOR_SAMPLER_HXX__
#define _BNMIN1_PRIOR_SAMPLER_HXX__

#include <vector>

#include <boost/scoped_ptr.hpp>

#include "minim.hxx"

namespace Minim
{
  // Forward declarations
  class IndependentPriors;
  class MetroPropose;

  /** \brief Constrained prior sampler
      
      Generate a point at position proportional to sample distribution
      with constraint that likelihood is higher than supplied limit
   */
  class CPriorSampler
  {

    boost::scoped_ptr<MetroPropose> prop;

    ModelDesc md;
    
    IndependentPriors &ml;

  public:

    // -------------- Construction/Destruction ---------------------
    
    CPriorSampler(IndependentPriors &ml,
		  const std::vector<double> &sigmas,
		  unsigned seed=0);

    // -------------- Public Interface -----------------------------

    /**
       \return the likelihood of the new current point
     */
    double advance(double L,
		   size_t maxprop);
    

  };

}

#endif
