/**
   \file mapdseval_flat.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   Initial version November 2011

   Interpolation of maps, but with the coefficients etc in flat data
   structures (minimal heap allocation) to optimise memore locality
*/
#ifndef _ASTROMAP_MAPDSEVAL_FLAT_HXX__
#define _ASTROMAP_MAPDSEVAL_FLAT_HXX__

#include <vector>

#include "mapdseval.hxx"

namespace AstroMap {

  class MapDSEvalFlat:
      public MapDSEvalBase
  {

    /** Stride in coefficients to get to next return value
     */
    const size_t c_stride;
    const size_t ndp;
    const size_t nt;

    std::vector<double> iv, cv;

  public:
    
    MapDSEvalFlat(DataSeries const & ds , 
                  Map const & msample,
                  double fwhm_px, 
                  double extent_px);

    ~MapDSEvalFlat();

    void Calc( Map const &m, 
	       std::valarray<double> & res);

    MapDSEvalBase *clone(void);
    
  };

}

#endif
