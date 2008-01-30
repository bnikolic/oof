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
   *  representation. Subclasses can add observation-dependant
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

    /** Non trivial copy constructor as we may own a pointer. If
	f_other is destroyed then this object will be invalid.
    */
    FarF ( const FarF & f_other );

    /** This will raise an exception ... no way to copy */
    const FarF & operator= (const FarF & f_other);

  public:

    // ------------ Constructors/Destructors ---------------

    /** Main aim is just initalise the FFTFact using the dimensions of
      apmapsample and wevel as wavelength. Content of apmapsample is
      not used. */
    FarF ( AstroMap::Map & apmapsample, double wavel );

    ~FarF(void);

    // ------------ Member functions -----------------------

    /**
       \brief Calculate the far-field power from the supplied aperture
       amplitude and phase distributions 
    */
    virtual void Power ( const AstroMap::Map & amp, 
			 const AstroMap::Map & phase, 
			 AstroMap::Map & res);

    /**
       \brief Calculate the far field amplitude pattern of the
       aperture-plane pair (amp, phase).
    */
    virtual void Amplitude ( const AstroMap::Map & amp, const AstroMap::Map & phase, 
    			     AstroMap::Map & res);

    /**
       \brief Calculate far-field amplitude and phase patterhs
    */
    virtual void AmpPhase( const AstroMap::Map & ap_amp, 
			   const AstroMap::Map & ap_phase, 
			   AstroMap::Map & ff_amp,
			   AstroMap::Map & ff_phase);

    /**
       \brief Report the type of far-field type
       
       For debug of swig related problems
    */
    virtual const char * FFType (void) const;
    
    
    // ------ Inherited functions rom Minim::Model ---------
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );    
    

  };
  
}
#endif

