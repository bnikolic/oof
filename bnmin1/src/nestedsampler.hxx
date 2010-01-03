/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file nestedsampler.hxx

   The nested sampler 
*/

#ifndef _BNMIN1_NESTEDSAMPLER_HXX__
#define _BNMIN1_NESTEDSAMPLER_HXX__

#include <set>
#include <vector>
#include <list>

#include <boost/scoped_ptr.hpp>

#include "mcpoint.hxx"
#include "minim.hxx"
#include "nestederr.hxx"

namespace Minim {

  // Forward declarations
  class PriorNLikelihood;
  class CPriorSampler;
  class MCMonitorBase;
  class IndependentFlatPriors;
  class NestedInitial;


  /** \brief Nested Sampler
      
      See for example Skilling (2006, Proc. Valencia/ISBA)

   */
  class NestedS:
    public ModelDesc
  {
    /** \brief Sample (or "live")set
	
	This is the current set of points
     */
    std::set<MCPoint> ss;

    /** \brief Sequence of calculated evidence values
     */
    std::vector<double> Zseq;

    /** \brief Sequence of X values
     */
    std::vector<double> Xseq;
    
    /** \brief The model defining the likelihood function and priors
     */
    PriorNLikelihood &ml;

    /** \brief The constrained prior sampler to replace points
     */
    boost::scoped_ptr<CPriorSampler> ps;

    /** \brief Points describing the posterior
	
	List of points which passed through the live set, with weights
	and likelihoods
    */
    std::list<WPPoint> post;

    /// The strategy for picking the inital point
    boost::scoped_ptr<NestedInitial> initials;
    
  public:

    // -------------- Public data ---------------------------------
    
    /// Interface to monitor the progress made by the nested sampler
    MCMonitorBase *mon;

    /// Number of samples to make when sampling the prior under
    /// the likelihood constraint 
    size_t n_psample;


    // -------------- Construction/Destruction ---------------------

    /**
       \param ml The definition of the likelihood and priors to be
       explored. Note that object of type PriorNLikelihood is required
       here as information about priors separately from the likelihood
       is required for nested sampling.

       \param start The starting set of points. The likelihod
       functions will be re-calculated so it does not need be supplied
       in the MCPoint structure
       
       \param seed Seed for the random number generator

    */
    NestedS(PriorNLikelihood & ml,
	    const std::list<MCPoint> & start,
	    unsigned seed=43) throw (NestedSmallStart);

    /**
       A constructor without a starting set, which allows for the
       to-fit parameters to be adjusted before initialisation
     */
    NestedS(PriorNLikelihood & ml,
	    unsigned seed=43) ;


    ~NestedS();

    // -------------- Public Interface -----------------------------

    /** Restart the sampler with the supplied starting set. Must be
	used if a constructor without a starting set is used.
     */
    void reset(const std::list<MCPoint> &start);

    /** Set the initial point selection strategy.  Note this object
	will take ownership of the supplied object
    */
    void InitalS(NestedInitial *ins);

    /** \brief Number of points in the current set
     */
    size_t N(void) const;

    /** \brief Return current evidence estimate */
    double Z(void) const;

    /** \brief Take j samples and return evidence estimate
     */
    double sample(size_t j);

    /** \brief Return the points describing the posterior
     */
    const std::list<WPPoint> & g_post(void) const;

    /** \brief Return the live point set
     */
    const std::set<MCPoint> & g_ss(void) const;
    
  };

  /** 
      \brief Calculate the log-likelihood at the supplied points and
      insert the points into the supplied set

      Example of usage is evaluting the points in a starting set
      before sorting them in likelihood for the nested sampler.

      \param md Model description which allows control of the
      ml. Allows information regarding which parameters are fitted for
      or not to be passed
      
      \param  lp The supplied points
      
      \param res The output set of points with likelihoods

      \note The pure likelihood is calcuted, and priors are no
      included in this calculation
   */
  void llPoint(PriorNLikelihood &ml,
	       ModelDesc &md,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res);

  /** 
      Operates like the four-parameter version but assumes all
      parameters are fitted-for

   */
  void llPoint(PriorNLikelihood &ml,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res);

  /** 
      \brief Create the starting set by directly sampling the prior
      distribution
      
      This requieres the prior distribution to be made from
      independent flat priors.
   */
  void startSetDirect(IndependentFlatPriors &prior,
		      size_t n,
		      std::list<MCPoint> &res,
		      unsigned seed=43);

  /**
     \brief Print the starting set to the stdout
  */
  void printSS(const std::set<MCPoint> &ss);


}

#endif
