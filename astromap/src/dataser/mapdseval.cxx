/**
   \file mapdseval.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk> , <bojan@bnikolic.co.uk>
   2004-2007
*/

#include "mapdseval.hxx"

#include <memory>
#include <vector>
#include <iostream>

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

  double MapPixLC::operator() (Map const &m, 
			       signed int offset)
  {
    double res=0;
    size_t totpx= m.nx*m.ny;
    for ( size_t i =0 ; i < index.size() ; ++i )
    {
      signed int px = index[i] + offset;
      if ( px <0 || px >= (int)totpx )
      {
	throw "Offset has taken the interpolation out of bounds";
      }
      res += coeff[i] * m[ px ];
    }

    return res;

  }

  void MapPixLC::print(void)
  {
    for (unsigned i =0 ; i < index.size() ; ++i )
    {
      std::cout<<"inx=" <<index[i]<<" c=" <<coeff[i];
    }
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

  MapPixLC * MkCircleCoeffs (int px, int py, 
			     Map const &msample,
			     double radius)
  {

    PixListInt pxl = ExSquare(  px,  py, ceil(radius), msample);
    
    std::vector<unsigned> index;
    std::vector<double>   coeff;

    for (unsigned i =0 ; i < pxl.size() ; ++i ) 
    {
	int currpx = (*pxl.px)[i];
	int currpy = (*pxl.py)[i];	
	
	if ( pow( currpx - px,2 ) + pow( currpy-py,2) < pow(radius,2))
	{
	  index.push_back( currpy * msample.nx + currpx);
	  coeff.push_back( 1.0);
	}
    }

    std::valarray<double> vcoeff( &coeff[0] , coeff.size() );
    std::valarray<unsigned> vindex( &index[0] , index.size() );
    vcoeff /= vcoeff.sum() ;
    return new MapPixLC( vindex, vcoeff);
  }

  MapDSEvalBase::~MapDSEvalBase()
  {
    for (unsigned i =0 ; i < lcs.size() ; ++i )
      delete lcs[i];
  }

  MapDSEval::MapDSEval( DataSeries const & ds , 
			Map const & msample,
			double fwhm_px, double extent_px)
  {

    lcs.resize(ds.size() );

    for (unsigned i =0 ; i < ds.size() ; ++i )
      lcs[i] = MkGaussCoffs( ds[i].dX, ds[i].dY, 
			     msample,
			     fwhm_px, extent_px );
  }

  void MapDSEvalBase::Calc( Map const &m, std::valarray<double> & res)
  {
    for (unsigned i =0 ; i < lcs.size() ; ++i )
      {
	res[i] = (*lcs[i])(m);
      }
  }

  void MapDSEvalBase::Calc( Map const &m, std::vector<double> & res)
  {
    for (unsigned i =0 ; i < lcs.size() ; ++i )
      {
	res[i] = (*lcs[i])(m);
      }
  }

}


