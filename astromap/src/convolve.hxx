/**
   \file convolve.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

   Tools for convolving maps together

*/
#ifndef _ASTROMAP_CONVOLVE_HXX__
#define _ASTROMAP_CONVOLVE_HXX__

#include "astromap_fwd.hxx"


namespace AstroMap {

  /*   -----  FFT Convolution -------------

  There is a 33% time advantage of storing one of the FFT'd maps if
  that map does not change.

  */

  /* Convolve maps m1 and m2 using the FFT */
  Map * FFTConvolve( const Map &  m1,
		     const Map &  m2);

  void FFTConvolve( const Map &  m1,
		    const Map &  m2,
		    Map &mres);


}



#endif

