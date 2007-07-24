/**
   \file farf.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   2004-2007
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

  FarF::FarF ( const FarF & f_other ) :
    wavel(f_other.wavel)
  {
    ffown = false;
    ff = f_other.ff;

  }
  
  const FarF & FarF::operator= (const FarF & f_other)
  {
    throw "Can not copy OOF::FarF";
    return * this;
  }

  FarF::~FarF(void)
  {
    if ( ffown)
    {
      delete ff;
    }
  }


  void FarF::Power ( const AstroMap::Map & amp, 
		     const AstroMap::Map & phase, 
		     AstroMap::Map & res)
  {
    ff->FFTAmpPh_Power(amp, phase , res);

    // now set the coordinate system!
    SetFarFCS( amp , wavel , res);

  }

  void FarF::Amplitude ( const AstroMap::Map & amp, 
			 const AstroMap::Map & phase, 
			 AstroMap::Map & res)
  {

    Power( amp, phase, res);
    res.sqrt();
  }
  
  void     FarF::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
  }

}


