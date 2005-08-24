/*
  Bojan Nikolic
  $Id: minimmodel.cxx,v 1.3 2005/08/24 21:20:36 bnikolic Exp $

*/

#include "minimmodel.hxx"

namespace Minim {

  Model::Model(void) 
  {
  } 

  Model::~Model(void) 
  {
  } 

  void     Model::AddParams ( std::vector< Minim::DParamCtr > &pars )
  {

  }

  void     Model::AddParams ( std::vector< Minim::DParamCtr > &pars , std::string prefix)
  {
    
    std::vector< Minim::DParamCtr > scratchpars;
    this->AddParams( scratchpars) ;

    for (unsigned j (0) ; j < scratchpars.size() ; ++j )
      {
	ParamCtr<double> pp( scratchpars[j].p, 
			     prefix+scratchpars[j].name, 
			     scratchpars[j].dofit, 
			     scratchpars[j].comment);
	
	pars.push_back(pp);
      }
    
  }

}
