/*
  Bojan Nikolic
  $Id: csops.hxx,v 1.2 2005/07/08 22:04:57 bnikolic Exp $

  Coordinate system operations
*/
#ifndef __ASTROMAP_CSOPS_HXX__
#define __ASTROMAP_CSOPS_HXX__

namespace AstroMap {

  class Map;

  /*! Assign a coordinate system centred at zero, square in total
    dimension and with the specified halflength
  */
  void MkApCS(Map &m, double halflen);


}

#endif
