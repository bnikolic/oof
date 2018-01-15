/**
   \file zernikepoly.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
*/

#include "zernikepoly.hxx"

#include "bndebug.hxx"

namespace BNLib {

  static int factorial( int n );

  static int factorial( int n )
  { 
    return ( n < 2 ) ? 1 : n * factorial( n - 1 ); 
  }
  
  
  ZernPoly::ZernPoly( int n, int l  ):
    n(n),
    l(l),
    m( l >= 0 ? l : -l),
    nradterm ( 1 + ( ( n - m ) / 2 ) ),
    radcoeffs(0.0, nradterm),
    radpowers(0 , nradterm )
  {

    ENFORCE( n >= 0);

    ENFORCE( m <= n );

    // Make sure n-m is not odd
    ENFORCE( ( ( n-m) & 1 ) == 0 );

  
    int sign = -1;
  
    for ( int s = 0; s < nradterm; s++ )
      {
      sign *= -1;      
      
      radpowers[s] = n - 2 * s;

      radcoeffs[s]  = sign * factorial( n - s ) / 
	( factorial( s ) * factorial( ( n + m ) / 2 - s ) * factorial( ( n - m ) / 2 - s ) );

      }

  }
  
  ZernPoly::~ZernPoly()
  {
  }

  double ZernPoly::operator()( double x, double y )
  {
    double r= sqrt ( pow(x,2) + pow(y,2) );
    double phi = atan2(y,x);

    double v = 0.0;

    for ( int s = 0; s < nradterm; s++ ) 
      {
	v += radcoeffs[s] * pow( r, radpowers[s] );
      }


    if ( l > 0 )
      {
	v *= cos( l * phi );
      }
    else if ( l < 0 )
      {
	v *= sin( - l * phi ); 
      }

   

    return v;
  }

  
  size_t ZernIFromNL(int n, int l)
  {
    return ( n*(n+1) + n+ l)/2 ; 
  }

  void ZernNLFromI(size_t i, int &n, int &l)
  {
    for (n=0; ZernIFromNL(n, -n) <= i; ++n);
    n--;
    for (l=-n; ZernIFromNL(n, l) != i; ++l);
  }


}

