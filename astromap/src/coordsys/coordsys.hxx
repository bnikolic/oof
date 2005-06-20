/*
  Bojan Nikolic
  $Id: coordsys.hxx,v 1.2 2005/06/21 00:44:47 bnikolic Exp $

  
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
    const virtual void pxtoworld(double px , double py , double &wx , double &wy) = 0;


  };
  


}

#endif
