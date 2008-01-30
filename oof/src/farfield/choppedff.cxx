/*! 
  Bojan Nikolic
  $Id: choppedff.cxx,v 1.3 2005/08/28 04:26:25 bnikolic Exp $
*/

#include "choppedff.hxx"

#include <astromap.hxx>

#include <zernikepoly.hxx>
#include <mapset.hxx>

namespace OOF {

  ChoppedFF::ChoppedFF( AstroMap::Map & apmapsample, double wavel ):
    FarF( apmapsample, wavel),
    vaptilt(AstroMap::Clone(apmapsample)),
    haptilt(AstroMap::Clone(apmapsample)),
    phasescratch(AstroMap::Clone(apmapsample)),
    skyscratch  (AstroMap::Clone(apmapsample)),
    vchop (0 ),
    hchop (30 * 5e-6 ),  // a random sensible value to avoid very
                         // confusing results,
    beamgainf(1.0)
    
  {
    BNLib::ZernPoly zvertical   ( 1, -1);    
    BNLib::ZernPoly zhorizontal ( 1, 1);    

    AstroMap::WorldSet( *vaptilt , zvertical);
    AstroMap::WorldSet( *haptilt , zhorizontal);

    (*vaptilt) *= 2 * M_PI / wavel;
    (*haptilt) *= 2 * M_PI / wavel;
  }

  ChoppedFF::~ChoppedFF()
  {
    delete ( vaptilt);
    delete ( haptilt);

    delete (phasescratch);
    delete (skyscratch);
  }

  void ChoppedFF::Power ( const AstroMap::Map & amp, 
			  const AstroMap::Map & phase, 
			  AstroMap::Map & res) 
  {

    // Want to divide one beam and multiply the other beam with same
    // factor to make total power uncorrelated with beamgainf.

    const double mfact= sqrt(beamgainf);

    (*phasescratch) = phase;
    
    if ( vchop != 0.0 )
      (*phasescratch) += (*vaptilt) * vchop /2 ;

    if ( hchop != 0.0 )
      (*phasescratch) += (*haptilt) * hchop /2 ;

    FarF::Power( amp, *phasescratch , res);
    
    res /= mfact;

    (*phasescratch) = phase;
    
    if ( vchop != 0.0 )
      (*phasescratch) -= (*vaptilt) * vchop /2 ;

    if ( hchop != 0.0 )
      (*phasescratch) -= (*haptilt) * hchop /2 ;

    FarF::Power( amp, *phasescratch , *skyscratch);    

    res -= (*skyscratch) * mfact;

  }

  void ChoppedFF::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    
    pars.push_back(Minim::DParamCtr ( & hchop ,      
				      "hchop", 
				      false     ,                       
				      "Horizontal chop magnitude"
				      ));

    pars.push_back(Minim::DParamCtr ( & vchop ,      
				      "vchop", 
				      false     ,                       
				      "Vertical chop magnitude"
				      ));

    pars.push_back(Minim::DParamCtr ( & beamgainf ,      
				      "beamgainf", 
				      false     ,                       
				      "Difference in gains of two beams"
				      ));

  }

  const char * ChoppedFF::FFType (void) const
  {
    return "ChoppedFF";
  }


}


