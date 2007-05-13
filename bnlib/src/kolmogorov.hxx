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
     Base class for iterators over cells for kolmogorov phase screen
     generation.
  */
  class KolCellIteratorBase {

  protected:

    /// Current position on the grid
    size_t i, j;    

  public:
    
    // ----------------  Public Data -----------------------    

    const size_t N;
    const size_t o;


    // ----------------   Constructors / Destructors ----------

    /**
       \param N the grid is NxN

       \param o the order; order 0 has one center subdivision, order 1
       has four, etc.
    */
    KolCellIteratorBase( size_t N, 
			 size_t o);

    // ---------------   Public interface --------------------

    /**
       Get the current point
    */
    void getc( size_t & iOUT,
	       size_t & jOUT) const;

    /**
       Return true if we haven't steped out of bounds. I.E., this will
       return false when all points have been iterated over.
    */
    bool inBounds(void) const;    


  };


  /**
     A utility class to iterate over centers of cells when subdividing
     for the KologorovPlatform algorithm.
  */
  class CenterIter:
    public KolCellIteratorBase
  {


  public:

    // ----------------  Public Data -----------------------

    const size_t origin; 
    const size_t delta; 

    enum parentPos { TL, TR, BL , BR };


    // ----------------   Constructors / Destructors ----------

    /**
       See KolCellIteratorBase constructor.
    */
    CenterIter(size_t N,
	       size_t o);

    // ---------------   Public interface --------------------


    /**
       Get the position of one of the parent points of the current
       point.
    */
    void getParent(size_t & iOUT,
		   size_t & jOUT,
		   parentPos p
		   ) const ;


    /**
       Iterate to the next point
    */
    void next(void);


  };

  /** A utlity class to iterate over edge cells */
  class EdgeIter :
    public KolCellIteratorBase
  {
    
  public:
    
    // ----------------  Public Data -----------------------

    const size_t origin; 
    const size_t delta; 

    /// Positions of parets: left, right, top, bottom
    enum parentPos { L, R, T , B };

    
    // ----------------   Constructors / Destructors ----------

    /**
       See KolCellIteratorBase constructor for description of
       parameters.
    */
    EdgeIter( size_t N,
	      size_t o);

    /**
       Iterate to the next point
    */
    void next(void);

  };

    
  
}
#endif

   
