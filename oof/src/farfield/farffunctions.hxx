/*
  Bojan Nikolic
  $Id: farffunctions.hxx,v 1.2 2005/08/11 21:17:41 bnikolic Exp $

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


}

#endif
