/*
  Bojan Nikolic
  $Id: unaryfn.hxx,v 1.2 2005/10/05 03:05:41 bnikolic Exp $

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
