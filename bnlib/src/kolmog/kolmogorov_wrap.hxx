/** 
    \file kolmogorov_wrap.hxx
    
    Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
    
    May 2007

    Package up generation of Kolmogorov screens a little to make it
    fit in better with rest of BNLib.  Interface in kolmogorov.hxx is
    intentionally sparse to make it distributable outside of this
    package if necessary.
*/
#ifndef __BNLIB_KOKMOGOROV_WRAP_HX__
#define __BNLIB_KOKMOGOROV_WRAP_HX__

#include <stdlib.h>

namespace BNLib {

  /**
     Construct a Kolmogorov phase screen, generating the required
     random numbers automatically. If seed == 0, then seed is taken
     from the current system time.
  */
  void KolmogorovPlatform( size_t N,
			   double * grid,
			   unsigned long seed = 0 );

  void BrkKolmogorovPlatform( size_t N,
			      double * grid,
			      double w,
			      unsigned long seed = 0 );


}

#endif
