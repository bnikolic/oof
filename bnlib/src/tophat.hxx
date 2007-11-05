/**
   \file tophat.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   A 2-d tophat functions
*/

#ifndef _BNLIB_TOPHAT_HXX__
#define _BNLIB_TOPHAT_HXX__

#include "binaryfn.hxx"

namespace BNLib {

  /*! 
    Defines a top hat function, i.e., a function which s.t.:
    \f[
    f(x,y) = 1 {\quad \rm if \quad} x^{2}+y^{2} \leq 1
    \f]
    \f[
    f(x,y) = 0 {\quad \rm otherwise}
    \f]
  */
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

  /*! 
     This is useful for modeling the Moon. See 1998A&AS..133..271G for
     justification.
  
  */
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
