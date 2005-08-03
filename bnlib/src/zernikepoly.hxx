/*
  Bojan Nikolic
  $Id: zernikepoly.hxx,v 1.2 2005/08/03 12:00:52 bnikolic Exp $

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
   */
  class ZernPoly :  public BinaryDD {

  public:
    const int    n;
    const int    l;

  private:
  
    const int    m;
    int    nradterm;

    std::valarray<double>  radcoeffs;
    std::valarray<int>     radpowers;
  
  public:
    
    /* ---------- Constructors & Destructors -----------*/
    ZernPoly( int n, int l  );
    virtual ~ZernPoly();

    /* ---------- Inherited             ----------------*/  
    double operator()( double x, double y );

  };

  /*! Return the sequential zernike polynomil number i from the radial
   * order n and angular order l*/
  size_t ZernIFromNL(int n, int l);

}

#endif
