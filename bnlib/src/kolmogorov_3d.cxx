/**
   \file kolmogorov_3d.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   


*/

#include "kolmogorov_3d.hxx"

#include <cmath>
#include <vector>

#include "bnrandom.hxx"
#include "kolmogorov_3diters.hxx"

namespace BNLib {

  struct edge {
    // First vertex of edge
    int i1, j1, k1;
    // Second vertex
    int i2, j2, k2;
  };

  
  /**
     Define diagonals on the faces of the cube.  List is automatically
     generated in kolmogorovmidpoint.py.
  */
  static edge cubefacediags[12]= { 
    { 0, 0, 0,  1, 1, 0 }, 
    { 1, 0, 0,  0, 1, 0 }, 
    { 0, 0, 1,  1, 1, 1 }, 
    { 1, 0, 1,  0, 1, 1 }, 
    { 0, 0, 0,  0, 1, 1 }, 
    { 0, 1, 0,  0, 0, 1 }, 
    { 1, 0, 0,  1, 1, 1 }, 
    { 1, 1, 0,  1, 0, 1 }, 
    { 0, 0, 0,  1, 0, 1 }, 
    { 0, 0, 1,  1, 0, 0 }, 
    { 0, 1, 0,  1, 1, 1 }, 
    { 0, 1, 1,  1, 1, 0 }
  };

  static edge cubebodydiagas[4] = {
    { 0, 0, 0,  1, 1, 1 }, 
    { 1, 0, 0,  0, 1, 1 }, 
    { 0, 1, 0,  1, 0, 1 }, 
    { 1, 1, 0,  0, 0, 1 } 
  };

  static void K3CheckParams( size_t Nx,
			     size_t Ny,
			     size_t Nz);



  void KolmogorovCorners3D(double *cube,
			   size_t N,
			   RDist &rfn)
  {
    
    const size_t N2 = size_t(pow(N,2));
    
    const double facediagstddev  = 1.09186593;
    
    const double bodydiagstddev  = 2.8520905;
    const double bodydiag_even_stddev  = 0.71572797;
    
    for (size_t l = 0 ; l < 12 ; ++l)
    {
      double f = facediagstddev * rfn.sample() * 0.5;
      
      size_t dx1 = cubefacediags[l].i1 *(N-1) + 
	cubefacediags[l].j1 *N *(N-1) + 
	cubefacediags[l].k1 *N2 *(N-1);

      size_t dx2 = cubefacediags[l].i2 *(N-1) +
	cubefacediags[l].j2 *N *(N-1) + 
	cubefacediags[l].k2 *N2*(N-1);

      cube[dx1] += f;
      cube[dx2] -= f;
    }

    for (size_t l = 0 ; l < 4 ; ++l)
    {
      double f = bodydiagstddev * rfn.sample() * 0.5;
      double g = bodydiag_even_stddev * rfn.sample() ;
      
      size_t dx1 = cubebodydiagas[l].i1 *(N-1) +
	cubebodydiagas[l].j1 *N *(N-1) + 
	cubebodydiagas[l].k1 *N2*(N-1) ;
      size_t dx2 = cubebodydiagas[l].i2 * (N-1) +
	cubebodydiagas[l].j2 * N * (N-1) + 
	cubebodydiagas[l].k2 * N2 * (N-1);

      cube[dx1] += f;
      cube[dx2] -= f;

      cube[dx1] += g;
      cube[dx2] += g;
    }

  }

  size_t Kolmogorov3D( double * cube,
		       size_t N,
		       RDist &rfn)
  {
    return Kolmogorov3D( cube, N,N,N,
			 rfn);
  }

