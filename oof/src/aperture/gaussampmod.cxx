/*
  Bojan Nikolic
  $Id: gaussampmod.cxx,v 1.7 2006/02/16 00:23:12 bnikolic Exp $

*/

#include "gaussampmod.hxx"

#include <bndebug.hxx>


#include <astromap.hxx>
#include <gaussian.hxx>
#include <mapset.hxx>
#include <cssave.hxx>


#include "../telgeo/telgeo.hxx"

#include  "zernmodel.hxx"


namespace OOF {

  GaussAmpMod::GaussAmpMod( TelGeometry * telgeo , 
			    AstroMap::Map & msample ):
    ApMask( ENFORCE(AstroMap::Clone(msample) ) ),
    BoolApMask( (*ApMask) != 0.0 ) , 
    gfn( ENFORCE(new BNLib::GaussianDD() )),
    EffRadius( telgeo->DishEffRadius() )
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
    
    // Save the coordinate system
    AstroMap::CSSave csorig (m);

    ZernCSSetup( m , EffRadius);

    // Reset map to zero
    m *= 0;


    // Ought to normalise the coordinate system here.
    WorldSet( m , *gfn, BoolApMask );    


    
  }

  void GaussAmpMod::SetSigma(double x)
  {
    gfn->sigma=x;
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
				      false     ,                       
				      "Illumination taper"
				      ));
    
  }


}


