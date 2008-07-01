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



namespace Minim {

  class MLikelihood;
  class MetroPropose;

  /** Structure containing the data recorded at each point in an MCMC
      distribution
  */
  struct MCPoint
  {
    /// The actual parameters
    std::vector<double> p;
    /// Log-likelihood of this point
    double ll;
    /// A vector to store derived quantities at sample of the
    /// distribution
    std::vector<double> fval;
  };

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

    // ---------- Public data -----------------------------

    /// If this pointer is set, this function will be called at each
    /// point in the distribution and values stored in parameter x
    /// will be saved in the field fval.
    boost::function< void (std::vector<double> &x) >  f;    

    // ---------- Construction / Destruction --------------

    /**
       \param sigmas The standard deviations of the parameter
       perturbation used in the Metropolis algorithm
     */
    MetropolisMCMC(MLikelihood & ml,
		   const std::vector<double> & sigmas,
		   unsigned seed=0
		   );
    
    virtual ~MetropolisMCMC();

    // ---------- Public interface --------------------------

    /**
       Create a sample chain.

       \param npropose number of proposal samples to run

     */
    std::list<MCPoint> *
    sample(size_t npropose);
    


  };


}
#endif
