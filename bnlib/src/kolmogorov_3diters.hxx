/**
   \file kolmogorov_3diters.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007

   In order for the mid-point displecement method of generating
   Kolmogorov turbulence to work, the (sampled) region of space to be
   calculated needs to be progressively subdivided into smaller
   sections.  The iterators in this file provide a way of iterating
   over all of the points in the correct order so that the mid point
   displacement can be applied.

   This is the 3-d generalisation of iterators in kolmogorov_iters.hxx


*/
#ifndef __BNLIB_KOLMOGOROV3DITERS_HXX__
#define __BNLIB_KOLMOGOROV3DITERS_HXX__

#include <cstddef> 

namespace BNLib {

  /**
     Base class for Mid-point displacement iterators over three
     dimensions.
  */
  class K3DIterBase {

  protected:

    size_t i,j,k;
    
  public:

    // ----------------  Public types ---------------------
    
    /**
       Just define the names of the dimensions so that we can easily
       acess them.
     */
    enum dirs {D_X, D_Y , D_Z};

    // ----------------  Public Data -----------------------    

    /** \brief Length in the first index direction
     */
    const size_t Nx;
    /** \brief Length in the second index direction
     */
    const size_t Ny;
    /** \brief Length in the third index direction
     */
    const size_t Nz;

    /**
       "Order" of the iteration. Roughly speaking, this is a parameter
       that needs to be incremented sequentially until all of the cube
       has been visited.
    */
    const size_t o;

    // ----------------   Constructors / Destructors ----------

    /**
       Need to specify each of the three dimensions and the order of
       the iteration.
    */
    K3DIterBase( size_t Nx, size_t Ny, size_t Nz , size_t o );    


    virtual ~K3DIterBase(void) {};
    
    // ---------------   Public interface --------------------

    /** \brief Get the current position.
    */
    void getc( size_t & iOUT,
	       size_t & jOUT,
	       size_t & kOUT );

    /** \brief Get the dimension in the specified direction
     */
    size_t getd( dirs d);

    /** \brief False if no more iteration left to do 
     */
    bool inBounds(void);

    /** \brief Iterate to the next position 
     */
    virtual void next(void)  = 0 ;

  };

  class K3DCenterItertor :
    public K3DIterBase
  {

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3DCenterItertor( size_t Nx, size_t Ny, size_t Nz , size_t o );

    // ---------------   Public interface --------------------
    
    /**
       Return the origin to use in the specified direction.
     */
    size_t origin(dirs d);

    size_t delta(dirs d);

    // Inherited from K3DIterBase
    virtual void next(void);

  };


  /**
     The second iterator over the 3D cube, that does the faces first.
   */
  class K3FaceIter :
    public K3DIterBase
  {

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3FaceIter( size_t Nx, size_t Ny, size_t Nz , 
		size_t o );

    // ---------------   Public interface --------------------
    
    /**
       Return the origin to use in the specified direction.
     */
    size_t origin(dirs d);

    size_t delta(dirs d);

    // Inherited from K3DIterBase
    virtual void next(void);

  };


}
#endif
