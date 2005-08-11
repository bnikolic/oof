/*
  Bojan Nikolic
  $Id: farf.cxx,v 1.1 2005/08/11 21:17:41 bnikolic Exp $


*/

#include "farf.hxx"

#include <astromap.hxx>
#include <fft.hxx>

#include "farffunctions.hxx"


namespace OOF {

  FarF::FarF( AstroMap::Map & apmapsample ):
    ff( MkFFFact( apmapsample ) ),
    ffown(true)
  {
  }
  


}


