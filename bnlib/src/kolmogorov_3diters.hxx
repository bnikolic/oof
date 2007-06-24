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
#include <vector>

namespace BNLib {

  struct K3DParent {

    size_t i,j,k;

  };

  /**
     Base class for Mid-point displacement iterators over three
     dimensions.
     
     \bug This approach is probably too unstructured to make work
     reliably. Begin work on a different approach.
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
    size_t getd( dirs d) const;

    /** \brief False if no more iteration left to do 
     */
    bool inBounds(void);

    /** \brief Set current point out of bounds */
    void setOutOfBounds(void);

    /** \brief Iterate to the next position 
     */
    virtual void next(void)  = 0 ;

    /** \brief Get the parents of this position.
	
    I.e., these are the positions which need to be interpolated to get
    the non-random part of the current position.
     */
    virtual void ParentList( std::vector<K3DParent> & vOUT) =0;

    /**
       \brief Return only those parents actually within the cube grid.
    */
    virtual void FilteredParentList(std::vector<K3DParent> & vOUT);

    /**
       Return parents as a copy of the vector. (for SWIG use)
    */
    std::vector<K3DParent> CopyParentList(void);

    /**
       Return FilteredParentList as copy of the vector. (for SWIG use)
    */
    std::vector<K3DParent> CopyFilteredParentList(void);
    

  };

  /** \brief A class to iterate of centre of cells when generating 3D
      Kolmogorov turbulence.
  */
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
    size_t origin(dirs d) const;

    size_t delta(dirs d) const;

    /** \brief Are we on the first position in the direction d?
     */
    bool firstDir(dirs d) const;


    // Inherited from K3DIterBase
    virtual void next(void);
    virtual void ParentList( std::vector<K3DParent> & vOUT);

  };


  /**
     \brief An iterator for cell faces. For generation of 3D
     Kolmogorov turbulence.
   */
  class K3FaceIterV2 :
    public K3DIterBase
  {
    size_t fcount;
    K3DCenterItertor ci;

    /**
       Update the position i,j,k on the basis of the current value of
       fcount (i.e., on the basis of the face that we are currently
       on).
     */
    void UpdateFace(void);

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3FaceIterV2( size_t Nx, size_t Ny, size_t Nz , 
		size_t o );

    // ---------------   Public interface --------------------

    /**
       Should a face be skipped because it would have been filled in
       by a previous iteration?
    */
    static bool pSkipFace(const K3DCenterItertor & ci,
			  size_t fcount);

    // Inherited from K3DIterBase
    virtual void next(void);
    virtual void ParentList( std::vector<K3DParent> & vOUT);

  };

  /** \brief An iterator for cell edges. For generation of 3D
      Kolmogorov turbulence.

   */
  class K3EdgeIterV2 :
    public K3DIterBase
  {
    
    size_t ecount;
    K3DCenterItertor ci;

    void UpdateEdge(void);

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3EdgeIterV2( size_t Nx, size_t Ny, size_t Nz , 
		  size_t o );

    // ---------------   Public interface --------------------
    
    // Inherited from K3DIterBase
    virtual void next(void);
    virtual void ParentList( std::vector<K3DParent> & vOUT);

  };

  /**
     \brief Average the values of parents for a cube.
     
     Only fully symetric cubes supported.
   */
  double KAverageParents( const double * cube,
			  size_t N,
			  const  std::vector<K3DParent> & pv);
  


}
#endif