  size_t Kolmogorov3D( double * cube,
		     size_t Nx,
		     size_t Ny,
		     size_t Nz,
		     RDist &rfn) throw (const char *)
  {

    K3CheckParams(Nx,Ny,Nz);

    // Order of iteration (if using subgrid method than this will not
    // start at 0, hence out of the for loop)
    size_t o =0;

    if (Nx == Ny && Nx == Nz )
    {
      KolmogorovCorners3D(cube, Nx, rfn);
    }
    else
    {
      // Need to create a subgrid.

      unsigned mag;
      if ( Ny > Nz )
      {
	mag = (Nx-1) / (Nz -1 );
      }
      else
      {
	mag = (Nx-1) / (Ny -1 );
      }
      
      size_t Nsub = mag +1;
      
      std::vector<double> subgrid ( Nsub*Nsub*Nsub);
      o=Kolmogorov3D( & subgrid[0],
		      Nsub,
		      rfn);

      KMagnifyGrid( & subgrid[0],
		    Nsub,
		    cube,
		    Nx,
		    Ny,
		    Nz);

      


    }

    const size_t N2 = Nx*Ny;

    for(  ; ( ((size_t)1) << (o+1) ) < Nx  ; ++o )
    {
      
      K3DCenterItertor ci(Nx,Ny,Nz, o);
      while ( ci.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	ci.getc( i,j, k);
	size_t dx= k* N2 + j *Nx + i;

	ci.FilteredParentList(pv);

	double val = KAverageParents(cube, Nx, Ny, pv);

	val += KMidPointVar_CI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	ci.next();

      }

      K3FaceIterV2 fi(Nx,Ny,Nz, o);
      while ( fi.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	fi.getc( i,j, k);
	size_t dx= k* N2 + j *Nx + i;

	fi.FilteredParentList(pv);

	double val = KAverageParents(cube, Nx, Ny, pv);

	val += KMidPointVar_FI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	fi.next();

      }

      K3EdgeIterV2 ei(Nx,Ny,Nz, o);
      while ( ei.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	ei.getc( i,j, k);
	size_t dx= k* N2 + j *Nx + i;

	ei.FilteredParentList(pv);
	
	double val = KAverageParents(cube, Nx, Ny, pv);

	val += KMidPointVar_EI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	ei.next();

      }
    }
    return o;
  }


  double  KMidPointVar_CI( size_t np,
			   size_t o)
  {
    
    double res;
    switch (np)
    {
    case 8:
      res=2.06434648615;
      break;
    default:
      throw "Logic error: center cell iterator should always have eight parents";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }

  double  KMidPointVar_FI( size_t np,
			   size_t o)
  {
    
    double res;
    switch (np)
    {
    case 6:
      res= 1.29278759904;
      break;
    case 5:
      res= 1.35819897457;
      break;
    default:
      throw "Logic error";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }

  double  KMidPointVar_EI( size_t np,
			   size_t o)
  {
    
    double res;
    switch (np)
    {
    case 6:
      res= 1.39304529911;
      break;
    case 5:
      res= 1.40696258599;
      break;
    case 4:
      res= 1.42135665233;
      break;
    default:
      throw "Logic error";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }

  void KMagnifyGrid(double *og,
		    const size_t N,
		    double *dd,
		    const size_t Nx,
		    const size_t Ny,
		    const size_t Nz)
  {
    
    // Magnification
    unsigned mag = (Nx-1)/(N-1);

    for (size_t ok =0 ; ok < N ; ++ ok)
    {
      const size_t k = mag * ok ;
      if ( k >= Nz )
      {
	break;
      }
      for (size_t oj=0 ; oj < N ; ++ oj)
      {
	const size_t j = mag * oj;
	if ( j >= Ny )
	{
	  break;
	}
	for (size_t oi = 0 ; oi < N ; ++ oi )
	{
	  const size_t i = mag * oi;
	  if ( i >= Nx)
	  {
	    break;
	  }
	  dd[i+ j * Nx + k *Nx*Ny] = og[oi+oj*N+ok*N*N];
	}
      }
    }

  }

  

  bool pTwoNPlustOne(unsigned n)
  {
    // must be odd 
    if (  not ( n  & 1 )  ) 
    {
      return false ;
    }

    // look for first non zero bit
    do 
    {
      n = n >> 1;
    } while (  not (n & 1 ) );
    
    // all remaining bits must now be zero
    if ( n >> 1   )
    {
      // other non zero bits
      return false;
    }
    else
    {
      return true;
    }

  }

  static void K3CheckParams( size_t Nx,
			     size_t Ny,
			     size_t Nz)
  {
    
    if ( not ( pTwoNPlustOne(Nx) && 
	       pTwoNPlustOne(Ny) &&
	       pTwoNPlustOne(Nz) )) 
    {
      throw "Parameters to 3d Kolmogorov generation must be of form 2^n+1";
    }

  }

}



