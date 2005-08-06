/*
  Bojan Nikolic
  $Id: mapset.hxx,v 1.2 2005/08/06 14:12:11 bnikolic Exp $

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

  /*! Additionally, must supplied of pixels to actually set.
   */
  void WorldSet(Map &m , BNLib::BinaryDD &fn, 
		std::valarray<bool>  &mask );

}

#endif 
