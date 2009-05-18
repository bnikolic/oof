/**
   \file mcpoint.hxx
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>

   Structure representing a Markov Chain point
*/

#ifndef _BNMIN1_MCPOINT_HXX__
#define _BNMIN1_MCPOINT_HXX__

#include <vector>

namespace Minim {

  /** \brief Data to be recorded at each point in an MCMC distribution
  */
  struct MCPoint
  {
    /// The actual parameters
    std::vector<double> p;
    /// Log-likelihood of this point
    double ll;
    /// A vector to store derived quantities at sample of the
    /// distribution
    std::vector<double> fval;
  };

  /** \brief Define ordering of MCPoints on basis of their likelihood

      Should be useful for nested sampling
  */
  inline bool operator< (const MCPoint &a, const MCPoint &b)
  {
    return a.ll < b.ll;
  }



}

#endif
