/*
  Bojan Nikolic
  $Id: interpolate.hxx,v 1.3 2005/05/05 12:52:08 bnikolic Exp $

  Routines for interpolation
*/
#ifndef _BNLIB_INTERPOLATE_HXX__
#define _BNLIB_INTERPOLATE_HXX__

#include <stddef.h> 

#include "unaryfn.hxx"

namespace BNLib {

  /// Base class for interpolation routines
  
  class InterpolatorBase : public UnaryDD {

  public:
    
    /// Interpolation type.
    enum imethod { linear, poly, cspline, akima, akimapos }  method;

    // --- Constructors ----
    InterpolatorBase( double * xvals , double * yvals , size_t size ,
		      imethod method );
    
    virtual ~InterpolatorBase() ;

    /// Approximates the value at x
    virtual double operator() (double x) = 0 ;

    /// Integrates from xmin to xmax
    virtual double Idx(double xmin, double xmax) =0 ;


  };






}
#endif
