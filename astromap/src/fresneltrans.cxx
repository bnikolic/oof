/**
   \file fresneltrans.cxx

    Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
    
    May 2007

*/

#include "fresneltrans.hxx"
#include "astromap.hxx"

namespace AstroMap {


  std::complex<double> dFresnelDir( const Map & m,
				    size_t k,
				    size_t l,
				    double R)
  {
    
    std::complex<double> res(0,0) ;

    std::complex<double>  i2pnx (0, 2 * M_PI / m.nx);

    std::complex<double>  i2pnx2 (0, 2 * M_PI / m.nx / m.nx / 2 / R);

    std::complex<double>  i2pny (0, 2 * M_PI / m.ny);
    std::complex<double>  i2pny2 (0, 2 * M_PI / m.ny / m.ny / 2 / R);

    const int sk = k - m.nx/2;
    const int sl = l - m.ny/2;

    for ( size_t j = 0 ; j < m.ny ; ++j )
    {
      const int sj = j -m.ny/2;
      for (size_t i =0 ; i < m.nx ; ++i)
      {
	if ( m.get(i,j) != 0.0 )
	{
	  const int si = i -m.nx/2;
	  res += std::complex<double>( m.get(i,j) ,  0 ) * 
	    exp( i2pny * std::complex<double>(sj * sl,0) + 
		 i2pnx * std::complex<double>(si * sk,0) +
		 i2pny2 * std::complex<double>( sj*sj,0)  + 
		 i2pnx2 * std::complex<double>(si*si,0)  );
	}
      }
    }
    
    return res;
  }
}



