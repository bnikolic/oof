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
  
  /** \brief Flat, independent priors on each parameter
      
      \bug Interface presented by this class has not yet been fully
      finalised.

   */
  class IndependentFlatPriors:
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
    
    typedef std::list<fprior_t> priorlist_t;
    
    priorlist_t priorlist;

  public:

    // ---------- Construction / Destruction --------------
    
    IndependentFlatPriors(MLikelihood * mod);

    /// Write out the constructor so that incomplete types in auto
    /// pointers get properly deleted
    ~IndependentFlatPriors(void);

    // ---------- Public interface  --------------------------

    /// Add a flat prior between low and high, on parameter with name
    /// pname
    void AddPrior( const std::string & pname,
		   double low,
		   double high);
    
    // Inherited from MLikelihood
    double lLikely(void) const;
    // Inherited from Model
    void     AddParams ( std::vector< Minim::DParamCtr > &pars );

  };
  


}
#endif
