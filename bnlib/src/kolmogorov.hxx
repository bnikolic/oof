/**

   \file kolmogorov.hxx

   Boan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   May 2007 

   Construct 2D radnom fields with Kolmorogov structure

*/
#ifndef _BNLIB_KOLMOGOROV_HXX__
#define _BNLIB_KOLMOGOROV_HXX__

#include <stdlib.h>

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

  /**
     A utility class to iterate over centers of cells when subdividing
     for the KologorovPlatform algorithm.
  */
  class CenterIter {

    size_t i, j;



  public:

    // ----------------  Public Data -----------------------

    const size_t N;
    const size_t o;
    const size_t delta; 


    // ----------------   Constructors / Destructors ----------

    /**
       \param N the grid is NxN

       \param o the order; order 0 has one center subdivision, order 1
       has four, etc.
    */
    CenterIter(size_t N,
	       size_t o);

    // ---------------   Public interface --------------------

    /**
       Get the current point
    */
    void getc( size_t & i,
	       size_t & j);

    /**
       Iterate to the next point
    */
    void next(void);

    
    
    

  };
  
}
#endif

   
