/**
   \file farffunctions.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>

   Far-field support functions 
*/

#ifndef _OOF_FARFFINCTIONS_HXX__
#define _OOF_FARFFINCTIONS_HXX__

namespace AstroMap {
  class Map;
  class FFTFact ;
}


namespace OOF {

  /*! Create an FFT factory suitable for transforming aperture field
    distributions to far field distributions */
  AstroMap::FFTFact * MkFFFact( AstroMap::Map & apmapsample  );

  /*! Set the correct coordinate system on  farfield map */
  void SetFarFCS(const AstroMap::Map & apmap, double wavel,
		 AstroMap::Map & res );


}

#endif
