/**
   \file prior_sampler.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Sampler of the prior distribution 
*/

#ifndef _BNMIN1_PRIOR_SAMPLER_HXX__
#define _BNMIN1_PRIOR_SAMPLER_HXX__

#include <vector>
#include <set>

#include <boost/scoped_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "minim.hxx"
#include "mcpoint.hxx"


namespace Minim
{
  // Forward declarations
  class PriorNLikelihood;
  class IndependentFlatPriors;
  class MetroPropose;
  class MCMonitorBase;
  class MarkovChain;
  class InitPntChain;
  class ILklChain;
  class NestedS;
  class EllipsoidSampler;

  /** \brief Constrained prior sampler
      
      Generate a new point at a position with probabilitiy
      proportional to prior distribution and sujbject to constraint
      that the likelihood is higher than supplied limit
   */
  class CPriorSampler
  {

  protected:

    ModelDesc &md;
    
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
		  ModelDesc &md);

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
	     ModelDesc &md,
	     const std::vector<double> &sigmas,
	     unsigned seed=0);

    ~CSPMetro();

    // -------------- Public Interface -----------------------------

    double advance(double L,
		   size_t maxprop);

  };

  /** \brief Adapaptive constrained sampler

      This sampler progressively reduces sigmas when it finds it can't
      make any steps. Can paint itself into a corner relatively easily.
   */
  class CSPAdaptive:
    public CPriorSampler
  {

    boost::scoped_ptr<InitPntChain> c;
    std::vector<double> sigmas;

  public:

    // -------------- Construction/Destruction ---------------------

    /**
       \param initSigmas are the initial variances to use in proposals

       \param seed the seed for the random number generator
     */
    CSPAdaptive(PriorNLikelihood &ml,
		ModelDesc &md,
		const std::vector<double> &initSigmas);

    ~CSPAdaptive();

    // -------------- Public Interface -----------------------------

    double advance(double L,
		   size_t maxprop);

  };

  /** Base the monte-carlo steps on the points in the live live set
     
   */
  class CSRMSSS:
    public CPriorSampler
  {

    boost::scoped_ptr<ILklChain> c;
    const std::set<MCPoint> &ss;

    void initChain(void);

    size_t nprop;


  public:

    // -------------- Construction/Destruction ---------------------

    /**

     */
    CSRMSSS(PriorNLikelihood &ml,
	    ModelDesc &md,
	    const std::set<MCPoint> &ss);

    CSRMSSS(PriorNLikelihood &ml,
	    NestedS &s);


    ~CSRMSSS();

    // -------------- Public Interface -----------------------------

    double advance(double L,
		   size_t maxprop);

  };


  /** \brief Sample prior mass by constructing ellipsoid and uniformly
      sampling within it

      This class is specialised to *flat* priors as in this case it
      can be optimised to simple rejection of points with poorer
      likelihood than the required value. 

      It can be generalised to non-flat priors by MCMC sampling of
      prior mass and then rejection of points with poorer likelihood.
      
      The current implementation of this class rescales the prior
      volume to a unit cube before sampling. This ensures that the
      ellipsoid volume minimisation works as intended

   */
  class EllipsoidCPSampler:
    public CPriorSampler
  {
    /// Random number generator
    boost::mt19937 rng;

    /// Current covering ellipsoid of the live set
    boost::scoped_ptr<EllipsoidSampler> es;

    /// Number of points that missed since last reshape
    size_t missp;

    /// Number of accepted points since last reshape
    size_t accp;

    /// Reference to the current live point set
    const std::set<MCPoint> &ss;

    /// The centre of each prior 
    std::vector<double> pcent;

    /// The half-range of each prior dimension
    std::vector<double> prange;

    /// Our own reference to the problem definition, which knows it is
    /// actually of type IndependentFlatPriors
    IndependentFlatPriors &ml;

  public:
    
    // -------------- Public data ----------------------------------
    
    /// Force recomputation of ellispoid after this many accepted
    /// points
    size_t reshape_maxp;

    /// Force recomputation of the ellipsoid if this many misses have
    /// been accumulated
    size_t reshape_missp;

    // -------------- Construction/Destruction ---------------------

    /** This class is specialised to flat prior volumes
     */
    EllipsoidCPSampler(IndependentFlatPriors &ml,
		       NestedS &s);

    ~EllipsoidCPSampler();

    // -------------- Public Interface -----------------------------

    /** \brief Reshape the ellipsoid to best-fit the live set
     */
    void reshape(void);
    
    // -------------Inherited from CPriorSampler -------------------
    double advance(double L,
		   size_t maxprop);

  };

  

}

#endif
