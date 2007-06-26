/**
   \file unaryfn.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   
   Declares a simple unary function class 

*/
#ifndef _BNLIB_UNARYFN_HXX___
#define _BNLIB_UNARYFN_HXX___

namespace BNLib {

  /// Base class for unary functions taking a double and returning a
  /// double
  class UnaryDD {

  public:

    virtual ~UnaryDD() {} ;

    virtual double operator() (double x) =0 ;


  };


}


#endif
