/*
  Bojan Nikolic
  $Id: csops.hxx,v 1.5 2006/06/20 17:56:12 bnikolic Exp $

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

  /*! Assign a rectangular coordinate system */
  void MkRectCS(Map &m, 
		double xmin, double xmax,
		double ymin, double ymax);

  /*! Shring the coordinate cs around the centre of the map by the
   * specified factor
   */
  void ShrinkCS(Map &m , double cf );

  /**
     Keep the scales defined by the coordinate system but re-center it
     so that the middle pixel of the map has coordinates 0,0.
   */
  void ZeroOffsetCS(Map &m);
    


}

#endif
