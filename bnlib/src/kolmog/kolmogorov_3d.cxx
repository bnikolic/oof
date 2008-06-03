/**
   \file kolmogorov_3d.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   


*/

#include "kolmogorov_3d.hxx"

#include <cmath>
#include <vector>
#include <map>
#include <memory>

#include "bnrandom.hxx"
#include "kolmogorov_3diters.hxx"
#include "kolmogorov_3diters_face.hxx"
#include "kolmogorov_3diters_edge.hxx"
#include "kolmogorov_3diters_t.hxx"

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

  /** Define edges on the cube
   */
  static edge cubeedges[12] = {
    {0,0,0, 1,0,0 },
    {0,0,0, 0,1,0 },
    {1,1,0, 1,0,0 },
    {1,1,0, 0,1,0 },
    {0,0,1, 1,0,1 },
    {0,0,1, 0,1,1 },
    {1,1,1, 1,0,1 },
    {1,1,1, 0,1,1 },
    {0,0,0, 0,0,1 },
    {1,0,0, 1,0,1 },
    {0,1,0, 0,1,1 },
    {1,1,0, 1,1,1 } };


  static edge cubebodydiagas[4] = {
    { 0, 0, 0,  1, 1, 1 }, 
    { 1, 0, 0,  0, 1, 1 }, 
    { 0, 1, 0,  1, 0, 1 }, 
    { 1, 1, 0,  0, 0, 1 } 
  };

  static void K3CheckParams( size_t Nx,
			     size_t Ny,
			     size_t Nz);


  /**
     This generates the corenrs using the old F, Body, Body (even)
     algorithm which does not seem to have the correct statistics.
  */
  template<class T>
  void TKolmogorovCorners3DFBB(T *cube,
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



  template<class T>
  void TKolmogorovCorners3D(T *cube,
			    size_t N,
			    RDist &rfn)
  {
    
    const size_t N2 = size_t(pow(N,2));

    const double edgestddev      = 1.23589948;
    const double facediagstddev  = 1.43145595;
    const double bodydiagstddev  = 2.13492543;

    // Iterate on edges first
    for (size_t l = 0 ; l < 12 ; ++l)
    {
      double f = edgestddev * rfn.sample() * 0.5;
      
      size_t dx1 = cubeedges[l].i1 *(N-1) + 
	cubeedges[l].j1 *N *(N-1) + 
	cubeedges[l].k1 *N2 *(N-1);

      size_t dx2 = cubeedges[l].i2 *(N-1) +
	cubeedges[l].j2 *N *(N-1) + 
	cubeedges[l].k2 *N2*(N-1);
      
      // Note that we are making this an "even" process, i.e. both
      // points connected by the edge are assigned with same sign
      cube[dx1] += f;
      cube[dx2] += f;      

    }

    // Next iterate on body diagonals
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
    
    // Finally on body diagonals
    for (size_t l = 0 ; l < 4 ; ++l)
    {
      double f = bodydiagstddev * rfn.sample() * 0.5;
      
      size_t dx1 = cubebodydiagas[l].i1 *(N-1) +
	cubebodydiagas[l].j1 *N *(N-1) + 
	cubebodydiagas[l].k1 *N2*(N-1) ;
      size_t dx2 = cubebodydiagas[l].i2 * (N-1) +
	cubebodydiagas[l].j2 * N * (N-1) + 
	cubebodydiagas[l].k2 * N2 * (N-1);

      cube[dx1] += f;
      cube[dx2] -= f;

    }

  }

  void Kolmog::KolmogorovCorners3D(double *cube,
				   size_t N,
				   RDist &rfn)
  {
    return TKolmogorovCorners3D(cube, N, rfn);
  }

  size_t Kolmogorov3D( double * cube,
		       size_t N,
		       RDist &rfn)
  {
    return Kolmogorov3D( cube, N,N,N,
			 rfn);
  }

  /** Cache values of variances.
  */
  class VarianceCache {
    size_t o;
    double  (* fn )(size_t, size_t)  ;
    std::map<size_t, double> varmap;
  public:
    VarianceCache(size_t o,
		  double (*fn)(size_t, size_t)) : o(o), fn(fn) {};
    
    double operator() (size_t np )
    {
      double v;
      if ( varmap.count(np) )
      { 
	v= varmap[np];
      }
      else
      {
	v=fn(np, o);
	varmap[np]=v;
      }
      return v;
    }
  };

  template<class T>
  void TKMagnifyGrid(T *og,
		     const size_t N,
		     T *dd,
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


  template<class T>
  size_t TKolmogorov3D( T * cube,
			size_t Nx,
			size_t Ny,
			size_t Nz,
			RDist &rfn,
			Kolmgorov3DOptions opt) throw (const char *)
  {
    using namespace Kolmog;

    memset( cube, 0 , Nx*Ny*Nz*sizeof(T) );

    K3CheckParams(Nx,Ny,Nz);

    // Order of iteration (if using subgrid method than this will not
    // start at 0, hence out of the for loop)
    size_t o =0;

    if (Nx == Ny && Nx == Nz )
    {

      if ( opt & KInitialFBB )
      {
	TKolmogorovCorners3DFBB(cube, Nx, rfn);
      }
      else
      {
	TKolmogorovCorners3D(cube, Nx, rfn);
      }
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
      
      std::vector<T> subgrid ( Nsub*Nsub*Nsub);
      o=TKolmogorov3D( & subgrid[0],
		       Nsub,
		       Nsub,
		       Nsub,
		       rfn,
		       opt);

      TKMagnifyGrid( & subgrid[0],
		     Nsub,
		     cube,
		     Nx,
		     Ny,
		     Nz);

      


    }

    const size_t N2 = Nx*Ny;

    for(  ; ( ((size_t)1) << (o+1) ) < Nx  ; ++o )
    {
      
      {
	K3DCenterItertor ci(Nx,Ny,Nz, o);
	VarianceCache cvc(o, KMidPointVar_CI);
	while ( ci.inBounds() )
	{
	  size_t i,j, k;
	  ci.getc( i,j, k);
	  size_t dx= k* N2 + j *Nx + i;

	  size_t np;
	  const K3DParent * cpv = ci.FilteredParentP(np);

	  double val;
	  if ( opt & KWeightedInterp ) 
	  {
	    K3DParent cp = {i,j,k};
	    val = TKWeightedAverageParents(cube, Nx, Ny, cpv, cp, np);
	  }
          else
	  {
	    val = TKAverageParents(cube, Nx, Ny, cpv, np);
	  }
	  
	  val += cvc( np ) * rfn.sample();
	  
	  cube[dx]=val;
	  
	  ci.next();
	  
	}
      }

      {
	std::auto_ptr<K3FaceIterV2> fi;
	if ( opt & KBalancedIters )
	  fi.reset( new K3FaceIterBalanced (Nx,Ny,Nz, o) );
	else
	  fi.reset( new K3FaceIterV2 (Nx,Ny,Nz, o) ) ;

	VarianceCache fvc(o, KMidPointVar_FI);
	while ( fi->inBounds() )
	{

	  size_t i,j, k;
	  fi->getc( i,j, k);
	  size_t dx= k* N2 + j *Nx + i;

	  size_t np;
	  const K3DParent * fpv = fi->FilteredParentP(np);
	  
	  double val;
	  if ( opt & KWeightedInterp ) 
	  {
	    K3DParent cp = {i,j,k};
	    val = TKWeightedAverageParents(cube, Nx, Ny, fpv, cp, np);
	  }
          else
	  {
	    val= TKAverageParents(cube, Nx, Ny, fpv, np);
	  }
	  
	  val += fvc( np ) * rfn.sample();
	  
	  cube[dx]=val;
	  
	  fi->next();
	  
	}
      }

      {
	std::auto_ptr<K3EdgeIterV2> ei;
	if ( opt & KEdgeBalanced)
	  ei.reset( new K3EdgeIterBalanced(Nx,Ny,Nz, o) );
	else
	  ei.reset( new K3EdgeIterV2(Nx,Ny,Nz, o) );
	VarianceCache evc(o, KMidPointVar_EI);
	while ( ei->inBounds() )
	{
	  size_t i,j, k;
	  ei->getc( i,j, k);
	  size_t dx= k* N2 + j *Nx + i;
	  
	  size_t np;
	  const K3DParent * epv = ei->FilteredParentP(np);
	  
	  double val;
	  if ( opt & KWeightedInterp ) 
	  {
	    K3DParent cp = {i,j,k};
	    val = TKWeightedAverageParents(cube, Nx, Ny, epv, cp, np);
	  }
          else
	  {
	    val = TKAverageParents(cube, Nx, Ny, epv, np);
	  }

	  val += evc( np ) * rfn.sample();
	  
	  cube[dx]=val;
	  
	  ei->next();
	  
	}
      }
    }
    return o;
  }

  size_t Kolmogorov3D( double * cube,
		       size_t Nx,
		       size_t Ny,
		       size_t Nz,
		       RDist &rfn,
		       Kolmgorov3DOptions opt) throw (const char *)
  {
    return TKolmogorov3D(cube, Nx, Ny, Nz, rfn, opt);
  }

  size_t Kolmogorov3DF( float * cube,
			size_t Nx,
			size_t Ny,
			size_t Nz,
			RDist &rfn)
  {
    return TKolmogorov3D(cube, Nx, Ny, Nz, rfn,KInitialEFB);
  }


  double  Kolmog::KMidPointVar_CI( size_t np,
				   size_t o)
  {
    
    double res;
    switch (np)
    {
    case 8:
      res= 1.64785599181;
      break;
    default:
      throw "Logic error: center cell iterator should always have eight parents";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }

  double  Kolmog::KMidPointVar_FI( size_t np,
				   size_t o)
  {
    
    double res;
    switch (np)
    {
    case 6:
      res= 1.4999830720263603;
      break;
    case 5:
      res=1.559617679005423;
      break;
    case 4:
      res=1.63006978865;
      break;
    default:
      throw "Logic error in KMidPointVar_FI:\
 don't know the variance for that many parent points";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }

  double  Kolmog::KMidPointVar_EI( size_t np,
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
    case 2:
      res= 1.6168266486;
      break;
    default:
      throw "Logic error in EdgePointVariances";
    }
    res = res * pow ( 1.0 / ( 1 << o) , 2.0/ 6.0);
    return res;
  }


  void Kolmog::KMagnifyGrid(double *og,
		    const size_t N,
		    double *dd,
		    const size_t Nx,
		    const size_t Ny,
		    const size_t Nz)
  {
    return TKMagnifyGrid  (og, N,
			   dd, 
			   Nx,Ny,Nz);
  }  

  bool Kolmog::pTwoNPlustOne(unsigned n)
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

    using namespace Kolmog;

    if ( not ( pTwoNPlustOne(Nx) && 
	       pTwoNPlustOne(Ny) &&
	       pTwoNPlustOne(Nz) )) 
    {
      throw "Parameters to 3d Kolmogorov generation must be of form 2^n+1";
    }

  }


}



