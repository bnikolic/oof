/**
   \file kernels_3d.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   June 2007   

   Caculate kernels of data on 3d grids 
*/
#ifndef __BNLIB_KERNELS_3D_HXX__
#define __BNLIB_KERNELS_3D_HXX__

#include <cstddef> 
#include <vector> 


namespace BNLib {

  /** Displacements in 3 dimensions 
   */
  struct Displacement3D {
    int i, j, k;
  };

  /** Extent of a 3D parallelopiped
   */
  struct Extnent3D {
    size_t i,j,k ;
  };

  struct Position3D {
    size_t i,j,k ;
  };
  

  /** Convolve cube with kernel defined by dps and coeffs on arbirtary
      set of points defined by x.

      \param KN size of the convolution kernel (i.e. arrays dps and
      coeffs and output array out)

      \param ext Extents of the supplied cube

      \param PN number of points to carry out the convolution at
      (i.e. length of array pos).
   */
  void KConvolve3D( const Displacement3D * dps ,
		    const double * coeffs,
		    const size_t KN,
		    const double * cube,
		    const Extnent3D & ext,
		    const Position3D * pos,
		    const size_t PN,
		    double * out );

  /** A simple wrap for KConvolve3D that uses std::vectors 
   */
  void KConvolve3D( const std::vector<Displacement3D> & dps,
		    const std::vector<double> & coeffs,
		    const double * cube,
		    const Extnent3D & ext,
		    const std::vector<Position3D> & pos,
		    std::vector<double> & cvals );

  /** \brief Generate a cylindrical kernel, in positive z-direction.

  \param r_px radius of the cyliner in pixels
  \param zextnet length of the cylinder in the z direction
  */
  void GenZCylinder( std::vector<Displacement3D> & dps,
		     std::vector<double> & coeffs,
		     double r_px,
		     size_t zextent );

  /** \brief Generate a gaussian-cylindrical kernel in z-direction

  if z iz the slice, then radius of gaussian used is r`=r_px * sqrt( 1 + (zhstart+z*zh_increment))

  
  */
  void GenGaussCylinder( std::vector<Displacement3D> & dps,
			 std::vector<double> & coeffs,
			 double r_px,
			 size_t zextent_px,
			 size_t rextent_px,
			 double zh_start,
			 double zh_increment);

  /** \brief Fill out a vector of Displacement3D from sepratre vectors
      containing i,j,k components.

      Speeds up some slow python access.

      Filling starts from index start.
  */
  void FillDisplacement3D ( std::vector<Displacement3D> & dps,
			    size_t start,
			    const std::vector<double>  & i_v,
			    const std::vector<double>  & j_v,
			    const std::vector<double>  & k_v);

  /** \brief Sum a rangle of horizontal slices of a cube
      
  \param cube Cube to be flattened
  \param ext  Extent of this cube
  \param zstart,zend range of slices to include in the sum
  \param res  store results in this array. Must be of size ext.i*ext.j
  */
  void ZFlatten( const double * cube,
		 const Extnent3D & ext,
		 size_t zstart,
		 size_t zend,
		 double * res);

  /** \brief Sum close-to horizontal slices
      
  Use this to simulate non-vertical sight lines through the
  cube. Linear interpolation is used. Parameters like ZFlatten plus
  the following.

  Pixels which are too close to edges to correctly sum are assigned
  NaNs.

  \bug Pixels which are exactly on edge, so are well defined, may also
  be assigned a NaN.

  \param cx offset at zstart in the x direction
  \param cy offset at zstart in the y direction
  \param dx change in x offset per slice in z direction
  \param dy change in y offset per sliec in z direction

  */
  void SkewFlatten( const double * cube,
		    const Extnent3D & ext,
		    size_t zstart,
		    size_t zend,
		    double cx, 
		    double cy,
		    double dx,
		    double dy,
		    double * res);


}

#endif
