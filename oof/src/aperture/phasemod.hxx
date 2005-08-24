/*!
  Bojan Nikolic
  $Id: phasemod.hxx,v 1.5 2005/08/24 21:21:14 bnikolic Exp $

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

  
  class PhaseMod : public Minim::Model  {

  public:

    // ------ Constructor / Destructor ---------------
    virtual ~PhaseMod(void);

    // ------ Member functions ----------------------------
    
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
