/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include "nestedsampler.hxx"
#include "priors.hxx"
#include "minim.hxx"
#include "prior_sampler.hxx"
#include "nestederr.hxx"
#include "mcmonitor.hxx"

namespace Minim {

  NestedS::NestedS(PriorNLikelihood & ml,
		   const std::list<MCPoint> & start,
		   const std::vector<double> & sigmas,
		   unsigned seed) throw (NestedSmallStart):
    Zseq(1,0.0),
    Xseq(1,1.0),
    ml(ml),
    md(ml),
    ps(new CPriorSampler(ml, sigmas, seed)),
    mon(NULL)
  {
    llPoint(ml,
	    start,
	    ss);

    //ps->mon= new SOutMCMon();
    
    if (ss.size() < 2)
    {
      throw NestedSmallStart(start);
    }
  }

  NestedS::~NestedS(void)
  {
    delete ps->mon;
  }

  size_t NestedS::N(void) const
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
      
      post.push_back(WPPoint(*worst, w));

      // Now just need to replace the Llow object
      md.put(worst->p);
      const double newl = ps->advance(-worst->ll,
				      100);

      const bool better = newl > -worst->ll;
      
      if (not better)
      {
	throw BaseErr("Could not obtain a better point");
      }

      MCPoint np;
      np.p.resize(md.NParam());
      md.get(np.p);
      np.ll=-newl;
      ss.erase(worst);
      ss.insert(np);
      if(mon)
	mon->accept(np);
      
    }
    return Zseq[Zseq.size()-1];
  }

  
  const std::list<WPPoint> & NestedS::g_post(void) const
  {
    return post;
  }
  
  

  void llPoint(PriorNLikelihood & ml,
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

  void startSetDirect(const IndependentFlatPriors &prior,
		      size_t n,
		      std::list<MCPoint> &res,
		      unsigned seed)
  {
    boost::mt19937 rng(seed);
    boost::uniform_01<boost::mt19937> zo(rng);

    Minim::MCPoint p(prior.npriors()); 
    for(size_t i=0; i<n; ++i)
    {
      size_t j=0;
      for (IndependentFlatPriors::priorlist_t::const_iterator dimp(prior.pbegin());
	   dimp != prior.pend();
	   ++dimp)
      {
	p.p[j]=dimp->pmin+ (dimp->pmax - dimp->pmin)* zo();
	++j;
      }
      res.push_back(p);
    }

  }

}


