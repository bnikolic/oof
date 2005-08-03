/*
  Bojan Nikolic
  $Id: mapdseval.cxx,v 1.2 2005/08/03 12:00:37 bnikolic Exp $

*/

#include "mapdseval.hxx"

#include <memory>
#include <gaussian.hxx>

#include "../astromap.hxx"
#include "../pixextract.hxx"
#include "../coordsys/coordsys.hxx"
#include "dataseries.hxx"


namespace AstroMap {

  MapPixLC::MapPixLC( std::valarray<unsigned> const &index , 
		      std::valarray<double > const &coeff ):
    index(index),
    coeff(coeff)
  {

  }


  double MapPixLC::operator() (Map const &m)
  {
    double res = 0;
    for (unsigned i =0 ; i < index.size() ; ++i )
      res += coeff[i] * m[ index[i] ];

    return res;
  }

  MapPixLC * MkGaussCoffs (double cx, double cy, Map const &msample,
			   double fwhm_px, double extent_px)
  {
    
    // These are the pixel coordinates of the supplied world
    // coordinates.
    double px, py;
    // Calculate them...
    msample.cs->worldtopx( cx  , cy , px, py);

    // This is the gaussian which we will use to calculate the coefficients
    BNLib::GaussianDD gfn( fwhm_px / 2.35, px, py );

    // Exactract the pixels withing the supplied extnent
    PixListInt pxl = ExSquare( (int) px, (int) py, (int) extent_px, msample);

    std::valarray<unsigned> index(pxl.size());
    std::valarray<double>   coeff(pxl.size());

    double totcoeff = 0;

    for (unsigned i =0 ; i < pxl.size() ; ++i ) 
      {
	int currpx = (*pxl.px)[i];
	int currpy = (*pxl.py)[i];	

	double currcoeff = gfn (currpx, currpy );
	totcoeff += currcoeff ;
	
	index[i] = currpy * msample.nx + currpx;
	coeff[i] = currcoeff;
	
      }

    coeff /= totcoeff;
    return new MapPixLC( index, coeff);

  }

  MapDSEval::MapDSEval( DataSeries const & ds , 
			Map const & msample,
			double fwhm_px, double extent_px):
    lcs(ds.size() )
  {

    for (unsigned i =0 ; i < ds.size() ; ++i )
      lcs[i] = MkGaussCoffs( ds[i].dX, ds[i].dY, 
			     msample,
			     fwhm_px, extent_px );
  }

  MapDSEval::~MapDSEval()
  {
    for (unsigned i =0 ; i < lcs.size() ; ++i )
      delete lcs[i];
  }

  void MapDSEval::Calc( Map const &m, std::valarray<double> & res)
  {
    for (unsigned i =0 ; i < lcs.size() ; ++i )
      {
	res[i] = (*lcs[i])(m);
      }
  }

}


