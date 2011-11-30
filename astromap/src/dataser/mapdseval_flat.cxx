/**
   \file mapdseval_flat.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>

   Initial version November 2011

*/

#include <memory>

#include <gaussian.hxx>
#include "../astromap.hxx"
#include "../astromap_err.hxx"
#include "../pixextract.hxx"
#include "../coordsys/coordsys.hxx"

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

  void MkGaussCoffsPadded (double cx, double cy, Map const &msample,
			   double fwhm_px, 
                           size_t extent_px,
                           size_t *iv,
                           double *cv)
  {

    // These are the pixel coordinates of the supplied world
    // coordinates.
    double px, py;
    // Calculate them...
    msample.cs->worldtopx( cx  , cy , px, py);

    // This is the gaussian which we will use to calculate the coefficients
    BNLib::GaussianDD gfn( fwhm_px / 2.35, px, py );


    int xmin = px - extent_px;
    int xmax = px + extent_px;
    int ymin = py - extent_px;
    int ymax = py + extent_px;
    
    if  (xmin < 0 or xmax >= (signed) msample.nx  or
         ymin < 0 or ymax >= (signed) msample.ny ) 
      throw "Can't use Reg degrid for points which are too close to edge of map";


    *iv=(ymin*msample.nx+xmin);

    double totcoeff = 0;

    for (size_t j =0; j < (extent_px*2+1) ; ++j ) 
      for(size_t i=0; i <(extent_px*2+1) ; ++i ) 
      {
	int currpx = xmin+i;
	int currpy = ymin+j;

	double currcoeff = gfn (currpx, currpy );
	totcoeff += currcoeff ;
	
	cv[j*(extent_px*2+1)+i] = currcoeff;
      }

    for (size_t j =0; j < (extent_px*2+1) ; ++j ) 
      for(size_t i=0; i <(extent_px*2+1) ; ++i ) 
      {
	cv[j*(extent_px*2+1)+i] /= totcoeff;
      }
  }


  MapDSEvalReg::MapDSEvalReg(DataSeries const & ds , 
                             Map const & msample,
                             double fwhm_px, 
                             double extent_px):
    i_stride(msample.nx),
    rl(2*extent_px+1),
    ndp(ds.size()),
    iv(ndp), 
    cv(rl*rl*ndp)
  {
    for (size_t i =0 ; i < ds.size() ; ++i )
    {
      
      MkGaussCoffsPadded( ds[i].dX, ds[i].dY, 
                          msample,
                          fwhm_px, extent_px,
                          &iv[i],
                          &cv[rl*rl*i]);
    }
  }

    MapDSEvalReg::~MapDSEvalReg()
  {
  }


  void MapDSEvalReg::Calc( Map const &m, 
                           std::valarray<double> & res)
  {
    size_t k=0;
    for(size_t i=0; i<ndp; ++i)
    {
      res[i]=0;
      double t=0;
      const size_t si=iv[i];
      for(size_t j=0; j<rl; ++j)
        for(size_t i=0; i<rl; ++i)
      {
        t+=cv[k]*m[si+j*rl*i];
        ++k;
      }
      res[i]=t;
    }
  }

  MapDSEvalBase *MapDSEvalReg::clone(void)
  {
    return new MapDSEvalReg(*this);
  }

}

