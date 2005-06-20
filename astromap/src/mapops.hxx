/*
  Bojan Nikolic
  $Id: mapops.hxx,v 1.1 2005/06/21 00:44:45 bnikolic Exp $

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

}


#endif
