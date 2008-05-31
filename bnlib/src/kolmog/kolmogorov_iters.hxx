/**

   \file kolmogorov_iters.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   May 2007

   Iterators of grids/cells to support generation Kolmogorov-like
   fileds. Moved to this file from kolmogorov.hxx.

*/
#ifndef _BNLIB_KOLMOGOROV_ITERS_HXX__
#define _BNLIB_KOLMOGOROV_ITERS_HXX__

#include <stdlib.h>


namespace BNLib {

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

    virtual ~KolCellIteratorBase() {} ;

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

    /**
       Return the lenght of the side of the cell currently being
       considered.
    */
    virtual double sideDist(void) const  = 0 ;


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
       Return normalised distance to the parent points.
    */
    double parentDist(void) const;

    double sideDist(void) const;

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

    /// Possible edges
    enum edgePos {noEdge = 0, HEdge, VEdge };

    
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

    /**
       Are we on an edge and if so, is it a horisontal or vertical
       edge.
     */
    edgePos isEdge(void) const;

    /**
       Are we on a horisontal edge
    */
    bool isHEdge(void) const ;

    /**
       Are we on a vertical edge
    */
    bool isVEdge(void) const;

    /**
       Get the position of one of the parent points of the current
       point.
    */
    void getParent(size_t & iOUT,
		   size_t & jOUT,
		   parentPos p
		   ) const ;

    /**
       Return normalised distance to the parent points.
    */
    double parentDist(void) const;

    double sideDist(void) const;

  };

    
  
}
#endif

   
