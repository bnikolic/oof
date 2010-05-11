/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   Initial version March 2010

   \file sqgaussmod.hxx

*/

#include <astromap.hxx>
#include <coordsys.hxx>
#include <bndebug.hxx>

#include "sqgaussmod.hxx"
#include "../telgeo/telgeo.hxx"

namespace OOF {

  SqGaussMod::SqGaussMod(TelGeometry *telgeo, 
			 AstroMap::Map &msample):
    ApMask(ENFORCE(AstroMap::Clone(msample))),
    effrad2(std::pow(telgeo->DishEffRadius(),2)),
    amp(1),
    sigma(0.55),
    x0(0),
    y0(0)
  {
    telgeo->DishMask(*ApMask);
  }
  
  SqGaussMod::~SqGaussMod(void)
  {
  }

  void SqGaussMod::Calc(AstroMap::Map &m) const
  {
    double wx;
    double wy;
    for (unsigned px (0) ; px < m.nx ; ++px)
      {
	for (unsigned py(0) ; py < m.ny ; ++py )
	  {
	    if (ApMask->get(px,py) > 0)
	    {
	      m.cs->pxtoworld(px, py, 
			      wx, wy);
	      const double r2=std::pow(wx-x0,2) + std::pow(wy-y0,2);
	      const double g=std::exp(-r2/effrad2/std::pow(sigma,2));
	      const double sqg=std::sqrt(1.0-std::pow(1-g, 2.0));
	      m.get(px, py) = amp*sqg;
	    }
	    else
	    {
	      m.get(px, py) = 0;
	    }
	  }
      }
  }

  void SqGaussMod::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    pars.push_back(Minim::DParamCtr(&amp,      
				    "amp", 
				    true,                       
				    "Illumination amplitude "
				    ));
    pars.push_back(Minim::DParamCtr(&sigma ,      
				    "sigma", 
				    false,                       
				    "Illumination taper"
				    ));
    pars.push_back(Minim::DParamCtr (&x0 ,      
				     "x0", 
				     false     ,                       
				     "Illumination offset in horizontal"
				     ));
    pars.push_back(Minim::DParamCtr (&y0 ,      
				     "y0", 
				     false     ,                       
				     "Illumination offset in vertical"
				     ));
  }

}
