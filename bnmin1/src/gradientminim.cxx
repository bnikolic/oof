/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2008

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file gradientminim.cxx

*/

#include "gradientminim.hxx"
#include "gradientmodel.hxx"

#include <gsl/gsl_multimin.h>


#include <boost/mem_fn.hpp>

#include <iostream>
#include <stdexcept>

namespace Minim {

  struct GSLGradWrap
  {
    
    ModelDesc &minim;
    LGradientModel &model;
    size_t n;

    GSLGradWrap(ModelDesc &minim,
		LGradientModel &model):
      minim(minim),
      model(model),
      n(minim.NParam())
    {
    }

    void setpars(const gsl_vector * X)
    {
      std::vector<double> pars(n);
      for(size_t i = 0; i<n; ++i)
      {
	pars[i]=gsl_vector_get(X,i);
      }
      minim.put(pars);
    }

    double f(const gsl_vector * X)
    {
      setpars(X);
      const double res=model.lLikely();
      return res;
    }

    void df(const gsl_vector * X, 
	    gsl_vector * G)
    {
      setpars(X);
      std::vector<double> g;
      model.lGrd(g);
      for(size_t i =0 ; i < g.size(); ++i)
      {
	gsl_vector_set(G,i,g[i]);
      }

    }

    void fdf (const gsl_vector * X, 
	      double * f, 
	      gsl_vector * G)
    {
      setpars(X);
      *f=model.lLikely();
      std::vector<double> g;
      model.lGrd(g);
      for(size_t i =0 ; i < g.size(); ++i)
      {
	gsl_vector_set(G,i,g[i]);
      }
    }

  };

  double bngsl_f(const gsl_vector * X, 
		 void * PARAMS)
  {
    if (not PARAMS)
    {
      throw std::runtime_error("BNGSL not passed a pointer to data class");
    }
    return reinterpret_cast<GSLGradWrap*>(PARAMS)->f(X);
  }

  void bngsl_df(const gsl_vector * X, 
		void * PARAMS, 
		gsl_vector * G)  
  {
    if (not PARAMS)
    {
      throw std::runtime_error("BNGSL not passed a pointer to data class");
    }
    reinterpret_cast<GSLGradWrap*>(PARAMS)->df(X,G);
  }

  void bngsl_fdf (const gsl_vector * X, 
		  void * PARAMS, 
		  double * f, 
		  gsl_vector * G)
  {
    if (not PARAMS)
    {
      throw std::runtime_error("BNGSL not passed a pointer to data class");
    }
    reinterpret_cast<GSLGradWrap*>(PARAMS)->fdf(X,f,G);
  }
  
    

  BFGS2Minim::BFGS2Minim(LGradientModel &pm):
    ModelDesc(pm),
    lgm(pm)
  {
  }

  void BFGS2Minim::solve(void)
  {
    GSLGradWrap w(*this, lgm);
    // Function to minimise
    gsl_multimin_function_fdf mfunc;

    mfunc.n=NParam();
    mfunc.f=&bngsl_f;
    mfunc.df=&bngsl_df;
    mfunc.fdf=&bngsl_fdf;
    mfunc.params=reinterpret_cast<void*>(&w);
    
    gsl_vector *startp = gsl_vector_alloc(NParam());
    std::vector<double> startv(NParam());
    get(startv);
    for (size_t i =0; i<startv.size(); ++i)
    {
      gsl_vector_set(startp,i,startv[i]);
    }

    gsl_multimin_fdfminimizer *s=gsl_multimin_fdfminimizer_alloc(gsl_multimin_fdfminimizer_vector_bfgs2,
								 NParam());
    gsl_multimin_fdfminimizer_set(s,
				  &mfunc,
				  startp, 
				  0.01,
				  1e-4);

    size_t iter=0;
    int status;
    do
    {
      ++iter;
      status = gsl_multimin_fdfminimizer_iterate(s);

      if (status)
      {
	break;
	//throw std::runtime_error("Problem in minimisation iteration");
      }
      
      status = gsl_multimin_test_gradient(s->gradient,
					  1e-3);
      
    }
    while (status == GSL_CONTINUE && iter < 100);
    
    gsl_multimin_fdfminimizer_free(s);
    gsl_vector_free(startp);
    
  }    
}



