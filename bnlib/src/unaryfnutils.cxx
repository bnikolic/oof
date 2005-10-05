/*
  Bojan Nikolic
  $Id: unaryfnutils.cxx,v 1.1 2005/10/05 03:06:00 bnikolic Exp $
*/

#include "unaryfnutils.hxx"


namespace BNLib {

  ConstUDD::ConstUDD( double c):
    c(c)
  {
  }

  double ConstUDD::operator() (double x) 
  {
    return x;
  }



}


