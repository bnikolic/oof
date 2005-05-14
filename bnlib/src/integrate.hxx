/*
  Bojan Nikolic
  $Id: integrate.hxx,v 1.1 2005/05/14 20:02:03 bnikolic Exp $
  
  Numerical integration

*/
#ifndef _BNLIB_INTEGRATE_HXX__
#define _BNLIB_INTEGRATE_HXX__

namespace BNLib {

  // Forward declarations
  class UnaryDD;
  
  class Integrator {

    UnaryDD &fn;

  public:

    /// Absolute error to which the integration should be continued
    const double epsabs;
    /// Relative error to which the integration should be continued
    const double epsrel;

    Integrator  ( UnaryDD &fn, double epsabs, double epsrel ) ;

    virtual ~Integrator() ;

    virtual double Eval(double xmin, double xmax) = 0 ;

    double EvalFn(double x);

  };


  /// Forward for implementation of AdaptiveInt
  class iAdaptiveInt;

  /// Performs adaptive integration of a function
  class AdaptiveInt : public Integrator {
    iAdaptiveInt *ip;

  public:
    AdaptiveInt(  UnaryDD &fn , double epsabs, double epsrel, unsigned maxsteps ) ;
    ~AdaptiveInt();
    
    virtual double Eval(double xmin, double xmax);

  };

}

#endif

