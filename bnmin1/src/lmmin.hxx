/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file lmmin.hxx

   The Lavenburg-Marquant minimisation algorithm interface
*/
#ifndef _BNMIN_LMMIN_HXX__
#define _BNMIN_LMMIN_HXX__

#include "minim.hxx"

namespace Minim {
  
  /** \brief Implemnation of the Lavenburg-Marquant minimisation
      algorithm
      
      See file f77/pda_lmdiff.f for more details.
  */
  class LMMin: 
    public Minimiser 
  {

  public:

    // ---------- Public data  -----------------------

    
    /** Termination occurs when both the actual and predicted relative
        reductions in the sum of squares are at most ftol.  therefore,
        ftol measures the relative error desired in the sum of squares
    */
    double ftol;

    /**
       Termination occurs when the relative error between two
       consecutive iterates is at most xtol. therefore, xtol measures
       the relative error desired in the approximate solution.
    */
    double xtol;
    
    /**
       Termination occurs when the cosine of the angle between fvec
       and any column of the jacobian is at most gtol in absolute
       value. therefore, gtol measures the orthogonality desired
       between the function vector and the columns of the jacobian.
     */
    double gtol;

    /**
       Termination occurs when the number of calls to fcn is at least
       maxfev by the end of an iteration.
    */
    int    maxfev;
    
    /**
       This approximation assumes that the relative errors in the
       functions are of the order of epsfcn. if epsfcn is less than
       the machine precision, it is assumed that the relative errors
       in the functions are of the order of the machine precision.
    */
    double epsfcn;
    

    // These together contain all of the information needed to
    // calculate the covariance matrix.
    std::vector<double>   fjac;
    int ldfjac ;
    std::vector<int > ipvt;

    // ---------- Construction / Destruction --------------

    /// Tolerances are initialised to some normal defaults
    LMMin(Minimisable &pm) ;
      
    virtual ~LMMin(void)
    {};

    // ------------------ Inherited from Minimiser -------------
    virtual void solve(void);

  };

  
}

#endif
