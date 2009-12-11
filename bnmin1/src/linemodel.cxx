/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version April 2009

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file linemodel.cxx
   
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


