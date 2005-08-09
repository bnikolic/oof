/*!
  Bojan Nikolic
  $Id: aperturemod.cxx,v 1.2 2005/08/09 02:15:24 bnikolic Exp $

*/

#include "aperturemod.hxx"

#include "amplimod.hxx"
#include "phasemod.hxx"


namespace OOF {

  ApertureMod::ApertureMod( double wavel):
    wavel(wavel),
    phasemodel(NULL),
    amplimodel(NULL)
  {
    
  }

  ApertureMod::~ApertureMod()
  {
    if ( phasemodel )
      delete phasemodel;

    if (amplimodel)
      delete amplimodel;

  }

  void ApertureMod::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {
    amplimodel->AddParams( pars);
    phasemodel->AddParams( pars);
  }


}


