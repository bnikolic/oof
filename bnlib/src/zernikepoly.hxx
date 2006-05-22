/*
  \file zernikepoly.hxx

  Bojan Nikolic
  $Id: zernikepoly.hxx,v 1.5 2006/05/22 21:21:18 bnikolic Exp $

  Zernike Polynomial functions
*/
#ifndef _BNLIB_ZERNIKEPOLY_HXX__
#define _BNLIB_ZERNIKEPOLY_HXX__

#include "binaryfn.hxx"

#include <valarray>

namespace BNLib {

  /*!
   * Defines a Zernike polynomial of radial order n and angular order
   * l.
   * 
   * Note under the definition used here that polynomials \f$ l < 0
   * \f$ have a \f$ sin\f$-like dependance on the azimuth angle and
   * polynomials with \f$l>0\f$ have a \f$ cos\f$-like dependance.
   */
  class ZernPoly :  public BinaryDD {

  public:
    /*! Radial order of the polynomial */
    const int    n;

    /*! Angular order of the polynomial */
    const int    l;

  private:
  
    const int    m;
    const int    nradterm;

    std::valarray<double>  radcoeffs;
    std::valarray<int>     radpowers;
  
  public:
    
    /* ---------- Constructors & Destructors -----------*/

    /*! 
      \param n is the radial  order
      \param l is the angular order
     */
    ZernPoly( int n, int l  );

    /*! destructor is trivial.
     */
    virtual ~ZernPoly();

    /* ---------- Inherited             ----------------*/  
    double operator()( double x, double y );

  };

  /*! Return the sequential zernike polynomil number i from the radial
   * order n and angular order l*/
  size_t ZernIFromNL(int n, int l);

}

#endif
