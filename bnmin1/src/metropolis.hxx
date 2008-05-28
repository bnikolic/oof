/**
   \file metropolis.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Metropolis sampling of the likelihood 
*/
#ifndef _BNMIN1_METROPOLIS_HXX__
#define _BNMIN1_METROPOLIS_HXX__

#include <stdexcept>
#include <list>
#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#include "minim.hxx"
#include "minimmodel.hxx"



namespace Minim {

  class MLikelihood;

  /** \brief Markov Chain Monte Carlo with Metropolis sampling
   */
  class MetropolisMCMC:
    public ModelDesc 
  {

    MLikelihood & ml;

    std::vector<double> sigmas;

    // Random-number generation

    typedef boost::mt19937  base_generator_type;
    base_generator_type generator;
    boost::normal_distribution<> norm_dist;
    boost::variate_generator<base_generator_type&, boost::normal_distribution<> > 
      norm;

  public:

    class Error :
      public std::runtime_error
    {
    public:
      Error(const std::string &msg):
	std::runtime_error(msg)
      {
      }
    };

    // ---------- Construction / Destruction --------------

    /**
       \param sigmas The standard deviations of the parameter
       perturbation used in the Metropolis algorithm
     */
    MetropolisMCMC(MLikelihood & ml,
		   const std::vector<double> & sigmas,
		   unsigned seed=0
		   );

    // ---------- Public interface --------------------------

    /**
       Create a sample chain.

       \param npropose number of proposal samples to run

     */
    std::list<std::vector<double> > *
    sample(size_t npropose);
    

    


  };


}
#endif
