/*
  Bojan Nikolic
  $Id: monitor.cxx,v 1.1 2005/08/18 04:57:08 bnikolic Exp $

*/

#include "monitor.hxx"

#include "minim.hxx"

#include <iostream>

namespace Minim {


  void ChiSqMonitor::Iter ( Minimiser * m)
  {
    std::cerr<<"Chi-squared: " << m->ChiSquared() <<std::endl;
  }


}



