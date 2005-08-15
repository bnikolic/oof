/*!
  Bojan Nikolic
  $Id: mkapertures.cxx,v 1.1 2005/08/15 21:57:46 bnikolic Exp $

  Functions to make apertures...
*/

#include "mkapertures.hxx"

#include <astromap.hxx>
#include <csops.hxx>


#include "aperturemod.hxx"

#include "../telgeo/telgeo.hxx"

#include "zernmodel.hxx"
#include "gaussampmod.hxx"



namespace  OOF {

  AstroMap::Map * MkApMap ( TelGeometry * telgeo ,
			    unsigned npix,
			    double oversample)
  {
    AstroMap::Map * res = new AstroMap::Map (npix, npix);
    
    MkApCS(*res ,  telgeo->DishEffRadius() * oversample  );

    return res;

  }

  ApertureMod * MkSimpleAp( TelGeometry * telgeo ,
			    double wavel,
			    unsigned npix,
			    unsigned nzern ,
			    double oversample )
  {

    

  }


}


