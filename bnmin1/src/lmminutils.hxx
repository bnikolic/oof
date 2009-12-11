/**
   Bojan Nikolic <bojan@bnikolic.co.uk> 
   Initial version 2005

   This file is part of BNMin1 and is licensed under GNU General
   Public License version 2.

   \file lmminutils.hxx
   
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
