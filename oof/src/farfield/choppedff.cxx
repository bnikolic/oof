/*! 
  Bojan Nikolic
  $Id: choppedff.cxx,v 1.1 2005/08/17 19:28:56 bnikolic Exp $
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
    hchop (30 * 5e-6 )  // a random sensible value to avoid very
			// confusing results
  {
    BNLib::ZernPoly zvertical   ( 1, -1);    
    BNLib::ZernPoly zhorizontal ( 1, 1);    

    AstroMap::WorldSet( *vaptilt , zvertical);
    AstroMap::WorldSet( *haptilt , zhorizontal);

    (*vaptilt) *= 4 * M_PI / wavel;
    (*haptilt) *= 4 * M_PI / wavel;
  }

  ChoppedFF::~ChoppedFF()
  {
    delete ( vaptilt);
    delete ( haptilt);

    delete (phasescratch);
    delete (skyscratch);
  }

  void ChoppedFF::Power ( const AstroMap::Map & amp, AstroMap::Map & phase, 
			  AstroMap::Map & res) 
  {

    (*phasescratch) = phase;
    
    if ( vchop != 0.0 )
      (*phasescratch) += (*vaptilt) * vchop /2 ;

    if ( hchop != 0.0 )
      (*phasescratch) += (*haptilt) * hchop /2 ;

    FarF::Power( amp, *phasescratch , res);

    (*phasescratch) = phase;
    
    if ( vchop != 0.0 )
      (*phasescratch) -= (*vaptilt) * vchop /2 ;

    if ( hchop != 0.0 )
      (*phasescratch) -= (*haptilt) * hchop /2 ;

    FarF::Power( amp, *phasescratch , *skyscratch);    

    res -= *skyscratch;

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

  }


}


