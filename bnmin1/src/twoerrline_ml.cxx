/** 
    \file twoerrline_imp.cxx

    Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
    Initial version 2009    


*/

#include "twoerrline_ml.hxx"

#include <boost/numeric/ublas/storage.hpp>


namespace Minim {

  LineTwoErrML::LineTwoErrML(const std::vector<double> &xvals,
			     const std::vector<double> &yvals,
			     double sigmax,
			     double sigmay):
    xobs(xvals.size()),
    yobs(yvals.size()),
    sigmax(sigmax),
    sigmay(sigmay)
  {
    for (size_t i=0; i<xobs.size(); ++i)
    {
      xobs[i]=xvals[i];
      yobs[i]=yvals[i];
    }
  }

}




