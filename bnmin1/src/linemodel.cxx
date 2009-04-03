/**
   \file linemodel.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version April 2009
   
*/

#include "linemodel.hxx"


namespace Minim {
  
  void LineMod::AddParams(std::vector< Minim::DParamCtr > &pars)
  {
    ParamCtr<double> pa(&a, 
			"a", 
			true, 
			"Linear term");
    ParamCtr<double> pb(&b, 
			"b", 
			true, 
			"Constant term");
    pars.push_back(pa);
    pars.push_back(pb);
  }

}


