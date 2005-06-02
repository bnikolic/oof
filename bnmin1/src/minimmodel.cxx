/*
  Bojan Nikolic
  $Id: minimmodel.cxx,v 1.1 2005/06/02 13:43:18 bnikolic Exp $

*/

#include "minimmodel.hxx"

namespace Minim {

  void     Model::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {

  }

  void     Model::AddParams ( std::vector< Minim::DParamCtr > &pars , std::string prefix)
  {
    
    std::vector< Minim::DParamCtr > scratchpars;
    this->AddParams( scratchpars) ;

    for (unsigned j (0) ; j < scratchpars.size() ; ++j )
      {
	ParamCtr<double> pp( scratchpars[j].p, prefix+scratchpars[j].name, scratchpars[j].dofit, scratchpars[j].comment);
	
	pars.push_back(pp);
      }
    
  }

}
