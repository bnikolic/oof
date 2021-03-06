/**
   \file   coordsys.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>
  
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

    // ---------- Construction - Destruction -----------
    
    virtual ~CoordSys() {};
    
    // ---------- Public interface ---------------------

    /*! Return a copy of myself */
    virtual CoordSys * Clone(void) const  = 0 ;

    /*! Converts pixel to world coordinates */
    virtual   void pxtoworld(double px , double py , double &wx , double &wy) const = 0;

    /*! Convert world to pixel coordinates */
    virtual void worldtopx(double wx, double wy , double &px , double &py ) const = 0;

    // ------------- Helper functions to avoid references ----------------
    
    double  x_pxtoworld(double px , double py );
    double  y_pxtoworld(double px , double py );

    double  x_worldtopx(double wx, double wy );
    double  y_worldtopx(double wx, double wy );

  };
  


}

#endif
