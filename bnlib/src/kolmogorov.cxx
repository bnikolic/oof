/**
   \file kolmogorov.cxx

   Boan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   May 2007 
*/

#include "kolmogorov.hxx"
#include "kolmogorov_iters.hxx"

#include <cmath>

namespace BNLib {

  /** Generate the four corner samples of the Kolmogorov
      platform. Will use six random samples from the normvect.
      
   */
  void KPCorners( double * alpha,
		  double * beta,
		  double * gamma,
		  double * delta,
		  const double * normvect)
  {
    const double SigmaC=0.86638145132179845;
    const double SigmaD=3.2798677905095714;

    const double Rad = normvect[4] * SigmaD;
    const double Rbg = normvect[5] * SigmaD;


    *alpha = normvect[0] * SigmaC + 0.5 * Rad;
    *beta  = normvect[1] * SigmaC + 0.5 * Rbg;
    *gamma = normvect[2] * SigmaC - 0.5 * Rbg;
    *delta = normvect[3] * SigmaC - 0.5 * Rad;
  }


  /**
     Get parent values from a double array
  */
  template<class T, class pT> 
  double getParentVal( double * a,
		       const T & iter,
		       pT  p)
  {
    size_t i, j;
    iter.getParent( i,j, p);
    return a[j* iter.N +i];
  }
  

  void KolmogorovPlatform( size_t N,
			   double * grid,
			   const double * normvect)
  {
    /*   (alpha)               (beta)

    
         (gamma)                (delta)

    */
    KPCorners( grid,
	       grid + (N-1),
	       grid + N*(N-1),
	       grid + N*N - 1,
	       normvect);

    // We've used up six random values
    normvect += 6;

    for ( size_t o =0 ;  ( ((size_t)1) << (o+1) ) < N  ; ++o )
    {
      // First the centre cells...
      CenterIter ci(N, o);
      while ( ci.inBounds() )
      {
	size_t i,j;
	ci.getc( i,j);

	double newval = 0.25 * ( getParentVal( grid, ci , CenterIter::TL) +
				 getParentVal( grid, ci , CenterIter::TR) +
				 getParentVal( grid, ci , CenterIter::BL) +
				 getParentVal( grid, ci , CenterIter::BR)  ) +
	  ( *normvect  ) * pow( 0.6091 * pow( ci.parentDist() , 5.0 / 3.0),
				0.5);
	
	grid[j*N+i] = newval;
	++normvect;

	ci.next();
      }
      
      // Next the "edge" cells
      EdgeIter ei(N,o);
      while (ei.inBounds() )
      {
	size_t i,j;
	ei.getc( i,j);
	double newval=0;

	// Do the calculation....
	if ( ei.isHEdge() )
	{
	  newval = 0.5 * ( getParentVal( grid, ei , EdgeIter::L) +
			   getParentVal( grid, ei , EdgeIter::R) ) +
	    (*normvect) * pow ( 0.4471 * pow(ei.parentDist(), 5.0/3.0) , 
				0.5 );
	}
	else if ( ei.isVEdge())
	{
	  newval = 0.5 * ( getParentVal( grid, ei , EdgeIter::T) +
			   getParentVal( grid, ei , EdgeIter::B) ) +
	    (*normvect) * pow ( 0.4471 * pow(ei.parentDist(), 5.0/3.0) , 
				0.5 );

	}
	else
	{
	  // not an edge, use four parents as normal.
	  newval = 0.25 * ( getParentVal( grid, ei , EdgeIter::T) + 
			    getParentVal( grid, ei , EdgeIter::B) + 
			    getParentVal( grid, ei , EdgeIter::L) +
			    getParentVal( grid, ei , EdgeIter::R)  ) +
	  ( *normvect  ) * pow( 0.6091 * pow( ei.parentDist() , 5.0 / 3.0),
				0.5);
	  
	}

	grid[j*N+i] = newval;
	++normvect;
	ei.next();

      }

    }

  }


}
