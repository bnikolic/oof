/*
  Copyright:
  Bojan Nikolic
*/

#include "interpolatelog.hxx"

#include <valarray>
#include <cmath>

#include "interpolategsl.hxx"


namespace BNLib {

  InterpolatorLog::InterpolatorLog( const double * xvals , 
				    const double * yvals , 
				    size_t size ,
				    imethod logmethod, imethod realmethod):
    InterpolatorBase( xvals, yvals, size, logmethod)
  {
    
    realspace.reset( new InterpolatorGSL( xvals, yvals, 
					  size , 
					  realmethod) );

    std::valarray<double> dcopy_x ( xvals, size);    
    std::valarray<double> dcopy_y ( yvals, size);

    std::valarray<double> dylog = std::log(dcopy_y);
    std::valarray<double> dxlog = std::log(dcopy_x);


    logspace.reset(  new InterpolatorGSL( &dxlog[0], 
					  &dylog[0], 
					  size , 
					  logmethod));


  }

  InterpolatorLog::~InterpolatorLog()
  {
  }

  double InterpolatorLog::operator() (double x) 
  {
    return exp(  (*logspace)( log(x) ) );
  }

  double InterpolatorLog::Idx(double xmin, double xmax) 
  {
    return realspace->Idx(xmin, xmax);
  }

}


