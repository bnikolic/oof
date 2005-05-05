/* 
  Bojan Nikolic
  $Id: interpolate.cxx,v 1.2 2005/05/05 12:52:08 bnikolic Exp $

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
