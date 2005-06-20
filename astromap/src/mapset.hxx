/*
  Bojan Nikolic
  $Id: mapset.hxx,v 1.1 2005/06/21 00:44:46 bnikolic Exp $

*/

#ifndef _ASTROMAP_MAPSET_HXX__
#define _ASTROMAP_MAPSET_HXX__

#include <binaryfn.hxx>

namespace AstroMap {

  // Forwads
  class Map;

  /*! Set the map by calling the supplied binary function with world
   *  coordinates of each pixel 
   */
  void WorldSet(Map &m , BNLib::BinaryDD &fn );

}

#endif 
