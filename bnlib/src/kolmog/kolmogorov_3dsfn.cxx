/**
   \file kolmogorov_3dsfn.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   Initial version November 2007
*/

#include "kolmogorov_3dsfn.hxx"

#include "../bnrandom.hxx"
#include <cmath>

namespace BNLib {

  void RandomSFN( const double * cube,
		  size_t Nx,
		  size_t Ny,
		  size_t Nz,
		  size_t s_p,
		  double * acum,
		  size_t * ns,
		  size_t acumlen)
  {

    // Random number generator to use
    UniformDist rfn;
    rfn.reseed(TimeSeed());

    // Set output arrays to zero:
    memset( acum , 0 , acumlen * sizeof(double) );
    memset( ns   , 0 , acumlen * sizeof(size_t) );

    double binfact = ((double)acumlen)/log10(2 * Nx) ;

    for ( size_t ck =0 ; ck < Nz ; ++ck)
      for ( size_t cj =0 ; cj < Ny ; ++cj )
	for (size_t ci =0 ; ci < Nx ; ++ci )
	{
	  double cval = cube[ck * Nx*Ny + cj * Nx + ci];
	  
	  for ( size_t sampleno = 0 ; sampleno < s_p ; ++sampleno)
	  {
	    
	    int ri = (int) std::floor ( Nx * rfn.sample());
	    int rj = (int) std::floor ( Ny * rfn.sample());
	    int rk = (int) std::floor ( Nz * rfn.sample());

	    double rval = cube[ rk * Nx*Ny + rj * Nx + ri ];

	    // This is the actuall distance
	    float  d =  (float) pow( pow(ci - ri ,2 )+
				     pow(cj - rj ,2 )+
				     pow(ck - rk ,2 ),
				     0.5);

	    // Use log binning
	    size_t s = (size_t) (log10(d) * binfact) ;
	    
	    if ( d<acumlen)
	    {
	      acum[s] += pow(rval - cval,2);
	      ns[s] += 1;
	    }

	  }

	}

  }


}

