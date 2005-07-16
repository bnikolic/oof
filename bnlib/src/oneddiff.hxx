/*
  Bojan Nikolic
  $Id: oneddiff.hxx,v 1.2 2005/07/16 15:50:17 bnikolic Exp $
  
  One dimensional numeric differentiation
*/

#ifndef _BNLIB_ONEDDIFF_HXX__
#define _BNLIB_ONEDDIFF_HXX__

#include "unaryfn.hxx"

namespace BNLib {

  /*! Returns the first differential of the supplied function */
  class LinDiff : public UnaryDD {
    
    /*! The function to be differentiated */
    UnaryDD &fn;

    /*! Forward difference amount to be used */
    double eps;
    
  public:
    
    LinDiff ( UnaryDD &fn, double eps );

    /* ---- Inherited functions ------*/

    /*! Returs the differential at x */
    virtual double operator() (double x)  ;

  };
  



}

#endif
