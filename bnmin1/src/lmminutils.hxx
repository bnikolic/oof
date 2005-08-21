/*
  Bojan Nikolic
  $Id: lmminutils.hxx,v 1.1 2005/08/21 02:42:03 bnikolic Exp $

  Utility functions for the Lavenberg-Marquant minimisation algorithm.
  
*/
#ifndef _BNMIN1_LMMINUTILS_HXX__
#define _BNMIN1_LMMINUTILS_HXX__

#include <vector>

namespace Minim {

  // Forwards
  class LMMin;

  /*! Returns the covariance matrix of the parameters once
   *  minimisation is complete.
   */
  std::vector<double> * CVMatrix ( LMMin &l ,     double epsrel );



}

#endif
