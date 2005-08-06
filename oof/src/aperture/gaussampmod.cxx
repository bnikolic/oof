/*
  Bojan Nikolic
  $Id: gaussampmod.cxx,v 1.2 2005/08/06 14:12:21 bnikolic Exp $

*/

#include "gaussampmod.hxx"

#include <bndebug.hxx>


#include <astromap.hxx>
#include <gaussian.hxx>
#include <mapset.hxx>


#include "../telgeo/telgeo.hxx"


namespace OOF {

  GaussAmpMod::GaussAmpMod( TelGeometry * telgeo , 
			    AstroMap::Map & msample ):
    ApMask( ENFORCE(AstroMap::Clone(msample) ) ),
    BoolApMask( (*ApMask) != 0.0 ) , 
    gfn( ENFORCE(new BNLib::GaussianDD() ))
  {
    telgeo->DishMask(*ApMask);
  }

  GaussAmpMod::~GaussAmpMod()
  {
    ENFORCE(ApMask);
    delete ApMask;
    delete gfn;
  }

  void GaussAmpMod::Calc( AstroMap::Map &m)   const
  {
    m *= 0;
    
    
    
    

  }


}


