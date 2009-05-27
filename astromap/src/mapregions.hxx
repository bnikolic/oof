/**
   \file mapregions.hxx

   Bojan Nikolic <b.nikoli@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/
#ifndef _ASTROMAP_MAPREGIONS_HXX__
#define _ASTROMAP_MAPREGIONS_HXX__

#include <cstddef>

namespace AstroMap {

  // Forward declaration
  class Map;

  /** \brief A rectangular map region 
      
      \bug This interface is at beta stage, do not use for production
   */
  class MRRect {

  public:
    
    size_t lx, ly, hx,hy;
    
    MRRect(size_t lx,
	   size_t ly,
	   size_t hx,
	   size_t hy);

  };

  /** \brief Sum the pixels in a rectangular region
      
      \bug This interface is in beta stage
   */
  double Sum(const Map &m,
	     const MRRect &reg);

  Map * Extract(const Map &m,
		const MRRect &reg);


}

#endif

