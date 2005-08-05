/*!
  Bojan Nikolic
  $Id: amplimod.hxx,v 1.2 2005/08/05 22:01:11 bnikolic Exp $

  Aperture model
*/
#ifndef __OOF_AMPLIMOD_HXX__
#define __OOF_AMPLIMOD_HXX__

#include <minimmodel.hxx>

namespace AstroMap {

  class Map ;

}

namespace OOF {

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
