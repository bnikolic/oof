/*
  Bojan Nikolic
  $Id: obscompare.cxx,v 1.3 2005/08/15 18:43:40 bnikolic Exp $
*/

#include "obscompare.hxx"

#include <astromap.hxx>

#include "obsphasescreen.hxx"
#include "maptoresidual.hxx"
#include "aperture/aperturemod.hxx"
#include "farfield/farf.hxx"


namespace OOF {

  ObsCompare::ObsCompare( ApertureMod * aperture,
			  AstroMap::Map &apsample ):
    aperture(aperture),
    ApScratch( AstroMap::Clone(apsample)),
    ApScratchDephase( AstroMap::Clone(apsample)),
    SkyScratch(AstroMap::Clone(apsample) ),
    farf( new FarF( apsample, aperture->wavel))
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
    delete farf;
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

  unsigned   ObsCompare::nres (void)  
  {
    unsigned tot = 0;
    for ( unsigned i =0 ; i < rescalculators.size() ; ++i )
      tot += rescalculators[i]->nres() ;
    
    return tot;

  }

  void     ObsCompare::AddParams ( std::vector< Minim::DParamCtr > &pars ) 
  {
    aperture->AddParams(pars);
  }

  void  ObsCompare::residuals ( std::vector< double > & res ) 
  {
    // do this the simple minded way first....

    std::vector<double>::iterator resiter ( res.begin() );

    for (unsigned i = 0  ; i < rescalculators.size() ; ++i ) 
      {
	(*ApScratch) = ( *aperture->getphase()) ;
	phasescreens[i]->DePhase(*ApScratch) ;
	
	farf->Power( *aperture->getamp() , *ApScratch, * SkyScratch );
	
	resiter += rescalculators[i]->residuals( *SkyScratch , resiter );
      }
    
  }

}

