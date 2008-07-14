/**
   \file obscompare.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>

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

  ObsCompare::ObsCompare( ApertureMod * aperture,
	      AstroMap::Map &apsample,
	      FarF * customff):
    aperture(aperture),
    ApScratch( AstroMap::Clone(apsample)),
    ApScratchDephase( AstroMap::Clone(apsample)),
    SkyScratch(AstroMap::Clone(apsample) ),
    farf( customff)
  {
  }
	

  ObsCompare::~ObsCompare(void)
  {

    delete aperture;
    
    delete ApScratch; 
    delete ApScratchDephase;
    delete SkyScratch;

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

  unsigned   ObsCompare::nres (void)   const
  {
    unsigned tot = 0;
    for ( unsigned i =0 ; i < rescalculators.size() ; ++i )
      tot += rescalculators[i]->nres() ;
    
    return tot;

  }

  void     ObsCompare::AddParams ( std::vector< Minim::DParamCtr > &pars ) 
  {
    aperture->AddParams(pars);
    farf->AddParams(pars);
  }

  void ObsCompare::Beam (unsigned i,
			 AstroMap::Map & res)
  {
    (*ApScratch) = ( *aperture->getPhase(i)) ;
    phasescreens[i]->DePhase(*ApScratch) ;
    
    farf->Power(*aperture->getAmp(i), 
		*ApScratch,
		res);
  }

  AstroMap::Map *  ObsCompare::Beam (unsigned i  )
  {

    AstroMap::Map * res = AstroMap::Clone(*SkyScratch) ;
    Beam(i, * res );

    return res;

  }

  AstroMap::Map *  ObsCompare::Beam (void  )
  {
    AstroMap::Map * res = AstroMap::Clone(*SkyScratch) ;

    (*ApScratch) = ( *aperture->getphase()) ;
    farf->Power( *aperture->getamp() , *ApScratch, * res );

    return res;
  }

  void  ObsCompare::residuals ( std::vector< double > & res ) const
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

  ApertureMod * ObsCompare::GetAperture(void)
  {
    return aperture;
  }
}

