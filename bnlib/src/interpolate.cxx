/*
  Bojan Nikolic
  $Id: interpolate.cxx,v 1.1 2005/05/04 21:07:55 bnikolic Exp $

*/

#include "interpolate.hxx"

namespace BNLib {
  
  InterpolatorBase::InterpolatorBase( double * xvals , double * yvals , size_t size ,
				      imethod method ):
    method(method)
    
  {

  }
  
  InterpolatorBase::~InterpolatorBase() 
  {

  }



}
