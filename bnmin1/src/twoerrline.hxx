/**
   \file twoerrline.hxx

   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2009

   Fit lines to data which have errors in both coordinates
*/
#ifndef _BNMIN1_TWOERRLINE_HXX__
#define _BNMIN1_TWOERRLINE_HXX__

#include <vector>
#include <boost/array.hpp>

namespace Minim {

  struct LineFit
  {
    /// Linear coefficient
    double a;
    /// Offset coefficient
    double b;
    /// Covariance matrix
    boost::array<double,4> cv;
  };

  /** Compute maximum-likelihood line-fit to data with known errors in
      both x and y values.

      Follows numerical recipes

   */
  void LFit_MaxL(const std::vector<double> &xvals,
		 const std::vector<double> &yvals,
		 double sigma_x,
		 double sigma_y,
		 LineFit &res);

}

#endif
