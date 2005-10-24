/*
  Bojan Nikolic
  $Id: mapops.hxx,v 1.2 2005/10/24 22:04:47 bnikolic Exp $

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
   * Calculate the weighted RMS value of the map
   */
  double MapRMS( Map &m, Map & weight);

}


#endif
