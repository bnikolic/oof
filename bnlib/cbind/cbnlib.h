/*
  Bojan Nikolic
  $Id: cbnlib.h,v 1.1 2005/05/05 12:52:07 bnikolic Exp $

  C binding for bnlib
*/
#ifndef _BNLIB_CBNLIB_H__
#define _BNLIB_CBNLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

  // treat pointers to interpolator as void pointers and convert
  typedef void * bnlib_interpolator;

  // Make new (GSL) interpolator
  bnlib_interpolator bnlib_Cinterpolator ( double * xvals, double *yvals,
					   unsigned size);

  // Evaluate an interpolator at value xval
  double bnlib_EvalIplt ( bnlib_interpolator iplt, double xval);

  // Destroy an interpolator
  void  bnlib_Dinterpolator( bnlib_interpolator iplt );

  
  
  


#ifdef __cplusplus
}
#endif


#endif
