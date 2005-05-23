/*
  Bojan Nikolic
  $Id: integrate.cxx,v 1.2 2005/05/23 13:46:54 bnikolic Exp $

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

  double iAdaptiveIntHelper ( double x , void * pars );

  class iAdaptiveInt  : public Integrator
  {

    gsl_integration_workspace * workspace;
    gsl_function gslF;
    unsigned maxsteps;

    /// The calculated absolute error is stored here.
    double abserror;

  public:

    iAdaptiveInt( UnaryDD &fn , double epsabs, double epsrel, unsigned maxsteps  ) :
      Integrator(fn, epsabs, epsrel ),
      workspace(gsl_integration_workspace_alloc (maxsteps)),
      maxsteps(maxsteps)
      {
        gslF.function = &iAdaptiveIntHelper;
	gslF.params   = this;
      }

    ~iAdaptiveInt( ) {
      gsl_integration_workspace_free(workspace);
    }
    
    double Eval(double xmin, double xmax) {

      double result;
      int status=0;
      GSLCheck _handleoff;

      status =
	gsl_integration_qags (&gslF, 
			      xmin, xmax, 
			      epsabs, 
			      epsrel,
			      maxsteps,
			      workspace, &result, &abserror); 
      
      if ( status ) // an error was reported
	{  
	  throw (status);
	}
      return result;

    };

  };
    
    
  double iAdaptiveIntHelper ( double x , void * pars ) {
    return static_cast<BNLib::iAdaptiveInt *>(pars)->EvalFn(x) ;
  }

  AdaptiveInt::AdaptiveInt(  UnaryDD &fn , double epsabs, double epsrel, unsigned maxsteps ) :
    Integrator  ( fn,  epsabs,  epsrel ) ,
    ip(new iAdaptiveInt(fn,epsabs, epsrel , maxsteps ))
  {
  }


  AdaptiveInt::~AdaptiveInt() {
    delete ip;
  }
  
  double AdaptiveInt::Eval(double xmin, double xmax) {
    return ip->Eval(xmin, xmax);
  }

}
