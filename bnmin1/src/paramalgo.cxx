/**
   \file paramalgo.cxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   
*/

#include "paramalgo.hxx"

namespace Minim {

  DParamCtr * findName(std::vector<DParamCtr> & parv,
		       const std::string & pname)
  {
    for ( std::vector<DParamCtr>::iterator i ( parv.begin() ) ;
	  i < parv.end() ;
	  ++i ) 
      if (i->name == pname ) return &(*i);
    
    return NULL;
  }

}

