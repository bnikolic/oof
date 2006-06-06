/**
   \file pixiterators.hxx

   Bojan Nikolic
   $Id: pixiterators.hxx,v 1.2 2006/06/06 20:18:18 bnikolic Exp $

   Iterating on pixels 
*/
#ifndef __ASTROMAP_PIXITERATORS_HXX
#define __ASTROMAP_PIXITERATORS_HXX

namespace AstroMap {

  /** A sketch for a spiral iterator */
  class PixISpiral {

    /// The central pixel
    int cx, cy;

    /// The current pixel
    int x, y;

    /// The recangular radius
    int n;

  public:


    PixISpiral ( int cx, int cy  );

    /// Go to next pixel
    void operator++ (void) ;

    /// Go to next pixel;
    void advance(void);

    /// Get current position
    int  get_x(void) { return x;};
    int  get_y(void) { return y;};

  };


}

#endif

