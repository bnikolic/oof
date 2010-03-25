/**
   \file convolve.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

*/

#include "convolve.hxx"

#include <stdexcept>

#include "astromap.hxx"
#include "fft.hxx"


namespace AstroMap {

  void FFTConvolve( const Map &  m1,
		    const Map &  m2,
		    Map &mres)
  {
    if (not (m1.nx == m2.nx &&
	     m1.ny == m2.ny) )
      throw std::runtime_error( "Don't know how to convolve maps without identical dimensions");

    mres=m1;

    Map m1phase (m1);
    m1phase=0;

    Map m2amp ( m2);

    Map m2phase (m2);
    m2phase=0;

    
    FFTFact InverseFF ( m1.nx, m1.ny, 
			FFTFact::backward,
			FFTFact::dontcenter);

    InverseFF.fftamphi( mres, m1phase);
    InverseFF.fftamphi( m2amp, m2phase);

    mres *= m2amp;
    m1phase += m2phase;


    FFTFact ForwardFF ( m1.nx, m1.ny, 
			FFTFact::forward,
			FFTFact::center);


    ForwardFF.fftamphi(mres, 
		       m1phase,
		       false);

    mres /= ( mres.nx * mres.ny);
    
    mres *=   cos(m1phase);
  }

  Map * FFTConvolve( const Map &  m1,
		     const Map &  m2)
  {
    Map *res=new Map(m1);
    FFTConvolve(m1, m2, 
		*res);
    return res;
  }


}





