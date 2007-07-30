/**
   \file fft.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>,
   <bnikolic@nrao.edu>
   
   2003--2007

   An interface to the FFT libraries.
*/

#include "fft.hxx"

#include <vector>

#include <fftw.h>

#include <bndebug.hxx>

#include "astromap.hxx"

namespace AstroMap {

  /* ------------------  Implementation class section -----------------------*/

  /// The implementation of FFTFact using FFTW
  class iFFTFact {
    
    /*! Holds the direction of transform in fftw units */
    fftw_direction direction;

    /// This holds the "plan" for the transform
    fftwnd_plan plan;

    /// Scratch space for the transform
    std::vector<fftw_complex>  fftScratch;

    /// Are we centering?
    FFTFact::cntr docenter;
    
  public:
    
    iFFTFact ( int nx, 
	       int ny,  
	       FFTFact::direction dir , 
	       FFTFact::cntr docenter=FFTFact::center
	       ):
      direction(dir == FFTFact::forward ? FFTW_FORWARD : FFTW_BACKWARD ),
      plan  ( ENFORCE(fftw2d_create_plan(nx,
					 ny, 
					 direction,
					 FFTW_ESTIMATE | FFTW_IN_PLACE) )),
      fftScratch( nx * ny  ),
      docenter(docenter)
    {
    }

    ~iFFTFact() 
    {
      fftwnd_destroy_plan( plan);
    }

    // now the functions that do the work

    /// Does the actuall tranform, leaves result in the fftScratch buffer
    void Transform(const Map &Amp, const Map &Phi ) {
            int mul = ( docenter == FFTFact::center ? -1 : 1 ) ;

	    int nx=Amp.nx;
	    int ny=Amp.ny;

  
	    for (int i =0 ; i < nx ; i++ ) 
	      {
		for (int j=0 ; j < ny ; j++ ) 
		  {
		    if (i+j & 1) 
		      {
			fftScratch[i*nx + j].re= Amp[i*nx + j] * cos( Phi[i*nx + j] ) * mul;
			fftScratch[i*nx + j].im= Amp[i*nx + j] * sin( Phi[i*nx + j] ) * mul;
		      } 
		    else 
		      {
			fftScratch[i*nx + j].re= Amp[i*nx + j] * cos(Phi[i*nx + j] );
			fftScratch[i*nx + j].im= Amp[i*nx + j] * sin(Phi[i*nx + j] );
		      }
		  }
	      }
  
	    fftwnd_one( plan , &fftScratch[0], NULL);
	    // Thats it... result should be in fftScratch
    }
    
    
    void AmpPhi(const Map &Amp, const Map &Phi,
		Map & resAmp, Map & resPhi ) 
    {

      Transform (Amp, Phi);

      unsigned  nx=Amp.nx;    
      unsigned  ny=Amp.ny;

      
      for (unsigned i =0 ; i < nx ; i++ ) 
	{
	  for (unsigned j=0 ; j < ny ; j++ ) 
	    {
	      resAmp[i*nx + j] = sqrt ( pow(fftScratch[i*nx + j].re,2) + pow(fftScratch[i*nx + j].im , 2) ) ;
	      resPhi[i*nx + j] = atan2( fftScratch[i*nx + j].im, fftScratch[i*nx + j].re ) ;
	  
	}
      }
      
    }
    
    void AmpPhi(Map &Amp, Map &Phi) {
      AmpPhi(Amp, Phi, Amp, Phi);
    }
    
    /// As AmpPhi, but result stored in map ResPower.
    void AmpPhiPower( const Map &Amp, const Map &Phi , Map &ResPower) {
      Transform (Amp, Phi);

      unsigned  nx=Amp.nx;    
      unsigned  ny=Amp.ny;
      
      for (unsigned  i =0 ; i < nx ; i++ ) 
	{
	  for (unsigned  j=0 ; j < ny ; j++ ) 
	    {
	      ResPower[i*nx + j] =  pow(fftScratch[i*nx + j].re,2) + 
		pow(fftScratch[i*nx + j].im ,2)   ;
	}
      }
    }
  };


  // -------------- FFTFact class section --------

  /// Implementation of constructor
  FFTFact::FFTFact(int nx, int ny,  direction dir , cntr docenter):
    ip ( new  iFFTFact(nx,ny,dir,docenter)),
    nx(nx), ny(ny),
    dir(dir) , docenter(docenter)
  {
    
  }
  
  FFTFact::~FFTFact() 
  {
    delete ip;
  }

  void FFTFact::fftamphi(Map &Amp, Map &Phi) {
    ip->AmpPhi(Amp, Phi);
  }

  void FFTFact::fftamphi(const Map &Amp, const Map &Phi,
			 Map &resAmp, Map &resPhi)
  {
    ip->AmpPhi(Amp, Phi,
	       resAmp, resPhi);
  }

  void FFTFact::FFTAmpPh_Power( const Map  &Amp, const Map &Ph , Map &ResPower) {
    ip->AmpPhiPower( Amp, Ph , ResPower);
  }

  bool congruous(FFTFact &f, unsigned nx, unsigned ny, 
		 FFTFact::direction dir , FFTFact::cntr docenter ) 
  {
    return ( f.nx       ==  nx && 
	     f.ny       ==  ny   &&
	     f.dir      ==  dir && 
	     f.docenter ==  docenter ) ;
  }

}
