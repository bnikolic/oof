/*
  Bojan Nikolic
  $Id: telswitch.cxx,v 1.2 2005/08/17 20:43:37 bnikolic Exp $

*/

#include "telswitch.hxx"

#include <memory>
#include <stdlib.h>

#include "telgeo.hxx"
#include "cassegrain.hxx"
#include "gbtgeo.hxx"

namespace OOF {

  TelGeometry * MkALMA(void)
  {
    std::auto_ptr<CassegrainGeo> res ( new CassegrainGeo() );

    res->PrimRadius = 6.0   ;
    res->PrimF      = 4.8   ;
    res->SecRadius  = 0.75/2;
    res->CasF       = 96.0  ;


    return res.release();
  }

  TelGeometry * TelSwitch(const char * telname )
  {
    
    if ( ! strcmp( telname , "ALMA" )  )
      {
	return MkALMA() ;
      }
    else if ( !strcmp (telname, "APEX") ) 
      {
	return MkALMA() ;
      }
    else if ( !strcmp (telname, "GBT") ) 
      {
	return new GBTGeo();
      }
    else
      {
	return NULL;
      }

  }


}


