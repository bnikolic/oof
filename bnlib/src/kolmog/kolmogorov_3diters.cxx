/**
   \file kolmogorov_3diters.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007
*/

#include "kolmogorov_3diters.hxx"

#include <cmath>

#include "kolmogorov_3diters_t.hxx"

namespace BNLib {
  namespace Kolmog {

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

  void K3DIterBase::setOutOfBounds(void)
  {
    i= Nx;
    j= Ny;
    k= Nz;
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
  const K3DParent * K3DIterBase::FilteredParentP(size_t & np_filtered)
  {
    const size_t np =nParents() ;
    const K3DParent * pparents = ParentListP();
    
    // Result goes here. Derived classes have allocated enough space.
    K3DParent * res= FilteredParentBuffer();

    size_t j=0;
    for (size_t i =0 ; i < np ; ++i)
    {
      const K3DParent &p = pparents[i];
      if (p.i >=0 and p.i < Nx and 
	  p.j >=0 and p.j < Ny and 
	  p.k >=0 and p.k < Nz )
      {
	res[j] = p;
	++j;
      }
    }
    np_filtered=j;
    return res;
  }

  void K3DIterBase::FilteredParentList(std::vector<K3DParent> & vOUT)
  {
    size_t np_filt;
    const K3DParent * filt_p = FilteredParentP(np_filt);
    vOUT.resize(np_filt);

    for ( size_t i =0 ; i< np_filt ; ++i )
    {
      vOUT[i]=filt_p[i];
    }

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
    if ( i >= Nx )
    {
      i = origin();

      j += delta();
      if ( j >= Ny )
      {
	j=origin();
	k+= delta();
      }
    }
  }

  const K3DParent * K3DCenterItertor::ParentListP(void) 
  {
    const size_t o = origin();
    for (size_t l =0 ; l < np ; ++l )
    {
      parents[l].i = i + ( l & 1 ? 1 : -1 )  * o;
      parents[l].j = j + ( l & 2 ? 1 : -1 )  * o;
      parents[l].k = k + ( l & 4 ? 1 : -1 )  * o;
    }

    return parents;

  }




  double KAverageParents( const double * cube,
			  size_t Nx,
			  size_t Ny,
			  const  std::vector<K3DParent> & pv)
  {
    return KAverageParents(cube, Nx, Ny,
			   & pv[0], 
			   pv.size() );

  }

  double KAverageParents( const double * cube,
			  size_t Nx,
			  size_t Ny,
			  const  K3DParent * pv,
			  size_t np)
  {
    return TKAverageParents( cube, Nx, Ny, pv ,np);
  }
  }}
