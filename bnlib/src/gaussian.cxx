/*
  Copyright:
  Bojan Nikolic

*/

#include "gaussian.hxx"

#include <cmath>


namespace BNLib {
  
  GaussianDD::GaussianDD(void):
    x0(0 ) , y0(0),
    sigma(1) , rho(0) , diff(0 ),
    amp(1)
  {
  }

  GaussianDD::GaussianDD(double sigma):
    x0(0 ) , y0(0),
    sigma(sigma) , rho(0) , diff(0 ),
    amp(1)
  {
  }

  GaussianDD::GaussianDD(double sigma, double x0 , double y0):
    x0(x0 ) , y0(y0),
    sigma(sigma) , rho(0) , diff(0 ),
    amp(1)
  {
  }

  double GaussianDD::operator() (double x1, double y1) 
  {
    double dx ( x1- x0);
    double dy ( y1- y0);

    return amp * exp ( -1.0 * ( 1.0/(2*sigma)   *  ( pow(dx,2) + pow(dy,2 ) ) +
				rho *  ( dx*dy)  +
				diff   *  ( pow(dx,2) - pow(dy,2 ) )));

  }  

}


