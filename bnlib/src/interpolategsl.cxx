/*
  Bojan Nikolic
  $Id: interpolategsl.cxx,v 1.1 2005/05/04 21:07:55 bnikolic Exp $

*/

#include "interpolategsl.hxx"



namespace BNLib {

  // --- Helper routines
  
  const  gsl_interp_type * ParseIMethod ( InterpolatorBase::imethod method ) 
  {
    switch (method) {
    case InterpolatorBase::linear:
      return gsl_interp_linear;
      break;
    case InterpolatorBase::poly:
      return gsl_interp_polynomial;
      break;
    case InterpolatorBase::cspline:
      return gsl_interp_cspline;
      break;
    case InterpolatorBase::akima:
      return gsl_interp_akima;
      break;
    }
  }


  InterpolatorGSL::InterpolatorGSL( double * xvals , 
				    double * yvals , 
				    size_t size ,
				    imethod method ):
    InterpolatorBase( xvals, yvals, size, method)
  {
    
    spline = gsl_spline_alloc( ParseIMethod (method) , size  );

    gsl_spline_init (spline , xvals , yvals , size );

    accel = gsl_interp_accel_alloc ();
  }

  InterpolatorGSL::~InterpolatorGSL() 
  {
    gsl_spline_free(spline);
    gsl_interp_accel_free (accel);
  }

  



}
