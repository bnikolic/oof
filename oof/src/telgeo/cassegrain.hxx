/*!
  Bojan Nikolic
  $Id: cassegrain.hxx,v 1.4 2005/08/09 01:09:19 bnikolic Exp $

*/
#ifndef _OOF_TELGEO_CASSEGRAIN_HXX__
#define _OOF_TELGEO_CASSEGRAIN_HXX__

#include "telgeo.hxx"

namespace OOF {

  /*! Describes the geometry when using a cassegrain focus */
  class  CassegrainGeo :  public  TelGeometry {

  public:

    /* ----------- Data members ------------*/

    /*! Radius of the primary reflector */
    double PrimRadius;
    
    /*! Focal length of the primary */
    double PrimF;
    
    /*! Radius of the secondary */
    double SecRadius;

    /*! Effective focal length at cassegrain focus*/
    double CasF;

    /* ------------ Inherited functions -------------*/

    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const  ;

    virtual void DishMask (AstroMap::Map &Dish) const ;

    virtual double DishEffRadius(void) const ;
    
  };

  /*! Calculate path change due to movement of the secondary mirror
   *  from optimal position.
   *
   *  x,y is the positions in the aperture plane to calculate the path
   *  change.  
   *  dX, dY , dZ are the movements of the secondary mirror. 
   */
  double SecDeltaPath (double x, double y,
		       double dX, double dY , double dZ,
		       const CassegrainGeo & geo);

  
}
#endif
