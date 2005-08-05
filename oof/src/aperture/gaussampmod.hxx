/*
  Bojan Nikolic
  $Id: gaussampmod.hxx,v 1.1 2005/08/05 22:01:11 bnikolic Exp $

  Gaussian amplitude model
*/
#ifndef __OOF_GAUSSAMPMOD_HXX__
#define __OOF_GAUSSAMPMOD_HXX__

#include "amplimod.hxx"

namespace AstroMap {
  class Map;
}

namespace OOF {

  class TelGeometry;

  /*!
   * Represents an illumination model with a gaussian taper.
   *
   */
  class GaussAmpMod : public AmpliMod {

    /*! This defines the physical extent of the aperture */

    AstroMap::Map * ApMask;
    
  public:
    
    // ----- Constructor & Destructor   ------------
    
    GaussAmpMod( TelGeometry * telgeo , AstroMap::Map & msample );
    
    virtual ~GaussAmpMod();

    // ----- Inherited from AmpliMod  ------------------------------

    virtual void Calc( AstroMap::Map &m) const  ;
      
    // ------ Inherited functions rom Minim::Model ---------
      
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;


  };
  



}

#endif
