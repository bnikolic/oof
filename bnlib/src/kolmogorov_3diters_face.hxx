/**
   \file kolmogorov_3diters_face.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   Some code transfered from kolmogorov_3diters.hxx

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
    size_t fcount;
    K3DCenterItertor ci;

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

    // Inherited from K3DIterBase
    virtual void next(void);
    virtual const K3DParent * ParentListP(void)  ;
    virtual K3DParent *  FilteredParentBuffer() { return filtParents; } ;
    virtual size_t nParents(void) const   {  return np; }

  };


}
#endif
   
