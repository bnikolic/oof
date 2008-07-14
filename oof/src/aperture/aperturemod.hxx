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

    /** \brief Recalculate and return pointer to the phase map
	
	\note see getPhase()
     */
    virtual const AstroMap::Map * getphase(void);

    /** \brief Return the i-th aperture phase model
	
    There is normally only one model for the aperture, corresponding
    to the assumption that telescope system remains unchanged between
    the beam map observations at various foucus settings.  In this
    case this functions should return the same aperture
    phase/amplitude regdless of the value of parameter i. (Ie., it
    returns getphase()).

    However, sometimes this is not a good assumption, or potential
    pre-processing problems need to be investigated.  By providing a
    different model for each focus seting this can be taken into
    account. To do this override these functions in derived classes.
    */
    virtual const AstroMap::Map * getPhase(size_t i);

    /** \brief Recalculate and return pointer to amplitude map

    */
    virtual const AstroMap::Map * getamp(void);

    /** \brief Return the i-th aperture amplitude model

    \note see getPhase()     
     */
    virtual const AstroMap::Map * getAmp(size_t i);

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
