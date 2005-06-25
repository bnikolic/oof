/*!
  Bojan Nikolic
  $Id: tdzhelper.hxx,v 1.1 2005/06/25 12:08:57 bnikolic Exp $

  Simple template class to use when calculating defocus phase 
*/
#ifndef _OOF_TDZHELPER_HXX__
#define _OOF_TDZHELPER_HXX__

#include <binaryfn.hxx>

namespace OOF {

  template<class TGeo>  class DzHelper : public BNLib::BinaryDD {

    const TGeo &geo;
    double dz;
    
  public:
    
    DzHelper(    const TGeo &geo,  double dz ):
      geo(geo),
      dz(dz)
    {
    }

    double operator() (double x , double y )
    {
      return SecDeltaPath( x, y , 0, 0, dz, geo);
    }
  };


}
#endif
