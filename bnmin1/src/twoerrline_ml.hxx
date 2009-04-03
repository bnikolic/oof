/** 
    \file twoerrline_imp.hxx

    Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
    Initial version 2009    
    
    Maximum likelihood tools for fitting a line to two noisy
    coordinates

*/
#ifndef _BNMIN1_TWOERRLINE_ML_HXX__
#define _BNMIN1_TWOERRLINE_ML_HXX__

#include <boost/numeric/ublas/vector.hpp>
#include "gradientmodel.hxx"

namespace Minim {

  namespace u = boost::numeric::ublas;

  /**
     Fit straight-line model to data with noise in both coordinates
     
   */
  class LineTwoErrML:
    public LGradientModel
  {

    u::vector<double> xobs;
    u::vector<double> yobs;
    const double sigmax;
    const double sigmay;

  public:


    // ------------ Construction / Destruction ----------------
    
    LineTwoErrML(const std::vector<double> &xvals,
		 const std::vector<double> &yvals,
		 double sigmax,
		 double sigmay);

    
    

  };


}

#endif
