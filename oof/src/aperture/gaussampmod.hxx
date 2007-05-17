/**
   \file gaussampmod.hxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   2004-2007
   
   The gaussian model for aperture plane amplitude distribution. Note
   that this describes the distribution of the amplitude of the
   electric field -- therefore to needs to converted to power (i.e.,
   squared) to calculate "dB" values. 

   For example if sigma=0.3 then this is equivalent to 14dB
   taper. (since \f$\log_{10}(e)=0.43\f$ and \f$\log_{10}(e)/0.3
   \times 10=14.47\f$)

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
   * Represents an illumination model with a gaussian taper. The taper
   * is controlled with the sigma parameter so that amplitude at dish
   * edge is: exp( -1.0 / ( 2* sigma) ) the value at centre of the
   * illumination.
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

    // ----- Add simplified access to the Gaussian parameers
    
    void SetSigma(double x);

    // ----- Inherited from AmpliMod  ------------------------------

    virtual void Calc( AstroMap::Map &m) const  ;
      
    // ------ Inherited functions rom Minim::Model ---------
      
    virtual    void     AddParams ( std::vector< Minim::DParamCtr > &pars ) ;



  };
  



}

#endif
