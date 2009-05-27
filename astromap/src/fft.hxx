/**
   \file fft.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk> , <bn204@mrao.cam.ac.uk>

   Support for FFT's

*/
#ifndef _AstroMap_FFT_HXX__
#define _AstroMap_FFT_HXX__



namespace AstroMap {

  class Map;

  /// Forward for the implementatin class
  class iFFTFact;

  /*! Short for FFTFactory.
   *
   *Does FFT on a supplied map -- only works on specific dimensions,
   *etc.
   */
  class FFTFact {
  public:
    /// Type to specify the direction of the transform
    enum direction { forward = -1 , backward = 1 };

    /// Type to specify whether the transform should be centred or
    /// not.
    enum cntr { center = 1 , dontcenter=0 };

  private:
    /// This is the actuall implementiation class;
    iFFTFact *ip;
  public:

    /// Size of maps to transform in pixels -- these are all const as
    /// it doesn't make sense to change them later.
    unsigned const  nx,ny;
    /// Direction of transform
    const    direction dir;
    /// To centre or not
    const    cntr      docenter;

    /// Constructor
    FFTFact(int nx, int ny,  direction dir , cntr docenter=center);
    
    /// Destructor; can't use auto_ptr for ip because it points to a
    /// class which in some context is never defined.
    ~FFTFact();

    /// Do the complex 2D fourier transform on the maps representing
    /// amplitude and phase, puting the result in the same maps.
    void fftamphi(Map &Amp, Map &Phi,
		  bool check=true);

    void fftamphi(const Map &Amp, const Map &Phi,
		  Map &resAmp, Map &resPhi,
		  bool check=true);

    /// Do the complex 2d fourier transform on a Amp, Phase pair and
    /// return the power. \calgraph
    void FFTAmpPh_Power( const Map  &Amp, const Map &Ph , Map &ResPower);

  };

  /// Returns true if f is a suitable factory to transform maps as
  /// described.
  bool congruous(FFTFact &f, unsigned nx, unsigned ny, 
		 FFTFact::direction dir , FFTFact::cntr docenter );
}
#endif 
