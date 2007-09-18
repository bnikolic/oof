/**
   \file dstomap.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
   Drizzle a dataseries into a map
*/

#ifndef _ASTROMAP_DSTOMAP_HXX__
#define _ASTROMAP_DSTOMAP_HXX__

namespace AstroMap {

  // Forwards
  class DataSeries;
  class Map;

  /*!
   *  Drizzle the supplied data series into the supplied map using a
   *  releatively simple algorithm.
   */
  void SimpleDrizzle ( DataSeries &ds , Map &m1, 
		       double extent_px, double fwhm_px );


}

#endif
