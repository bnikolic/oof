/*!
  Bojan Nikolic
  $Id: amplimod.hxx,v 1.1 2005/08/05 13:01:26 bnikolic Exp $

  Aperture model
*/
#ifndef __OOF_AMPLIMOD_HXX__
#define __OOF_AMPLIMOD_HXX__

#include <minimmodel.hxx>

namespace OOF {

    class AmpliMod : public Minim::Model  {

    public:

      // ------ Inherited functions rom Minim::Model ---------
      
      virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars );
      
    };


}

#endif
