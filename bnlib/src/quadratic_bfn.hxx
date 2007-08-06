/**
   \file quadratic_bfn.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   August 2007

   Define a simple quadratic function of two coordinates
*/
#ifndef __BNLIB_QUADRATIC_BFN_HXX__
#define __BNLIB_QUADRATIC_BFN_HXX__

#include "binaryfn.hxx"

namespace BNLib {

  /**
     A quadratic function of two coordinates
  */
  class QuadraticDD : 
    public BinaryDD 
  {

  public:
    // --------- Public data -------------

    double x0;
    double y0;
    double a;
    
    // --------- Construction / destructio -------
    QuadraticDD (void) ; 

    
    /**
       returns:
       \f[
       a(x_1-x_0)^2+a(y_1-y_0)^2
       \f]
    */
    virtual double operator() (double x1, double y1)
    {
      return a* ( x1-x0)*( x1-x0) +
	a*(y1-y0)*(y1-y0);
    }


  };

}

#endif

