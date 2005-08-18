/*
  Bojan Nikolic
  $Id: farf.cxx,v 1.5 2005/08/18 04:57:43 bnikolic Exp $


*/

#include "farf.hxx"

#include <astromap.hxx>
#include <coordsys.hxx>
#include <csops.hxx>
#include <fft.hxx>

#include "farffunctions.hxx"


namespace OOF {

  FarF::FarF( AstroMap::Map & apmapsample, double wavel  ):
    ff( MkFFFact( apmapsample ) ),
    ffown(true),
    wavel( wavel )
  {
  }


  void FarF::Power ( const AstroMap::Map & amp, AstroMap::Map & phase, 
		     AstroMap::Map & res)
  {
    ff->FFTAmpPh_Power(amp, phase , res);

    // now set the coordinate system!
    SetFarFCS( amp , wavel , res);

  }
  
  void     FarF::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
  }

}


