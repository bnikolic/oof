/**
   \file kolmogorov_3diters_edge.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   Some code transfered from kolmogorov_3diters.hxx. 

*/
#ifndef __BNLIB__K3ITER_EDGE_HXX__
#define __BNLIB__K3ITER_EDGE_HXX__


#include "kolmogorov_3diters.hxx"

namespace BNLib {
  namespace Kolmog {

  /** \brief An iterator for cell edges. 

      
      On a 3x3x3 cube this iterator sits on the centres of all cell
      edges. Larger cubes are made up of these building blocks.
      
      Used for generation of 3D Kolmogorov turbulence.

   */
  class K3EdgeIterV2 :
    public K3DIterBase
  {
    
    size_t ecount;
    K3DCenterItertor ci;

    void UpdateEdge(void);

    static const size_t np =6;
    K3DParent parents[np];
    K3DParent filtParents[np];

  protected:
    /**
       Generate the two parents in the direction supplied.
     */
    void ParentOnDir( K3DParent * parents,
		      dirs d) const;
		 

  public:

    // ----------------  Public Data -----------------------    

    
    // ----------------   Constructors / Destructors ----------

    K3EdgeIterV2( size_t Nx, size_t Ny, size_t Nz , 
		  size_t o );

    // ---------------   Public interface --------------------

    /**
       Calculates the offset of the current point as multiples of the
       "origin" distance.

       \param  imult,jmlut,kmlut Output parameters
    */
    void CalcIJKMult( int & imult, 
		      int & jmult,
		      int & kmult) const;

    /**
       Should an edge be skipped because it would have been filled in
       by a previous iteration?
    */
    bool pSkipEdge(void) const ;
    
    // Inherited from K3DIterBase
    virtual void next(void);
    virtual const K3DParent * ParentListP(void)  ;
    virtual K3DParent *  FilteredParentBuffer() { return filtParents; } ;
    virtual size_t nParents(void) const   {  return np; }


  };

  /**
     \brief A refined iterator that only includes parents that have an
     opposite number. On the outermost cube therefore, this iterator
     always ends up with two parents.
     
   */
  class K3EdgeIterBalanced :
    public K3EdgeIterV2
  {

  public:

    // ----------------   Constructors / Destructors ----------

    K3EdgeIterBalanced( size_t Nx, size_t Ny, size_t Nz , 
			size_t o );

    /**
       Override to provide balanced parents.
     */
    virtual const K3DParent * FilteredParentP(size_t & np);

  };

  

  }}
#endif
