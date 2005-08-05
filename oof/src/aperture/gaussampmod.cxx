/*
  Bojan Nikolic
  $Id: gaussampmod.cxx,v 1.1 2005/08/05 22:01:11 bnikolic Exp $

*/

#include "gaussampmod.hxx"

#include <bndebug.hxx>
#include <astromap.hxx>

#include "../telgeo/telgeo.hxx"


namespace OOF {

  GaussAmpMod::GaussAmpMod( TelGeometry * telgeo , 
			    AstroMap::Map & msample ):
    ApMask( ENFORCE(AstroMap::Clone(msample) ) )
  {
    telgeo->DishMask(*ApMask);
  }

  GaussAmpMod::~GaussAmpMod()
  {
    ENFORCE(ApMask);
    delete ApMask;
  }

  


}


