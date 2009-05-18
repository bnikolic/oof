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

#include "mcpoint.hxx"

namespace Minim {

  // Forward declarations
  class MLikelihood;

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
    MLikelihood & ml;

    
  public:

    // -------------- Construction/Destruction ---------------------

    /**
       \param ml The likelihood to be explored

       \param start The starting set of points. The likelihod
       functions will be re-calculated so they need not be supplied in
       the MCPoint structure
     */
    NestedS(MLikelihood & ml,
	    std::list<MCPoint> start,
	    const std::vector<double> & sigmas,
	    unsigned seed=43);

    ~NestedS();

    // -------------- Public Interface -----------------------------

    
    
    
    
  };


}

#endif
