/**
   \file mkapertures.cxx
   
   Bojan Nikolic  <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include "mkapertures.hxx"

#include <memory>

#include <astromap.hxx>
#include <csops.hxx>

#include "aperturemod.hxx"

#include "../telgeo/telgeo.hxx"

#include "zernmodel.hxx"
#include "gaussampmod.hxx"
#include "tophatmodel.hxx"



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

  ApertureMod * MkMUSTANGAp( TelGeometry * telgeo ,
			     double wavel,
			     unsigned npix,
			     unsigned nzern ,
			     double oversample )
  {
    std::auto_ptr< AstroMap::Map  > msample (  MkApMap ( telgeo, npix, oversample));
    
    RZernModel * phasemod = new RZernModel( nzern,
					    *msample,
					    telgeo);

    TopHatAmpMod * ampmod  = new TopHatAmpMod(45.0);

    
    return new ApertureMod( phasemod, ampmod,
			    wavel,
			    *msample);


  }


  Minim::Model * ApertureMod::downcast(void)
  {
    return this;
  }


}


