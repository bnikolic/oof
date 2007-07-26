/**
   \file kolmogorov_3diters.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007
*/

#include "kolmogorov_3diters.hxx"

#include <cmath>

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

  size_t K3DIterBase::getd( dirs d) const
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
  
  void K3DIterBase::setOutOfBounds(void)
  {
    i= getd(D_X);
    j= getd(D_Y);
    k= getd(D_Z);
  }

  void K3DIterBase::ParentList( std::vector<K3DParent> & vOUT) 
  {
    const size_t np =nParents() ;
    const K3DParent * parents= ParentListP();

    vOUT.resize(np);

    for( size_t i =0 ; i < np ; ++i )
    {
      vOUT[i]= parents[i];
    }
  }

  void K3DIterBase::FilteredParentList(std::vector<K3DParent> & vOUT)
  {
    const size_t np =nParents() ;
    vOUT.resize(np);

    const K3DParent * pparents = ParentListP();

    size_t j=0;
    for (size_t i =0 ; i < np ; ++i)
    {
      const K3DParent &p = pparents[i];
      if (p.i >=0 and p.i < Nx and 
	  p.j >=0 and p.j < Ny and 
	  p.k >=0 and p.k < Nz )
      {
	vOUT[j] = p;
	++j;
      }
    }
    vOUT.resize(j);
  }

  std::vector<K3DParent> K3DIterBase::CopyParentList(void)
  {
    std::vector<K3DParent>  v;
    ParentList(v);
    return v;
  }

  std::vector<K3DParent> K3DIterBase::CopyFilteredParentList(void)
  {
    std::vector<K3DParent>  v;
    FilteredParentList(v);
    return v;
  }

  K3DCenterItertor::K3DCenterItertor( size_t Nx, size_t Ny, size_t Nz , 
				      size_t o ) :
    
    K3DIterBase( Nx, Ny, Nz, o)
  {
    i= origin();
    j= origin();
    k= origin();
  }

  size_t K3DCenterItertor::origin(void) const
  {
    return getd(D_X) >> (o+1);
  }

  size_t K3DCenterItertor::delta(void) const
  {
    return getd(D_X) >> o;
  }

  bool K3DCenterItertor::firstDir(dirs d) const
  {
    if ( d == D_X )
    {
      return (i == origin() ) ;
    }
    else if ( d == D_Y)
    {
      return (j == origin() ) ;
    }
    else
    {
      return (k == origin() ) ;
    }
  }

  void K3DCenterItertor::next(void)
  {
    i += delta();
    if ( i >= getd(D_X) )
    {
      i = origin();

      j += delta();
      if ( j >= getd(D_Y) )
      {
	j=origin();
	k+= delta();
      }
    }
  }

  const K3DParent * K3DCenterItertor::ParentListP(void) 
  {
    for (size_t l =0 ; l < np ; ++l )
    {
      parents[l].i = i + ( l & 1 ? 1 : -1 )  * origin();
      parents[l].j = j + ( l & 2 ? 1 : -1 )  * origin();
      parents[l].k = k + ( l & 4 ? 1 : -1 )  * origin();
    }

    return parents;

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
  const K3DParent * K3FaceIterV2::ParentListP(void) 
  {

    // Center of current is always a parent.
    ci.getc( parents[0].i, parents[0].j, parents[0].k );
    
    // Then the four on the current face.
    for (size_t l =0 ; l < 4 ; ++l )
    {
      K3DParent & p = parents[l+1];

      switch (fcount)
      {
      case 0:
      case 1:
	p.i = i ;
	p.j = j + ci.origin() * ( l & 2 ? -1 : 1 ) ;
	p.k = k + ci.origin() * ( l & 1 ? -1 : 1 ) ;
	break;
      case 2:
      case 3:
	p.i = i + ci.origin() * ( l & 1 ? -1 : 1 ) ;
	p.j = j ;
	p.k = k + ci.origin() * ( l & 2 ? -1 : 1 ) ;
	break;
      case 4:
      case 5:
	p.i = i + ci.origin() * ( l & 1 ? -1 : 1 ) ;
	p.j = j + ci.origin() * ( l & 2 ? -1 : 1 ) ;
	p.k = k;
	break;      
      default:
	throw "Logic error";
      }
    }

    // Finaly the oposite center
    K3DParent & opp = parents[5];
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
    
    return parents;

  }


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
	p.i += ( l  ? 1 : -1 ) * ci.origin();
	break;
      case 2 :
      case 3 :
	p.j += ( l % 2 ? 1 : -1 ) * ci.origin();
	break;
      case 4 :
      case 5 :
	p.k +=  ( l % 4 ? 1 : -1 ) * ci.origin();
	break;
      default:
	throw "Logic error";
      }
    }
    return parents;
  }  

  double KAverageParents( const double * cube,
			  size_t Nx,
			  size_t Ny,
			  const  std::vector<K3DParent> & pv)
  {
    double res = 0;
    const size_t N2 = Nx*Ny;
    for (size_t i = 0; i < pv.size() ; ++ i )
    {
      size_t dx=pv[i].i +pv[i].j*Nx + pv[i].k *N2;
      res += cube[dx];
    }
    return res / pv.size();

  }
  
}
