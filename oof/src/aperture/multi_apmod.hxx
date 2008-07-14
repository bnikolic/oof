/**
   \file multi_apmod.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
*/
#ifndef __OOF_MULTIAPMOD_HXX__
#define __OOF_MULTIAPMOD_HXX__

#include <vector>
#include <boost/scoped_ptr.hpp>

#include "aperturemod.hxx"

namespace OOF {

  /** \brief Aperture model where the amplitude might be different
      between observations
      
      This class defines additional parameters amp_r1, etc., which
      control the ratio of amplitude of the first observation to other
      observations.
  */
  class MultiAmp_ApModel :
    public ApertureMod
  {
    /// Amplitude ratios are stored here
    std::vector<double> amp_r;

    /**
       Scratch to keep the aperture amplitude in 
    */
    boost::scoped_ptr<AstroMap::Map> mamp;
    
  public:

    // ----------------- Construction/Destruction -----------------
    
    /**
       \param phasemodel,amplimodel,wavel,mapsample see
       ApertureMod::ApertureMod
       
       \param nobs Number of observations

     */
    MultiAmp_ApModel(PhaseMod * phasemodel,
		     AmpliMod * amplimodel,
		     double wavel,
		     AstroMap::Map &mapsample,
		     size_t nobs);    

    virtual ~MultiAmp_ApModel();
    

    // ----------------- Public Interface -------------------------

    /** \brief Return the i-th amplitude ratio
     */
    double getAR(size_t i) const 
    { return amp_r[i]; }
    

    // ---------- Inherited from ApertureMod ----------------------
    virtual const AstroMap::Map * getAmp(size_t i);
    // ---------- Inherited functions rom Minim::Model ------------
    virtual void AddParams(std::vector< Minim::DParamCtr > &pars);

  };

}
#endif
