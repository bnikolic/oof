/** 
    \file integrateutils.hxx
    Bojan Nikolic <bojan@bnikolic.co.uk>
    Some utilities to deal with difficult integrations.
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

  /*! Evaluate the integral of the product of two functions */
  double ProdInteg ( UnaryDD &fn1 , UnaryDD &fn2 , double xmin, double xmax, 
		     double epsrel, unsigned  maxsteps);
  
  
  


}

#endif
