/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2008

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file metropolis.cxx

*/

#include <list>
#include <memory>
#include <cmath>
#include <boost/format.hpp>

#include "metropolis.hxx"
#include "metro_propose.hxx"


namespace Minim {

  MetropolisMCMC::MetropolisMCMC(MLikelihood & ml,
				 const std::vector<double> & sigmas,
				 unsigned seed,
				 Options opt):
    ModelDesc(ml),
    ml(ml),
    f(NULL)
  {
    if (opt & Sequence)
      prop.reset(new MetroProposeSeq(sigmas, seed));
    else
      prop.reset(new MetroPropose(sigmas, seed));
  }

  MetropolisMCMC::~MetropolisMCMC()
  {
  }

  std::list<MCPoint> *
  MetropolisMCMC::sample(size_t npropose)
  {
    if (prop->nPars() != NParam() )
    {
      throw Error((boost::format("Number of sigmas not consistent with number of pars\
 set to fit: expected %i, got %i") %  NParam() % prop->nPars()).str());
    }

    std::auto_ptr< std::list<MCPoint> > res
      (new std::list<MCPoint> ) ;

    // Current point in chain
    std::vector<double> cpoint( prop->nPars());
    get(cpoint);

    // Current likelihood
    double clogl = - ml.lLikely();
    
    std::vector<double> propose( prop->nPars() );
    
    for(size_t sn =0 ; sn < npropose; ++sn)
    {
      propose=cpoint;
      prop->displace(propose);      
      put(propose);

      double proplogl = - ml.lLikely();
      double    ldiff = proplogl - clogl;

      // If new point more likely than old, definitly accept (ldiff
      // >0). If new point less likely accept with probability
      // exp(ldiff)

      if (ldiff > 0 or 
	  prop->raccept() < exp(ldiff) )
      {
	MCPoint mcp(propose);
	mcp.ll=proplogl;
	if (f)
	  f(mcp.fval);
	res->push_back(mcp);
	cpoint=propose;
	clogl =proplogl;      
      }
    }

    return res.release();

  }

  


}

