/**
   \file kolmogorov_3d.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   

   The 3-d generalisation of kolmogorov turbulence generation.

*/
#ifndef __BNLIB_KOLMOGOROV3D_HXX__
#define __BNLIB_KOLMOGOROV3D_HXX__

#include <stdlib.h>

/// General utilities namespace
namespace BNLib {

  // Forwards
  class RDist;

  /**
     Options for the 3d turbulence generation routies. Has the
     structure of a bit field.
   */
  enum Kolmgorov3DOptions { 
    /// Generate the inital corners using the exact algorithm
    /// considering edge, face and body diagonals
    KInitialEFB =0 ,
    /// Generate the initial corners using approximate algorithm (not
    /// recomended)
    KInitialFBB =1,
    /// If this bit is set, weigh interpolation by inverse distance to
    /// parent point
    KWeightedInterp = 2,
    /// If this bit is set, only interpolate paraents which have a
    /// valid symetric parent. This applies to face interpolation
    KBalancedIters  = 4,
    /// As KBalancedIters, but for edge interpolation.
    KEdgeBalanced   = 8
  };

  /**
     Generate 3d komogorov turbulence on Ncubed grid
  */
  size_t Kolmogorov3D( double * cube,
		       size_t N,
		       RDist &rfn);

  /**
     Generated 3d Kolmogorov turbuluence on a Nx by Ny by Nz
     grid. This is the main entry point to the three dimensional
     Kolmogorov field generation.
     
     \param cube is the pre-allocated output array of size Nx times Ny
     times Nz.

     \param Nx,Ny,Nz lenghts in the Nx,Ny,Nz directions. Direction Nx
     must not be smaller than then two other directions.
     
     \param rfn the gaussian random number generator to be used by the
     routie

     \param opt Options for adjusting the generation algorithm. See
     BNLib::Kolmgorov3DOptions .

     \return The maximum order used + 1
   */
  size_t Kolmogorov3D( double * cube,
		       size_t Nx,
		       size_t Ny,
		       size_t Nz,
		       RDist &rfn,
		       int opt=KInitialEFB) throw (const char *);

  /**
     As Kolmogorov3D, but generate on single precision ("float") grid.
   */
  size_t Kolmogorov3DF( float * cube,
			size_t Nx,
			size_t Ny,
			size_t Nz,
			RDist &rfn);

  namespace Kolmog {

  /**
     \brief Set up the eight initial corner values for 3d turbulence
     generation.

     In this instance only support a fully symetric cube. This uses
     the Edge-Face-Body algorithm.
  */
  void KolmogorovCorners3D(double *cube,
			   size_t N,
			   RDist &rfn);


  /**
     Compute the required mid-point standard deviation for the case of
     3-dimensional Kolmogorov turbulence for the center-cell
     iterator. See bnlib/gen/kolmogorovmidpoint.py 
     
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

  /** \brief
      Returns true if the supplied unsigned int is of form 2^n +1 
  */
  bool pTwoNPlustOne(unsigned n);

  }
  

}


#endif
