/*!
  Bojan Nikolic
  $Id: zernmodel.hxx,v 1.1 2005/08/03 12:01:42 bnikolic Exp $

  Zernike model for the aperture phase distribution
*/
#ifndef _OOF_ZERNMODEL_HXX__
#define _OOF_ZERNMODEL_HXX__

// forwards
namespace AstroMap {
  class Map;
  class CoordSys;
}

namespace OOF {

  /*! Saves the coordinate system of a map and automatically restores
   *   at object destructin
   */
  class CSSave {

    AstroMap::Map & m;
    AstroMap::CoordSys * csorig;

  public:
    
    CSSave(AstroMap::Map & m );

    /*! At destruction, restore the saved coordinate system */
    ~CSSave();
    

  };
  


  /*! Set up a coordinate system suitable for calculating zernike
   *  polys. For circular apertures (ie., all cases so far?) this
   *  means normalising at to unit value at edge.
   */
  void ZernCSSetup(Map &m , double dishradius);
  
  



}

#endif
