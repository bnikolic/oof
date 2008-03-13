/**
   \file monitor.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

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



