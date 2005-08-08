/*
  Bojan Nikolic
  $Id: gaussampmod.cxx,v 1.4 2005/08/09 00:54:35 bnikolic Exp $

*/

#include "gaussampmod.hxx"

#include <bndebug.hxx>


#include <astromap.hxx>
#include <gaussian.hxx>
#include <mapset.hxx>
#include <cssave.hxx>


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

    // Ought to normalise the coordinate system here.
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


