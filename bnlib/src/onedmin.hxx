/*
  Bojan Nikolic
  $Id: onedmin.hxx,v 1.1 2005/05/14 20:02:03 bnikolic Exp $

  One dimensional minimisation
*/
#ifndef _BNLIB_OEDMIN_HXX__
#define _BNLIB_OEDMIN_HXX__

namespace BNLib {

  class UnaryDD;

  /// Returns the minimum of a one-dimensional function
  double Min1D ( UnaryDD & fn , 
		 double xmin, double xmax,
		 double xguess,
		 double epsrel,
		 double epsabs,
		 unsigned maxiter);


}

#endif
