/*
  Bojan Nikolic
  $Id: gaussampmod.cxx,v 1.3 2005/08/06 14:46:38 bnikolic Exp $

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
    BoolApMask = (*ApMask != 0.0) ;
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
    
    WorldSet( m , *gfn, BoolApMask );    
    //WorldSet( m , *gfn );    
    
  }

  void     GaussAmpMod::AddParams ( std::vector< Minim::DParamCtr > &pars ) 
  {

    pars.push_back(Minim::DParamCtr ( & gfn->amp ,      
				      "amp", 
				      true     ,                       
				      "Illumination amplitude "
				      ));

    pars.push_back(Minim::DParamCtr ( & gfn->sigma ,      
				      "sigma", 
				      true     ,                       
				      "Illumination taper"
				      ));
    
  }


}


