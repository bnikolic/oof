/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

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
    llPoint(ml,
	    start,
	    ss);
  }

  NestedS::~NestedS(void)
  {
  }

  size_t NestedS::N(void)
  {
    return ss.size();
  }

  double NestedS::sample(size_t j)
  {
    for (size_t i=0; i<j; ++i)
    {
      const double Llow=exp(- (--ss.end())->ll);
      const double X=exp(-Xseq.size()/N());
      const double w=Xseq[Xseq.size()-1]-X;
      
      Zseq.push_back(Zseq[Zseq.size()-1] + Llow* w);
      Xseq.push_back(X);

      // Now just need to replace the Llow object!
    }
    return Zseq[Zseq.size()-1];
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


