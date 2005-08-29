/*
  Bojan Nikolic
  $Id: interpolatelog.cxx,v 1.2 2005/08/29 21:02:05 bnikolic Exp $
*/

#include "interpolatelog.hxx"

#include <valarray>
#include <cmath>

#include "interpolategsl.hxx"


namespace BNLib {

  InterpolateLog::InterpolateLog( double * xvals , double * yvals , size_t size ,
				  imethod logmethod, imethod realmethod):
    InterpolatorBase( xvals, yvals, size, logmethod)
  {

    realspace = new InterpolatorGSL( xvals, yvals, size , realmethod);
    
    std::valarray<double> dcopy ( yvals, size);

    std::valarray<double> dlog = std::log(dcopy);

    logspace =  new InterpolatorGSL( xvals, 
				     &dlog[0], size , 
				     logmethod);


  }

  InterpolateLog::~InterpolateLog()
  {
    delete logspace;
    delete realspace;
  }

  double InterpolateLog::operator() (double x) 
  {
    return exp(  (*logspace)(x) );
  }

  double InterpolateLog::Idx(double xmin, double xmax) 
  {
    return realspace->Idx(xmin, xmax);
  }

}


