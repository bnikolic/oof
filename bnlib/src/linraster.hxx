/*
  Bojan Nikolic
  $Id: linraster.hxx,v 1.1 2005/05/14 20:02:03 bnikolic Exp $

  Routines to create 1-d rasters
*/

#ifndef _BNLIB_LINRASTER_HXX__
#define _BNLIB_LINRASTER_HXX__


#include <cmath>

namespace BNLib {

  template<class T> void LogRaster( T beg, 
				    T end,
				    double begval,
				    double endval)
  {
    unsigned n = end-beg;
    for ( T i(beg) ; i < end ; ++i) 
      {
	*i= begval  * pow( endval/begval , ((double)(i - beg)) / n );
      }
  }

  template<class T> void LinRaster( T beg, 
				    T end,
				    double begval,
				    double endval)
  {
    unsigned n = end-beg;
    for ( T i(beg) ; i < end ; ++i) 
      {
	*i= begval  + (endval - begval) * (i-beg) /n ;
      }
  }

}

#endif
