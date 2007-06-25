/**
   \file kolmogorov_3d.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   

   The 3-d generalisation of kolmogorov turbulence generation.

*/
#ifndef __BNLIB_KOLMOGOROV3D_HXX__
#define __BNLIB_KOLMOGOROV3D_HXX__

#include <stdlib.h>

namespace BNLib {

  // Forwards
  class RDist;

  /**
     Set up the eight initial corner values for 3d turbulence
     generation.

     In this instance only support a fully symetric cube.
  */
  void KolmogorovCorners3D(double *cube,
			   size_t N,
			   RDist &rfn);

  /**
     Generate 3d komogorov turbulence on Ncubed grid
  */
  void Kolmogorov3D( double * cube,
		     size_t N,
		     RDist &rfn);

  /**
     Compute the required mid-point standard deviation for the case of
     3-dimensional Kolmogorov turbulence for the center-cell iterator.
     
     \param np the the number of parents from which the mid-point was
     constrcted.
     
     \param o The iteration order.
  */
  double  KMidPointVar_CI( size_t np,
			   size_t o);

  /**
     \brief As KMidPointVar_CI, but for the face iterator

  */
  double  KMidPointVar_FI( size_t np,
			   size_t o);

  /**
     \brief As KMidPointVar_CI, but for the edge iterator

  */
  double  KMidPointVar_EI( size_t np,
			   size_t o);

  /**
     Magnify the grid od by placing the values on dd. Magnification
     factor is Nx/N. Ny,Nz may be samller than Nx in which case data
     points from the original grid are discarded.
     
     \param og original grid, of total length pow(N,3)
     \param N  linear size of the original grid
     \param dd destination grid
     \param Nx,Ny,Nz linear sizes of the destination grid in the X,Y, and Z directions respectivey.
   */
  void KMagnifyGrid(double *og,
		    const size_t N,
		    double *dd,
		    const size_t Nx,
		    const size_t Ny,
		    const size_t Nz);

}


#endif
