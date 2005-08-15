/*
  Bojan Nikolic
  $Id: farf.hxx,v 1.3 2005/08/15 18:43:40 bnikolic Exp $

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

    /*! This will do the actuall far-field calculation
     */
    AstroMap::FFTFact * ff;
    
    /*! If this is true then this class will delete ff;
     */
    bool   ffown;

    /*! The wavelength of radiation ( allows correct setting of
     *  coordinate systems on the results maps */
    const double wavel;

  public:

    // ------------ Constructors/Destructors ---------------

    /*! Construct the FFTFactory using the sample map */
    FarF ( AstroMap::Map & apmapsample, double wavel );


    // ------------ Member functions -----------------------

    /*! Calculate the far-field power from the supplied aperture
      amplitude and phase distributions */
    void Power ( const AstroMap::Map & amp, AstroMap::Map & phase, AstroMap::Map & res);

    
    

  };
  
}
#endif

