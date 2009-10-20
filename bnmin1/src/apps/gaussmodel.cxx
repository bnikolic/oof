/**
g   \file gaussmodel.cpp
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include <boost/format.hpp>

#include "gaussmodel.hxx"

namespace Minim {
  
  void GaussObs::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    using namespace Minim;
    for (size_t i=0; i<p.size(); ++i)
    {
      ParamCtr<double> pa( &p[i], 
			   (boost::format("p%i") % i).str(), 
			   true, 
			   "n-th parameter");
      pars.push_back(pa);
  }
    
  }
  
}
