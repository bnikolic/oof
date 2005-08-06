/*!
  Bojan Nikolic
  $Id: zernmodel.hxx,v 1.6 2005/08/06 16:20:29 bnikolic Exp $

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

    /*!
     * n is the maximum zernike polynomial order 
     */
    RZernModel ( unsigned n , AstroMap::Map & msample, CassegrainGeo & telgeo );

    RZernModel ( unsigned n , AstroMap::Map & msample, TelGeometry * telgeo );

    virtual ~RZernModel();

    // ------ Member functions ----------------------------
    void RastZerns (  unsigned n , AstroMap::Map &msample);

    // ------ Inherited functions from PhaseMod    ---------

    void Calc( AstroMap::Map &m) const;

    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );


  };
  
  



}

#endif
