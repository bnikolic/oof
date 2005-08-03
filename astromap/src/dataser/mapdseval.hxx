/*
  Bojan Nikolic
  $Id: mapdseval.hxx,v 1.2 2005/08/03 12:00:37 bnikolic Exp $

  Interpolate a map to positions contained in a dataseries.
*/
#ifndef _ASTROMAP_MAPDSEVAL_HXX__
#define _ASTROMAP_MAPDSEVAL_HXX__

#include <valarray>



namespace AstroMap {

  // Forwards;
  class Map;
  class DataSeries;

  /*!

    This represents a linear combination of pixels from a map. I.E.,
    this can be used to interpolate a map to a particular postion
    using any desired kernel.

  */
  class MapPixLC {
    
    std::valarray<unsigned> index;
    std::valarray<double>   coeff;

  public:
    
    /*! */
    MapPixLC( std::valarray<unsigned> const &index , 
	      std::valarray<double > const &coeff );

    /*! Calculate the linear combination on the supplied map and
      return the value*/
    double operator() (Map const &m);
    
  };

  /*! 
    Return a pixel linear combination which represents a gaussian
    interpolation at position cx,cy of a map of properties like
    msample.
    
    fwhm_px is the full-width-half-maximum of the interpolation
    gaussian kernel and extent_px it the size of the kernel.
  */
  MapPixLC * MkGaussCoffs (double cx, double cy, Map const &msample,
			   double fwhm_px, double extent_px);

  
  /*! 
   
  */
  class MapDSEval {
    
    std::valarray<MapPixLC *> lcs;

  public:

    /*! Setup the interpolators so that can be evaluated quickly*/
    MapDSEval( DataSeries const & ds , 
	       Map const & msample,
	       double fwhm_px, double extent_px);

    ~MapDSEval();

    /*! 
      Interpolate the supplied map m to the position in the
      dataseries supplied in constructor and return the result in the
      array res.
    */
    void Calc( Map const &m, std::valarray<double> & res);

  };


}
#endif
