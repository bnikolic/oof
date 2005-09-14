/*
 * Bojan Nikolic
 *
 * Some utilities to deal with difficult integrations.
 * 
 * $Id: integrateutils.hxx,v 1.2 2005/09/14 17:40:16 bnikolic Exp $
 */

#ifndef _BNLIB_INTEGRATEUTILS_HXX__
#define _BNLIB_INTEGRATEUTILS_HXX__

#include <vector>

namespace BNLib {

  // Forward declarations
  class UnaryDD;


  /*! Integrate a function section by section in order to force a more
   *  accurate result. By customising sections can focus ranges with
   *  known difficult features. Uses adaptive integrator. bounds[0] is
   *  xmin, bounds[bounds.size-1] is xmax.
   */
  double SectionInteg (UnaryDD &fn , double epsabs, 
		       double epsrel, unsigned maxsteps,
		       std::vector<double> &bounds );


  /*! Evaluate the integral from xmin to xmax by subdividing the range
   *  into equal ranges in log-space with ratio step.
   */
  double LogSecInteg ( UnaryDD &fn , double xmin, double xmax, double step , 
		       double epsabs, 
		       double epsrel, unsigned maxsteps );
  
  


}

#endif
