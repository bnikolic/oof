/*
  Bojan Nikoic
  $Id: primefoc.hxx,v 1.2 2005/08/31 14:07:32 bnikolic Exp $

  Description of prime focus telescope geometry
*/
#ifndef _OOF_TELGEO_PRIMEF___
#define _OOF_TELGEO_PRIMEF___

#include "telgeo.hxx"

namespace OOF {

  class  PrimeFocusGeo : public  TelGeometry {

  public:

    /* ----------- Data members ------------*/

    /*! Radius of the primary reflector */
    double PrimRadius;
    
    /*! Focal length of the primary */
    double PrimF;

    /* ------------ Member fns -----------*/

    void MkFocMove ( double dx, double dy , double dz, AstroMap::Map & Phase) const ;

    /* ------------ Functions inherited from TelGeo -------------*/

    virtual void MkDefocus( double dz , AstroMap::Map & Phase) const  ;

    virtual void DishMask (AstroMap::Map &Dish) const ;

    virtual double DishEffRadius(void) const ;  

  };


  /*! Calculate path change due to movement of the prime focus.
   *  x,y is the positions in the aperture plane to calculate the path
   *  change.  
   *  dX, dY , dZ are the movements of the secondary mirror. 
   */
  double PrimDeltaPath (double x, double y,
			double dX, double dY , double dZ,
			const PrimeFocusGeo & geo);
}


#endif
