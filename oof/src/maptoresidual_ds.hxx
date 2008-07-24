/**
   \file maptoresidual_ds.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>

*/

#ifndef __OOF_MAPTORESIDUAL_DS_HXX__
#define __OOF_MAPTORESIDUAL_DS_HXX__

#include "maptoresidual.hxx"

#include <valarray>
#include <astromap_fwd.hxx>


namespace OOF {

  /** \brief Residuals from dataseries observations

     This class takes dataseries observations and compares them to
     model `skyviews` or beams convolved for the effects of
     observations
  */
  class MapToResidualDS : 
    public MapToResidual 
  {

    /*! The observed dataseries. This class takes ownership */
    AstroMap::DataSeries * obsds;
    
    /*! A scratch valarray to hold the results of interpolation of the
     * map to dataseries */
    std::valarray<double> modelds;

    /*! This converts the supplied maps to a model data series */
    AstroMap::MapDSEval * mapinterp;

  public:

    /* ----- Constructors / Destructors  ----------------*/

    /**
       \param obsds The obseved data series, we take ownership
       
       \param msample A sample skyview map

       \param fwhm_px the FWHM of the interpolation kernel (in pixels)
    */
    MapToResidualDS(  AstroMap::DataSeries * obsds, 
		      AstroMap::Map const & msample,
		      double fwhm_px, double extent_px);

    virtual ~MapToResidualDS() ;

    /* ----- Member Functions ---------------------------*/
    
    /*! Returns a dataseries which would have been observed if the
      modelmap was the true beam*/
    AstroMap::DataSeries * MkModelDS( AstroMap::Map & modelmap);

    /* ----- Functions inherited from MApToResidual ------ */

    virtual unsigned   nres (void)    ; 

    virtual size_t residuals ( AstroMap::Map & model, 
			       std::vector<double>::iterator  resv ) ;


    

  };


}


#endif
