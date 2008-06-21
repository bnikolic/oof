/**
   \file paramalgo.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
   Algorithms on parameters
*/
#ifndef _BNMIN_PARAMALGO_HXX__
#define _BNMIN_PARAMALGO_HXX__

#include <vector>
#include "paramctr.hxx"

namespace Minim {

  DParamCtr * findName(std::vector<DParamCtr> & parv,
		       const std::string & pname);


}
#endif
