/**
   \file gradientmodel.hxx
   
   Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
   Initial version 2008

   Models with gradients of the likelihood function
*/
#ifndef _BNMIN_GRADIENTMODEL_HXX__
#define _BNMIN_GRADIENTMODEL_HXX__

#include "minimmodel.hxx"

namespace Minim {

  /** \brief A model that defines the gradients of the likelihood,
      enabling gradient and quasi-newton type searches for extrema
   */
  class LGradientModel :
    public MLikelihood
  {

  public:

    /** Compute the gradient of the likelihood with respect to each
	parameter.
     */ 
    virtual void lGrd(std::vector<double> &o) const = 0;
  };

}

#endif
