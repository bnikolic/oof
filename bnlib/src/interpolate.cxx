/* 
  Bojan Nikolic
  $Id: interpolate.cxx,v 1.3 2005/09/23 21:26:20 bnikolic Exp $

*/

#include "interpolate.hxx"

namespace BNLib {
  
  InterpolatorBase::InterpolatorBase( const double * xvals , 
				      const double * yvals , 
				      size_t size ,
				      imethod method ):
    method(method)
    
  {

  }
  
  InterpolatorBase::~InterpolatorBase() 
  {

  }



}
