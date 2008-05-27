/**
   \file minimmodel.cxx
   Bojan Nikolic <bojan@bnikolic.co.uk>

*/

#include "minimmodel.hxx"
#include <cmath>

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

  void     Model::AddParams ( std::vector< Minim::DParamCtr > &pars , 
			      std::string &prefix)
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
  
  double Minimisable::lLikely(void) const
  {
    std::vector<double> res(nres());
    residuals(res);
    
    double ss=0;
    for (size_t i=0; i < res.size() ; ++i)
      ss += std::pow(res[i],2);
    return ss;
  }

}
