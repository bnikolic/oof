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
	       size_t & kOUT ) const
    {
      iOUT=i;     jOUT=j;    kOUT=k;
    }

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
    virtual void ParentList( std::vector<K3DParent> & vOUT) ;

    /** \brief Return the number of parents that this iterator has
     */
    virtual size_t nParents(void) const =0;

    /** \brief Return const pointer to list of parents

    Reduces un-necessary allocation of vectors.
    */
    virtual const K3DParent * ParentListP(void) = 0;

  protected:
    /** \brief Return pointer to buffer big enough to contain all
	possible parents 
    */
    virtual K3DParent *  FilteredParentBuffer(void) = 0;
  public:

    /**
       \brief Return only those parents actually within the cube grid.
    */
    virtual void FilteredParentList(std::vector<K3DParent> & vOUT);

    /** \brief Return pointer to array of only those parents actually
	within the cube grid. 

	This should be substantially faster than
	FilteredParentList. Number of parents goes into parameter np.
	
	Override this function if have an algorithm that directly
	generates the parents within the volume rather than the
	generate and filter technique used here (in the base class).
	
	\param np Used to the return value of how many parents are
	actually within the volume at this position
    */
    virtual const K3DParent * FilteredParentP(size_t & np);

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

    static const size_t np =8;
    K3DParent parents[np];
    K3DParent filtParents[np];

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3DCenterItertor( size_t Nx, size_t Ny, size_t Nz , size_t o );

    // ---------------   Public interface --------------------
    
    /**
       Return the origin to use. Calculated always from the size of
       the D_X direction.

       Inline for speed.
     */
    size_t origin(void) const
    {
      return Nx >> (o+1);
    }

    /// Inline for speed
    size_t delta(void) const
    {
      return Nx >> o;
    }

    /** \brief Are we on the first position in the direction d?
     */
    bool firstDir(dirs d) const;


    // Inherited from K3DIterBase
    virtual void next(void);
    virtual const K3DParent * ParentListP(void) ;
    virtual K3DParent *  FilteredParentBuffer() { return filtParents; } ;
    virtual size_t nParents(void) const   {  return np; }

  };

  /**
     \brief Average the values of parents for a cube.
     
     Only fully symetric cubes supported.
   */
  double KAverageParents( const double * cube,
			  size_t Nx,
			  size_t Ny,
			  const  std::vector<K3DParent> & pv);

  /**
     \brief Average the values of parents for a cube.

     Uses pointers to parent array to elimate need for memory
     allocation.

     \param pv the array of parents
     \param np number of parants in array pv
     
  */
  double KAverageParents( const double * cube,
			  size_t Nx,
			  size_t Ny,
			  const  K3DParent * pv,
			  size_t np);
  


}
#endif
