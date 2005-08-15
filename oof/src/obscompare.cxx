/*
  Bojan Nikolic
  $Id: obscompare.cxx,v 1.2 2005/08/15 15:45:44 bnikolic Exp $
*/

#include "obscompare.hxx"

#include <astromap.hxx>

#include "obsphasescreen.hxx"
#include "maptoresidual.hxx"
#include "aperture/aperturemod.hxx"


namespace OOF {

  ObsCompare::ObsCompare( ApertureMod * aperture,
			  AstroMap::Map &apsample ):
    aperture(aperture),
    ApScratch( AstroMap::Clone(apsample)),
    ApScratchDephase( AstroMap::Clone(apsample))
  {
  }

  ObsCompare::~ObsCompare(void)
  {

    delete aperture;
    
    delete ApScratch; 
    delete ApScratchDephase;

    for (size_t i =0 ; i < phasescreens.size() ; ++i )
      {
	delete phasescreens[i];
	delete rescalculators[i];
      }
  }

  
  void ObsCompare::AddObs( MapToResidual * rc , ObsPhaseScreen * ps)
  {
    rescalculators.push_back(rc);
    phasescreens.push_back(ps);
  }

  unsigned ObsCompare::NObs(void)
  {
    return phasescreens.size();
  }


}

