/**
   \file fft.cxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>,
   <bnikolic@nrao.edu>
   
   2003--2007

   An interface to the FFT libraries.
*/

#include <vector>

#include "fft.hxx"


#include <fftw3.h>

#include <bndebug.hxx>

#include "astromap.hxx"

// This variable is initialised at the time of loading of the shared
// library and contains the return code of fftw_init_threads(). This
// functions sets FFTW up for multi-threaded operation
static int _astromap_fftw_threads_init=fftw_init_threads();


// A simple function to prepare for transform
void TransfPrep(const double *amp,
                const double *phi,
                const size_t nx,
                const size_t ny,
                double mul,
                double *fin)
{
  for (size_t i=0; i<nx; i++) 
  {
    for (size_t j=0; j<ny; j++) 
    {
      if ( (i+j) & 1) 
      {
        fin[(i*nx + j)*2]= amp[i*nx + j] * cos( phi[i*nx + j] ) * mul;
        fin[(i*nx + j)*2+1]= amp[i*nx + j] * sin( phi[i*nx + j] ) * mul;
      } 
      else 
      {
        fin[(i*nx + j)*2]= amp[i*nx + j] * cos(phi[i*nx + j] );
        fin[(i*nx + j)*2+1]= amp[i*nx + j] * sin(phi[i*nx + j] );
      }
    }
  }
}

namespace AstroMap {

  /* ------------------  Implementation class section -----------------------*/

  /// The implementation of FFTFact using FFTW
  class iFFTFact {
    
    /*! Holds the direction of transform in fftw units */
    int direction;

    /// This holds the "plan" for the transform
    fftw_plan plan;

    /// Scratch space for the transform. Leave as naked pointer, since
    /// we need to allocate the space using specialised functions to
    /// ensure proper alignement 
    fftw_complex *fin;
    fftw_complex *fout;

    /// Are we centering?
    FFTFact::cntr docenter;

    /// Maximum number of threads to use
    static const size_t threads=2;
    
  public:
    
    iFFTFact ( int nx, 
	       int ny,  
	       FFTFact::direction dir , 
	       FFTFact::cntr docenter=FFTFact::center
	       ):
      direction(dir == FFTFact::forward ? FFTW_FORWARD : FFTW_BACKWARD ),
      fin(reinterpret_cast<fftw_complex*>(fftw_malloc( sizeof(fftw_complex)* nx * ny  ))),
      fout(reinterpret_cast<fftw_complex*>(fftw_malloc( sizeof(fftw_complex)* nx * ny  ))),
      docenter(docenter)
    {
      ENFORCE(_astromap_fftw_threads_init);
      fftw_plan_with_nthreads(threads);
      plan=ENFORCE( fftw_plan_dft_2d(nx,
				     ny, 
				     fin,
				     fout,
				     direction,
				     FFTW_MEASURE));
    }

    ~iFFTFact() 
    {
      fftw_free(fin);
      fftw_free(fout);
      fftw_destroy_plan( plan);
    }

    // now the functions that do the work

    /// Does the actuall tranform, leaves result in the fftScratch buffer
    void Transform(const Map &Amp, const Map &Phi ) {
            int mul = ( docenter == FFTFact::center ? -1 : 1 ) ;

            TransfPrep(&Amp[0], &Phi[0],
                       Amp.nx, Amp.ny,
                       mul,
                       &fin[0][0]);
  
	    fftw_execute(plan);
	    // Thats it... result should be in fftScratch
    }
    
    
    void AmpPhi(const Map &Amp, const Map &Phi,
		Map & resAmp, Map & resPhi,
		bool check=true ) 
    {

      Transform (Amp, Phi);

      unsigned  nx=Amp.nx;    
      unsigned  ny=Amp.ny;

      double mul;
      if (check)
      {
	mul = ( docenter == FFTFact::center ? -1.0 : 1.0 ) ;
      }
      else
      {
	mul = 1.0;
      }
      
      for (unsigned i =0 ; i < nx ; i++ ) 
	{
	  for (unsigned j=0 ; j < ny ; j++ ) 
	    {
	      resAmp[i*nx + j] = sqrt ( pow(fout[i*nx + j][0],2) + pow(fout[i*nx + j][1] , 2) ) ;
	      
	      if (i+j & 1) 
	      {	      
		resPhi[i*nx + j] = atan2( fout[i*nx + j][1] *mul, fout[i*nx + j][0]*mul ) ;
	      }
	      else
	      {
		resPhi[i*nx + j] = atan2( fout[i*nx + j][1], fout[i*nx + j][0] ) ;
	      }
	  
	}
      }
      
    }
    
    void AmpPhi(Map &Amp, Map &Phi,
		bool check)
    {
      AmpPhi(Amp, Phi, Amp, Phi,
	     check);
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
	      ResPower[i*nx + j] =  pow(fout[i*nx + j][0],2) + 
		pow(fout[i*nx + j][1] ,2)   ;
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

  FFTFact::FFTFact(const FFTFact &other):
    ip ( new  iFFTFact(other.nx,
		       other.ny,
		       other.dir,
		       other.docenter)),
    nx(other.nx),
    ny(other.ny),
    dir(other.dir),
    docenter(other.docenter)
  {
  }

  FFTFact *FFTFact::clone(void)
  {
    return new FFTFact(*this);
  }
  
  FFTFact::~FFTFact() 
  {
    delete ip;
  }

  void FFTFact::fftamphi(Map &Amp, Map &Phi,
			 bool check) 
  {
    ip->AmpPhi(Amp, Phi,
	       check);
  }

  void FFTFact::fftamphi(const Map &Amp, const Map &Phi,
			 Map &resAmp, Map &resPhi,
			 bool check)
  {
    ip->AmpPhi(Amp, Phi,
	       resAmp, resPhi,
	       check);
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
