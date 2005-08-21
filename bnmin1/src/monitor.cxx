/*
  Bojan Nikolic
  $Id: monitor.cxx,v 1.2 2005/08/21 02:42:03 bnikolic Exp $

*/

#include "monitor.hxx"

#include "minim.hxx"
#include "minimio.hxx"

#include <iostream>

namespace Minim {


  void ChiSqMonitor::Iter ( Minimiser * m)
  {
    std::cerr<<"Chi-squared: " << m->ChiSquared() <<std::endl;
  }

  

  void  ParsMonitor::Iter ( Minimiser * m)
  {
    PrettyPrint ( *m );
  }

}



