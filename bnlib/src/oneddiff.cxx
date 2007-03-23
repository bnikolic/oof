/*
  Copyright:
  Bojan Nikolic
  
*/

#include "oneddiff.hxx"

namespace BNLib {

  LinDiff::LinDiff ( UnaryDD &fn, double eps ):
    fn(fn),
    eps(eps)
  {
  }

  double LinDiff::operator() (double x)  
  {
    // Use a symetric difference here 
    double y1 = fn(x+eps);
    double y2 = fn(x-eps);

    return (y1-y2) / ( 2* eps );

  }
  



}


