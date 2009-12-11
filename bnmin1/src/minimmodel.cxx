/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2003

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file minimmodel.cxx

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

    // Account for the (2 sigma^2) at the bottom of likelihood....
    return 0.5*ss;
  }

  size_t nPars(Model &m)
  {
    std::vector<Minim::DParamCtr> pars;
    m.AddParams(pars);
    return pars.size();
  }

}
