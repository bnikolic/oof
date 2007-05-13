/**
   \file kolmogorov.cxx

   Boan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   May 2007 
*/

#include "kolmogorov.hxx"

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

  KolCellIteratorBase::KolCellIteratorBase( size_t N, 
					    size_t o):
    N(N),
    o(o)
  {

  }

  void KolCellIteratorBase::getc( size_t & pi,
				  size_t & pj) const
  {
    pi=i;
    pj=j;
  }

  bool KolCellIteratorBase::inBounds(void) const
  {
    return ( i < N && j < N);
  }

  

  CenterIter::CenterIter( size_t N,
			  size_t o):
    KolCellIteratorBase( N,  o),
    origin(N>>(o+1)),
    delta( N>>(o))
  {
    if ( delta > 0 )
    {
      // initialise to the first point
      i=origin;
      j=origin;
    }
    else
    {
      // order is too high for this grid size so go out of bounds
      // straight away
      i=N;
      j=N;
    }
  }

  


  void CenterIter::getParent(size_t & iOUT,
			     size_t & jOUT,
			     parentPos p
			     ) const
  {
    size_t ri = i;
    size_t rj = j;

    if ( p == TL || p == TR )
    {
      rj -= origin;
    }
    else 
    {
      rj += origin;
    }

    if ( p == TL || p == BL )
    {
      ri -= origin;
    }
    else
    {
      ri += origin;
    }
    
    iOUT= ri;
    jOUT= rj;
  }

  double CenterIter::parentDist(void) const
  {
    size_t pi , pj;

    // Distance to all should be the same of course
    getParent( pi, pj,
	       TL);

    double d2=    pow( i-pi , 2) + pow( j - pj, 2);

    return pow( d2, 0.5) / ( double(N)-1) ;
  }

  void CenterIter::next(void)
  {
    if ( i + delta >= N )
    {
      i=origin;
      j=j+delta;
    }
    else
    {
      i=i+delta;
    }
  }

  EdgeIter::EdgeIter( size_t N,
		      size_t o):
    KolCellIteratorBase( N, o),
    origin(N>>(o+1)),
    delta( origin *2  )
  {
    if ( origin > 0 ) 
    {
      i=origin;
      j=0;
    }
    else
    {
      i=j=N;
    }
  }

  void EdgeIter::next(void)
  {
    if ( i + delta >= N)
    {
      // start new row.
      j +=  origin;

      //odd rows start at i =0
      if ( (j/origin) & 1 )
      {
	i =0;
      }
      else
      {
	i=origin;
      }
    }
    else
    {
      i += delta;
    }
    
  }

  EdgeIter::edgePos EdgeIter::isEdge(void) const
  {
    if ( i == 0 || i== ( N-1 ) )
    {
      return VEdge;
    }
    else if ( j ==0 || j == (N-1) )
    {
      return HEdge;
    }
    else
    {
      return noEdge;
    }
  }

  bool EdgeIter::isHEdge(void) const 
  {
    return isEdge() == HEdge;
  }

  bool EdgeIter::isVEdge(void) const 
  {
    return isEdge() == VEdge;
  }

  void EdgeIter::getParent(size_t & iOUT,
			   size_t & jOUT,
			   parentPos p
			   ) const 
  {
    iOUT= i;
    jOUT= j;
    
    if ( p == L )
    {
      iOUT -= origin;
    } 
    else if ( p == R)
    {
      iOUT += origin;
    }
    else if ( p == T )
    {
      jOUT -= origin;
    }
    else 
    {
      jOUT += origin;
    }
  }

  double EdgeIter::parentDist(void) const
  {
    return origin/ (double (N-1));
    
  }


}
