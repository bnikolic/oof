/**
   \file nestedsampler.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>
#include <iostream>

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include <boost/assign/list_of.hpp>

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
    ModelDesc(ml),
    Zseq(1,0.0),
    Xseq(1,1.0),
    ml(ml),
    md(ml),
    //ps(new CSPMetro(ml, sigmas, seed)),
    //ps(new CSPAdaptive(ml, *this, sigmas)),
    ps(new CSRMSSS(ml, *this, g_ss())),
    sigmas(sigmas),
    mon(NULL),
    n_psample(100)
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

  NestedS::NestedS(PriorNLikelihood & ml,
		   const std::vector<double> & sigmas,
		   unsigned seed):
    ModelDesc(ml),
    Zseq(1,0.0),
    Xseq(1,1.0),
    ml(ml),
    md(ml),
    ps(NULL),
    sigmas(sigmas),
    mon(NULL),
    n_psample(100)
  {
  }

  NestedS::~NestedS(void)
  {
    if(ps)
    {
      delete ps->mon;
    }
  }

  void NestedS::reset(const std::list<MCPoint> &start)
  {
    if (start.size() < 2)
    {
      throw NestedSmallStart(start);
    }
    if (start.begin()->p.size() != NParam())
    {
      throw BaseErr("Dimension of start set points is not the same as number of parameters to fit");
    }

    ps.reset(new CSRMSSS(ml, 
			 *this, 
			 g_ss()));
    Zseq=boost::assign::list_of(0.0);
    Xseq=boost::assign::list_of(1.0);
    llPoint(ml,
	    start,
	    ss);
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

      // Look for the next sample
      md.put(worst->p);
      const double newl = ps->advance(-worst->ll,
				      n_psample);
      // Is the new sample actually inside the contours of last?
      const bool better = newl > -worst->ll;
      
      if (not better)
      {
	// Can't find a better point so terminate early
	break;
      }

      // Save the point about to be bumped off
      Zseq.push_back(Zseq[Zseq.size()-1] + Llow* w);
      Xseq.push_back(X);
      post.push_back(WPPoint(*worst, w));

      // Create new point
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
  
  const std::set<MCPoint> & NestedS::g_ss(void) const
  {
    return ss;
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
      MCPoint p(i->p);
      m.put(p.p);
      p.ll=ml.llprob();
      res.insert(p);
    }
  }

  void startSetDirect(IndependentFlatPriors &prior,
		      size_t n,
		      std::list<MCPoint> &res,
		      unsigned seed)
  {
    const size_t nprior=prior.npriors();

    boost::mt19937 rng(seed);
    boost::uniform_01<boost::mt19937> zo(rng);

    Minim::MCPoint p(nprior); 
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

  void printSS(const std::set<MCPoint> &ss)
  {
    for(std::set<MCPoint>::const_iterator i(ss.begin());
	i != ss.end();
	++i)
    {
      std::cout<<"p:";
      for(size_t j=0; j<i->p.size(); ++j)
	std::cout<<i->p[j]
		 <<",";
      std::cout<<i->ll<<",";
      std::cout<<std::endl;
    }
  }

}


