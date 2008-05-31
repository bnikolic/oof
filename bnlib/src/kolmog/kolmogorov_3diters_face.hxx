/**
   \file kolmogorov_3diters_face.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   Some code transfered from kolmogorov_3diters.hxx. Deal with
   iterations over "faces"

*/
#ifndef __BNLIB__K3ITER_FACE_HXX__
#define __BNLIB__K3ITER_FACE_HXX__

#include "kolmogorov_3diters.hxx"

namespace BNLib {

  /**
     \brief An iterator for cell faces. For generation of 3D
     Kolmogorov turbulence.
   */
  class K3FaceIterV2 :
    public K3DIterBase
  {
  protected:
    size_t fcount;
    K3DCenterItertor ci;

  public:
    /**
       Update the position i,j,k on the basis of the current value of
       fcount (i.e., on the basis of the face that we are currently
       on).
     */
    void UpdateFace(void);

    static const size_t np =6;
    K3DParent parents[np];
    K3DParent filtParents[np];

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

    /**
       Enter the centre-of-cell parent to the supplied pointer.
     */
    void ParentCentre(K3DParent * parents) const;
    
    /**
       Enter the face parents to the supplied pointer
    */
    void ParentFace(K3DParent * parents) const;

    /**
       Enter the opposite cell parent to the supplied pointer
    */
    void ParentOpposite(K3DParent * parents) const;
    

    

    // Inherited from K3DIterBase
    virtual void next(void);
    virtual const K3DParent * ParentListP(void)  ;
    virtual K3DParent *  FilteredParentBuffer() { return filtParents; } ;
    virtual size_t nParents(void) const   {  return np; }

  };

  /** \brief Also a face iterator, but better generation of parent
      points, avoiding asymetric parent sets.

   */
  class K3FaceIterBalanced : 
    public K3FaceIterV2
  {
    
    /** Are we on a face of the overal volume?
     */
    bool pOnFace(void);

  public:

    // ----------------  Public Data -----------------------    
    
    
    // ----------------   Constructors / Destructors ----------

    K3FaceIterBalanced( size_t Nx, size_t Ny, size_t Nz , 
			size_t o );

    // ---------------   Public interface --------------------    

    /**
       Overriding this to provide better generation of parents that
       actually lie within the volume.
     */
    virtual const K3DParent * FilteredParentP(size_t & np);


  };


}
#endif
   
