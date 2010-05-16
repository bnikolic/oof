/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file ellipsoids.hxx

   Computation and use of ellipsoids releated to sets of points
*/
#ifndef _BNMIN1_SETS_ELIIPSOIDS_HXX__
#define _BNMIN1_SETS_ELIIPSOIDS_HXX__

#include <boost/numeric/ublas/vector.hpp>

namespace Minim {

  namespace ublas=boost::numeric::ublas;  

  /**  Lift to a higher dimensional space that so that points are
       centrally symmetric.

       The input data are arranged in columns of A

       c.f. Eq 9
   */
  void Lift(const ublas::matrix<double> &A,
	    ublas::matrix<double> &Ap);


  /** Compute the result of operator Lambda

      c.f. eq. 13

      \param Lambdap The result is stored here
   */
  void KaLambda(const ublas::matrix<double> &Ap,
		const ublas::vector<double> &p,
		ublas::matrix<double> &Lambdap);

  /** Calculate the inverse of a result of lambda operator
   */
  void InvertLP(const ublas::matrix<double> &Lambdap,
		ublas::matrix<double> &LpInv);
  

  /** Iterate the Khachiyan algorithm one step
      
      \param Ap is the lifted data set 

      \param p is the current guess, and the iterated guess is stored
      here

      \returns Error estimate 
   */
  double KhachiyanIter(const ublas::matrix<double> &Ap,
		       ublas::vector<double> &p);


  /** Invert from the dual problem back to real space

      \param Q The ellipsiod matrix
      \param c The centre of the ellipse
   */
  void KaInvertDual(const ublas::matrix<double> &A,
		    const ublas::vector<double> &p,
		    ublas::matrix<double> &Q,
		    ublas::vector<double> &c
		    );


  double KhachiyanAlgo(const ublas::matrix<double> &A,
		       double eps,
		       size_t maxiter,
		       ublas::matrix<double> &Q,
		       ublas::vector<double> &c);


  struct KhachiyanEllipsoid
  {
    ublas::matrix<double> Q;
    ublas::vector<double> c;
  };

  struct MCPoint;


  //void SampleEllipsoid();
  //SampleSphere
  
  

}

#endif
