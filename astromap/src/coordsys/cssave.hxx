/*!
  Bojan Nikolic
  $Id: cssave.hxx,v 1.2 2005/08/06 16:19:54 bnikolic Exp $

  A small utility class to save the state of a coordinate system
  attached to a map
*/

#ifndef _ASTROMAP_CSSAVE_HXX__
#define _ASTROMAP_CSSAVE_HXX__

namespace AstroMap {

  // Forwards
  class Map;
  class CoordSys;

  /*! Saves the coordinate system of a map and automatically restores
   *   at object destructin
   */
  class CSSave {

    Map & m;
    CoordSys * csorig;

  public:
    
    CSSave(Map & m );

    /*! At destruction, restore the saved coordinate system */
    ~CSSave();
    

  };



}

#endif
