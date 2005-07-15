/*
  Bojan Nikolic
  $Id: onedroot.hxx,v 1.2 2005/07/15 21:04:56 bnikolic Exp $

  One dimensional root finding
*/
#ifndef __BNLIB_ONEDROOT_HXX__
#define __BNLIB_ONEDROOT_HXX__

namespace BNLib {

  class UnaryDD;

  /*! Finds a root of the supplied function fn
   *
   *  Root is sought in interval xmin, xmax
   *  epsrel is the desired absolute accuracy
   *  epsrel is the desired relative accuracy
   */
  double Root1D ( UnaryDD & fn , 
		  double xmin, double xmax,
		  double epsabs, double epsrel,
		  unsigned maxiter
		  );

}

#endif
