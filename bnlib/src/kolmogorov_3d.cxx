/**
   \file kolmogorov_3d.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   


*/

#include "kolmogorov_3d.hxx"

#include <cmath>
#include <iostream>

#include "bnrandom.hxx"
#include "kolmogorov_3diters.hxx"

namespace BNLib {

  struct vertex {
    int i,j,k ; 
  };

  struct edge {
    // First vertex of edge
    int i1, j1, k1;
    // Second vertex
    int i2, j2, k2;
  };

  static vertex cubevertices[8]= {
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {1,1,0},
    {0,0,1},
    {1,0,1},
    {0,1,1},
    {1,1,1}
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



  void KolmogorovCorners3D(double *cube,
			   size_t N,
			   RDist &rfn)
  {
    
    const size_t N2 = int(pow(N,2));
    
    const double vrtexstddev = 0;
    const double facediagstddev  = 1.09186593;
    
    const double bodydiagstddev  = 2.8520905;
    const double bodydiag_even_stddev  = 0.71572797;
    
    /*
    for (size_t l =0 ; l < 8 ; ++l)
    {
      size_t dx= cubevertices[l].i * (N-1) + 
	cubevertices[l].j * N *(N-1) + 
	cubevertices[l].k *N2 *(N-1);
      cube[dx] = vrtexstddev * rfn.sample();
    }
    
    */

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

  void Kolmogorov3D( double * cube,
		     size_t N,
		     RDist &rfn)
  {

    KolmogorovCorners3D(cube, N, rfn);
    const size_t N2 = (size_t)pow(N,2);

    for( size_t o =0 ; ( ((size_t)1) << (o+1) ) < N  ; ++o )
    {
      
      K3DCenterItertor ci(N,N,N, o);
      while ( ci.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	ci.getc( i,j, k);
	size_t dx= k* N2 + j *N + i;

	ci.FilteredParentList(pv);

	double val = KAverageParents(cube, N, pv);

	val += KMidPointVar_CI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	ci.next();

      }

      K3FaceIterV2 fi(N,N,N, o);
      while ( fi.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	fi.getc( i,j, k);
	size_t dx= k* N2 + j *N + i;

	fi.FilteredParentList(pv);

	double val = KAverageParents(cube, N, pv);

	val += KMidPointVar_FI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	fi.next();

      }

      K3EdgeIterV2 ei(N,N,N, o);
      while ( ei.inBounds() )
      {
	std::vector<K3DParent> pv;

	size_t i,j, k;
	ei.getc( i,j, k);
	size_t dx= k* N2 + j *N + i;

	ei.FilteredParentList(pv);
	
	double val = KAverageParents(cube, N, pv);

	val += KMidPointVar_EI( pv.size(), o ) * rfn.sample();

	cube[dx]=val;

	ei.next();

      }

      

    }
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
      std::cerr<<"Received "<<np<<" parents"<<std::endl;
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

  



  

    

}



