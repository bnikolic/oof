/**
   \file mcpoint.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

#include "mcpoint.hxx"

namespace Minim {
  
  MCPoint::MCPoint(void):
    p(0),
    ll(-9999),
    fval(0)
  {
  }
  
  MCPoint::MCPoint(const std::vector<double> &p):
    p(p),
    ll(-9999),
    fval(0)
  {
  }  

  MCPoint::MCPoint(size_t np):
    p(np),
    ll(-9999),
    fval(0)
  {
  }

  MCPoint::MCPoint(const MCPoint &other):
    p(other.p),
    ll(other.ll),
    fval(other.fval)
  {
  }

  MCPoint &MCPoint::operator=(const MCPoint &other)
  {
    p=other.p;
    ll=other.ll;
    fval=other.fval;
    return *this;
  }

  void moment1(const std::list<WPPoint> &l,
	       std::vector<double> &res)
  {
    const size_t n=l.begin()->p.size();
    res=std::vector<double>(n, 0.0);
    for(std::list<WPPoint>::const_iterator i=l.begin();
	i!= l.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	  res[j]+= (i->p[j] * i->w * exp(- i->ll));
      }
    }
  }

  void moment1(const std::list<WPPoint> &l,
	       double Z,
	       std::vector<double> &res)
  {
    moment1(l,res);
    for(size_t j=0; j<res.size(); ++j)
      res[j] /= Z;
  }

  void moment2(const std::list<WPPoint> &l,
	       const std::vector<double> &m1,
	       std::vector<double> &res)
  {
    const size_t n=m1.size();
    res=std::vector<double>(n, 0.0);
    for(std::list<WPPoint>::const_iterator i=l.begin();
	i!= l.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	res[j]+= ( pow(i->p[j]-m1[j],2.0) * i->w * exp(- i->ll));
      }
    }
  }

  void moment2(const std::list<WPPoint> &l,
	       const std::vector<double> &m1,
	       double Z,
	       std::vector<double> &res)
  {
    moment2(l, m1, res);
    for(size_t j=0; j<res.size(); ++j)
      res[j] /= Z;    
  }

  void moment1(const std::set<MCPoint> &s,
	       std::vector<double> &res)
  {
    const size_t n=s.begin()->p.size();
    res=std::vector<double>(n, 0.0);

    size_t N=0;
    for(std::set<MCPoint>::const_iterator i=s.begin();
	i!= s.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	res[j]+= (i->p[j]);
      }
      ++N;
    }
    
    for(size_t j=0; j<res.size(); ++j)
    {
      res[j]/=N;
    }
  }

  void moment2(const std::set<MCPoint> &s,
	       const std::vector<double> &m1,
	       std::vector<double> &res)
  {
    const size_t n=m1.size();
    res=std::vector<double>(n, 0.0);

    size_t N=0;
    for(std::set<MCPoint>::const_iterator i=s.begin();
	i!= s.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	res[j]+= pow(i->p[j]-m1[j], 2);
      }
      ++N;
    }
    
    for(size_t j=0; j<res.size(); ++j)
    {
      res[j]/=N;
    }
  }

  void StdDev(const std::set<MCPoint> &s,
	      std::vector<double> &res)
  {
    std::vector<double> m1, m2;
    moment1(s, m1);
    moment2(s, m1, m2);
    res.resize(m2.size());
    for(size_t j=0; j<res.size(); ++j)
    {
      res[j]=pow(m2[j],0.5);
    }
  }


}

