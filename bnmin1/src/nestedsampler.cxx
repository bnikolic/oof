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
#include "nestedinitial.hxx"

namespace Minim {

  NestedS::NestedS(PriorNLikelihood & ml,
		   const std::list<MCPoint> & start,
		   unsigned seed) throw (NestedSmallStart):
    ModelDesc(ml),
    Zseq(1,0.0),
    Xseq(1,1.0),
    ml(ml),
    //ps(new CSPMetro(ml, sigmas, seed)),
    //ps(new CSPAdaptive(ml, *this, sigmas)),
    ps(new CSRMSSS(ml, *this, g_ss())),
    initials(new InitialWorst()),
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
		   unsigned seed):
    ModelDesc(ml),
    Zseq(1,0.0),
    Xseq(1,1.0),
    ml(ml),
    ps(NULL),
    initials(new InitialWorst()),
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
	    *this,
	    start,
	    ss);
  }

  void NestedS::InitalS(NestedInitial *ins)
  {
    initials.reset(ins);
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
      put((*initials)(*this).p);
      //put(worst->p);
      const double newl = ps->advance(worst->ll,
				      n_psample);

      // Create new point
      MCPoint np;
      np.p.resize(NParam());
      get(np.p);
      np.ll=-newl;

      // Is the new sample actually inside the contours of last?
      const bool better = -newl  < worst->ll;

      if (not better )
      {
	// Can't find a better point so terminate early.

	// Note that this test is not definitive, since some
	// strategies will start from a point which not the worst
	// point and hence will return a "better" point event though
	// they haven not actually advanced their chain at all. See
	// below.

	break;
      }

      // Save the point about to be bumped off
      Zseq.push_back(Zseq[Zseq.size()-1] + Llow* w);
      Xseq.push_back(X);
      post.push_back(WPPoint(*worst, w));

      // Erase old point
      ss.erase(worst);
      
      std::pair<std::set<MCPoint>::iterator, bool> r=ss.insert(np);
      if (not r.second)
      {
	// Could not insert a point because it has identical
	// likelihood to an existing point. Can not contiue as we have
	// fewer points in the live set now.

	// Note that this is often due to the chain not avancing in
	// the constained sampler.
	break;
      }

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
	       ModelDesc &md,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res)
  {
    for(std::list<MCPoint>::const_iterator i(lp.begin());
	i != lp.end();
	++i)
    {
      MCPoint p(i->p);
      md.put(p.p);
      p.ll=ml.llprob();
      res.insert(p);
    }
  }

  void llPoint(PriorNLikelihood & ml,
	       const std::list<MCPoint> &lp,
	       std::set<MCPoint> &res)
  {
    ModelDesc m(ml);
    llPoint(ml,
	    m,
	    lp,
	    res);
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


