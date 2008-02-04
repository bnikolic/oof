/**
   \file amplimod.hxx 
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

  Aperture model
*/
#ifndef __OOF_AMPLIMOD_HXX__
#define __OOF_AMPLIMOD_HXX__

#include <minimmodel.hxx>

namespace AstroMap {

  class Map ;

}

namespace OOF {

  /** \brief A model for the aperture plane illumination (or amplitude)

   */
    class AmpliMod : public Minim::Model  {

    public:

      // ------ Member functions ----------------------------
    
      virtual void Calc( AstroMap::Map &m) const = 0 ;

      /*! This is only really for the python binding to work */
      Minim::Model * downcast(void);
      
      // ------ Inherited functions rom Minim::Model ---------
      
      virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) = 0;
      
    };


}

#endif
