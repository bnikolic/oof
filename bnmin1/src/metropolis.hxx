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

#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include "minim.hxx"
#include "minimmodel.hxx"
#include "mcpoint.hxx"



namespace Minim {

  class MLikelihood;
  class MetroPropose;

  /** \brief Markov Chain Monte Carlo with Metropolis sampling
   */
  class MetropolisMCMC:
    public ModelDesc 
  {

    MLikelihood & ml;
    
    boost::scoped_ptr<MetroPropose> prop;

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
    
    /// Options for the Metropolis MCMC sampling algorithm
    enum Options {
      /// No special options, default
      NoOp=0,
      /** Normally proposal points are generated by perturbing the
      whole parameter vector simultanousely. If this option is set,
      each parameter is perturbed in turn. This reduces the impact of
      sigmas which are too large by allowing other parameters to
      evolve. However, if sigmas are too low and there are many
      parameters, time to converge increases.
      */
      Sequence=1};

    // ---------- Public data -----------------------------

    /** \brief A function to record at each accepted distribution
	point
	
	If this pointer is set, this function will be called at each
	point in the distribution and values stored in parameter x
	will be saved in the field fval.
    */
    boost::function< void (std::vector<double> &x) >  f;    

    // ---------- Construction / Destruction --------------

    /**
       \brief Initialise the class

       \param sigmas The standard deviations of the parameter
       perturbation used in the Metropolis algorithm.
       
       \param seed The seed for the random number generator

       \param opt Options
     */
    MetropolisMCMC(MLikelihood & ml,
		   const std::vector<double> & sigmas,
		   unsigned seed=0,
		   Options opt=NoOp
		   );
    
    virtual ~MetropolisMCMC();

    // ---------- Public interface --------------------------

    /**
       \brief Create a sample chain.

       \param npropose number of proposal samples to run

     */
    std::list<MCPoint> *
    sample(size_t npropose);
    


  };


}
#endif
