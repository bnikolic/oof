/**
   \file maptoresidual_ds.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>
   
*/

#include "maptoresidual_ds.hxx"

#include <astromap.hxx>
#include <dataseries.hxx>
#include <mapdseval.hxx>
#include <mapdseval_flat.hxx>

#define DSREG 1

namespace OOF {

  MapToResidualDS::MapToResidualDS(  AstroMap::DataSeries * obsds, 
				     AstroMap::Map const & msample,
				     double fwhm_px, double extent_px) :
    obsds(obsds) ,
    modelds( obsds->size() ),
#ifdef DSFLAT
    mapinterp( new AstroMap::MapDSEvalFlat( * obsds, msample, fwhm_px, extent_px ) )
#endif
#ifdef DSREG
    mapinterp( new AstroMap::MapDSEvalReg( * obsds, msample, fwhm_px, extent_px ) )
#endif
#ifdef DSSTD
    mapinterp( new AstroMap::MapDSEval( * obsds, msample, fwhm_px, extent_px ) )
#endif
  {

  }
  MapToResidualDS::MapToResidualDS(AstroMap::DataSeries *obsds, 
				   AstroMap::MapDSEvalBase *mapinterp):
    obsds(obsds),
    modelds(obsds->size()),
    mapinterp(mapinterp)
  {
  }
    

  MapToResidualDS::~MapToResidualDS()
  {
    delete obsds;
    delete mapinterp;
  }

  MapToResidualDS * MapToResidualDS::clone(void)
  {
    return new MapToResidualDS(obsds->clone(),
			       mapinterp->clone());
  }

  unsigned   MapToResidualDS::nres (void)  
  {
    return obsds->size();
  }

  AstroMap::DataSeries * MapToResidualDS::MkModelDS( AstroMap::Map & modelmap)
  {

    mapinterp->Calc( modelmap, modelds );

    AstroMap::DataSeries * res  ( new AstroMap::DataSeries(*obsds));

    for (size_t i =0 ; i < obsds->size() ; ++i )
      (*res)[i].fnu = modelds[i];

    return res;
  }

  size_t MapToResidualDS::residuals ( AstroMap::Map & model, 
				      std::vector<double>::iterator  resv )
  {

    mapinterp->Calc( model, modelds );
    
    for (size_t i = 0 ; i < obsds->size() ; ++i )
      {
	* resv = ( (*obsds)[i].fnu - modelds[i] )  / (*obsds)[i].ufnu ;
	++resv;
      }
    return obsds->size();
  }

}



