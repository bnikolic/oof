/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2011

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file simplexminim.cxx
*/

#include "simplexminim.hxx"

namespace Minim {

  SimplexMinim::SimplexMinim(MLikelihood &m):
    ModelDesc(m),
    m(m)
  {
  }

  SimplexMinim::~SimplexMinim()
  {
  }

  void SimplexMinim::solve(void)
  {

  }

}

