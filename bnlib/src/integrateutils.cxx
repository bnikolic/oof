/*
 * Bojan Nikolic
 *
 */

#include "integrateutils.hxx"

#include <cmath>

#include "unaryfn.hxx"
#include "integrate.hxx"
#include "linraster.hxx"


namespace BNLib {

  double SectionInteg (UnaryDD &fn , double epsabs, 
		       double epsrel, unsigned maxsteps,
		       std::vector<double> &bounds )
  {

    double result = 0 ;

    AdaptiveInt integrator (  fn,  epsabs, epsrel,  maxsteps );

    for (unsigned i =0 ; i < bounds.size() - 1 ; ++i )
      {
	result += integrator.Eval( bounds[i] , bounds[i+1] );
      }

    return result;
  }

  double LogSecInteg ( UnaryDD &fn , double xmin, double xmax, double step , 
		       double epsabs, 
		       double epsrel, unsigned maxsteps )
  {
    
    std::vector<double> bounds ( (int)( log(xmax/xmin) / log(step) ) +2 );

    LogRaster( bounds.begin() , bounds.end() -1 , 
	       xmin, xmax);

    bounds[bounds.size() -1 ] = xmax;

    return SectionInteg( fn  , epsabs, epsrel, maxsteps, bounds);
    
  }

  double ProdInteg ( UnaryDD &fn1 , UnaryDD &fn2 , double xmin, double xmax, 
		     double epsrel, 
		     unsigned  maxsteps)
  {

    class ProdClass : public UnaryDD {
      
      UnaryDD & fn1 ;
      UnaryDD & fn2 ;

    public:
      
      ProdClass( UnaryDD & fn1,   UnaryDD & fn2) :
	fn1(fn1) , fn2(fn2)
      {
      }
      
      double operator() (double x)
      {
	return fn1(x)  * fn2(x);
      }

    };
    
    ProdClass pd (fn1, fn2);
    AdaptiveInt integrator (  pd,  0, epsrel,  maxsteps );

    return integrator.Eval(xmin, xmax);
    
  }




}


