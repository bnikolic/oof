/*!
  Bojan Nikolic
  $Id: gbtgeo.hxx,v 1.1 2005/08/17 20:43:31 bnikolic Exp $

*/
#ifndef _OOF_TELGEO_GBTGEO_HXX__
#define _OOF_TELGEO_GBTGEO_HXX__

#include "telgeo.hxx"

namespace OOF {

  /*! Describes the geometry when using a cassegrain focus */
  class  GBTGeo :  public  TelGeometry {

  public:

    /* ----------- Data members ------------*/

    /*! Radius of the primary reflector */
    double PrimRadius;
    
    /*! Focal length of the primary */
    double PrimF;
    
    /*! Effective focal length at gregorian focus*/
    double GregF ;

    /* Constructors / Desctructors                  */

    /*! Default constructor sets up for the real GBT */
    GBTGeo(void);

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
		       const GBTGeo & geo);

  
}
#endif
