/**
   \file kolmogorov_iters.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   
   May 2007

*/

#include "kolmogorov_iters.hxx"

#include <cmath>

namespace BNLib {
  namespace Kolmog {


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

  double CenterIter::sideDist(void) const
  {
    
    size_t tli , tlj;
    size_t tri , trj;

    getParent( tli, tlj,
	       TL);

    getParent( tri, trj,
	       TR);

    return (tri-tli)/ (double(N)-1);


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

  double EdgeIter::sideDist(void) const
  {
    if ( isEdge()  )
    {
      return parentDist() * 2.0;
    }
    else
    {
      return parentDist() * M_SQRT2;
    }
  }

  }}
