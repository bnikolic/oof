/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include "nestedsampler.hxx"
#include "priors.hxx"
#include "minim.hxx"

namespace Minim {

  NestedS::NestedS(IndependentPriors & ml,
		   std::list<MCPoint> start,
		   const std::vector<double> & sigmas,
		   unsigned seed):
    Zseq(1,0.0),
    Xseq(1,0.0),
    ml(ml)
  {
  }

  NestedS::~NestedS(void)
  {
  }

  void llPoint(IndependentPriors & ml,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res)
  {
    ModelDesc m(ml);
    for(std::list<MCPoint>::const_iterator i(lp.begin());
	i != lp.end();
	++i)
    {
      MCPoint p=*i;
      m.put(p.p);
      p.ll=ml.llprob();
      res.insert(p);
    }
  }

}


