/**
   \file mcpoint.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

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

  void moment1(const std::list<WPPoint> &l,
	       std::vector<double> &res)
  {
    const size_t n=l.begin()->p.size();
    res=std::vector<double>(n, 0.0);
    for(std::list<WPPoint>::const_iterator i=l.begin();
	i!= l.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	  res[j]+= (i->p[j] * i->w * exp(- i->ll));
      }
    }
  }


}

