/**
   \file kolmogorov_3d.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk> 

   June 2007   


*/

#include "kolmogorov_3d.hxx"

#include <cmath>

#include "bnrandom.hxx"

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
    const double facediagstddev  = 1.54413161;
    const double bodydiagstddev  = 2.46685105;

    for (size_t l =0 ; l < 8 ; ++l)
    {
      size_t dx= cubevertices[l].i * (N-1) + 
	cubevertices[l].j * N *(N-1) + 
	cubevertices[l].k *N2 *(N-1);
      cube[dx] = vrtexstddev * rfn.sample();
    }
    
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


}



