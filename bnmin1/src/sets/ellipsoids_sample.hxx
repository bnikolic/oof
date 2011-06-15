/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2010

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2

   \file ellipsoids_sample.hxx

   Sampling from volumes defined by (hyper-)ellipsoids
*/
#ifndef _BNMIN1_SETS_ELIIPSOIDS_SAMPLING_HXX__
#define _BNMIN1_SETS_ELIIPSOIDS_SAMPLING_HXX__

#include <vector>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace Minim {

  namespace ublas=boost::numeric::ublas;  

  /** \brief Uniform sampling from an ellipsoid
   */
  class EllipsoidSampler
  {
    /** The random number generator engine
     */
    boost::mt19937 &rng;

    /** Cholesky factorisation of the axes definition vector
     */
    ublas::matrix<double> Qu;

    /** Centre of the ellipsoid
     */
    ublas::vector<double> c;
    
  public:

    /**
       \param Q Matrix defining the axes of the ellipsoid

       \param c Vector definning the centre of the ellipsoid

       \param rng Engine for generating random numbers

     */
    EllipsoidSampler(ublas::matrix<double> Q,
		     ublas::vector<double> c,
		     boost::mt19937 &rng);

    /** \brief Generate a point within ellipsoid and store in v
     */
    void operator() (ublas::vector<double> &v,
		     double s=1.0);

    void operator() (std::vector<double> &v,
		     double s=1.0);


  };


}

#endif
