/*
  Bojan Nikolic

*/

#include "convolve.hxx"

#include <stdexcept>

#include "astromap.hxx"
#include "fft.hxx"


namespace AstroMap {

  Map * FFTConvolve( const Map &  m1,
		     const Map &  m2)
  {
    if (not (m1.nx == m2.nx &&
	     m1.ny == m2.ny) )
      throw std::runtime_error( "Don't know how to convolve maps without identical dimensions");

    Map m1amp ( m1);

    Map m1phase (m1);
    m1phase *= 0;

    Map m2amp ( m2);

    Map m2phase (m2);
    m2phase *= 0;

    
    FFTFact InverseFF ( m1.nx, m1.ny, 
			FFTFact::backward,
			FFTFact::dontcenter);

    InverseFF.fftamphi( m1amp, m1phase);
    InverseFF.fftamphi( m2amp, m2phase);

    m1amp *= m2amp;
    m1phase += m2phase;


    FFTFact ForwardFF ( m1.nx, m1.ny, 
			FFTFact::forward,
			FFTFact::center);


    ForwardFF.fftamphi( m1amp, m1phase);
    m1amp /= ( m1amp.nx * m1amp.ny);
    
    return new Map(m1amp);


  }


}





