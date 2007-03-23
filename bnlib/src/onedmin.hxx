/*
  Bojan Nikolic

  One dimensional minimisation
*/
#ifndef _BNLIB_OEDMIN_HXX__
#define _BNLIB_OEDMIN_HXX__

#include <stdexcept>

namespace BNLib {

  class UnaryDD;

  /// Returns the minimum of a one-dimensional function
  double Min1D ( UnaryDD & fn , 
		 double xmin, double xmax,
		 double xguess,
		 double epsrel,
		 double epsabs,
		 unsigned maxiter);

  /*! 
   * This is the class thrown if the mimiser fails 
   */
  class NoMinFound  : std::runtime_error 
  {

  public:

    NoMinFound(void) :
      std::runtime_error("No Minimum found")
    {
    }
    
  };


}

#endif
