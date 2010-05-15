/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file ellipsoids.cxx

   Computation and use of ellipsoids releated to sets of points
*/

#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>


#include "ellipsoids.hxx"

namespace Minim {
  
  template<class T>
  bool InvertMatrix(const ublas::matrix<T> &input,
		    ublas::matrix<T> &inverse) 
  {
    using namespace boost::numeric::ublas;
    typedef permutation_matrix<std::size_t> pmatrix;
    // create a working copy of the input
    matrix<T> A(input);
    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());
    
    // perform LU-factorization
    int res = lu_factorize(A,pm);
    if( res != 0 ) return false;
    
    // create identity matrix of "inverse"
    inverse.assign(ublas::identity_matrix<T>(A.size1()));
    
    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);
    
    return true;
  }

  void InvertLP(const ublas::matrix<double> &Lambdap,
		ublas::matrix<double> &LpInv)
  {
    bool res=InvertMatrix(Lambdap, LpInv);
  }

  void Lift(const ublas::matrix<double> &A,
	    ublas::matrix<double> &Ap)
  {
    
  }

  


}


