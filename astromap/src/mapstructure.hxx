/**
   \file mapstructure.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Computation of structure functions from maps

*/
#ifndef _ASTROMAP_MAPSTRUCTURE_HXX__
#define _ASTROMAP_MAPSTRUCTURE_HXX__

#include "astromap_fwd.hxx"

#include <vector>

namespace AstroMap {

  /**
     Calculate the structure function by iterating over pixels and
     sampling the structure function randomly from each in turn.

     \param samples_px samples per pixel to take.

     \param OUTsfn the calculated structure function is stored here.

     \param OUTcount the number of samples going into each pixel of
     the structure function is output to this vector.
  */
  void  RndStructureFn( const Map & m,
			size_t samples_px,
			std::vector<double> & OUTsfn,
			std::vector<size_t> & OUTcount );

  /** Wrap the version taking std::vector<double> so that it stores
      the result in the supplied C-vecotrs.
   */
  void  RndStructureFn( const Map & m,
			size_t samples_px,
			double * OUTsfn,
			double * OUTcount,
			size_t   n);
  

}

#endif
