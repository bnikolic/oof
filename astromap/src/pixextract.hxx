/**
   \file pixextract.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>

   Extract ranges of pixels from a map
*/

#ifndef _ASTROMPA_PIXEXTRACT_HXX__
#define _ASTROMPA_PIXEXTRACT_HXX__

#include <valarray>
#include <memory>

namespace AstroMap {

  // Forwards
  class Map;

  /**
     \brief Return the nearest in-bounds pixel in map m to the world
     coordinates (cx,cy)
  */
  void GetNearestPixel( const Map & m,
			double cx, double cy,
			int & pxOUT, int & pyOUT );

  /** Stores a list of pixel positions
  */
  struct PixListInt {

    /*! x-position of each pixel.  */
    std::valarray<int>  px;

    /*! y-position of each pixel */
    std::valarray<int> py;

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
