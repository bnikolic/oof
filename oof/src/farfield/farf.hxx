/*
  Bojan Nikolic
  $Id: farf.hxx,v 1.1 2005/08/11 21:17:41 bnikolic Exp $

  A class that transforms from the aperture plane to the far field.
*/
#ifndef _OOF_FARF_HXX__
#define _OOF_FARF_HXX__

// Forwards
namespace AstroMap {
  class Map;
  class FFTFact ;
}

namespace OOF {

  /*! Calculates the far field from an aperture representation */

  class FarF {

    // This will do the actuall far-field calculation
    AstroMap::FFTFact * ff;
    
    // If this is true then this class will delete ff;
    bool   ffown;

  public:

    /* Construct the FFTFactory using the sample map */
    FarF ( AstroMap::Map & apmapsample );
    

  };
  
}
#endif

