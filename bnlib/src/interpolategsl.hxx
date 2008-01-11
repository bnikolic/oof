/**
   \file interpolategsl.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

  Routines for interpolation
*/
#ifndef _BNLIB_INTERPOLATEGSL_HXX__
#define _BNLIB_INTERPOLATEGSL_HXX__

#include "interpolate.hxx"

#include <gsl/gsl_spline.h>

namespace BNLib {


  class InterpolatorGSL : public InterpolatorBase {

    /// Holds the data GSL needs to do the interpolation
    gsl_spline * spline;
    
    /// Holds data to accelarate multiple interpolations
    gsl_interp_accel * accel;

  public:

    // --- Constructors ----
    
    InterpolatorGSL( const double * xvals , 
		     const double * yvals , 
		     size_t size ,
		     imethod method );

    // --- Destructor ---
    ~InterpolatorGSL();

    // --- Inherited Fns -----

    /// Does the actuall interpolation
    double operator() (double x) {
      return  gsl_spline_eval( spline , x, accel);
    }

    /// Evaluates the integral between xmin, xmax 
    double Idx ( double xmin, double xmax) {
      return  gsl_spline_eval_integ( spline , xmin, xmax, accel);
    }


  };


}

#endif


