/* 
  Copyright:
  Bojan Nikolic
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
