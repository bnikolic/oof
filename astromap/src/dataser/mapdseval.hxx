/**
   \file mapdseval.hxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   2004-2008

   Interpolation of maps to positions contained in a dataseries and
   similar routines.
*/
#ifndef _ASTROMAP_MAPDSEVAL_HXX__
#define _ASTROMAP_MAPDSEVAL_HXX__

#include <valarray>
#include <vector>

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
    
    /**
     \param index The indices of pixels to be weighted together

     \param coeff The coefficients to use for the weighthing
    */
    MapPixLC( std::valarray<unsigned> const &index , 
	      std::valarray<double > const &coeff );

    /*! Calculate the linear combination on the supplied map and
      return the value*/
    double operator() (Map const &m);

    /**
       Calculate the linear combination, but ofset all of the indices
       by the supplied parameter
    */
    double operator() (Map const &m, 
		       signed int offset);

    /**
       Print indices and coefficients to standard output
    */
    void print(void) ;
    
  };

  /**
    Return a pixel linear combination which represents a gaussian
    interpolation at position cx,cy of a map of properties like
    msample.
    
    \param fwhm_px is the full-width-half-maximum of the interpolation
    gaussian kernel

    \param extent_px it the size of the kernel.
  */
  MapPixLC * MkGaussCoffs (double cx, double cy, Map const &msample,
			   double fwhm_px, double extent_px);

  /**
     Return a pixel interpolation which represent simple flat circle
     specified in pixel coordinates.
     
  */
  MapPixLC * MkCircleCoeffs (int px, int py, 
			     Map const &msample,
			     double radius);

  /**
     \brief Return a pixel linear combination which represents a bi-linear
     interpolation.

     \param px,py position to interpoalte to
   */
  MapPixLC * MkBiLinearCoeffs (double px, 
			       double py, 
			       Map const &msample);

  /**\brief Bi-linearly interpolate map to supplied positions
   */
  void BiLinearMapInterp( const double *px,
			  const double *py,
			  double  * res,
			  size_t n,
			  const Map &m);

  /**
     Allow easy storage of pre-computed linear-combination
     coefficients so that multiple interpolations from maps with same
     coordinate systems can be obtained quickly.
     
  */
  class MapDSEvalBase {

  protected:
    
    std::valarray<MapPixLC *> lcs;    

  public:

    virtual ~MapDSEvalBase();

    /*! 
      Interpolate the supplied map m to the position in the
      dataseries supplied in constructor and return the result in the
      array res.
    */
    void Calc( Map const &m, 
	       std::valarray<double> & res);

    /** Provide an interface to calc that uses standard
	vectors... better for use in python.
     */
    void Calc( Map const &m, 
	       std::vector<double> & res);
    
    /**
       Store the evaluated interpolations into a the "fnu" element of
       a dataseries structure -- useful for simulations etc.
    */
    void Calc( Map const &m, 
	       DataSeries & res);

  };
  
  /** 
    Interpolates a map using a gaussian kernel onto the positions
    specified by the data series. Use this class to make it possible
    to re-use kernel coefficients as the input map changes --
    significantly saving time.
  */
  class MapDSEval:
    public MapDSEvalBase
  {

  public:

    /** \brief Setups the interpolators so that they can be evaluated
	quickly.
	
	\param ds The positions to interpolate to. All calls to Calc
	will be apropriate for these positions only.

	\param msample Map dimensions are figured out from this.

	\param fwhm_px define the Gaussian interpolation kernel used.

	\param extent_px extent of the kernel in pixels. The kernel
	will extend from centre-extent to centre+extent inclusive, so
	extent_px=1 implies a 3x3 kernel.
    */
    MapDSEval( DataSeries const & ds , 
	       Map const & msample,
	       double fwhm_px, double extent_px);


  };
  
  /**
     For each position in the supplied data series, return the closest
     pixel in the supplied maps. In contrast to MapDSEval no
     interpolation of any kind is done.
   */
  class MapDSNearest :
    public MapDSEvalBase
  {

  public:
    /**
       \param msample used only to determine the dimensions and the
       coordinate system.
    */
    MapDSNearest( DataSeries const & ds , 
		  Map const & msample);


  };


}
#endif
