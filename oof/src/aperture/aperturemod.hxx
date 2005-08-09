/*!
  Bojan Nikolic
  $Id: aperturemod.hxx,v 1.2 2005/08/09 02:15:24 bnikolic Exp $

  Aperture model
*/
#ifndef __OOF_APERTUREMOD_HXX__
#define __OOF_APERTUREMOD_HXX__

#include <minimmodel.hxx>

namespace OOF {

  // Forwards

  class PhaseMod;
  class AmpliMod;

  /*! 
   *  A class to represent the aperture field distribution.
   */
  class ApertureMod : public Minim::Model  {

    /*! The wavelength of the EM field ... in the same units as the
     * coordinate system of the maps in order for the FFT coordinate
     * system to work OK*/ 
    double wavel;

    /*! 
     * Pointer to the current phase model. Take ownership.
     */
    PhaseMod * phasemodel;

    /*! 
     * Pointer to the current amplitude model. Take ownership.
     */
    AmpliMod * amplimodel;

  public:

    // ------ Constructors & Destructors   -----------------
    
    ApertureMod( double wavel);

    virtual ~ApertureMod();

    // ------ Member Functions  ----------------------------
    
    

    // ------ Inherited functions rom Minim::Model ---------
    
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );
    


  };



}

#endif
