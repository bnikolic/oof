/*
  Bojan Nikolic
  $Id: csops.hxx,v 1.4 2006/04/13 16:16:18 bnikolic Exp $

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

  /*! Assing a rectangular coordinate system */
  void MkRectCS(Map &m, double xhalflen, double yhalflen);

  /*! Shring the coordinate cs around the centre of the map by the
   * specified factor
   */
  void ShrinkCS(Map &m , double cf );


}

#endif
