/*
  Bojan Nikolic
  $Id: mapops.hxx,v 1.3 2006/04/01 20:40:01 bnikolic Exp $

  Some operations on maps
*/
#ifndef _ASTROMAP_MAPOPS_HXX__
#define _ASTROMAP_MAPOPS_HXX__

namespace AstroMap {

  // Forwards
  class Map;

  /*!
   *  Assign a normal distribution of defined by sigma to the supplied
   *  map.
   *
   *  This is _not_ the function to use if you need lots and lots of
   *  random maps. The reson for this is that each call uses a new 
   *  random number generator which only seeded from the sysclock --
   *   bound to be less random than a real sequence.  void
   *  
   */
  void NormDist(Map &m, double sigma);

  /*!
   * Calculate the RMS value of the map
   */
  double MapRMS( Map &m);

  /*!
   * This function is misnamed: it actually calculates the standard
   * deviation of the supplied map weighted by the map weight.
   */
  double MapRMS( Map &m, Map & weight);

  /*!
   *  Create a map that is scale times bigger than m, with the pixel
   *  values replicated to fill up the bigger map.
   */
  Map *  IntZoom( Map &m, unsigned scale);

}


#endif
