/**
   \file markovchain.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
*/

#include "markovchain.hxx"

namespace Minim {

  MarkovChain::MarkovChain(fx_t fLkl,
			   fx_t fPr,
			   size_t n):
    fLkl(fLkl),
    fPr(fPr),
    fAccept(metropolis),
    ngen(igen,
	 norm_dist),
    u01gen(igen),
    n(n)
  {
  }

  void MarkovChain::propose(const std::vector<double> &x)
  {
    p.x=x;
    p.l=fLkl(x);
    p.p=fPr(x);

    const double aprob=fAccept(c,p);
    
    if (aprob>=1.0)
    {
      c=p;
    }
    else
    {
      if(u01gen() < aprob)
      {
	c=p;
      }
    }
  }

  void normProp(const MarkovChain &c,
		const std::vector<double> &sigma,
		std::vector<double> &res)
  {
    res=c.gcx();
    for(size_t i=0; i<res.size(); ++i)
    {
      res[i]+= sigma[i]*c.ngen();
    }
  }

  double metropolis(const MCPoint2 &c, 
		    const MCPoint2 &p)
  {
    if (p.l<c.l)
      return 1;
    else
      return exp(c.l-p.l);
  }


}


