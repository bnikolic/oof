/*
  Bojan Nikolic
  $Id: gaussampmod.hxx,v 1.3 2005/08/09 01:09:19 bnikolic Exp $

  Gaussian amplitude model
*/
#ifndef __OOF_GAUSSAMPMOD_HXX__
#define __OOF_GAUSSAMPMOD_HXX__

#include "amplimod.hxx"
#include <valarray>


namespace AstroMap {
  class Map;
}

namespace BNLib {
  class GaussianDD;
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
    
    /*! This is similar to ApMask but is a bool valarray */
    std::valarray<bool> BoolApMask;

    /*! Store here the actuall gaussian used */
    BNLib::GaussianDD * gfn;

    /*! Effective radius to use when evaluating the gaussian a so dish
      edge is at unit disance */
    double EffRadius;
    
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
