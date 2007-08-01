/**
   \file mapops.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include "mapops.hxx"

#include <valarray>
#include <cmath>
#include <memory>

#include "astromap.hxx"
#include "coordsys/lincordsys.hxx"

#include <bnrandom.hxx>
#include <kolmogorov_wrap.hxx>



namespace AstroMap {

  void NormDist(Map &m, double sigma)
  {
    using namespace BNLib;

    NormDistZM nd(sigma);
    nd.reseed(TimeSeed());

    for (unsigned i =0 ; i < m.size() ; ++i)
      m[i]= nd.sample();

  }

  double MapRMS( Map &m)
  {
    double var = ( (m*m).sum()/ m.size()  - pow( (m.sum()/ m.size() ),2) );

    return sqrt(var);
  }

  double MapRMS( Map &m, Map & weight)
  {
    std::valarray<double> goodmap ( m[weight>0.0] );
    std::valarray<double> goodweight ( weight[weight>0.0] );

    double mean = (goodmap * goodweight).sum() / goodweight.sum() ;

    goodmap *= goodmap;

    double var = (goodmap  * goodweight).sum() / goodweight.sum()  - pow(mean,2);

    return sqrt(var);

  }

  Map *  IntZoom( Map &m, unsigned scale)
  {
    
    std::auto_ptr<Map> mres ( new Map( m.nx *scale, m.ny  *scale));

    // First copy the data
    for (unsigned x =0 ;  x < m.nx  ; ++x)
      for (unsigned y= 0 ; y < m.ny; ++y ) 
	{
	  for ( unsigned dx  =0 ; dx < scale ; ++dx)
	    for (unsigned dy =0 ; dy < scale ; ++dy)
	      {
		mres->get( x*scale+dx, y*scale+dy) = m.get(x,y);
	      }
	}

    // Sort out the coordinate system
    delete(    mres->cs);
    mres->cs = m.cs->Clone();
    
    return mres.release();

  }

  std::complex<double> ComplexSum( const Map & amp,
				   const Map & phase)
  {
    std::complex<double> res(0,0);
    std::complex<double> imag(0,1);
    for ( size_t i =0 ; i < amp.size() ; ++i)
    {
      res += amp[i]*exp( imag * phase[i]);
    }
    
    return res;
  }
  

  void KolmogorovMap( Map &m )
  {
    BNLib::KolmogorovPlatform(m.nx, &m[0], 0);
  }

  void KolmogorovMap( Map &m,
		      double w)
  {
    BNLib::BrkKolmogorovPlatform(m.nx, &m[0], w, 0);
  }

}



