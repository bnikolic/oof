/**
   \file kolmogorov_wrap.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   May 2007
*/

#include "kolmogorov_wrap.hxx"

#include "kolmogorov.hxx"
#include "kolmogorov_spec.hxx"
#include "../bnrandom.hxx"


namespace BNLib {

  void KolmogorovPlatform( size_t N,
			   double * grid,
			   unsigned long seed  )
  {

    if ( seed == 0)
    {
      seed = TimeSeed();
    }

    std::vector<double> normvect (N*N +2);
    
    NormDistZM dist(1.0 );
    dist.reseed(seed);

    dist.samplefill(normvect);

    KolmogorovPlatform( N,
			grid,
			&normvect[0] );
    
  }

  void BrkKolmogorovPlatform( size_t N,
			      double * grid,
			      double w,
			      unsigned long seed  )
  {
    if ( seed == 0)
    {
      seed = TimeSeed();
    }

    NormDistZM rfn(1.0 );
    Kol3DBreakLaw sfn(w);
    
    KolmogorovPlatform( N,
			grid,
			sfn,
			rfn);

  }

  


}
