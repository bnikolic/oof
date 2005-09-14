/*
 * Bojan Nikolic
 *
 * $Id: integrateutils.cxx,v 1.3 2005/09/14 17:55:42 bnikolic Exp $
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




}


