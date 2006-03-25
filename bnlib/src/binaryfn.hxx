/*
  Bojan Nikolic
  $Id: binaryfn.hxx,v 1.2 2006/03/25 14:29:30 bnikolic Exp $

  Declares a simple binary function class 

*/
#ifndef _BNLIB_BINARYFN_HXX___
#define _BNLIB_BINARYFN_HXX___

namespace BNLib {


  /*! Abstract base class representing functions taking two doubles
   *  and returning a double 
   */
  class BinaryDD {

  public:
    
    virtual ~BinaryDD() {};

    virtual double operator() (double x, double y) =0 ;

  };


}


#endif
