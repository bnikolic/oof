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
  
  /** \brief Independent priors on each parameter
      
      \bug Interface presented by this class has not yet been fully
      finalised.

   */
  class IndependentPriors:
    public MLikelihood 
  {

    boost::scoped_ptr<MLikelihood> _mod;
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

    /// --------------- Public data -----------------------
    static const double lkl_h=1e9;

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

    // ------------   Inherited from Model   ----------------
    void AddParams (std::vector<Minim::DParamCtr> &pars);

    // Inherited from MLikelihood
    double lLikely(void) const
    {
      return _mod->lLikely();
    }

  };

  class IndependentFlatPriors:
    public IndependentPriors

  {
  public:

    // ---------- Construction / Destruction --------------

    /** 
	Construct with reference to an existing model
    */
    IndependentFlatPriors(MLikelihood * mod);

    virtual ~IndependentFlatPriors(void);

    // ---------- Public interface  --------------------------
    // Inherited from MLikelihood
    double lLikely(void) const;
  };
  


}
#endif
