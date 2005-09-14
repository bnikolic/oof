/*
  Bojan Nikolic
  $Id: integrate.cxx,v 1.3 2005/09/14 15:50:50 bnikolic Exp $

*/
#include "integrate.hxx"

#include "unaryfn.hxx"

#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>



namespace BNLib
{

  /*! 
   * This is a little helper class which turns of the dump-core gsl error checking mechanism
   */
  class GSLCheck {
  
    gsl_error_handler_t * h;
    
  public:

    GSLCheck(void) 
    { 
      h=gsl_set_error_handler_off () ;
    }
    
    ~GSLCheck() 
    { 
      gsl_set_error_handler (h); 
    }
    
  };
  
  Integrator::Integrator  ( UnaryDD &fn, double epsabs, double epsrel ) : 
    fn(fn), 
    epsabs(epsabs) , 
    epsrel(epsrel) 
  {
  }

  Integrator::~Integrator() 
  {
  }

  double Integrator::EvalFn(double x)
  {
    return fn(x) ; 
  }

  // Forward declaration
  double iAdaptiveIntHelper ( double x , void * pars );

  /*! This is the actual implementation class. It hides all the GSL
   *  details from the header class.   
   *
   *
   */
  class iAdaptiveInt  : public Integrator
  {

    gsl_integration_workspace * workspace;
    gsl_function gslF;
    unsigned maxsteps;

    /// The calculated absolute error is stored here.
    double abserror;
    
    AdaptiveInt::itype type;

  public:

    iAdaptiveInt( UnaryDD &fn , 
		  double epsabs,   double epsrel, 
		  unsigned maxsteps,
 		  AdaptiveInt::itype type  ) :

      Integrator(fn, epsabs, epsrel ),
      workspace(gsl_integration_workspace_alloc (maxsteps)),
      maxsteps(maxsteps),
      type(type)

      {
        gslF.function = &iAdaptiveIntHelper;
	gslF.params   = this;
      }

    ~iAdaptiveInt() 
    {
      gsl_integration_workspace_free(workspace);
    }
    
    double Eval(double xmin, double xmax) 
    {

      double result =0 ;
      int status=0;
      GSLCheck _handleoff;

      if ( type == AdaptiveInt::normal ) 
	{
 	  status= gsl_integration_qag (&gslF,
 				       xmin, xmax,
 				       epsabs,
 				       epsrel,
 				       maxsteps,
 				       GSL_INTEG_GAUSS31,  
 				       workspace, &result, 
 				       &abserror);
	}  
      else if ( type == AdaptiveInt::singularity  )
	{
	  status =
	    gsl_integration_qags (&gslF, 
				  xmin, xmax, 
				  epsabs, 
				  epsrel,
				  maxsteps,
				  workspace, &result, 
				  &abserror);
	  
	}
      else
	{
	  throw( type);
	}
      
      if ( status ) // an error was reported
	{  
	  throw (status);
	}
      
      return result; 
    }
    
  };
    
  


  AdaptiveInt::AdaptiveInt(  UnaryDD &fn , 
			     double epsabs, double epsrel, 
			     unsigned maxsteps, 
			     itype type ) :
    Integrator  ( fn,  epsabs,  epsrel ) ,
    ip(new iAdaptiveInt(fn,epsabs, epsrel , maxsteps, type ))
  {
  }


  AdaptiveInt::~AdaptiveInt() 
  {
    delete ip;
  }
  
  double AdaptiveInt::Eval(double xmin, double xmax) 
  {
    return ip->Eval(xmin, xmax);
  }

  double iAdaptiveIntHelper ( double x , void * pars ) 
  {
    return static_cast<BNLib::iAdaptiveInt *>(pars)->EvalFn(x) ;
  }

}
