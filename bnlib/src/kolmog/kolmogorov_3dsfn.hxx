/**
   \file kolmogorov_3dsfn.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   Initial version November 2007

   Measure structure functions of three dimensional cubes directly
   using random sampling. See also 2d versions in astromap.
*/
#ifndef __BNLIB__KOL_3DSFN_HXX__
#define __BNLIB__KOL_3DSFN_HXX__

#include <stdlib.h>

namespace BNLib {

  /** \brief Compute the structure function by randomnly sampling the
     cube.

     \param cube      The input cube
     \param Nx,Ny,Nz  Dimensions of the input cube
     \param s_p       Samples per cube point
     \param acum      Array to output accumulated sum of differences squared
     \param ns        Array to output accumulated samples
     \param acumlen   Length of acum array (longer distances are not recorded)

     acum and ns are treated as logarthmic bins with maximum bin at
     distance of 2 * Nx and minimum bin at distance 1 and number of
     bins acumlen.
     
   */
  void RandomSFN( const double * cube,
		  size_t Nx,
		  size_t Ny,
		  size_t Nz,
		  size_t s_p,
		  double * acum,
		  size_t * ns,
		  size_t acumlen);


}


#endif
