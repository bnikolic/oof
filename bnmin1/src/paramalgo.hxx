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

  /** \brief Find parameter with name pname
      
      \returns First parameter in parv with name equal to pname, or if
      none found return NULL.
   */
  DParamCtr * findName(std::vector<DParamCtr> & parv,
		       const std::string & pname);


}
#endif
