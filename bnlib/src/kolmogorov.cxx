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

  CenterIter::CenterIter( size_t N,
			  size_t o):
    N(N),
    o(o),
    origin( N>>(o+1) ),
    delta( N>>(o) )
  {
    // initialise to the first point
    i=origin;
    j=origin;
  }

  
  void CenterIter::getc( size_t & pi,
			 size_t & pj)
  {
    pi=i;
    pj=j;
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

  bool CenterIter::inBounds(void)
  {
    return ( i < N && j < N);
  }


}
