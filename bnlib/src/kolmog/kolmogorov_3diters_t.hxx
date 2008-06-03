/**
   \file kolmogorov_3diters_t.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   July 2007

   Templated function related to 3d-iterators over grids
*/

#ifndef __BNLIB_KOL_3DITERS_T_HX__
#define __BNLIB_KOL_3DITERS_T_HX__

namespace BNLib {
  namespace Kolmog {

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

  /**
     Find weighted average of parent points, weighted by inverse
     distance to the central point supplied in the cp parameter
     
     \param cp the point being interpolated to
     \param pv array of parent points which are being interpolated
     \param np number of parent points
  */
  template<class T>
  T TKWeightedAverageParents( const T * cube,
			      size_t Nx,
			      size_t Ny,
			      const  K3DParent * pv,
			      const  K3DParent & cp,
			      size_t np)
  {
    T res = 0;
    T totalweight = 0;
    const size_t N2 = Nx*Ny;
    for (size_t i = 0; i < np ; ++ i )
    {
      size_t dx=pv[i].i +pv[i].j*Nx + pv[i].k *N2;
      T      d = 1.0/ pow( pow( ((int)cp.i) - (int)pv[i].i,2) +
			   pow( ((int)cp.j) - (int)pv[i].j,2) +
			   pow( ((int)cp.k) - (int)pv[i].k,2) , 0.5);
      res += cube[dx] * d ;
      totalweight += d  ;
    }
    return res / totalweight;

  }



  }}

#endif
