/**
   \file tophatmodel.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>
   

*/
#ifndef __OOF__TOPHATMOD_HXX__
#define __OOF__TOPHATMOD_HXX__

#include "amplimod.hxx"

namespace OOF {

  /** \brief Model the aperture plane amplitude by a top hat function.

      An approximation for receivers with a cold stop in the optics
      such as the MUSTANG on the GBT.

      Note that the parameter "R" can easily be fitted-for because of
      the digital nature of algorithm means that numerical
      differential wrt R can not be calculated.
   */
  class TopHatAmpMod : 
    public AmpliMod {

    /** \brief Radius of the top hat
     */
    double R;

    /** \brief Amplitude of the illumination
     */
    double amp;
    
  public:
    
    // -------- Construction & Destruction -------
    /**
       \param R radius of the top hat
     */
    TopHatAmpMod ( double R);

    TopHatAmpMod (const TopHatAmpMod &other);

    TopHatAmpMod *clone(void);

    // -------- Inherited from AmpliMod ----------
    
    virtual void Calc( AstroMap::Map &m) const  ;
    virtual void AddParams ( std::vector< Minim::DParamCtr > &pars );
    

  };


}

#endif

