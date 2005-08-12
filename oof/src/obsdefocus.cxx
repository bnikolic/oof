/*
  Bojan Nikolic
  $Id: obsdefocus.cxx,v 1.1 2005/08/12 18:43:15 bnikolic Exp $

*/

#include "obsdefocus.hxx"

#include <astromap.hxx>

#include "telgeo/telgeo.hxx"


namespace OOF {
  
  ObsDefocus::ObsDefocus ( TelGeometry * telgeo , 
			   AstroMap::Map  & apmapsample, 
			   double dz ):
    screen(AstroMap::Clone(apmapsample) ),
    dz(dz)
  {
    telgeo->MkDefocus( dz, *screen) ;
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


