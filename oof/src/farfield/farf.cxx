/*
  Bojan Nikolic
  $Id: farf.cxx,v 1.4 2005/08/17 17:28:45 bnikolic Exp $


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
    
    // Assume square for the time being
    double scratchx;  double scratchy ;
    double ap_x  ;
    
    amp.cs->pxtoworld(1 , 0 ,  ap_x , scratchy);
    amp.cs->pxtoworld(0 , 0 ,  scratchx , scratchy);
    ap_x -= scratchx ;

    // this is half of the total field view on the sky.
    double halfsky = wavel / ap_x  / 2;

    MkApCS( res , halfsky );

  }
  
  void     FarF::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
  }

}


