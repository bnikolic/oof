/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

#include "nestedsampler.hxx"
#include "priors.hxx"
#include "minim.hxx"
#include "prior_sampler.hxx"

namespace Minim {

  NestedS::NestedS(IndependentPriors & ml,
		   std::list<MCPoint> start,
		   const std::vector<double> & sigmas,
		   unsigned seed):
    Zseq(1,0.0),
    Xseq(1,0.0),
    ml(ml),
    md(ml),
    ps(new CPriorSampler(ml, sigmas, seed))
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
      std::set<MCPoint>::iterator worst( --ss.end() );

      const double Llow=exp(-worst->ll);
      const double X=exp(-((double)Xseq.size())/N());
      const double w=Xseq[Xseq.size()-1]-X;

      Zseq.push_back(Zseq[Zseq.size()-1] + Llow* w);
      Xseq.push_back(X);

      // Now just need to replace the Llow object
      md.put(worst->p);
      const double newl = ps->advance(-worst->ll,
				      100);

      MCPoint np;
      np.p.resize(md.NParam());
      md.get(np.p);
      np.ll=-newl;
      ss.erase(worst);
      ss.insert(np);
      
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


