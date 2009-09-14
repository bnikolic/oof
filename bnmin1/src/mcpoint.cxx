/**
   \file mcpoint.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "mcpoint.hxx"

namespace Minim {
  
  MCPoint::MCPoint(void):
    p(0),
    ll(-9999),
    fval(0)
  {
  }
  
  MCPoint::MCPoint(const std::vector<double> &p):
    p(p),
    ll(-9999),
    fval(0)
  {
  }  

  MCPoint::MCPoint(size_t np):
    p(np),
    ll(-9999),
    fval(0)
  {
  }

  MCPoint::MCPoint(const MCPoint &other):
    p(other.p),
    ll(other.ll),
    fval(other.fval)
  {
  }

  MCPoint &MCPoint::operator=(const MCPoint &other)
  {
    p=other.p;
    ll=other.ll;
    fval=other.fval;
    return *this;
  }


}

