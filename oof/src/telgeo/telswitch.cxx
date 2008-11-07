/**
   \file telswitch.cxx
    Bojan Nikolic <bojan@bnikolic.co.uk>
*/

#include "telswitch.hxx"

#include <memory>
#include <stdlib.h>
#include <string.h>

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

  TelGeometry * MkALMANoSec(void)
  {
    std::auto_ptr<CassegrainGeo> res ( new CassegrainGeo() );

    res->PrimRadius = 6.0   ;
    res->PrimF      = 4.8   ;
    res->SecRadius  = 0;
    res->CasF       = 96.0  ;


    return res.release();
  }

  TelGeometry * TelSwitch(const char * telname )
  {
    
    if ( ! strcmp( telname , "ALMA" )  )
    {
      return MkALMA() ;
    }
    if ( ! strcmp( telname , "ALMANoSec" )  )
    {
      return MkALMANoSec() ;
    }
    else if ( !strcmp (telname, "APEX") ) 
    {
      return MkALMA() ;
    }
    else if ( !strcmp (telname, "GBT") ) 
    {
      return new GBTGeo();
    }
    else if ( !strcmp (telname, "90GBT") )
    {
      return new TruncGBT(45);
    }
    else
    {
      return NULL;
    }

  }


}


