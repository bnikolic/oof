/*!
  Bojan Nikolic
  $Id: cassegrain.hxx,v 1.1 2005/05/24 20:34:16 bnikolic Exp $

*/
#ifndef _OOF_TELGEO_CASSEGRAIN_HXX__
#define _OOF_TELGEO_CASSEGRAIN_HXX__
namespace OOF {

  
  struct CassegrainGeo {
    
    double PrimRadius;
    double PrimF;
    
    double SecRadius;
    double CasF;
  };

  
}
#endif
