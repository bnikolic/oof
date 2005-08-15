/*!
  Bojan Nikolic
  $Id: aperturemod.cxx,v 1.3 2005/08/15 18:43:40 bnikolic Exp $

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

  ApertureMod::~ApertureMod()
  {
    if ( phasemodel )
      delete phasemodel;

    if (amplimodel)
      delete amplimodel;

    delete mphase;
    delete mamp;


  }

  const AstroMap::Map * ApertureMod::getphase(void)
  {
    // in principle could check at this point if the parameters
    // changed and avoid re-calculation.

    phasemodel->Calc(*mphase);
    
    return mphase;
  }

  const AstroMap::Map * ApertureMod::getamp(void)
  {
    
    amplimodel->Calc(*mamp);

    return mamp;
  }

  void ApertureMod::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    amplimodel->AddParams( pars);
    phasemodel->AddParams( pars);
  }


}


