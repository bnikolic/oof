/**
   \file farf.hxx
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   A class to transforms from the aperture plane into the far field.
*/
#ifndef _OOF_FARF_HXX__
#define _OOF_FARF_HXX__

#include <minimmodel.hxx>

// Forwards
namespace AstroMap {
  class Map;
  class FFTFact ;
}

namespace OOF {

  /*! Calculates the far field from an aperture
   *  representation. Subclasses can add observation-depemdant
   *  features like chopping or convolution for a known source extent.
   */
  class FarF : public Minim::Model {

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
    virtual void Power ( const AstroMap::Map & amp, const AstroMap::Map & phase, 
			 AstroMap::Map & res);

    /**
       Calculate the far field amplitude pattern of the aperture-plane
       pair (amp, phase).
    */
    virtual void Amplitude ( const AstroMap::Map & amp, const AstroMap::Map & phase, 
    			     AstroMap::Map & res);

    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );    
    

  };
  
}
#endif

