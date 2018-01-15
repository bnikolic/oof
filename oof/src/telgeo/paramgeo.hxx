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

  typedef std::vector<  std::pair< std::string, double>  > parset;

  /**
     \brief Geometry specified as a Zernike parametrisation
     
     Use for shaped antennas 
  */
  class  ParamGeo :  
    public  TelGeometry 
  {

  public:

    ParamGeo(void):
      _R(1)
    {};
    
    /** 
	\param R Radius of the aperture (aperture is assumed circular)

	\param zpars Zernike coefficients parametrising the effective
	focal length
     */
    ParamGeo(double R,
	     const parset  &zpars);

    /* ------------ Functions inherited from TelGeo -------------*/
    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const  ;
    virtual void DishMask (AstroMap::Map &Dish) const ;
    virtual double DishEffRadius(void) const {return _R;} ;

  private:
    const double _R;
    const parset _zpars;
    
  };

  /** Zernike param name to integer */
  size_t ZernToInt(const std::string &zname);

  /** What is the maximum order needed to represent params
   */
  size_t maxZOrder(const parset &zpars);
		   

  /** Rasterize and sum Zernikes 
   */
  void RasterizeZern(const  parset &zpars,
		     AstroMap::Map &m,
		     double R);

}

#endif
