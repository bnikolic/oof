/**
   \file tophat.cxx
   Bojan Nikolic  <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include "tophat.hxx"
#include <iostream>

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

  TaperedTopHatDD::TaperedTopHatDD(void):
    TopHatDD()
  {

  }

  double TaperedTopHatDD::operator() (double x1, double y1)
  {
    if ( pow( x1-x0 , 2) + pow(y1-y0, 2) > pow (radius, 2) )
      {
	return 0;
      }
    else 
      {
	double rhosq  = (pow( x1-x0 , 2) + pow(y1-y0, 2) )/ pow (radius, 2);
	/*std::cerr<<rhosq<<std::endl;
	  std::cerr<<Cm<<std::endl;*/

	return 1 + Cm * (1 - rhosq );
      }
    

  }
  

}


