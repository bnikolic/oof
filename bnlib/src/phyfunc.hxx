/*
  Bojan Nikolic

  Some useful functions from physics
*/
#ifndef _BNLIB_PHYFUNCS_HXX__
#define _BNLIB_PHYFUNCS_HXX__

namespace BNLib {

  namespace Phy {
    
    /// This should be  the Planck fn in units of W per Hz per m^2 per
    /// steradian.
    double Planck_dnu (double T, double nu );

    /// This should be the Planck fn in terms of dE as a function of E
    double PlanckE_dE (double T, double E );
    
    
  }

}


#endif
