/**
   \file mcpoint.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

*/

#include <cmath>

#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

#include "mcpoint.hxx"
#include "bnmin_main.hxx"

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
      if(i->p.size() != n)
      {
	throw NParsErr("moment1", n, i->p.size());
      }
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

  void omoment2(const std::set<MCPoint> &s,
		const std::vector<double> &m1,
		std::vector<double> &res)
  {
    const size_t n=m1.size();
    res=std::vector<double>(n*n, 0.0);

    size_t N=0;
    for(std::set<MCPoint>::const_iterator i=s.begin();
	i!= s.end();
	++i)
    {
      for (size_t j=0; j<n; ++j)
      {
	for(size_t k=0; k<n; ++k)
	{
	  res[j*n+k] += (i->p[j]-m1[j])*(i->p[k]-m1[k]);
	}
      }
      ++N;
    }
    
    for(size_t j=0; j<res.size(); ++j)
    {
      res[j]/=N;
    }

  }
  void omoment2(const std::set<MCPoint> &s,
		std::vector<double> &res)
  {
    std::vector<double> m1;
    moment1(s, m1);
    omoment2(s, m1, res);
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

  void principalCV(const std::vector<double> &cv,
		   std::vector<double> &res)
  {
    const size_t n=sqrt(cv.size());
    gsl_matrix_view m
      = gsl_matrix_view_array (const_cast<double*>(&cv[0]), n, n);

    gsl_vector *eval = gsl_vector_alloc (n);
    gsl_matrix *evec = gsl_matrix_alloc (n, n);

    gsl_eigen_symmv_workspace * w =
      gsl_eigen_symmv_alloc (n);

    gsl_eigen_symmv (&m.matrix,
		     eval,
		     evec,
		     w);

    gsl_eigen_symmv_free (w);
    
    gsl_eigen_symmv_sort (eval, 
			  evec,
			  GSL_EIGEN_SORT_ABS_ASC);

    res.resize(n*n);
    for(size_t j=0; j<n; ++j)
    {
      for(size_t i=0; i<n; ++i)
      {
	res[j*n+i]= gsl_vector_get (eval, j) * 
	  gsl_matrix_get(evec, i,j);
      }
    }
    
    gsl_vector_free (eval);
    gsl_matrix_free (evec);
  }

}

