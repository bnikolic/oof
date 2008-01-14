/**
   \file mapset.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
   
   Set map values from supplied functions
*/

#ifndef _ASTROMAP_MAPSET_HXX__
#define _ASTROMAP_MAPSET_HXX__

#include <binaryfn.hxx>
#include <valarray>

namespace AstroMap {

  // Forwads
  class Map;

  /*! Set the map by calling the supplied binary function with world
   *  coordinates of each pixel 
   */
  void WorldSet(Map &m , BNLib::BinaryDD &fn );
  
  /** \brief Like WorldSet, but add to existing values */
  void WorldAdd(Map &m , BNLib::BinaryDD &fn );

  /*! Additionally, must supplied of pixels to actually set.
   */
  void WorldSet(Map &m , BNLib::BinaryDD &fn, 
		std::valarray<bool> const  &mask );

  /** \brief Set a map by passing pixel coordinates to a function
     
      \param m the map to be set
      \param fn the function to use
   */
  void PixelSet(Map &m , BNLib::BinaryDD &fn );

}

#endif 
