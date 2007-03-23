/*
  Bojan Nikolic


*/

#include "phyfunc.hxx"

#include <cmath>

#include "phyconstants.hxx"

namespace BNLib {

  namespace Phy {

    double Planck_dnu (double T, double nu )
    {
      return 2* h_J_s / pow(c_m_s,2) *
	pow(nu, 3) / ( exp ( ( h_J_s * nu ) / ( T * k_J_K ) ) - 1) ;
    }

    double PlanckE_dE (double T, double E )
    {
      return 1.0/ Phy::c_m_s * 
	2.0 / ( pow(Phy::c_m_s,2) * pow(Phy::h_J_s,3) ) *
	pow(E,3) / ( exp( E/ (Phy::k_J_K * T ) ) -1.0 ) ;
    }
    
  }

}



