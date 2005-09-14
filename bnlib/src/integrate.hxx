/*
  Bojan Nikolic
  $Id: integrate.hxx,v 1.2 2005/09/14 15:50:51 bnikolic Exp $
  
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


  /* Forward for implementation of AdaptiveInt */
  class iAdaptiveInt;

  /*! Performs adaptive integration of a function */
  class AdaptiveInt : public Integrator {
    iAdaptiveInt *ip;

  public:
    
    /*! Type of integration to employ. If type==normal will use normal
     *  gaussian integration. If type==singularity will use qags whic
     *  can integrate singlularities
     */
    enum itype { normal , singularity } type;
  
  
    AdaptiveInt(  UnaryDD &fn , 
		  double epsabs, double epsrel, 
		  unsigned maxsteps, 
		  itype type=normal) ;

    ~AdaptiveInt();
    
    virtual double Eval(double xmin, double xmax);

  };
}

#endif

