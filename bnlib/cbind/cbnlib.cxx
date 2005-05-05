/*
  Bojan Nikolic
  $Id: cbnlib.cxx,v 1.1 2005/05/05 12:52:07 bnikolic Exp $

*/


#include "cbnlib.h"

#include "../src/interpolategsl.hxx"

bnlib_interpolator bnlib_Cinterpolator ( double * xvals, double *yvals,
					 unsigned size)
{
  
  return (void *) new BNLib::InterpolatorGSL( xvals, yvals, size, 
					      BNLib::InterpolatorBase::linear);

}


double bnlib_EvalIplt ( bnlib_interpolator iplt, double xval) 
{
  return ((BNLib::InterpolatorBase *)iplt)->operator() (xval ) ;

}

void  bnlib_Dinterpolator( bnlib_interpolator iplt )
{
  delete  ((BNLib::InterpolatorBase *)iplt);
}

