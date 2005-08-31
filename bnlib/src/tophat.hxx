/*
  Bojan Nikolic
  $Id: tophat.hxx,v 1.1 2005/08/31 02:32:04 bnikolic Exp $

  A 2-d tophat functions
*/

#ifndef _BNLIB_TOPHAT_HXX__
#define _BNLIB_TOPHAT_HXX__

#include "binaryfn.hxx"

namespace BNLib {

  class TopHatDD : public BinaryDD {

  public:
    
    /* ---- Public data members ----- */

    /*! Centre of the top hat */
    double x0,y0;  

    /*! radius of the top hat */
    double radius;
  

    /* ---- Constructors & destructors ----- */

    /*! */
    TopHatDD(void);


    /* ------- Inherited   -------------------*/

    double operator() (double x1, double y1);


  };

  

}

#endif
