/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2005

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file lmminutils.cxx

*/

#include "lmminutils.hxx"

#include <memory>
#include <cmath>

#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>

#include "lmmin.hxx"

namespace Minim {



  gsl_permutation *  GetPerm( LMMin & l ) 
  {
    
    gsl_permutation *  res( gsl_permutation_alloc (l.ipvt.size()));
    
    // Permutations are taken from F77 hence probably 1-relative
    // rather than 0-relative which are taken by gsl.
    for (unsigned i (0) ; i < l.ipvt.size(); ++i )
      res->data[i] = l.ipvt[i]-1;

    return res;
  }

  gsl_matrix * GetR ( LMMin &l )
  {
    
    unsigned n = l.NParam();
    unsigned m = l.NRes();

    gsl_matrix *  res( gsl_matrix_alloc (m,n ));


    for (unsigned i (0) ; i < m ; ++i )
      for (unsigned j(0) ; j < n ; ++j )
	gsl_matrix_set( res , i, j , l.fjac[ i + j * m ] );
    return res;

  }

  std::vector<double> * CVMatrix ( LMMin &l ,     double epsrel  ) 
  {


    
    unsigned n = l.NParam();

    std::auto_ptr<   std::vector<double> > res ( new   std::vector<double>( n * n ));

    gsl_matrix *  r = GetR(l);

    gsl_matrix *  covar (gsl_matrix_alloc (n,n ) );

    gsl_permutation *perm = GetPerm(l);
    
    



    
    double tolr = epsrel * fabs(gsl_matrix_get(r, 0, 0));
    
    unsigned k,j,i,kmax;
    kmax=0;
    
    for (k = 0 ; k < n ; k++)
      {
       double rkk = gsl_matrix_get(r, k, k);

       if (fabs(rkk) <= tolr)
	 {
	   break;
	 }

       gsl_matrix_set(r, k, k, 1.0/rkk);

       for (j = 0; j < k ; j++)
	 {
	   double t = gsl_matrix_get(r, j, k) / rkk;
	   gsl_matrix_set (r, j, k, 0.0);

	   for (i = 0; i <= j; i++)
	     {
	       double rik = gsl_matrix_get (r, i, k);
	       double rij = gsl_matrix_get (r, i, j);

	       gsl_matrix_set (r, i, k, rik - t * rij);
	     }
	 }
       kmax = k;
     }

   /* Form the full upper triangle of the inverse of R^T R in the full
      upper triangle of R */

   for (k = 0; k <= kmax ; k++)
     {
       for (j = 0; j < k; j++)
	 {
	   double rjk = gsl_matrix_get (r, j, k);

	   for (i = 0; i <= j ; i++)
	     {
	       double rij = gsl_matrix_get (r, i, j);
	       double rik = gsl_matrix_get (r, i, k);

	       gsl_matrix_set (r, i, j, rij + rjk * rik);
	     }
	 }

       {
	 double t = gsl_matrix_get (r, k, k);

	 for (i = 0; i <= k; i++)
	   {
	     double rik = gsl_matrix_get (r, i, k);

	     gsl_matrix_set (r, i, k, t * rik);
	   };
       }
     }

   /* Form the full lower triangle of the covariance matrix in the
      strict lower triangle of R and in w */

   for (j = 0 ; j < n ; j++)
     {
       size_t pj = gsl_permutation_get (perm, j);

       for (i = 0; i <= j; i++)
	 {
	   size_t pi = gsl_permutation_get (perm, i);

	   double rij;

	   if (j > kmax)
	     {
	       gsl_matrix_set (r, i, j, 0.0);
	       rij = 0.0 ;
	     }
	   else 
	     {
	       rij = gsl_matrix_get (r, i, j);
	     }

	   if (pi > pj)
	     {
	       gsl_matrix_set (r, pi, pj, rij); 
	     } 
	   else if (pi < pj)
	     {
	       gsl_matrix_set (r, pj, pi, rij);
	     }

	 }

       { 
	 double rjj = gsl_matrix_get (r, j, j);
	 gsl_matrix_set (covar, pj, pj, rjj);
       }
     }


   /* symmetrize the covariance matrix */

   for (j = 0 ; j < n ; j++)
     {
       for (i = 0; i < j ; i++)
	 {
	   double rji = gsl_matrix_get (r, j, i);

	   gsl_matrix_set (covar, j, i, rji);
	   gsl_matrix_set (covar, i, j, rji);
	 }
     }

   
   for (i = 0 ; i < n ; i++)
     {
       for (j = 0; j < n ; j++)
	 {
	   (*res)[j*n+i]= gsl_matrix_get (covar, i, j);
	 }
     }

   gsl_matrix_free(r);
   gsl_matrix_free(covar);
   gsl_permutation_free(perm);
   return res.release();
  }



}


