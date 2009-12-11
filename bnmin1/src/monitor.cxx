/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file monitor.cxx


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



