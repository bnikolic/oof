/*!
  Bojan Nikolic
  $Id: cssave.hxx,v 1.1 2005/08/06 16:18:27 bnikolic Exp $

  A small utility class to save the state of a coordinate system
  attached to a map
*/

#ifndef _ASTROMAP_CSSAVE_HXX__
#define _ASTROMAP_CSSAVE_HXX__

namespace AstroMap {

  // Forwards
  class Map;

  /*! Saves the coordinate system of a map and automatically restores
   *   at object destructin
   */
  class CSSave {

    AstroMap::Map & m;
    AstroMap::CoordSys * csorig;

  public:
    
    CSSave(AstroMap::Map & m );

    /*! At destruction, restore the saved coordinate system */
    ~CSSave();
    

  };



}

#endif
