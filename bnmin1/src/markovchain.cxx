/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file markovchain.cxx
   
*/

#include "markovchain.hxx"

namespace Minim {

  ChainBase::ChainBase(const v_t &ic,
		       fx_t fLkl,
		       fx_t fPr):
    fLkl(fLkl),
    fPr(fPr),
    ngen(igen,
	 norm_dist),
    u01gen(igen),
    n(ic.size())
  {
    reset(ic);
  }

  ChainBase::~ChainBase()
  {
  }

  void ChainBase::reset(const v_t &x)
  {
    c.x=x;
    c.l=fLkl(x);
    c.p=fPr(x);    
  }

  MarkovChain::MarkovChain(const v_t &ic,
			   fx_t fLkl,
			   fx_t fPr,
			   fa_t fAccept):
    ChainBase(ic,
	      fLkl,
	      fPr),
    fAccept(fAccept)
  {
  }

  bool MarkovChain::propose(const std::vector<double> &x)
  {
    p.x=x;
    p.l=fLkl(x);
    p.p=fPr(x);

    const double aprob=fAccept(c,p);
    
    if (aprob>=1.0)
    {
      c=p;
      return true;
    }
    else
    {
      if(u01gen() < aprob)
      {
	c=p;
	return true;
      }
    }
    return false;
  }

  InitPntChain::InitPntChain(const v_t &ic,
			     fx_t fLkl,
			     fx_t fPr,
			     fa_t fAccept):
    ChainBase(ic,
	      fLkl,
	      fPr),
    fAccept(fAccept)
  {
    f=c;
  }

  bool InitPntChain::propose(const v_t &x)
  {
    p.x=x;
    p.l=fLkl(x);
    p.p=fPr(x);

    const double aprob=fAccept(f,c,p);
    
    if (aprob>=1.0)
    {
      c=p;
      return true;
    }
    else
    {
      if(u01gen() < aprob)
      {
	c=p;
	return true;
      }
    }
    return false;
  }

  void InitPntChain::reset(const v_t &x)
  {
    ChainBase::reset(x);
    f=c;
  }

  ILklChain::ILklChain(const v_t &ic,
		       fx_t fLkl,
		       fx_t fPr,
		       fa_t fAccept):
    ChainBase(ic,
	      fLkl,
	      fPr),
    fAccept(fAccept)
  {
    L=c.l;
  }

  bool ILklChain::propose(const v_t &x)
  {
    p.x=x;
    p.l=fLkl(x);
    p.p=fPr(x);

    const double aprob=fAccept(L,c,p);
    
    if (aprob>=1.0)
    {
      c=p;
      return true;
    }
    else
    {
      if(u01gen() < aprob)
      {
	c=p;
	return true;
      }
    }
    return false;
  }

  void ILklChain::reset(const v_t &x,
			double Ls)
  {
    ChainBase::reset(x);
    L=Ls;
  }

  bool normProp(ChainBase &c,
		const std::vector<double> &sigma)
  {
    const std::vector<double> & cx=c.gcx();
    std::vector<double> px(cx.size());
    for(size_t i=0; i<cx.size(); ++i)
    {
      px[i]= cx[i]+ sigma[i]*c.ngen();
    }
    return c.propose(px);
  }

  bool normProp(ChainBase &c,
		size_t i,
		double s)
  {
    const std::vector<double> &cx=c.gcx();
    std::vector<double> px(cx);
    px[i]+= s*c.ngen();
    return c.propose(px);
  }

  bool eigenProp(ChainBase &c,
		 const std::vector<double> &eigvals,
		 const std::vector<double> &eigvects
		 )
  {
    const size_t n=eigvals.size();
    const std::vector<double> &cx=c.gcx();
    std::vector<double> px(cx);
    for(size_t i=0; i<n; ++i)
    {
      const double s=eigvals[i]*c.ngen();
      for(size_t j=0; j<n; ++j)
      {
	px[j]+= s*eigvects[i*n+j];
      }
    }
    return c.propose(px);

  }

  double metropolis(const MCPoint2 &c, 
		    const MCPoint2 &p)
  {
    if (p.l<c.l)
      return 1;
    else
      return exp(c.l-p.l);
  }

  double constrPrior(const MCPoint2 &c, 
		     const MCPoint2 &p)
  {
    if(p.l >= c.l)
      return 0;
    else
    {
      if (p.p<c.p)
      {
	return 1;
      }
      else
      {
	return exp(c.p-p.p);
      }
    }
  }

  double constrPriorP(const MCPoint2 &f,
		      const MCPoint2 &c, 
		      const MCPoint2 &p)
  {
    if(p.l >= f.l)
      return 0;
    else
    {
      if (p.p<c.p)
      {
	return 1;
      }
      else
      {
	return exp(c.p-p.p);
      }
    }
  }    

  double constrPriorL(double L,
		      const MCPoint2 &c, 
		      const MCPoint2 &p)
  {
    if(p.l >= L)
      return 0;
    else
    {
      if (p.p<c.p)
      {
	return 1;
      }
      else
      {
	return exp(c.p-p.p);
      }
    }
  }


}


