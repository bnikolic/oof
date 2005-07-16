/*
  Bojan Nikolic
  $Id: oneddiff.cxx,v 1.2 2005/07/16 15:50:17 bnikolic Exp $
  
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


