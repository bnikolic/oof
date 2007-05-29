/**
   \file kolmogorov_spec.cxx

   Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
   Initial version: May 2007

*/

#include "kolmogorov_spec.hxx"

#include <cmath>

namespace BNLib {

  KolPowerLawFn::KolPowerLawFn (double xi):
    xi(xi)
  {
  }

  KolPowerLawFn::KolPowerLawFn (LawsPreDefined l):
    xi(GetPowerLaw(l))
  {
  }


  double KolPowerLawFn::GetPowerLaw( LawsPreDefined l )
  {
    if ( l == D3Thin )
    {
      return 2.0/3.0;
    }
    else if ( l == D3Thick )
    {
      return 5.0/3.0;
    }
    else
    {
      throw "Unknown power law";
    }

  }

  double KolPowerLawFn::operator() (double x)
  {
    return 6.88 * pow(x, xi);
  }


}
   
