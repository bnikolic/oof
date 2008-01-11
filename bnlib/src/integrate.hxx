/**
   \file integrate.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>
  
   Numerical integration

*/
#ifndef _BNLIB_INTEGRATE_HXX__
#define _BNLIB_INTEGRATE_HXX__

namespace BNLib {

  // Forward declarations
  class UnaryDD;

  /*! Virtual base class for ways of integrating an one-dimensional
   *  real function.
   */
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
    
    /*! Use a completely separate implementation class to hide the
     *  details of the numerical library used to perform the
     *  integration.
     */
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

