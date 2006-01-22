/*
  Bojan Nikolic
  $Id: phycosmo.cxx,v 1.2 2006/01/22 21:12:30 bnikolic Exp $

*/

#include "phycosmo.hxx"

#include <gsl/gsl_integration.h>

#include "phyconstants.hxx"


static double cr_integrand(double z, void * params );

/// Reference for all this is:
/// http://nedwww.ipac.caltech.edu/level5/Hogg/frames.html
double cr_integrand(double z, void * params )
{

  double omega_0= ((double *)params)[0];
  double omega_L= ((double *)params)[1];


  double res= 1.0 / sqrt( gsl_pow_3(1+z) * omega_0 + omega_L  + (1- omega_0 - omega_L) * gsl_pow_2(1+z)    ) ;

  return res;
}


namespace BNLib{

  namespace Phy {

    RelCosmo::RelCosmo( double H0_km_s_Mpc  , 
			double  Omega_0 , 
			double Omega_L ):
	H0(H0_km_s_Mpc) , 
	O0(Omega_0) , 
	OL(Omega_L)  ,
	c_km_s ( c_m_s * 1e-3)

    {
    }

    
    double RelCosmo::D_Mpc(double z) 
    { 
      return  c_km_s / H0 * comovingr(z)  ; 
    }

    double RelCosmo::D_m(double z) 
    { 
      return  D_Mpc(z) * Mpc_m ; 
    }
      
    double RelCosmo::Dangular_m(double z) 
    { 
      return D_m(z) / (1 + z) ; 
    } 

    double RelCosmo::Dangular_Mpc(double z) 
    { 
      return D_Mpc(z) / (1 + z) ; 
    } 

    double RelCosmo::comovingr (double z )
    {
      const int nsteps=1000;
      double result, error;
      double pars[2];
      
      if ( z > 0 ) {
	/* 
	   Allocate working space for integration
	*/
	gsl_integration_workspace * work 
	  = gsl_integration_workspace_alloc(nsteps);
	
	gsl_function F;
	F.function = &cr_integrand;
	F.params = pars;
	
	pars[0]=O0 ;
	pars[1]=OL ;
	
	gsl_integration_qags (&F, 0 , z, 0, 1e-4, nsteps,
			      work, &result, &error); 
	
	gsl_integration_workspace_free(work); 
      } else {
	result =0;
      }
      
      return result;

    }

  }
}


