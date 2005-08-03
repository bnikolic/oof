/*
  Bojan Nikolic
  $Id: pixextract.hxx,v 1.3 2005/08/03 12:00:37 bnikolic Exp $

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

    /*! Return the number of pixels in the pixel list */
    size_t size(void);
    
  };

  /*! Extract a sqaure of pixels around cx, cy */
  PixListInt ExSquare( int cx, int cy , int halflen_px, Map const &m);


}

#endif
