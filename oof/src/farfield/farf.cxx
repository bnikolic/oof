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
    wavel( wavel )
  {
  }

  FarF::FarF ( const FarF & f_other ) :
    ff(f_other.ff->clone()),
    wavel(f_other.wavel)
  {

  }

  FarF * FarF::clone(void)
  {
    return new FarF(*this);
  }
  
  const FarF & FarF::operator= (const FarF & f_other)
  {
    throw "Can not copy OOF::FarF";
    return * this;
  }

  FarF::~FarF(void)
  {
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

  void FarF::AmpPhase( const AstroMap::Map & ap_amp, 
		       const AstroMap::Map & ap_phase, 
		       AstroMap::Map & ff_amp,
		       AstroMap::Map & ff_phase)
  {
    ff->fftamphi(ap_amp, ap_phase , ff_amp, ff_phase);    

    SetFarFCS( ap_amp , wavel , ff_amp);    
    SetFarFCS( ap_amp , wavel , ff_phase);    

  }
  
  void     FarF::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
  }

  const char * FarF::FFType (void) const
  {
    return "FarF";
  }

}


