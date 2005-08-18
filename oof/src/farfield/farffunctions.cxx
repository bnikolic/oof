/*
  Bojan Nikolic
  $Id: farffunctions.cxx,v 1.3 2005/08/18 04:57:43 bnikolic Exp $

  Far-field support functions 
*/

#include "farffunctions.hxx"

#include <astromap.hxx>
#include <coordsys.hxx>
#include <csops.hxx>

#include <fft.hxx>


namespace OOF {

  AstroMap::FFTFact * MkFFFact( AstroMap::Map & m  )
  {
    return new AstroMap::FFTFact( m.nx , m.ny ,
				  AstroMap::FFTFact::forward,
				  AstroMap::FFTFact::center );
  }


  void SetFarFCS(const AstroMap::Map & apmap, double wavel, AstroMap::Map & res )
  {
    // Assume square for the time being
    double scratchx;  double scratchy ;
    double ap_x  ;
    
    apmap.cs->pxtoworld(1 , 0 ,  ap_x , scratchy);
    apmap.cs->pxtoworld(0 , 0 ,  scratchx , scratchy);
    ap_x -= scratchx ;

    // this is half of the total field view on the sky.
    double halfsky = wavel / ap_x  / 2;

    MkApCS( res , halfsky );

  }

}


