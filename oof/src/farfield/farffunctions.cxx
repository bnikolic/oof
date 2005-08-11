/*
  Bojan Nikolic
  $Id: farffunctions.cxx,v 1.2 2005/08/11 21:17:41 bnikolic Exp $

  Far-field support functions 
*/

#include "farffunctions.hxx"

#include <astromap.hxx>

#include <fft.hxx>


namespace OOF {

  AstroMap::FFTFact * MkFFFact( AstroMap::Map & m  )
  {
    return new AstroMap::FFTFact( m.nx , m.ny ,
				  AstroMap::FFTFact::forward,
				  AstroMap::FFTFact::center );
  }

 

}


