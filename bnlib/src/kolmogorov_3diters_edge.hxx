/**
   \file kolmogorov_3diters_edge.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   Some code transfered from kolmogorov_3diters.hxx. 

*/
#ifndef __BNLIB__K3ITER_EDGE_HXX__
#define __BNLIB__K3ITER_EDGE_HXX__


#include "kolmogorov_3diters.hxx"

namespace BNLib {

  /** \brief An iterator for cell edges. For generation of 3D
      Kolmogorov turbulence.

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

}
#endif
