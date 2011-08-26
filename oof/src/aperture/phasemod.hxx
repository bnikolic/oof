/**
  \file phasemod.hxx
  Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

  Phase model
*/
#ifndef __OOF_PHASEMOD_HXX__
#define __OOF_PHASEMOD_HXX__

#include <minimmodel.hxx>

// Forwards
namespace AstroMap {
  
  class Map;

}

namespace OOF {


  /** \brief A model for the aperture plane phase of the electric field
   */
  class PhaseMod : public Minim::Model  {

  public:

    // ------ Constructor / Destructor ---------------
    virtual ~PhaseMod(void);

    virtual PhaseMod *clone(void) =0;

    // ------ Member functions ----------------------------

    /** \brief Calculate the phase model
	
    \param m The calculate phase is stored in this map

     */
    virtual void Calc( AstroMap::Map &m) const = 0 ;

    /*! Remove the tilt from the aperture */
    virtual void ZeroTilt(void) =0;
    
    // ------ Inherited functions rom Minim::Model ---------

    /*! Don't know yet how this will be parameterised */
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) =0;

    Minim::Model * downcast(void);

  };


}

#endif
