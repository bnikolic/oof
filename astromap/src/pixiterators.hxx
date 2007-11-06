/**
   \file pixiterators.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

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

    /// Get current position
    int  get_y(void) { return y;};

    /// Return the current rectangular radius.
    unsigned get_n(void);

  };


}

#endif

