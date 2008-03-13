/**
   \file minimmodel.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

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
