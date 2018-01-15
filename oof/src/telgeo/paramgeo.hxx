/**
   \file paramgeo.hxx
   2018 Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
*/
#ifndef _OOF_TELGEO_PARAMGEO_HXX__
#define _OOF_TELGEO_PARAMGEO_HXX__

#include "telgeo.hxx"

#include <vector>

#include <minimmodel.hxx>

namespace OOF {

  /**
     \brief Geometry specified as a Zernike parametrisation
     
     Use for shaped antennas 
  */
  class  ParamGeo :  
    public  TelGeometry 
  {

  public:
    /** 
	\param R Radius of the aperture (aperture is assumed circular)

	\param zpars Zernike coefficients parametrising the effective
	focal length
     */
    ParamGeo(double R,
	     const std::vector< Minim::DParamCtr > &zpars);

    /* ------------ Functions inherited from TelGeo -------------*/
    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const  ;
    virtual void DishMask (AstroMap::Map &Dish) const ;
    virtual double DishEffRadius(void) const ;

  private:
    double _R;
    
  };

  /** Zernike param name to integer */
  size_t ZernToInt(const std::string &zname);

  /** What is the maximum order needed to represent params
   */
  size_t maxZOrder(const std::vector< Minim::DParamCtr > &zpars);
		   

  /** Rasterize and sum Zernikes 
   */
  void RasterizeZern(const std::vector< Minim::DParamCtr > &zpars,
		     AstroMap::Map &m,
		     double R);

}

#endif
