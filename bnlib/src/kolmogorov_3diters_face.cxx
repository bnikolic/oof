/**
   \file kolmogorov_3diters_face.cxx
   
   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

*/

#include "kolmogorov_3diters_face.hxx"

namespace BNLib {

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

  bool K3FaceIterV2::pSkipFace(const K3DCenterItertor & ci,
			       size_t fcount)
  {
    if ( fcount == 0 && ( ! ci.firstDir(D_X) ) )
    {
      return true;
    }
    else if ( fcount == 2 && ( ! ci.firstDir(D_Y) ))
    {
      return true;
    }
    else if ( fcount == 4 && ( ! ci.firstDir(D_Z) ))
    {
      return true;
    }
    else
    {
      return false;
    }

  }
  
  void K3FaceIterV2::UpdateFace(void)
  {
    size_t di, dj, dk ;
    ci.getc( di,dj,dk);

    switch (fcount)
    {
    case 0 :
    case 1 :
      i = di + ( fcount  ? 1 : -1 ) * ci.origin();
      j = dj;
      k = dk;
      break;
    case 2 :
    case 3 :
      i = di;
      j = dj + ( fcount % 2 ? 1 : -1 ) * ci.origin();
      k = dk;
      break;
    case 4 :
    case 5 :
      i = di;
      j = dj;
      k = dk + ( fcount % 4 ? 1 : -1 ) * ci.origin();
      break;
    default:
      throw "Logic error";
    }
  }

  void K3FaceIterV2::next(void)
  {
    do {

      if ( fcount > 4 )
      {
	fcount = 0;
	ci.next();
	break;
      }
      else
      {
	++fcount;
      }
      
    } while ( pSkipFace( ci, fcount));


    UpdateFace()    ;

  }
  
  void K3FaceIterV2::ParentCentre(K3DParent * parents) const
  {
    ci.getc( parents[0].i, parents[0].j, parents[0].k );
  }

  void K3FaceIterV2::ParentFace(K3DParent * parents) const
  {
    const size_t o = ci.origin();
    for (size_t l =0 ; l < 4 ; ++l )
    {
      K3DParent & p = parents[l];

      switch (fcount)
      {
      case 0:
      case 1:
	p.i = i ;
	p.j = j + o * ( l & 2 ? -1 : 1 ) ;
	p.k = k + o * ( l & 1 ? -1 : 1 ) ;
	break;
      case 2:
      case 3:
	p.i = i + o * ( l & 1 ? -1 : 1 ) ;
	p.j = j ;
	p.k = k + o * ( l & 2 ? -1 : 1 ) ;
	break;
      case 4:
      case 5:
	p.i = i + o * ( l & 1 ? -1 : 1 ) ;
	p.j = j + o * ( l & 2 ? -1 : 1 ) ;
	p.k = k;
	break;      
      default:
	throw "Logic error";
      }
    }
  }

  void K3FaceIterV2::ParentOpposite(K3DParent * parents) const
  {

    K3DParent & opp = parents[0];
    ci.getc( opp.i, opp.j, opp.k );

    switch (fcount)
    {
    case 0 :
    case 1 :
      opp.i +=  ( fcount  ? 1 : -1 ) * ci.delta();
      break;
    case 2 :
    case 3 :
      opp.j +=  ( fcount % 2 ? 1 : -1 ) * ci.delta();
      break;
    case 4 :
    case 5 :
      opp.k +=  ( fcount % 4 ? 1 : -1 ) * ci.delta();
      break;
    default:
      throw "Logic error";
    }

  }

  const K3DParent * K3FaceIterV2::ParentListP(void) 
  {

    // Center of current is always a parent.
    ParentCentre(parents);
    
    // Then the four on the current face.
    ParentFace(parents + 1);

    // Finaly the oposite center
    ParentOpposite( parents + 5 );

    return parents;

  }

  K3FaceIterBalanced::K3FaceIterBalanced( size_t Nx, 
					  size_t Ny, 
					  size_t Nz , 
					  size_t o ):
    K3FaceIterV2(Nx, Ny, Nz, o)
  {

  }

  const K3DParent * K3FaceIterBalanced::FilteredParentP(size_t & np)
  {
    // Note that this is a modified version of the code that generates
    // all of the parents.
    
    // For the time being just return old value
    return K3FaceIterV2::FilteredParentP( np);

  }

}
