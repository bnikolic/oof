/*
  Bojan Nikolic
  $Id: farffunctions.hxx,v 1.3 2005/08/18 04:57:43 bnikolic Exp $

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
