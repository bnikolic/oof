/**
   \file zernmodel.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

   Zernike model for the aperture phase distribution
*/
#ifndef _OOF_ZERNMODEL_HXX__
#define _OOF_ZERNMODEL_HXX__

#include "phasemod.hxx"



// forwards
namespace AstroMap {
  class Map;
  class CoordSys;
  class LCMaps;
}

namespace OOF {


  // forwards
  class CassegrainGeo;
  class TelGeometry;


  /*! Set up a coordinate system suitable for calculating zernike
   *  polys. For circular apertures (ie., all cases so far?) this
   *  means normalising at to unit value at edge.
   */
  void ZernCSSetup(AstroMap::Map &m , double dishradius);


  /*! 
   * An aperture phase model using rasterized zernike polynomials
   */
  class RZernModel  : public PhaseMod {

    /*! The higherst radial order of zernikes that is present */
    unsigned maxzorder;

    /*!  Rasterised  zernike polys are stored here */
    AstroMap::LCMaps * lcm;

    
  public:
    
    // -----    Constructors & Destructors   ------------

    /**
       \param n        the maximum zernike polynomial order 

       \param msample A sample aperture map which
       dimensions/coordinate system is used to setup the zernike
       polynomials
       
       \param telgeo Telescope geometry (ownership not taken)
       
       \bug telgeo should be const

     */
    RZernModel ( unsigned n , AstroMap::Map & msample, TelGeometry * telgeo );

    virtual ~RZernModel();

    // ------ Member functions ----------------------------

    /*! Make a rasterised version of the required zernike
     *  polynomials. Phase values where mask ==0.0 are set to zero. */
    void RastZerns (  unsigned n , AstroMap::Map &msample, 
		      AstroMap::Map & mask );

    // ------ Inherited functions from PhaseMod    ---------

    void Calc( AstroMap::Map &m) const;
    void ZeroTilt(void) ;

    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );


  };
  
  



}

#endif
