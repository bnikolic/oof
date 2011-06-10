// Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
// Initial version December 2009
//
// This file is part of BNMin1 and is licensed as described in file
// COPYING

/**
   \file bayesline.hxx
   Full Bayesian line fitting with error in both coordinates
*/
#ifndef _BNMIN1_APP_BAYESLINE_HXX__
#define _BNMIN1_APP_BAYESLINE_HXX__

#include <vector>
#include <list>

#include "../src/minimmodel.hxx"
#include "../src/twoerrline.hxx"

namespace Minim {

  // Forward declarations
  class WPPoint;

  /**
   */
  class LineLkl :
    public Minim::MLikelihood
  {

    std::vector<double> x,y;
    
    double sigmax; 
    double sigmay;

  public:

    // -------------------  Public data ----------------

    // Model parameters
    double x0, y0;
    /// Log10 range in the x-coordinate 
    double Rx;
    /// Log10 range in the y-coordinate
    double Ry;

    
    // ------------------- Construction -----------------
    
    LineLkl(const std::vector<double> &x,
	    const std::vector<double> &y,
	    double sigmax,
	    double sigmay);

    // ------------------ Public interface ---------------

    double lLikely(void) const;
    void AddParams(std::vector< Minim::DParamCtr > &pars);


  };


  /** Compute the point estimates of slope and intercept and their
      covariance from posterior distribution 
  */
  void  margin(const std::list<WPPoint> &l,
	       double Z,
	       LineFit &res);
    


}

#endif

