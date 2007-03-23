/*
  Copyright:
  Bojan Nikolic

*/
#include "onedmin.hxx"

#include <gsl/gsl_min.h>
#include <gsl/gsl_errno.h>

#include <iostream>

#include "unaryfn.hxx"
#include "gsl_utils.hxx"

namespace BNLib {

  double  GSLMinimHelper( double x, void * pars)
  {
    UnaryDD * fn = static_cast<UnaryDD * > (pars);
    return (*fn)(x);
  }


  class GSLMinim {

  public:
    
    /// Minimiser data is kept here
    gsl_min_fminimizer *s;

    /// The gsl function data  is kept here
    gsl_function GSLF;

    /// The function to be minimised is fn.
    GSLMinim(    UnaryDD *fn) :
      s(gsl_min_fminimizer_alloc (gsl_min_fminimizer_brent ) )
    {
      GSLF.function = &GSLMinimHelper;
      GSLF.params=fn;
    }

    ~GSLMinim()
    {
      gsl_min_fminimizer_free(s);
    }

  };


  double Min1D ( UnaryDD & fn , 
		 double xmin, double xmax,
		 double xguess,
		 double epsrel,
		 double epsabs,
		 unsigned maxiter)
  {

    // This turns off the crazy gsl error handler which aborts the program
    GSLCheck gslcheck;

    GSLMinim gslm( &fn);
    
    gsl_min_fminimizer_set (gslm.s, &gslm.GSLF, 
			    xguess, xmin, xmax);

    unsigned iter(0);
    int status;
    double m ,a ,b;
    
    do
      {
	iter++;
	status = gsl_min_fminimizer_iterate (gslm.s);
	
	m = gsl_min_fminimizer_x_minimum (gslm.s);
	a = gsl_min_fminimizer_x_lower (gslm.s);
	b = gsl_min_fminimizer_x_upper (gslm.s);

	//std::cerr<<"a: " << a << " b: " << b << std::endl;
     
	status 
	  = gsl_min_test_interval (a, b, 0.001, 0.0);
     
      }
    while (status == GSL_CONTINUE && iter < maxiter);
    
    if (status == GSL_SUCCESS ) 
      {
      return m;
      }
    else 
      {
	///no convergance
	//std::cerr<<status;
	throw (status);
      }
  }

}


