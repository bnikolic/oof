/*!
  Bojan Nikolic
  $Id: maptoresidual_ds.hxx,v 1.1 2005/08/15 15:02:07 bnikolic Exp $

*/

#ifndef __OOF_MAPTORESIDUAL_DS_HXX__
#define __OOF_MAPTORESIDUAL_DS_HXX__

#include "maptoresidual.hxx"

#include <valarray>
#include <astromap_fwd.hxx>


namespace OOF {

  /*! This map takes dataseries observations and compares them to
    model `skyviews` or beams convolved for the effects of
    observations  */
  class MapToResidualDS : public MapToResidual {

    /*! The observed dataseries. This class takes ownership */
    AstroMap::DataSeries * obsds;
    
    /*! A scratch valarray to hold the results of interpolation of the
     * map to dataseries */
    std::valarray<double> modelds;

    /*! This converts the supplied maps to a model data series */
    AstroMap::MapDSEval * mapinterp;

  public:

    /* ----- Constructors / Destructors  ----------------*/

    /*! obsds is the obseved data sereis, this class will take
    ownership. msample is a sample skyview map. fwhm_px is the FWHM of
    the interpolation kernel in terms of pixels. */
    MapToResidualDS(  AstroMap::DataSeries * obsds, 
		      AstroMap::Map const & msample,
		      double fwhm_px, double extent_px);

    virtual ~MapToResidualDS() ;

    /* ----- Member Functions ---------------------------*/


    /* ----- Functions inherited from MApToResidual ------ */

    virtual unsigned   nres (void)    ; 

    virtual size_t residuals ( AstroMap::Map & model, 
			       std::vector<double>::iterator  resv ) ;


    

  };


}


#endif
