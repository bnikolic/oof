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

  std::vector<K3DParent> K3DIterBase::CopyParentList(void)
  {
    std::vector<K3DParent>  v;
    ParentList(v);
    return v;
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

  void K3DCenterItertor::ParentList( std::vector<K3DParent> & vOUT)
  {
    vOUT.resize(8);

    for (size_t l =0 ; l < 8 ; ++l )
    {
      vOUT[l].i = i + ( l & 1 ? 1 : -1 )  * origin(D_X);
      vOUT[l].j = j + ( l & 2 ? 1 : -1 )  * origin(D_Y);
      vOUT[l].k = k + ( l & 4 ? 1 : -1 )  * origin(D_Z);
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
    const size_t kdelta = delta(D_Z) >> 1;
    const size_t jdenom = delta(D_Y) >> 1;

    size_t jdelta;
    if (   k / kdelta   & 1 )
    {
      jdelta = delta(D_Y) >> 1;
    }
    else
    {
      jdelta= delta(D_Y);
    }

    i += delta(D_X);

    if ( i >= getd(D_X) )
    {
      j += jdelta;

      if ( j >= getd(D_Y) )      
      {
	k += kdelta;
      }
    }
    
    // now reset if necessary
    if ( j >= getd(D_Y) )      
    {
      if ( k/kdelta & 1 )
      {
	j =0;
      }
      else
      {
	j = origin(D_Y);
      }
    }

    if ( i >= getd(D_X) )
    {
      if ( j/jdenom + k/kdelta & 1 )
      {
	i = origin(D_X);
      }
      else
      {
	i = 0;
      }
    }
  }

  void K3FaceIter::ParentList( std::vector<K3DParent> & vOUT)
  {
    vOUT.resize(8);

    for (size_t l =0 ; l < 8 ; ++l )
    {

    }

  }

  K3FaceIterV2::K3FaceIterV2( size_t Nx, 
			      size_t Ny, 
			      size_t Nz , 
			      size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o),
    fcount(0),
    ci( Nx, Ny, Nz, o)
  {
    UpdateFace();
  }
  
  void K3FaceIterV2::UpdateFace(void)
  {
    size_t di, dj, dk ;
    ci.getc( di,dj,dk);

    switch (fcount)
    {
    case 0 :
    case 1 :
      i = di + ( fcount  ? 1 : -1 ) * ci.origin(D_X);
      j = dj;
      k = dk;
      break;
    case 2 :
    case 3 :
      i = di;
      j = dj + ( fcount % 2 ? 1 : -1 ) * ci.origin(D_Y);
      k = dk;
      break;
    case 4 :
    case 5 :
      i = di;
      j = dj;
      k = dk + ( fcount % 4 ? 1 : -1 ) * ci.origin(D_Z);
      break;
    default:
      throw "Logic error";
    }
  }

  void K3FaceIterV2::next(void)
  {
    if ( fcount > 4 )
    {
      fcount = 0;
      ci.next();
    }
    else
    {
      ++fcount;
    }
    UpdateFace()    ;

  }

  void K3FaceIterV2::ParentList( std::vector<K3DParent> & vOUT)
  {
    vOUT.resize(8);

    for (size_t l =0 ; l < 8 ; ++l )
    {

    }

  }


  K3EdgeIter::K3EdgeIter( size_t Nx, size_t Ny, size_t Nz , 
			  size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o)
  {
    i= origin( D_X);
    j= 0;
    k= 0;
  }

  size_t K3EdgeIter::origin(dirs d)
  {
    return getd(d) >> (o+1);
  }

  size_t K3EdgeIter::delta(dirs d)
  {
    return origin(d) << 1;
  }

  void K3EdgeIter::next(void)
  {

    const size_t kdelta = delta(D_Z) >> 1;
    const size_t jdenom = delta(D_Y) >> 1;

    size_t jdelta;
    
    if ( k /kdelta  & 1 )
    {
      jdelta = delta(D_Y);
    }
    else
    {
      jdelta = delta(D_Y) >> 1;
    }

    // First do the increments
    i += delta(D_X);
    if ( i >= getd(D_X) )
    {
      j += jdelta;

      if ( j >= getd(D_Y) )
      {
	k+= kdelta;
      }
    }
    
    // Now reset

    if ( j >= getd(D_Y) )
    {
      j=0;
    }

    if ( i >= getd(D_X) ) 
    {
      if ( (j/jdenom +  k / kdelta ) & 1 )
      {
	i = 0;
      }
      else
      {
	i = origin(D_X);
      }
    }



  }

  void K3EdgeIter::ParentList( std::vector<K3DParent> & vOUT)
  {
    vOUT.resize(8);
  }  

  K3EdgeIterV2::K3EdgeIterV2( size_t Nx, size_t Ny, size_t Nz , 
			      size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o),
    ecount(0),
    ci(Nx, Ny, Nz, o)
  {
    UpdateEdge();
  }

  void K3EdgeIterV2::UpdateEdge(void)
  {
    int kf    = ecount /9 ;
    int jf    = (ecount - kf*9) /3 ;

    int imult = ((int)ecount % 3) -1;

    int jmult =  jf -1;

    int kmult = ecount/4 -1;

    if ( kmult == 0 )
    {
      switch (ecount % 4 )
      {
      case 0:
	imult = 1; 
	jmult = 1;
	break;
      case 1:
	imult = 1; 
	jmult = -1;
	break;
      case 2:
	imult = -1; 
	jmult = 1;
	break;
      case 3:
	imult = -1; 
	jmult = -1;
	break;
      }
    }
    else
    {
      switch (ecount % 4) 
      {
      case 0:
	imult = 1; 
	jmult = 0;
	break;
      case 1:
	imult = -1; 
	jmult = 0;
	break;
      case 2:
	imult = 0; 
	jmult = 1;
	break;
      case 3:
	imult = 0; 
	jmult = -1;
	break;
      }
    }

    
    size_t di, dj, dk ;
    ci.getc( di,dj,dk);

    i = di + imult * ci.origin(D_X);
    j = dj + jmult * ci.origin(D_Y);
    k = dk + kmult * ci.origin(D_Z);
    
  }

  void K3EdgeIterV2::next(void)
  {
    if ( ecount > 10 )
    {
      ecount = 0;
      ci.next();
    }
    else
    {
      ++ecount;
    }
    UpdateEdge()    ;

  }

  void K3EdgeIterV2::ParentList( std::vector<K3DParent> & vOUT)
  {
    vOUT.resize(8);
  }  
  
}
