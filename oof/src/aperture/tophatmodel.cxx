/**
   \file tophatmodel.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

*/

#include "tophatmodel.hxx"

// From BNLib
#include <tophat.hxx>
// From AstroMap
#include <astromap.hxx>
#include <mapset.hxx>

namespace OOF {

  TopHatAmpMod::TopHatAmpMod ( double R):
    R(R),
    amp(1.0)
  {
  }

  void TopHatAmpMod::Calc( AstroMap::Map &m) const  
  {
    BNLib::TopHatDD th;
    th.radius=R;
    
    WorldSet( m , th);
    
    m *= amp;

  }

  void TopHatAmpMod::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    pars.push_back(Minim::DParamCtr ( & amp ,      
				      "amp", 
				      true     ,                       
				      "Illumination amplitude "
				      ));
    
    pars.push_back(Minim::DParamCtr ( & R ,      
				      "R", 
				      false     ,                       
				      "Radius of tophat illum "
				      ));

  }


}



