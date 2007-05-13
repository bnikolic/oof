/**
   \file kolmogorov.cxx

   Boan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   May 2007 
*/

#include "kolmogorov.hxx"

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

  

  void KolmogorovPlatform( size_t N,
			   double * grid,
			   const double * normvect)
  {

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

}
