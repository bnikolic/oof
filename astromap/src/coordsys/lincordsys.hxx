/*
  Bojan Nikolic
  $Id: lincordsys.hxx,v 1.3 2005/07/03 16:15:06 bnikolic Exp $

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

    /** \brief Initialise with just the linear scales in the two
	direction
     */
    LinCS(double xs,
	  double ys);

    virtual ~LinCS();

    /* ------- Member functions  -------------------*/
    
    /*! Make a copy of myself */
    virtual CoordSys * Clone(void) const {
      return new LinCS(*this) ;
    }

    /* ------ Inherited member functions  ------------ */
    void pxtoworld(double px , double py , double &wx , double &wy) const ;
    void worldtopx(double wx, double wy , double &px , double &py ) const ;

  };
  


}

#endif
