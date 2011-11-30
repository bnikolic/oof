/**
   \file mapdseval_flat.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   Initial version November 2011

*/

#include <memory>

#include "mapdseval_flat.hxx"
#include "dataseries.hxx"

namespace AstroMap {

  MapDSEvalFlat::MapDSEvalFlat(DataSeries const & ds, 
                               Map const & msample,
                               double fwhm_px, 
                               double extent_px):
    c_stride((2*extent_px+1)*(2*extent_px+1)),
    ndp(ds.size()),
    nt(ndp * c_stride),
    iv(nt), cv(nt, 0.0)
  {
    for (size_t i =0 ; i < ds.size() ; ++i )
    {
      std::auto_ptr<MapPixLC> t (MkGaussCoffs( ds[i].dX, ds[i].dY, 
                                               msample,
                                               fwhm_px, extent_px));
      
      for (size_t j=0 ; j < t->index.size(); ++j)
      {
        iv[c_stride*i+j]=t->index[j];
        cv[c_stride*i+j]=t->coeff[j];
      }
    }
  }

  MapDSEvalFlat::~MapDSEvalFlat()
  {
  }

  void MapDSEvalFlat::Calc( Map const &m, 
                            std::valarray<double> &res)
  {
    for(size_t i=0; i<ndp; ++i)
    {
      res[i]=0;
      double t=0;
      for(size_t j=0; j<c_stride; ++j)
      {
        t+=cv[i*c_stride+j] * m[ iv[i*c_stride+j] ];
      }
      res[i]=t;
    }
  }

  MapDSEvalBase *MapDSEvalFlat::clone(void)
  {
    return new MapDSEvalFlat(*this);
  }
}

