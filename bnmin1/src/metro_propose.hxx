/**
   \file metro_propose.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Calculation of proposal points for Metropolis sampling
*/
#ifndef _BNMIN1_METRO_PROPOSAL_HXX__
#define _BNMIN1_METRO_PROPOSAL_HXX__

#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

namespace Minim {

  /** \brief Helper class which handles the random number parts of the
      Metropolis algorithm.

      The two of this class functions are to generate the proposal
      points (via displace()) and to generate uniform random numbers
      for accepting less likely points.
   */
  class MetroPropose {

  protected:
    const std::vector<double> sigmas;

    // Stuff for random numbers
    typedef boost::mt19937  base_generator_type;
    base_generator_type generator;
    boost::normal_distribution<> norm_dist;
    boost::uniform_real<> uni_dist;
    
    /// Normal distribution for creating proposal points
    boost::variate_generator<base_generator_type&, boost::normal_distribution<> > 
      norm;

    /// Uniform distribution for accepting according to probability
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni;
    
    
  public:
    
    // ---------- Construction / Destruction --------------

    MetroPropose(const std::vector<double> & sigmas,
		 unsigned seed=0);
    
    virtual ~MetroPropose();

    // ---------- Public interface --------------------------

    /// Generate a proposal point by displacing the supplied point.
    virtual void displace( std::vector<double> &x);

    /// Return the number of parameters for which we can propose
    size_t nPars(void);

    /// Generate a uniform number between zero and one for acceptance
    /// probability
    double raccept(void)
    {
      return uni();
    }
  };

  /**
     Intead of displacing the entire vector at once, each parameter is
     displaced in turn. See MetropolisMCMC::Options::Sequence.
   */
  class MetroProposeSeq :
    public MetroPropose
  {

    size_t count;

    const size_t n;

  public:

    // ---------- Construction / Destruction --------------

    MetroProposeSeq(const std::vector<double> & sigmas,
		    unsigned seed=0);

    // ---------- Public interface --------------------------
    virtual void displace( std::vector<double> &x);

  };

}

#endif
