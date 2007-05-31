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

  // Forwards
  class KolStructureFn;
  class RDist;

  /** 
      \brief Calculate the four corners of the grid on which
      Kolmogorov turbulence is to be calculated.
      
      This function is general to both power law or broken power law
      structure functions.
      
      \param sfn is the structure function that defines the turbulence
      properties (e.g., thick screen or thin screen).
      
      \param rfn Normal distribution random number generator. Will be
      sampled six times.

  */
  void KolmogorovCorners( double *OUTalpha,
			  double *OUTbeta,
			  double *OUTgamma,
			  double *OUTdelta,
			  KolStructureFn & sfn,
			  RDist &rfn);

  /**
     Construct a Kolmogorov random field on a NxN grid using the
     algorithm of Lane et al 2002 (1992WRM.....2..209L).
     
     \param N size of the grid; must be 2^n+1

     \param grid pre-allocated grid of size NxN
     
     \param normvect a vector of std normal distributed random samples
     of length NxN+2

     \bug This is the non-generalised version which will be retired --
     use the generalised version
     
  */
  void KolmogorovPlatform( size_t N,
			   double * grid,
			   const double * normvect);


  void KolmogorovPlatform( size_t N,
			   double * grid,
			   KolStructureFn & sfn,
			   RDist &rfn);

  
}
#endif

   
