/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file ellipsoids.cxx

   Computation and use of ellipsoids releated to sets of points
*/

#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include <iostream>
#include <boost/numeric/ublas/io.hpp>

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
    Ap.resize(A.size1()+1,
	      A.size2());
    ublas::matrix_range<ublas::matrix<double> > 
      sub(Ap, 
	  ublas::range(0, A.size1()), 
	  ublas::range(0, A.size2()));
    sub.assign(A);
    ublas::row(Ap, Ap.size1()-1)=ublas::scalar_vector<double>(A.size2(),1.0);

  }

  void genDiag(const ublas::vector<double> &p,
	       ublas::matrix<double> &res)
  {
    res.assign(ublas::zero_matrix<double>(p.size(), 
					  p.size()));
    for(size_t i=0; i<p.size(); ++i)
    {
      res(i,i)=p(i);
    }    
  }

  void KaLambda(const ublas::matrix<double> &Ap,
		const ublas::vector<double> &p,
		ublas::matrix<double> &Lambdap)
  {
    
    ublas::matrix<double> dp(p.size(), p.size());
    genDiag(p, dp);

    dp=ublas::prod(dp, ublas::trans(Ap));
    Lambdap=ublas::prod(Ap, 
			dp);
  }

  double KhachiyanIter(const ublas::matrix<double> &Ap,
		       ublas::vector<double> &p)
  {
    /// Dimensionality of the problem
    const size_t d=Ap.size1()-1;

    ublas::matrix<double> Lp;
    ublas::matrix<double> M;
    KaLambda(Ap, p, Lp);
    ublas::matrix<double> ILp(Lp.size1(), Lp.size2());
    InvertLP(Lp, ILp);
    M=ublas::prod(ILp, Ap);
    M=ublas::prod(ublas::trans(Ap), M);

    double maxval=0;
    size_t maxi=0;
    for(size_t i=0; i<M.size1(); ++i)
    {
      if (M(i,i) > maxval)
      {
	maxval=M(i,i);
	maxi=i;
      }
    }
    const double step_size=(maxval -d - 1)/((d+1)*(maxval-1));
    ublas::vector<double> newp=p*(1-step_size);
    newp(maxi) += step_size;

    const double err= ublas::norm_2(newp-p);
    p=newp;
    return err;
    
  }

  void KaInvertDual(const ublas::matrix<double> &A,
		    const ublas::vector<double> &p,
		    ublas::matrix<double> &Q,
		    ublas::vector<double> &c
		    )
  {
    const size_t d=A.size1();
    ublas::matrix<double> dp(p.size(), p.size());
    genDiag(p, dp);

    ublas::matrix<double> PN=ublas::prod(dp, ublas::trans(A));
    PN=ublas::prod(A, PN);

    ublas::vector<double> M2=ublas::prod(A, p);
    ublas::matrix<double> M3=ublas::outer_prod(M2, M2);

    ublas::matrix<double> invert(PN.size1(), PN.size2());
    InvertLP(PN- M3, invert);
    
    Q.assign( 1.0/d *invert);
    c=ublas::prod(A, p);
        
    
  }

  double KhachiyanAlgo(const ublas::matrix<double> &A,
		       double eps,
		       size_t maxiter,
		       ublas::matrix<double> &Q,
		       ublas::vector<double> &c)
  {
    ublas::vector<double> p=ublas::scalar_vector<double>(A.size2(), 1.0)*(1.0/A.size2());

    ublas::matrix<double> Ap;
    Minim::Lift(A, Ap);

    double ceps=eps*2;
    for (size_t i=0;  i<maxiter && ceps>eps; ++i)
    {
      ceps=KhachiyanIter(Ap, p);
    }

    KaInvertDual(A, p, Q, c);
      
    return ceps;


  }

  


}


