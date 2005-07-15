/*
  Bojan Nikolic
  $Id: onedroot.cxx,v 1.3 2005/07/15 22:09:35 bnikolic Exp $

*/

#include "onedroot.hxx"

#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

#include "unaryfn.hxx"

#include <iostream>

namespace BNLib {

  /*!
   * Helper fn to faciliate calling UnaryDD from C.
   */
  double  GSLRootHelper( double x, void * pars)
  {
    UnaryDD * fn = static_cast<UnaryDD * > (pars);
    return (*fn)(x);
  }


  /*!
   * Helper class that encapsulates the required GSL structures
   */
  class GSL1DRoot {

  public:

    /*! The root solver struct is here */
    gsl_root_fsolver *s;

    /*! The gsl function data  is kept here */
    gsl_function GSLF;

    /*!
     * fn: the function for which the root needs to be found
     */
    GSL1DRoot ( UnaryDD *fn ) :
      s(gsl_root_fsolver_alloc ( gsl_root_fsolver_brent ))
    {
      GSLF.function = &GSLRootHelper;
      GSLF.params=fn;
    }
    
    /*! 
     * Just need to free up the gsl root finder struct 
     */
    ~GSL1DRoot()
    {
      gsl_root_fsolver_free(s);
    }
    
  };

  
  double Root1D ( UnaryDD & fn , 
		  double xmin, double xmax,
		  double epsabs, double epsrel,
		  unsigned max_iter
		  )
  {

    GSL1DRoot gslrf( & fn );

    gsl_root_fsolver_set (gslrf.s, & gslrf.GSLF, xmin, xmax);

    unsigned iter(0);
    int status;

    // r is the best guess result
    double r;

    do
         {
           iter++;
           status = gsl_root_fsolver_iterate ( gslrf.s);
           r = gsl_root_fsolver_root (gslrf.s);
           xmin = gsl_root_fsolver_x_lower (gslrf.s);
           xmax = gsl_root_fsolver_x_upper (gslrf.s);

           status = gsl_root_test_interval (xmin, xmax,
                                            epsabs, 
					    epsrel);
         }
       while (status == GSL_CONTINUE && iter < max_iter);

    if (status == GSL_SUCCESS ) 
      {
	std::cerr<<"Found root: "<<r<<std::endl;
	return r;
      }
    else 
      {
	///no convergance
	throw (status);
      }    

    

  }

  



}


