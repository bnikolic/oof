/**
   \file kolmogorov_3diters.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007
*/

#include "kolmogorov_3diters.hxx"

namespace BNLib {

  K3DIterBase::K3DIterBase( size_t Nx, size_t Ny, size_t Nz , size_t o ):
    Nx(Nx),
    Ny(Ny),
    Nz(Nz),
    o(o)
  {

  }
  bool K3DIterBase::inBounds(void)
  {
    return ( i < Nx &&
	     j < Ny &&
	     k < Nz );
  }

  void K3DIterBase::getc( size_t & iOUT,
			  size_t & jOUT,
			  size_t & kOUT )
  {
    iOUT=i; 
    jOUT=j;
    kOUT=k;
  }

  size_t K3DIterBase::getd( dirs d)
  {
    if ( d== D_X)
    {
      return Nx;
    }
    else if ( d==D_Y )
    {
      return Ny ; 
    }
    else if ( d== D_Z)
    {
      return Nz ;
    }
    else 
    {
      throw "Unknown dimension";
    }
	      
  }

  K3DCenterItertor::K3DCenterItertor( size_t Nx, size_t Ny, size_t Nz , 
				      size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o)
  {
    i= origin( D_X);
    j= origin( D_Y);
    k= origin( D_Z);
  }

  size_t K3DCenterItertor::origin(dirs d)
  {
    return getd(d) >> (o+1);
  }

  size_t K3DCenterItertor::delta(dirs d)
  {
    return getd(d) >> o;
  }

  void K3DCenterItertor::next(void)
  {
    i += delta(D_X);
    if ( i >= getd(D_X) )
    {
      i = origin(D_X);

      j += delta(D_Y);
      if ( j >= getd(D_Y) )
      {
	j=origin(D_Y);
	k+= delta(D_Z);
      }
    }
  }

  K3FaceIter::K3FaceIter( size_t Nx, size_t Ny, size_t Nz , 
			  size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o)
  {
    i= origin( D_X);
    j= origin( D_Y);
    k= 0;
  }

  size_t K3FaceIter::origin(dirs d)
  {
    return getd(d) >> (o+1);
  }

  size_t K3FaceIter::delta(dirs d)
  {
    return origin(d) << 1;
  }

  void K3FaceIter::next(void)
  {
    i += delta(D_X);
    if ( i >= getd(D_X) )
    {
      size_t jdelta;
      if ( (k / (delta(D_Z) >> 1) ) & 1  )
      {
	jdelta = delta(D_Y) >> 1;
      }
      else
      {
	jdelta = delta(D_Y);
      }

      j += jdelta;

      if ( (j/jdelta ) & 1 )
      {
	i = 0;
      }
      else
      {
	i = origin(D_X);
      }

      if ( j >= getd(D_Y) )
      {
	k+= delta(D_Z) >> 1;
	if ( (k / (delta(D_Z) >> 1) ) & 1 )
	{
	  i = origin(D_X);
	  j = 0;
	}
	else
	{
	  i= origin( D_X);
	  j= origin( D_Y);
	}

      }
    }
  }

  
  
}
