/*
  Bojan Nikolic
  $Id: linraster.hxx,v 1.2 2005/10/08 20:28:54 bnikolic Exp $

  Routines to create 1-d rasters
*/

#ifndef _BNLIB_LINRASTER_HXX__
#define _BNLIB_LINRASTER_HXX__


#include <cmath>

namespace BNLib {

  /*!  Fill the supplied interval with values between begval and
   *   endval, evenly spaced in log-space.  endval is _not_ included.
   */
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

  /*! As LogRaster but include the endpoint */
  template<class T> void LogRasterEI( T beg, 
				      T end,
				      double begval,
				      double endval)
  {
    unsigned n = end-beg;
    for ( T i(beg) ; i < end ; ++i) 
      {
	*i= begval  * pow( endval/begval , ((double)(i - beg)) / (n-1) );
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
