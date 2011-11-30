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

  /** The kernel is always a regular square of same size. This means
      that pixels too close to the map edge can not be degridded, but
      should improve performance significantly because of easier to
      predict memory access
   */ 
  class MapDSEvalReg:
      public MapDSEvalBase
  {

    /** Stride to go to next row in map
     */
    const size_t i_stride;

    /** Row length*/
    const size_t rl;

    const size_t ndp;

    /** Starting index for each square */
    std::vector<size_t> iv;

    std::vector<double> cv;

  public:
    
    MapDSEvalReg(DataSeries const & ds , 
                 Map const & msample,
                 double fwhm_px, 
                 double extent_px);

    ~MapDSEvalReg();

    void Calc( Map const &m, 
	       std::valarray<double> & res);

    MapDSEvalBase *clone(void);
    
  };

}

#endif
