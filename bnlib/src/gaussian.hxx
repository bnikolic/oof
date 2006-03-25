/*
  Bojan Nikolic
  $Id: gaussian.hxx,v 1.3 2006/03/25 14:29:30 bnikolic Exp $

  Support for Gaussian  fns
*/

#ifndef _BNLIB_GAUSSIAN_HXX__
#define _BNLIB_GAUSSIAN_HXX__

#include "binaryfn.hxx"

namespace BNLib {

  /*! A 2-dimensional gaussian  */
  class GaussianDD : public BinaryDD {

  public:
    
    /* ---- Public data members ----- */
    /*! Centre of gaussian */
    double x0,y0;  
    /*! sigma: width of gaussian */
    double sigma, rho , diff;
    /*! Amplitude of the gaussian, i.e., value at x=x0, y=y0 */
    double amp;
  

    /* ---- Constructors & destructors ----- */

    /*! Default constructor: gaussian at origin with sigma equal to  one */
    GaussianDD(void);

    /*! If one par give assume it is sigma :*/
    GaussianDD( double sigma);

    /*! If three assume given sigma and centre */
    GaussianDD( double sigma, double x0 , double y0);


    /* ------- Inherited   -------------------*/

    double operator() (double x1, double y1);


  };
  

}


#endif
