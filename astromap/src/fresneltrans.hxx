/**
   \file fresneltrans.hxx

    Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
    
    May 2007

    Implementation fresnel transforms for the investigation of near
    field beam shapes.
*/
#ifndef _ASTROMAM_FRESNELTRANS_HXX__
#define _ASTROMAM_FRESNELTRANS_HXX__

#include <complex>

namespace AstroMap {

  // Forward declarations
  class Map;

  /** 
      Calculate the pixel (k,l) of the Fresnel transform of the map m.
  */
  std::complex<double> dFresnelDir( const Map & m,
				    size_t k,
				    size_t l,
				    double R);



}


#endif
