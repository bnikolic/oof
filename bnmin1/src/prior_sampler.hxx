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
  class PriorNLikelihood;
  class MetroPropose;
  class MCMonitorBase;

  /** \brief Constrained prior sampler
      
      Generate a new point at a position with probabilitiy
      proportional to prior distribution and sujbject to constraint
      that the likelihood is higher than supplied limit
   */
  class CPriorSampler
  {

    boost::scoped_ptr<MetroPropose> prop;

    ModelDesc md;
    
    PriorNLikelihood &ml;

  public:
    
    // -------------- Public data  --------------------------------
    MCMonitorBase * mon;

    // -------------- Construction/Destruction ---------------------

    /**
       \note We need separately the prior and the likelihood hence
       inheritance from indepenedentPriors
     */
    CPriorSampler(PriorNLikelihood &ml,
		  const std::vector<double> &sigmas,
		  unsigned seed=0);

    ~CPriorSampler();

    // -------------- Public Interface -----------------------------

    /**
       \return the likelihood of the new current point
     */
    double advance(double L,
		   size_t maxprop);
    

  };

}

#endif
