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
    const size_t o = ci.origin();
    for ( size_t l = 0 ; l < 6 ; ++l )
    {
      K3DParent & p = parents[l];
      p.i=i;
      p.j=j;
      p.k=k;
      
      switch (l)
      {
      case 0 :
      case 1 :
	p.i += ( l  ? 1 : -1 ) * o;
	break;
      case 2 :
      case 3 :
	p.j += ( l % 2 ? 1 : -1 ) * o;
	break;
      case 4 :
      case 5 :
	p.k +=  ( l % 4 ? 1 : -1 ) * o;
	break;
      default:
	throw "Logic error";
      }
    }
    return parents;
  }  
}

