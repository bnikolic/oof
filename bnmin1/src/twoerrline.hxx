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

  /** \brief Results of a line fit

   */
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

      Computes the best fit using standard BFGS minimisation of the
      chi-squared function. Does not compute the covariance matrix.

   */
  void LFit_MaxL(const std::vector<double> &xvals,
		 const std::vector<double> &yvals,
		 double sigma_x,
		 double sigma_y,
		 LineFit &res);

  /** Compute maximum-likelihood line-fit to data with known errors in
      both x and y values.

      This version uses the lavenberg-marquand algorithm. This version
      calculates the co-variance matrix.

      \bug Monte-Carlo simulations suggest that there is a factor two
      error in the calculation of the variances and covariances. This
      should not, however, affect relative errors.

   */
  void LFit_LM(const std::vector<double> &xvals,
	       const std::vector<double> &yvals,
	       double sigma_x,
	       double sigma_y,
	       LineFit &res);

}

#endif
