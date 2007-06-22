/**
   \file mapstructure.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>

*/

#include "mapstructure.hxx"

#include <bnrandom.hxx>

#include "astromap.hxx"

namespace AstroMap {

  void  RndStructureFn( const Map & m,
			size_t samples_px,
			std::vector<double> & OUTsfn,
			std::vector<size_t> & OUTcount )
  {
    size_t sfnsize= (size_t) ceil( sqrt( pow(m.nx,2) + pow(m.ny, 2)));

    OUTsfn.resize(sfnsize);
    OUTcount.resize(sfnsize);

    BNLib::UniformDist rfn;
    rfn.reseed(BNLib::TimeSeed());

    for (size_t j =0 ; j < m.ny ; ++j)
      for(size_t i =0 ; i < m.nx ; ++i)
      {
	for (size_t c = 0 ; c < samples_px ; ++ c)
	{
	  int rj = (size_t) floor( m.ny * rfn.sample() );
	  int ri = (size_t) floor( m.nx * rfn.sample() );
	  
	  size_t d =  (size_t) sqrt( pow( (int)j-rj, 2) +
				     pow( (int)i-ri, 2) );
	  
	  
	  OUTsfn[d] += pow( m.get(i,j) - m.get(ri, rj) , 2);
	  OUTcount[d] += 1;
	}
      }
  }

  void  RndStructureFn( const Map & m,
			size_t samples_px,
			double * OUTsfn,
			double * OUTcount,
			size_t   n)
  {
    std::vector<double>  sfn;
    std::vector<size_t>  count;

    RndStructureFn( m, samples_px, sfn, count);

    for (size_t i =0 ; i < n && i < sfn.size() ; ++i )
    {
      OUTsfn[i]=sfn[i];
      OUTcount[i]=count[i];
    }

  }


}

