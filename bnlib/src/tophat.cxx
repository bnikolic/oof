/*
  Bojan Nikolic
  $Id: tophat.cxx,v 1.1 2005/08/31 02:32:04 bnikolic Exp $
*/

#include "tophat.hxx"

#include <cmath>

namespace BNLib {

  TopHatDD::TopHatDD(void):
    x0(0) , y0(0) , radius(1)
  {

  }

  double TopHatDD::operator() (double x1, double y1)
  {

    if ( pow( x1-x0 , 2) + pow(y1-y0, 2) > pow (radius, 2) )
      {
	return 0;
      }
    else 
      {
	return 1;
      }
  }
  

}


