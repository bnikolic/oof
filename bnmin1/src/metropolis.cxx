/**
   \file metropolis.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <list>
#include <memory>
#include <cmath>

#include "metropolis.hxx"


namespace Minim {

  MetropolisMCMC::MetropolisMCMC(MLikelihood & ml,
				 const std::vector<double> & sigmas,
				 unsigned seed
				 ):
    ModelDesc(ml),
    ml(ml),
    sigmas(sigmas),
    generator(seed),
    uni_dist(0,1),
    norm(generator, norm_dist),
    uni(generator, uni_dist)
  {
  }

  void MetropolisMCMC::displace( std::vector<double> &x)
  {
    for (size_t i =0 ; i < sigmas.size() ; ++i)
      x[i] += sigmas[i]* norm();
  }

  std::list<MCPoint> *
  MetropolisMCMC::sample(size_t npropose)
  {
    if (sigmas.size() != NParam() )
      throw Error("Number of sigmas not consistent with number of pars set to fit");

    std::auto_ptr< std::list<MCPoint> > res
      (new std::list<MCPoint> ) ;

    // Current point in chain
    std::vector<double> cpoint( sigmas.size() );
    get(cpoint);

    // Current likelihood
    double clogl = - ml.lLikely();
    
    std::vector<double> propose( sigmas.size() );
    
    for(size_t sn =0 ; sn < npropose; ++sn)
    {
      propose=cpoint;
      displace(propose);      
      put(propose);

      double proplogl = - ml.lLikely();
      double    ldiff = proplogl - clogl;

      // If new point more likely than old, definitly accept (ldiff
      // >0). If new point less likely accept with probability
      // exp(ldiff)

      if (ldiff > 0 or 
	  uni() < exp(ldiff) )
      {
	MCPoint mcp;
	mcp.p=propose;
	mcp.ll=proplogl;
	res->push_back(mcp);
	cpoint=propose;
	clogl =proplogl;      
      }
    }

    return res.release();

  }

  


}

