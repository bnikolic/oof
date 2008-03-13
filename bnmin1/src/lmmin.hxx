/**
   \file lmmin.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>
   Initial version 2003

   The Lavenburg-Marquant minimisation algorithm interface

*/
#ifndef _BNMIN_LMMIN_HXX__
#define _BNMIN_LMMIN_HXX__

#include "minim.hxx"

namespace Minim {
  
  /// Implemnation of the Lavenburg-Marquant minimisation
  /// algorithm. See file f77/pda_lmdiff.f for more details.

  class LMMin : public Minimiser {

  public:

    // controls various tolerances; names same as in the original f77
    // file

    double ftol , xtol , gtol;
    int    maxfev; 
    double epsfcn;
    

    // These together contain all of the information needed to
    // calculate the covariance matrix.
    std::vector<double>   fjac;
    int ldfjac ;
    std::vector<int > ipvt;

    /// Tolerances are initialised to some normal defaults
    LMMin( Minimisable &pm ) ;
      
    virtual ~LMMin (void) { };

    virtual void solve(void);

  };

  
}

#endif
