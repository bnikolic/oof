/*
  Bojan Nikolic
  $Id: lincordsys.hxx,v 1.1 2005/06/21 00:44:47 bnikolic Exp $

  Linear 2-D coordinate system implementation
*/

#ifndef __ASTROMAP_LINCOORDSYS_HXX__
#define __ASTROMAP_LINCOORDSYS_HXX__

#include "coordsys.hxx"

#include <valarray>

namespace AstroMap {

  class LinCS : public CoordSys {

  public:

    /*! This is the 3 by 2 transformation matrix corresponding to the
     *  coordinate system
     */
    std::valarray<double> TM;

    /* ------- Constructors  & Destructors  --------*/

    /*! Default constructor: unit transformation */
    LinCS(void);

    virtual ~LinCS();

    /* ------- Member functions  -------------------*/
    
    /*! Make a copy of myself */
    virtual CoordSys * Clone(void) const {
      return new LinCS(*this) ;
    }

    const void pxtoworld(double px , double py , double &wx , double &wy) ;

  };
  


}

#endif
