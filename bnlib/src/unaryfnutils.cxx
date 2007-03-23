/*
  Bojan Nikolic

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


