/**
   \file aperturemod.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>

*/

#include "aperturemod.hxx"

#include <astromap.hxx>

#include "amplimod.hxx"
#include "phasemod.hxx"


namespace OOF {


  ApertureMod::ApertureMod( PhaseMod * phasemodel,
			    AmpliMod * amplimodel,
			    double wavel,
			    AstroMap::Map &mapsample):
    wavel(wavel),
    phasemodel(phasemodel),
    amplimodel(amplimodel),
    mphase( AstroMap::Clone(mapsample) ),
    mamp( AstroMap::Clone(mapsample) )
  {

  }

  ApertureMod::ApertureMod(const ApertureMod &other):
    wavel(other.wavel),
    phasemodel(other.phasemodel->clone()),
    amplimodel(other.amplimodel->clone()),
    mphase(AstroMap::Clone(*other.mphase)),
    mamp(AstroMap::Clone(*other.mamp))
  {
  }

  ApertureMod::~ApertureMod()
  {
    if ( phasemodel )
      delete phasemodel;

    if (amplimodel)
      delete amplimodel;

    delete mphase;
    delete mamp;
  }

  ApertureMod * ApertureMod::clone(void)
  {
    return new ApertureMod(*this);
  }

  const AstroMap::Map * ApertureMod::getphase(void)
  {
    // in principle could check at this point if the parameters
    // changed and avoid re-calculation.

    phasemodel->Calc(*mphase);
    
    return mphase;
  }
  
  const AstroMap::Map * ApertureMod::getPhase(size_t i)
  {
    return getphase();
  }

  const AstroMap::Map * ApertureMod::getamp(void)
  {
    
    amplimodel->Calc(*mamp);

    return mamp;
  }
  
  const AstroMap::Map * ApertureMod::getAmp(size_t i)
  {
    return getamp();
  }

  void ApertureMod::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    amplimodel->AddParams( pars);
    phasemodel->AddParams( pars);
  }


  void ApertureMod::ZeroTilt(void)
  {
    phasemodel->ZeroTilt();
  }
}


