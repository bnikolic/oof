/*
  Bojan Nikolic
  $Id: obsdefocus.cxx,v 1.2 2005/08/17 15:57:16 bnikolic Exp $

*/

#include "obsdefocus.hxx"

#include <astromap.hxx>

#include "telgeo/telgeo.hxx"


namespace OOF {
  
  ObsDefocus::ObsDefocus ( TelGeometry * telgeo , 
			   AstroMap::Map  & apmapsample, 
			   double dz,
			   double wavel):
    screen(AstroMap::Clone(apmapsample) ),
    dz(dz)
  {
    // this is in terms of geometric path
    telgeo->MkDefocus( dz, *screen) ;

    // convert to radians
    (*screen) *= 2 * M_PI /  wavel;
    
  }

  ObsDefocus::~ObsDefocus()
  {
    delete screen;
  }

  void ObsDefocus::DePhase( AstroMap::Map  & res) 
  {
    // Could try doing a masked addition here ... may save time!
    res += *screen;
  }


}


