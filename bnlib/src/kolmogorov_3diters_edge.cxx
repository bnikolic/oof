/**
   \file kolmogorov_3diters_edge.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 
   

*/

#include "kolmogorov_3diters_edge.hxx"

namespace BNLib {

  K3EdgeIterV2::K3EdgeIterV2( size_t Nx, size_t Ny, size_t Nz , 
			      size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o),
    ecount(0),
    ci(Nx, Ny, Nz, o)
  {
    UpdateEdge();
  }

  void K3EdgeIterV2::CalcIJKMult( int & imult, 
				  int & jmult,
				  int & kmult) const
  {
    kmult = ecount/4 -1;

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
      default:
	throw "logic error";
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
      default:
	throw "logic error";
      }
    }

  }

  void K3EdgeIterV2::UpdateEdge(void)
  {
    int imult ;
    int jmult ;
    int kmult ;

    CalcIJKMult( imult, jmult, kmult);

    size_t di, dj, dk ;
    ci.getc( di,dj,dk);

    i = di + imult * ci.origin();
    j = dj + jmult * ci.origin();
    k = dk + kmult * ci.origin();
    
  }

  bool K3EdgeIterV2::pSkipEdge(void) const
  {
    
    int imult ;
    int jmult ;
    int kmult ;

    CalcIJKMult( imult, jmult, kmult);    

    if ( imult == -1 && ( ! ci.firstDir(D_X) ) )
    {
      return true;
    }
    else if ( jmult == -1 && ( ! ci.firstDir(D_Y) ) )
    {
      return true;
    }
    else if  ( kmult == -1 && ( ! ci.firstDir(D_Z) ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  void K3EdgeIterV2::next(void)
  {

    do {
      
      if ( ecount > 10 )
      {
	ecount = 0;
	ci.next();
	break;
      }
      else
      {
	++ecount;
      }
    }
    while  ( pSkipEdge() );
    UpdateEdge()    ;

  }

  const K3DParent * K3EdgeIterV2::ParentListP(void) 
  {
    
    ParentOnDir(& parents[0], D_X);
    ParentOnDir(& parents[2], D_Y);
    ParentOnDir(& parents[4], D_Z);

    return parents;
  }  

  void K3EdgeIterV2::ParentOnDir( K3DParent * parents,
				  dirs d) const
  {
    const size_t o = ci.origin();
    
    for ( size_t l = 0 ; l < 2 ; ++l )
    {
      K3DParent & p = parents[l];
      p.i=i;
      p.j=j;
      p.k=k;

      int offset = ( l  ? 1 : -1 ) * o ;

      switch (d)
      {
      case D_X:
	p.i += offset;
	break;
      case D_Y :
	p.j += offset;
	break;
      case D_Z:
	p.k += offset;
	break;
      default:
	throw "logic error";
      }
    }

  }

  K3EdgeIterBalanced::K3EdgeIterBalanced( size_t Nx, size_t Ny, size_t Nz , 
					  size_t o ):
    K3EdgeIterV2( Nx , Ny, Nz, o)
  {

  }

  const K3DParent * K3EdgeIterBalanced::FilteredParentP(size_t & np)
  {
    K3DParent * fp = FilteredParentBuffer();
    size_t cp =0;

    if ( i != 0 && i != Nx-1 )
    {
      ParentOnDir(& fp[cp], D_X);
      cp +=2;
    }

    if ( j != 0 && j != Ny-1 )
    {
      ParentOnDir(& fp[cp], D_Y);
      cp +=2;
    }

    if ( k != 0 && k != Nz-1 )
    {
      ParentOnDir(& fp[cp], D_Z);
      cp +=2;
    }
    
    np=cp;

    return fp;


  }
  
}

