/**
   \file kolmogorov_3d.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   

   The 3-d generalisation of kolmogorov turbulence generation.

*/
#ifndef __BNLIB_KOLMOGOROV3D_HXX__
#define __BNLIB_KOLMOGOROV3D_HXX__

#include <stdlib.h>

namespace BNLib {

  // Forwards
  class RDist;

  /**
     Set up the eight initial corner values for 3d turbulence
     generation.

     In this instance only support a fully symetric cube.
  */
  void KolmogorovCorners3D(double *cube,
			   size_t N,
			   RDist &rfn);

  /**
     Generate 3d komogorov turbulence on Ncubed grid
  */
  void Kolmogorov3D( double * cube,
		     size_t N,
		     RDist &rfn);
}


#endif
