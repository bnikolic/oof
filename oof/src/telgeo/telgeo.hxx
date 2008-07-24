/**
   \file telgeo.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Classes to describe relevant parameters of telescope geometry
*/

#ifndef _OOF_TELGEO_HXX__
#define _OOF_TELGEO_HXX__

// Forwards
namespace AstroMap {
  class Map;
}

namespace OOF {

  /** Defines interface of functions needed to describe the telescope
      geometry oof analysis.
   
  */
  class TelGeometry {


  public:
    
    // ---------- Construction - Destruction -----------
    
    virtual ~TelGeometry() {};

    // ---------- Public interface ---------------------
    
    /*! Calculates the phase change in the aperture plane due to a
     * defocus dz */
    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const = 0 ;

    /*! Sets all of the pixels in the supplied map to 1 where there
     * exists a reflecting surface and 0 where there doesn't exist a
     * reflecting surface*/
    virtual void DishMask (AstroMap::Map &Dish) const =0;

    /*! Returns an effective radius for use when it is necessary to
     * normalise quantaties to unity at dish-edge
     */
    virtual double DishEffRadius(void) const = 0;


  };


}
#endif
