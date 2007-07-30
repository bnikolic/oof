/**
   \file kolmogorov_3diters_t.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   July 2007

   Templated function related to 3d-iterators over grids
*/

#ifndef __BNLIB_KOL_3DITERS_T_HX__
#define __BNLIB_KOL_3DITERS_T_HX__

namespace BNLib {

  template<class T>
  T TKAverageParents( const T * cube,
		      size_t Nx,
		      size_t Ny,
		      const  K3DParent * pv,
		      size_t np)
  {
    T res = 0;
    const size_t N2 = Nx*Ny;
    for (size_t i = 0; i < np ; ++ i )
    {
      size_t dx=pv[i].i +pv[i].j*Nx + pv[i].k *N2;
      res += cube[dx];
    }
    return res / np;

  }



}

#endif
