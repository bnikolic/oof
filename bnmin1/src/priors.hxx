/**
   \file priors.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Mechanism to include prior information when sampling posterior
   distributions
*/
#ifndef _BNMIN_PRIORS_HXX__
#define _BNMIN_PRIORS_HXX__

#include "minimmodel.hxx"

#include <list>
#include <boost/scoped_ptr.hpp>

namespace Minim {

  /** \brief Represents combined priors and likelihood in a single
      object
      
      
   */
  class PriorNLikelihood:
    public MLikelihood
  {
    /// Keeps the encapsulated likelihoood model
    boost::scoped_ptr<MLikelihood> _mod;
    
  public:

    /// --------------- Public data -----------------------
    
    /** \brief Value representing very low likelihood 
	
	I.e., this is the value used for the negative log-likelihood
	when priors have "hard" constraints
     */
    static const double lkl_h=1e9;

    // ---------- Construction / Destruction --------------

    /** Construct with reference to an existing model

       \note This class takes ownership of the supplied pointer
    */
    PriorNLikelihood(MLikelihood * mod);    
    
    virtual ~PriorNLikelihood();

    // ---------- Public interface  --------------------------
    
    /** \brief Likelihood (without prior multiplied in)
	
     */
    double llprob(void) const
    {
      return _mod->lLikely();
    }

    /** \brief Prior probability at current point
     */
    virtual double pprob(void) const
    {
      return 0;
    }

    // Inherited from MLikelihood
    double lLikely(void) const
    {
      return llprob()+pprob();
    }

    // ------------   Inherited from Model   ----------------
    void AddParams (std::vector<Minim::DParamCtr> &pars);


  };
  
  /** \brief Independent priors on each parameter
      
      \bug Interface presented by this class has not yet been fully
      finalised.

   */
  class IndependentPriors:
    public PriorNLikelihood
  {

    std::vector< Minim::DParamCtr > _mpars;
    
    struct fprior_t
    {
      const double * p;
      double pmin;
      double pmax;
    };
    
  public:
    typedef std::list<fprior_t> priorlist_t;

  private:
    priorlist_t priorlist;

  public:

    // ---------- Construction / Destruction --------------

    /** Construct with reference to an existing model

       \note This class takes ownership of the supplied pointer
    */
    IndependentPriors(MLikelihood * mod);

    virtual ~IndependentPriors(void);

    // ---------- Public interface  --------------------------

    /// Add a flat prior between low and high, on parameter with name
    /// pname
    void AddPrior( const std::string & pname,
		   double low,
		   double high);

    /// Support iteration overpriors
    priorlist_t::const_iterator pbegin(void) const
    {
      return priorlist.begin();
    }

    /// Support iteration overpriors
    priorlist_t::const_iterator pend(void) const
    {
      return priorlist.end();
    }

    /// Number of priors
    size_t npriors(void) const
    {
      return priorlist.size();
    }

  };

  class IndependentFlatPriors:
    public IndependentPriors

  {
  public:

    // ---------- Construction / Destruction --------------

    /** 
	Construct with reference to an existing model

	\note This class takes ownership of the supplied pointer
    */
    IndependentFlatPriors(MLikelihood * mod);

    virtual ~IndependentFlatPriors(void);

    // ---------- Public interface  --------------------------

    /** Retrieve the coordinates of the prior box defined by the
	priors

	\param cent are the centres of each param
	\param range the range of each param
     */
    void getBoxCntr(std::vector<double> &cent,
		    std::vector<double> &range) const;

    // Inherited
    double pprob(void) const;
  };

  class LogFlatPriors:
    public IndependentPriors

  {
  public:

    // ---------- Construction / Destruction --------------

    /** 
	Construct with reference to an existing model
    */
    LogFlatPriors(MLikelihood * mod);

    virtual ~LogFlatPriors(void);

    // ---------- Public interface  --------------------------
    // Inherited
    double pprob(void) const;
  };
  


}
#endif
