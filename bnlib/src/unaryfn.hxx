/*
  Bojan Nikolic
  $Id: unaryfn.hxx,v 1.1 2005/05/04 21:07:55 bnikolic Exp $

  Declares a simple unary function class 

*/
#ifndef _BNLIB_UNARYFN_HXX___
#define _BNLIB_UNARYFN_HXX___

namespace BNLib {

  /// Base class for unary functions taking a double and returning a
  /// double
  class UnaryDD {

  public:

    virtual double operator() (double x) =0 ;

  };


}


#endif
