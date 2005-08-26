/*!
  Bojan Nikolic
  $Id: mkapertures.cxx,v 1.2 2005/08/15 22:14:16 bnikolic Exp $

  Functions to make apertures...
*/

#include "mkapertures.hxx"

#include <memory>

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

    std::auto_ptr< AstroMap::Map  > msample (  MkApMap ( telgeo, npix, oversample));
    
    RZernModel * phasemod = new RZernModel( nzern,
					    *msample,
					    telgeo);

    GaussAmpMod * ampmod  = new GaussAmpMod (telgeo,
					     *msample);

    
    return new ApertureMod( phasemod, ampmod,
			    wavel,
			    *msample);


  }


  Minim::Model * ApertureMod::downcast(void)
  {
    return this;
  }


}

