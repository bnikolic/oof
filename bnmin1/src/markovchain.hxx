/**
   \file markovchain.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
*/
#ifndef _BNMIN1_MARKOVCHAIN_HXX__
#define _BNMIN1_MARKOVCHAIN_HXX__

#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/function.hpp>

namespace Minim {

  struct MCPoint2
  {
    /// The position in space of the point
    std::vector<double>  x;
    
    /// The value of likelihood
    double l;
    
    /// The value of the prior
    double p;
  };

  class MarkovChain
  {

  public:

    /// Type of the interger random number generator
    typedef boost::mt19937  irg_t;

    /// Vector type
    typedef std::vector<double>  v_t;
    
    /// A function of a point in the chain
    typedef boost::function< double (const v_t &x) >  fx_t;

    /// A function to return the acceptance probability
    typedef boost::function< double (const MCPoint2 &c, const MCPoint2 &p) >  fa_t;

  private:
    
    /// The integer random number generator
    irg_t igen;
    
    boost::normal_distribution<> norm_dist;

    /// The likelihood function
    fx_t fLkl;    

    /// The prior function
    fx_t fPr;    

    /// The acceptance function
    fa_t fAccept;

    /// The current position of the chain
    MCPoint2 c;

    /// The next proposed point     
    MCPoint2 p;
    
  public:

    /// The normal distribution generator
    mutable
    boost::variate_generator<irg_t&, 
			     boost::normal_distribution<> > 
    ngen;

    /**  Uniform random numbers between 0 and 1

	 \note The generator is take by copy
    */
    mutable
    boost::uniform_01<irg_t> u01gen;
    

    // ---------- Public data -----------------------------    

    /// Number of parameters
    const size_t n;

    // ---------- Construction / Destruction --------------
    
    MarkovChain(const v_t &ic,
		fx_t fLkl,
		fx_t fPr,
		size_t n);

    // ---------- Public interface --------------------------

    /**  Propose x as the next point in chain
     */
    void propose(const v_t &x);

    /** Reset the chain, discard existing data and set x as the
	starting point*/
    void reset(const v_t &x);

    //          ------------ Access type functions ---------------

    /// Return the current point of the chain
    const std::vector<double> &gcx(void) const
    {
      return c.x;
    }
    

  };

  void normProp(MarkovChain &c,
		const std::vector<double> &sigma);


  /** \brief The standard metropolis acceptance function
   */
  double metropolis(const MCPoint2 &c, 
		    const MCPoint2 &p);

  /** \brief The nested sampling acceptance function
   */
  double constrPrior(const MCPoint2 &c, 
		     const MCPoint2 &p);

    


}

#endif
