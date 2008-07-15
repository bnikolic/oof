/**
   \file tdzhelper.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Simple template class to use when calculating defocus phase 
*/
#ifndef _OOF_TDZHELPER_HXX__
#define _OOF_TDZHELPER_HXX__

#include <binaryfn.hxx>

namespace OOF {

  /** \brief Wrap SecDeltaPath as binary function
   */
  template<class TGeo>  class DzHelper : 
    public BNLib::BinaryDD 
  {
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

  /** \brief Wrap functions on telescope gemetry as binary functions

      Provide a choice of functions to use to calculate the path and
      allow calculation of deflections in any direction.
  */
  template<class TGeo,   
	   double (*SecFn) (double, double, 
			    double, double, double, 
			    const TGeo &)
    >  class DzHelperFull : public BNLib::BinaryDD {

    const TGeo &geo;
    double dx;
    double dy;
    double dz;
    
  public:
    
    DzHelperFull(    const TGeo &geo,  double dx, double dy, double dz ):
      geo(geo),
      dx(dx),      dy(dy),
      dz(dz)
    {
    }

    double operator() (double x , double y )
    {
      return SecFn( x, y , dx, dy, dz, geo);
    }
  };


}
#endif
