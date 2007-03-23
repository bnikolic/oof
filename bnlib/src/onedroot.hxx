/*
  Bojan Nikolic

  One dimensional root finding
*/
#ifndef __BNLIB_ONEDROOT_HXX__
#define __BNLIB_ONEDROOT_HXX__

namespace BNLib {

  class UnaryDD;

  /*! Finds a root of the supplied function fn
   *
   *  Root is sought in interval xmin, xmax
   *  \param epsrel is the desired absolute accuracy
   *  \param epsrel is the desired relative accuracy
   */
  double Root1D ( UnaryDD & fn , 
		  double xmin, double xmax,
		  double epsabs, double epsrel,
		  unsigned maxiter
		  );

  /*! Find a root using   derivative information */
  double Root1D(  UnaryDD & fn ,  UnaryDD & dfn , 
		  double xguess,
		  double xmin, double xmax,
		  double epsabs, double epsrel,
		  unsigned maxiter);
		  

}

#endif
