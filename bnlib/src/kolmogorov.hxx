/**

   \file kolmogorov.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   May 2007

   Construct 2D random fields with Kolmorogov structure

*/
#ifndef _BNLIB_KOLMOGOROV_HXX__
#define _BNLIB_KOLMOGOROV_HXX__

#include <stdlib.h>

/**
   BNLib is the strandard namespace into which parts of this library
   go.
*/
namespace BNLib {

  /**
     Construct a Kolmogorov random field on a NxN grid using the
     algorithm of Lane et al 2002 (1992WRM.....2..209L).
     
     \param N size of the grid; must be 2^n+1

     \param grid pre-allocated grid of size NxN
     
     \param normvect a vector of std normal distributed random samples
     of length NxN+2
     
  */
  void KolmogorovPlatform( size_t N,
			   double * grid,
			   const double * normvect);

  
}
#endif

   
