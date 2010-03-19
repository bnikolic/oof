/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   Initial version March 2010, after code with orgini in 2005

   \file planetff.cxx
   
*/
#include <astromap.hxx>
#include <tophat.hxx>
#include <mapset.hxx>
#include <convolve.hxx>

#include "planetff.hxx"

namespace OOF {

  PlanetFF::PlanetFF(double radius,
		     AstroMap::Map &apmapsample,
		     double wavel):
    FarF(apmapsample,
	 wavel),
    radius(radius)
  {
  }

  PlanetFF::~PlanetFF()
  {
  }

  AstroMap::Map *PlanetFF::mkModel(const AstroMap::Map &ffsample,
				   double radius)
  {
    AstroMap::Map *res=AstroMap::Clone(ffsample);
    
    BNLib::TopHatDD th;
    th.radius=radius;

    AstroMap::WorldSet(*res, 
		       th);
    return res;
  }

  void PlanetFF::Power(const AstroMap::Map &amp, 
		       const AstroMap::Map &phase, 
		       AstroMap::Map &res)
  {
    if (not planetm)
      planetm.reset(mkModel(res, radius));
    
    FarF::Power(amp, 
		phase, 
		res);

    FFTConvolve(res, 
		*planetm,
		res);

  }

  const char * PlanetFF::FFType (void) const
  {
    return "PlanetFF";
  }

  void  PlanetFF::AddParams(std::vector<Minim::DParamCtr> &pars)
  {
    // No parameters
  }

  

}



