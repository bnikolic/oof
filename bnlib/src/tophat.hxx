/*
  Bojan Nikolic
  $Id: tophat.hxx,v 1.2 2006/03/09 14:59:41 bnikolic Exp $

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

    virtual double operator() (double x1, double y1);


  };

  /*! This is useful for modeling the Moon */
  class TaperedTopHatDD : public TopHatDD {
    


  public:

    /*! This is the amount of taper */
    double Cm;

    /* ---- Constructors & destructors ----- */

    /*! Default constructor*/
    TaperedTopHatDD(void);

    /* ------- Inherited   -------------------*/

    double operator() (double x1, double y1);

  };

  

}

#endif
