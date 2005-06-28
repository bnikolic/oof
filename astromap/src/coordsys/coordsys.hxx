/*
  Bojan Nikolic
  $Id: coordsys.hxx,v 1.3 2005/06/28 13:19:14 bnikolic Exp $

  
*/
#ifndef _ASTROMAP_COORDSYS_HXX__
#define _ASTROMAP_COORDSYS_HXX__

namespace AstroMap {

  
  /*! Coordinate system description, specific to two dimensions
   *  without attempts for generalisations.
   *
   */
  class CoordSys {

  public:

    /*! Return a copy of myself */
    virtual CoordSys * Clone(void) const  = 0 ;

    /*! Converts pixel to world coordinates */
    virtual   void pxtoworld(double px , double py , double &wx , double &wy) const = 0;


  };
  


}

#endif
