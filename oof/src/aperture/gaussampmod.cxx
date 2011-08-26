/**
   \file gaussampmod.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

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
    BoolApMask( new std::valarray<bool>( (*ApMask) != 0.0)) , 
    gfn( ENFORCE(new BNLib::GaussianDD() )),
    EffRadius( telgeo->DishEffRadius() )
  {
    telgeo->DishMask(*ApMask);
    (*BoolApMask) = (*ApMask != 0.0) ;
  }

  GaussAmpMod::GaussAmpMod(const GaussAmpMod &other):
    ApMask(other.ApMask),
    BoolApMask(other.BoolApMask),
    gfn(ENFORCE(new BNLib::GaussianDD(*other.gfn))),
    EffRadius(other.EffRadius)
  {
  }
    

  GaussAmpMod::~GaussAmpMod()
  {
    delete gfn;
  }

  GaussAmpMod *GaussAmpMod::clone(void)
  {
    return new GaussAmpMod(*this);
  }

  void GaussAmpMod::Calc( AstroMap::Map &m)   const
  {
    
    // Save the coordinate system
    AstroMap::CSSave csorig (m);

    ZernCSSetup( m , EffRadius);

    // Reset map to zero
    m *= 0;


    // Ought to normalise the coordinate system here.
    WorldSet( m , *gfn, *BoolApMask);    


    
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

    pars.push_back(Minim::DParamCtr ( & gfn->x0 ,      
				      "x0", 
				      false     ,                       
				      "Illumination offset in horizontal"
				      ));
    pars.push_back(Minim::DParamCtr ( & gfn->y0 ,      
				      "y0", 
				      false     ,                       
				      "Illumination offset in vertical"
				      ));
    
  }


}


