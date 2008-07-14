/**
   \file aperturemod.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

   Aperture model
*/
#ifndef __OOF_APERTUREMOD_HXX__
#define __OOF_APERTUREMOD_HXX__

#include <minimmodel.hxx>

#include <astromap_fwd.hxx>


namespace OOF {

  // Forwards

  class PhaseMod;
  class AmpliMod;

  /** \brief Represent the aperture field distribution
      
   */
  class ApertureMod : 
    public Minim::Model  
  {

  public:
    /** \brief The wavelength of the EM field

     In the same units as the coordinate system of the maps in order
     for the FFT coordinate system to work OK
    */ 
    const double wavel;

  private:

    /*! 
     * Pointer to the current phase model. Take ownership.
     */
    PhaseMod * phasemodel;

    /*! 
     * Pointer to the current amplitude model. Take ownership.
     */
    AmpliMod * amplimodel;

    /*!
     * Scratch to keep the aperture phase in 
     */
    AstroMap::Map * mphase;

    /*!
     * Scratch to keep the aperture amplitude in 
     */
    AstroMap::Map * mamp;

    /// Should not be able to copy
    ApertureMod( const ApertureMod & a): wavel(0) {};
    
    /// Should not be able to assign
    const ApertureMod & operator= (const ApertureMod &a)
    {
      return * this;
    }
    

  public:

    // ------ Constructors & Destructors   -----------------

    /** This class takes ownership of phasemodel and amplimodel.
     */
    ApertureMod( PhaseMod * phasemodel,
		 AmpliMod * amplimodel,
		 double wavel,
		 AstroMap::Map &mapsample);


    virtual ~ApertureMod();

    // ------ Member Functions  ----------------------------

    /** \brief Recalculate and return pointer to the phase map.
     */
    const AstroMap::Map * getphase(void);

    /** \brief Recalculate and return pointer to amplitude map

    */
    const AstroMap::Map * getamp(void);

    /** \brief Remove the tilt terms from the aperture model
     */
    void ZeroTilt(void);

    // ------ Inherited functions rom Minim::Model ---------
    
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );

    //  ------ Utility functons to help with python
    
    /// Cast to Minim::Model (python helper)
    Minim::Model * downcast(void);
    


  };



}

#endif
