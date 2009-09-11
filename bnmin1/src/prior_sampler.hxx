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
  class MarkovChain;

  /** \brief Constrained prior sampler
      
      Generate a new point at a position with probabilitiy
      proportional to prior distribution and sujbject to constraint
      that the likelihood is higher than supplied limit
   */
  class CPriorSampler
  {

  protected:

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
    CPriorSampler(PriorNLikelihood &ml);

    virtual ~CPriorSampler();

    // -------------- Public Interface -----------------------------

    /** \brief Advance the model to the now sample point
	
	\param L The minimum likelihood of the new point

	\param maxprop Take no more than specified number of proposals
       
	\return the likelihood of the new current point
     */
    virtual double advance(double L,
			   size_t maxprop) = 0;
    

  };

  /** \brief Constrained prior sample based on simple metropolis
      proposals

   */
  class CSPMetro:
    public CPriorSampler
  {

    boost::scoped_ptr<MetroPropose> prop;

  public:
    
    // -------------- Construction/Destruction ---------------------

    /**

     */
    CSPMetro(PriorNLikelihood &ml,
	     const std::vector<double> &sigmas,
	     unsigned seed=0);

    ~CSPMetro();

    // -------------- Public Interface -----------------------------

    double advance(double L,
		   size_t maxprop);

  };

  /** \brief Adapaptive constrained sampler
   */
  class CSPAdaptive:
    public CPriorSampler
  {

    boost::scoped_ptr<MarkovChain> c;
    std::vector<double> sigmas;

  public:

    // -------------- Construction/Destruction ---------------------

    /**
       \param initSigmas are the initial variances to use in proposals

       \param seed the seed for the random number generator
     */
    CSPAdaptive(PriorNLikelihood &ml,
		const std::vector<double> &initSigmas);

    ~CSPAdaptive();

    // -------------- Public Interface -----------------------------

    double advance(double L,
		   size_t maxprop);

  };

}

#endif
