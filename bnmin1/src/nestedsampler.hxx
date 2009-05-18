/**
   \file nestedsampler.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

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

namespace Minim {

  // Forward declarations
  class IndependentPriors;
  class CPriorSampler;

  /** \brief Nested Sampler
      
      See for example Skilling (2006, Proc. Valencia/ISBA)

   */
  class NestedS
  {
    /** \brief Sample set
	
	This is the current set of points
     */
    std::set<MCPoint> ss;

    /** \brief Sequence of calculated evidence values
     */
    std::vector<double> Zseq;

    /** \brief Sequence of X values
     */
    std::vector<double> Xseq;
    
    /** \brief The model defining the likelihood function
     */
    IndependentPriors &ml;

    ModelDesc md;

    /** \brief The constrained prior sampler to replace points
     */
    boost::scoped_ptr<CPriorSampler> ps;

    
  public:

    // -------------- Construction/Destruction ---------------------

    /**
       \param ml The definition of the likelihood and priors to
       explored. Note that IndependentPriors is required here
       information about priors separately from likelihood is requied
       for nested sampling.

       \param start The starting set of points. The likelihod
       functions will be re-calculated so they need not be supplied in
       the MCPoint structure
     */
    NestedS(IndependentPriors & ml,
	    std::list<MCPoint> start,
	    const std::vector<double> & sigmas,
	    unsigned seed=43);

    ~NestedS();

    // -------------- Public Interface -----------------------------

    /** \brief Number of points in the current set
     */
    size_t N(void);

    /** \brief Take j samples and return evidence estimate
     */
    double sample(size_t j);
    
  };

  /** 
      Calculate the log-likelihood at the supplied points and insert
      into supplied set

      \note pure likelihood is calcuted, disregarding prior
      information.
   */
  void llPoint(IndependentPriors & ml,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res);


}

#endif
