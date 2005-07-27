/*
  Bojan Nikolic
  $Id: pixextract.hxx,v 1.2 2005/07/27 20:00:55 bnikolic Exp $

  Extract ranges of pixels from a map
*/

#ifndef _ASTROMPA_PIXEXTRACT_HXX__
#define _ASTROMPA_PIXEXTRACT_HXX__

#include <valarray>
#include <memory>

namespace AstroMap {

  // Forwards
  class Map;

  /*! Stores a list of pixel positions */
  struct PixListInt {

    /*! x-position of each pixel.  */
    std::auto_ptr< std::valarray<int> > px;

    /*! y-position of each pixel */
    std::auto_ptr< std::valarray<int> > py;

    /*--- Constructors & Destructors ----*/
    PixListInt(size_t npix);

    /*! copy constructor needed for swig */
    PixListInt(const PixListInt &p);
    
  };

  /*! Extract a sqaure of pixels around cx, cy */
  PixListInt ExSquare( int cx, int cy , int halflen_px, Map const &m);


}

#endif
