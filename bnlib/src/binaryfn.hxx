/*
  Bojan Nikolic
  $Id: binaryfn.hxx,v 1.1 2005/06/21 11:42:12 bnikolic Exp $

  Declares a simple binary function class 

*/
#ifndef _BNLIB_BINARYFN_HXX___
#define _BNLIB_BINARYFN_HXX___

namespace BNLib {


  class BinaryDD {

  public:

    virtual double operator() (double x, double y) =0 ;

  };


}


#endif
