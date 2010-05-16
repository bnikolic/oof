/// Bojan Nikolic <bojan@bnikolic.co.uk>
/// 
/// Tests of the sets routines

#define BOOST_AUTO_TEST_MAIN

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <iostream>

#include "../config.h"

#include "sets/ellipsoids.hxx"

namespace ublas = boost::numeric::ublas;

BOOST_AUTO_TEST_CASE(InvertIdentity)
{
  ublas::identity_matrix<double> id(5);
  ublas::matrix<double> idc=id;
  idc(1,0)=1;
  ublas::matrix<double> res(5,5);
  Minim::InvertLP(id, res);
  Minim::InvertLP(idc, res);
  std::cout<<res
	   <<std::endl;
}

BOOST_AUTO_TEST_CASE(KaLift)
{
  ublas::identity_matrix<double> id(5);
  ublas::matrix<double> res;
  Minim::Lift(id, res);
  std::cout<<res
	   <<std::endl;
}

BOOST_AUTO_TEST_CASE(KaLambda_basic)
{
  ublas::matrix<double> ap=ublas::identity_matrix<double>(4);
  ap(3,0)=1;

  ublas::vector<double> p=ublas::scalar_vector<double>(4, 1.0);

  ublas::matrix<double> res;

  Minim::KaLambda(ap, p, res);

  BOOST_CHECK_EQUAL(res(0,0), 1);
  BOOST_CHECK_EQUAL(res(0,3), 1);
  BOOST_CHECK_EQUAL(res(3,3), 2);
  BOOST_CHECK_EQUAL(res(3,0), 1);
  BOOST_CHECK_EQUAL(res(0,1), 0);
}


BOOST_AUTO_TEST_CASE(KhachiyanAlgo_reallybasic)
{
  ublas::matrix<double> A(2,6);
  A(0,0)=1;  A(1,0)=0;
  A(0,1)=-1; A(1,1)=0;
  A(0,2)=0; A(1,2)=1;
  A(0,3)=0; A(1,3)=-1;
  A(0,4)=0; A(1,4)=0;
  A(0,5)=0.5; A(1,5)=0;

  ublas::matrix<double> Q(2,2);
  ublas::vector<double> c(2);

  Minim::KhachiyanAlgo(A, 0.01, 100, Q, c);

  std::cout<<Q<<std::endl;
}





