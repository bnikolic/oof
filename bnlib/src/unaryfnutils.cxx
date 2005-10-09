/*
  Bojan Nikolic
  $Id: unaryfnutils.cxx,v 1.2 2005/10/09 22:18:02 bnikolic Exp $
*/

#include "unaryfnutils.hxx"


namespace BNLib {

  ConstUDD::ConstUDD( double c):
    c(c)
  {
  }

  double ConstUDD::operator() (double x) 
  {
    return c;
  }



}


