/**
   \file mkapertures.cxx
   
   Bojan Nikolic  <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include "mkapertures.hxx"

#include <memory>
#include <boost/scoped_ptr.hpp>

#include <astromap.hxx>
#include <csops.hxx>

#include "aperturemod.hxx"
#include "multi_apmod.hxx"

#include "../telgeo/telgeo.hxx"

#include "zernmodel.hxx"
#include "gaussampmod.hxx"
#include "tophatmodel.hxx"
#include "sqgaussmod.hxx"



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

  ApertureMod *mkALMAAp(TelGeometry *telgeo,
			double wavel,
			unsigned npix,
			unsigned nzern,
			double oversample)
  {

    std::auto_ptr<AstroMap::Map> msample(MkApMap(telgeo,
						 npix, 
						 oversample));
    RZernModel * phasemod = new RZernModel( nzern,
					    *msample,
					    telgeo);
    SqGaussMod *ampmod=new SqGaussMod(telgeo,
				      *msample);
    return new ApertureMod(phasemod, 
			   ampmod,
			   wavel,
			   *msample);
  }

  ApertureMod * MkMUSTANGAp(TelGeometry * telgeo,
			    double wavel,
			    unsigned npix,
			    unsigned nzern,
			    double oversample)
  {
    return MkMgMltiAmpAp(telgeo,
			 wavel,
			 npix,
			 nzern,
			 oversample,
			 1);
  }
  
  ApertureMod * MkMgMltiAmpAp(TelGeometry * telgeo ,
			      double wavel,
			      unsigned npix,
			      unsigned nzern ,
			      double oversample,
			      size_t nobs)
  {
    boost::scoped_ptr<AstroMap::Map> msample (MkApMap(telgeo,
						      npix,
						      oversample));
    RZernModel * phasemod = new RZernModel( nzern,
					    *msample,
					    telgeo);
    TopHatAmpMod * ampmod  = new TopHatAmpMod(45.0);
    if (nobs==1)
    {
      return new ApertureMod(phasemod,
			     ampmod,
			     wavel,
			     *msample);
    }
    else
    {
      return new MultiAmp_ApModel(phasemod,
				  ampmod,
				  wavel,
				  *msample,
				  nobs);
    }

  }


  Minim::Model * ApertureMod::downcast(void)
  {
    return this;
  }


}


